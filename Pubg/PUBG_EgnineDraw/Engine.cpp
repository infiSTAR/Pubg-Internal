#include "Main.h"
#include "info_weapon.h"




DWORD32 PubgData::GetNameIndex(ULONG64 obj) {
	auto value = Read<DWORD>(obj + offset_NamePrivate);
	if (!value)
		return 0;
	value = offset_NameIsROR ? __ROR4__(value ^ offset_NameIndexXor1, offset_NameIndexOne) : __ROL4__(value ^ offset_NameIndexXor1, offset_NameIndexOne);
	return value ^ (value << offset_NameIndexTwo) ^ offset_NameIndexXor2;
}
DWORD32 PubgData::DecryptIndex(ULONG64 value) {
	if (!value)
		return 0;
	value = offset_NameIsROR ? __ROR4__(value ^ offset_NameIndexXor1, offset_NameIndexOne) : __ROL4__(value ^ offset_NameIndexXor1, offset_NameIndexOne);
	return value ^ (value << offset_NameIndexTwo) ^ offset_NameIndexXor2;
}
ULONG64 PubgData::DecryptClass(ULONG64 address) {
	ULONG64 v22 = offset_ClassIsROR ? __ROR8__(address ^ offset_ClassXor1, offset_ClassOne) : __ROL8__(address ^ offset_ClassXor1, offset_ClassOne);
	return v22 ^ (v22 << offset_ClassTwo) ^ offset_ClassXor2;
}
ULONG64 PubgData::DecryptOuter(ULONG64 address) {
	ULONG64 v5 = offset_OuterIsROR ? __ROR8__(address ^ offset_OuterXor1, offset_OuterOne) : __ROL8__(address ^ offset_OuterXor1, offset_OuterOne);
	return (v5 ^ (v5 << offset_OuterTwo) ^ offset_OuterXor2);
}
ULONG64 PubgData::XeDecryption(ULONG64 Encrypted)
{
	auto XeDecryptionPtr = Read<ULONG64>(Game->GameBase + offset_XeDecryption);
//	printf("XeDecryptionPtr:%llX\n", XeDecryptionPtr);
	if (!XeDecryptionPtr) return NULL;
	return SpoofCall<ULONG64>(XeDecryptionPtr, 0, Encrypted);
}
std::string PubgData::GetName(ULONG value)
{
	ULONG Id = value / offset_ChunkSize;
	ULONG Idtemp = value % offset_ChunkSize;
	ULONG64 Serial = Read<ULONG64>(GNames + Id * sizeof(PVOID));
	ULONG64 Name = Read<ULONG64>(Serial + Idtemp * sizeof(PVOID));
	FText name = Read<FText>(Name + 0x10);
	auto rel = std::string(name.buffer);
	auto pos = rel.rfind('/');
	if (pos != std::string::npos)
	{
		rel = rel.substr(pos + 1);
	}
	return std::string(rel);
}
unsigned PubgData::GetNameHash(ULONG value) {
	return  CompileTime::StrHash(GetName(value));
}
ULONG64 PubgData::GetOuter(ULONG64 Outer) {
	return DecryptOuter(Read<ULONG64>(Outer + offset_OuterPrivate));
}
ULONG64 PubgData::GetClass(ULONG64 Class) {
	return DecryptClass(Read<ULONG64>(Class + offset_ClassPrivate));
}
std::string PubgData::GetFullName(ULONG64 Object)
{
	std::string name;
	for (auto outer = GetOuter(Object); outer; outer = GetOuter(outer)) {name = GetName(GetNameIndex(outer)) + "." + name;}
	name = GetName(GetNameIndex(GetClass(Object))) + " " + name + GetName(GetNameIndex(Object));
	return name;
}
ULONG64 PubgData::FindObject(const char* name){
	ULONG64 Result = 0;
	ULONG64 GObjectsTArray = XeDecryption(Read<ULONG64>(Game->GameBase + offset_GObjects));
	for (int i = 0; i < 10000000; i++) {
		auto object = Read<ULONG64>(GObjectsTArray + 0x18 * i);
		if (object && GetFullName(object) == name) {
			Result = object;
			break;
		}
	}
	return Result;
}
ULONG_PTR PubgData::FindObjectClass(const char* lpClassName) {
	ULONG64 GObjectsTArray = XeDecryption(Read<ULONG64>(Game->GameBase + offset_GObjects));
	if (GObjectsTArray > 0) {
		for (size_t i = 0; i < 1000000; i++) {
			ULONG64 GObjects = Read<ULONG64>(GObjectsTArray + 0x18 * i);
			ULONG FontId = GetNameIndex(GObjects);
			if (FontId > 0 && FontId < 1000000)
			{
				std::string Name = GetName(FontId);
				if (Name != ("NULL") && strcmp(Name.c_str(), lpClassName) == 0)
				{
					return GObjects;
				}
			}
		}
	}
	return 0;
}
ULONG64 PubgData::GetWorld()
{
	return XeDecryption(Read<ULONG64>(Game->GameBase + offset_UWorld));
}
ULONG64 PubgData::GetCurrentLevel(ULONG64 World)
{
	return XeDecryption(Read<ULONG64>(World + offset_CurrentLevel));
}
ULONG64 PubgData::GetActor(ULONG64 CurrentLevel)
{
	return XeDecryption(Read<ULONG64>(CurrentLevel + offset_Actor));
}
ULONG64 PubgData::GetGameInstance(ULONG64 World)
{
	return	XeDecryption(Read<ULONG64>((ULONG64)World + offset_TslGameInstance));
}
ULONG64 PubgData::GetLocalPlayer(ULONG64 GameInstance)
{
	return	XeDecryption(Read<ULONG64>(Read<ULONG64>(GameInstance + offset_TslLocalPlayer)));
}
ULONG64 PubgData::GetPlayerController(ULONG64 localPlayer)
{
	return	XeDecryption(Read<ULONG64>(localPlayer + offset_PlayerController));
}
ULONG64 PubgData::GetPlayerCameraManager(ULONG64 PlayerController)
{
	return	Read<ULONG64>(PlayerController + offset_PlayerCameraManager);
}
ULONG64 PubgData::GetAcknowledgedPawn(ULONG64 PlayerController)
{
	return	XeDecryption(Read<ULONG64>(PlayerController + offset_AcknowledgedPawn));
}
ULONG64 PubgData::GetMesh(ULONG64 ACharacter) {
	return	Read<ULONG64>(ACharacter + offset_Mesh);
}
ULONG64 PubgData::GetPlayerState(ULONG64 ACharacter) {
	return XeDecryption(Read<ULONG64>(ACharacter + offset_PlayerState));
}
int PubgData::GetWatchCount(ULONG64 ACharacter)
{
	return Read<uint32_t>(ACharacter + offset_SpectatedCount);
}
ULONG PubgData::GetKillNum(ULONG64 ACharacter)
{
	auto tmp = GetPlayerState(ACharacter);
	if (ValidPtr(tmp)) return NULL;
	return Read<ULONG>(tmp + offset_PlayerStatistics);
}
ULONG PubgData::GetSquadMemberIndex(ULONG64 ACharacter)
{
	auto tmp = GetPlayerState(ACharacter);
	if (ValidPtr(tmp)) return NULL;
	return Read<ULONG>(tmp + offset_SquadMemberIndex);
}
float PubgData::GetHealth(ULONG64 ACharacter)
{
	return Read<float>(ACharacter + offset_Health);
}
float PubgData::GetHealthDie(ULONG64 ACharacter)
{
	return Read<float>(ACharacter + offset_GroggyHealth);
}
int PubgData::GetTeam(ULONG64 ACharacter)
{
	return Read<int>(ACharacter + offset_LastTeamNum);
}
FVector PubgData::GetPos(ULONG64 ACharacter)
{
	auto RootComp =XeDecryption(Read<ULONG64>(ACharacter + offset_RootComponent));
	if (ValidPtr(RootComp))return FVector();
	return Read<FVector>(RootComp + offset_AbsoluteLocation);
}
FVector PubgData::GetVihecleSpeed(ULONG64 ACharacter)
{

	ULONG64	VehicleRiderComponent = Read<ULONG64>(ACharacter + offset_VehicleRiderComponent);
	if(ValidPtr(VehicleRiderComponent))return FVector(0, 0, 0);
	int Seatindex = Read<int>(VehicleRiderComponent + offset_SeatIndex);

	if (Seatindex != -1)
	{
		ULONG64 MovementComponent = Read<ULONG_PTR>(VehicleRiderComponent + offset_LastVehiclePawn);
		return Read<FVector>(MovementComponent + offset_ReplicatedMovement);
	}
	else
	{
		return FVector(0, 0, 0);
	}
}
ULONG64 PubgData::GetTslWeapon(ULONG64 ACharacter) {
	auto WeaponProcessor = Read<ULONG64>(ACharacter + offset_WeaponProcessor);
	if (ValidPtr(WeaponProcessor))return NULL;
	auto EquippedWeapons = Read<ULONG64>(WeaponProcessor + offset_EquippedWeapons);
	if (ValidPtr(EquippedWeapons))return NULL;
	auto CurrentWeaponIndex = Read<BYTE>(WeaponProcessor + offset_CurrentWeaponIndex);
	if (CurrentWeaponIndex >= 0 && CurrentWeaponIndex <= 3)
		return Read<ULONG64>(EquippedWeapons + CurrentWeaponIndex * sizeof(PVOID));
	return NULL;
}
ULONG64 PubgData::GetTslWeaponA(ULONG64 ACharacter) {
	auto WeaponProcessor = Read<ULONG64>(ACharacter + offset_WeaponProcessor);
	if (ValidPtr(WeaponProcessor))return NULL;
	auto EquippedWeapons = Read<ULONG64>(WeaponProcessor + offset_EquippedWeapons);
	if (ValidPtr(EquippedWeapons))return NULL;
	auto CurrentWeaponIndex = Read<BYTE>(WeaponProcessor + offset_CurrentWeaponIndex);

	return Read<ULONG64>(EquippedWeapons + CurrentWeaponIndex * sizeof(PVOID));
}
std::string PubgData::GetWeaponName(ULONG64 ACharacter) {

	auto WeaponProcessor = Read<ULONG64>(ACharacter + offset_WeaponProcessor);
	if (ValidPtr(WeaponProcessor))return "";
	auto EquippedWeapons = Read<ULONG64>(WeaponProcessor + offset_EquippedWeapons);
	if (ValidPtr(EquippedWeapons))return "";
	auto CurrentWeaponIndex = Read<BYTE>(WeaponProcessor + offset_CurrentWeaponIndex);
	if (CurrentWeaponIndex >= 0 && CurrentWeaponIndex <= 4)
	{
		auto TslWeapon = Read<ULONG64>(EquippedWeapons + CurrentWeaponIndex * sizeof(PVOID));
		if (ValidPtr(TslWeapon))return "";
		uint32_t WeaponID = GetNameIndex(TslWeapon);
		std::string WeaponName = GetName(WeaponID);
		WeaponName = WeaponName.substr(4, WeaponName.size());
		WeaponName = WeaponName.substr(0, WeaponName.size() - 2);
		return WeaponName + sformat((const char*)"({})"e, std::to_string(Read<SHORT>(TslWeapon + offset_CurrentAmmoData)));
	}
	return "";
}
std::string PubgData::GetPlayerName(ULONG64 ACharacter)
{
	auto Name = Read<ULONG64>(ACharacter + offset_CharacterName);
	if (ValidPtr(Name))return "";
	auto name = Read<FText>(Name);
	return UnicodeToAnsi(name.buffer);
}
int PubgData::GetSurvivalLevel(ULONG64 ACharacter)
{
	auto tmp = GetPlayerState(ACharacter);
	if (ValidPtr(tmp)) return NULL;
	return Read<int>(tmp + offset_PubgIdData + offset_SurvivalLevel);
}
float PubgData::GetDamageDealtOnEnemy(ULONG64 ACharacter)
{
	auto tmp = GetPlayerState(ACharacter);
	if (ValidPtr(tmp)) return NULL;
	return Read<float>(tmp + offset_DamageDealtOnEnemy);
}
PlayerInfo PubgData::GetPlayerInfo(ULONG64 ACharacter) {
	PlayerInfo Info;
	Info.PlayerName = GetPlayerName(ACharacter);
	Info.PlayerTeamID = GetTeam(ACharacter);
	Info.PlayerNumKill = GetKillNum(ACharacter);
	Info.PlayerWatchCount = GetWatchCount(ACharacter);
	Info.PlayerWeaponName = GetWeaponName(ACharacter);
	Info.PlayerDamageDealtOnEnemy = GetDamageDealtOnEnemy(ACharacter);
	Info.PlayerSurvivalLevel = GetSurvivalLevel(ACharacter);
	return Info;
}
bool PubgData::GetBoneMatrix(ULONG64 Mesh, FVector* Result, int BoneIdx)
{
	auto Bone = Read<ULONG64>(Mesh + offset_StaticMesh);
	if (ValidPtr(Bone))return false;
	FTransform BoneArray = Read<FTransform>(Bone + BoneIdx * sizeof(FTransform));
	FTransform ComponentToWorld = Read<FTransform>(Mesh + offset_ComponentToWorld);
	D3DMATRIX BoneMatrix = ToMatrixWithScale(BoneArray.Rotation, BoneArray.Translation, BoneArray.Scale3D);
	D3DMATRIX ComponentToWorldMatrix = ToMatrixWithScale(ComponentToWorld.Rotation, ComponentToWorld.Translation, ComponentToWorld.Scale3D);
	D3DMATRIX NewMatrix = D3DMATRIXMultiply(BoneMatrix, ComponentToWorldMatrix);
	*Result = { NewMatrix._41, NewMatrix._42, NewMatrix._43 };
	return true;
}
D3DMATRIX PubgData::ToMatrixWithScale(FQuat Rotation, FVector Translation, FVector Scale3D)
{
	D3DMATRIX m;

	m._41 = Translation.X;
	m._42 = Translation.Y;
	m._43 = Translation.Z;

	float x2 = Rotation.X + Rotation.X;
	float y2 = Rotation.Y + Rotation.Y;
	float z2 = Rotation.Z + Rotation.Z;

	float xx2 = Rotation.X * x2;
	float yy2 = Rotation.Y * y2;
	float zz2 = Rotation.Z * z2;
	m._11 = (1.0f - (yy2 + zz2)) * Scale3D.X;
	m._22 = (1.0f - (xx2 + zz2)) * Scale3D.Y;
	m._33 = (1.0f - (xx2 + yy2)) * Scale3D.Z;

	float yz2 = Rotation.Y * z2;
	float wx2 = Rotation.W * x2;
	m._32 = (yz2 - wx2) * Scale3D.Z;
	m._23 = (yz2 + wx2) * Scale3D.Y;

	float xy2 = Rotation.X * y2;
	float wz2 = Rotation.W * z2;
	m._21 = (xy2 - wz2) * Scale3D.Y;
	m._12 = (xy2 + wz2) * Scale3D.X;

	float xz2 = Rotation.X * z2;
	float wy2 = Rotation.W * y2;
	m._31 = (xz2 + wy2) * Scale3D.Z;
	m._13 = (xz2 - wy2) * Scale3D.X;

	m._14 = 0.0f;
	m._24 = 0.0f;
	m._34 = 0.0f;
	m._44 = 1.0f;
	return m;
}
D3DMATRIX PubgData::D3DMATRIXMultiply(D3DMATRIX pM1, D3DMATRIX pM2)
{
	D3DMATRIX pOut;
	pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
	pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
	pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
	pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
	pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
	pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
	pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
	pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
	pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
	pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
	pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
	pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
	pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
	pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
	pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
	pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;
	return pOut;
}
FTransform PubgData::GetSocketLocalTransform(ULONG64 Socket) {

	auto RelativeRotation = Read<FRotator>(Socket + offset_SkeletalRelativeRotation);
	auto RelativeLocation = Read<FVector>(Socket + offset_SkeletalRelativeLocation);
	auto RelativeScale = Read<FVector>(Socket + offset_SkeletalRelativeScale);

	return FTransform(RelativeRotation, RelativeLocation, RelativeScale);
}
FTransform PubgData::GetBoneTransform(ULONG64 WeaponMesh, int BoneIdx, const FTransform& LocalToWorld) {

	auto BoneSpaceTransforms = Read<ULONG64>(WeaponMesh + offset_StaticMesh);
	if (ValidPtr(BoneSpaceTransforms)) return FTransform();
	FTransform BoneTransform = Read<FTransform>(BoneSpaceTransforms + BoneIdx * sizeof(FTransform));
	return FTransform(BoneTransform) * LocalToWorld;
}
FTransform PubgData::GetBoneTransform(ULONG64 WeaponMesh,FTransform SocketTransform, int BoneIdx) {

	return GetBoneTransform(WeaponMesh,BoneIdx, SocketTransform);
}
bool PubgData::FindSocketAndIndex(ULONG64 Skeleton, FName InSocketName, int& OutIndex, ULONG64& OutSocket) {
	int Index = -1;

	auto Sockets = Read<TArray<ULONG64>>(Skeleton + offset_SkeletonSockets);
	if (!Sockets.size()) return false;
	for (const auto& SocketPtr : Sockets.GetVector())
	{
		Index++;
		auto SocketName = Read<FName>(SocketPtr + offset_SkeletalSocketName);
		if (SocketName == InSocketName) {
			OutIndex = Index;
			OutSocket = SocketPtr;
			return true;
		}
	}
	return false;
}

int PubgData::FindBoneIndex(ULONG64 SkeletalMesh, FName BoneName) {
	int Index = -1;
	auto FinalRefBoneInfo = Read<TArray<FMeshBoneInfo>>(SkeletalMesh + offset_FinalRefBoneInfo);
	if (!FinalRefBoneInfo.size()) return INDEX_NONE;
	for (const FMeshBoneInfo& BoneInfo : FinalRefBoneInfo.GetVector())
	{
		Index++;
		if (BoneName == BoneInfo.Name)
			return Index;
	}
	return INDEX_NONE;
}
bool PubgData::FindSocketInfo(ULONG64 SkeletalMesh, FName InSocketName, FTransform& OutTransform, int& OutBoneIndex, int& OutIndex, ULONG64& OutSocket) {
	OutIndex = INDEX_NONE;
	OutTransform = FTransform();
	OutBoneIndex = INDEX_NONE;
	int Index = -1;
	auto Sockets = Read<TArray<ULONG64>>(SkeletalMesh + offset_SkeletalSockets);
	if (!Sockets.size()) return false;
	for (const auto& SocketPtr : Sockets.GetVector())
	{
		Index++;
		auto SocketName = Read<FName>(SocketPtr + offset_SkeletalSocketName);
		if (SocketName == InSocketName) {
			OutIndex = Index;
			OutTransform = GetSocketLocalTransform(SocketPtr);
			OutBoneIndex = FindBoneIndex(SkeletalMesh, Read<FName>(SocketPtr + offset_BoneName));
			OutSocket = SocketPtr;
			return true;
		}
	}


	ULONG64 Skeleton = Read<ULONG64>(SkeletalMesh + offset_Skeleton);
	if (ValidPtr(Skeleton))
		return false;

	ULONG64 SkeletonSocket;
	if (!FindSocketAndIndex(Skeleton, InSocketName, OutIndex, SkeletonSocket))
		return false;

	OutIndex += (int32_t)Sockets.size();
	OutTransform = GetSocketLocalTransform(SkeletonSocket);
	OutBoneIndex = FindBoneIndex(SkeletalMesh, Read<FName>(SkeletonSocket + offset_BoneName));
	OutSocket = SkeletonSocket;
	return true;
}
bool PubgData::GetSocketInfoByName(ULONG64 Mesh, FName InSocketName, FTransform& OutTransform, int& OutBoneIndex, ULONG64& OutSocket) {
	ULONG64 SkeletalMesh = Read<ULONG64>(Mesh + offset_SkeletalMesh);
	if (ValidPtr(SkeletalMesh))
		return false;
	
	int SocketIndex;
	return FindSocketInfo(SkeletalMesh, InSocketName, OutTransform, OutBoneIndex, SocketIndex, OutSocket);
}
int PubgData::GetBoneIndex(ULONG64 Mesh, FName BoneName) {
	int BoneIndex = -1;

	ULONG64 SkeletalMesh = Read<ULONG64>(Mesh + offset_SkeletalMesh);
	if (BoneName != NAME_None && !ValidPtr(SkeletalMesh))
		BoneIndex = FindBoneIndex(SkeletalMesh, BoneName);

	return BoneIndex;
}
ULONG64 PubgData::GetStaticMeshComponentScopeType(ULONG64 Mesh){
	ULONG64 Result = 0;
	auto AttachedStaticComponentMap = Read<TMap<TEnumAsByte<EWeaponAttachmentSlotID>, ULONG64>>(Mesh + offset_AttachedStaticComponentMap);
	AttachedStaticComponentMap.GetValue(EWeaponAttachmentSlotID::UpperRail, Result);
	return Result;
}


float PubgData::GetScopingAttachPointRelativeZ(ULONG64 TslWeapon, FName ScopingAttachPoint) {
	float Default = 15.0f;
	auto WeaponMesh = XeDecryption(Read<ULONG64>(TslWeapon + offset_Mesh3P));
	if(ValidPtr(WeaponMesh)) return Default;
	ULONG64 StaticMeshComponent = GetStaticMeshComponentScopeType(WeaponMesh);
	auto ComponentToWorld = Read<FTransform>(WeaponMesh + offset_ComponentToWorld);
	if (!ValidPtr(StaticMeshComponent)) {
		//Scope Attached
		auto StaticComponentToWorld = Read<FTransform>(StaticMeshComponent + offset_ComponentToWorld);
		const float RelativeZ_1 = GetSocketTransform(StaticMeshComponent, ScopingAttachPoint, RTS_Component).Translation.Z;
		const float RelativeZ_2 = StaticComponentToWorld.GetRelativeTransform(ComponentToWorld).Translation.Z;
		return RelativeZ_1 + RelativeZ_2;
	}
	else
		return GetSocketTransform(WeaponMesh, RTS_Component, ScopingAttachPoint).Translation.Z;

	return Default;
}
bool PubgData::FindSocket(ULONG64 StaticMesh, FName InSocketName, ULONG64& OutSocket) {
	if (InSocketName == NAME_None)
		return false;
	auto Sockets = Read<TArray<ULONG64>>(StaticMesh + offset_StaticSockets);
	if (!Sockets.size()) return false;
	for (const auto& SocketPtr : Sockets.GetVector()) {

		auto SocketName = Read<FName>(SocketPtr + offset_StaticSocketName);
		if (SocketName == InSocketName) {
			OutSocket = SocketPtr;
			return true;
		}
	}
	return false;

}
bool PubgData::GetSocketByName(ULONG64 Mesh, FName InSocketName, ULONG64& OutSocket) {

	ULONG64 StaticMMesh = Read<ULONG64>(Mesh + offset_StaticMesh);
	if (ValidPtr(StaticMMesh))
		return false;

	return FindSocket(StaticMMesh, InSocketName, OutSocket);
}
bool PubgData::GetSocketTransform(ULONG64 Socket, FTransform& OutTransform, ULONG64& MeshComp) {
	auto RelativeRotation = Read<FRotator>(Socket + offset_StaticRelativeRotation);
	auto RelativeLocation = Read<FVector>(Socket + offset_StaticRelativeLocation);
	auto RelativeScale = Read<FVector>(Socket + offset_StaticRelativeScale);
	auto ComponentToWorld = Read<FTransform>(MeshComp + offset_ComponentToWorld);
	OutTransform = FTransform(RelativeRotation, RelativeLocation, RelativeScale) * ComponentToWorld;
	return true;
}
FTransform GetSocketTransform(FName SocketName, ERelativeTransformSpace TransformSpace, FTransform ComponentToWorld) {
	switch (TransformSpace)
	{
	case RTS_Actor:
	case RTS_Component:
	case RTS_ParentBoneSpace:
	{
		return FTransform();
	}
	}
	return ComponentToWorld;
}
FTransform PubgData::GetSocketTransform(ULONG64 StaticMeshComponent, FName InSocketName, ERelativeTransformSpace TransformSpace) {
	auto ComponentToWorld = Read<FTransform>(StaticMeshComponent + offset_ComponentToWorld);
	if (InSocketName != NAME_None) {
		ULONG64 Socket;
		if (GetSocketByName(StaticMeshComponent, InSocketName, Socket))
		{
			FTransform SocketWorldTransform;
			if (GetSocketTransform(Socket, SocketWorldTransform, StaticMeshComponent))
			{
				switch (TransformSpace)
				{
					case RTS_World:
					{
						return SocketWorldTransform;
					}
					case RTS_Component:
					{
						return SocketWorldTransform.GetRelativeTransform(ComponentToWorld);
					}
				}
			}
		}
	}

	return GetSocketTransform(InSocketName, TransformSpace, ComponentToWorld);
}
FTransform PubgData::GetSocketTransform(ULONG64 WeaponMesh, ERelativeTransformSpace TransformSpace, FName InSocketName) {
	auto ComponentToWorld = Read<FTransform>(WeaponMesh + offset_ComponentToWorld);
	FTransform OutSocketTransform = ComponentToWorld;
	if (InSocketName != NAME_None)
	{
		int SocketBoneIndex;
		FTransform SocketLocalTransform;
		ULONG64 SkeletalMeshSocket;
		if (GetSocketInfoByName(WeaponMesh, InSocketName, SocketLocalTransform, SocketBoneIndex, SkeletalMeshSocket)) {
			if (TransformSpace == RTS_ParentBoneSpace)
			{
				//we are done just return now
				return SocketLocalTransform;
			}

			if (SocketBoneIndex != -1)
			{
				FTransform BoneTransform = GetBoneTransform(WeaponMesh, ComponentToWorld, SocketBoneIndex);
				OutSocketTransform = SocketLocalTransform * BoneTransform;
			}
		}
		else {
			int BoneIndex = GetBoneIndex(WeaponMesh, InSocketName);
			if (BoneIndex != -1)
			{
				OutSocketTransform = GetBoneTransform(WeaponMesh, ComponentToWorld, BoneIndex);
			}
		}
	}
	switch (TransformSpace)
	{

	case RTS_Component:
	{
		return OutSocketTransform.GetRelativeTransform(ComponentToWorld);
	}
	}
	return OutSocketTransform;
}


FVector PubgData::WorldToScreen(const FVector& WorldLocation) {
	FVector Screenlocation;
	auto RotationMatrix = Game->Rotation.GetMatrix();
	FVector AxisX = RotationMatrix.GetScaledAxisX();
	FVector AxisY = RotationMatrix.GetScaledAxisY();
	FVector AxisZ = RotationMatrix.GetScaledAxisZ();

	FVector vDelta(WorldLocation - Game->Location);
	FVector vTransformed(vDelta | AxisY, vDelta | AxisZ, vDelta | AxisX);

	if (vTransformed.Z == 0.0f)
		vTransformed.Z = -0.001f;

	Screenlocation.Z = vTransformed.Z;

	if (vTransformed.Z < 0.0f)
		vTransformed.Z = -vTransformed.Z;

	float ScreenCenterX = Game->ScreenCenter.X;
	float ScreenCenterY = Game->ScreenCenter.Y;
	float TangentFOV = tanf(ConvertToRadians(Game->FOV / 2.0f));

	Screenlocation.X = ScreenCenterX + vTransformed.X * (ScreenCenterX / TangentFOV) / vTransformed.Z;
	Screenlocation.Y = ScreenCenterY - vTransformed.Y * (ScreenCenterX / TangentFOV) / vTransformed.Z;
	return Screenlocation;
}
bool PubgData::WorldToScreen(FVector WorldLocation, FVector2D& pOut) {
	auto RotationMatrix = Game->Rotation.GetMatrix();
	FVector vAxisX = RotationMatrix.GetScaledAxisX();
	FVector vAxisY = RotationMatrix.GetScaledAxisY();
	FVector vAxisZ = RotationMatrix.GetScaledAxisZ();

	FVector vDelta = WorldLocation - Game->Location;
	FVector vTransformed(vDelta | vAxisY, vDelta | vAxisZ, vDelta | vAxisX);
	if (vTransformed.Z == 0.0f)
		vTransformed.Z = -0.001f;
	auto VieW = vTransformed.Z;
	if (vTransformed.Z < 0.0f)
		vTransformed.Z = -vTransformed.Z;

	auto ScreenCenterX = Game->ScreenCenter.X;
	auto ScreenCenterY = Game->ScreenCenter.Y;
	float TangentFOV = tanf(ConvertToRadians(Game->FOV / 2.0f));
	pOut.X = ScreenCenterX + vTransformed.X * (ScreenCenterX / TangentFOV) / vTransformed.Z;
	pOut.Y = ScreenCenterY - vTransformed.Y * (ScreenCenterX / TangentFOV) / vTransformed.Z;

	return VieW > 0.0f;
}
ESight PubgData::GetSight(ULONG64 TslWeapon) {

	auto AttachedItems = Read<ULONG64>(TslWeapon + offset_AttachedItems);
	if (ValidPtr(AttachedItems))return ESight::Iron;;
	auto AttachedItemsCount = Read<int>(TslWeapon + offset_AttachedItems + 8);
	for (auto i = 0; i < AttachedItemsCount; i++)
	{
		auto AttachableItemPtr = Read<ULONG64>(AttachedItems + i * sizeof(PVOID));
		if (ValidPtr(AttachableItemPtr))return ESight::Iron;;
		auto WeaponAttachmentData = Read<ULONG64>(AttachableItemPtr + offset_bVested + 4);
		if (ValidPtr(WeaponAttachmentData))return ESight::Iron;;
		auto ItemID = Read<ULONG>(WeaponAttachmentData + offset_ItemID);
		auto Name = GetNameHash(ItemID);
		switch (Name) {
			HASH_CASE("Item_Attach_Weapon_Upper_PM2_01_C"h, ESight::X15);
			HASH_CASE("Item_Attach_Weapon_Upper_CQBSS_C"h, ESight::X8);
			HASH_CASE("Item_Attach_Weapon_Upper_Scope6x_C"h, ESight::X6);
			HASH_CASE("Item_Attach_Weapon_Upper_ACOG_01_C"h, ESight::X4);
			HASH_CASE("Item_Attach_Weapon_Upper_Scope3x_C"h, ESight::X3);
			HASH_CASE("Item_Attach_Weapon_Upper_Aimpoint_C"h, ESight::X2);
			HASH_CASE("Item_Attach_Weapon_Upper_DotSight_01_C"h, ESight::RedDot);
			HASH_CASE("Item_Attach_Weapon_Upper_Holosight_C"h, ESight::Holo);
		}
	}
	return ESight::Iron;
}
float PubgData::GetZeroingDistance(ULONG64 TslWeapon, bool IsScoping) {
	uint32_t WeaponID = GetNameIndex(TslWeapon);
	auto Weapon = GetNameHash(WeaponID);
	auto bCantedSighted = Read<bool>(TslWeapon + offset_bLoackLoadedAmmo + 1);
	auto CurrentZeroLevel = Read<int>(TslWeapon + offset_CurrentZeroLevel);
	if (bCantedSighted)
		return Weapon == "WeapP90_C"h ? 100.0f : 50.0f;
	auto ZeroingInfo = GetWeaponInfo(Weapon).ZeroingInfo;
	int ZeroLevel = IsScoping ? CurrentZeroLevel : 0;
	switch (GetSight(TslWeapon)) {
	case ESight::X15:
	case ESight::X8:
		return ZeroingInfo.BaseScope + ZeroingInfo.Increment * ZeroLevel;
	case ESight::X6:
	case ESight::X4:
	case ESight::X3:
	case ESight::X2:
	case ESight::RedDot:
		return ZeroingInfo.BaseScope;
	case ESight::Holo:
		return ZeroingInfo.BaseHolo;
	}

	return ZeroingInfo.BaseIron + ZeroingInfo.Increment * ZeroLevel;
}
BOOL WorldToScreen_Aim(FVector WorldLocation, FVector* pOut)
{
	ULONG64 AnimScriptInstance = Read<ULONG64>(PubgData::GetMesh(Game->MyPlayerAddress) + offset_AnimScriptInstance);
	if (ValidPtr(AnimScriptInstance))return false;
	auto ControlRotation = Read<FRotator>(AnimScriptInstance + offset_ControlRotation_CP);
	auto RecoilADSRotation = Read<FRotator>(AnimScriptInstance + offset_RecoilADSRotation_CP);
	if (RecoilADSRotation.Length() > 0.25f)
	{
		RecoilADSRotation.Yaw -= Read<float>(AnimScriptInstance + offset_LeanLeftAlpha_CP) / 4.0f;
		RecoilADSRotation.Yaw += Read<float>(AnimScriptInstance + offset_LeanRightAlpha_CP) / 4.0f;
	}

	auto RotationMatrix = (ControlRotation + RecoilADSRotation).GetMatrix();
	FVector vAxisX = RotationMatrix.GetScaledAxisX();
	FVector vAxisY = RotationMatrix.GetScaledAxisY();
	FVector vAxisZ = RotationMatrix.GetScaledAxisZ();

	FVector vDelta(WorldLocation - Game->Location);
	FVector vTransformed(vDelta | vAxisY, vDelta | vAxisZ, vDelta | vAxisX);

	if (vTransformed.Z == 0.0f)
		vTransformed.Z = -0.001f;
	pOut->Z = vTransformed.Z;
	if (vTransformed.Z < 0.0f)
		vTransformed.Z = -vTransformed.Z;

	float FovAngle = Read<float>(Game->PlayerCameraManager + offset_CameraFOV);
	auto ScreenCenterX = Game->ScreenCenter.X;
	auto ScreenCenterY = Game->ScreenCenter.Y;
	float TangentFOV = tanf(ConvertToRadians(FovAngle / 2.0f));

	pOut->X = ScreenCenterX + vTransformed.X * (ScreenCenterX / TangentFOV) / vTransformed.Z;
	pOut->Y = ScreenCenterY - vTransformed.Y * (ScreenCenterX / TangentFOV) / vTransformed.Z;

	return pOut->Z > 0.0f;
}
typedef  int	 		int32;		// 32-bit signed.
__forceinline int32 FloorToInt(float F)
{
	return _mm_cvt_ss2si(_mm_set_ss(F + F - 0.5f)) >> 1;
}
template< class T >
constexpr __forceinline T Abs(const T A)
{
	return (A >= (T)0) ? A : -A;
}
inline bool IsItNotWeighted(const FRichCurveKey& Key1, const FRichCurveKey& Key2)
{
	return ((Key1.TangentWeightMode == RCTWM_WeightedNone || Key1.TangentWeightMode == RCTWM_WeightedArrive)
		&& (Key2.TangentWeightMode == RCTWM_WeightedNone || Key2.TangentWeightMode == RCTWM_WeightedLeave));
}
void CycleTime(float MinTime, float MaxTime, float& InTime, int& CycleCount)
{
	float InitTime = InTime;
	float Duration = MaxTime - MinTime;

	if (InTime > MaxTime)
	{
		CycleCount = FloorToInt((MaxTime - InTime) / Duration);
		InTime = InTime + Duration * CycleCount;
	}
	else if (InTime < MinTime)
	{
		CycleCount = FloorToInt((InTime - MinTime) / Duration);
		InTime = InTime - Duration * CycleCount;
	}

	if (InTime == MaxTime && InitTime < MinTime)
	{
		InTime = MinTime;
	}

	if (InTime == MinTime && InitTime > MaxTime)
	{
		InTime = MaxTime;
	}

	CycleCount = Abs(CycleCount);
}
void RemapTimeValue(float& InTime, float& CycleValueOffset, FRichCurve RichCurve, int KeysNum, std::vector<FRichCurveKey> Keys)
{
	const int NumKeys = KeysNum;

	if (NumKeys < 2)
	{
		return;
	}

	if (InTime <= Keys[0].Time)
	{
		if (RichCurve.PreInfinityExtrap != RCCE_Linear && RichCurve.PreInfinityExtrap != RCCE_Constant)
		{
			float MinTime = Keys[0].Time;
			float MaxTime = Keys[NumKeys - 1].Time;

			int CycleCount = 0;
			CycleTime(MinTime, MaxTime, InTime, CycleCount);

			if (RichCurve.PreInfinityExtrap == RCCE_CycleWithOffset)
			{
				float DV = Keys[0].Value - Keys[NumKeys - 1].Value;
				CycleValueOffset = DV * CycleCount;
			}
			else if (RichCurve.PreInfinityExtrap == RCCE_Oscillate)
			{
				if (CycleCount % 2 == 1)
				{
					InTime = MinTime + (MaxTime - InTime);
				}
			}
		}
	}
	else if (InTime >= Keys[NumKeys - 1].Time)
	{
		if (RichCurve.PostInfinityExtrap != RCCE_Linear && RichCurve.PostInfinityExtrap != RCCE_Constant)
		{
			float MinTime = Keys[0].Time;
			float MaxTime = Keys[NumKeys - 1].Time;

			int CycleCount = 0;
			CycleTime(MinTime, MaxTime, InTime, CycleCount);

			if (RichCurve.PostInfinityExtrap == RCCE_CycleWithOffset)
			{
				float DV = Keys[NumKeys - 1].Value - Keys[0].Value;
				CycleValueOffset = DV * CycleCount;
			}
			else if (RichCurve.PostInfinityExtrap == RCCE_Oscillate)
			{
				if (CycleCount % 2 == 1)
				{
					InTime = MinTime + (MaxTime - InTime);
				}
			}
		}
	}
}
float Eval(float InTime, float InDefaultValue, FRichCurve RichCurve, int KeysNum, std::vector<FRichCurveKey> Keys)
{
	// Remap time if extrapolation is present and compute offset value to use if cycling 
	float CycleValueOffset = 0;
	RemapTimeValue(InTime, CycleValueOffset, RichCurve, KeysNum, Keys);

	const int NumKeys = KeysNum;

	// If the default value hasn't been initialized, use the incoming default value
	float InterpVal = RichCurve.DefaultValue == 3.402823466e+38F ? InDefaultValue : RichCurve.DefaultValue;

	if (NumKeys == 0)
	{
		// If no keys in curve, return the Default value.
	}
	else if (NumKeys < 2 || (InTime <= Keys[0].Time))
	{
		if (RichCurve.PreInfinityExtrap == RCCE_Linear && NumKeys > 1)
		{
			float DT = Keys[1].Time - Keys[0].Time;

			if (IsNearlyZero(DT))
			{
				InterpVal = Keys[0].Value;
			}
			else
			{
				float DV = Keys[1].Value - Keys[0].Value;
				float Slope = DV / DT;

				InterpVal = Slope * (InTime - Keys[0].Time) + Keys[0].Value;
			}
		}
		else
		{
			// Otherwise if constant or in a cycle or oscillate, always use the first key value
			InterpVal = Keys[0].Value;
		}
	}
	else if (InTime < Keys[NumKeys - 1].Time)
	{
		// perform a lower bound to get the second of the interpolation nodes
		int first = 1;
		int last = NumKeys - 1;
		int count = last - first;

		while (count > 0)
		{
			int step = count / 2;
			int middle = first + step;

			if (InTime >= Keys[middle].Time)
			{
				first = middle + 1;
				count -= step + 1;
			}
			else
			{
				count = step;
			}
		}

		int InterpNode = first;
		const float Diff = Keys[InterpNode].Time - Keys[InterpNode - 1].Time;

		if (Diff > 0.f && Keys[InterpNode - 1].InterpMode != RCIM_Constant)
		{
			const float Alpha = (InTime - Keys[InterpNode - 1].Time) / Diff;
			const float P0 = Keys[InterpNode - 1].Value;
			const float P3 = Keys[InterpNode].Value;

			if (Keys[InterpNode - 1].InterpMode == RCIM_Linear)
			{
				InterpVal = Lerp(P0, P3, Alpha);
			}
			else
			{
				const float OneThird = 1.0f / 3.0f;
				const float P1 = P0 + (Keys[InterpNode - 1].LeaveTangent * Diff * OneThird);
				const float P2 = P3 - (Keys[InterpNode].ArriveTangent * Diff * OneThird);

				InterpVal = BezierInterp(P0, P1, P2, P3, Alpha);
			}
		}
		else
		{
			InterpVal = Keys[InterpNode - 1].Value;
		}
	}
	else
	{
		if (RichCurve.PostInfinityExtrap == RCCE_Linear)
		{
			float DT = Keys[NumKeys - 2].Time - Keys[NumKeys - 1].Time;

			if (IsNearlyZero(DT))
			{
				InterpVal = Keys[NumKeys - 1].Value;
			}
			else
			{
				float DV = Keys[NumKeys - 2].Value - Keys[NumKeys - 1].Value;
				float Slope = DV / DT;

				InterpVal = Slope * (InTime - Keys[NumKeys - 1].Time) + Keys[NumKeys - 1].Value;
			}
		}
		else
		{
			// Otherwise if constant or in a cycle or oscillate, always use the last key value
			InterpVal = Keys[NumKeys - 1].Value;
		}
	}
	return InterpVal + CycleValueOffset;
}
bool PubgData::InsideCircle(int xc, int yc, int r, int x, int y)
{
	int dx = xc - x;
	int dy = yc - y;
	return dx * dx + dy * dy <= r * r;
}
void SimulateWeaponTrajectory(FVector Direction, float Distance, float TrajectoryGravityZ,
	float BallisticDragScale, float BallisticDropScale,
	float BDS, float SimulationSubstepTime, float VDragCoefficient,
	FRichCurve RichCurve, int KeysNum, std::vector<FRichCurveKey> Keys,
	float& BulletDrop, float& TravelTime)
{
	float TravelDistance = 0.0f;
	float CurrentDrop = 0.0f;
	BulletDrop = 0.0f;
	TravelTime = 0.0f;

	Direction.Normalize();
	Direction = Direction * 100.0f;

	while (1)
	{
		float BulletSpeed = Eval(TravelDistance * BDS * BallisticDragScale, 0.0, RichCurve, KeysNum, Keys);

		FVector Velocity = Direction * BulletSpeed;
		Velocity.Z += CurrentDrop;

		FVector Acceleration = Velocity * SimulationSubstepTime;
		float AccelerationLen = Acceleration.Length() / 100.0f;
		if (TravelDistance + AccelerationLen > Distance)
		{
			float RemainDistance = Distance - TravelDistance;
			float AccelerationSpeed = AccelerationLen / SimulationSubstepTime;
			float RemainTime = RemainDistance / AccelerationSpeed;

			TravelTime += RemainTime;
			BulletDrop += RemainTime * CurrentDrop;
			break;
		}
		TravelDistance += AccelerationLen;
		TravelTime += SimulationSubstepTime;
		BulletDrop += SimulationSubstepTime * CurrentDrop;
		CurrentDrop += SimulationSubstepTime * TrajectoryGravityZ * 100 * VDragCoefficient * BallisticDropScale;
	}
}

std::pair<float, float> PubgData::GetBulletDropAndTravelTime(const FVector& GunLocation, const FRotator& GunRotation, const FVector& TargetPos,
	float ZeroingDistance, float BulletDropAdd, float InitialSpeed, float TrajectoryGravityZ, float BallisticDragScale,
	float BallisticDropScale, float BDS, float SimulationSubstepTime, float VDragCoefficient, FRichCurve RichCurve, int KeysNum, std::vector<FRichCurveKey> Keys)
{
	const float ZDistanceToTarget = TargetPos.Z - GunLocation.Z;
	const float DistanceToTarget = GunLocation.Distance(TargetPos) / 100.0f;
	float TravelTime = DistanceToTarget / InitialSpeed;
	float BulletDrop = 0.5f * TrajectoryGravityZ * TravelTime * TravelTime * 100.0f;

	float TravelTimeZero = ZeroingDistance / InitialSpeed;
	float BulletDropZero = 0.5f * TrajectoryGravityZ * TravelTimeZero * TravelTimeZero * 100.0f;

	SimulateWeaponTrajectory(GunRotation.GetUnitVector(), DistanceToTarget, TrajectoryGravityZ,
		BallisticDragScale, BallisticDropScale,
		BDS, SimulationSubstepTime,
		VDragCoefficient,
		RichCurve, KeysNum, Keys, BulletDrop, TravelTime);


	SimulateWeaponTrajectory(FVector(1.0f, 0.0f, 0.0f), ZeroingDistance, TrajectoryGravityZ,
		BallisticDragScale, BallisticDropScale, BDS, SimulationSubstepTime, VDragCoefficient,
		RichCurve, KeysNum, Keys, TravelTimeZero, BulletDropZero);


	BulletDrop = fabsf(BulletDrop) - fabsf(BulletDropAdd);
	if (BulletDrop < 0.0f)
		BulletDrop = 0.0f;
	BulletDropZero = fabsf(BulletDropZero) + fabsf(BulletDropAdd);

	const float TargetPitch = asinf((ZDistanceToTarget + BulletDrop) / 100.0f / DistanceToTarget);
	const float ZeroPitch = IsNearlyZero(ZeroingDistance) ? 0.0f : atan2f(BulletDropZero / 100.0f, ZeroingDistance);
	const float FinalPitch = TargetPitch - ZeroPitch;
	const float AdditiveZ = DistanceToTarget * sinf(FinalPitch) * 100.0f - ZDistanceToTarget;

	return std::pair(AdditiveZ, TravelTime);
}
int AimBot_API(int X, int Y) {
	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.dx = (LONG)X;
	input.mi.dy = (LONG)Y;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	input.mi.time = 0;
	return SpoofCall<int>(SendInput, 1, &input, sizeof(INPUT));
}
void PubgData::PredictPos(ULONG64 ACharacter, FVector AimPos) {

	auto AMesh = GetMesh(ACharacter);
	if (ValidPtr(AMesh))return;
	FVector neck, spine;
	if (!GetBoneMatrix(AMesh, &neck, neck_01) || !GetBoneMatrix(AMesh, &spine, spine_02))return;
	FVector2D W2SCheck;
	auto AimAtPos = AimPos;
	if (WorldToScreen(AimAtPos, W2SCheck))
	{
		//printf("1\n"e);
		auto TslWeapon = GetTslWeapon(Game->MyPlayerAddress);
		if (!ValidPtr(TslWeapon))
		{
			//printf("2\n"e);

			DWORD64 WeaponData = Read<uint64_t>(TslWeapon + offset_WeaponTrajectoryData);
			if (ValidPtr(WeaponData))return;
			FWeaponTrajectoryConfig TrajectoryConfig = Read<FWeaponTrajectoryConfig>(WeaponData + offset_TrajectoryConfig);
			//printf("TrajectoryConfig:%p\n"e, TrajectoryConfig);
			FRichCurve RichCurve = Read<FRichCurve>(TrajectoryConfig.BallisticCurve + offset_FloatCurves + offset_Keys - 8);
			std::vector<FRichCurveKey> Keys;
			//Reading keys (I don't know why but I can't read TArray from UE4)
			DWORD64 KeysArray = Read<ULONG64>(TrajectoryConfig.BallisticCurve + offset_FloatCurves + offset_Keys);
			if (ValidPtr(KeysArray))return;
			auto KeysArrayCount = Read<ULONG32>(TrajectoryConfig.BallisticCurve + offset_FloatCurves + offset_Keys + 8);
			for (auto i = 0; i < KeysArrayCount; i++)
			{
				FRichCurveKey RichCurveKey = Read<FRichCurveKey>(KeysArray + (0x1C * i));
				Keys.push_back(RichCurveKey);
			}
		//printf("3\n"e);
			FVector velocity{};
			velocity = GetVihecleSpeed(ACharacter);
			if (velocity.X == 0.f && velocity.Y == 0.f && velocity.Z == 0.f) {
				uint64_t ActorRootcomp = XeDecryption(Read<ULONG64>(ACharacter + offset_RootComponent));
				velocity = Read<FVector>(ActorRootcomp + offset_ComponentVelocity);
			}

			ULONG64	VehicleRiderComponent = Read<ULONG64>(ACharacter + offset_VehicleRiderComponent);
			if (ValidPtr(VehicleRiderComponent))return;
			int Seatindex = Read<int>(VehicleRiderComponent + offset_SeatIndex);
			//printf("Seatindex:%d\n"e, Seatindex);
			if (Seatindex != -1)
			{
				AimAtPos = neck;
			}
			FVector local_location = GetPos(Game->MyPlayerAddress);
			float Distance = (AimAtPos - local_location).Length() / 100.f;


			float BulletDrop = 0;
			float TravelTime = 0;
			float BallisticDragScale = 1;
			float BallisticDropScale = 1;
			float TrajectoryGravityZ = Read<float>(TslWeapon + offset_TrajectoryGravityZ);
			//printf("TrajectoryGravityZ:%p\n"e, TrajectoryGravityZ);
			auto FiringAttachPoint = Read<FName>(TslWeapon + offset_FiringAttachPoint);//CartridgeChamber
			if (FiringAttachPoint == FName(0, 0))return;
			auto ScopingAttachPoint = Read<FName>(TslWeapon + offset_ScopingAttachPoint);//ScopeAimCamera
			if (ScopingAttachPoint == FName(0, 0))return;
			auto WeaponMesh = XeDecryption(Read<ULONG64>(TslWeapon + offset_Mesh3P));
			if (ValidPtr(WeaponMesh))return;
			auto WeaponComponentToWorld = Read<FTransform>(WeaponMesh + offset_ComponentToWorld);
			//printf("WeaponComponentToWorld:%p\n"e, WeaponComponentToWorld);

		

			FTransform GunTransform = GetSocketTransform(WeaponMesh, RTS_World, FiringAttachPoint);
		//	printf("GunTransform:%p\n"e, GunTransform);

			auto GunLocation = GunTransform.Translation;
			FRotator GunRotation = GunTransform.Rotation;

			auto BulletDropAdd = GetScopingAttachPointRelativeZ(TslWeapon, ScopingAttachPoint) -
				GunTransform.GetRelativeTransform(WeaponComponentToWorld).Translation.Z;

		//	printf("BulletDropAdd:%p\n"e, BulletDropAdd);

			auto LocalMesh = GetMesh(Game->MyPlayerAddress);
			printf("LocalMesh:%p\n"e, LocalMesh);

			if (ValidPtr(LocalMesh))return;
			auto LocalComponentToWorld = Read<FTransform>(LocalMesh + offset_ComponentToWorld);
			auto AnimScriptInstance = Read<ULONG64>(LocalMesh + offset_AnimScriptInstance);
			if (ValidPtr(AnimScriptInstance))return;
			auto IsScoping = Read<bool>(AnimScriptInstance + offset_bIsScoping_CP);
		//	printf("IsScoping:%p\n"e, IsScoping);
			auto LeanRightAlpha_CP = Read<float>(AnimScriptInstance + offset_LeanRightAlpha_CP);
			auto LeanLeftAlpha_CP = Read<float>(AnimScriptInstance + offset_LeanLeftAlpha_CP);
			auto Recoil = Read<FRotator>(AnimScriptInstance + offset_RecoilADSRotation_CP);
			auto ControlRotation_CP = Read<FRotator>(AnimScriptInstance + offset_ControlRotation_CP);
			Recoil.Yaw += (LeanRightAlpha_CP - LeanLeftAlpha_CP) * Recoil.Pitch / 3.0f;

			auto ControlRotation = ControlRotation_CP + Recoil;
			auto AimLocation = GunLocation.Length() > 0.0f ? GunLocation : LocalComponentToWorld.Translation;
			auto AimRotation = IsScoping ? GunRotation : ControlRotation;
			auto ZeroingDistance = GetZeroingDistance(TslWeapon, IsScoping);
			auto Result = GetBulletDropAndTravelTime(
				AimLocation,
				AimRotation,
				AimAtPos,
				ZeroingDistance,
				BulletDropAdd,
				TrajectoryConfig.InitialSpeed,
				TrajectoryGravityZ,
				BallisticDragScale,
				BallisticDropScale,
				TrajectoryConfig.BDS,
				TrajectoryConfig.SimulationSubstepTime,
				TrajectoryConfig.VDragCoefficient,
				RichCurve,
				Keys.size(),
				Keys);
			BulletDrop = Result.first;
			TravelTime = Result.second;
	//	printf("AimAtPos.X:%f || AimAtPos.Y:%f || AimAtPos.Z:%f "e, AimAtPos.X, AimAtPos.Y, AimAtPos.Z);
			FVector PredictedPos = FVector(AimAtPos.X, AimAtPos.Y, AimAtPos.Z + Abs(BulletDrop)) + velocity * (TravelTime / 1.f);

			FVector TargetScreenPos = WorldToScreen(AimAtPos);
			FVector AimScreenPos = WorldToScreen(PredictedPos);
			const float LineLen = std::clamp(AimScreenPos.Y - WorldToScreen({ AimAtPos.X, AimAtPos.Y, AimAtPos.Z + 10.0f }).Y, 4.0f, 8.0f);
			UCanvas::DrawLine(TargetScreenPos.X, TargetScreenPos.Y, AimScreenPos.X, AimScreenPos.Y, 2.0f, Colo->红色);
			UCanvas::DrawX({ AimScreenPos.X,AimScreenPos.Y }, LineLen, Colo->红色, 2.0f);
			if (PredictedPos != FVector(0, 0, 0))
			{
				FVector AimBots = FVector(0.f, 0.f, 0.f);
				if (WorldToScreen_Aim(PredictedPos, &AimBots))
				{
			//	printf("执行自瞄\n"e);

				
					
					AimBots.X = (AimBots.X - Game->ScreenCenter.X) * 0.01f * off->AimSpeedX;
					AimBots.Y = (AimBots.Y - Game->ScreenCenter.Y) * 0.01f * off->AimSpeedY;


					SpoofCall<int>(AimBot_API, (int)AimBots.X, (int)AimBots.Y);
				}
			}
		}
	}			
}

bool bWorldMap = false;
bool bRadarExtended = false;
float WorldMapZoomFactor = 0;
FVector2D WorldMapPosition = FVector2D();
FVector2D DefaultSize = { 1080.0f, 1080.0f };
float PubgData::GetZoomFactor(ULONG64 MapGrid)  {
	ULONG64 Slot = Read<ULONG64>(MapGrid + offset_Slot);
	if (ValidPtr(Slot))
		return 0.0f;
	auto Offsets = Read<FMargin>(Slot + offset_LayoutData + offset_Offsets);
	const FVector2D CurrentSize = { Offsets.Right, Offsets.Bottom };
	return CurrentSize.X / DefaultSize.X;
}
FVector2D PubgData::GetPosition(ULONG64 MapGrid) {
	ULONG64 Slot = Read<ULONG64>(MapGrid + offset_Slot);
	if (ValidPtr(Slot))
		return FVector2D();
	auto Offsets = Read<FMargin>(Slot + offset_LayoutData + offset_Offsets);
	auto Alignment = Read<FVector2D>(Slot + offset_LayoutData + offset_Offsets + offset_Alignment);
	const FVector2D CurrentPos = {
		Offsets.Right * (Alignment.X - 0.5f) - Offsets.Left,
		Offsets.Bottom * (Alignment.Y - 0.5f) - Offsets.Top
	};	
	const float ZoomFactor = GetZoomFactor(MapGrid);
	return { CurrentPos.X / DefaultSize.X / ZoomFactor * 2.0f, CurrentPos.Y / DefaultSize.Y / ZoomFactor * 2.0f };
}
bool PubgData::IsVisible(ULONG64 MapWidget,ULONG64 MapGrid) {
	if (IsNearlyZero(GetZoomFactor(MapGrid)))
		return false;
	return Read<ESlateVisibility>(MapWidget + offset_Visibility) == ESlateVisibility::SelfHitTestInvisible;
}

void PubgData::EnumAllWidget(ULONG64 TslBaseHUD) {
	auto WidgetStateMap = Read<TMap<FString, FTslWidgetState>>(TslBaseHUD + offset_WidgetStateMap);
	for (auto& Elem : WidgetStateMap.GetVector()) {
		auto& Key = Elem.Value.Key;
		auto& Value = Elem.Value.Value;
		if (ValidPtr(Value.Widget))continue;
		auto WidgetPtrName = PubgData::GetName(PubgData::GetNameIndex(Value.Widget));
		if (!WidgetPtrName.empty() && WidgetPtrName != "None")
		{
			switch (PubgData::GetNameHash(PubgData::GetNameIndex(Value.Widget))) {
			case "NewWorldMapWidget_BP_C"h: 
			{
				auto MapGrid = Read<ULONG64>(Value.Widget + offset_TrainingMapGrid + 0x30);
				if (!MapGrid || 0xFFFFFFFF == MapGrid)break;
				bWorldMap = PubgData::IsVisible(Value.Widget, MapGrid);
				if (!bWorldMap)
					break;

				WorldMapZoomFactor = PubgData::GetZoomFactor(MapGrid);
				WorldMapPosition = PubgData::GetPosition(MapGrid);
				break;
			}
			case "UI_TrainingWorldMapWidget_C"h:
			{
				auto MapGrid = Read<ULONG64>(Value.Widget + offset_TrainingMapGrid);
				if (!MapGrid || 0xFFFFFFFF == MapGrid)break;
				bWorldMap = PubgData::IsVisible(Value.Widget, MapGrid);
				if (!bWorldMap)
					break;

				WorldMapZoomFactor = PubgData::GetZoomFactor(MapGrid);
				WorldMapPosition = PubgData::GetPosition(MapGrid);
				break;
			}
			case "MinimapOriginalType_C"h: {
				bRadarExtended = Read<int>(Value.Widget + offset_SelectMinimapSizeIndex) > 0;
				break;
			}
			}
		}
	}
}

FVector2D PubgData::DrawMap(FVector ActorLocation, float MapSize) {
	int X = Read<int>(Game->UWorld + offset_WorldToMap);
	int Y = Read<int>(Game->UWorld + offset_WorldToMap + 4);
	FVector OriginLocation = FVector(X, Y, 0);

	const float MapSizeFactored = MapSize / WorldMapZoomFactor;
	const FVector WorldLocation = ActorLocation + OriginLocation;
	const FVector WorldCenterLocation = { MapSize * (1.0f + WorldMapPosition.X), MapSize * (1.0f + WorldMapPosition.Y), 0.0f };
	const FVector RadarPos = WorldLocation - WorldCenterLocation;
	const FVector2D RadarScreenCenterPos = Game->ScreenCenter;
	const FVector2D RadarScreenPos = RadarScreenCenterPos + FVector2D{
		RadarPos.X / MapSizeFactored * Game->ScreenCenter.Y,
		RadarPos.Y / MapSizeFactored * Game->ScreenCenter.Y
	};
	return RadarScreenPos;
}
