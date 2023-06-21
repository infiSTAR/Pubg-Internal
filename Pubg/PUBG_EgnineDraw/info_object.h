#pragma once
#include "common/util.h"

struct ObjectInfo {
	fixstr::basic_fixed_string<char, 0x100> Name;
	bool IsLong = false;
	bool bFrendly = false;
};

static ObjectInfo GetObjectInfo(unsigned Hash) {
	switch (Hash) {


		HASH_CASE("ProjGrenade_C"h, { "ÊÖÀ×"e });
		HASH_CASE("ProjFlashBang_C"h, { "ÉÁ¹â"e });
		HASH_CASE("ProjMolotov_C"h, { "È¼ÉÕÆ¿"e });
		HASH_CASE("ProjSmokeBomb_v2_C"h, { "ÑÌÎíµ¯"e });
		HASH_CASE("ProjSpiketrap_C"h, { "Õ¨µ¯"e });
		HASH_CASE("BP_Spiketrap_C"h, { "Õ¨µ¯"e });
		HASH_CASE("ProjStickyGrenade_C"h, { "Õ³ÐÔÕ¨µ¯"e });
		HASH_CASE("ProjC4_C"h, { "C4"e });
		HASH_CASE("ProjDecoyGrenade_C"h, { "ÓÕ¶üÊÖÀ×"e });
		HASH_CASE("BP_Projectile_40mm_Smoke_C"h, { "ÑÌÎíµ¯"e });
		HASH_CASE("ProjBluezoneBomb_C"h, { "¶¾È¦ÊÖÀ×"e });
		HASH_CASE("BP_Drone_C"h, { "ÎÞÈË»ú"e });
		HASH_CASE("WeapMortar_C"h, { "ÆÈ»÷ÅÚ"e });

		HASH_CASE("WeapMacheteProjectile_C"h, { "¿³µ¶"e });
		HASH_CASE("WeapCowbarProjectile_C"h, { "åó¼ý"e });
		HASH_CASE("WeapPanProjectile_C"h, { "Æ½µ×¹ø"e });
		HASH_CASE("WeapSickleProjectile_C"h, { "Á­µ¶"e });

		HASH_CASE("PanzerFaust100M_Projectile_C"h, { "»ð¼ýÍ²"e, true });
		HASH_CASE("Mortar_Projectile_C"h, { "ÆÈ»÷ÅÚµ¯"e, true });
		HASH_CASE("Flare_Projectile_C"h, { "ÐÅºÅµ¯"e, true });

		HASH_CASE("BP_KillTruck_C"h, { "»áÉ±ÈËµÄ³µ"e, true });
		HASH_CASE("BP_Helicopter_C"h, { "Ö±Éý»ú"e, true });

		HASH_CASE("BP_Vending_machine_1_C"h, { "ÒûÁÏ»ú"e, false, true });
		HASH_DEFAULT({ ""e, false });
	}
}