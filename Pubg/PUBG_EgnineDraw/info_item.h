#pragma once
#include "common/util.h"

struct ItemInfo {
	std::string Name;
	int ItemPriority;
	int Type;
};

static ItemInfo GetItemInfo(unsigned Hash) {
	switch (Hash) {


		//Ammo
		HASH_CASE("Item_Ammo_Mortar_C"h, { "60mm"e, 4 ,16 });
		HASH_CASE("Item_Ammo_Bolt_C"h, { "Bolt"e, 4 ,16 });
		HASH_CASE("Item_Ammo_Flare_C"h, { "�źŵ�"e, 4 ,16 });
		HASH_CASE("Item_Ammo_57mm_C"h, { "5.7mm"e, 4 ,16 });
		HASH_CASE("Item_Ammo_300Magnum_C"h, { ".300�����"e, 4 ,16 });
		HASH_CASE("Item_Ammo_556mm_C"h, { "5.56mm"e, 3 ,16 });
		HASH_CASE("Item_Ammo_762mm_C"h, { "7.62mm"e, 3 ,16 });
		HASH_CASE("Item_Ammo_40mm_C"h, { "40mm"e, 3 ,16 });
		HASH_CASE("Item_Ammo_9mm_C"h, { "9mm"e, 2 ,16 });
		HASH_CASE("Item_Ammo_12Guage_C"h, { "12�ھ�"e, 2 ,16 });
		HASH_CASE("Item_Ammo_45ACP_C"h, { ".45"e, 2 ,16 });

		//Attach
		HASH_CASE("Item_Attach_Weapon_Lower_Foregrip_C"h, { "��ֱ�հ�"e, 3 ,1 });
		HASH_CASE("Item_Attach_Weapon_Lower_AngledForeGrip_C"h, { "�����հ�"e, 2 ,1 });
		HASH_CASE("Item_Attach_Weapon_Lower_HalfGrip_C"h, { "����հ�"e, 2 ,1 });
		HASH_CASE("Item_Attach_Weapon_Lower_LightweightForeGrip_C"h, { "�����հ�"e, 2 ,1 });
		HASH_CASE("Item_Attach_Weapon_Lower_ThumbGrip_C"h, { "Ĵָ�հ�"e, 2 ,1 });

		HASH_CASE("Item_Attach_Weapon_Magazine_ExtendedQuickDraw_Large_C"h, { "��ǹ�������ݵ���"e, 4 ,1 });
		HASH_CASE("Item_Attach_Weapon_Magazine_Extended_Large_C"h, { "��ǹ���ݵ���"e, 3 ,1 });

		HASH_CASE("Item_Attach_Weapon_Magazine_ExtendedQuickDraw_SniperRifle_C"h, { "�ѻ��������ݵ���"e, 4 ,1 });
		HASH_CASE("Item_Attach_Weapon_Magazine_Extended_SniperRifle_C"h, { "�ѻ����ݵ���"e, 3 ,1 });


		HASH_CASE("Item_Attach_Weapon_Muzzle_Compensator_Large_C"h, { "��ǹ������"e, 3 ,1 });


		HASH_CASE("Item_Attach_Weapon_Muzzle_Suppressor_SniperRifle_C"h, { "�ѻ�������"e, 4 ,1 });
		HASH_CASE("Item_Attach_Weapon_Muzzle_Suppressor_Large_C"h, { "��ǹ������"e, 4 ,1 });


		HASH_CASE("Item_Attach_Weapon_SideRail_DotSight_RMR_C"h, { "�����׼��"e, 4 ,1 });

		HASH_CASE("Item_Attach_Weapon_Stock_AR_Composite_C"h, { "ս��ǹ��"e, 3 ,1 });
		HASH_CASE("Item_Attach_Weapon_Stock_SniperRifle_CheekPad_C"h, { "������"e, 3 ,1 });
		HASH_CASE("Item_Attach_Weapon_Stock_SniperRifle_BulletLoops_C"h, { "�ӵ���"e, 2 ,1 });

		HASH_CASE("Item_Attach_Weapon_Upper_PM2_01_C"h, { "15����"e, 4 ,1 });
		HASH_CASE("Item_Attach_Weapon_Upper_CQBSS_C"h, { "8����"e, 4 ,1 });
		HASH_CASE("Item_Attach_Weapon_Upper_Scope6x_C"h, { "6����"e, 4 ,1 });
		HASH_CASE("Item_Attach_Weapon_Upper_ACOG_01_C"h, { "4����"e, 3 ,1 });
		HASH_CASE("Item_Attach_Weapon_Upper_Scope3x_C"h, { "3����"e, 3 ,1 });
		HASH_CASE("Item_Attach_Weapon_Upper_Aimpoint_C"h, { "2����"e, 3 ,1 });
		HASH_CASE("Item_Attach_Weapon_Upper_DotSight_01_C"h, { "���"e, 3 ,1 });
		HASH_CASE("Item_Attach_Weapon_Upper_Holosight_C"h, { "ȫϢ"e, 3 ,1 });

		HASH_CASE("Item_Back_BackupParachute_C"h, { "����ɡ"e, 3 ,1 });


		//Throw
		HASH_CASE("Item_Weapon_C4_C"h, { "C4"e, 4 ,2 });
		HASH_CASE("Item_Weapon_BluezoneGrenade_C"h, { "��Ȧ����"e, 3 ,2 });
		HASH_CASE("Item_Weapon_Grenade_C"h, { "����"e, 3 ,2 });
		HASH_CASE("Item_Weapon_Grenade_Warmode_C"h, { "����"e, 3 ,2 });
		HASH_CASE("Item_Weapon_FlashBang_C"h, { "���ⵯ"e, 3 ,2 });
		HASH_CASE("Item_Weapon_StickyGrenade_C"h, { "ճ��ը��"e, 3 ,2 });
		HASH_CASE("Item_Weapon_Molotov_C"h, { "ȼ��ƿ"e, 3 ,2 });
		HASH_CASE("Item_Weapon_SmokeBomb_C"h, { "����"e, 3 ,2 });
		HASH_CASE("Item_Weapon_SpikeTrap_C"h, { "�������"e, 3 ,2 });
		HASH_CASE("Item_Weapon_DecoyGrenade_C"h, { "�ն�����"e, 1 ,2 });

		HASH_CASE("Item_Weapon_Pan_C"h, { "ƽ�׹�"e, 3 ,1 });


		//AR
		HASH_CASE("Item_Weapon_Groza_C"h, { "����"e, 4 ,4 });
		HASH_CASE("Item_Weapon_BerylM762_C"h, { "BerylM762"e, 4 ,4 });
		HASH_CASE("Item_Weapon_ACE32_C"h, { "ACE32"e, 4 ,4 });
		HASH_CASE("Item_Weapon_HK416_C"h, { "M416"e, 4 ,4 });
		HASH_CASE("Item_Weapon_Duncans_M416_C"h, { "M416"e, 4 ,4 });
		HASH_CASE("Item_Weapon_AUG_C"h, { "AUG"e, 4 ,4 });
		HASH_CASE("Item_Weapon_AK47_C"h, { "AKM"e, 3 ,4 });
		HASH_CASE("Item_Weapon_Lunchmeats_AK47_C"h, { "AKM"e, 3 ,4 });
		HASH_CASE("Item_Weapon_SCAR-L_C"h, { "SCAR-L"e, 3 ,4 });
		HASH_CASE("Item_Weapon_G36C_C"h, { "G36C"e, 3 ,4 });
		HASH_CASE("Item_Weapon_QBZ95_C"h, { "QBZ95"e, 3 ,4 });
		HASH_CASE("Item_Weapon_K2_C"h, { "K2"e, 3 ,4 });
		HASH_CASE("Item_Weapon_Mk47Mutant_C"h, { "Mk47"e, 2 ,4 });
		HASH_CASE("Item_Weapon_M16A4_C"h, { "M16A4"e, 2 ,4 });
		HASH_CASE("Item_Weapon_OriginS12_C"h, { "O12"e, 4 ,4 });
		//LMG
		HASH_CASE("Item_Weapon_MG3_C"h, { "MG3"e, 4 ,5 });
		HASH_CASE("Item_Weapon_DP28_C"h, { "DP28"e, 2 ,5 });
		HASH_CASE("Item_Weapon_M249_C"h, { "M249"e, 2 ,5 });

		//SR
		HASH_CASE("Item_Weapon_L6_C"h, { "������"e, 4 ,6 });
		HASH_CASE("Item_Weapon_AWM_C"h, { "AWM"e, 4 ,6 });
		HASH_CASE("Item_Weapon_M24_C"h, { "M24"e, 3 ,6 });
		HASH_CASE("Item_Weapon_Julies_Kar98k_C"h, { "Kar98k"e, 3 ,6 });
		HASH_CASE("Item_Weapon_Kar98k_C"h, { "Kar98k"e, 3 ,6 });
		HASH_CASE("Item_Weapon_Mosin_C"h, { "Ī������"e, 3 ,6 });
		HASH_CASE("Item_Weapon_Win1894_C"h, { "Win94"e, 1 ,6 });

		//DMR
		HASH_CASE("Item_Weapon_Mk14_C"h, { "Mk14"e, 4 ,7 });
		HASH_CASE("Item_Weapon_FNFal_C"h, { "SLR"e, 4 ,7 });
		HASH_CASE("Item_Weapon_Mk12_C"h, { "Mk12"e, 4 ,7 });
		HASH_CASE("Item_Weapon_SKS_C"h, { "SKS"e, 3 ,7 });
		HASH_CASE("Item_Weapon_Mads_QBU88_C"h, { "QBU"e, 3 ,7 });
		HASH_CASE("Item_Weapon_QBU88_C"h, { "QBU"e, 3 ,7 });
		HASH_CASE("Item_Weapon_Mini14_C"h, { "Mini14"e, 3 ,7 });
		HASH_CASE("Item_Weapon_VSS_C"h, { "VSS"e, 3 ,7 });

		//SG
		HASH_CASE("Item_Weapon_DP12_C"h, { "DBS"e, 4 ,8 });
		HASH_CASE("Item_Weapon_Saiga12_C"h, { "S12K"e, 3 ,8 });
		HASH_CASE("Item_Weapon_Winchester_C"h, { "S1897"e, 2 ,8 });
		HASH_CASE("Item_Weapon_Berreta686_C"h, { "S686"e, 2 ,8 });

		//SMG
		HASH_CASE("Item_Weapon_P90_C"h, { "P90"e, 4 ,10 });
		HASH_CASE("Item_Weapon_Vector_C"h, { "Vector"e, 3 ,10 });
		HASH_CASE("Item_Weapon_UZI_C"h, { "UZI"e, 3 ,10 });
		HASH_CASE("Item_Weapon_UMP_C"h, { "UMP"e, 3 ,10 });
		HASH_CASE("Item_Weapon_Thompson_C"h, { "��ķѷ"e, 2 ,10 });
		HASH_CASE("Item_Weapon_BizonPP19_C"h, { "ҰţPP19"e, 2 ,10 });
		HASH_CASE("Item_Weapon_MP5K_C"h, { "MP5K"e, 2 ,10 });

		//Special Weapon
		HASH_CASE("Item_Weapon_Mortar_C"h, { "�Ȼ���"e, 4 ,11 });
		HASH_CASE("Item_Weapon_FlareGun_C"h, { "�ź�ǹ"e, 4,11 });
		HASH_CASE("Item_Weapon_M79_C"h, { "M79"e, 4 ,11 });
		HASH_CASE("Item_Weapon_PanzerFaust100M_C"h, { "���Ͳ"e, 4 ,11 });

		//Boost
		HASH_CASE("Item_Boost_AdrenalineSyringe_C"h, { "�����ټ���"e, 3 ,13 });
		HASH_CASE("Item_Boost_EnergyDrink_C"h, { "��������"e, 3 ,13 });
		HASH_CASE("Item_Boost_PainKiller_C"h, { "ֹ��ҩ"e, 3 ,13 });

		//Heal
		HASH_CASE("Item_Heal_MedKit_C"h, { "ҽ����"e, 4 ,13 });
		HASH_CASE("Item_Heal_FirstAid_C"h, { "���Ȱ�"e, 3 ,13 });
		HASH_CASE("Item_Heal_Bandage_C"h, { "����"e, 2 ,13 });
		HASH_CASE("Item_Weapon_TraumaBag_C"h, { "ҽ���׼�"e, 4,13 });

		//Key
		HASH_CASE("Item_Heaven_Key_C"h, { "Կ��"e, 4 ,14 });
		HASH_CASE("Item_Chimera_Key_C"h, { "Կ��"e, 4 ,14 });
		HASH_CASE("Item_Tiger_Key_C"h, { "Կ��"e, 4 ,14 });


		HASH_CASE("Item_Armor_C_01_Lv3_C"h, { "������Lv3"e, 4 ,12});
		HASH_CASE("Item_Armor_D_01_Lv2_C"h, { "������Lv2"e, 3 ,12});
		HASH_CASE("Item_Armor_E_01_Lv1_C"h, { "������Lv1"e, 2 ,12});

		HASH_CASE("Item_Back_B_08_Lv3_C"h, { "����Lv3"e, 4 ,3 });
		HASH_CASE("Item_Back_C_01_Lv3_C"h, { "����Lv3"e, 4 ,3 });
		HASH_CASE("Item_Back_C_02_Lv3_C"h, { "����Lv3"e, 4 ,3 });
		HASH_CASE("Item_Back_F_01_Lv2_C"h, { "����Lv2"e, 3 ,3 });
		HASH_CASE("Item_Back_F_02_Lv2_C"h, { "����Lv2"e, 3 ,3 });
		HASH_CASE("Item_Back_E_01_Lv1_C"h, { "����Lv1"e, 2 ,3 });
		HASH_CASE("Item_Back_E_02_Lv1_C"h, { "����Lv1"e, 2 ,3 });
		HASH_CASE("Item_Back_BlueBlocker"h, { "�粨���ű���"e, 4 ,1 });

		HASH_CASE("Item_Ghillie_01_C"h, { "������"e, 4 ,12 });
		HASH_CASE("Item_Ghillie_02_C"h, { "������"e, 4 ,12 });
		HASH_CASE("Item_Ghillie_03_C"h, { "������"e, 4 ,12 });
		HASH_CASE("Item_Ghillie_04_C"h, { "������"e, 4 ,12 });
		HASH_CASE("Item_Ghillie_05_C"h, { "������"e, 4 ,12 });
		HASH_CASE("Item_Ghillie_06_C"h, { "������"e, 4 ,12 });
		HASH_CASE("Item_Head_E_01_Lv1_C"h, { "ͷ��Lv1"e, 2 ,9 });
		HASH_CASE("Item_Head_E_02_Lv1_C"h, { "ͷ��Lv1"e, 2 ,9 });
		HASH_CASE("Item_Head_F_01_Lv2_C"h, { "ͷ��Lv2"e, 3 ,9 });
		HASH_CASE("Item_Head_F_02_Lv2_C"h, { "ͷ��Lv2"e, 3 ,9 });
		HASH_CASE("Item_Head_G_01_Lv3_C"h, { "ͷ��Lv3"e, 4 ,9 });



		HASH_CASE("Item_JerryCan_C"h, { "����Ͱ"e, 4 ,15 });
		HASH_CASE("Item_EmergencyPickup_C"h, { "����������"e, 4,15 });
		HASH_CASE("InstantRevivalKit_C"h, { "�Ծ���"e, 4 ,15 });
		HASH_CASE("Item_Tiger_SelfRevive_C"h, { "�Ծ���"e, 4 ,15 });
		HASH_CASE("Item_Mountainbike_C"h, { "���г�"e, 4 ,15 });
		HASH_CASE("Item_Weapon_Drone_C"h, { "���˻�"e, 4 ,15 });

		HASH_CASE("Item_Weapon_Spotter_Scope_C"h, { "��Զ��"e, 4 ,15 });
		HASH_CASE("Item_Weapon_TacPack_C"h, { "ս������"e, 4 ,15 });
		HASH_DEFAULT({ ""e, 0 });
	}
}
