#include "Main.h"
#include <Psapi.h>
inline UCHAR CodeSave[9];
inline UCHAR GDIcode[17];
inline int AntiScreenShotCount, AntiScreenShotCount_GDI, AntiScreenShotCount_CRC, AntiScreenShotCount_CRCa, AntiScreenShotCount_CRCBB, AntiScreenShotCount_Dx, AntiScreenShotCount_CRCb=NULL, Dxgi_PresentReCount,
DxCount,GdiCount,GdiCountA,dx判断, DX函数监控, AntiScreenShotCount_GDLL;
inline BOOL IsAntiScreenShot, ForceByPassAntiScreenShot,判断是否, GDLL判断是否,GDI判断是否,还原写入,GDLL修复, RCXxiufu = true;
inline ULONG64 Dxgi_Present,RAX指针缓存, GDLL缓存, GDI缓存,RAX1,绘制全局地址;
struct Memory {
public:
    Memory(ULONG64 Address) {
        m_Address = Address;
    }
    Memory(ULONG64 Address, bool bEnable) {
        m_Address = Address;
        if (bEnable) Enable();
    }
    ~Memory() {
        OldProt = -1;
        m_Address = -1;
    }
    void Enable() {
        VirtualQuery((PVOID)m_Address, &mbi, sizeof(mbi));
        VirtualProtect((PVOID)m_Address, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &OldProt);
    }
    void Disable() {
        VirtualProtect((PVOID)m_Address, mbi.RegionSize, OldProt, NULL);
    }
private:
    DWORD OldProt = 0;
    ULONG64 m_Address = 0;
    MEMORY_BASIC_INFORMATION mbi = {};
};
struct SetRwc {
public:
    SetRwc(ULONG64 Address) {
        m_Address = Address;
    }
    SetRwc(ULONG64 Address, bool bEnable, SIZE_T pSize = 0) {
        m_Address = Address;
        dwSize = pSize;
        if (bEnable) Enable();
    }
    ~SetRwc() {
        OldProt = -1;
        m_Address = -1;
    }
    void Enable() {
        if (0 == dwSize) {
            VirtualQuery((PVOID)m_Address, &mbi, sizeof(mbi));//这个东西啊
            VirtualProtect((PVOID)m_Address, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &OldProt);
        }
        else {
            VirtualProtect((PVOID)m_Address, dwSize, PAGE_EXECUTE_READWRITE, &OldProt);
        }

    }
    void Disable() {
        if (0 == dwSize) {
            VirtualProtect((PVOID)m_Address, mbi.RegionSize, OldProt, NULL);
        }
        else {
            VirtualProtect((PVOID)m_Address, dwSize, OldProt, NULL);
        }


    }
private:
    DWORD OldProt = 0;
    ULONG64 m_Address = 0;
    SIZE_T dwSize = 0;
    MEMORY_BASIC_INFORMATION mbi = {};
};
BOOLEAN MaskCompare(PVOID buffer, LPCSTR pattern, LPCSTR mask) {
    for (auto b = reinterpret_cast<PBYTE>(buffer); *mask; ++pattern, ++mask, ++b) {
        if (*mask == 'x' && *reinterpret_cast<LPCBYTE>(pattern) != *b) {
            return FALSE;
        }
    }

    return TRUE;
}
PBYTE FindPattern(PVOID base, DWORD size, LPCSTR pattern, LPCSTR mask) {
    size -= static_cast<DWORD>(strlen(mask));

    for (auto i = 0UL; i < size; ++i) {
        auto addr = reinterpret_cast<PBYTE>(base) + i;
        if (MaskCompare(addr, pattern, mask)) {
            return addr;
        }
    }

    return NULL;
}
PBYTE FindPattern(LPCSTR pattern, LPCSTR mask, HMODULE hMod) {
    MODULEINFO info = { 0 };
    GetModuleInformation(GetCurrentProcess(), hMod, &info, sizeof(info));

    return FindPattern(info.lpBaseOfDll, info.SizeOfImage, pattern, mask);
}
DWORD SearchByteBase(std::string markCode, ULONG64 memBeginAddr, ULONG64 memEndAddr, ULONG64 retAddr[], int deviation, bool isAll) {
    //HANDLE hProcess = GetCurrentProcess();
    //----------------------处理特征码----------------------//
    //去除所有空格
    if (!markCode.empty()) {
        int index = 0;
        while ((index = markCode.find(' ', index)) >= 0) {
            markCode.erase(index, 1);
        }
        index = 0;
        while (true) {
            // 删掉头部通配符
            index = markCode.find("??", index);
            if (index == 0) {
                markCode.erase(index, 2);
            }
            else {
                break;
            }
        }
    }

    // 特征码长度不能为单数
    if (markCode.length() % 2 != 0) return 0;

    // 特征码长度
    int len = markCode.length() / 2;

    // Sunday算法模板数组的长度
    int nSundayLen = len;

    // 将特征码转换成byte型
    BYTE* pMarkCode = new BYTE[len];
    for (int i = 0; i < len; i++) {
        std::string tempStr = markCode.substr(i * 2, 2);
        if (tempStr == "??") {
            pMarkCode[i] = 0x3F;
            if (nSundayLen == len) nSundayLen = i;
        }
        else {
            pMarkCode[i] = strtoul(tempStr.c_str(), 0, 16);
        }
    }
    // --------------------------end------------------------- //

    // Sunday算法模板数组赋值，+1防止特征码出现FF时越界
    int aSunday[0xFF + 1] = { 0 };
    for (int i = 0; i < nSundayLen; i++) {
        aSunday[pMarkCode[i]] = i + 1;
    }

    // 起始地址
    const ULONG64 dwBeginAddr = memBeginAddr;
    // 结束地址
    const ULONG64 dwEndAddr = memEndAddr;
    // 当前读取的Memory块地址
    ULONG64 dwCurAddr = dwBeginAddr;
    // 存放Memory数据的缓冲区
    BYTE* pMemBuffer = NULL;
    // 计算参数retAddr[]数组的长度
    // int nArrayLength = sizeof(retAddr) / sizeof(*retAddr);
    int nArrayLength = 0;
    for (int i = 0; ; i++) {
        if (*(retAddr + i) != 0) {
            nArrayLength = i;
            break;
        }
    }
    // 偏移量
    int nOffset;
    // 数组下标：Memory、特征码、返回地址
    int i = 0, j = 0, nCount = 0;

    // Memory信息
    MEMORY_BASIC_INFORMATION mbi;

    // 记录起始搜索时间
    clock_t nBeginTime = clock();

    // 扫描Memory
    while (dwCurAddr < dwEndAddr)
    {
        // 查询地址空间中Memory地址的信息
        memset(&mbi, 0, sizeof(MEMORY_BASIC_INFORMATION));
        //if (::VirtualQueryEx(hProcess, (LPCVOID)dwCurAddr, &mbi, sizeof(mbi)) == 0) {
        if (VirtualQuery((LPCVOID)dwCurAddr, &mbi, sizeof(mbi)) == 0) {
            goto end;
        }

        // 过滤Memory空间, 根据Memory的状态和保护属性进行过滤
        if (MEM_COMMIT == mbi.State &&				// 已分配的物理Memory
            // MEM_PRIVATE == mbi.Type ||			// 私有Memory，不被其他进程共享
            // MEM_IMAGE == mbi.Type &&
            PAGE_READONLY == mbi.Protect ||		// 只读
            PAGE_EXECUTE_READ == mbi.Protect ||	// 读及执行
            PAGE_READWRITE == mbi.Protect ||		// 读写
            PAGE_EXECUTE_READWRITE == mbi.Protect)	// 读写及执行
        {
            // 申请动态Memory
            if (pMemBuffer) {
                delete[] pMemBuffer;
                pMemBuffer = NULL;
            }
            pMemBuffer = new BYTE[mbi.RegionSize];
            // 读取进程Memory
            ReadProcessMemory(GetCurrentProcess(), (LPCVOID)dwCurAddr, pMemBuffer, mbi.RegionSize, 0);
            //Mem::ReadMemory(dwCurAddr, &pMemBuffer, mbi.RegionSize);
            i = 0;
            j = 0;
            while (j < len) {
            nextAddr:
                if (pMemBuffer[i] == pMarkCode[j] || pMarkCode[j] == 0x3F) {
                    i++;
                    j++;
                }
                else {
                    nOffset = i - j + nSundayLen;
                    // 判断偏移量是否大于缓冲区
                    if (nOffset > mbi.RegionSize - len) break;
                    // 判断 aSunday模板数组 里有没有 Memory偏移后的值，有则回溯，否则+1
                    if (aSunday[pMemBuffer[nOffset]]) {
                        i = nOffset - aSunday[pMemBuffer[nOffset]] + 1;
                        j = 0;
                    }
                    else {
                        i = nOffset + 1;
                        j = 0;
                    }
                }
            }

            if (j == len) {
                // 计算找到的目标地址：
                // 特征码地址 = 当前Memory块基址 + i偏移 - 特征码长度
                // 目标地址 = 特征码地址 + 偏移距离
                // CALL（E8）跳转的地址 = E8指令后面的4个字节地址 + 下一条指令地址(也就是目标地址 + 5)
                retAddr[nCount] = dwCurAddr + i - len + deviation;

                if (++nCount >= nArrayLength) {
                    // 传入的数组下标越界就结束搜索
                    goto end;
                }

                if (isAll) {
                    i = i - len + 1;
                    j = 0;
                    goto nextAddr;
                }
                else {
                    goto end;
                }
            }
            dwCurAddr += mbi.RegionSize; // 取下一块Memory地址
        }
        else {
            dwCurAddr += mbi.RegionSize;
        }
    }


end:
    // 计算搜索用时(ms)
    clock_t nEndTime = clock();
    int m_useTime = (nEndTime - nBeginTime);
    // Print("Using: %dms\tSearch: %d\n", m_useTime, nCount);
    // 释放Memory
    if (pMemBuffer) {
        delete[] pMemBuffer;
        pMemBuffer = NULL;
    }
    delete[] pMarkCode;
    pMarkCode = NULL;
    return nCount;
}
ULONG64 SearchOffsetB(std::string markCode, int Offset = 0, HMODULE hModule = GetModuleHandle(NULL)) {
    //去除所有空格
    if (!markCode.empty()) {
        int index = 0;
        while ((index = markCode.find(' ', index)) >= 0) {
            markCode.erase(index, 1);
        }
        index = 0;
        while (true) {
            // 删掉头部通配符
            index = markCode.find("??", index);
            if (index == 0) {
                markCode.erase(index, 2);
            }
            else {
                break;
            }
        }
    }
    // 特征码长度不能为单数
    if (markCode.length() % 2 != 0) return 0;

    // 特征码长度
    int len = markCode.length() / 2;

    // 将特征码转换成byte型
    BYTE* pMark = new BYTE[len + 1];
    BYTE* pPattern = new BYTE[len + 1];
    memset(pMark, 0, len + 1);
    memset(pPattern, 0, len + 1);
    for (int i = 0; i < len; i++) {
        std::string tempStr = markCode.substr(i * 2, 2);
        if (tempStr == "??") {
            pPattern[i] = 0x3F; // '?'
            pMark[i] = 0x3F; // '?'
        }
        else {
            pPattern[i] = strtoul(tempStr.c_str(), 0, 16);
            pMark[i] = 'x';
        }
    }
    //ULONG64 SearchAddress = (ULONG64)FindPattern((char*)pPattern, (char*)pMark) + Offset;
    ULONG64 SearchAddress = (ULONG64)FindPattern((char*)pPattern, (char*)pMark, hModule) + Offset;
    if (SearchAddress < 0x10000000) SearchAddress = 0uLL;
    delete[] pMark;
    delete[] pPattern;
    return SearchAddress;
}
void steam(UINT64 VtableAddr)
{
    BYTE Jc_A[] = { 0x48, 0x8B, 0xC4, 0x55, 0x41 };
    BYTE Jc_B[] = { 0x48, 0x89, 0x5C, 0x24, 0x10 };
    BYTE Jc_C[] = { 0x48, 0x8B, 0xC4, 0x55, 0x41 };
    UINT64 加密地址1 = Read<UINT64>(VtableAddr + 0x68);
    if (*(BYTE*)(加密地址1) == (BYTE)0xE9) {
        Memory RWC(加密地址1, true);
        memcpy((void*)加密地址1, Jc_A, sizeof(Jc_A));
        RWC.Disable();
        Dxgi_PresentReCount++;
    }
    UINT64 加密地址2 = Read<UINT64>(VtableAddr + 0xB0);
    if (*(BYTE*)(加密地址2) == (BYTE)0xE9) {
        Memory RWC(加密地址2, true);
        memcpy((void*)加密地址2, Jc_B, sizeof(Jc_B));
        RWC.Disable();
        Dxgi_PresentReCount++;
    }
    UINT64 加密地址3 = Read<UINT64>(VtableAddr + 0x138);
    if (*(BYTE*)(加密地址3) == (BYTE)0xE9) {
        Memory RWC(加密地址3, true);
        memcpy((void*)加密地址3, Jc_C, sizeof(Jc_C));
        RWC.Disable();
        Dxgi_PresentReCount++;
    }
}
void 获取新函数()
{
    static auto CheckDxASM = [](ULONG64 Address, ULONG64* DxAddr_R9 = NULL)
    {

        if (*(uint32_t*)Address == 0x4DDC8B4C)
        {
            return true;
        }
        return false;
    };
    uint64_t DX储存[15]{ 0 };
    uint64_t GDLL储存[15]{ 0 };
    uint64_t GDI储存[15]{ 0 };
    BYTE GDILL[] = { 0x48 ,0x81 ,0xC4 ,0xA0 ,0x03 ,0x00 ,0x00 ,0x41 ,0x5F ,0x41 ,0x5E ,0x41 ,0x5D ,0x41 ,0x5C ,0x5F ,0x5E ,0x5D ,0xC3 ,0xCC };//

    DxCount = SearchByteBase("4C 8B DC 4D 89 4B ?? 41 56 48 81 EC ?? ?? ?? ?? 48 C7 44 24 ?? ?? ?? ?? ?? 49 89 5B ?? 49 89 73 ?? 49 89 7B"e, 0x10000000000, 0x30000000000, DX储存, 0, true);
    for (int i = 0; i < DxCount; i++)
    {
        if (CheckDxASM(DX储存[i])) {
            RAX指针缓存 = DX储存[i];
            printf(("DxCount缓存 %llX\n"e), RAX指针缓存);
            判断是否 = true;
        }
    }
    GdiCountA = SearchByteBase("48 89 07 48 8D 45 ?? 48 89 44 24 ?? 4C 8D 4C 24 ?? 4D 8B ?? 48 8B CF E8 ?? ?? ?? ?? 85 C0 0F 88 ?? ?? ?? ?? 83"e, 0x10000000000, 0x30000000000, GDI储存, 0x17, true);
    for (int i = 0; i < GdiCountA; i++) {
        if (*(BYTE*)GDI储存[i] == (BYTE)0xE8 &&
            *(USHORT*)(GDI储存[i] + 5) == (USHORT)0xC085) {
            if (*(BYTE*)(GDI储存[i] - 0x4B) != (BYTE)0xCD && *(BYTE*)(GDI储存[i] - 0x4B + 1) != (BYTE)0x2C && *(USHORT*)(GDI储存[i] - 0x4B) != (ULONG)0xCCF42CCD)
            {
                GDI缓存 = GDI储存[i];
                printf(("GDI缓存 %llX\n"e), GDI缓存);
                GDI判断是否 = true;
            }
        }
    }
}
void Draw_steam()
{
    bool 局部_还原 = false;
    bool 局部_修改 = false;
    while (true)
    {
        auto ResolveAddres = [](ULONG64 Addr, DWORD Speace, DWORD size)
        {
            return  Addr + Read<ULONG32>(Addr + Speace) + size;
        };
        auto JmpTo = [&](uint64_t Current, uint64_t Target)->void
        {
            Memory RWC(Current, true);
            BYTE Code[] = { 0xE9,0x00,0x00 ,0x00 ,0x00 };
            *(int32_t*)(*&Code + 0x1) = Target - Current - sizeof(Code);
            memcpy((PVOID)Current, &Code, sizeof(Code));
            RWC.Disable();
        };
        auto MemFind = [&](const PBYTE buffer, const int dwBufferSize, const PBYTE Pattern, const size_t PatternLen, const BYTE WildCard)->int
        {
            if (dwBufferSize < 0)
            {
                return -1;
            }
            DWORD  i, j;
            for (i = 0; i < dwBufferSize; i++)
            {
                for (j = 0; j < PatternLen; j++)
                {
                    if (buffer[i + j] != Pattern[j] && Pattern[j] != WildCard)
                        break;
                }
                if (j == PatternLen)
                    return i;
            }
            return -1;
        };
        if (IsAntiScreenShot == true)
        {
            if (RCXxiufu == true)
            {
                UINT64 GameOverlayRenderer64 = (UINT64)GetModuleHandleA("GameOverlayRenderer64.dll"e);
                if (GameOverlayRenderer64 > 0)
                {
                    UINT64 VtableAddr = Read<UINT64>(Read<UINT64>(Read<UINT64>(GameOverlayRenderer64 + 0x169D58) + 0xF0));

                    if (VtableAddr > 0)
                    {
                        //steam(VtableAddr);
                        UINT64 加密地址 = Read<UINT64>(VtableAddr + 0x40);
                        UINT64 RAX1地址 = VtableAddr + 0x40; //F9B7C480//4BEAC480
                        RAX1 = *(ULONG*)RAX1地址; //F9B7C480//4BEAC480
                        绘制全局地址 = 加密地址;
                        //判断是否加载二次函数

                        printf("加密地址 %llX  Dxgi_Present %llX CodeSave  %llX\n"e, 加密地址, Dxgi_Present, CodeSave[0]);

                        if (加密地址 != Dxgi_Present)
                        {
                            dx判断++;
                            if (DxCount < 1)
                            {
                                获取新函数();
                            }
                        }
                        //还原效验函数
                        if (DxCount > 0)
                        {
                            BYTE loopne[] = { 0xE0,0x1F,0xD5,0x76,0xF9,0x7F,0x00,0x00 };//
                            UINT64 RAX地址 = VtableAddr + 0x40; //F9B7C480//4BEAC480
                            if (*(BYTE*)RAX地址 != (BYTE)CodeSave[0] && *(UINT64*)RAX地址 != Dxgi_Present)
                            {
                                if (*(BYTE*)RAX地址 != (BYTE)CodeSave[0])
                                {
                                    Memory RWC(RAX地址, true);
                                    memcpy((void*)RAX地址, CodeSave, sizeof(CodeSave));
                                    RWC.Disable();
                                    AntiScreenShotCount++;                       
                                    还原写入 = true;
                                }
                            }
                        }
                        //DX函数
                        if (DxCount > 0)
                        {
                            if (还原写入 == true)
                            {
                                UINT64 RAX地址 = VtableAddr + 0x40; //F9B7C480//4BEAC480
                               // DX函数监控;
                                if (*(BYTE*)RAX地址 == (BYTE)CodeSave[0])
                                {
                                    uint64_t Mover = ResolveAddres(RAX指针缓存 + 0x2B, 3, 7);
                                    int 读取mov = Read<int>(Mover);
                                    printf("Mover地址 %llX 读取mov地址 %llX Mover字节[1] %llX\n"e, Mover, 读取mov, *(BYTE*)(Mover));
                                    if (读取mov!=0)
                                    {
                                        if (*(BYTE*)(Mover) == (BYTE)CodeSave[0])
                                        {
                                            if (*(BYTE*)(RAX指针缓存 - 0x11) != (BYTE)0xCC && *(BYTE*)(RAX指针缓存 - 0x12) != (BYTE)0xF4)
                                            {
                                                BYTE DXLL[] = { 0x49,0x8B ,0xE3,0x41,0x5E,0xC3,0xCC };//
                                                UINT64 sub = RAX指针缓存 + 9;
                                                if (*(BYTE*)sub != (BYTE)0x49)
                                                {
                                                    printf("sub %llX\n"e, sub);
                                                    if (*(BYTE*)RAX地址 == (BYTE)CodeSave[0])
                                                    {
                                                        Memory RWC(sub, true);
                                                        memcpy((void*)sub, DXLL, sizeof(DXLL));
                                                        RWC.Disable();
                                                        // off->wangbamoshi = true;
                                                        AntiScreenShotCount++;
                                                        AntiScreenShotCount_Dx++;
                                                        DX函数监控++;
                                                        局部_修改 = true;
                                                    }

                                                }
                                            }

                                        }
                                    }

                                    if (*(BYTE*)GDI缓存 == (BYTE)0xE8 &&
                                        *(USHORT*)(GDI缓存 + 5) == (USHORT)0xC085) {
                                        if (*(BYTE*)(GDI缓存 - 0x4B) != (BYTE)0xCD && *(BYTE*)(GDI缓存 - 0x4B + 1) != (BYTE)0x2C && *(USHORT*)(GDI缓存 - 0x4B) != (ULONG)0xCCF42CCD)
                                        {
                                            printf("GDI缓存 %llX\n"e, GDI缓存);
                                            SetRwc RWC(GDI缓存, true);
                                            *(BYTE*)GDI缓存 = (BYTE)0x90;
                                            *(BYTE*)(GDI缓存 + 1) = (BYTE)0x90;
                                            *(BYTE*)(GDI缓存 + 2) = (BYTE)0x90;
                                            *(BYTE*)(GDI缓存 + 3) = (BYTE)0x90;
                                            *(BYTE*)(GDI缓存 + 4) = (BYTE)0x90;
                                            RWC.Disable();
                                            AntiScreenShotCount++;
                                            AntiScreenShotCount_GDI++;
                                        }
                                    }                       
                                    if (局部_修改 == true)
                                    {
                                        while (true)
                                        {
                                            BYTE moe[] = { 0x00,0x00 ,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };//
                                            int 读取mov1 = Read<int>(Mover);
                                            if (读取mov1 != 0)
                                            {
                                                if (*(BYTE*)(Mover) == (BYTE)CodeSave[0])
                                                {
                                                    Memory RWC(Mover, true);
                                                    memcpy((void*)Mover, moe, sizeof(moe));
                                                    RWC.Disable();
                                                }                      
                                            }
                                            if (*(BYTE*)RAX地址 != (BYTE)CodeSave[0])
                                            {
                                                Memory RWC(RAX地址, true);
                                                memcpy((void*)RAX地址, CodeSave, sizeof(CodeSave));
                                                RWC.Disable();
                                            }                                           
                                            if (*(BYTE*)(RAX指针缓存 - 0x11) != (BYTE)0xCC && *(BYTE*)(RAX指针缓存 - 0x12) != (BYTE)0xF4)
                                            {
                                                BYTE DXLL[] = { 0x49,0x8B ,0xE3,0x41,0x5E,0xC3,0xCC };//
                                                UINT64 sub = RAX指针缓存 + 9;
                                                if (*(BYTE*)sub != (BYTE)0x49)
                                                {
                                                    printf("sub-> %llX\n"e, sub);
                                                    Memory RWC(sub, true);
                                                    memcpy((void*)sub, DXLL, sizeof(DXLL));
                                                    RWC.Disable();
                                                    // off->wangbamoshi = true;
                                                    AntiScreenShotCount++;
                                                    AntiScreenShotCount_Dx++;
                                                    DX函数监控++;                                     
                                                }
                                            }
                                            if (*(BYTE*)GDI缓存 == (BYTE)0xE8 &&
                                                *(USHORT*)(GDI缓存 + 5) == (USHORT)0xC085) {
                                                if (*(BYTE*)(GDI缓存 - 0x4B) != (BYTE)0xCD && *(BYTE*)(GDI缓存 - 0x4B + 1) != (BYTE)0x2C && *(USHORT*)(GDI缓存 - 0x4B) != (ULONG)0xCCF42CCD)
                                                {
                                                    printf("GDI缓存 %llX\n"e, GDI缓存);
                                                    SetRwc RWC(GDI缓存, true);
                                                    *(BYTE*)GDI缓存 = (BYTE)0x90;
                                                    *(BYTE*)(GDI缓存 + 1) = (BYTE)0x90;
                                                    *(BYTE*)(GDI缓存 + 2) = (BYTE)0x90;
                                                    *(BYTE*)(GDI缓存 + 3) = (BYTE)0x90;
                                                    *(BYTE*)(GDI缓存 + 4) = (BYTE)0x90;
                                                    RWC.Disable();
                                                    AntiScreenShotCount++;
                                                    AntiScreenShotCount_GDI++;

                                                }


                                            }


                                        }



                                    }


                                }
                            }
                        }
                            
                    }
                }
            }

        }
        Sleep(100);
    }
}
void GDIShot()
{
    auto ResolveAddres = [](ULONG64 Addr, DWORD Speace, DWORD size)
    {
        //printf("Addr %llX\n"e, Addr);
        return  Addr + Read<ULONG32>(Addr + Speace) + size;
    };
    int GDICount;
    uint64_t GDLLSave[15]{ 0 };
    BYTE GDILL[] = { 0x48 ,0x81 ,0xC4 ,0xA0 ,0x03 ,0x00 ,0x00 ,0x41 ,0x5F ,0x41 ,0x5E ,0x41 ,0x5D ,0x41 ,0x5C ,0x5F ,0x5E ,0x5D ,0xC3 ,0xCC };//
    GDICount = SearchByteBase("48 8D AC 24 ?? ?? ?? ?? 48 81 EC ?? ?? ?? ?? 48 C7 85 ?? ?? ?? ?? ?? ?? ?? ?? 48 89 9C 24 ?? ?? ?? ?? 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 85 ?? ?? ?? ?? 4D 8B F8 48 8B F9"e, 0x10000000000, 0x7fffffffffff, GDLLSave, 8, true);
    for (int i = 0; i < GDICount; i++)
    {
        if (*(BYTE*)(GDLLSave[i]) == (BYTE)0x48 && *(ULONG*)(GDLLSave[i]) == (ULONG)0xA0EC8148)
        {

            uint64_t RAX1地址 = ResolveAddres(GDLLSave[i] + 0x1A, 3, 7);
            printf("GDLLRAX1地址 %llX\n"e, RAX1地址);
            ReadMemory(RAX1地址, GDIcode, 17);
            printf("GDIcode %llX %llX %llX\n"e, GDIcode[0], GDIcode[1], GDIcode[2]);
            printf("GDLLSave %llX\n"e, GDLLSave[i]);
            SetRwc RWC((GDLLSave[i] + 0x7), true);
            memcpy((void*)(GDLLSave[i] + 0x7), GDILL, sizeof(GDILL));
            RWC.Disable();
            AntiScreenShotCount++;
            AntiScreenShotCount_GDLL++;
        }
    }
}
void AntiScreenShot()
{
    static auto PassDxgiHook = []() {
        /* 18362.1500 -- 22000.100 Only */
        Dxgi_Present = SearchOffsetB("48 89 74 24 20 55 57 41 56 48 8D 6C 24 90 48 81 EC 70 01 00 00 48 8B 05 ?? ?? ?? ?? 48 33 C4 48 89 45 60 45 33 F6 44 89 44 24 48"e, -5, GetModuleHandle("dxgi.dll"));
        if (!Dxgi_Present) {

            UINT64 GameOverlayRenderer64 = (UINT64)GetModuleHandle("GameOverlayRenderer64.dll"e);
            if (GameOverlayRenderer64 > 0)
            {
                UINT64 VtableAddr = Read<UINT64>(Read<UINT64>(Read<UINT64>(GameOverlayRenderer64 + 0x169D58) + 0xF0));
                if (VtableAddr > 0)
                {
                    Dxgi_Present = Read<UINT64>(VtableAddr + 0x40);
                }
            }
        }
    };
    auto JmpTo = [&](uint64_t Current, uint64_t Target)->void
    {
        SetRwc RWC(Current, true);
        BYTE Code[] = { 0xE9,0x00,0x00 ,0x00 ,0x00 };
        *(int32_t*)(*&Code + 0x1) = Target - Current - sizeof(Code);
        memcpy((PVOID)Current, &Code, sizeof(Code));
        RWC.Disable();
    };
    auto MemFind = [&](const PBYTE buffer, const int dwBufferSize, const PBYTE Pattern, const size_t PatternLen, const BYTE WildCard)->int
    {
        if (dwBufferSize < 0)
        {
            return -1;
        }
        DWORD  i, j;
        for (i = 0; i < dwBufferSize; i++)
        {
            for (j = 0; j < PatternLen; j++)
            {
                if (buffer[i + j] != Pattern[j] && Pattern[j] != WildCard)
                    break;
            }
            if (j == PatternLen)
                return i;
        }
        return -1;
    };

    auto ResolveAddres = [](ULONG64 Addr, DWORD Speace, DWORD size)
    {
       
        return  Addr + Read<ULONG32>(Addr + Speace) + size;
    };


    static auto CheckDxASM = [](ULONG64 Address, ULONG64* DxAddr_R9 = NULL)
    {
        if (*(uint32_t*)Address == 0x4DDC8B4C)
        {
            return true;
        }
        return false;
    };
    Sleep(1000 * 59); // 等数据稳定下来
   // Sleep(1000 * 30); // 等数据稳定下来
    PassDxgiHook();
    uint64_t CRCSave[15]{ 0 };
    uint64_t CRCSaveA[30]{ 0 };
    uint64_t CRCSaveB[30]{ 0 };
    uint64_t CRCSaveBB[30]{ 0 };
    uint64_t DXSave[15]{ 0 };
    uint64_t GDISave[15]{ 0 };
    int GDICount = 0, DxCount = 0, vTmpCount = 0;
    while (!DxCount) {
        Sleep(1000);
        DxCount = SearchByteBase("4C 8B DC 4D 89 4B ?? 41 56 48 81 EC ?? ?? ?? ?? 48 C7 44 24 ?? ?? ?? ?? ?? 49 89 5B ?? 49 89 73 ?? 49 89 7B"e, 0x10000000000, 0x30000000000, DXSave, 0, true);
        bool bHaveSuccessAddr = false;
        for (int i = 0; i < DxCount; i++) {
            printf("DX %llX\n"e, DXSave[i]);
            if (CheckDxASM(DXSave[i])) {
                bHaveSuccessAddr = true;
                break;
            }
        }
        if (!bHaveSuccessAddr)
        {
            DxCount = 0;
            memset(DXSave, 0, sizeof(DXSave));
        }
        vTmpCount++; if (vTmpCount > 60) break;
    }
    vTmpCount = 0;
    //920 gid函数头到尾巴差值
    while (!GDICount) {
        Sleep(1000);
        GDICount = SearchByteBase("48 89 07 48 8D 45 ?? 48 89 44 24 ?? 4C 8D 4C 24 ?? 4D 8B ?? 48 8B CF E8 ?? ?? ?? ?? 85 C0 0F 88 ?? ?? ?? ?? 83"e, 0x10000000000, 0x30000000000, GDISave, 0x17, true);
        vTmpCount++; if (vTmpCount > 15) break;
    }
    vTmpCount = 0;
    int CRC数量 = SearchByteBase("48 83 EC ?? 48 C7 40 ?? ?? ?? ?? ?? 4C 8B F9 48 8D 99 ?? ?? ?? ?? 48 89 58 ?? 48 8B 43 ?? 33 FF"e, 0x10000000000, 0x30000000000, CRCSave, 0, true);
    //8.9
    int CRC数量A = SearchByteBase("CC CC CC 48 8B C4 48 89 50 10 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 83 EC ?? 48 C7 45 ?? ?? ?? ?? ?? 48 89 58 ?? 48 8B F1 33 DB"e, 0x10000000000, 0x30000000000, CRCSaveA, 0, true);
   //CC CC CC 40 53 55 56 57 41 54 41 55 41 56 41 57 48 83 EC ?? 48 C7 44 24 ?? ?? ?? ?? ?? 48 8B F1 4C 8D 69 ?? 4C 89 AC 24 ?? ?? ?? ?? 45 33 F6
    //C3 CC  CC CC 40 53  55  56  57 41 54 41 55 41 56 41 57 48 83 EC 38 48 C7 44 ? ? ? ? ? ? ? ? ? ? ? ? 48 8B F1 4C 8D 69 ? ? 4C 89 AC 24 ? ? ? ? ? ? ? ? 45 33 F6
       int CRC数量BB = SearchByteBase("C3 CC CC CC 40 53 55 56 57 41 54 41 55 41 56 41 57 48 83 EC 38 48 C7 44 ?? ?? ?? ?? ?? ?? 48 8B F1 4C 8D 69 ? ? 4C 89 AC 24 ?? ?? ?? ?? 45 33 F6"e, 0x10000000000, 0x30000000000, CRCSaveBB, 0, true);
        for (int i = 0; i < CRC数量BB; i++)
        {
            if (*(BYTE*)(CRCSaveBB[i] + 4) == (BYTE)0x40 &&
                *(BYTE*)(CRCSaveBB[i] + 4 + 1) == (BYTE)0x53 &&
                *(BYTE*)(CRCSaveBB[i] + 4 + 2) == (BYTE)0x55)
            {
                //48 83 C4 38 41 5F 41 5E 41 5D 41 5C  5F 5E  5D 5B C3 CC                   
                //0x15
                if (*(BYTE*)(CRCSaveBB[i] + 0x15) == (BYTE)0x48 &&
                    *(BYTE*)(CRCSaveBB[i] + 0x15 + 1) == (BYTE)0xC7 &&
                    *(BYTE*)(CRCSaveBB[i] + 0x15 + 2) == (BYTE)0x44)
                {
                    printf("CRCSaveBB[i] %llX\n"e, CRCSaveBB[i] + 0x15);
                    BYTE code[] = { 0x48,0x83,0xC4,0x38,0x41,0x5F,0x41,0x5E,0x41,0x5D,0x41,0x5C,0x5F,0x5E,0x5D,0x5B,0xC3,0xCC };//
                    SetRwc RWC((CRCSaveBB[i] + 0x15), true);
                    memcpy((void*)(CRCSaveBB[i]+0x15), code, sizeof(code));
                    RWC.Disable();
                    AntiScreenShotCount++;
                    AntiScreenShotCount_CRCBB++;
                }


            }

        }
        
    //    for (int i = 0; i < CRC数量; i++) {
    //    if (*(BYTE*)CRCSave[i] == (BYTE)0x48 &&
    //        *(BYTE*)(CRCSave[i] + 1) == (BYTE)0x83 &&
    //        *(BYTE*)(CRCSave[i] + 2) == (BYTE)0xEC) {

    //        uint64_t Jmp_Start = CRCSave[i] + 0x4;
    //        BYTE Pattern[] = { 0x48,0x83,0xC4,0xCC };//add rsp,xxx
    //        int offset = MemFind((PBYTE)Jmp_Start, 0x1000, Pattern, sizeof(Pattern), 0xCC);
    //        if (offset != -1)
    //        {
    //            JmpTo(Jmp_Start, Jmp_Start + offset);
    //            AntiScreenShotCount++;
    //            AntiScreenShotCount_CRC++;
    //            printf("CRCSave %llX | %llX | %llX\n"e, Jmp_Start, offset, *(uint64_t*)(Jmp_Start + offset));
    //        }
    //    }
    //}
    //for (int i = 0; i < CRC数量A; i++) {
    //    if (*(BYTE*)(CRCSaveA[i] + 4) == (BYTE)0x8B && *(ULONG*)(CRCSaveA[i] + 9) == (ULONG)0x57565510) {
    //        for (int N = 0; N < 600; N++) {
    //            if (*(BYTE*)(CRCSaveA[i] + N) == (BYTE)0xE9 && *(ULONG*)(CRCSaveA[i] + N + 5) == (ULONG)0xCCCCCCCC) {

    //                uint64_t Jmp_Start = CRCSaveA[i] + 0x1C;
    //                BYTE Pattern[] = { 0x48,0x83,0xC4,0xCC };//add rsp,xxx
    //                int offset = MemFind((PBYTE)Jmp_Start, 0x1000, Pattern, sizeof(Pattern), 0xCC);
    //                if (offset != -1)
    //                {
    //                    JmpTo(Jmp_Start, Jmp_Start + offset);
    //                    AntiScreenShotCount++;
    //                    AntiScreenShotCount_CRCa++;
    //                    printf("CRCSaveA %llX | %llX | %llX\n"e, Jmp_Start, offset, *(uint64_t*)(Jmp_Start + offset));
    //                }
    //                break;
    //            }
    //        }
    //    }
    //}





    static auto 修改 = [](ULONG64 Address)
    {
        BYTE DXLL[] = { 0x49,0x8B ,0xE3,0x41,0x5E,0xC3,0xCC };//
        UINT64 sub = Address + 9;
        SetRwc RWC(sub, true);
        memcpy((void*)sub, DXLL, sizeof(DXLL));
        RWC.Disable();
        AntiScreenShotCount++;
        AntiScreenShotCount_Dx++;
    };
    for (int i = 0; i < DxCount; i++) {
        printf("DX %llX\n"e, DXSave[i] - 0x10);
        if (CheckDxASM(DXSave[i]))
        {
            uint64_t Mover = ResolveAddres(DXSave[i] + 0x2B, 3, 7);
            printf("Mover %llX\n"e, Mover);
            int 读取mov=Read<int>(Mover);
            printf("读取mov %llX\n"e, 读取mov);
            if (读取mov==0)
            {
                if (*(BYTE*)(DXSave[i] - 0x11) != (BYTE)0xCC && *(BYTE*)(DXSave[i] - 0x12) != (BYTE)0xF4)
                {
                    if (RCXxiufu == true)
                    {
                        修改(DXSave[i]);

                    }

                }
            }



        }
    }


    for (int i = 0; i < GDICount; i++) {
        if (*(BYTE*)GDISave[i] == (BYTE)0xE8 &&
            *(USHORT*)(GDISave[i] + 5) == (USHORT)0xC085) {
            if (*(BYTE*)(GDISave[i]-0x4B) != (BYTE)0xCD && *(BYTE*)(GDISave[i] - 0x4B+1) != (BYTE)0x2C && *(USHORT*)(GDISave[i] - 0x4B) != (ULONG)0xCCF42CCD)
            {
                printf("GDISave %llX\n"e, GDISave[i]);
                SetRwc RWC(GDISave[i], true);
                *(BYTE*)GDISave[i] = (BYTE)0x90;
                *(BYTE*)(GDISave[i] + 1) = (BYTE)0x90;
                *(BYTE*)(GDISave[i] + 2) = (BYTE)0x90;
                *(BYTE*)(GDISave[i] + 3) = (BYTE)0x90;
                *(BYTE*)(GDISave[i] + 4) = (BYTE)0x90;
                RWC.Disable();
                AntiScreenShotCount++;
                AntiScreenShotCount_GDI++;

            }


        }
    }


    AntiScreenShotCount_CRCb = 1;
    IsAntiScreenShot = true;
    ForceByPassAntiScreenShot = false;
}

void codell()
{
    UINT64 GameOverlayRenderer64 = (UINT64)GetModuleHandleA("GameOverlayRenderer64.dll"e);
    if (GameOverlayRenderer64 > 0)
    {
        //48 83 EC ?? 48 8B 89 ?? ?? ?? ?? 48 85 C9 74 1C
        UINT64 VtableAddr = Read<UINT64>(Read<UINT64>(Read<UINT64>(GameOverlayRenderer64 + 0x169D58) + 0xF0));
        printf("VtableAddr地址 %llX\n"e, VtableAddr);
        if (VtableAddr > 0)
        {
            UINT64 RAX地址 = VtableAddr + 0x40; //F9B7C480//4BEAC480
            printf("RAX地址 %llX\n"e, RAX地址);
            ReadMemory(RAX地址, CodeSave, 9);
            printf("CodeSave %llX %llX %llX %llX %llX\n"e, CodeSave[0], CodeSave[1], CodeSave[2], CodeSave[3], CodeSave[4]);
                   
        }

    }


}
void InitialEvent()
{
    //while (true)
    //{
    //    int InLoabby = Read<int>(Game->GameBase + offset_IsInLoabby);

    //    if (InLoabby == 1)
    //    {
    //        Sleep(1000 * 5);
    //        break;
    //    }

    //    Sleep(10);
    //}

    SpoofCall<void>(codell);
    SpoofCall<void>(AntiScreenShot);
    if (IsAntiScreenShot ==true)
    {
      SpoofCall<void>(Draw_steam);
    }

}
