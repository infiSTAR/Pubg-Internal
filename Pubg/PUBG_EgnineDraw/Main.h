#pragma once
#define WIN64_LEAN_AND_MEAN // 从 Windows 头文件中排除极少使用的内容
#include <windows.h>
#include <vector>
#include <map>
#include <string>
#include <cstdint>
#include <intrin.h>
#include "ue4math/vector.h"
#include "ue4math/quat.h"
#include "ue4math/matrix.h"
#include "ue4math/rotator.h"
#include "ue4math/transform.h"
#include "ue4math/ue4math.h"
#include "common/util.h"
#include "offsets.h"
#include "Engine.h"
#include "Draw.h"
#include "Driver.h"
inline bool ValidPtr(uint64_t Ptr)
{
	return (bool)(Ptr < 0x1000000 || Ptr > 0x7FFFFFF00000 || Ptr % sizeof(uint64_t));
}
inline bool ValidPtr(PVOID Ptr)
{
	auto v1 = (ULONG64)Ptr;

	return (bool)(v1 < 0x1000000 || v1 > 0x7FFFFFF00000 || v1 % sizeof(uint64_t));
}
constexpr inline auto NAME_None = FName(0, 0);
constexpr inline auto INDEX_NONE = -1;
typedef struct _M_PEB_LDR_DATA
{
	ULONG Length;
	BOOLEAN Initialized;
	PVOID SsHandle;
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
} M_M_PEB_LDR_DATA, * PM_M_PEB_LDR_DATA;
typedef struct _M_LDR_MODULE
{
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
	PVOID BaseAddress;
	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG Flags;
	SHORT LoadCount;
	SHORT TlsIndex;
	LIST_ENTRY HashTableEntry;
	ULONG TimeDateStamp;
} M_LDR_MODULE, * PM_LDR_MODULE;
typedef struct
{
	DWORD64 dwEP;
	void* pParam;
}CALL_MYFUNCTION, * PCALL_MYFUNCTION;
typedef struct _M_PEB {
	BOOLEAN InheritedAddressSpace;
	BOOLEAN ReadImageFileExecOptions;
	BOOLEAN BeingDebugged;
	BOOLEAN Spare;
	HANDLE Mutant;
	PVOID ImageBaseAddress;
	PM_M_PEB_LDR_DATA LoaderData;
	PVOID ProcessParameters;
	PVOID SubSystemData;
	PVOID ProcessHeap;
	PVOID FastM_PEBLock;
	PVOID FastM_PEBLockRoutine;
	PVOID FastM_PEBUnlockRoutine;
	ULONG EnvironmentUpdateCount;
	PVOID* KernelCallbackTable;
	PVOID EventLogSection;
	PVOID EventLog;
	PVOID FreeList;
	ULONG TlsExpansionCounter;
	PVOID TlsBitmap;
	ULONG TlsBitmapBits[2];
	PVOID ReadOnlySharedMemoryBase;
	PVOID ReadOnlySharedMemoryHeap;
	PVOID* ReadOnlyStaticServerData;
	PVOID AnsiCodePageData;
	PVOID OemCodePageData;
	PVOID UnicodeCaseTableData;
	ULONG NumberOfProcessors;
	ULONG NtGlobalFlag;
	BYTE Spare2[0x4];
	LARGE_INTEGER CriticalSectionTimeout;
	ULONG HeapSegmentReserve;
	ULONG HeapSegmentCommit;
	ULONG HeapDeCommitTotalFreeThreshold;
	ULONG HeapDeCommitFreeBlockThreshold;
	ULONG NumberOfHeaps;
	ULONG MaximumNumberOfHeaps;
	PVOID** ProcessHeaps;
	PVOID GdiSharedHandleTable;
	PVOID ProcessStarterHelper;
	PVOID GdiDCAttributeList;
	PVOID LoaderLock;
	ULONG OSMajorVersion;
	ULONG OSMinorVersion;
	ULONG OSBuildNumber;
	ULONG OSPlatformId;
	ULONG ImageSubSystem;
	ULONG ImageSubSystemMajorVersion;
	ULONG ImageSubSystemMinorVersion;
	ULONG GdiHandleBuffer[0x22];
	ULONG PostProcessInitRoutine;
	ULONG TlsExpansionBitmap;
	BYTE TlsExpansionBitmapBits[0x80];
	ULONG SessionId;
} M_PEB, * PM_PEB;
class GameData {
public:
	bool IsKm = false;
	uint64_t GameBase = NULL;
	HWND hWnd = NULL;
	ULONG64 UWorld = NULL;
	ULONG64 Actor = NULL;
	FVector2D ScreenCenter = FVector2D();
	ULONG64 MyPlayerAddress = NULL;
	ULONG64 PlayerCameraManager = NULL;
	FVector Location;
	FRotator Rotation;
	float FOV;
	int PassChackNum;
	int codedll;
	float juli;
};
class ColorData
{
public:
	FLinearColor 红色 = { 1.0f , 0.0f , 0.0f , 1.0f };
	FLinearColor 品红 = { 1.0f , 0.0f , 1.0f , 1.0f };
	FLinearColor 黄色 = { 1.0f , 1.0f , 0.0f , 1.0f };
	FLinearColor 灰蓝 = { 0.5019607843137f , 0.5019607843137f , 1.0f , 1.0f };
	FLinearColor 嫩绿 = { 0.5019607843137f , 0.878431372549f , 0.0f , 1.0f };
	FLinearColor 深绿 = { 0.0f , 0.878431372549f , 0.5019607843137f , 1.0f };
	FLinearColor 棕色 = { 0.7529411764706f , 0.3764705882353f , 0.0f , 1.0f };
	FLinearColor 粉色 = { 1.0f , 0.6588235294118f , 1.0f , 1.0f };
	FLinearColor 暗黄 = { 0.8470588235294f , 0.8470588235294f , 0.0f , 1.0f };
	FLinearColor 银白 = { 0.9254901960784f , 0.9254901960784f , 0.9254901960784f , 1.0f };
	FLinearColor 紫色 = { 0.5647058823529f , 0.0f , 1.0f , 1.0f };
	FLinearColor 藏蓝 = { 0.3450980392157f , 0.1882352941176f , 0.878431372549f , 1.0f };
	FLinearColor 天蓝 = { 0.0f , 0.5333333333333f , 1.0f , 1.0f };
	FLinearColor 灰绿 = { 0.5019607843137f , 0.6274509803922f , 0.5019607843137f , 1.0f };
	FLinearColor 青蓝 = { 0.0f , 0.3764705882353f , 0.7529411764706f , 1.0f };
	FLinearColor 橙黄 = { 1.0f , 0.5019607843137f , 0.0f , 1.0f };
	FLinearColor 桃红 = { 1.0f , 0.3137254901961f , 0.5019607843137f , 1.0f };
	FLinearColor 芙红 = { 1.0f , 0.5019607843137f , 0.7529411764706f , 1.0f };
	FLinearColor 深灰 = { 0.3764705882353f , 0.3764705882353f , 0.3764705882353f , 1.0f };
	FLinearColor 藏青 = { 0.0f , 0.0f , 0.5019607843137f , 1.0f };
	FLinearColor 墨绿 = { 0.0f , 0.5019607843137f , 0.0f , 1.0f };
	FLinearColor 深青 = { 0.0f , 0.5019607843137f , 0.5019607843137f , 1.0f };
	FLinearColor 红褐 = { 0.5019607843137f , 0.0f , 0.0f , 1.0f };
	FLinearColor 紫红 = { 0.5019607843137f , 0.0f , 0.5019607843137f , 1.0f };
	FLinearColor 绿色 = { 0.0f , 1.0f , 0.0f , 0.5f };
	FLinearColor 艳青 = { 0.0f , 1.0f , 1.0f , 1.0f };
	FLinearColor 黑色 = { 0.0f , 0.0f , 0.0f , 1.0f };
	FLinearColor 灰色 = { 0.5019607843137f , 0.5019607843137f , 0.5019607843137f , 1.0f };
	FLinearColor 白色 = { 1.0f , 1.0f , 1.0f , 0.7843137254902f };
	FLinearColor 白色_ = { 0.9725490196078f , 0.9725490196078f , 1.0f , 1.0f };
	FLinearColor 白色__ = { 1.0f , 1.0f , 1.0f , 0.3921568627451f };
	FLinearColor 灰色_ = { 0.5019607843137f , 0.5019607843137f , 0.5019607843137f , 0.7843137254902f };
	FLinearColor 黑色_ = { 0.0f , 0.0f , 0.0f , 0.7843137254902f };
	FLinearColor 黑色__ = { 0.0f , 0.0f , 0.0f , 0.3137254901961f };
	FLinearColor 红色_ = { 1.0f , 0.0f , 0.0f , 0.7843137254902f };
	FLinearColor 品红_ = { 1.0f , 0.0f , 1.0f , 0.7843137254902f };
	FLinearColor 黄色_ = { 1.0f , 1.0f , 0.0f , 0.7843137254902f };
	FLinearColor 灰蓝_ = { 0.5019607843137f , 0.5019607843137f , 1.0f , 0.7843137254902f };
	FLinearColor 嫩绿_ = { 0.5019607843137f , 0.878431372549f , 0.0f , 0.7843137254902f };
	FLinearColor 深绿_ = { 0.0f , 0.878431372549f , 0.5019607843137f , 0.7843137254902f };
	FLinearColor 棕色_ = { 0.7529411764706f , 0.3764705882353f , 0.0f , 0.7843137254902f };
	FLinearColor 粉色_ = { 1.0f , 0.6588235294118f , 1.0f , 0.7843137254902f };
	FLinearColor 暗黄_ = { 0.8470588235294f , 0.8470588235294f , 0.0f , 1.0f };
	FLinearColor 银白_ = { 0.9254901960784f , 0.9254901960784f , 0.9254901960784f , 0.7843137254902f };
	FLinearColor 紫色_ = { 0.5647058823529f , 0.0f , 1.0f , 0.7843137254902f };
	FLinearColor 藏蓝_ = { 0.3450980392157f , 0.1882352941176f , 0.878431372549f , 0.7843137254902f };
	FLinearColor 天蓝_ = { 0.0f , 0.5333333333333f , 1.0f , 0.7843137254902f };
	FLinearColor 灰绿_ = { 0.5019607843137f , 0.6274509803922f , 0.5019607843137f , 0.7843137254902f };
	FLinearColor 青蓝_ = { 0.0f , 0.3764705882353f , 0.7529411764706f , 0.7843137254902f };
	FLinearColor 橙黄_ = { 1.0f , 0.5019607843137f , 0.0f , 0.7843137254902f };
	FLinearColor 桃红_ = { 1.0f , 0.3137254901961f , 0.5019607843137f , 0.7843137254902f };
	FLinearColor 芙红_ = { 1.0f , 0.5019607843137f , 0.7529411764706f , 0.7843137254902f };
	FLinearColor 深灰_ = { 0.3764705882353f , 0.3764705882353f , 0.3764705882353f , 0.7843137254902f };
	FLinearColor 藏青_ = { 0.0f , 0.0f , 0.5019607843137f , 0.7843137254902f };
	FLinearColor 墨绿_ = { 0.0f , 0.5019607843137f , 0.0f , 0.7843137254902f };
	FLinearColor 深青_ = { 0.0f , 0.5019607843137f , 0.5019607843137f , 0.7843137254902f };
	FLinearColor 红褐_ = { 0.5019607843137f , 0.0f , 0.0f , 0.7843137254902f };
	FLinearColor 紫红_ = { 0.5019607843137f , 0.0f , 0.5019607843137f , 0.7843137254902f };
	FLinearColor 绿色_ = { 0.0f , 1.0f , 0.0f , 1.0f };
	FLinearColor 绿色__ = { 0.0f , 1.0f , 0.0f , 0.3137254901961f };
	FLinearColor 艳青_ = { 0.0f , 1.0f , 1.0f , 0.7843137254902f };
	FLinearColor 土色_ = { 0.5450980392157f , 0.2705882352941f , 0.07450980392157f , 1.0f };
	FLinearColor 玻璃黑 = { 0.0f , 0.0f , 0.0f , 0.6274509803922f };
	FLinearColor 玻璃蓝 = { 0.2549019607843f , 0.4117647058824f , 0.8823529411765f , 0.3137254901961f };
	FLinearColor 玻璃黄 = { 1.0f , 1.0f , 0.0f , 0.6274509803922f };
	FLinearColor 玻璃 = { 0.7843137254902f , 0.7843137254902f , 0.7843137254902f , 0.2352941176471f };

	FLinearColor Box = 黄色;//方框可视
	FLinearColor Bone = 黄色;//骨骼可视
	FLinearColor NoBox = 白色;//方框不可视
	FLinearColor NoBone = 白色;//骨骼不可视
	FLinearColor AimBot = 红色;//预锁颜色

	FLinearColor Info = 黄色_;//信息可视
	FLinearColor NoInfo = 白色_;//信息不可视

	FLinearColor Lv1 = 白色;
	FLinearColor Lv2 = 绿色;
	FLinearColor Lv3 = 天蓝;
	FLinearColor Lv4 = 紫色;
	FLinearColor Lv5 = 橙黄;
	FLinearColor Vehicle = 艳青;

};
class CheatSwitch
{
public:
	bool Menu = true,
		Box,
		Bone = true,
		Name = true,
		Health = true,
		Distance = true,
		Display_Player = true,
		Display_Dropped = true,
		PlayerESP_Message = true,
		DroppedESP_hezi,
		Kill = true,
		WatchCount = true,
		Damage = true,
		Weapon = true,
		DroppedESP_Weapon = true,
		RankInfo = true,
		Team = true,
		Level ,
		Radar = true,//范围雷达
		EyeLine ,//视角射线
		Debug ,
		AimBot = true,
		DrawFov = true,
		Groggy = true,
		MissHit = true,
		Vehicle = true,
		Item = true,
		Icon ,
		Ammo ,
		Attach = true,
		Throw = true,
		Bag = true,
		AR ,
		LMG ,
		SR ,
		DMR ,
		SG ,
		Head ,
		SMG ,
		Special ,
		Armor = true,
		Heal = true,
		Key ,
		Other,
		qingshuang,
		AntiScreen = true,
		实体飞车,
		人物穿墙,
		一秒千拳,
		人物加速,
		人物穿楼,
		开车开枪,
		飞车说明 = false,
		无视碰撞;


	int AimSpeedX = 100,
		AimSpeedY = 100,
		AimFov = 185,
		ESPDistance = 1000,//透视距离
		AimDistance = 1000,//自瞄距离

		VehicleDistance = 1000,//载具距离
		ItemDistance = 100,
		UpDownSpeed = 3000,
		Speed = 4000;

	int AimPos = 2, AimKey = 2;
};
template<class T> T __ROL__(T value, int count)
{
	const uint32_t nbits = sizeof(T) * 8;

	if (count > 0)
	{
		count %= nbits;
		T high = value >> (nbits - count);
		if (T(-1) < 0) // signed value
			high &= ~((T(-1) << count));
		value <<= count;
		value |= high;
	}
	else
	{
		count = -count % nbits;
		T low = value << (nbits - count);
		value >>= count;
		value |= low;
	}
	return value;
}
inline uint8_t  __ROL1__(uint8_t  value, int count) { return __ROL__((uint8_t)value, count); }
inline uint16_t __ROL2__(uint16_t value, int count) { return __ROL__((uint16_t)value, count); }
inline uint32_t __ROL4__(uint32_t value, int count) { return __ROL__((uint32_t)value, count); }
inline uint64_t __ROL8__(uint64_t value, int count) { return __ROL__((uint64_t)value, count); }
inline uint8_t  __ROR1__(uint8_t  value, int count) { return __ROL__((uint8_t)value, -count); }
inline uint16_t __ROR2__(uint16_t value, int count) { return __ROL__((uint16_t)value, -count); }
inline uint32_t __ROR4__(uint32_t value, int count) { return __ROL__((uint32_t)value, -count); }
inline uint64_t __ROR8__(uint64_t value, int count) { return __ROL__((uint64_t)value, -count); }
EXTERN_C void _SpoofCall();
template<typename ReturnType = void, typename... Args,
	typename T, typename T1 = void*, typename T2 = void*, typename T3 = void*, typename T4 = void* >
	ReturnType SpoofCall(const T Index, T1 A1 = { }, T2 A2 = { }, T3 A3 = { }, T4 A4 = { }, Args... Arguments)
{
	return reinterpret_cast<ReturnType(*)(T1, T2, T3, T4, T, Args...)>(_SpoofCall)(A1, A2, A3, A4, Index, Arguments... // Stack must be aligned to 16 byte boundary.
		);
}
namespace Func {
	void HideInList(HMODULE hModule);
	BOOL SGetWindowInfo(PWINDOWINFO pwi);
	BOOL SGetCursorPos(LPPOINT lpPoint);
	SHORT GetAsyncKeyState2(int vKey);
	ULONG64 GetIconTexture(ULONG64 Value);
	HWND SGetForegroundWindow();
	bool LineTraceSingle(FVector TraceStart, FVector TraceEnd);
	bool LineTraceSingle(FVector TraceStart, FVector TraceEnd, FHitResult* OutFHitResult);
	void DrawRect(ULONG64 UCanvas, const FLinearColor* RectColor, float ScreenX, float ScreenY, float ScreenW, float ScreenH);
	void DrawLine(ULONG64 UCanvas, float StartScreenX, float StartScreenY, float EndScreenX, float EndScreenY, const FLinearColor* LineColor, float LineThickness);
	void K2_DrawText(ULONG64 UCanvas, ULONG64 RenderFont, struct FString RenderText, class FVector2D ScreenPosition, struct FLinearColor RenderColor,
		float Kerning, struct FLinearColor ShadowColor, class FVector2D ShadowOffset, bool bCentreX, bool bCentreY, bool bOutlined, struct FLinearColor OutlineColor);

	void K2_DrawTexture(ULONG64 UCanvas, ULONG64 RenderTexture, class FVector2D ScreenPosition, class FVector2D ScreenSize,
		class FVector2D CoordinatePosition, class FVector2D& CoordinateSize, struct FLinearColor RenderColor, EBlendMode BlendMode,
		float Rotation, class FVector2D& PivotPoint);




}
extern 	bool WriteMemory(uint64_t Address, void* Buffer, uint32_t Size);
extern 	bool ReadMemory(uint64_t Address, void* Buffer, uint32_t Size);
template <typename T>
T Read(uint64_t addr)
{
	T Novalue = T();
	ReadMemory(addr, &Novalue, sizeof(T));
	return Novalue;
}
template<typename T>
bool Write(uint64_t dwAddress, T Values)
{
	return WriteMemory(dwAddress, &Values, sizeof(T));
}
extern CheatSwitch* off;
extern GameData* Game;
extern ColorData* Colo;
extern int AntiScreenShotCount_Dx, AntiScreenShotCount_GDI, AntiScreenShotCount_CRC, AntiScreenShotCount_CRCb, dx判断, DX函数监控, DxCount;

namespace PubgData {
	inline ULONG64 GNames;

	DWORD32 GetNameIndex(ULONG64 obj);

	DWORD32 DecryptIndex(ULONG64 value);

	ULONG64 DecryptClass(ULONG64 address);

	ULONG64 DecryptOuter(ULONG64 address);

	ULONG64 XeDecryption(ULONG64 Encrypted);

	std::string GetName(ULONG value);

	unsigned GetNameHash(ULONG value);

	ULONG64 GetOuter(ULONG64 Outer);

	ULONG64 GetClass(ULONG64 Class);

	std::string GetFullName(ULONG64 Object);

	ULONG64 FindObject(const char* name);
	ULONG64 FindObjectClass(const char* name);
	ULONG64 GetWorld();

	ULONG64 GetCurrentLevel(ULONG64 World);

	ULONG64 GetActor(ULONG64 CurrentLevel);

	ULONG64 GetGameInstance(ULONG64 World);

	ULONG64 GetLocalPlayer(ULONG64 GameInstance);

	ULONG64 GetPlayerController(ULONG64 localPlayer);

	ULONG64 GetPlayerCameraManager(ULONG64 PlayerController);

	ULONG64 GetAcknowledgedPawn(ULONG64 PlayerController);

	ULONG64 GetMesh(ULONG64 ACharacter);

	ULONG64 GetPlayerState(ULONG64 ACharacter);

	int GetWatchCount(ULONG64 ACharacter);

	ULONG GetKillNum(ULONG64 ACharacter);

	ULONG GetSquadMemberIndex(ULONG64 ACharacter);

	float GetHealth(ULONG64 ACharacter);

	float GetHealthDie(ULONG64 ACharacter);

	int GetTeam(ULONG64 ACharacter);

	FVector GetPos(ULONG64 ACharacter);

	FVector GetVihecleSpeed(ULONG64 ACharacter);

	ULONG64 GetTslWeapon(ULONG64 ACharacter);

	ULONG64 GetTslWeaponA(ULONG64 ACharacter);

	std::string GetWeaponName(ULONG64 ACharacter);

	std::string GetPlayerName(ULONG64 ACharacter);

	int GetSurvivalLevel(ULONG64 ACharacter);

	float GetDamageDealtOnEnemy(ULONG64 ACharacter);

	PlayerInfo GetPlayerInfo(ULONG64 ACharacter);

	bool GetBoneMatrix(ULONG64 Mesh, FVector* Result, int BoneIdx);

	D3DMATRIX ToMatrixWithScale(FQuat Rotation, FVector Translation, FVector Scale3D);

	D3DMATRIX D3DMATRIXMultiply(D3DMATRIX pM1, D3DMATRIX pM2);

	FTransform GetSocketLocalTransform(ULONG64 Socket);

	FTransform GetBoneTransform(ULONG64 WeaponMesh, int BoneIdx, const FTransform& LocalToWorld);

	FTransform GetBoneTransform(ULONG64 WeaponMesh, FTransform SocketTransform, int BoneIdx);

	bool FindSocketAndIndex(ULONG64 Skeleton, FName InSocketName, int& OutIndex, ULONG64& OutSocket);

	int FindBoneIndex(ULONG64 SkeletalMesh, FName BoneName);

	bool FindSocketInfo(ULONG64 SkeletalMesh, FName InSocketName, FTransform& OutTransform, int& OutBoneIndex, int& OutIndex, ULONG64& OutSocket);

	bool GetSocketInfoByName(ULONG64 Mesh, FName InSocketName, FTransform& OutTransform, int& OutBoneIndex, ULONG64& OutSocket);

	int GetBoneIndex(ULONG64 Mesh, FName BoneName);

	ULONG64 GetStaticMeshComponentScopeType(ULONG64 Mehs);

	float GetScopingAttachPointRelativeZ(ULONG64 TslWeapon, FName ScopingAttachPoint);

	bool FindSocket(ULONG64 StaticMesh, FName InSocketName, ULONG64& OutSocket);

	bool GetSocketByName(ULONG64 Mesh, FName InSocketName, ULONG64& OutSocket);

	bool GetSocketTransform(ULONG64 Socket, FTransform& OutTransform, ULONG64& MeshComp);

	FTransform GetSocketTransform(ULONG64 StaticMeshComponent, FName InSocketName, ERelativeTransformSpace TransformSpace);

	FTransform GetSocketTransform(ULONG64 WeaponMesh, ERelativeTransformSpace TransformSpace, FName InSocketName);

	FVector WorldToScreen(const FVector& WorldLocation);

	bool WorldToScreen(FVector WorldLocation, FVector2D& pOut);

	ESight GetSight(ULONG64 TslWeapon);

	float GetZeroingDistance(ULONG64 TslWeapon, bool IsScoping);

	bool InsideCircle(int xc, int yc, int r, int x, int y);

	std::pair<float, float> GetBulletDropAndTravelTime(const FVector& GunLocation, const FRotator& GunRotation, const FVector& TargetPos, float ZeroingDistance, float BulletDropAdd, float InitialSpeed, float TrajectoryGravityZ, float BallisticDragScale, float BallisticDropScale, float BDS, float SimulationSubstepTime, float VDragCoefficient, FRichCurve RichCurve, int KeysNum, std::vector<FRichCurveKey> Keys);

	void PredictPos(ULONG64 ACharacter, FVector AimPos);
	void PredictPos2(ULONG64 ACharacter, FVector AimPos);

	float GetZoomFactor(ULONG64 MapWidget);

	FVector2D GetPosition(ULONG64 MapWidget);

	bool IsVisible(ULONG64 MapWidget,ULONG64 MarGrid);

	void EnumAllWidget(ULONG64 TslBaseHUD);


	FVector2D DrawMap(FVector ActorLocation,float WorldMapSize);

};