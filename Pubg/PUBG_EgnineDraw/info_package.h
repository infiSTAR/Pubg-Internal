#pragma once
#include "common/util.h"

struct PackageInfo {
	fixstr::basic_fixed_string<char, 0x100> Name;
	bool IsSmall;
};

static PackageInfo GetPackageInfo(unsigned Hash) {
	switch (Hash) {


		HASH_CASE("DeathDropItemPackage_C"h, { "����"e, false });
		HASH_CASE("Carapackage_RedBox_C"h, { "��Ͷ"e, false });
		HASH_CASE("Carapackage_FlareGun_C"h, { "�ź�ǹ"e, false });
		HASH_CASE("BP_Loot_AmmoBox_C"h, { "�ӵ���"e, true });
		HASH_CASE("BP_Loot_MilitaryCrate_C"h, { "������"e, true });
		HASH_CASE("BP_Loot_TruckHaul_C"h, { "ս��Ʒ��"e, false });
		HASH_CASE("Carapackage_SmallPackage_C"h, { "С��Ͷ"e, true });
		HASH_CASE("BP_ItemPackage_GuardedLoot_Heaven_C"h, { "�����ߺ���"e, true });
		HASH_DEFAULT({ ""e, false });
	}
}