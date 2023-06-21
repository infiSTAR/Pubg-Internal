#pragma once
#include <stdint.h>
#include <minwindef.h>
#include <WinUser.h>

#pragma comment(lib, "DriverInMsg.lib")

namespace Driver {


	//ͨ�Žṹ
	typedef struct IO_MESSAGE {
		uint32_t ProcessId;
		uint32_t Size;
		uint64_t Address;
	}IO_MESSAGE, * PIO_MESSAGE;
	typedef struct _MODULEINFO {
		uint64_t ModuleBase;
		wchar_t modulename[64];
	}_MODULEINFO;

	extern ULONG ServerId;
	extern ULONG NtUserGetAsyncKeyStateIndex, NtUserSendInputIndex;
	extern USHORT KeyState[255];

	extern uint32_t ProcessId;
	extern bool IsWin7;

	uint64_t GetThreadNumber();
	/// <summary>
	/// ���������鿴�����Ƿ����
	/// </summary>
	/// <returns>�ɹ�����true ʧ�ܷ���false</returns>
	bool LinkDevice();
	/// <summary>
	/// ����Ŀ�����ID
	/// </summary>
	/// <param name="pid">����ID</param>
	void SetTargetProcessId(uint32_t pid);
	/// <summary>
	/// ��ȡ�ڴ�(ֱ��)
	/// </summary>
	/// <param name="Address"></param>
	/// <param name="buff"></param>
	/// <param name="Size"></param>
	void ReadMemory(uint64_t Address, void* buff, uint32_t Size);
	/// <summary>
	/// дȡ�ڴ�(ֱд)
	/// </summary>
	/// <param name="Address"></param>
	/// <param name="buff"></param>
	/// <param name="Size"></param>
	void WriteMemory(uint64_t Address, void* buff, uint32_t Size);
	/// <summary>
	/// ��ȡ�ڴ�(API)
	/// </summary>
	/// <param name="Address"></param>
	/// <param name="buff"></param>
	/// <param name="Size"></param>
	void ReadMemory2(uint64_t Address, void* buff, uint32_t Size);
	/// <summary>
	/// дȡ�ڴ�(API)
	/// </summary>
	/// <param name="Address"></param>
	/// <param name="buff"></param>
	/// <param name="Size"></param>
	void WriteMemory2(uint64_t Address, void* buff, uint32_t Size);
	/// <summary>
	/// дȡ�ڴ�(MDL)
	/// </summary>
	/// <param name="Address"></param>
	/// <param name="buff"></param>
	/// <param name="Size"></param>
	void WriteMemoryMDL(uint64_t Address, void* buff, uint32_t Size);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="ModuleName"></param>
	/// <returns></returns>
	uint64_t GetModuleBase(const wchar_t* ModuleName);



	USHORT NtUserGetAsyncKeyState(DWORD key);
	DWORD NtUserSendInput(UINT cInputs, LPINPUT pInputs, int cbSize);
	void GetAllAsyncKeyState();
	bool ReadMemoryAPI(uint64_t Address, void* buff, uint32_t Size);
	void PassScreenshot();


	template<class T> T Ram(__int64 ptr);
	template<class T> T RamA(__int64 ptr);
	template<class T> T Read(__int64 ptr);
	template<class T> void Wam(__int64 ptr, T Val);
};