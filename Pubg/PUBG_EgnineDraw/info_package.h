#pragma once
#include "common/util.h"

struct PackageInfo {
	fixstr::basic_fixed_string<char, 0x100> Name;
	bool IsSmall;
};

static PackageInfo GetPackageInfo(unsigned Hash) {
	switch (Hash) {


		HASH_CASE("DeathDropItemPackage_C"h, { "盒子"e, false });
		HASH_CASE("Carapackage_RedBox_C"h, { "空投"e, false });
		HASH_CASE("Carapackage_FlareGun_C"h, { "信号枪"e, false });
		HASH_CASE("BP_Loot_AmmoBox_C"h, { "子弹箱"e, true });
		HASH_CASE("BP_Loot_MilitaryCrate_C"h, { "军用箱"e, true });
		HASH_CASE("BP_Loot_TruckHaul_C"h, { "战利品车"e, false });
		HASH_CASE("Carapackage_SmallPackage_C"h, { "小空投"e, true });
		HASH_CASE("BP_ItemPackage_GuardedLoot_Heaven_C"h, { "守卫者盒子"e, true });
		HASH_DEFAULT({ ""e, false });
	}
}