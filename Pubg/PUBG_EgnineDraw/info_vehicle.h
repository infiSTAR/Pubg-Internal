#pragma once
#include "common/util.h"

enum class VehicleType1 {
	Wheeled,
	Floating,
	None
};

enum class VehicleType2 {
	Destructible,
	Invincible
};

enum class VehicleType3 {
	Normal,
	Special
};

struct VehicleInfo {
	fixstr::basic_fixed_string<char, 0x100> Name;
	VehicleType1 Type1;
	VehicleType2 Type2;
	VehicleType3 Type3;
};

static VehicleInfo GetVehicleInfo(unsigned Hash) {
	switch (Hash) {


		HASH_CASE("BP_EmPickup_Aircraft_C"h, { "Îï×Ê³µ"e, VehicleType1::None, VehicleType2::Invincible, VehicleType3::Special });
		HASH_CASE("BP_EmergencyPickupVehicle_C"h, { "½ô¼±ºô¾ÈÆ÷"e, VehicleType1::None, VehicleType2::Invincible, VehicleType3::Special });
		HASH_CASE("TransportAircraft_Chimera_C"h, { "·É»ú"e, VehicleType1::None, VehicleType2::Invincible, VehicleType3::Special });
		HASH_CASE("BP_Bicycle_C"h, { "×ÔÐÐ³µ"e, VehicleType1::None, VehicleType2::Invincible, VehicleType3::Normal });

		HASH_CASE("BP_BRDM_C"h, { "×°¼×³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Special });
		HASH_CASE("Uaz_Armored_C"h, { "¼ªÆÕ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Special });
		HASH_CASE("BP_Mirado_Open_05_C"h, { "Æ¤¿¨"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Special });
		HASH_CASE("BP_Motorglider_C"h, { "»¬Ïè»ú"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Special });
		HASH_CASE("BP_Motorglider_Blue_C"h, { "»¬Ïè»ú"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Special });
		HASH_CASE("BP_Motorglider_Green_C"h, { "»¬Ïè»ú"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Special });
		HASH_CASE("BP_Motorglider_Orange_C"h, { "»¬Ïè»ú"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Special });
		HASH_CASE("BP_Motorglider_Red_C"h, { "»¬Ïè»ú"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Special });
		HASH_CASE("BP_Motorglider_Teal_C"h, { "»¬Ïè»ú"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Special });
		HASH_CASE("BP_LootTruck_C"h, { "Îï×Ê³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Special });

		HASH_CASE("AquaRail_A_01_C"h, { "Ä¦ÍÐÍ§"e, VehicleType1::Floating, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("AquaRail_A_02_C"h, { "Ä¦ÍÐÍ§"e, VehicleType1::Floating, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("AquaRail_A_03_C"h, { "Ä¦ÍÐÍ§"e, VehicleType1::Floating, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("Boat_PG117_C"h, { "¿ìÍ§"e, VehicleType1::Floating, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("PG117_A_01_C"h, { "¿ìÍ§"e, VehicleType1::Floating, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("AirBoat_V2_C"h, { "ÆûÍ§"e, VehicleType1::Floating, VehicleType2::Destructible, VehicleType3::Normal });

		HASH_CASE("BP_M_Rony_A_01_C"h, { "Æ¤¿¨³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_M_Rony_A_02_C"h, { "Æ¤¿¨³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_M_Rony_A_03_C"h, { "Æ¤¿¨³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Mirado_C"h, { "ÅÜ³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Mirado_A_01_C"h, { "ÅÜ³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Mirado_A_02_C"h, { "ÅÜ³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Mirado_A_03_C"h, { "ÅÜ³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Mirado_A_03_Esports_C"h, { "ÅÜ³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Mirado_A_04_C"h, { "ÅÜ³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Mirado_Open_C"h, { "³¬ÅÜ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Mirado_Open_01_C"h, { "³¬ÅÜ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Mirado_Open_02_C"h, { "³¬ÅÜ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Mirado_Open_03_C"h, { "³¬ÅÜ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Mirado_Open_04_C"h, { "³¬ÅÜ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Motorbike_04_C"h, { "Ä¦ÍÐ³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Motorbike_04_Desert_C"h, { "Ä¦ÍÐ³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Motorbike_Solitario_C"h, { "Ä¦ÍÐ³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Motorbike_04_SideCar_C"h, { "Ä¦ÍÐ³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Motorbike_04_SideCar_Desert_C"h, { "Ä¦ÍÐ³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Niva_01_C"h, { "Ñ©µØ¼ªÆÕ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Niva_02_C"h, { "Ñ©µØ¼ªÆÕ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Niva_03_C"h, { "Ñ©µØ¼ªÆÕ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Niva_04_C"h, { "Ñ©µØ¼ªÆÕ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Niva_05_C"h, { "Ñ©µØ¼ªÆÕ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Niva_06_C"h, { "Ñ©µØ¼ªÆÕ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Niva_07_C"h, { "Ñ©µØ¼ªÆÕ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Niva_Esports_C"h, { "Ñ©µØ¼ªÆÕ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_PickupTruck_A_01_C"h, { "Æ¤¿¨"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_PickupTruck_A_02_C"h, { "Æ¤¿¨"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_PickupTruck_A_03_C"h, { "Æ¤¿¨"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_PickupTruck_A_04_C"h, { "Æ¤¿¨"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_PickupTruck_A_05_C"h, { "Æ¤¿¨"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_PickupTruck_A_esports_C"h, { "Æ¤¿¨"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_PickupTruck_B_01_C"h, { "Æ¤¿¨"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_PickupTruck_B_02_C"h, { "Æ¤¿¨"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_PickupTruck_B_03_C"h, { "Æ¤¿¨"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_PickupTruck_B_04_C"h, { "Æ¤¿¨"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_PickupTruck_B_05_C"h, { "Æ¤¿¨"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_TukTukTuk_A_01_C"h, { "Ä¦ÍÐ³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_TukTukTuk_A_02_C"h, { "Ä¦ÍÐ³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_TukTukTuk_A_03_C"h, { "Ä¦ÍÐ³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Van_A_01_C"h, { "¹«½»³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Van_A_02_C"h, { "¹«½»³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Van_A_03_C"h, { "¹«½»³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_MiniBus_C"h, { "¹«½»³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Scooter_01_A_C"h, { "Ì¤°å³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Scooter_02_A_C"h, { "Ì¤°å³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Scooter_03_A_C"h, { "Ì¤°å³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Scooter_04_A_C"h, { "Ì¤°å³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Snowbike_01_C"h, { "Ñ©µØÄ¦ÍÐ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Snowbike_02_C"h, { "Ñ©µØÄ¦ÍÐ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Snowmobile_01_C"h, { "Ñ©µØÄ¦ÍÐ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Snowmobile_02_C"h, { "Ñ©µØÄ¦ÍÐ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Snowmobile_03_C"h, { "Ñ©µØÄ¦ÍÐ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("Buggy_A_01_C"h, { "É³µØ³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("Buggy_A_02_C"h, { "É³µØ³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("Buggy_A_03_C"h, { "É³µØ³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("Buggy_A_04_C"h, { "É³µØ³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("Buggy_A_05_C"h, { "É³µØ³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("Buggy_A_06_C"h, { "É³µØ³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("Dacia_A_01_v2_C"h, { "Æû³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("Dacia_A_01_v2_snow_C"h, { "Æû³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("Dacia_A_02_v2_C"h, { "Æû³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("Dacia_A_03_v2_C"h, { "Æû³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("Dacia_A_03_v2_Esports_C"h, { "Æû³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("Dacia_A_04_v2_C"h, { "Æû³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("Uaz_A_01_C"h, { "¼ªÆÕ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("Uaz_B_01_C"h, { "¼ªÆÕ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("Uaz_B_01_esports_C"h, { "¼ªÆÕ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("Uaz_C_01_C"h, { "¼ªÆÕ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Dirtbike_C"h, { "Ô½Ò°Ä¦ÍÐ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_CoupeRB_C"h, { "Ë«ÈËÅÜ³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_ATV_C"h, { "È«µØÐÎÄ¦ÍÐ³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_PonyCoupe_C"h, { "ÅÜ³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Porter_C"h, { "»õ³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Pillar_Car_C"h, { "¾¯³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_CASE("BP_Food_Truck_C"h, { "Ê³Æ·ÔËÊä³µ"e, VehicleType1::Wheeled, VehicleType2::Destructible, VehicleType3::Normal });
		HASH_DEFAULT({ ""e, VehicleType1::None, VehicleType2::Destructible, VehicleType3::Normal });
	}
}