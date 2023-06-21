#pragma once
#include "common/util.h"

struct tZeroingInfo {
	float BaseIron = 100.0f;
	float BaseScope = 100.0f;
	float Increment = 100.0f;
	float BaseHolo = BaseScope;
};

enum class tWeaponType {
	None,
	Throw,
	Melee,
	AR,
	SR,
	SG,
	LMG,
	SMG,
	BOW,
	PISTOL,
	DMR
};

struct tWeaponInfo {
	fixstr::basic_fixed_string<char, 0x100> WeaponName;
	tWeaponType WeaponType = tWeaponType::None;
	tZeroingInfo ZeroingInfo;
};

static tWeaponInfo GetWeaponInfo(unsigned Hash) {
	constexpr static tZeroingInfo ZeroingSG = { 50.0f, 100.0f, 0.0f };
	constexpr static tZeroingInfo ZeroingCBow = { 25.0f, 25.0f, 0.0f };
	constexpr static tZeroingInfo ZeroingVSS = { 100.0f, 100.0f, 25.0f };
	constexpr static tZeroingInfo ZeroingPistol = { 50.0f, 50.0f, 0.0f, 100.0f };
	constexpr static tZeroingInfo ZeroingDeagle = { 50.0f, 100.0f, 0.0f, 100.0f };
	constexpr static tZeroingInfo ZeroingSkorpion = { 100.0f, 50.0f, 0.0, 100.0f };
	
	switch (Hash) {
		//Throw
		HASH_CASE("WeapFlashBang_C"h, { "���ⵯ"e, tWeaponType::Throw });
		HASH_CASE("WeapGrenade_C"h, { "����"e, tWeaponType::Throw });
		HASH_CASE("WeapStickyGrenade_C"h, { "ճ��ը��"e, tWeaponType::Throw });
		HASH_CASE("WeapMolotov_C"h, { "ȼ��ƿ"e, tWeaponType::Throw });
		HASH_CASE("WeapSmokeBomb_C"h, { "����"e, tWeaponType::Throw });
		HASH_CASE("WeapC4_C"h, { "C4"e, tWeaponType::Throw });
		HASH_CASE("WeapDecoyGrenade_C"h, { "�ն�����"e, tWeaponType::Throw });
		HASH_CASE("WeapBluezoneGrenade_C"h, { "��Ȧ����"e, tWeaponType::Throw });
		HASH_CASE("WeapSpikeTrap_C"h, { "�������"e, tWeaponType::Throw });

		//Melee
		HASH_CASE("WeapCowbar_C"h, { "�˹�"e, tWeaponType::Melee });
		HASH_CASE("WeapPan_C"h, { "ƽ�׹�"e, tWeaponType::Melee });
		HASH_CASE("WeapSickle_C"h, { "����"e, tWeaponType::Melee });
		HASH_CASE("WeapMachete_C"h, { "����"e, tWeaponType::Melee });
		HASH_CASE("WeapCowbarProjectile_C"h, { "�˹�"e, tWeaponType::Throw });
		HASH_CASE("WeapMacheteProjectile_C"h, { "Machete"e, tWeaponType::Throw });
		HASH_CASE("WeapPanProjectile_C"h, { "ƽ�׹�"e, tWeaponType::Throw });
		HASH_CASE("WeapSickleProjectile_C"h, { "����"e, tWeaponType::Throw });

		//AR
		HASH_CASE("WeapLunchmeatsAK47_C"h, { "AKM"e, tWeaponType::AR });
		HASH_CASE("WeapAK47_C"h, { "AK,"e, tWeaponType::AR });
		HASH_CASE("WeapGroza_C"h, { "����"e, tWeaponType::AR });
		HASH_CASE("WeapDuncansHK416_C"h, { "M416"e, tWeaponType::AR });
		HASH_CASE("WeapHK416_C"h, { "M416"e, tWeaponType::AR });
		HASH_CASE("WeapM16A4_C"h, { "M16A4"e, tWeaponType::AR });
		HASH_CASE("WeapSCAR-L_C"h, { "SCAR-L"e, tWeaponType::AR });
		HASH_CASE("WeapACE32_C"h, { "ACE"e, tWeaponType::AR });
		HASH_CASE("WeapAUG_C"h, { "AUG"e, tWeaponType::AR });
		HASH_CASE("WeapBerylM762_C"h, { "BerylM762"e, tWeaponType::AR });
		HASH_CASE("WeapG36C_C"h, { "G36C"e, tWeaponType::AR });
		HASH_CASE("WeapQBZ95_C"h, { "QBZ95"e, tWeaponType::AR });
		HASH_CASE("WeapK2_C"h, { "K2"e, tWeaponType::AR });
		HASH_CASE("WeapMk47Mutant_C"h, { "Mk47"e, tWeaponType::AR });
		HASH_CASE("Weapon_OriginS12_C"h, { "O12"e, tWeaponType::AR });

		//SR
		HASH_CASE("WeapAWM_C"h, { "AWM"e, tWeaponType::SR });
		HASH_CASE("WeapJuliesM24_C"h, { "M24"e, tWeaponType::SR });
		HASH_CASE("WeapM24_C"h, { "M24"e, tWeaponType::SR });
		HASH_CASE("WeapJuliesKar98k_C"h, { "Kar98k"e, tWeaponType::SR });
		HASH_CASE("WeapKar98k_C"h, { "Kar98k"e, tWeaponType::SR });
		HASH_CASE("WeapWin94_C"h, { "Win94"e, tWeaponType::SR });
		HASH_CASE("WeapL6_C"h, { "Lynx"e, tWeaponType::SR });
		HASH_CASE("WeapMosinNagant_C"h, { "Ī������"e, tWeaponType::SR });
		HASH_CASE("WeapCrossbow_1_C"h, { "��"e, tWeaponType::SR, ZeroingCBow });

		//SG
		HASH_CASE("WeapBerreta686_C"h, { "S686"e, tWeaponType::SG, ZeroingSG });
		HASH_CASE("WeapSaiga12_C"h, { "S12K"e, tWeaponType::SG, ZeroingSG });
		HASH_CASE("WeapWinchester_C"h, { "S1897"e, tWeaponType::SG, ZeroingSG });
		HASH_CASE("WeapDP12_C"h, { "DBS"e, tWeaponType::SG, ZeroingSG });
		HASH_CASE("WeapSawnoff_C"h, { "�����ǹ"e, tWeaponType::SG, ZeroingSG });

		//PISTOL
		HASH_CASE("WeapG18_C"h, { "P18C"e, tWeaponType::PISTOL, ZeroingPistol });
		HASH_CASE("WeapM1911_C"h, { "P1911"e, tWeaponType::PISTOL, ZeroingPistol });
		HASH_CASE("WeapM9_C"h, { "P92"e, tWeaponType::PISTOL, ZeroingPistol });
		HASH_CASE("WeapNagantM1895_C"h, { "R1895"e, tWeaponType::PISTOL, ZeroingPistol });
		HASH_CASE("WeapRhino_C"h, { "R45"e, tWeaponType::PISTOL, ZeroingPistol });
		HASH_CASE("WeapDesertEagle_C"h, { "Deagle"e, tWeaponType::PISTOL, ZeroingDeagle });
		HASH_CASE("Weapvz61Skorpion_C"h, { "Skorpion"e, tWeaponType::PISTOL, ZeroingSkorpion });

		//LMG
		HASH_CASE("WeapM249_C"h, {"M249"e, tWeaponType::LMG });
		HASH_CASE("WeapMG3_C"h, { "MG3"e, tWeaponType::LMG });
		HASH_CASE("WeapDP28_C"h, { "DP28"e, tWeaponType::LMG });

		//DMR
		HASH_CASE("WeapMini14_C"h, { "Mini14"e, tWeaponType::DMR });
		HASH_CASE("WeapMk14_C"h, { "Mk14"e, tWeaponType::DMR });
		HASH_CASE("WeapSKS_C"h, { "SKS"e, tWeaponType::DMR });
		HASH_CASE("WeapFNFal_C"h, { "SLR"e, tWeaponType::DMR });
		HASH_CASE("WeapMadsFNFal_C"h, { "SLR"e, tWeaponType::DMR });
		HASH_CASE("WeapMadsQBU88_C"h, { "QBU"e, tWeaponType::DMR });
		HASH_CASE("WeapQBU88_C"h, { "QBU"e, tWeaponType::DMR });
		HASH_CASE("WeapMk12_C"h, { "Mk12"e, tWeaponType::DMR });
		HASH_CASE("WeapVSS_C"h, { "VSS"e, tWeaponType::DMR, ZeroingVSS });

		//SMG
		HASH_CASE("WeapThompson_C"h, { "��ķѷ"e, tWeaponType::SMG });
		HASH_CASE("WeapUMP_C"h, { "UMP"e, tWeaponType::SMG });
		HASH_CASE("WeapUZI_C"h, { "UZI"e, tWeaponType::SMG });
		HASH_CASE("WeapUziPro_C"h, { "UZI"e, tWeaponType::SMG });
		HASH_CASE("WeapVector_C"h, { "Vector"e, tWeaponType::SMG });
		HASH_CASE("WeapBizonPP19_C"h, { "ҰţPP19"e, tWeaponType::SMG });
		HASH_CASE("WeapMP5K_C"h, { "MP5K"e, tWeaponType::SMG });
		HASH_CASE("WeapP90_C"h, { "P90"e, tWeaponType::SMG });

		//Special
		HASH_CASE("WeapMortar_C"h, { "Mortar"e });
		HASH_CASE("WeapFlareGun_C"h, { "�ź�ǹ"e });
		HASH_CASE("WeapPanzerFaust100M1_C"h, { "���Ͳ"e });
		HASH_CASE("WeapJerryCan_C"h, { "����Ͱ"e });
		HASH_CASE("WeapDrone_C"h, { "���˻�"e });
		HASH_CASE("WeapTraumaBag_C"h, { "ҽ���׼�"e });
		HASH_CASE("WeapSpotterScope_C"h, { "��Զ��"e });
		HASH_CASE("WeapTacPack_C"h, { "ս������"e });
		HASH_CASE("WeapM79_C"h, { "M79"e });

		HASH_DEFAULT({});
	}
}
