// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "Main.h"
#include "GameHack.h"


EXTERN_C ULONG64 g_SpoofBack = NULL;
EXTERN_C ULONG64 CurrentRsp = NULL;
EXTERN_C ULONG64 EngineDrawHook = NULL;
EXTERN_C void HookFunc();

ULONG64 Vtable[200] = { 0 };
ULONG64 OldRet;



void __fastcall EngineHookProxy(ULONG64 falg)
{
	//printf("(ULONG64)_ReturnAddress():%p\n", (ULONG64)_ReturnAddress());
	//printf("(ULONG64)Game->GameBase + offset_ReturnAddress():%p\n", Game->GameBase + offset_ReturnAddress);
	if ((ULONG64)_ReturnAddress() == Game->GameBase + offset_ReturnAddress)
	{

		auto GameW = Read<DWORD>(UCanvas::DebugCanvas + offset_SizeX);
		auto GameH = Read<DWORD>(UCanvas::DebugCanvas + offset_SizeY);
		Game->ScreenCenter = { (float)(GameW * 0.5),(float)(GameH * 0.5) };
		//printf("GameW:%p\n", GameW);
		//printf("GameH:%p\n", GameH);
		


		if (UCanvas::DebugCanvas) {

		//	printf("UCanvas::Canvas:%p\n", UCanvas::Canvas);
			if (Func::GetAsyncKeyState2(VK_END))
				Vtable[35] = OldRet;//这个是还原hook续表直接卸dll的给你说一下1
			if (Func::GetAsyncKeyState2(VK_HOME) & 1)
				off->Menu = !off->Menu;
			else if (Func::GetAsyncKeyState2(192) & 1)
				off->qingshuang = !off->qingshuang;
			else if (Func::GetAsyncKeyState2(VK_F2) & 1)
				off->Item = !off->Item;

			//ce呢

			UCanvas::SetCanvas(UCanvas::DebugCanvas);
			SpoofCall<void>(GameHack::DrawESP);

			UCanvas::SetCanvas(UCanvas::DebugCanvas);
			SpoofCall<void>(GameHack::F菜单);

			SpoofCall<void>(GameHack::F按键);

			//UCanvas::DrawRect(80, 80,200,200, 2, Colo->黑色);


			//UCanvas::DrawText(80, 440, Colo->NoInfo, Colo->黑色, "EngineDraw-Master", true, true, true);
			//UCanvas::DrawText(80, 440, Colo->白色, Colo->黑色, false, "次数：%d"e, Game->codedll);
		
		
		}
	}
	*(DWORD*)(Game->GameBase + offset_pUnknownTick) += 1;
}
//等一下
void CheatInit() {
	//AllocConsole();
	//freopen_s((FILE**)stdin, "CONIN$"e, "r"e, stdin);
	//freopen_s((FILE**)stdout, "CONOUT$"e, "w"e, stdout);

	Game->GameBase = (ULONG64)GetModuleHandle(NULL);
	
	Game->hWnd = FindWindowA("UnrealWindow"e, NULL);
	g_SpoofBack = Game->GameBase + offset_SpoolBack;
	
	PubgData::GNames = PubgData::XeDecryption(Read<ULONG64>(PubgData::XeDecryption(Read<ULONG64>(Game->GameBase + offset_GName))));
	//printf("GNames:%llX\n", PubgData::GNames);

	UCanvas::Init();
	ULONG64 EngineDrawHookPoint_Chain1 = Read<ULONG64>(Game->GameBase + offset_pUnknownHook);
	ReadMemory(Read<ULONG64>(EngineDrawHookPoint_Chain1), Vtable, sizeof(Vtable));
	OldRet = Vtable[35];
	Vtable[35] = (ULONG64)EngineHookProxy;
	*(uint64_t*)EngineDrawHookPoint_Chain1 = (uint64_t)&Vtable;

	//printf("EngineDrawHookPoint_Chain1:%llX\n", EngineDrawHookPoint_Chain1);
}


bool Is_Inject = false;
typedef struct _PEB_LDR_DATA {
	BYTE Reserved1[8];
	PVOID Reserved2[3];
	LIST_ENTRY InMemoryOrderModuleList;
} PEB_LDR_DATA, * PPEB_LDR_DATA;
typedef
VOID
(NTAPI* PPS_POST_PROCESS_INIT_ROUTINE) (
	VOID
	);
typedef struct _RTL_USER_PROCESS_PARAMETERS {
	BYTE Reserved1[16];
	PVOID Reserved2[10];
	UNICODE_STRING ImagePathName;
	UNICODE_STRING CommandLine;
} RTL_USER_PROCESS_PARAMETERS, * PRTL_USER_PROCESS_PARAMETERS;
typedef struct _PEB {
	BYTE Reserved1[2];
	BYTE BeingDebugged;
	BYTE Reserved2[1];
	PVOID Reserved3[2];
	PPEB_LDR_DATA Ldr;
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
	PVOID Reserved4[3];
	PVOID AtlThunkSListPtr;
	PVOID Reserved5;
	ULONG Reserved6;
	PVOID Reserved7;
	ULONG Reserved8;
	ULONG AtlThunkSListPtr32;
	PVOID Reserved9[45];
	BYTE Reserved10[96];
	PPS_POST_PROCESS_INIT_ROUTINE PostProcessInitRoutine;
	BYTE Reserved11[128];
	PVOID Reserved12[1];
	ULONG SessionId;
} PEB, * PPEB;
typedef struct _TEB {
	PVOID Reserved1[12];
	PPEB ProcessEnvironmentBlock;
	PVOID Reserved2[399];
	BYTE Reserved3[1952];
	PVOID TlsSlots[64];
	BYTE Reserved4[8];
	PVOID Reserved5[26];
	PVOID ReservedForOle;  // Windows 2000 only
	PVOID Reserved6[4];
	PVOID TlsExpansionSlots;
} TEB, * PTEB;


typedef struct _LDR_DATA_TABLE_ENTRY2
{
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InMemoryOrderLinks;
	LIST_ENTRY InInitializationOrderLinks;
	PVOID      DllBase;
	PVOID      EntryPoint;
	ULONG32    SizeOfImage;
	UINT8      Unknow0[0x4];
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
}LDR_DATA_TABLE_ENTRY2, * PLDR_DATA_TABLE_ENTRY2;


typedef HMODULE(__stdcall* _LoadLibraryA)(
	_In_ LPCSTR lpLibFileName);

typedef FARPROC(__stdcall* _GetProcAddress)(
	_In_ HMODULE hModule,
	_In_ LPCSTR lpProcName);

typedef BOOL(__stdcall* _DllMain)(
	HMODULE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved);

//鳳?kernel32.dll耀輸華硊
ULONG_PTR GetKernel32()
{
	//get ntdll base
#if defined _M_IX86
	PPEB_LDR_DATA Ldr = ((PTEB)__readfsdword(FIELD_OFFSET(NT_TIB, Self)))->ProcessEnvironmentBlock->Ldr;
#elif defined _M_X64
	PPEB_LDR_DATA Ldr = ((PTEB)__readgsqword(FIELD_OFFSET(NT_TIB, Self)))->ProcessEnvironmentBlock->Ldr;
#endif

	//process modules
	for (PLIST_ENTRY CurEnt = Ldr->InMemoryOrderModuleList.Flink; CurEnt != &Ldr->InMemoryOrderModuleList; CurEnt = CurEnt->Flink) {
		PLDR_DATA_TABLE_ENTRY2 pEntry = CONTAINING_RECORD(CurEnt, LDR_DATA_TABLE_ENTRY2, InMemoryOrderLinks);

		if ((pEntry->BaseDllName.Length == 24) && ((*(ULONG_PTR*)pEntry->BaseDllName.Buffer == 0x004E00520045004B) || (*(ULONG_PTR*)pEntry->BaseDllName.Buffer == 0x006E00720065006B)))
		{
			//printf("耀輸曆梟:%p  ==  耀輸靡:%ws\n", pEntry->DllBase, pEntry->BaseDllName.Buffer);
			return (ULONG_PTR)pEntry->DllBase;
		}
		//if ((pEntry->BaseDllName.Length == 18) && (*(uint64_t*)pEntry->BaseDllName.Buffer == 0x6C00640074006E))
			//return (uintptr_t)pEntry->DllBase;
	} return 0;
}

uintptr_t GetDll_Export(ULONG64 hModule, const char* Name)
{
	//parse info
	static PIMAGE_EXPORT_DIRECTORY ExportDir = nullptr;

	PIMAGE_NT_HEADERS NT_Head = (PIMAGE_NT_HEADERS)(hModule + ((PIMAGE_DOS_HEADER)hModule)->e_lfanew);
	ExportDir = (PIMAGE_EXPORT_DIRECTORY)(hModule + NT_Head->OptionalHeader.DataDirectory[0].VirtualAddress);


	//process list
	for (ULONG i = 0; i < ExportDir->NumberOfNames; i++)
	{
		//get ordinal & name
		USHORT Ordinal = ((USHORT*)(hModule + ExportDir->AddressOfNameOrdinals))[i];
		const char* ExpName = (const char*)hModule + ((ULONG*)(hModule + ExportDir->AddressOfNames))[i];

		//check name
		for (int i = 0; ExpName[i] == Name[i]; i++) if (!ExpName[i])
			return hModule + ((ULONG*)(hModule + ExportDir->AddressOfFunctions))[Ordinal];
	} return 0;
}
ULONG_PTR GetMyModuleAddress() {
	ULONG64 pStart = (ULONG64)GetMyModuleAddress & 0xFFFFFFFFFFFF0000;
	while (true)
	{
		if (*(WORD*)pStart == 0x5A4D)
		{
			return pStart;
		}
		pStart -= 0x1000;
	}
	return 0;
}
void StartHook(HMODULE hDLL) {
	//这里写DLL初始化代码


	//	AllocConsole();
	//freopen_s((FILE**)stdin, "CONIN$"e, "r"e, stdin);
	//freopen_s((FILE**)stdout, "CONOUT$"e, "w"e, stdout);
	Func::HideInList(hDLL);
	CheatInit();

}
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{


		//memset(hModule, 0, 0x1000);
		//PassThread();
		StartHook(hModule);

	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

extern "C" __declspec(dllexport) LRESULT Initialization(int code, WPARAM wParam, LPARAM lParam) {
	if (!Is_Inject) {
		Is_Inject = true;

		//*(ULONG64*)-1 = 0;


		PVOID HandleModule = (PVOID)GetMyModuleAddress();
		_LoadLibraryA Fn_LoadLibraryA = (_LoadLibraryA)GetDll_Export(GetKernel32(), "LoadLibraryA");
		_GetProcAddress Fn__GetProcAddress = (_GetProcAddress)GetDll_Export(GetKernel32(), "GetProcAddress");




		PIMAGE_DOS_HEADER pDosHeader;
		PIMAGE_NT_HEADERS pNTHeader;

		pDosHeader = (PIMAGE_DOS_HEADER)HandleModule; // DOS头
		pNTHeader = (PIMAGE_NT_HEADERS)((ULONG_PTR)HandleModule + pDosHeader->e_lfanew); // PE头
		/*******************重定位信息****************************************************/
		if (pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress > 0
			&& pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size > 0) {
			ULONG_PTR Delta = (ULONG_PTR)HandleModule - pNTHeader->OptionalHeader.ImageBase;
			ULONG_PTR* pAddress;
			//注意重定位表的位置可能和硬盘文件中的偏移地址不同，应该使用加载后的地址
			PIMAGE_BASE_RELOCATION pLoc = (PIMAGE_BASE_RELOCATION)((ULONG_PTR)HandleModule
				+ pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
			while ((pLoc->VirtualAddress + pLoc->SizeOfBlock) != 0) //开始扫描重定位表
			{
				WORD* pLocData = (WORD*)((ULONG_PTR)pLoc + sizeof(IMAGE_BASE_RELOCATION));
				//计算本节需要修正的重定位项（地址）的数目
				int NumberOfReloc = (pLoc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);
				for (int i = 0; i < NumberOfReloc; i++)
				{
					//printf("重定位:%d  NumberOfReloc:%d\n", pLocData[i], NumberOfReloc);
					if ((ULONG_PTR)(pLocData[i] & 0xF000) == 0x00003000 || (ULONG_PTR)(pLocData[i] & 0xF000) == 0x0000A000) //这是一个需要修正的地址
					{
						pAddress = (ULONG_PTR*)((ULONG_PTR)HandleModule + pLoc->VirtualAddress + (pLocData[i] & 0x0FFF));
						*pAddress += Delta;
					}
				}
				//转移到下一个节进行处理
				pLoc = (PIMAGE_BASE_RELOCATION)((ULONG_PTR)pLoc + pLoc->SizeOfBlock);
			}
		}
		/******************* 修正引入地址表**************/
		ULONG_PTR Offset = pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
		PIMAGE_IMPORT_DESCRIPTOR pID = (PIMAGE_IMPORT_DESCRIPTOR)((ULONG_PTR)HandleModule + Offset);
		PIMAGE_IMPORT_BY_NAME pByName = NULL;
		while (pID->Characteristics != 0) {
			PIMAGE_THUNK_DATA pRealIAT = (PIMAGE_THUNK_DATA)((ULONG_PTR)HandleModule + pID->FirstThunk);
			PIMAGE_THUNK_DATA pOriginalIAT = (PIMAGE_THUNK_DATA)((ULONG_PTR)HandleModule + pID->OriginalFirstThunk);
			char* pName = (char*)((ULONG_PTR)HandleModule + pID->Name);
			HMODULE hDll = Fn_LoadLibraryA(pName);
			if (hDll == NULL) {
				return 0;
			}
			for (int i = 0; ; i++) {
				if (pOriginalIAT[i].u1.Function == 0)break;
				FARPROC lpFunction = NULL;
				if (IMAGE_SNAP_BY_ORDINAL(pOriginalIAT[i].u1.Ordinal)) {
					if (IMAGE_ORDINAL(pOriginalIAT[i].u1.Ordinal)) {
						lpFunction = Fn__GetProcAddress(hDll, (char*)pOriginalIAT[i].u1.Ordinal);
					}
				}
				else
				{
					pByName = (PIMAGE_IMPORT_BY_NAME)((ULONG_PTR)HandleModule + (ULONG_PTR)(pOriginalIAT[i].u1.AddressOfData));
					if ((char*)pByName->Name) {
						lpFunction = Fn__GetProcAddress(hDll, (char*)pByName->Name);
					}
				}
				//标记***********

				if (lpFunction != NULL) {
					pRealIAT[i].u1.Function = (ULONG_PTR)lpFunction;
				}
				else {
					return 0;
				}
			}
			pID = (PIMAGE_IMPORT_DESCRIPTOR)((ULONG_PTR)pID + sizeof(IMAGE_IMPORT_DESCRIPTOR));
		}
		/******************修正基地址*****调用DllMain************************************/
		pNTHeader->OptionalHeader.ImageBase = (ULONG_PTR)HandleModule;
		_DllMain pDllMain = (_DllMain)(pNTHeader->OptionalHeader.AddressOfEntryPoint + (ULONG_PTR)HandleModule);
		pDllMain((HMODULE)HandleModule, DLL_PROCESS_ATTACH, HandleModule);
	}
	return 0;
}
