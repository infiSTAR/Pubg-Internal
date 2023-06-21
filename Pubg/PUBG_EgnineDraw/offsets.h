inline ULONG64 offset_ClassXor1 = 0x84001E99BC1C13C9;
inline ULONG64 offset_ClassXor2 = 0x7A98DC18AE987C17;

inline ULONG64 offset_OuterXor1 = 0xEA45782AB9AF8C57;
inline ULONG64 offset_OuterXor2 = 0xDBF2148ABB9D77D3;

enum GameOffset
{

	offset_XeDecryption = 0x7D6F228,
	offset_UWorld = 0x93B2670,
	offset_GName = 0x9597F88,
	offset_GObjects = 0x09371020,

	offset_SpoolBack = 0xC25353,


	offset_LineTraceSingle = 0x5DF069C,//漏打Call

	offset_IsInLoabby = 0x91AFA38,//判断大厅

	offset_DrawLineCall = 0x5D2B7F0,//TslGame.exe+5C6A618 - E8 5FDAF7FF           - call TslGame.exe+5BE807C
	offset_DrawRectCall = 0x5F9EAE0,//TslGame.exe+5C6AA77 - E8 C4D51E00           - call TslGame.exe+5E58040
	offset_DrawCall = 0x8F53F8,//TslGame.exe+5C6AA98 - E8 6B98C7FA           - call TslGame.exe+8E4308
	offset_K2_DrawText = 0x5FA8050,
	offset_Font_Roboto = 0x95A1918,
	//TslGame.exe+9EDF4B - 48 8B 15 B6D59F08     - mov rdx,[TslGame.exe+93EB508] { (1EDD2775C40) }
	//TslGame.exe+9EEABF - 48 8B 15 32CA9F08     - mov rdx,[TslGame.exe+93EB4F8] { (1EDD2775C40) }
	offset_DebugCanvas = 0x95A4E98,
	offset_GetUCavcsFn = 0x9122A8,
	offset_ReturnAddress = 0x3DB82A, //TslGame.exe + 4D3931 - 38 1D 0770BB08 - cmp[TslGame.exe + 908A93E], bl{ (1) }
	offset_pUnknownHook = 0x9359938,//TslGame.AK::WriteBytesMem::Bytes+FA3A - 48 8B 05 37EDC708     - mov rax,[TslGame.exe+91A3B88] { (1EDC75BE080) }
	offset_pUnknownTick = 0x91790F4,//TslGame.exe+4C591A - 44 8B 35 4308B008     - mov r14d,[TslGame.exe+8FC6164] { (9570) }
	offset_NewHook = 0x93C5A00,
	offset_NewHookTick = 0x4CF251,

	offset_K2_DrawTexture = 0x5FA8194,
	offset_ImportedSize = 0xcc,//
	offset_GetIconTexture = 0x20,//FSprayDecalDBDataRow

	offset_ClassPrivate = 0x10,
	offset_ClassOne = 0x20,//ROR
	offset_ClassTwo = 0x19,//
	offset_ClassIsROR = 1,

	offset_OuterPrivate = 0x18,
	offset_OuterOne = 0xD,//ROL
	offset_OuterTwo = 0x20,
	offset_OuterIsROR = 0,

	offset_NamePrivate = 0x24,
	offset_NameIndexXor1 = 0xA42ADA38,
	offset_NameIndexOne = 0x4,//ROR
	offset_NameIndexTwo = 0x10,
	offset_NameIndexXor2 = 0x127EBCA2,
	offset_NameIsROR = 1,//ROL=0 ROR=1

	offset_CurrentLevel = 0x968,
	offset_Actor = 0x98,
	offset_TslGameInstance = 0x870,
	offset_TslLocalPlayer = 0xB8,
	offset_PlayerController = 0x38,

	offset_AcknowledgedPawn = 0x498,
	offset_PlayerCameraManager = 0x4B8,


	offset_StaticMesh = 0xAF0,//Bone

	offset_SkeletalMesh = 0xae0,// USkeletalMesh* 

	offset_ComponentToWorld = 0x210,//BoneArry 
	offset_AbsoluteLocation = 0x220,//Position 

	offset_ChunkSize = 0x3E70,


	offset_DroppedItem = 0x448,
	offset_DroppedItemGroup = 0x318,
	offset_DroppedItemGroup_UItem = 0x758,
	offset_Items = 0x560,
	offset_ItemInformationComponent = 0xB0,
	offset_ItemID = 0x248,




	offset_Visibility = 0xa9, //enum class ESlateVisibility      Visibility;   //0xa9
	offset_Slot = 0x38,
	offset_Keys = 0x60,// FRichCurveKey

	offset_RootComponent = 0x2C0,


	offset_PlayerState = 0x440,
	offset_PlayerStatistics = 0x6D8,//没有//杀敌

	offset_SurvivalLevel = 0x0,//没有
	offset_Alignment = 0x20,
	offset_Offsets = 0x0,

	offset_CameraLocation = 0x10A0,
	offset_CameraRotation = 0x108C,
	offset_CameraFOV = 0x109C,


	offset_bVested = 0x11c,//bool     bVested;    //0x124

	offset_ComponentVelocity = 0x258,

	offset_AttachParent = 0x310,//USceneComponent*                             AttachParent;    
	offset_LastRenderTimeOnScreen = 0x780,//无
	offset_LastSubmitTime = 0x778,//无


	offset_WorldToMap = 0x19C,//世界转小地图
	offset_TrainingMapGrid = 0x6b0,

	offset_SelectMinimapSizeIndex = 0x5c0,

	offset_WidgetStateMap = 0x510,

	offset_Mesh = 0x528,
	offset_CharacterState = 0x2280,
	offset_LastTeamNum = 0x1150,//无
	offset_Team = 0x1148,
	offset_CharacterName = 0x2220,

	offset_AimOffsets = 0x1760,//被瞄偏移

	offset_GroggyHealthMax = 0x1458,//无
	offset_SpectatedCount = 0x221C,//Audience 
	offset_GroggyHealth = 0x1534,

	offset_HealthMax = 0x88c,//ATslCharacterBase
	offset_Health = 0x888,

	offset_WeaponProcessor = 0x8a0,
	offset_EquippedWeapons = 0x208,
	offset_CurrentWeaponIndex = 0x309,

	offset_TrajectoryConfig = 0x108,
	offset_WeaponTrajectoryData = 0x1008,
	offset_TrajectoryGravityZ = 0xfec,
	offset_bIsScoping_CP = 0xcf6,

	offset_Character = 0x430,//EncryptedObjectProperty                             Character;  
	offset_Pawn = 0x438, //EncryptedObjectProperty                             Pawn;     


	offset_FiringAttachPoint = 0x860,
	offset_WeaponTag = 0x818,
	offset_AttachedItems = 0x808,
	offset_Mesh3P = 0x7c0,
	offset_WeaponIcon = 0x440,//无
	offset_SpectatorPawn = 0x748, //APlayerController
	offset_PlayerInput = 0x530, //无



	offset_MyHUD = 0x4b0,

	offset_PubgIdData = 0xcd8,//无

	offset_DamageDealtOnEnemy = 0x620,
	offset_SquadMemberIndex = 0x714,

	offset_DefaultFOV = 0xc3c,
	offset_AttachedStaticComponentMap = 0x11d8,
	offset_bLoackLoadedAmmo = 0xe84,
	offset_ScopingAttachPoint = 0xc20,
	offset_CurrentZeroLevel = 0xa34,
	offset_CurrentAmmoData = 0xa30,
	offset_CurrentState = 0xa2a,


	offset_VehicleRiderComponent = 0x1cd8,
	offset_VehicleFuelMax = 0x2dc,
	offset_VehicleFuel = 0x2d8,

	offset_VehicleHealthMax = 0x2d4,
	offset_VehicleHealth = 0x2d0,

	offset_VehicleMesh = 0x0450,
	offset_WheeledVehicleCommonComponent = 0xB70,
	offset_FloatingVehicleCommonComponent = 0x4D8,

	offset_bLocalFPP_CP = 0xF28,//0xF28
	offset_LeanRightAlpha_CP = 0x0DE8,
	offset_LeanLeftAlpha_CP = 0x0DE4,


	offset_AnimScriptInstance = 0xC90,
	offset_RecoilADSRotation_CP = 0x9CC,
	offset_ControlRotation_CP = 0x774,

	offset_LastVehiclePawn = 0x260,
	offset_SeatIndex = 0x228,
	offset_ReplicatedMovement = 0x70,



	offset_LayoutData = 0x40,

	offset_StaticSockets = 0xc8,// UStaticMeshSocket*>            Sockets;  
	offset_SkeletalSockets = 0x2c8,//USkeletalMeshSocket*>          Sockets;   

	offset_FinalRefBoneInfo = 0x158,

	offset_Skeleton = 0x50,//struct USkeletalMesh : public UObject
	offset_SkeletonSockets = 0x198,//USkeletalMeshSocket




	offset_SizeX = 0x78,
	offset_SizeY = 0x7c,


	offset_FloatCurves = 0x38,

	//	USkeletalMeshSocket
	offset_SkeletalSocketName = 0x30,
	offset_SkeletalRelativeScale = 0x58,
	offset_SkeletalRelativeRotation = 0x4c,
	offset_SkeletalRelativeLocation = 0x40,

	offset_BoneName = 0x38,

	//	UStaticMeshSocket MeshSocket
	offset_StaticSocketName = 0x30,
	offset_StaticRelativeScale = 0x50,
	offset_StaticRelativeRotation = 0x44,
	offset_StaticRelativeLocation = 0x38,



	offset_SetActorEnableCollision = 0xAAAC30, //TslGame.exe+7034F8 - 4C 8B DC              - mov r11,rsp


	offset_BulletTable = 0xFE8,

	offset_子弹时间偏移 = 0x100,
	offset_子弹坐标偏移 = 0x104,
	offset_子弹数组偏移 = 0x108,

	offset_开车开枪 = 0x050,




};