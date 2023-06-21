#pragma once
#include "common/util.h"

struct ObjectInfo {
	fixstr::basic_fixed_string<char, 0x100> Name;
	bool IsLong = false;
	bool bFrendly = false;
};

static ObjectInfo GetObjectInfo(unsigned Hash) {
	switch (Hash) {


		HASH_CASE("ProjGrenade_C"h, { "����"e });
		HASH_CASE("ProjFlashBang_C"h, { "����"e });
		HASH_CASE("ProjMolotov_C"h, { "ȼ��ƿ"e });
		HASH_CASE("ProjSmokeBomb_v2_C"h, { "����"e });
		HASH_CASE("ProjSpiketrap_C"h, { "ը��"e });
		HASH_CASE("BP_Spiketrap_C"h, { "ը��"e });
		HASH_CASE("ProjStickyGrenade_C"h, { "ճ��ը��"e });
		HASH_CASE("ProjC4_C"h, { "C4"e });
		HASH_CASE("ProjDecoyGrenade_C"h, { "�ն�����"e });
		HASH_CASE("BP_Projectile_40mm_Smoke_C"h, { "����"e });
		HASH_CASE("ProjBluezoneBomb_C"h, { "��Ȧ����"e });
		HASH_CASE("BP_Drone_C"h, { "���˻�"e });
		HASH_CASE("WeapMortar_C"h, { "�Ȼ���"e });

		HASH_CASE("WeapMacheteProjectile_C"h, { "����"e });
		HASH_CASE("WeapCowbarProjectile_C"h, { "���"e });
		HASH_CASE("WeapPanProjectile_C"h, { "ƽ�׹�"e });
		HASH_CASE("WeapSickleProjectile_C"h, { "����"e });

		HASH_CASE("PanzerFaust100M_Projectile_C"h, { "���Ͳ"e, true });
		HASH_CASE("Mortar_Projectile_C"h, { "�Ȼ��ڵ�"e, true });
		HASH_CASE("Flare_Projectile_C"h, { "�źŵ�"e, true });

		HASH_CASE("BP_KillTruck_C"h, { "��ɱ�˵ĳ�"e, true });
		HASH_CASE("BP_Helicopter_C"h, { "ֱ����"e, true });

		HASH_CASE("BP_Vending_machine_1_C"h, { "���ϻ�"e, false, true });
		HASH_DEFAULT({ ""e, false });
	}
}