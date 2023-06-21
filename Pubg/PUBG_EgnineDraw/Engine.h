#pragma once
#include "info_bone.h"
extern bool bWorldMap, bRadarExtended;
enum ECharacterState : uint8_t
{
	Unk,
	Fire,
	Wounded,
	BeHit,
	Offline,
};

enum ERichCurveTangentWeightMode : uint8_t
{
	RCTWM_WeightedNone,
	RCTWM_WeightedArrive,
	RCTWM_WeightedLeave,
	RCTWM_WeightedBoth,
};
enum EWeaponAttachmentSlotID : uint8_t {
	None,
	Muzzle,
	LowerRail,
	UpperRail,
	Magazine,
	Stock,
	Angled
};

// Enum Engine.EBlendMode
enum EBlendMode : uint8_t
{
	BLEND_Opaque = 0,
	BLEND_Masked = 1,
	BLEND_Translucent = 2,
	BLEND_Additive = 3,
	BLEND_Modulate = 4,
	BLEND_AlphaComposite = 5,
	BLEND_MAX = 6
};
enum ERelativeTransformSpace : uint8_t
{
	RTS_World,
	RTS_Actor,
	RTS_Component,
	RTS_ParentBoneSpace,
};
enum class ESlateVisibility : uint8_t
{
	Visible = 0,
	Collapsed = 1,
	Hidden = 2,
	HitTestInvisible = 3,
	SelfHitTestInvisible = 4,
	ESlateVisibility_MAX = 5
};
enum ERichCurveExtrapolation : uint8_t
{
	RCCE_Cycle = 0,
	RCCE_CycleWithOffset = 1,
	RCCE_Oscillate = 2,
	RCCE_Linear = 3,
	RCCE_Constant = 4,
	RCCE_None = 5,
	RCCE_MAX = 6
};
enum ERichCurveInterpMode : uint8_t
{
	RCIM_Linear = 0,
	RCIM_Constant = 1,
	RCIM_Cubic = 2,
	RCIM_None = 3,
	RCIM_MAX = 4
};
enum class ESight
{
	Iron,
	RedDot,
	Holo,
	X2,
	X3,
	X4,
	X6,
	X8,
	X15
};
struct FLinearColor
{
	float                                              R;                                                        // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              G;                                                        // 0x0004(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              B;                                                        // 0x0008(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              A;                                                        // 0x000C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)

	inline FLinearColor()
		: R(0), G(0), B(0), A(0)
	{ }

	inline FLinearColor(float r, float g, float b, float a)
		: R(r),
		G(g),
		B(b),
		A(a)
	{ }
};
template<class T>
class TArray {
private:
	T* Data;
	int32_t Count;
	int32_t Max;

	friend struct FString;
public:
	size_t size(size_t MaxSize = 0x2000) const {
		return Count < MaxSize ? Count : MaxSize;
	}

	bool GetValue(int i, T& value) const {
		if (i < 0 || i >= size(0x2000)) return false;
		return memcpy(&value, (PVOID)(Data + sizeof(T) * i), sizeof(T));
	}

	bool GetValues(T& value, size_t MaxSize = 0x2000) const {
		return memcpy(&value, (PVOID)Data, sizeof(T) * size(MaxSize));
	}

	std::vector<T> GetVector(size_t MaxSize = 0x2000) const {
		std::vector<T> v(size(MaxSize));
		if (!GetValues(v[0], MaxSize))
			v.clear();

		return v;
	}

	operator std::vector<T>() const { return GetVector(); }

	T operator [](int i) const {
		T Value;
		if (!GetValue(i, Value))
			ZeroMemory(&Value, sizeof(Value));
		return Value;
	}
};
struct FText
{
	char buffer[64];
};

// ScriptStruct Engine.HitResult
// 0x0088
struct FHitResult
{
	unsigned char                                      bStartPenetrating : 1;                                    // 0x0000(0x0001)
	unsigned char                                      bBlockingHit : 1;                                         // 0x0000(0x0001)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0001(0x0003) MISSED OFFSET
	float                                              Time;                                                     // 0x0004(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              Distance;                                                 // 0x0008(0x0004) (ZeroConstructor, IsPlainOldData)
	struct FVector									   Location;                                                 // 0x000C(0x000C)
	struct FVector									   ImpactPoint;                                              // 0x0018(0x000C)
	struct FVector									   Normal;                                                   // 0x0024(0x000C)
	struct FVector									   ImpactNormal;                                             // 0x0030(0x000C)
	struct FVector									   TraceStart;                                               // 0x003C(0x000C)
	struct FVector									   TraceEnd;                                                 // 0x0048(0x000C)
	float                                              PenetrationDepth;                                         // 0x0054(0x0004) (ZeroConstructor, IsPlainOldData)
	int                                                Item;                                                     // 0x0058(0x0004) (ZeroConstructor, IsPlainOldData)
	PVOID								               PhysMaterial;                                             // 0x005C(0x0008) (ZeroConstructor, IsPlainOldData)
	PVOID								               Actor;                                                    // 0x0064(0x0008) (ZeroConstructor, IsPlainOldData)
	PVOID								               Component;                                                // 0x006C(0x0008) (ExportObject, ZeroConstructor, InstancedReference, IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                                       // 0x0074(0x0004) MISSED OFFSET
	ULONG64                                            BoneName;                                                 // 0x0078(0x0008) (ZeroConstructor, IsPlainOldData)
	int                                                FaceIndex;                                                // 0x0080(0x0004) (ZeroConstructor, IsPlainOldData)
	unsigned char                                      UnknownData02[0x4];                                       // 0x0084(0x0004) MISSED OFFSET
};
struct FString : public TArray<wchar_t>
{
	FString() = default;

	explicit FString(const wchar_t* other)
	{
		Max = Count = *other ? std::wcslen(other) + 1 : 0;

		if (Count)
		{
			Data = const_cast<wchar_t*>(other);
		}
	};

	inline bool IsValid() const
	{
		return Data != nullptr;
	}

	inline const wchar_t* cw_str() const
	{
		return Data;
	}

	inline const char* c_str() const
	{
		return (const char*)Data;
	}

	std::string ToString() const
	{
		size_t length = std::wcslen(Data);
		std::string str(length, '\0');
		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);

		return str;
	}

	std::wstring ToWString() const
	{
		std::wstring str(Data);
		return str;
	}
};

template<class T>
struct TSetElement {
	T Value;//0
	int HashNextId;//9
	int HashIndex;//A
};

template<class T>
class TSet : public TArray<TSetElement<T>> {};

template<class KeyType, class ValueType>
struct TPair {
	KeyType Key;
	ValueType Value;
};
template<class KeyType, class ValueType>
class TMap : public TSet<TPair<KeyType, ValueType>> {
public:
	bool GetValue(const KeyType& Key, ValueType& Value) const {

		for (const auto& Elem : this->GetVector()) {
			if (Elem.Value.Key == Key) {
				Value = Elem.Value.Value;
				return true;
			}
		}
		return false;
	}
};
struct PlayerInfo
{
	std::string PlayerName;
	std::string PlayerWeaponName;
	float PlayerDamageDealtOnEnemy;
	int PlayerTeamID;
	int PlayerNumKill;
	int PlayerWatchCount;
	int PlayerSurvivalLevel;
};
extern ULONG64 FindObject(const char* name);
inline FString AnsiToUnicode(std::string str)
{
	FString result;
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), NULL, 0);
	wchar_t* buffer = new wchar_t[len + 1];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size(), buffer, len);
	buffer[len] = '\0';
	result = FString(buffer);
	delete[] buffer;
	return result;
}
inline char* UnicodeToAnsi(char* wstr)
{
	if (!wstr) { return NULL; }
	int strleng = WideCharToMultiByte(CP_ACP, NULL, (LPCWCH)wstr, (int)wcslen((LPCWCH)wstr), NULL, 0, NULL, FALSE);
	char* str = new char[strleng + 1];
	WideCharToMultiByte(CP_ACP, NULL, (LPCWCH)wstr, (int)wcslen((LPCWCH)wstr), str, strleng, NULL, FALSE);
	str[strleng] = '\0';
	return str;
}

typedef struct _D3DMATRIX {
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;
		};
		float m[4][4];
	};
} D3DMATRIX;
struct FWeaponTrajectoryConfig
{
	float                                              InitialSpeed;                                             // 0x0000(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              HitDamage;                                                // 0x0004(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              VehicleDamageScalar;                                      // 0x0008(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              LowerClampDamage;                                         // 0x000C(0x0004) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	ULONG64	 										   BallisticCurve;                                           // 0x0010(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              RangeModifier;                                            // 0x0018(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              ReferenceDistance;                                        // 0x001C(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              TravelDistanceMax;                                        // 0x0020(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bUseMaxDamageDistance;                                    // 0x0024(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData00[0x3];                                       // 0x0025(0x0003) MISSED OFFSET
	float                                              SimulationSubstepTime;                                    // 0x0028(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              VDragCoefficient;                                         // 0x002C(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	float                                              BDS;                                                      // 0x0030(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bUseAdvancedBallistics;                                   // 0x0034(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               bCanProduceCrackSound;                                    // 0x0035(0x0001) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	bool                                               IsPenetrable;                                             // 0x0036(0x0001) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      UnknownData01[0x1];                                       // 0x0037(0x0001) MISSED OFFSET
	ULONG64											   DamageType;                                               // 0x0038(0x0008) (Edit, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
	unsigned char                                      bIsTrajectoryReplicationEnabled : 1;                      // 0x0040(0x0001) (Edit, DisableEditOnInstance)
	unsigned char                                      UnknownData02[0x3];                                       // 0x0041(0x0003) MISSED OFFSET
	float                                              WeaponSpread;                                             // 0x0044(0x0004) (Edit, BlueprintVisible, BlueprintReadOnly, ZeroConstructor, DisableEditOnInstance, IsPlainOldData)
};
struct FRichCurveKey
{
	BYTE		                                       InterpMode;                                               // 0x0000(0x0001) (ZeroConstructor, IsPlainOldData)
	BYTE		                                       TangentMode;                                              // 0x0001(0x0001) (ZeroConstructor, IsPlainOldData)
	BYTE		                                       TangentWeightMode;                                        // 0x0002(0x0001) (ZeroConstructor, IsPlainOldData)
	BYTE		                                       UnknownData00[0x1];                                       // 0x0003(0x0001) MISSED OFFSET
	float                                              Time;                                                     // 0x0004(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              Value;                                                    // 0x0008(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	float                                              ArriveTangent;                                            // 0x000C(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              ArriveTangentWeight;                                      // 0x0010(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              LeaveTangent;                                             // 0x0014(0x0004) (ZeroConstructor, IsPlainOldData)
	float                                              LeaveTangentWeight;                                       // 0x0018(0x0004) (ZeroConstructor, IsPlainOldData)
};
struct FKeyHandleMap
{
	unsigned char                                      UnknownData00[0x50];                                      // 0x0000(0x0050) MISSED OFFSET
};
struct FIndexedCurve
{
	unsigned char                                      UnknownData00[0x8];                                       // 0x0000(0x0008) MISSED OFFSET
	struct FKeyHandleMap                               KeyHandlesToIndices;                                      // 0x0008(0x0050) (Transient)
};
struct FRichCurve : public FIndexedCurve
{
	BYTE		                                       PreInfinityExtrap;                                        // 0x0058(0x0001) (ZeroConstructor, IsPlainOldData)
	BYTE		                                       PostInfinityExtrap;                                       // 0x0059(0x0001) (ZeroConstructor, IsPlainOldData)
	BYTE		                                       UnknownData00[0x2];                                       // 0x005A(0x0002) MISSED OFFSET
	float                                              DefaultValue;                                             // 0x005C(0x0004) (Edit, ZeroConstructor, IsPlainOldData)
	ULONG64						                       Keys;                                                     // 0x0060(0x0010) (Edit, EditFixedSize, ZeroConstructor)
};
struct FMargin
{
	float                                              Left;                                                     // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Top;                                                      // 0x0004(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Right;                                                    // 0x0008(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
	float                                              Bottom;                                                   // 0x000C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, IsPlainOldData)
};


// ScriptStruct TslGame.TslWidgetState
// 0x0060
struct FTslWidgetState
{
	unsigned char Pad[0x30];
	ULONG64 WidgetClass;	                                                                             // 0x0030(0x0008) (CPF_ZeroConstructor, CPF_Transient, CPF_IsPlainOldData)
	unsigned char                                      UnknownData00[0x8];                                       // 0x0038(0x0008) MISSED OFFSET
	ULONG64 Widget;                                                                               // 0x0040(0x0008) (CPF_ExportObject, CPF_ZeroConstructor, CPF_Transient, CPF_InstancedReference, CPF_IsPlainOldData)
	unsigned char                                      UnknownData01[0x18];                                      // 0x0048(0x0018) MISSED OFFSET
};
template<class TEnum>
class TEnumAsByte
{
public:
	typedef TEnum EnumType;
	TEnumAsByte() = default;
	TEnumAsByte(const TEnumAsByte&) = default;
	TEnumAsByte& operator=(const TEnumAsByte&) = default;
	FORCEINLINE TEnumAsByte(TEnum InValue) : Value(static_cast<uint8_t>(InValue)) {}
	explicit FORCEINLINE TEnumAsByte(int32_t InValue) : Value(static_cast<uint8_t>(InValue)) {}
	explicit FORCEINLINE TEnumAsByte(uint8_t InValue) : Value(InValue) {}
	bool operator==(TEnum InValue) const { return static_cast<TEnum>(Value) == InValue; }
	bool operator==(TEnumAsByte InValue) const { return Value == InValue.Value; }
	operator TEnum() const { return (TEnum)Value; }
	TEnum GetValue() const { return (TEnum)Value; }
private:
	uint8_t Value;
};

struct FName
{
	int ComparisonIndex = 0;
	int Number = 0;
	bool operator == (const FName& rhs) const { return ComparisonIndex == rhs.ComparisonIndex && Number == rhs.Number; }
	bool operator != (const FName& rhs) const { return !(*this == rhs); }
};
struct FMeshBoneInfo
{
	FName Name;
	int32_t ParentIndex;
	int32_t pad;
};