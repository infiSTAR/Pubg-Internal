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
		HASH_CASE("Item_Ammo_Flare_C"h, { "ÐÅºÅµ¯"e, 4 ,16 });
		HASH_CASE("Item_Ammo_57mm_C"h, { "5.7mm"e, 4 ,16 });
		HASH_CASE("Item_Ammo_300Magnum_C"h, { ".300Âí¸ñÄÏ"e, 4 ,16 });
		HASH_CASE("Item_Ammo_556mm_C"h, { "5.56mm"e, 3 ,16 });
		HASH_CASE("Item_Ammo_762mm_C"h, { "7.62mm"e, 3 ,16 });
		HASH_CASE("Item_Ammo_40mm_C"h, { "40mm"e, 3 ,16 });
		HASH_CASE("Item_Ammo_9mm_C"h, { "9mm"e, 2 ,16 });
		HASH_CASE("Item_Ammo_12Guage_C"h, { "12¿Ú¾¶"e, 2 ,16 });
		HASH_CASE("Item_Ammo_45ACP_C"h, { ".45"e, 2 ,16 });

		//Attach
		HASH_CASE("Item_Attach_Weapon_Lower_Foregrip_C"h, { "´¹Ö±ÎÕ°Ñ"e, 3 ,1 });
		HASH_CASE("Item_Attach_Weapon_Lower_AngledForeGrip_C"h, { "Èý½ÇÎÕ°Ñ"e, 2 ,1 });
		HASH_CASE("Item_Attach_Weapon_Lower_HalfGrip_C"h, { "°ë½ØÎÕ°Ñ"e, 2 ,1 });
		HASH_CASE("Item_Attach_Weapon_Lower_LightweightForeGrip_C"h, { "ÇáÐÍÎÕ°Ñ"e, 2 ,1 });
		HASH_CASE("Item_Attach_Weapon_Lower_ThumbGrip_C"h, { "Ä´Ö¸ÎÕ°Ñ"e, 2 ,1 });

		HASH_CASE("Item_Attach_Weapon_Magazine_ExtendedQuickDraw_Large_C"h, { "²½Ç¹¿ìËÙÀ©ÈÝµ¯¼Ð"e, 4 ,1 });
		HASH_CASE("Item_Attach_Weapon_Magazine_Extended_Large_C"h, { "²½Ç¹À©ÈÝµ¯¼Ð"e, 3 ,1 });

		HASH_CASE("Item_Attach_Weapon_Magazine_ExtendedQuickDraw_SniperRifle_C"h, { "¾Ñ»÷¿ìËÙÀ©ÈÝµ¯¼Ð"e, 4 ,1 });
		HASH_CASE("Item_Attach_Weapon_Magazine_Extended_SniperRifle_C"h, { "¾Ñ»÷À©ÈÝµ¯¼Ð"e, 3 ,1 });


		HASH_CASE("Item_Attach_Weapon_Muzzle_Compensator_Large_C"h, { "²½Ç¹²¹³¥Æ÷"e, 3 ,1 });


		HASH_CASE("Item_Attach_Weapon_Muzzle_Suppressor_SniperRifle_C"h, { "¾Ñ»÷ÏûÒôÆ÷"e, 4 ,1 });
		HASH_CASE("Item_Attach_Weapon_Muzzle_Suppressor_Large_C"h, { "²½Ç¹ÏûÒôÆ÷"e, 4 ,1 });


		HASH_CASE("Item_Attach_Weapon_SideRail_DotSight_RMR_C"h, { "²à±ßÃé×¼Æ÷"e, 4 ,1 });

		HASH_CASE("Item_Attach_Weapon_Stock_AR_Composite_C"h, { "Õ½ÊõÇ¹ÍÐ"e, 3 ,1 });
		HASH_CASE("Item_Attach_Weapon_Stock_SniperRifle_CheekPad_C"h, { "ÍÐÈù°å"e, 3 ,1 });
		HASH_CASE("Item_Attach_Weapon_Stock_SniperRifle_BulletLoops_C"h, { "×Óµ¯´ø"e, 2 ,1 });

		HASH_CASE("Item_Attach_Weapon_Upper_PM2_01_C"h, { "15±¶¾µ"e, 4 ,1 });
		HASH_CASE("Item_Attach_Weapon_Upper_CQBSS_C"h, { "8±¶¾µ"e, 4 ,1 });
		HASH_CASE("Item_Attach_Weapon_Upper_Scope6x_C"h, { "6±¶¾µ"e, 4 ,1 });
		HASH_CASE("Item_Attach_Weapon_Upper_ACOG_01_C"h, { "4±¶¾µ"e, 3 ,1 });
		HASH_CASE("Item_Attach_Weapon_Upper_Scope3x_C"h, { "3±¶¾µ"e, 3 ,1 });
		HASH_CASE("Item_Attach_Weapon_Upper_Aimpoint_C"h, { "2±¶¾µ"e, 3 ,1 });
		HASH_CASE("Item_Attach_Weapon_Upper_DotSight_01_C"h, { "ºìµã"e, 3 ,1 });
		HASH_CASE("Item_Attach_Weapon_Upper_Holosight_C"h, { "È«Ï¢"e, 3 ,1 });

		HASH_CASE("Item_Back_BackupParachute_C"h, { "½µÂäÉ¡"e, 3 ,1 });


		//Throw
		HASH_CASE("Item_Weapon_C4_C"h, { "C4"e, 4 ,2 });
		HASH_CASE("Item_Weapon_BluezoneGrenade_C"h, { "¶¾È¦ÊÖÀ×"e, 3 ,2 });
		HASH_CASE("Item_Weapon_Grenade_C"h, { "ÊÖÀ×"e, 3 ,2 });
		HASH_CASE("Item_Weapon_Grenade_Warmode_C"h, { "ÊÖÀ×"e, 3 ,2 });
		HASH_CASE("Item_Weapon_FlashBang_C"h, { "ÉÁ¹âµ¯"e, 3 ,2 });
		HASH_CASE("Item_Weapon_StickyGrenade_C"h, { "Õ³ÐÔÕ¨µ¯"e, 3 ,2 });
		HASH_CASE("Item_Weapon_Molotov_C"h, { "È¼ÉÕÆ¿"e, 3 ,2 });
		HASH_CASE("Item_Weapon_SmokeBomb_C"h, { "ÑÌÎíµ¯"e, 3 ,2 });
		HASH_CASE("Item_Weapon_SpikeTrap_C"h, { "¼â´ÌÏÝÚå"e, 3 ,2 });
		HASH_CASE("Item_Weapon_DecoyGrenade_C"h, { "ÓÕ¶üÊÖÀ×"e, 1 ,2 });

		HASH_CASE("Item_Weapon_Pan_C"h, { "Æ½µ×¹ø"e, 3 ,1 });


		//AR
		HASH_CASE("Item_Weapon_Groza_C"h, { "¹·ÔÒ"e, 4 ,4 });
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
		HASH_CASE("Item_Weapon_L6_C"h, { "°ÍÀ×ÌØ"e, 4 ,6 });
		HASH_CASE("Item_Weapon_AWM_C"h, { "AWM"e, 4 ,6 });
		HASH_CASE("Item_Weapon_M24_C"h, { "M24"e, 3 ,6 });
		HASH_CASE("Item_Weapon_Julies_Kar98k_C"h, { "Kar98k"e, 3 ,6 });
		HASH_CASE("Item_Weapon_Kar98k_C"h, { "Kar98k"e, 3 ,6 });
		HASH_CASE("Item_Weapon_Mosin_C"h, { "ÄªÐÁ¸ÊÄÉ"e, 3 ,6 });
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
		HASH_CASE("Item_Weapon_Thompson_C"h, { "ÌÀÄ·Ñ·"e, 2 ,10 });
		HASH_CASE("Item_Weapon_BizonPP19_C"h, { "Ò°Å£PP19"e, 2 ,10 });
		HASH_CASE("Item_Weapon_MP5K_C"h, { "MP5K"e, 2 ,10 });

		//Special Weapon
		HASH_CASE("Item_Weapon_Mortar_C"h, { "ÆÈ»÷ÅÚ"e, 4 ,11 });
		HASH_CASE("Item_Weapon_FlareGun_C"h, { "ÐÅºÅÇ¹"e, 4,11 });
		HASH_CASE("Item_Weapon_M79_C"h, { "M79"e, 4 ,11 });
		HASH_CASE("Item_Weapon_PanzerFaust100M_C"h, { "»ð¼ýÍ²"e, 4 ,11 });

		//Boost
		HASH_CASE("Item_Boost_AdrenalineSyringe_C"h, { "ÉöÉÏÏÙ¼¤ËØ"e, 3 ,13 });
		HASH_CASE("Item_Boost_EnergyDrink_C"h, { "ÄÜÁ¿ÒûÁÏ"e, 3 ,13 });
		HASH_CASE("Item_Boost_PainKiller_C"h, { "Ö¹ÌÛÒ©"e, 3 ,13 });

		//Heal
		HASH_CASE("Item_Heal_MedKit_C"h, { "Ò½ÁÆÏä"e, 4 ,13 });
		HASH_CASE("Item_Heal_FirstAid_C"h, { "¼±¾È°ü"e, 3 ,13 });
		HASH_CASE("Item_Heal_Bandage_C"h, { "±Á´ø"e, 2 ,13 });
		HASH_CASE("Item_Weapon_TraumaBag_C"h, { "Ò½ÁÆÌ×¼ä"e, 4,13 });

		//Key
		HASH_CASE("Item_Heaven_Key_C"h, { "Ô¿³×"e, 4 ,14 });
		HASH_CASE("Item_Chimera_Key_C"h, { "Ô¿³×"e, 4 ,14 });
		HASH_CASE("Item_Tiger_Key_C"h, { "Ô¿³×"e, 4 ,14 });


		HASH_CASE("Item_Armor_C_01_Lv3_C"h, { "·Àµ¯ÒÂLv3"e, 4 ,12});
		HASH_CASE("Item_Armor_D_01_Lv2_C"h, { "·Àµ¯ÒÂLv2"e, 3 ,12});
		HASH_CASE("Item_Armor_E_01_Lv1_C"h, { "·Àµ¯ÒÂLv1"e, 2 ,12});

		HASH_CASE("Item_Back_B_08_Lv3_C"h, { "±³°üLv3"e, 4 ,3 });
		HASH_CASE("Item_Back_C_01_Lv3_C"h, { "±³°üLv3"e, 4 ,3 });
		HASH_CASE("Item_Back_C_02_Lv3_C"h, { "±³°üLv3"e, 4 ,3 });
		HASH_CASE("Item_Back_F_01_Lv2_C"h, { "±³°üLv2"e, 3 ,3 });
		HASH_CASE("Item_Back_F_02_Lv2_C"h, { "±³°üLv2"e, 3 ,3 });
		HASH_CASE("Item_Back_E_01_Lv1_C"h, { "±³°üLv1"e, 2 ,3 });
		HASH_CASE("Item_Back_E_02_Lv1_C"h, { "±³°üLv1"e, 2 ,3 });
		HASH_CASE("Item_Back_BlueBlocker"h, { "µç²¨¸ÉÈÅ±³°ü"e, 4 ,1 });

		HASH_CASE("Item_Ghillie_01_C"h, { "¼ªÀû·þ"e, 4 ,12 });
		HASH_CASE("Item_Ghillie_02_C"h, { "¼ªÀû·þ"e, 4 ,12 });
		HASH_CASE("Item_Ghillie_03_C"h, { "¼ªÀû·þ"e, 4 ,12 });
		HASH_CASE("Item_Ghillie_04_C"h, { "¼ªÀû·þ"e, 4 ,12 });
		HASH_CASE("Item_Ghillie_05_C"h, { "¼ªÀû·þ"e, 4 ,12 });
		HASH_CASE("Item_Ghillie_06_C"h, { "¼ªÀû·þ"e, 4 ,12 });
		HASH_CASE("Item_Head_E_01_Lv1_C"h, { "Í·¿øLv1"e, 2 ,9 });
		HASH_CASE("Item_Head_E_02_Lv1_C"h, { "Í·¿øLv1"e, 2 ,9 });
		HASH_CASE("Item_Head_F_01_Lv2_C"h, { "Í·¿øLv2"e, 3 ,9 });
		HASH_CASE("Item_Head_F_02_Lv2_C"h, { "Í·¿øLv2"e, 3 ,9 });
		HASH_CASE("Item_Head_G_01_Lv3_C"h, { "Í·¿øLv3"e, 4 ,9 });



		HASH_CASE("Item_JerryCan_C"h, { "ÆûÓÍÍ°"e, 4 ,15 });
		HASH_CASE("Item_EmergencyPickup_C"h, { "½ô¼±ºô¾ÈÆ÷"e, 4,15 });
		HASH_CASE("InstantRevivalKit_C"h, { "×Ô¾ÈÆ÷"e, 4 ,15 });
		HASH_CASE("Item_Tiger_SelfRevive_C"h, { "×Ô¾ÈÆ÷"e, 4 ,15 });
		HASH_CASE("Item_Mountainbike_C"h, { "×ÔÐÐ³µ"e, 4 ,15 });
		HASH_CASE("Item_Weapon_Drone_C"h, { "ÎÞÈË»ú"e, 4 ,15 });

		HASH_CASE("Item_Weapon_Spotter_Scope_C"h, { "ÍûÔ¶¾µ"e, 4 ,15 });
		HASH_CASE("Item_Weapon_TacPack_C"h, { "Õ½Êõ±³°ü"e, 4 ,15 });
		HASH_DEFAULT({ ""e, 0 });
	}
}
