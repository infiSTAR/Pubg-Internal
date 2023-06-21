#pragma once
#include <map>
#include "Main.h"
#include "Gui/ZeroGUI.h"
#include "GameHack.h"
#include "info_character.h"
#include "info_item.h"
#include "info_object.h"
#include "info_package.h"
#include "info_vehicle.h"
#include "info_weapon.h"
#include "userinfo.h"
#include "xorstr.h"
CUserInfo UserInfo;
bool IsLock = false;
ULONG64 AimPlayer = NULL,  LastAimPlayer = NULL;

#define Sss(vKey) (Func::GetAsyncKeyState2(vKey) & 1)
#define SSs(vKey) ((Func::GetAsyncKeyState2(vKey) & 1) && Func::GetAsyncKeyState2(vKey))

#define KeyState(KEY) GetAsyncKeyState(KEY) & 1
#define KeyState2(KEY) ((GetAsyncKeyState(KEY) & 0x8000) ? 1 : 0)

FVector AmtPos = { 0.f,0.f,0.f };
FVector AmtPos111 = { 0.f,0.f,0.f };
int GEDistance;
std::vector<FVector> TempItemOverlayArr;
float ScreenDis(FVector2D vector, float GameX, float GameY) {
	FVector2D Vec;
	Vec.X = GameX - vector.X;
	Vec.Y = GameY - vector.Y;
	float dis = sqrtf(Vec.X * Vec.X + Vec.Y * Vec.Y);
	return dis;
}
float Get2DDis(FVector2D vector, float GameX, float GameY) {
	FVector2D Vec;
	Vec.X = GameX - vector.X;
	Vec.Y = GameY - vector.Y;
	float dis = sqrtf(powf(Vec.X, 2) + powf(Vec.Y, 2));
	return dis;
}
bool IsRange(int CurrentValue, int Min, int Max)
{
	return CurrentValue > Min && CurrentValue < Max;
}
void IsOverlay(FVector& D2D)
{
	for (int i = 0; i < TempItemOverlayArr.size(); i++)
	{
		if (IsRange(D2D.X, TempItemOverlayArr[i].X - 30, TempItemOverlayArr[i].X + 30) && IsRange(D2D.Y, TempItemOverlayArr[i].Y - 15, TempItemOverlayArr[i].Y + 15))
		{
			D2D = TempItemOverlayArr[i];
			D2D.Y = D2D.Y - 13.f;
		}
	}
}
void ��������(FVector2D A, FVector2D B, FVector2D C, float thickness, FLinearColor clr)
{

	UCanvas::DrawLine(A.X, A.Y, B.X, B.Y, thickness, clr);
	UCanvas::DrawLine( B.X, B.Y, C.X, C.Y, thickness, clr);
	UCanvas::DrawLine( C.X, C.Y, A.X, A.Y, thickness, clr);
}
void ���Ʊ�ʶ(FRotator ���, FVector ����Pos, FVector ����pos, float Size)
{
	float ���� = (����Pos).Distance(����pos) / 100;
	float �Ƕ� = atan2(����Pos.Y - ����pos.Y, ����Pos.X - ����pos.X);
	�Ƕ� = �Ƕ� * 180 / M_PI;
	�Ƕ� = ���.Yaw + 360 - �Ƕ�; //Y��ʵ��X���洢˳��ͬ

	FVector2D A, B, C;
	A.X = (Size + 10.0f) * sin(�Ƕ� * M_PI / 180) + Game->ScreenCenter.X;
	A.Y = (Size + 10.0f) * cos(�Ƕ� * M_PI / 180) + Game->ScreenCenter.Y;

	B.X = (Size - 10.0f) * sin((�Ƕ� - 5) * M_PI / 180) + Game->ScreenCenter.X;
	B.Y = (Size - 10.0f) * cos((�Ƕ� - 5) * M_PI / 180) + Game->ScreenCenter.Y;

	C.X = (Size - 10.0f) * sin((�Ƕ� + 5) * M_PI / 180) + Game->ScreenCenter.X;
	C.Y = (Size - 10.0f) * cos((�Ƕ� + 5) * M_PI / 180) + Game->ScreenCenter.Y;

	FLinearColor clr;

	if (���� < 400)
	{
		clr = Colo->��ɫ;
		if (���� < 100.0f)
			clr = Colo->��ɫ;
		else if (���� < 200.0f)
			clr = Colo->�Ȼ�;
		else if (���� < 300.0f)
			clr = Colo->��ɫ;
		��������(A, B, C, 1, clr);
	}
}
void Drawbone(ULONG64 mesh, FLinearColor Col, FLinearColor NoColor)
{
	FVector Head, Neck, R_Clavicle, L_Clavicle, R_UpperArm, L_UpperArm, R_Forearm, L_Forearm, R_Hand, L_Hand, Pelvis, L_Thigh, R_Thigh, R_Calf, L_Calf, R_Foot, L_Foot;
	FVector2D HeadPos, NeckPos, R_ClaviclePos, L_ClaviclePos, R_UpperArmPos, L_UpperArmPos, R_ForearmPos, L_ForearmPos, R_HandPos, L_HandPos, PelvisPos, L_ThighPos, R_ThighPos, R_CalfPos, L_CalfPos, R_FootPos, L_FootPos;

	PubgData::GetBoneMatrix(mesh, &Head, forehead);
	PubgData::GetBoneMatrix(mesh, &Neck, neck_01);
	PubgData::GetBoneMatrix(mesh, &Pelvis, pelvis);
	PubgData::GetBoneMatrix(mesh, &R_Clavicle, clavicle_r);
	PubgData::GetBoneMatrix(mesh, &L_Clavicle, clavicle_l);
	PubgData::GetBoneMatrix(mesh, &R_UpperArm, upperarm_r);
	PubgData::GetBoneMatrix(mesh, &L_UpperArm, upperarm_l);
	PubgData::GetBoneMatrix(mesh, &R_Forearm, lowerarm_r);
	PubgData::GetBoneMatrix(mesh, &L_Forearm, lowerarm_l);

	PubgData::GetBoneMatrix(mesh, &R_Hand, hand_r);
	PubgData::GetBoneMatrix(mesh, &L_Hand, hand_l);

	PubgData::GetBoneMatrix(mesh, &R_Thigh, thigh_r);
	PubgData::GetBoneMatrix(mesh, &L_Thigh, thigh_l);
	PubgData::GetBoneMatrix(mesh, &R_Calf, calf_r);
	PubgData::GetBoneMatrix(mesh, &L_Calf, calf_l);
	PubgData::GetBoneMatrix(mesh, &R_Foot, foot_r);
	PubgData::GetBoneMatrix(mesh, &L_Foot, foot_l);
	if (PubgData::WorldToScreen(Head, HeadPos) &&
		PubgData::WorldToScreen(Neck, NeckPos) &&
		PubgData::WorldToScreen(Pelvis, PelvisPos) &&
		PubgData::WorldToScreen(L_Clavicle, L_ClaviclePos) &&
		PubgData::WorldToScreen(R_Clavicle, R_ClaviclePos) &&
		PubgData::WorldToScreen(L_UpperArm, L_UpperArmPos) &&
		PubgData::WorldToScreen(R_UpperArm, R_UpperArmPos) &&
		PubgData::WorldToScreen(L_Forearm, L_ForearmPos) &&
		PubgData::WorldToScreen(R_Forearm, R_ForearmPos) &&
		PubgData::WorldToScreen(L_Hand, L_HandPos) &&
		PubgData::WorldToScreen(R_Hand, R_HandPos) &&
		PubgData::WorldToScreen(L_Thigh, L_ThighPos) &&
		PubgData::WorldToScreen(R_Thigh, R_ThighPos) &&
		PubgData::WorldToScreen(L_Calf, L_CalfPos) &&
		PubgData::WorldToScreen(R_Calf, R_CalfPos) &&
		PubgData::WorldToScreen(L_Foot, L_FootPos) &&
		PubgData::WorldToScreen(R_Foot, R_FootPos)) {
		//����

		//UCanvas::DrawLine(HeadPos.X, HeadPos.Y, NeckPos.X, NeckPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, Neck) ? Col : NoColor);
		UCanvas::DrawLine(NeckPos.X, NeckPos.Y, PelvisPos.X, PelvisPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, Pelvis) ? Col : NoColor);
		//����
		UCanvas::DrawLine(NeckPos.X, NeckPos.Y, L_ClaviclePos.X, L_ClaviclePos.Y, 0.9f, Func::LineTraceSingle(Game->Location, L_Clavicle) ? Col : NoColor);
		UCanvas::DrawLine(L_ClaviclePos.X, L_ClaviclePos.Y, L_UpperArmPos.X, L_UpperArmPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, L_UpperArm) ? Col : NoColor);
		UCanvas::DrawLine(L_UpperArmPos.X, L_UpperArmPos.Y, L_ForearmPos.X, L_ForearmPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, L_Forearm) ? Col : NoColor);
		UCanvas::DrawLine(L_ForearmPos.X, L_ForearmPos.Y, L_HandPos.X, L_HandPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, L_Hand) ? Col : NoColor);
		//����
		UCanvas::DrawLine(NeckPos.X, NeckPos.Y, R_ClaviclePos.X, R_ClaviclePos.Y, 0.9f, Func::LineTraceSingle(Game->Location, R_Clavicle) ? Col : NoColor);
		UCanvas::DrawLine(R_ClaviclePos.X, R_ClaviclePos.Y, R_UpperArmPos.X, R_UpperArmPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, R_UpperArm) ? Col : NoColor);
		UCanvas::DrawLine(R_UpperArmPos.X, R_UpperArmPos.Y, R_ForearmPos.X, R_ForearmPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, R_Forearm) ? Col : NoColor);
		UCanvas::DrawLine(R_ForearmPos.X, R_ForearmPos.Y, R_HandPos.X, R_HandPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, R_Hand) ? Col : NoColor);
		//����
		UCanvas::DrawLine(PelvisPos.X, PelvisPos.Y, L_ThighPos.X, L_ThighPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, L_Thigh) ? Col : NoColor);
		UCanvas::DrawLine(L_ThighPos.X, L_ThighPos.Y, L_CalfPos.X, L_CalfPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, L_Calf) ? Col : NoColor);
		UCanvas::DrawLine(L_CalfPos.X, L_CalfPos.Y, L_FootPos.X, L_FootPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, L_Foot) ? Col : NoColor);
		//����
		UCanvas::DrawLine(PelvisPos.X, PelvisPos.Y, R_ThighPos.X, R_ThighPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, R_Thigh) ? Col : NoColor);
		UCanvas::DrawLine(R_ThighPos.X, R_ThighPos.Y, R_CalfPos.X, R_CalfPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, R_Calf) ? Col : NoColor);
		UCanvas::DrawLine(R_CalfPos.X, R_CalfPos.Y, R_FootPos.X, R_FootPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, R_Foot) ? Col : NoColor);
	}

}
FLinearColor ������ɫת��(INT R, INT G, INT B, INT A)
{
	FLinearColor temp;
	temp.R = (float)R / 255;
	temp.G = (float)G / 255;
	temp.B = (float)B / 255;
	temp.A = (float)A / 100;
	return temp;
}
FLinearColor GetTeamCrolor(int32_t ����)
{
	FLinearColor ��ʱ��ɫ;
	if (���� == 1 || ���� == 26 || ���� == 51 || ���� == 76)
	{
		��ʱ��ɫ = ������ɫת��(255, 182, 193, 255);
	}
	else if (���� == 2 || ���� == 27 || ���� == 52 || ���� == 77)
	{
		��ʱ��ɫ = ������ɫת��(255, 192, 203, 255);
	}
	else if (���� == 3 || ���� == 28 || ���� == 5. || ���� == 78)
	{
		��ʱ��ɫ = ������ɫת��(220, 20, 60, 255);
	}
	else if (���� == 4 || ���� == 29 || ���� == 54 || ���� == 79)
	{
		��ʱ��ɫ = ������ɫת��(0, 255, 127, 255);
	}
	else if (���� == 5 || ���� == 30 || ���� == 55 || ���� == 80)
	{
		��ʱ��ɫ = ������ɫת��(219, 112, 147, 255);
	}
	else if (���� == 6 || ���� == 31 || ���� == 56 || ���� == 81)
	{
		��ʱ��ɫ = ������ɫת��(255, 105, 180, 255);
	}
	else if (���� == 7 || ���� == 32 || ���� == 57 || ���� == 82)
	{
		��ʱ��ɫ = ������ɫת��(255, 20, 147, 255);
	}
	else if (���� == 8 || ���� == 33 || ���� == 58 || ���� == 83)
	{
		��ʱ��ɫ = ������ɫת��(255, 106, 106, 255);
	}
	else if (���� == 9 || ���� == 34 || ���� == 59 || ���� == 84)
	{
		��ʱ��ɫ = ������ɫת��(218, 112, 214, 255);
	}
	else if (���� == 10 || ���� == 35 || ���� == 60 || ���� == 85)
	{
		��ʱ��ɫ = ������ɫת��(216, 191, 216, 255);
	}
	else if (���� == 11 || ���� == 36 || ���� == 61 || ���� == 86)
	{
		��ʱ��ɫ = ������ɫת��(221, 160, 221, 255);
	}
	else if (���� == 12 || ���� == 37 || ���� == 62 || ���� == 87)
	{
		��ʱ��ɫ = ������ɫת��(238, 130, 238, 255);
	}
	else if (���� == 13 || ���� == 38 || ���� == 63 || ���� == 88)
	{
		��ʱ��ɫ = ������ɫת��(255, 69, 0, 255);
	}
	else if (���� == 14 || ���� == 39 || ���� == 64 || ���� == 89)
	{
		��ʱ��ɫ = ������ɫת��(255, 130, 71, 255);
	}
	else if (���� == 15 || ���� == 40 || ���� == 65 || ���� == 90)
	{
		��ʱ��ɫ = ������ɫת��(255, 127, 36, 255);
	}
	else if (���� == 16 || ���� == 41 || ���� == 66 || ���� == 91)
	{
		��ʱ��ɫ = ������ɫת��(255, 69, 0, 255);
	}
	else if (���� == 17 || ���� == 42 || ���� == 67 || ���� == 92)
	{
		��ʱ��ɫ = ������ɫת��(0, 255, 0, 255);
	}
	else if (���� == 18 || ���� == 43 || ���� == 68 || ���� == 93)
	{
		��ʱ��ɫ = ������ɫת��(192, 255, 62, 255);
	}
	else if (���� == 19 || ���� == 44 || ���� == 69 || ���� == 94)
	{
		��ʱ��ɫ = ������ɫת��(153, 50, 204, 255);
	}
	else if (���� == 20 || ���� == 45 || ���� == 70 || ���� == 95)
	{
		��ʱ��ɫ = ������ɫת��(0, 255, 255, 255);
	}
	else if (���� == 21 || ���� == 46 || ���� == 71 || ���� == 96)
	{
		��ʱ��ɫ = ������ɫת��(212, 242, 231, 255);
	}
	else if (���� == 22 || ���� == 47 || ���� == 72 || ���� == 97)
	{
		��ʱ��ɫ = ������ɫת��(0, 206, 209, 255);
	}
	else if (���� == 23 || ���� == 48 || ���� == 73 || ���� == 98)
	{
		��ʱ��ɫ = ������ɫת��(127, 255, 170, 255);
	}
	else if (���� == 24 || ���� == 49 || ���� == 74 || ���� == 99)
	{
		��ʱ��ɫ = ������ɫת��(0, 255, 127, 255);
	}
	else if (���� == 25 || ���� == 50 || ���� == 75 || ���� == 100)
	{
		��ʱ��ɫ = ������ɫת��(127, 255, 0, 255);
	}
	else
	{
		��ʱ��ɫ = ������ɫת��(255, 255, 0, 255);
	}
	return ��ʱ��ɫ;
}
FVector2D pos = { 100,100 };

const FVector2D FHD = { 1920.0f, 1080.0f };
const FVector2D RadarTo_FHD = { 1887.0f , 1054.0f };
constexpr static float RadarSizeNormal_FHD = 261.0f;
constexpr static float RadarSizeLarge_FHD = 461.0f;
const FVector2D RadarTo = { RadarTo_FHD.X / FHD.X , RadarTo_FHD.Y / FHD.Y };
const FVector2D RadarSizeNormal = { RadarSizeNormal_FHD / FHD.X, RadarSizeNormal_FHD / FHD.Y };
const FVector2D RadarFromNormal = { RadarTo.X - RadarSizeNormal.X , RadarTo.Y - RadarSizeNormal.Y };
const FVector2D RadarSizeLarge = { RadarSizeLarge_FHD / FHD.X, RadarSizeLarge_FHD / FHD.Y };
const FVector2D RadarFromLarge = { RadarTo.X - RadarSizeLarge.X, RadarTo.Y - RadarSizeLarge.Y };
float GetSpeedXYPerHour() { return  FVector(PubgData::GetVihecleSpeed(Game->MyPlayerAddress).X, PubgData::GetVihecleSpeed(Game->MyPlayerAddress).Y, 0.0f).Length() / 100.0f * 3.6f; }

VOID DrawCorneredBox(int X, int Y, int W, int H, const FLinearColor& color, int thickness) {

	float lineW = (W / 3);
	float lineH = (H / 3);


	//black outlines
	UCanvas::DrawLine(X, Y, X, Y + lineH,  3,FLinearColor(0.003921568627451, 0.003921568627451, 0.003921568627451,1));
	UCanvas::DrawLine(X, Y, X + lineW, Y, 3,FLinearColor(0.003921568627451, 0.003921568627451, 0.003921568627451, 1));
	UCanvas::DrawLine(X + W - lineW, Y, X + W, Y, 3,FLinearColor(0.003921568627451, 0.003921568627451, 0.003921568627451,1));
	UCanvas::DrawLine(X + W, Y, X + W, Y + lineH, 3,FLinearColor(0.003921568627451, 0.003921568627451, 0.003921568627451,1));
	UCanvas::DrawLine(X, Y + H - lineH, X, Y + H, 3,FLinearColor(0.003921568627451, 0.003921568627451, 0.003921568627451,1));
	UCanvas::DrawLine(X, Y + H, X + lineW, Y + H, 3,FLinearColor(0.003921568627451, 0.003921568627451, 0.003921568627451,1));
	UCanvas::DrawLine(X + W - lineW, Y + H, X + W, Y + H, 3,FLinearColor(0.003921568627451, 0.003921568627451, 0.003921568627451,1));
	UCanvas::DrawLine(X + W, Y + H - lineH, X + W, Y + H, 3,FLinearColor(0.003921568627451, 0.003921568627451, 0.003921568627451,1));


	//corners
	UCanvas::DrawLine(X, Y, X, Y + lineH, thickness, color);
	UCanvas::DrawLine(X, Y, X + lineW, Y, thickness, color);
	UCanvas::DrawLine(X + W - lineW, Y, X + W, Y, thickness, color);
	UCanvas::DrawLine(X + W, Y, X + W, Y + lineH, thickness, color);
	UCanvas::DrawLine(X, Y + H - lineH, X, Y + H, thickness, color);
	UCanvas::DrawLine(X, Y + H, X + lineW, Y + H, thickness, color);
	UCanvas::DrawLine(X + W - lineW, Y + H, X + W, Y + H, thickness, color);
	UCanvas::DrawLine(X + W, Y + H - lineH, X + W, Y + H, thickness, color);
}

void AddDrawItem(ULONG64 ItemPtr, FVector D2D, FLinearColor ItemColor, std::string ItemName) {


	IsOverlay(D2D);
	TempItemOverlayArr.push_back(D2D);
	if (off->Icon) {
		auto icon = Func::GetIconTexture(ItemPtr + offset_GetIconTexture);

		//UCanvas::DrawText(D2D.X, D2D.Y, ItemColor, Colo->��ɫ, true,"%p", icon);
		if (ValidPtr(icon))return;
		float size = 0.2;
		auto Xx = Read<int>(icon + offset_ImportedSize);
		auto Yy = Read<int>(icon + offset_ImportedSize + 4);
		UCanvas::K2_DrawTexture(icon, { D2D.X,D2D.Z }, FVector2D(Xx * size, Yy * size), FVector2D(), FVector2D(1, 1), FLinearColor(1, 1, 1, 1), EBlendMode::BLEND_Masked, 0.0f, FVector2D(1, 1));
	}

	UCanvas::DrawText(D2D.X, D2D.Y, ItemColor, Colo->��ɫ, true, ItemName.c_str());
}

void SetActorEnableCollision(ULONG64 Actor,bool bNewActorEnableCollision) {
	//SpoofCall<void>(Game->GameBase + offset_SetActorEnableCollision, Actor, bNewActorEnableCollision);
}

void SetEnableGravity(ULONG64 VehicleMesh, bool bGravityEnabled) {
	auto VTable = Read<PULONG64>(VehicleMesh);
	SpoofCall<void>(VTable[244], VehicleMesh, bGravityEnabled);
}

void SetAllPhysicsLinearVelocity(ULONG64 VehicleMesh, const struct FVector& NewVel ,bool bAddToCurrent) {
	auto VTable = Read<PULONG64>(VehicleMesh);
	SpoofCall<void>(VTable[189], VehicleMesh, NewVel, bAddToCurrent);
}

void SetAllPhysicsAngularVelocity(ULONG64 VehicleMesh, const struct FVector& NewAngVel, bool bAddToCurrent) {
	auto VTable = Read<PULONG64>(VehicleMesh);
	SpoofCall<void>(VTable[239], VehicleMesh, NewAngVel, bAddToCurrent);
}



//void GameHack::DrawMenu() {
//	if (!off->AntiScreen)return;
//	ZeroGUI::Input::Handle();
//	//char temp[0xFF] = {};
//	//sprintf_s(temp, "PUBG:%d/%d/%d/%d/%d/%d/%d"e, AntiScreenShotCount_Dx, AntiScreenShotCount_GDI, AntiScreenShotCount_CRC, AntiScreenShotCount_CRCb, dx�ж�, DX�������, DxCount);
//	/*UCanvas::DrawText(100, 100, Colo->��ɫ, Colo->��ɫ, false, "F5 ʵ��ɳ�[%s]"e, off->ʵ��ɳ� ? "����"e : "�ر�"e);
//	UCanvas::DrawText(100, 120, Colo->��ɫ, Colo->��ɫ, false, "F6 ������ײ[%s]"e, off->������ײ ? "����"e : "�ر�"e);
//	UCanvas::DrawText(100, 140, Colo->��ɫ, Colo->��ɫ, false, "���� �����ƶ��ٶ�[%d]"e, (int)off->Speed);
//	UCanvas::DrawText(100, 160, Colo->��ɫ, Colo->��ɫ, false, "���� ���������ٶ�[%d]"e, (int)off->UpDownSpeed);*/
//	if (Func::GetAsyncKeyState2(VK_F5) & 1)
//		off->ʵ��ɳ� = !off->ʵ��ɳ�;
//	else if (Func::GetAsyncKeyState2(VK_F6) & 1)
//		off->������ײ = !off->������ײ;
//
//	if (ZeroGUI::Window("������"e, &pos, FVector2D{ 585.0f, 350.0f }, off->Menu))
//	{
//		static int tab = 0;
//		if (ZeroGUI::ButtonTab("�Ӿ�"e, FVector2D{ 110, 25 }, tab == 0)) tab = 0;
//		if (ZeroGUI::ButtonTab("��׼"e, FVector2D{ 110, 25 }, tab == 1)) tab = 1;
//		if (ZeroGUI::ButtonTab("��Ʒ"e, FVector2D{ 110, 25 }, tab == 2)) tab = 2;
//		if (ZeroGUI::ButtonTab("��ɫ"e, FVector2D{ 110, 25 }, tab == 3)) tab = 3;
//		if (ZeroGUI::ButtonTab("����"e, FVector2D{ 110, 25 }, tab == 4)) tab = 4;
//		ZeroGUI::NextColumn(20.0f);
//
//		if (tab == 0) {
//			ZeroGUI::Text("Visuals"e, 15);
//
//			ZeroGUI::Checkbox("����"e, &off->Box); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("����"e, &off->Bone); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("����"e, &off->Name); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("Ѫ��"e, &off->Health);
//
//			ZeroGUI::Checkbox("����"e, &off->Distance); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("ɱ��"e, &off->Kill); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("��ս"e, &off->WatchCount); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("����"e, &off->Weapon);
//
//			ZeroGUI::Checkbox("ս��"e, &off->RankInfo); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("����"e, &off->Team); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("�ȼ�"e, &off->Level); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("�˺�"e, &off->Damage);
//
//			ZeroGUI::Checkbox("�״�"e, &off->Radar); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("����"e, &off->EyeLine); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("����ģʽ"e, &off->Debug);
//
//			ZeroGUI::SliderFloat("͸�Ӿ���"e, &off->ESPDistance, 100, 1000);
//		}
//		else if (tab == 1) {
//			ZeroGUI::Text("AimBot"e, 15);
//
//			ZeroGUI::Checkbox("����"e, &off->AimBot); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("��Χ"e, &off->DrawFov); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("©��"e, &off->MissHit); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("����"e, &off->Groggy);
//
//			ZeroGUI::Hotkey("����"e, FVector2D{ 100, 25 }, &off->AimKey); ZeroGUI::SameLine();
//
//			ZeroGUI::Combobox("������׼"e, FVector2D{ 100, 25 }, &off->AimPos, "ͷ��\0", "����\0", "�ز�\0", NULL);
//
//			ZeroGUI::SliderFloat("Fov"e, &off->AimFov, 1, 1000);
//			ZeroGUI::SliderFloat("�����ٶ�X"e, &off->AimSpeedX, 1, 100);
//			ZeroGUI::SliderFloat("�����ٶ�Y"e, &off->AimSpeedY, 1, 100);
//			ZeroGUI::SliderFloat("��׼����"e, &off->AimDistance, 100, 1000);
//		}
//		else if (tab == 2) {
//			ZeroGUI::Text("Item"e, 15);
//			ZeroGUI::Checkbox("����"e, &off->Vehicle); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("����"e, &off->Item);; ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("ͼ��"e, &off->Icon);; ZeroGUI::SameLine();
//			ZeroGUI::Text("~�� ս��"e);
//
//			ZeroGUI::Checkbox("�ӵ�"e, &off->Ammo); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("���"e, &off->Attach); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("Ͷ��"e, &off->Throw); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("Կ��"e, &off->Key);
//
//
//			ZeroGUI::Checkbox("��ǹ"e, &off->AR); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("��ǹ"e, &off->LMG); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("˨��"e, &off->SR); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("����"e, &off->DMR);
//
//
//			ZeroGUI::Checkbox("���"e, &off->SMG); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("����"e, &off->SG); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("����"e, &off->Special);  ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("ҩ��"e, &off->Heal);
//
//			ZeroGUI::Checkbox("ͷ��"e, &off->Head); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("����"e, &off->Armor); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("����"e, &off->Bag); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("����"e, &off->Other);
//
//			ZeroGUI::SliderFloat("��������"e, &off->VehicleDistance, 100, 1000);
//			ZeroGUI::SliderFloat("���ʾ���"e, &off->ItemDistance, 50, 150);
//		}
//		else if (tab == 3) {
//			ZeroGUI::Text("Color"e, 15);
//			ZeroGUI::ColorPicker("����ɼ���ɫ"e, &Colo->Box); ZeroGUI::SameLine();
//			ZeroGUI::ColorPicker("�����ϰ���ɫ"e, &Colo->NoBox);
//
//			ZeroGUI::ColorPicker("�����ɼ���ɫ"e, &Colo->Bone); ZeroGUI::SameLine();
//			ZeroGUI::ColorPicker("�����ϰ���ɫ"e, &Colo->NoBone);
//
//			ZeroGUI::ColorPicker("��Ϣ�ɼ���ɫ"e, &Colo->Info); ZeroGUI::SameLine();
//			ZeroGUI::ColorPicker("��Ϣ�ϰ���ɫ"e, &Colo->NoBox);
//
//			ZeroGUI::ColorPicker("Ԥ����ɫ"e, &Colo->AimBot); ZeroGUI::SameLine();
//			ZeroGUI::ColorPicker("������ɫ"e, &Colo->Vehicle);
//
//			ZeroGUI::ColorPicker("��ƷLv1��ɫ"e, &Colo->Lv1); ZeroGUI::SameLine();
//			ZeroGUI::ColorPicker("��ƷLv2��ɫ"e, &Colo->Lv2); ZeroGUI::SameLine();
//			ZeroGUI::ColorPicker("��ƷLv3��ɫ"e, &Colo->Lv3);
//			ZeroGUI::ColorPicker("��ƷLv4��ɫ"e, &Colo->Lv4); ZeroGUI::SameLine();
//			ZeroGUI::ColorPicker("��ƷLv5��ɫ"e, &Colo->Lv5);
//		}
//		else if (tab == 4) {
//
//			ZeroGUI::Text("����"e, 15);
//			ZeroGUI::Checkbox("���ﴩǽ"e, &off->���ﴩǽ); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("���ﴩ¥"e, &off->���ﴩ¥);
//			ZeroGUI::Checkbox("������ǹ"e, &off->������ǹ);
//			ZeroGUI::Checkbox("��������˵��"e, &off->�ɳ�˵��); ZeroGUI::SameLine();
//			ZeroGUI::SliderFloat("�ɳ��ٶ�"e, &off->Speed, 1000, 4500);
//			ZeroGUI::SliderFloat("�����ٶ�"e, &off->UpDownSpeed, 1000, 3000);
//		}
//
//	}
//	ZeroGUI::Render();//Custom Render. I use it for drawing Combobox and ColorPicker over the menu
//	ZeroGUI::Draw_Cursor(off->Menu);
//}



void GameHack::F����()
{
	if (Sss(VK_F1))		off->Display_Player = !off->Display_Player;//����

	if (off->Display_Player)
	{
		if (Func::GetAsyncKeyState2(VK_MENU) && off->Display_Player)
		{
			if (SSs(49))		off->Box = !off->Box;//����
			if (SSs(50))		off->Bone = !off->Bone;//����
			if (SSs(51))		off->Health = !off->Health;//Ѫ��
			if (SSs(52))		off->PlayerESP_Message = !off->PlayerESP_Message;//��Ϣ
			if (SSs(53))		off->WatchCount = !off->WatchCount;//��ս
			//if (SSs(49))		off->PlayerESP_Box = !off->PlayerESP_Box;
		}
	}

	if (off->Item)
	{
		if (Func::GetAsyncKeyState2(VK_LCONTROL) && off->Item)
		{
		
			if (SSs(53))		off->DroppedESP_Weapon = !off->DroppedESP_Weapon;//����
			if (SSs(54))		off->Heal = !off->Heal;//ҩƷ
			if (SSs(55))		off->Attach = !off->Attach;//���
			if (SSs(56))		off->Armor = !off->Armor;//����
			//if (SSs(57))		off->PlayerESP_gaunzhan = !off->PlayerESP_gaunzhan;//Ͷ��
			//if (SSs(58))		off->PlayerESP_gaunzhan = !off->PlayerESP_gaunzhan;//��ս
		}
	
	}
	if (Sss(VK_F3))		off->Vehicle = !off->Vehicle;//����
	if (Sss(VK_F4))		off->DroppedESP_hezi = !off->DroppedESP_hezi;//����
	if (Sss(VK_F5))		off->AimBot = !off->AimBot;//����
	if (Sss(VK_F6))		off->MissHit = !off->MissHit;//©��
	if (Sss(VK_F8))		off->DrawFov = !off->DrawFov;//��Χ
	if (Sss(VK_F9))		off->Groggy = !off->Groggy;//����
	//�������
	if (Func::GetAsyncKeyState2(33))//����PGip����
	{
		Sleep(25);
		if (off->AimDistance <= 1000) {
			off->AimDistance += 100;
		}
	}
	if (Func::GetAsyncKeyState2(34))//����Pgdn����
	{
		Sleep(25);
		if (off->AimDistance >= 200) {
			off->AimDistance -= 100;
		}
	}
	//͸�Ӿ���

	if (Func::GetAsyncKeyState2(39))//���ǡ�����
	{
		Sleep(25);
		if (off->ESPDistance < 1000) {
			off->ESPDistance += 100;
		}
	}
	if (Func::GetAsyncKeyState2(37))//���ǡ�����
	{
		Sleep(25);
		if (off->ESPDistance >= 200) {
			off->ESPDistance -= 100;

		}
	}

	//����XY������
	if (Func::GetAsyncKeyState2(38))//�����ϼ���
	{
		Sleep(25);
		if (off->AimSpeedX <= 500) {
			//off->AimSpeedX += 1;
			off->AimSpeedY += 1;
		}
	}
	if (Func::GetAsyncKeyState2(40))//�����ϼ���
	{
		Sleep(25);
		if (off->AimSpeedX >= 2) {
			//off->AimSpeedX -= 1;
			off->AimSpeedY -= 1;
		}
	}
	//����FOV��Χ
	if (Func::GetAsyncKeyState2(107))//����+����
	{
		Sleep(25);
		if (off->AimFov < 500) {

			off->AimFov += 10;
		}
	}
	if (Func::GetAsyncKeyState2(109))//����-����
	{
		Sleep(25);

		if (off->AimFov >= 20) {
			off->AimFov -= 10;
		}

	}

}

void ���ܿ���(int X, int Y, const char* text, bool Bool)
{
	if (Bool)
	{
		UCanvas::DrawText(X, Y, Colo->����, Colo->��ɫ, false, text, Bool);
		//UCanvas::DrawText(X + 165, Y, Colo->����, Colo->��ɫ, false, "��"e);
	}
	else
	{
		UCanvas::DrawText(X, Y, Colo->��ɫ_, Colo->��ɫ, false, text, Bool);
		//UCanvas::DrawText(X + 165, Y, Colo->��ɫ_, Colo->��ɫ, false, "��"e);
	}

}


void GameHack::F�˵�()
{
	float ��Ϸ��� = 20.0f;
	float �о� = 300;
	float ��� = 20.0f;

	if (off->Menu)
	{
		//UCanvas::DrawText(��Ϸ���, �о�, Colo->��ɫ_, Colo->��ɫ, false, "ʣ��: %d"e, Game->Time);
		//�о� += ���;
		//UCanvas::DrawText(��Ϸ���, �о�, Colo->��ɫ_, Colo->��ɫ, false, "�汾;21.2.5.9"e);
		//�о� += ���;
		UCanvas::DrawText(��Ϸ���, �о�, Colo->��ɫ_, Colo->��ɫ, false, "Home ��/���˵�"e);
		�о� += ���;
		���ܿ���(��Ϸ���, �о�, "[~] ս��ģʽ"e, off->qingshuang);
		�о� += ���;
		���ܿ���(��Ϸ���, �о�, "F1  ��ʾ����"e, off->Display_Player);
		�о� += ���;
		if (off->Display_Player)
		{
			���ܿ���(��Ϸ���, �о�, "|Alt+1  ����"e, off->Box);
			�о� += ���;
			���ܿ���(��Ϸ���, �о�, "|Alt+2  ����"e, off->Bone);
			�о� += ���;
			���ܿ���(��Ϸ���, �о�, "|Alt+3  Ѫ��"e, off->Health);
			�о� += ���;
			���ܿ���(��Ϸ���, �о�, "|Alt+4  ��Ϣ"e, off->PlayerESP_Message);
			�о� += ���;
			���ܿ���(��Ϸ���, �о�, "|Alt+5  ��ս"e, off->WatchCount);
			�о� += ���;
		}
		���ܿ���(��Ϸ���, �о�, "F2  ��ʾ��Ʒ"e, off->Item);
		�о� += ���;
		if (off->Item)
		{
			���ܿ���(��Ϸ���, �о�, "|Ctrl+5  ����"e, off->DroppedESP_Weapon);
			�о� += ���;
			���ܿ���(��Ϸ���, �о�, "|Ctrl+6  ҩƷ"e, off->Heal);
			�о� += ���;
			���ܿ���(��Ϸ���, �о�, "|Ctrl+7  ���"e, off->Attach);
			�о� += ���;
			���ܿ���(��Ϸ���, �о�, "|Ctrl+8  ����"e, off->Armor);
			�о� += ���;
		}
		���ܿ���(��Ϸ���, �о�, "F3  ��ʾ����"e, off->Vehicle);
		�о� += ���;
		���ܿ���(��Ϸ���, �о�, "F4  ��ʾ����"e, off->DroppedESP_hezi);
		�о� += ���;
		���ܿ���(��Ϸ���, �о�, "F5  Ԥ������"e, off->AimBot);
		�о� += ���;
		���ܿ���(��Ϸ���, �о�, "F6  ©�Ǵ���"e, off->MissHit);
		�о� += ���;
		���ܿ���(��Ϸ���, �о�, "F8  ���鷶Χ"e, off->DrawFov);
		�о� += ���;
		���ܿ���(��Ϸ���, �о�, "F9  ��������"e, off->Groggy);
		�о� += ���;
		UCanvas::DrawText(��Ϸ���, �о�, Colo->��ɫ_, Colo->��ɫ, false, "��������ƽ�� [%dm]"e, off->AimSpeedY);
		�о� += ���;
		UCanvas::DrawText(��Ϸ���, �о�, Colo->��ɫ_, Colo->��ɫ, false, "�� /������͸�Ӿ��� [%dm]"e, off->ESPDistance);
		�о� += ���;
		UCanvas::DrawText(��Ϸ���, �о�, Colo->��ɫ_, Colo->��ɫ, false, "PgUp /PgDn����������� [%dm]"e, off->AimDistance);
		�о� += ���;
		UCanvas::DrawText(��Ϸ���, �о�, Colo->��ɫ_, Colo->��ɫ, false, "+ / - �������鷶Χ [%dm]"e, off->AimFov);
		�о� += ���;
		UCanvas::DrawText(��Ϸ���, �о�, Colo->��ɫ_, Colo->��ɫ, false, "Shift������������"e);
	}


}




void GameHack::DrawESP() {
	UserInfo.Update();
	Game->UWorld = PubgData::GetWorld();
	if (ValidPtr(Game->UWorld))return;

	auto GameInstance = PubgData::GetGameInstance(Game->UWorld);
	if (ValidPtr(GameInstance))return;

	auto LocalPlayers = PubgData::GetLocalPlayer(GameInstance);
	if (ValidPtr(LocalPlayers))return;

	auto PlayerController = PubgData::GetPlayerController(LocalPlayers);
	if (ValidPtr(PlayerController))return;

	auto TslBaseHUD = Read<ULONG64>(PlayerController + offset_MyHUD);

	Game->PlayerCameraManager = PubgData::GetPlayerCameraManager(PlayerController);
	if (ValidPtr(Game->PlayerCameraManager))return;

	Game->FOV = Read<float>(Game->PlayerCameraManager + offset_CameraFOV);
	Game->Location = Read<FVector>(Game->PlayerCameraManager +  offset_CameraLocation);
	Game->Rotation = Read<FRotator>(Game->PlayerCameraManager + offset_CameraRotation);
	auto AcknowledgedPawn = PubgData::GetAcknowledgedPawn(PlayerController);
	if (ValidPtr(AcknowledgedPawn))return;



	bool IsFPPOnly = false;
	const auto MyHash = PubgData::GetNameHash(PubgData::GetNameIndex(AcknowledgedPawn));
	if (IsPlayerCharacter(MyHash)) {
		Game->MyPlayerAddress = AcknowledgedPawn;
		auto AnimScriptInstance = Read<ULONG64>(PubgData::GetMesh(AcknowledgedPawn) + offset_AnimScriptInstance);
		if (AnimScriptInstance)
			IsFPPOnly = Read<bool>(AnimScriptInstance + offset_bLocalFPP_CP);
	}
	else if (MyHash == "DefaultPawn"h) {
		Game->MyPlayerAddress = NULL;
		return;
	}
	if (off->AimBot && off->DrawFov && off->AntiScreen && !bWorldMap)
		UCanvas::DrawCircle(Game->ScreenCenter.X, Game->ScreenCenter.Y, off->AimFov, 50, Colo->��ɫ);

	float currentcenterDistance;
	float currentDistance = NULL;
	auto CurrentLevel = PubgData::GetCurrentLevel(Game->UWorld);
	if (!CurrentLevel)return;
	
	Game->Actor = PubgData::GetActor(CurrentLevel);
	if (ValidPtr(Game->Actor))return;

	auto ActorArray = Read<ULONG64>(Game->Actor);
	auto ActorCount = Read<ULONG>(Game->Actor + sizeof(PVOID));
	if (ValidPtr(ActorArray) || ActorCount < 30 || ActorCount > 20000) return;
	PubgData::EnumAllWidget(TslBaseHUD);

	//UCanvas::DrawText(100, 500, Colo->��ɫ, Colo->��ɫ, false, "UWorld->%p"e, Game->UWorld);
	//UCanvas::DrawText(100, 520, Colo->��ɫ, Colo->��ɫ, false, "GameInstance->%p"e, GameInstance);
	//UCanvas::DrawText(100, 540, Colo->��ɫ, Colo->��ɫ, false, "LocalPlayers->%p"e, LocalPlayers);
	//UCanvas::DrawText(100, 560, Colo->��ɫ, Colo->��ɫ, false, "MapName->%s"e, PubgData::GetName(PubgData::GetNameIndex(Game->UWorld)).c_str());
	//UCanvas::DrawText(100, 580, Colo->��ɫ, Colo->��ɫ, false, "PlayerController->%p"e, PlayerController);
	//UCanvas::DrawText(100, 150, Colo->��ɫ, Colo->��ɫ, false, "AcknowledgedPawn->%p"e, AcknowledgedPawn);
	//UCanvas::DrawText(100, 600, Colo->��ɫ, Colo->��ɫ, false, "PlayerCameraManager->%p"e, Game->PlayerCameraManager);

	//UCanvas::DrawText(100, 620, Colo->��ɫ, Colo->��ɫ, false, "MyPlayerAddress->%p"e, Game->MyPlayerAddress);
	//UCanvas::DrawText(100, 640, Colo->��ɫ, Colo->��ɫ, false, "CurrentLevel->%p"e, CurrentLevel);
	//UCanvas::DrawText(100, 660, Colo->��ɫ, Colo->��ɫ, false, "Actor->%p"e, Game->Actor);
	//UCanvas::DrawText(100, 680, Colo->��ɫ, Colo->��ɫ, false, "ActorArray->%p"e, ActorArray);
	//UCanvas::DrawText(100, 700, Colo->��ɫ, Colo->��ɫ, false, "ActorCount->%d"e, ActorCount);
	//UCanvas::DrawText(100, 200, Colo->��ɫ, Colo->��ɫ, false, "AcknowledgedPawn��%p"e, AcknowledgedPawn);





	auto MapNameHash = PubgData::GetNameHash(PubgData::GetNameIndex(Game->UWorld));
	float MapSize = 0.0f;
	if (MapNameHash == "Tiger_Main"h || MapNameHash == "Desert_Main"h || MapNameHash == "Kiki_Main"h)
		MapSize = 408000.f;
	else if (MapNameHash == "Range_Main"h)
		MapSize = 101175.f;
	else if (MapNameHash == "Baltic_Main"h)
		MapSize = 406387.5;
	else if (MapNameHash == "Heaven_Main"h)
		MapSize = 51420.f;
	else if (MapNameHash == "Savage_Main"h)
		MapSize = 202387.5f;
	else if (MapNameHash == "DihorOtok_Main"h)
		MapSize = 306050.f;
	else if (MapNameHash == "Chimera_Main"h)
		MapSize = 152950.f;

	TempItemOverlayArr.clear();
	for (auto i = 0; i < ActorCount; i++)
	{
		auto Actor = Read<ULONG64>(ActorArray + i * sizeof(PVOID));
		if (!Actor || !Game->MyPlayerAddress)continue;
		auto ActorNameHash = PubgData::GetNameHash(PubgData::GetNameIndex(Actor));



		//DrawPlayer
		[&] {
			if (IsPlayerCharacter(ActorNameHash) || IsAICharacter(ActorNameHash)) {
				auto Health = PubgData::GetHealth(Actor);
				auto GroggyHealth = PubgData::GetHealthDie(Actor);
				if (Health <= 0.0f && GroggyHealth <= 0.0f) return;

				auto Mesh = PubgData::GetMesh(Actor);
				if (ValidPtr(Mesh))return;
				auto ActorLocation = PubgData::GetPos(Actor);
				const float Distance = Game->Location.Distance(ActorLocation) / 100.0f;
				PlayerInfo Info = PubgData::GetPlayerInfo(Actor);
				Info.PlayerTeamID = Info.PlayerTeamID >= 100000 || Info.PlayerTeamID == 100000 ? Info.PlayerTeamID = Info.PlayerTeamID - 100000 : Info.PlayerTeamID;
				auto Weapon = PubgData::GetTslWeaponA(Actor);
				auto CharacterState = Read<ECharacterState>(Actor + offset_CharacterState);
				std::map<unsigned, tUserInfo>& UserInfoMap = *[&] {
					const bool bSolo = !(Info.PlayerTeamID < 200);
					if (IsFPPOnly && !bSolo)
						return &UserInfo.InfoSteamSquadFPP;
					if (!IsFPPOnly && bSolo)
						return &UserInfo.InfoSteamSolo;
					if (!IsFPPOnly && !bSolo)
						return &UserInfo.InfoSteamSquad;
					return &UserInfo.InfoEmpty;
				}();
				UserInfo.AddUser(Info.PlayerName);
				const std::string InfoStr = [&]() -> std::string {
					const unsigned NameHash = CompileTime::StrHash(Info.PlayerName);
					if (!UserInfoMap.contains(NameHash))
						return "?"e;

					auto& UserInfo = UserInfoMap[NameHash];
					if (!UserInfo.bExist)
						return "0"e;

					return sformat((const char*)"{:.1f} {} {:.1f} {:.0f}"e, UserInfo.AvgKda, UserInfo.rankPoint, UserInfo.AvgKills, UserInfo.AvgDmg);
				}();
				//if (!ValidPtr(PubgData::XeDecryption(Read<ULONG64>(Actor + offset_LastTeamNum - 8))) && off->AntiScreen) {
				//	int SquadIndex = PubgData::GetSquadMemberIndex(Actor);
				//	UCanvas::DrawText(20, 20 + SquadIndex * 15, Colo->��ɫ_, Colo->��ɫ, false, "%s L:%d W:%d K:%d D:%.0f (%s)"e, Info.PlayerName.c_str(), Info.PlayerSurvivalLevel, Info.PlayerWatchCount, Info.PlayerNumKill, Info.PlayerDamageDealtOnEnemy, InfoStr.c_str());
				//	return;
				//}
				if (Actor == Game->MyPlayerAddress)return;

				auto TeamColor = GetTeamCrolor(Info.PlayerTeamID);
				auto AimOffsets = Read<FRotator>(Actor + offset_AimOffsets);
				constexpr float Size = 8.0f;
				if (bWorldMap) {
					auto map = PubgData::DrawMap(ActorLocation, MapSize);
					FVector GunDir = FRotator(0.0f, AimOffsets.Yaw, 0.0f).GetUnitVector();

					float Degree90 = ConvertToRadians(90.0f);
					FVector Dir1 = {
						GunDir.X * cosf(Degree90) - GunDir.Y * sinf(Degree90),
						GunDir.X * sinf(Degree90) + GunDir.Y * cosf(Degree90),
						0.0f };

					FVector Dir2 = {
						GunDir.X * cosf(-Degree90) - GunDir.Y * sinf(-Degree90),
						GunDir.X * sinf(-Degree90) + GunDir.Y * cosf(-Degree90),
						0.0f };
					auto RadarScreenPos = FVector(map.X, map.Y, 0);
					UCanvas::SetCanvas(UCanvas::DebugCanvas);
					for (size_t i = 0; i < 3; i++)
					{
						FVector p1 = RadarScreenPos + GunDir * (Size - i) * 2.0f;
						FVector p2 = RadarScreenPos + Dir1 * (Size - i);
						FVector p3 = RadarScreenPos + Dir2 * (Size - i);

						UCanvas::DrawLine(p1.X, p1.Y, p2.X, p2.Y, 2, TeamColor);
						UCanvas::DrawLine(p2.X, p2.Y, p3.X, p3.Y, 2, TeamColor);
						UCanvas::DrawLine(p3.X, p3.Y, p1.X, p1.Y, 2, TeamColor);
					}
					if (CharacterState == ECharacterState::Fire)
						UCanvas::DrawLine(map.X, map.Y, map.X + AimOffsets.GetUnitVector().X * 200.0f, map.Y + AimOffsets.GetUnitVector().Y * 200.0f, 1, Colo->����);

					UCanvas::DrawFillCircle(map.X, map.Y, Size, TeamColor);
					UCanvas::DrawText(map.X, map.Y, Colo->��ɫ, Colo->��ɫ, true,  "%d"e, Info.PlayerTeamID);
					UCanvas::SetCanvas(UCanvas::DebugCanvas);
					//return;
				}
				
				if (1) {
				
					const float SpeedPerHour = GetSpeedXYPerHour();
					float RadarDistance =
						SpeedPerHour < 30.0f ? 200.0f :
						SpeedPerHour < 70.0f ? 250.0f :
						SpeedPerHour < 95.0f ? 300.0f :
						400.0f;
					if (bRadarExtended)
						RadarDistance *= RadarSizeLarge_FHD / RadarSizeNormal_FHD;
					if (Distance <= RadarDistance) {

						const FVector2D RadarSize = bRadarExtended ? RadarSizeLarge : RadarSizeNormal;
						const FVector2D RadarFrom = bRadarExtended ? RadarFromLarge : RadarFromNormal;
						const FVector RadarPos = (ActorLocation - Game->Location) * 0.01f;
						const FVector RadarScreenPos = {
							RadarFrom.X * (Game->ScreenCenter.X * 2) + ((1.0f + RadarPos.X / RadarDistance) * RadarSize.X / 2.0f) * (Game->ScreenCenter.X * 2),
							RadarFrom.Y * (Game->ScreenCenter.Y * 2) + ((1.0f + RadarPos.Y / RadarDistance) * RadarSize.Y / 2.0f) * (Game->ScreenCenter.Y * 2),
							0.0f
						};
						FVector GunDir = FRotator(0.0f, AimOffsets.Yaw, 0.0f).GetUnitVector();

						float Degree90 = ConvertToRadians(90.0f);
						FVector Dir1 = {
							GunDir.X * cosf(Degree90) - GunDir.Y * sinf(Degree90),
							GunDir.X * sinf(Degree90) + GunDir.Y * cosf(Degree90),
							0.0f };

						FVector Dir2 = {
							GunDir.X * cosf(-Degree90) - GunDir.Y * sinf(-Degree90),
							GunDir.X * sinf(-Degree90) + GunDir.Y * cosf(-Degree90),
							0.0f };

						UCanvas::SetCanvas(UCanvas::DebugCanvas);
						for (size_t i = 0; i < 3; i++)
						{
							FVector p1 = RadarScreenPos + GunDir * (Size - i) * 2.0f;
							FVector p2 = RadarScreenPos + Dir1 * (Size - i);
							FVector p3 = RadarScreenPos + Dir2 * (Size - i);
																	  
							UCanvas::DrawLine(p1.X, p1.Y, p2.X, p2.Y, 2, TeamColor);
							UCanvas::DrawLine(p2.X, p2.Y, p3.X, p3.Y, 2, TeamColor);
							UCanvas::DrawLine(p3.X, p3.Y, p1.X, p1.Y, 2, TeamColor);
						}											  

			

						if (CharacterState == ECharacterState::Fire)
							UCanvas::DrawLine(RadarScreenPos.X, RadarScreenPos.Y, RadarScreenPos.X + AimOffsets.GetUnitVector().X * 200.0f, RadarScreenPos.Y + AimOffsets.GetUnitVector().Y * 200.0f, 1, Colo->����);
						UCanvas::DrawFillCircle(RadarScreenPos.X, RadarScreenPos.Y, Size, TeamColor);
						UCanvas::DrawText(RadarScreenPos.X, RadarScreenPos.Y, Colo->��ɫ, Colo->��ɫ, true,  "%d"e, Info.PlayerTeamID);
						UCanvas::SetCanvas(UCanvas::DebugCanvas);

					}
				}
				if (off->ESPDistance < Distance) return;

				FVector HeadLoc, FootLoc;
				FVector2D HeadScreen, FootScreen;
				if (!PubgData::GetBoneMatrix(Mesh, &HeadLoc, forehead) || !PubgData::GetBoneMatrix(Mesh, &FootLoc, root))return;
				HeadLoc.Z += 15;
				FootLoc.Z -= 10;
				if (off->Radar && off->AntiScreen)
					���Ʊ�ʶ(Game->Rotation, Game->Location, HeadLoc, 200);

				if (!PubgData::WorldToScreen(HeadLoc, HeadScreen) || !PubgData::WorldToScreen(FootLoc, FootScreen))return;
				if (off->EyeLine) {
					auto Rotation = Read<FRotator>(Actor + offset_AimOffsets);
					FVector TempD3D = HeadLoc;
					constexpr float Dis = 10000.F;
					TempD3D.X += cos(Rotation.Yaw * M_PI / 180) * Dis;
					TempD3D.Y += sin(Rotation.Yaw * M_PI / 180) * Dis;
					TempD3D.Z += sin(Rotation.Pitch * M_PI / 180) * Dis;
					FVector2D Sc2;
					FHitResult HitResult;
					Func::LineTraceSingle(HeadLoc, TempD3D, &HitResult);
					if (HitResult.ImpactPoint != FVector(0, 0, 0) && HitResult.ImpactPoint != TempD3D) {
						if (PubgData::WorldToScreen(HitResult.ImpactPoint, Sc2))
							UCanvas::DrawLine(HeadScreen.X, HeadScreen.Y, Sc2.X, Sc2.Y, 1.5f, Colo->��ɫ);
					}
				}
				float H = FootScreen.Y - HeadScreen.Y;
				float W = H / 2.f;
				float X = HeadScreen.X - W / 2.f;
				float Y = HeadScreen.Y;
				auto IsAim = LastAimPlayer == Actor;
				auto IsVisible = Func::LineTraceSingle(Game->Location, HeadLoc);
				if (off->Box && off->AntiScreen) {//���Ʒ���
					float CornerHeight = abs(HeadScreen.Y - FootScreen.Y);
					float CornerWidth = CornerHeight * 0.5; //0.5
					DrawCorneredBox(HeadScreen.X - (CornerWidth / 2), HeadScreen.Y, CornerWidth, CornerHeight, IsAim ? Colo->AimBot : IsVisible ? Colo->Box : Colo->NoBox, 1.0f);
					//UCanvas::DrawRect(HeadScreen.X - (CornerWidth / 2), HeadScreen.Y, CornerWidth, CornerHeight, 1.0f, IsAim ? Colo->AimBot : IsVisible ? Colo->Box : Colo->NoBox);
				}
				if (off->Bone && Distance < 500.0f && off->AntiScreen)//���ƹ���
					Drawbone(Mesh, IsAim ? Colo->AimBot : Colo->Bone, Colo->NoBone);

				if (off->Health && off->AntiScreen) {//����Ѫ��
					float DrawW = W < 40 ? 40 : W;
					float DHealth = DrawW *  (Health <= 0 ? GroggyHealth : Health) / 100;
					UCanvas::DrawFilled(X + W / 2 - DrawW / 2, Y - 7, DHealth, 5, Health <= 0 ? Colo->��ɫ : Health <= 30 ? Colo->��ɫ : Health <= 70 ? Colo->�Ȼ� : Colo->��ɫ_);
					UCanvas::DrawRect(X + W / 2 - DrawW / 2, Y - 7, DrawW, 5, 1, Colo->��ɫ);
				}
				std::string Line;
				std::string LineLL;
				std::string PlayerInfo;
				std::string PlayerInfoLL;

				if (off->PlayerESP_Message) {
					if (IsAICharacter(ActorNameHash))
						Line += (std::string)"AI������"e;
					else if (Info.PlayerName.size() > 6)
						Line += Info.PlayerName.substr(0, 6) + (std::string)""e;
					else
						Line += Info.PlayerName;
				}
				if (Line.size())
					Line += (std::string)" ��:"e;
				if (off->PlayerESP_Message)
					Line += std::to_string(Info.PlayerSurvivalLevel);
				
				if (Line.size())
					Line += (std::string)" ��:"e;
				if (off->PlayerESP_Message)
					Line += std::to_string(Info.PlayerTeamID);
				
				//if (off->PlayerESP_Message)
				//	Line += std::string("("e) + InfoStr + std::string(")"e);
			
				if (Line.size()) {
					PlayerInfo += Line;
					PlayerInfo += (std::string)"\n"e;
					Line = {};
				}
				if (off->PlayerESP_Message) {
					if (Weapon) {
						auto icon = Read<ULONG64>(Weapon + offset_WeaponIcon);
						if (!ValidPtr(icon)) {
							auto size = 0.2;
							auto Xx = Read<int>(icon + offset_ImportedSize);
							auto Yy = Read<int>(icon + offset_ImportedSize + 4);
							UCanvas::K2_DrawTexture(icon, FVector2D(X + W / 2 - Xx * size / 2, Y - Yy * size - 10), FVector2D(Xx* size, Yy* size), FVector2D(0, 0), FVector2D(1, 1), FLinearColor(1.0f, 1.0f, 1.0f, 1.0f), EBlendMode::BLEND_Masked, Read<float>(Weapon + offset_WeaponIcon + 8), FVector2D(1, 1));

						}
					}
					//Line += Info.PlayerWeaponName;
				}
				if (Line.size()) {
					PlayerInfo += Line;
					PlayerInfo += (std::string)"\n"e;
					Line = {};
				}
				
				if (off->PlayerESP_Message)
					Line += std::to_string((int)Distance) + (std::string)"M"e;
				if (Line.size())
					Line += (std::string)" "e;
				if (off->PlayerESP_Message && Info.PlayerNumKill > 0)
					Line += std::to_string(Info.PlayerNumKill) + (std::string)"K"e;
				if (Line.size())
					Line += (std::string)" "e;
				if (off->PlayerESP_Message && Info.PlayerWatchCount > 0)
					Line += std::to_string(Info.PlayerWatchCount) + (std::string)"W"e;
				if (Line.size())
					Line += (std::string)" "e;
				if (off->PlayerESP_Message && Info.PlayerDamageDealtOnEnemy > 0)
					Line += std::to_string((int)Info.PlayerDamageDealtOnEnemy) + (std::string)"D"e;
				if (Line.size()) {
					PlayerInfo += Line;
					PlayerInfo += (std::string)"\n"e;
					Line = {};
				}

				if (Distance > 150.0f && off->AntiScreen)
					UCanvas::DrawText(HeadScreen.X, HeadScreen.Y + H + 3, IsVisible ? Colo->Info : Colo->NoInfo, Colo->��ɫ, true, PlayerInfo.c_str());
				else if(off->AntiScreen)
					UCanvas::DrawText(HeadScreen.X, HeadScreen.Y + H + 3, IsVisible ? Colo->Info : Colo->NoInfo, Colo->��ɫ, true, PlayerInfo.c_str());

				GEDistance = (int)Distance;
				if (IsLock == false && off->AimBot && ((int)Distance) < off->AimDistance) {
					if (!off->Groggy && Health <= 0.0f && GroggyHealth > 0.0f) return;
					if (PubgData::InsideCircle(HeadScreen.X, HeadScreen.Y, off->AimFov, Game->ScreenCenter.X, Game->ScreenCenter.Y)) {
						currentcenterDistance = Get2DDis(HeadScreen, Game->ScreenCenter.X, Game->ScreenCenter.Y);
						if (currentDistance == NULL) {
							currentDistance = currentcenterDistance;
							AimPlayer = Actor;
						}
						else if (currentcenterDistance < currentDistance) {
							currentDistance = currentcenterDistance;
							AimPlayer = Actor;
						}
					}
				}
			}
		}();
		if (bWorldMap)
			continue;
		
		//DrawAircraft
		[&] {
			auto ActorName = PubgData::GetName(PubgData::GetNameIndex(Actor));
			auto bAircraftCarePackage = (ActorName.substr(0, sizeof("AircraftCarePackage"e) - 1) == (std::string)"AircraftCarePackage"e);
			if (!bAircraftCarePackage || !off->AntiScreen)
				return;

			auto ActorLocation = PubgData::GetPos(Actor);
			const float Distance = Game->Location.Distance(ActorLocation) / 100.0f;
			FVector2D ActorLocationScreen;
			if (!PubgData::WorldToScreen(ActorLocation, ActorLocationScreen))return;

			auto Output = sformat((const char*)"{}\n{}M"e, (const char*)"�ɻ�"e, (unsigned)Distance);
			UCanvas::DrawText(ActorLocationScreen.X, ActorLocationScreen.Y, Colo->�Ȼ�, Colo->��ɫ, true, Output.c_str());

		}();
		//DrawObject
		[&] {
			auto ObjectInfo = GetObjectInfo(ActorNameHash);
			auto& ObjectName = ObjectInfo.Name;
			if (!ObjectName[0] || !off->AntiScreen)
				return;

			auto ActorLocation = PubgData::GetPos(Actor);
			const float Distance = Game->Location.Distance(ActorLocation) / 100.0f;

			if (!ObjectInfo.IsLong || Distance > 300.0f)
				return;

			FVector2D ActorLocationScreen;
			if (!PubgData::WorldToScreen(ActorLocation, ActorLocationScreen))return;

			auto Output = sformat((const char*)"{}\n{}M"e, ObjectName.data(), (unsigned)Distance);
			UCanvas::DrawText(ActorLocationScreen.X, ActorLocationScreen.Y, Colo->��ɫ, Colo->��ɫ, true, Output.c_str());
		}();
		if (off->qingshuang || !off->AntiScreen)continue;
		//DrawVehicle
		[&] {
			if (!off->Vehicle)return;
			auto VehicleInfo = GetVehicleInfo(ActorNameHash);
			auto& VehicleName = VehicleInfo.Name;
			if (!VehicleName[0])
				return;
			float Health = 100.0f;
			float HealthMax = 100.0f;
			float Fuel = 100.0f;
			float FuelMax = 100.0f;
			switch (VehicleInfo.Type1) {
			case VehicleType1::Wheeled:
			{
				auto VehicleCommonComponent = Read<ULONG64>(Actor + offset_WheeledVehicleCommonComponent);
				//printf("WheeledVehicleCommonComponent:%llX\n", VehicleCommonComponent);

				if (ValidPtr(VehicleCommonComponent))
					
					break;

				Health = Read<float>(VehicleCommonComponent + offset_VehicleHealth);
				HealthMax = Read<float>(VehicleCommonComponent + offset_VehicleHealthMax);

				Fuel = Read<float>(VehicleCommonComponent + offset_VehicleFuel);
				FuelMax = Read<float>(VehicleCommonComponent + offset_VehicleFuelMax);
				break;
			}
			case VehicleType1::Floating:
			{
				auto VehicleCommonComponent = Read<ULONG64>(Actor + offset_FloatingVehicleCommonComponent);
			//	printf("FloatingVehicleCommonComponent:%llX\n", VehicleCommonComponent);

				if (ValidPtr(VehicleCommonComponent))
					break;

				Health = Read<float>(VehicleCommonComponent + offset_VehicleHealth);
				HealthMax = Read<float>(VehicleCommonComponent + offset_VehicleHealthMax);
				Fuel = Read<float>(VehicleCommonComponent + offset_VehicleFuel);
				FuelMax = Read<float>(VehicleCommonComponent + offset_VehicleFuelMax);
				break;
			}
			}
			if (ActorNameHash == "BP_LootTruck_C"h && Health <= 0.0f)
				return;
			bool IsDestructible = (VehicleInfo.Type2 == VehicleType2::Destructible);
			FLinearColor Color = Colo->Vehicle;
			if (VehicleInfo.Type3 == VehicleType3::Special)
				Color = Colo->����;
			if (Health <= 0.0f || Fuel <= 0.0f)
				Color = Colo->��ɫ;
			auto ActorLocation = PubgData::GetPos(Actor);
			const float Distance = Game->Location.Distance(ActorLocation) / 100.0f;
			if (off->VehicleDistance < Distance) return;
			FVector2D ActorLocationScreen;
			if (!PubgData::WorldToScreen(ActorLocation, ActorLocationScreen))return;
			auto Output = sformat((const char*)"{} {}M"e, VehicleName.data(), (unsigned)Distance);
			UCanvas::DrawText(ActorLocationScreen.X, ActorLocationScreen.Y, Color, Colo->��ɫ, true, Output.c_str());
			UCanvas::SetCanvas(UCanvas::DebugCanvas);

			//Draw vehicle health, fuel
			[&] {
				UCanvas::SetCanvas(UCanvas::DebugCanvas);
				if (!IsDestructible || Health <= 0.0f)
					return;

				float DrawW = 60;
				float DHealth = DrawW * Health / HealthMax;

				UCanvas::DrawFilled(ActorLocationScreen.X - DrawW / 2, ActorLocationScreen.Y + 15, DHealth, 5, Colo->��ɫ_);
				UCanvas::DrawRect(ActorLocationScreen.X - DrawW / 2, ActorLocationScreen.Y + 15, DrawW, 5, 1, Colo->��ɫ);

				float DFuel = DrawW * Fuel / FuelMax;
				UCanvas::DrawFilled(ActorLocationScreen.X - DrawW / 2, ActorLocationScreen.Y + 20, DFuel, 5, Colo->����);
				UCanvas::DrawRect(ActorLocationScreen.X - DrawW / 2, ActorLocationScreen.Y + 20, DrawW, 5, 1, Colo->��ɫ);
				UCanvas::SetCanvas(UCanvas::DebugCanvas);
			}();
		}();
		if (!off->Item)continue;
		auto DrawItem = [&](ULONG64 ItemPtr, FVector2D ItemLocation, bool IsBox = false) {
			auto ItemInformationComponent = Read<ULONG64>(ItemPtr + offset_ItemInformationComponent);
			if (ValidPtr(ItemInformationComponent))return false;
			auto Id = Read<ULONG>(ItemInformationComponent + offset_ItemID);
			if (Id <= 0)return false;
			auto Hash = PubgData::GetNameHash(Id);
			auto ItemInfo = GetItemInfo(Hash);
			if (ItemInfo.Name.empty())return false;

		//	UCanvas::DrawText(ItemLocation.X, ItemLocation.Y + 20, Colo->��ɫ, Colo->��ɫ, true, "%llX"e, ItemPtr); //�����Ʒ��ַ

			std::string ItemName = off->Debug ? PubgData::GetName(Id) : ItemInfo.Name;
			FLinearColor ItemColor = [&] {
				switch (ItemInfo.ItemPriority) {
				case 1: return Colo->Lv1;
				case 2: return Colo->Lv2;
				case 3: return Colo->Lv3;
				case 4: return Colo->Lv4;
				case 5: return Colo->Lv5;
				default:return Colo->��ɫ;
				}
			}();
			if (!IsBox) {
				FVector D2D = { ItemLocation.X,ItemLocation.Y,ItemLocation.Y };
				if (off->Debug) {
					//UCanvas::DrawText(100, 500, Colo->��ɫ, Colo->��ɫ, false, "UWorld->%p"e, Game->UWorld);
					//UCanvas::DrawText(100, 520, Colo->��ɫ, Colo->��ɫ, false, "GameInstance->%p"e, GameInstance);
					//UCanvas::DrawText(100, 540, Colo->��ɫ, Colo->��ɫ, false, "LocalPlayers->%p"e, LocalPlayers);
					//UCanvas::DrawText(100, 560, Colo->��ɫ, Colo->��ɫ, false, "MapName->%s"e, PubgData::GetName(PubgData::GetNameIndex(Game->UWorld)).c_str());
					//UCanvas::DrawText(100, 580, Colo->��ɫ, Colo->��ɫ, false, "PlayerController->%p"e, PlayerController);
					//UCanvas::DrawText(100, 150, Colo->��ɫ, Colo->��ɫ, false, "AcknowledgedPawn->%p"e, AcknowledgedPawn);
					//UCanvas::DrawText(100, 600, Colo->��ɫ, Colo->��ɫ, false, "PlayerCameraManager->%p"e, Game->PlayerCameraManager);

					//UCanvas::DrawText(100, 620, Colo->��ɫ, Colo->��ɫ, false, "MyPlayerAddress->%p"e, Game->MyPlayerAddress);
					//UCanvas::DrawText(100, 640, Colo->��ɫ, Colo->��ɫ, false, "CurrentLevel->%p"e, CurrentLevel);
					//UCanvas::DrawText(100, 660, Colo->��ɫ, Colo->��ɫ, false, "Actor->%p"e, Game->Actor);
					//UCanvas::DrawText(100, 680, Colo->��ɫ, Colo->��ɫ, false, "ActorArray->%p"e, ActorArray);
					//UCanvas::DrawText(100, 700, Colo->��ɫ, Colo->��ɫ, false, "ActorCount->%d"e, ActorCount);

					UCanvas::DrawText(ItemLocation.X, ItemLocation.Y, Colo->�Ȼ�, Colo->��ɫ, true, ItemName.c_str());
				}
				else if (ItemInfo.Type == 1 && off->Attach)//�������
				{
					AddDrawItem(ItemPtr, D2D, ItemColor, ItemName);
				}
				else if (ItemInfo.Type == 2 && off->Throw)//����Ͷ����
				{
					AddDrawItem(ItemPtr, D2D, ItemColor, ItemName);
				}
				else if (ItemInfo.Type == 3 && off->Bag)
				{
					AddDrawItem(ItemPtr, D2D, ItemColor, ItemName);
				}
				else if (ItemInfo.Type == 4 && off->DroppedESP_Weapon)
				{
					AddDrawItem(ItemPtr, D2D, ItemColor, ItemName);
				}
				else if (ItemInfo.Type == 5 && off->DroppedESP_Weapon)
				{
					AddDrawItem(ItemPtr, D2D, ItemColor, ItemName);
				}
				else if (ItemInfo.Type == 6 && off->DroppedESP_Weapon)
				{
					AddDrawItem(ItemPtr, D2D, ItemColor, ItemName);
				}
				else if (ItemInfo.Type == 7 && off->DroppedESP_Weapon)
				{
					AddDrawItem(ItemPtr, D2D, ItemColor, ItemName);
				}
				else if (ItemInfo.Type == 8 && off->DroppedESP_Weapon)
				{
					AddDrawItem(ItemPtr, D2D, ItemColor, ItemName);
				}
				else if (ItemInfo.Type == 9 && off->Head)
				{
					AddDrawItem(ItemPtr, D2D, ItemColor, ItemName);
				}
				else if (ItemInfo.Type == 10 && off->DroppedESP_Weapon)
				{
					AddDrawItem(ItemPtr, D2D, ItemColor, ItemName);
				}
				else if (ItemInfo.Type == 11 && off->Special)
				{
					AddDrawItem(ItemPtr, D2D, ItemColor, ItemName);
				}
				else if (ItemInfo.Type == 12 && off->Armor)
				{
					AddDrawItem(ItemPtr, D2D, ItemColor, ItemName);
				}
				else if (ItemInfo.Type == 13 && off->Heal)
				{
					AddDrawItem(ItemPtr, D2D, ItemColor, ItemName);
				}
				else if (ItemInfo.Type == 14 && off->Key)
				{
					AddDrawItem(ItemPtr, D2D, ItemColor, ItemName);
				}
				else if (ItemInfo.Type == 15 && off->Other)
				{
					AddDrawItem(ItemPtr, D2D, ItemColor, ItemName);
				}
				else if (ItemInfo.Type == 16 && off->Ammo)
				{
					AddDrawItem(ItemPtr, D2D, ItemColor, ItemName);
				}
			}
			else
			{
				if (ItemInfo.Type < 18 && ItemInfo.Type > 0)
				{
					if (off->DroppedESP_hezi)
					{
						UCanvas::DrawText(ItemLocation.X, ItemLocation.Y, ItemColor, Colo->��ɫ, true, ItemName.c_str());
					}
					return true;
				}
				return false;
			}

		};
		
		//DrawDropptedItem
		[&] {
			if (ActorNameHash != "DroppedItem"h)
				return;
			auto DroppedItem = PubgData::XeDecryption(Read<ULONG64>(Actor + offset_DroppedItem));
			if (!DroppedItem)
				return;
			auto ActorLocation = PubgData::GetPos(Actor);
			if (ActorLocation == FVector())return;
			const float Distance = Game->Location.Distance(ActorLocation) / 100.0f;
			if (off->ItemDistance < Distance)return;
			FVector2D ActorLocationScreen;
			if (!PubgData::WorldToScreen(ActorLocation, ActorLocationScreen))return;
			DrawItem(DroppedItem, ActorLocationScreen,false);
		}();
		//DrawDroppedItemGroup
		[&] {
			if (ActorNameHash != "DroppedItemGroup"h)
				return;
			auto pItemArray = Read<ULONG64>(Actor + offset_DroppedItemGroup);
			auto pItemCount = Read<ULONG>(Actor + offset_DroppedItemGroup + 0x8);
			if (pItemCount <= 0 || pItemCount > 50 || !pItemArray)  return;
			for (size_t i = 0; i < pItemCount; i++)
			{
				auto ItemComponent = Read<ULONG64>(pItemArray + i * 0x10);
				if (ValidPtr(ItemComponent))
					continue;
				auto Id = PubgData::GetNameIndex(ItemComponent);
				if (Id <= 0)continue;
				auto ItemComponentHash = PubgData::GetNameHash(Id);

				if (ItemComponentHash != "DroppedItemInteractionComponent"h && ItemComponentHash != "DestructibleItemInteractionComponent"h)
					continue;
				FVector2D ItemLocationScreen;
				auto ActorLocation = Read<FVector>(ItemComponent + offset_AbsoluteLocation);
				const float Distance = Game->Location.Distance(ActorLocation) / 100.0f;
				if (off->ItemDistance < Distance)return;
				if (!PubgData::WorldToScreen(ActorLocation, ItemLocationScreen))continue;
				auto DroppedItemGroup = Read<ULONG64>(ItemComponent + offset_DroppedItemGroup_UItem);
				if (ValidPtr(DroppedItemGroup)) continue;
				DrawItem(DroppedItemGroup, ItemLocationScreen, false);
			}
		}();
		//DrawPackage
		[&] {
			auto PackageInfo = GetPackageInfo(ActorNameHash);
			auto& PackageName = PackageInfo.Name;
			if (!PackageName[0])
				return;
			auto DroppedItemGroup = Read<ULONG64>(Actor + offset_DroppedItemGroup); if (ValidPtr(DroppedItemGroup))  return;
			DroppedItemGroup = Read<ULONG64>(DroppedItemGroup); if (ValidPtr(DroppedItemGroup))  return;
			auto ActorLocation = Read<FVector>(DroppedItemGroup + offset_AbsoluteLocation);
			const float Distance = Game->Location.Distance(ActorLocation) / 100.0f;
			FVector2D ActorLocationScreen;
			if (!PubgData::WorldToScreen(ActorLocation, ActorLocationScreen))return;
			if (PackageInfo.IsSmall && Distance > 800.0f)
				return;
			auto Output = PackageInfo.IsSmall ?
				std::string(PackageName.data()) :
				sformat((const char*)"{} {}M"e, PackageName.data(), (unsigned)Distance);
			UCanvas::DrawText(ActorLocationScreen.X, ActorLocationScreen.Y + 13, Colo->�Һ�, Colo->��ɫ, true, Output.c_str());
			//DrawBoxContents
			[&] {
				FVector2D PackageLocationScreen = ActorLocationScreen;
				auto  pItemArray = Read<ULONG64>(Actor + offset_Items);
				if (ValidPtr(pItemArray))return;
				auto  pItemCount = Read<ULONG>(Actor + offset_Items + sizeof(PVOID));

				for (size_t i = 0; i < pItemCount; i++)
				{
					auto ItemPtr = Read<ULONG64>(pItemArray + i * sizeof(PVOID));
					if (ValidPtr(ItemPtr))
						continue;
					if (!DrawItem(ItemPtr, PackageLocationScreen,true))
						continue;
					PackageLocationScreen.Y -= 13.f;
				}
			}();
		}();
		
	}

	LastAimPlayer = AimPlayer;
	if (Func::GetAsyncKeyState2(off->AimKey)) {
		if (NULL == AimPlayer)return;
		if (PubgData::GetHealth(AimPlayer) <= 0 && PubgData::GetHealthDie(AimPlayer) <= 0)return;
		IsLock = true;
		auto Mesh = PubgData::GetMesh(AimPlayer);

		auto Mesh111 = PubgData::GetMesh(AimPlayer);//����
		bool IsBoneShow = false;
		if (Func::GetAsyncKeyState2(VK_SHIFT)) {
			if (Game->juli > 80)
			{
				PubgData::GetBoneMatrix(Mesh, &AmtPos, 13);

			}
			if (Game->juli < 80)
			{
				PubgData::GetBoneMatrix(Mesh, &AmtPos, 14);
			}


			IsBoneShow = true;
		}
		else if (off->MissHit) {
			auto Index = forehead;
			switch (off->AimPos)
			{
			case 0:
				if (Game->juli > 80)
				{
					Index = Bones::forehead_root;
				}
				if (Game->juli < 80)
				{
					Index = Bones::eyebrow_r;
				}
				break;
			case 1:
				Index = Bones::neck_01;//Bones::neck_01
				break;
			case 2:
				Index = Bones::spine_03;
				break;
			default:
				break;
			}
			PubgData::GetBoneMatrix(Mesh, &AmtPos, Index);
			PubgData::GetBoneMatrix(Mesh111, &AmtPos111, Index);//����

			if (Func::LineTraceSingle(Game->Location, AmtPos))
				IsBoneShow = true;
			else
			{
				for (auto BoneIndex : GetBoneIndexArray()) {
					PubgData::GetBoneMatrix(Mesh, &AmtPos, BoneIndex);
					if (Func::LineTraceSingle(Game->Location, AmtPos)) {
						IsBoneShow = true;
						break;
					}
				}
			}
		}
		else {
			PubgData::GetBoneMatrix(Mesh, &AmtPos, spine_03);
			IsBoneShow = true;
		}
		if (IsBoneShow) {
			//printf("���������߳�\n");
			PubgData::PredictPos(AimPlayer, AmtPos);
		
		//	UCanvas::DrawText(100, 560, Colo->��ɫ, Colo->��ɫ, false, "%f  %f   %f"e, AmtPos111.X, AmtPos111.Y, AmtPos111.Z);
			//����׷��(AmtPos111, GEDistance, AmtPos);



		}
	}
	else
	{
		AimPlayer = NULL;
		IsLock = false;
	}
}