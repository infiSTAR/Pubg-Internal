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
void 绘制三角(FVector2D A, FVector2D B, FVector2D C, float thickness, FLinearColor clr)
{

	UCanvas::DrawLine(A.X, A.Y, B.X, B.Y, thickness, clr);
	UCanvas::DrawLine( B.X, B.Y, C.X, C.Y, thickness, clr);
	UCanvas::DrawLine( C.X, C.Y, A.X, A.Y, thickness, clr);
}
void 绘制标识(FRotator 鼠标, FVector 本人Pos, FVector 对象pos, float Size)
{
	float 距离 = (本人Pos).Distance(对象pos) / 100;
	float 角度 = atan2(本人Pos.Y - 对象pos.Y, 本人Pos.X - 对象pos.X);
	角度 = 角度 * 180 / M_PI;
	角度 = 鼠标.Yaw + 360 - 角度; //Y其实是X，存储顺序不同

	FVector2D A, B, C;
	A.X = (Size + 10.0f) * sin(角度 * M_PI / 180) + Game->ScreenCenter.X;
	A.Y = (Size + 10.0f) * cos(角度 * M_PI / 180) + Game->ScreenCenter.Y;

	B.X = (Size - 10.0f) * sin((角度 - 5) * M_PI / 180) + Game->ScreenCenter.X;
	B.Y = (Size - 10.0f) * cos((角度 - 5) * M_PI / 180) + Game->ScreenCenter.Y;

	C.X = (Size - 10.0f) * sin((角度 + 5) * M_PI / 180) + Game->ScreenCenter.X;
	C.Y = (Size - 10.0f) * cos((角度 + 5) * M_PI / 180) + Game->ScreenCenter.Y;

	FLinearColor clr;

	if (距离 < 400)
	{
		clr = Colo->白色;
		if (距离 < 100.0f)
			clr = Colo->红色;
		else if (距离 < 200.0f)
			clr = Colo->橙黄;
		else if (距离 < 300.0f)
			clr = Colo->绿色;
		绘制三角(A, B, C, 1, clr);
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
		//主干

		//UCanvas::DrawLine(HeadPos.X, HeadPos.Y, NeckPos.X, NeckPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, Neck) ? Col : NoColor);
		UCanvas::DrawLine(NeckPos.X, NeckPos.Y, PelvisPos.X, PelvisPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, Pelvis) ? Col : NoColor);
		//左手
		UCanvas::DrawLine(NeckPos.X, NeckPos.Y, L_ClaviclePos.X, L_ClaviclePos.Y, 0.9f, Func::LineTraceSingle(Game->Location, L_Clavicle) ? Col : NoColor);
		UCanvas::DrawLine(L_ClaviclePos.X, L_ClaviclePos.Y, L_UpperArmPos.X, L_UpperArmPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, L_UpperArm) ? Col : NoColor);
		UCanvas::DrawLine(L_UpperArmPos.X, L_UpperArmPos.Y, L_ForearmPos.X, L_ForearmPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, L_Forearm) ? Col : NoColor);
		UCanvas::DrawLine(L_ForearmPos.X, L_ForearmPos.Y, L_HandPos.X, L_HandPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, L_Hand) ? Col : NoColor);
		//右手
		UCanvas::DrawLine(NeckPos.X, NeckPos.Y, R_ClaviclePos.X, R_ClaviclePos.Y, 0.9f, Func::LineTraceSingle(Game->Location, R_Clavicle) ? Col : NoColor);
		UCanvas::DrawLine(R_ClaviclePos.X, R_ClaviclePos.Y, R_UpperArmPos.X, R_UpperArmPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, R_UpperArm) ? Col : NoColor);
		UCanvas::DrawLine(R_UpperArmPos.X, R_UpperArmPos.Y, R_ForearmPos.X, R_ForearmPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, R_Forearm) ? Col : NoColor);
		UCanvas::DrawLine(R_ForearmPos.X, R_ForearmPos.Y, R_HandPos.X, R_HandPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, R_Hand) ? Col : NoColor);
		//左腿
		UCanvas::DrawLine(PelvisPos.X, PelvisPos.Y, L_ThighPos.X, L_ThighPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, L_Thigh) ? Col : NoColor);
		UCanvas::DrawLine(L_ThighPos.X, L_ThighPos.Y, L_CalfPos.X, L_CalfPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, L_Calf) ? Col : NoColor);
		UCanvas::DrawLine(L_CalfPos.X, L_CalfPos.Y, L_FootPos.X, L_FootPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, L_Foot) ? Col : NoColor);
		//右腿
		UCanvas::DrawLine(PelvisPos.X, PelvisPos.Y, R_ThighPos.X, R_ThighPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, R_Thigh) ? Col : NoColor);
		UCanvas::DrawLine(R_ThighPos.X, R_ThighPos.Y, R_CalfPos.X, R_CalfPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, R_Calf) ? Col : NoColor);
		UCanvas::DrawLine(R_CalfPos.X, R_CalfPos.Y, R_FootPos.X, R_FootPos.Y, 0.9f, Func::LineTraceSingle(Game->Location, R_Foot) ? Col : NoColor);
	}

}
FLinearColor 队伍颜色转换(INT R, INT G, INT B, INT A)
{
	FLinearColor temp;
	temp.R = (float)R / 255;
	temp.G = (float)G / 255;
	temp.B = (float)B / 255;
	temp.A = (float)A / 100;
	return temp;
}
FLinearColor GetTeamCrolor(int32_t 队伍)
{
	FLinearColor 临时颜色;
	if (队伍 == 1 || 队伍 == 26 || 队伍 == 51 || 队伍 == 76)
	{
		临时颜色 = 队伍颜色转换(255, 182, 193, 255);
	}
	else if (队伍 == 2 || 队伍 == 27 || 队伍 == 52 || 队伍 == 77)
	{
		临时颜色 = 队伍颜色转换(255, 192, 203, 255);
	}
	else if (队伍 == 3 || 队伍 == 28 || 队伍 == 5. || 队伍 == 78)
	{
		临时颜色 = 队伍颜色转换(220, 20, 60, 255);
	}
	else if (队伍 == 4 || 队伍 == 29 || 队伍 == 54 || 队伍 == 79)
	{
		临时颜色 = 队伍颜色转换(0, 255, 127, 255);
	}
	else if (队伍 == 5 || 队伍 == 30 || 队伍 == 55 || 队伍 == 80)
	{
		临时颜色 = 队伍颜色转换(219, 112, 147, 255);
	}
	else if (队伍 == 6 || 队伍 == 31 || 队伍 == 56 || 队伍 == 81)
	{
		临时颜色 = 队伍颜色转换(255, 105, 180, 255);
	}
	else if (队伍 == 7 || 队伍 == 32 || 队伍 == 57 || 队伍 == 82)
	{
		临时颜色 = 队伍颜色转换(255, 20, 147, 255);
	}
	else if (队伍 == 8 || 队伍 == 33 || 队伍 == 58 || 队伍 == 83)
	{
		临时颜色 = 队伍颜色转换(255, 106, 106, 255);
	}
	else if (队伍 == 9 || 队伍 == 34 || 队伍 == 59 || 队伍 == 84)
	{
		临时颜色 = 队伍颜色转换(218, 112, 214, 255);
	}
	else if (队伍 == 10 || 队伍 == 35 || 队伍 == 60 || 队伍 == 85)
	{
		临时颜色 = 队伍颜色转换(216, 191, 216, 255);
	}
	else if (队伍 == 11 || 队伍 == 36 || 队伍 == 61 || 队伍 == 86)
	{
		临时颜色 = 队伍颜色转换(221, 160, 221, 255);
	}
	else if (队伍 == 12 || 队伍 == 37 || 队伍 == 62 || 队伍 == 87)
	{
		临时颜色 = 队伍颜色转换(238, 130, 238, 255);
	}
	else if (队伍 == 13 || 队伍 == 38 || 队伍 == 63 || 队伍 == 88)
	{
		临时颜色 = 队伍颜色转换(255, 69, 0, 255);
	}
	else if (队伍 == 14 || 队伍 == 39 || 队伍 == 64 || 队伍 == 89)
	{
		临时颜色 = 队伍颜色转换(255, 130, 71, 255);
	}
	else if (队伍 == 15 || 队伍 == 40 || 队伍 == 65 || 队伍 == 90)
	{
		临时颜色 = 队伍颜色转换(255, 127, 36, 255);
	}
	else if (队伍 == 16 || 队伍 == 41 || 队伍 == 66 || 队伍 == 91)
	{
		临时颜色 = 队伍颜色转换(255, 69, 0, 255);
	}
	else if (队伍 == 17 || 队伍 == 42 || 队伍 == 67 || 队伍 == 92)
	{
		临时颜色 = 队伍颜色转换(0, 255, 0, 255);
	}
	else if (队伍 == 18 || 队伍 == 43 || 队伍 == 68 || 队伍 == 93)
	{
		临时颜色 = 队伍颜色转换(192, 255, 62, 255);
	}
	else if (队伍 == 19 || 队伍 == 44 || 队伍 == 69 || 队伍 == 94)
	{
		临时颜色 = 队伍颜色转换(153, 50, 204, 255);
	}
	else if (队伍 == 20 || 队伍 == 45 || 队伍 == 70 || 队伍 == 95)
	{
		临时颜色 = 队伍颜色转换(0, 255, 255, 255);
	}
	else if (队伍 == 21 || 队伍 == 46 || 队伍 == 71 || 队伍 == 96)
	{
		临时颜色 = 队伍颜色转换(212, 242, 231, 255);
	}
	else if (队伍 == 22 || 队伍 == 47 || 队伍 == 72 || 队伍 == 97)
	{
		临时颜色 = 队伍颜色转换(0, 206, 209, 255);
	}
	else if (队伍 == 23 || 队伍 == 48 || 队伍 == 73 || 队伍 == 98)
	{
		临时颜色 = 队伍颜色转换(127, 255, 170, 255);
	}
	else if (队伍 == 24 || 队伍 == 49 || 队伍 == 74 || 队伍 == 99)
	{
		临时颜色 = 队伍颜色转换(0, 255, 127, 255);
	}
	else if (队伍 == 25 || 队伍 == 50 || 队伍 == 75 || 队伍 == 100)
	{
		临时颜色 = 队伍颜色转换(127, 255, 0, 255);
	}
	else
	{
		临时颜色 = 队伍颜色转换(255, 255, 0, 255);
	}
	return 临时颜色;
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

		//UCanvas::DrawText(D2D.X, D2D.Y, ItemColor, Colo->黑色, true,"%p", icon);
		if (ValidPtr(icon))return;
		float size = 0.2;
		auto Xx = Read<int>(icon + offset_ImportedSize);
		auto Yy = Read<int>(icon + offset_ImportedSize + 4);
		UCanvas::K2_DrawTexture(icon, { D2D.X,D2D.Z }, FVector2D(Xx * size, Yy * size), FVector2D(), FVector2D(1, 1), FLinearColor(1, 1, 1, 1), EBlendMode::BLEND_Masked, 0.0f, FVector2D(1, 1));
	}

	UCanvas::DrawText(D2D.X, D2D.Y, ItemColor, Colo->黑色, true, ItemName.c_str());
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
//	//sprintf_s(temp, "PUBG:%d/%d/%d/%d/%d/%d/%d"e, AntiScreenShotCount_Dx, AntiScreenShotCount_GDI, AntiScreenShotCount_CRC, AntiScreenShotCount_CRCb, dx判断, DX函数监控, DxCount);
//	/*UCanvas::DrawText(100, 100, Colo->白色, Colo->黑色, false, "F5 实体飞车[%s]"e, off->实体飞车 ? "开启"e : "关闭"e);
//	UCanvas::DrawText(100, 120, Colo->白色, Colo->黑色, false, "F6 无视碰撞[%s]"e, off->无视碰撞 ? "开启"e : "关闭"e);
//	UCanvas::DrawText(100, 140, Colo->白色, Colo->黑色, false, "←→ 调整移动速度[%d]"e, (int)off->Speed);
//	UCanvas::DrawText(100, 160, Colo->白色, Colo->黑色, false, "↑↓ 调整上下速度[%d]"e, (int)off->UpDownSpeed);*/
//	if (Func::GetAsyncKeyState2(VK_F5) & 1)
//		off->实体飞车 = !off->实体飞车;
//	else if (Func::GetAsyncKeyState2(VK_F6) & 1)
//		off->无视碰撞 = !off->无视碰撞;
//
//	if (ZeroGUI::Window("猪猪人"e, &pos, FVector2D{ 585.0f, 350.0f }, off->Menu))
//	{
//		static int tab = 0;
//		if (ZeroGUI::ButtonTab("视觉"e, FVector2D{ 110, 25 }, tab == 0)) tab = 0;
//		if (ZeroGUI::ButtonTab("瞄准"e, FVector2D{ 110, 25 }, tab == 1)) tab = 1;
//		if (ZeroGUI::ButtonTab("物品"e, FVector2D{ 110, 25 }, tab == 2)) tab = 2;
//		if (ZeroGUI::ButtonTab("颜色"e, FVector2D{ 110, 25 }, tab == 3)) tab = 3;
//		if (ZeroGUI::ButtonTab("功能"e, FVector2D{ 110, 25 }, tab == 4)) tab = 4;
//		ZeroGUI::NextColumn(20.0f);
//
//		if (tab == 0) {
//			ZeroGUI::Text("Visuals"e, 15);
//
//			ZeroGUI::Checkbox("方框"e, &off->Box); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("骨骼"e, &off->Bone); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("名字"e, &off->Name); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("血量"e, &off->Health);
//
//			ZeroGUI::Checkbox("距离"e, &off->Distance); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("杀敌"e, &off->Kill); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("观战"e, &off->WatchCount); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("武器"e, &off->Weapon);
//
//			ZeroGUI::Checkbox("战绩"e, &off->RankInfo); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("队伍"e, &off->Team); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("等级"e, &off->Level); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("伤害"e, &off->Damage);
//
//			ZeroGUI::Checkbox("雷达"e, &off->Radar); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("眼线"e, &off->EyeLine); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("开发模式"e, &off->Debug);
//
//			ZeroGUI::SliderFloat("透视距离"e, &off->ESPDistance, 100, 1000);
//		}
//		else if (tab == 1) {
//			ZeroGUI::Text("AimBot"e, 15);
//
//			ZeroGUI::Checkbox("自瞄"e, &off->AimBot); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("范围"e, &off->DrawFov); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("漏打"e, &off->MissHit); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("倒地"e, &off->Groggy);
//
//			ZeroGUI::Hotkey("按键"e, FVector2D{ 100, 25 }, &off->AimKey); ZeroGUI::SameLine();
//
//			ZeroGUI::Combobox("优先瞄准"e, FVector2D{ 100, 25 }, &off->AimPos, "头部\0", "脖子\0", "胸部\0", NULL);
//
//			ZeroGUI::SliderFloat("Fov"e, &off->AimFov, 1, 1000);
//			ZeroGUI::SliderFloat("自瞄速度X"e, &off->AimSpeedX, 1, 100);
//			ZeroGUI::SliderFloat("自瞄速度Y"e, &off->AimSpeedY, 1, 100);
//			ZeroGUI::SliderFloat("瞄准距离"e, &off->AimDistance, 100, 1000);
//		}
//		else if (tab == 2) {
//			ZeroGUI::Text("Item"e, 15);
//			ZeroGUI::Checkbox("车辆"e, &off->Vehicle); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("物资"e, &off->Item);; ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("图标"e, &off->Icon);; ZeroGUI::SameLine();
//			ZeroGUI::Text("~键 战斗"e);
//
//			ZeroGUI::Checkbox("子弹"e, &off->Ammo); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("配件"e, &off->Attach); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("投掷"e, &off->Throw); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("钥匙"e, &off->Key);
//
//
//			ZeroGUI::Checkbox("步枪"e, &off->AR); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("机枪"e, &off->LMG); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("栓狙"e, &off->SR); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("连狙"e, &off->DMR);
//
//
//			ZeroGUI::Checkbox("冲锋"e, &off->SMG); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("霰弹"e, &off->SG); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("特殊"e, &off->Special);  ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("药物"e, &off->Heal);
//
//			ZeroGUI::Checkbox("头盔"e, &off->Head); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("护甲"e, &off->Armor); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("背包"e, &off->Bag); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("其它"e, &off->Other);
//
//			ZeroGUI::SliderFloat("车辆距离"e, &off->VehicleDistance, 100, 1000);
//			ZeroGUI::SliderFloat("物资距离"e, &off->ItemDistance, 50, 150);
//		}
//		else if (tab == 3) {
//			ZeroGUI::Text("Color"e, 15);
//			ZeroGUI::ColorPicker("方框可见颜色"e, &Colo->Box); ZeroGUI::SameLine();
//			ZeroGUI::ColorPicker("方框障碍颜色"e, &Colo->NoBox);
//
//			ZeroGUI::ColorPicker("骨骼可见颜色"e, &Colo->Bone); ZeroGUI::SameLine();
//			ZeroGUI::ColorPicker("骨骼障碍颜色"e, &Colo->NoBone);
//
//			ZeroGUI::ColorPicker("信息可见颜色"e, &Colo->Info); ZeroGUI::SameLine();
//			ZeroGUI::ColorPicker("信息障碍颜色"e, &Colo->NoBox);
//
//			ZeroGUI::ColorPicker("预瞄颜色"e, &Colo->AimBot); ZeroGUI::SameLine();
//			ZeroGUI::ColorPicker("车辆颜色"e, &Colo->Vehicle);
//
//			ZeroGUI::ColorPicker("物品Lv1颜色"e, &Colo->Lv1); ZeroGUI::SameLine();
//			ZeroGUI::ColorPicker("物品Lv2颜色"e, &Colo->Lv2); ZeroGUI::SameLine();
//			ZeroGUI::ColorPicker("物品Lv3颜色"e, &Colo->Lv3);
//			ZeroGUI::ColorPicker("物品Lv4颜色"e, &Colo->Lv4); ZeroGUI::SameLine();
//			ZeroGUI::ColorPicker("物品Lv5颜色"e, &Colo->Lv5);
//		}
//		else if (tab == 4) {
//
//			ZeroGUI::Text("功能"e, 15);
//			ZeroGUI::Checkbox("人物穿墙"e, &off->人物穿墙); ZeroGUI::SameLine();
//			ZeroGUI::Checkbox("人物穿楼"e, &off->人物穿楼);
//			ZeroGUI::Checkbox("开车开枪"e, &off->开车开枪);
//			ZeroGUI::Checkbox("车辆飞天说明"e, &off->飞车说明); ZeroGUI::SameLine();
//			ZeroGUI::SliderFloat("飞车速度"e, &off->Speed, 1000, 4500);
//			ZeroGUI::SliderFloat("上升速度"e, &off->UpDownSpeed, 1000, 3000);
//		}
//
//	}
//	ZeroGUI::Render();//Custom Render. I use it for drawing Combobox and ColorPicker over the menu
//	ZeroGUI::Draw_Cursor(off->Menu);
//}



void GameHack::F按键()
{
	if (Sss(VK_F1))		off->Display_Player = !off->Display_Player;//人物

	if (off->Display_Player)
	{
		if (Func::GetAsyncKeyState2(VK_MENU) && off->Display_Player)
		{
			if (SSs(49))		off->Box = !off->Box;//方框
			if (SSs(50))		off->Bone = !off->Bone;//骨骼
			if (SSs(51))		off->Health = !off->Health;//血条
			if (SSs(52))		off->PlayerESP_Message = !off->PlayerESP_Message;//信息
			if (SSs(53))		off->WatchCount = !off->WatchCount;//观战
			//if (SSs(49))		off->PlayerESP_Box = !off->PlayerESP_Box;
		}
	}

	if (off->Item)
	{
		if (Func::GetAsyncKeyState2(VK_LCONTROL) && off->Item)
		{
		
			if (SSs(53))		off->DroppedESP_Weapon = !off->DroppedESP_Weapon;//武器
			if (SSs(54))		off->Heal = !off->Heal;//药品
			if (SSs(55))		off->Attach = !off->Attach;//配件
			if (SSs(56))		off->Armor = !off->Armor;//防具
			//if (SSs(57))		off->PlayerESP_gaunzhan = !off->PlayerESP_gaunzhan;//投掷
			//if (SSs(58))		off->PlayerESP_gaunzhan = !off->PlayerESP_gaunzhan;//观战
		}
	
	}
	if (Sss(VK_F3))		off->Vehicle = !off->Vehicle;//车辆
	if (Sss(VK_F4))		off->DroppedESP_hezi = !off->DroppedESP_hezi;//盒子
	if (Sss(VK_F5))		off->AimBot = !off->AimBot;//自瞄
	if (Sss(VK_F6))		off->MissHit = !off->MissHit;//漏打
	if (Sss(VK_F8))		off->DrawFov = !off->DrawFov;//范围
	if (Sss(VK_F9))		off->Groggy = !off->Groggy;//倒地
	//自瞄距离
	if (Func::GetAsyncKeyState2(33))//这是PGip键↑
	{
		Sleep(25);
		if (off->AimDistance <= 1000) {
			off->AimDistance += 100;
		}
	}
	if (Func::GetAsyncKeyState2(34))//这是Pgdn键↓
	{
		Sleep(25);
		if (off->AimDistance >= 200) {
			off->AimDistance -= 100;
		}
	}
	//透视距离

	if (Func::GetAsyncKeyState2(39))//这是→键↑
	{
		Sleep(25);
		if (off->ESPDistance < 1000) {
			off->ESPDistance += 100;
		}
	}
	if (Func::GetAsyncKeyState2(37))//这是←键↓
	{
		Sleep(25);
		if (off->ESPDistance >= 200) {
			off->ESPDistance -= 100;

		}
	}

	//自瞄XY轴速率
	if (Func::GetAsyncKeyState2(38))//这是上键↑
	{
		Sleep(25);
		if (off->AimSpeedX <= 500) {
			//off->AimSpeedX += 1;
			off->AimSpeedY += 1;
		}
	}
	if (Func::GetAsyncKeyState2(40))//这是上键↓
	{
		Sleep(25);
		if (off->AimSpeedX >= 2) {
			//off->AimSpeedX -= 1;
			off->AimSpeedY -= 1;
		}
	}
	//自瞄FOV范围
	if (Func::GetAsyncKeyState2(107))//这是+键↑
	{
		Sleep(25);
		if (off->AimFov < 500) {

			off->AimFov += 10;
		}
	}
	if (Func::GetAsyncKeyState2(109))//这是-键↓
	{
		Sleep(25);

		if (off->AimFov >= 20) {
			off->AimFov -= 10;
		}

	}

}

void 功能开关(int X, int Y, const char* text, bool Bool)
{
	if (Bool)
	{
		UCanvas::DrawText(X, Y, Colo->艳青, Colo->黑色, false, text, Bool);
		//UCanvas::DrawText(X + 165, Y, Colo->艳青, Colo->黑色, false, "开"e);
	}
	else
	{
		UCanvas::DrawText(X, Y, Colo->白色_, Colo->黑色, false, text, Bool);
		//UCanvas::DrawText(X + 165, Y, Colo->白色_, Colo->黑色, false, "关"e);
	}

}


void GameHack::F菜单()
{
	float 游戏左边 = 20.0f;
	float 行距 = 300;
	float 间隔 = 20.0f;

	if (off->Menu)
	{
		//UCanvas::DrawText(游戏左边, 行距, Colo->黄色_, Colo->黑色, false, "剩余: %d"e, Game->Time);
		//行距 += 间隔;
		//UCanvas::DrawText(游戏左边, 行距, Colo->白色_, Colo->黑色, false, "版本;21.2.5.9"e);
		//行距 += 间隔;
		UCanvas::DrawText(游戏左边, 行距, Colo->白色_, Colo->黑色, false, "Home 显/隐菜单"e);
		行距 += 间隔;
		功能开关(游戏左边, 行距, "[~] 战斗模式"e, off->qingshuang);
		行距 += 间隔;
		功能开关(游戏左边, 行距, "F1  显示人物"e, off->Display_Player);
		行距 += 间隔;
		if (off->Display_Player)
		{
			功能开关(游戏左边, 行距, "|Alt+1  方框"e, off->Box);
			行距 += 间隔;
			功能开关(游戏左边, 行距, "|Alt+2  骨骼"e, off->Bone);
			行距 += 间隔;
			功能开关(游戏左边, 行距, "|Alt+3  血条"e, off->Health);
			行距 += 间隔;
			功能开关(游戏左边, 行距, "|Alt+4  信息"e, off->PlayerESP_Message);
			行距 += 间隔;
			功能开关(游戏左边, 行距, "|Alt+5  观战"e, off->WatchCount);
			行距 += 间隔;
		}
		功能开关(游戏左边, 行距, "F2  显示物品"e, off->Item);
		行距 += 间隔;
		if (off->Item)
		{
			功能开关(游戏左边, 行距, "|Ctrl+5  武器"e, off->DroppedESP_Weapon);
			行距 += 间隔;
			功能开关(游戏左边, 行距, "|Ctrl+6  药品"e, off->Heal);
			行距 += 间隔;
			功能开关(游戏左边, 行距, "|Ctrl+7  配件"e, off->Attach);
			行距 += 间隔;
			功能开关(游戏左边, 行距, "|Ctrl+8  防具"e, off->Armor);
			行距 += 间隔;
		}
		功能开关(游戏左边, 行距, "F3  显示车辆"e, off->Vehicle);
		行距 += 间隔;
		功能开关(游戏左边, 行距, "F4  显示盒子"e, off->DroppedESP_hezi);
		行距 += 间隔;
		功能开关(游戏左边, 行距, "F5  预判自瞄"e, off->AimBot);
		行距 += 间隔;
		功能开关(游戏左边, 行距, "F6  漏那打那"e, off->MissHit);
		行距 += 间隔;
		功能开关(游戏左边, 行距, "F8  自瞄范围"e, off->DrawFov);
		行距 += 间隔;
		功能开关(游戏左边, 行距, "F9  锁定倒地"e, off->Groggy);
		行距 += 间隔;
		UCanvas::DrawText(游戏左边, 行距, Colo->白色_, Colo->黑色, false, "↑↓调整平滑 [%dm]"e, off->AimSpeedY);
		行距 += 间隔;
		UCanvas::DrawText(游戏左边, 行距, Colo->白色_, Colo->黑色, false, "← /→调整透视距离 [%dm]"e, off->ESPDistance);
		行距 += 间隔;
		UCanvas::DrawText(游戏左边, 行距, Colo->白色_, Colo->黑色, false, "PgUp /PgDn调整自瞄距离 [%dm]"e, off->AimDistance);
		行距 += 间隔;
		UCanvas::DrawText(游戏左边, 行距, Colo->白色_, Colo->黑色, false, "+ / - 调整自瞄范围 [%dm]"e, off->AimFov);
		行距 += 间隔;
		UCanvas::DrawText(游戏左边, 行距, Colo->白色_, Colo->黑色, false, "Shift无视掩体锁定"e);
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
		UCanvas::DrawCircle(Game->ScreenCenter.X, Game->ScreenCenter.Y, off->AimFov, 50, Colo->白色);

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

	//UCanvas::DrawText(100, 500, Colo->白色, Colo->绿色, false, "UWorld->%p"e, Game->UWorld);
	//UCanvas::DrawText(100, 520, Colo->白色, Colo->绿色, false, "GameInstance->%p"e, GameInstance);
	//UCanvas::DrawText(100, 540, Colo->白色, Colo->绿色, false, "LocalPlayers->%p"e, LocalPlayers);
	//UCanvas::DrawText(100, 560, Colo->白色, Colo->绿色, false, "MapName->%s"e, PubgData::GetName(PubgData::GetNameIndex(Game->UWorld)).c_str());
	//UCanvas::DrawText(100, 580, Colo->白色, Colo->绿色, false, "PlayerController->%p"e, PlayerController);
	//UCanvas::DrawText(100, 150, Colo->白色, Colo->绿色, false, "AcknowledgedPawn->%p"e, AcknowledgedPawn);
	//UCanvas::DrawText(100, 600, Colo->白色, Colo->绿色, false, "PlayerCameraManager->%p"e, Game->PlayerCameraManager);

	//UCanvas::DrawText(100, 620, Colo->白色, Colo->绿色, false, "MyPlayerAddress->%p"e, Game->MyPlayerAddress);
	//UCanvas::DrawText(100, 640, Colo->白色, Colo->绿色, false, "CurrentLevel->%p"e, CurrentLevel);
	//UCanvas::DrawText(100, 660, Colo->白色, Colo->绿色, false, "Actor->%p"e, Game->Actor);
	//UCanvas::DrawText(100, 680, Colo->白色, Colo->绿色, false, "ActorArray->%p"e, ActorArray);
	//UCanvas::DrawText(100, 700, Colo->白色, Colo->绿色, false, "ActorCount->%d"e, ActorCount);
	//UCanvas::DrawText(100, 200, Colo->白色, Colo->黑色, false, "AcknowledgedPawn：%p"e, AcknowledgedPawn);





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
				//	UCanvas::DrawText(20, 20 + SquadIndex * 15, Colo->绿色_, Colo->黑色, false, "%s L:%d W:%d K:%d D:%.0f (%s)"e, Info.PlayerName.c_str(), Info.PlayerSurvivalLevel, Info.PlayerWatchCount, Info.PlayerNumKill, Info.PlayerDamageDealtOnEnemy, InfoStr.c_str());
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
						UCanvas::DrawLine(map.X, map.Y, map.X + AimOffsets.GetUnitVector().X * 200.0f, map.Y + AimOffsets.GetUnitVector().Y * 200.0f, 1, Colo->银白);

					UCanvas::DrawFillCircle(map.X, map.Y, Size, TeamColor);
					UCanvas::DrawText(map.X, map.Y, Colo->白色, Colo->黑色, true,  "%d"e, Info.PlayerTeamID);
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
							UCanvas::DrawLine(RadarScreenPos.X, RadarScreenPos.Y, RadarScreenPos.X + AimOffsets.GetUnitVector().X * 200.0f, RadarScreenPos.Y + AimOffsets.GetUnitVector().Y * 200.0f, 1, Colo->银白);
						UCanvas::DrawFillCircle(RadarScreenPos.X, RadarScreenPos.Y, Size, TeamColor);
						UCanvas::DrawText(RadarScreenPos.X, RadarScreenPos.Y, Colo->白色, Colo->黑色, true,  "%d"e, Info.PlayerTeamID);
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
					绘制标识(Game->Rotation, Game->Location, HeadLoc, 200);

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
							UCanvas::DrawLine(HeadScreen.X, HeadScreen.Y, Sc2.X, Sc2.Y, 1.5f, Colo->红色);
					}
				}
				float H = FootScreen.Y - HeadScreen.Y;
				float W = H / 2.f;
				float X = HeadScreen.X - W / 2.f;
				float Y = HeadScreen.Y;
				auto IsAim = LastAimPlayer == Actor;
				auto IsVisible = Func::LineTraceSingle(Game->Location, HeadLoc);
				if (off->Box && off->AntiScreen) {//绘制方框
					float CornerHeight = abs(HeadScreen.Y - FootScreen.Y);
					float CornerWidth = CornerHeight * 0.5; //0.5
					DrawCorneredBox(HeadScreen.X - (CornerWidth / 2), HeadScreen.Y, CornerWidth, CornerHeight, IsAim ? Colo->AimBot : IsVisible ? Colo->Box : Colo->NoBox, 1.0f);
					//UCanvas::DrawRect(HeadScreen.X - (CornerWidth / 2), HeadScreen.Y, CornerWidth, CornerHeight, 1.0f, IsAim ? Colo->AimBot : IsVisible ? Colo->Box : Colo->NoBox);
				}
				if (off->Bone && Distance < 500.0f && off->AntiScreen)//绘制骨骼
					Drawbone(Mesh, IsAim ? Colo->AimBot : Colo->Bone, Colo->NoBone);

				if (off->Health && off->AntiScreen) {//绘制血条
					float DrawW = W < 40 ? 40 : W;
					float DHealth = DrawW *  (Health <= 0 ? GroggyHealth : Health) / 100;
					UCanvas::DrawFilled(X + W / 2 - DrawW / 2, Y - 7, DHealth, 5, Health <= 0 ? Colo->白色 : Health <= 30 ? Colo->红色 : Health <= 70 ? Colo->橙黄 : Colo->绿色_);
					UCanvas::DrawRect(X + W / 2 - DrawW / 2, Y - 7, DrawW, 5, 1, Colo->黑色);
				}
				std::string Line;
				std::string LineLL;
				std::string PlayerInfo;
				std::string PlayerInfoLL;

				if (off->PlayerESP_Message) {
					if (IsAICharacter(ActorNameHash))
						Line += (std::string)"AI机器人"e;
					else if (Info.PlayerName.size() > 6)
						Line += Info.PlayerName.substr(0, 6) + (std::string)""e;
					else
						Line += Info.PlayerName;
				}
				if (Line.size())
					Line += (std::string)" 级:"e;
				if (off->PlayerESP_Message)
					Line += std::to_string(Info.PlayerSurvivalLevel);
				
				if (Line.size())
					Line += (std::string)" 队:"e;
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
					UCanvas::DrawText(HeadScreen.X, HeadScreen.Y + H + 3, IsVisible ? Colo->Info : Colo->NoInfo, Colo->黑色, true, PlayerInfo.c_str());
				else if(off->AntiScreen)
					UCanvas::DrawText(HeadScreen.X, HeadScreen.Y + H + 3, IsVisible ? Colo->Info : Colo->NoInfo, Colo->黑色, true, PlayerInfo.c_str());

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

			auto Output = sformat((const char*)"{}\n{}M"e, (const char*)"飞机"e, (unsigned)Distance);
			UCanvas::DrawText(ActorLocationScreen.X, ActorLocationScreen.Y, Colo->橙黄, Colo->黑色, true, Output.c_str());

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
			UCanvas::DrawText(ActorLocationScreen.X, ActorLocationScreen.Y, Colo->红色, Colo->黑色, true, Output.c_str());
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
				Color = Colo->青蓝;
			if (Health <= 0.0f || Fuel <= 0.0f)
				Color = Colo->灰色;
			auto ActorLocation = PubgData::GetPos(Actor);
			const float Distance = Game->Location.Distance(ActorLocation) / 100.0f;
			if (off->VehicleDistance < Distance) return;
			FVector2D ActorLocationScreen;
			if (!PubgData::WorldToScreen(ActorLocation, ActorLocationScreen))return;
			auto Output = sformat((const char*)"{} {}M"e, VehicleName.data(), (unsigned)Distance);
			UCanvas::DrawText(ActorLocationScreen.X, ActorLocationScreen.Y, Color, Colo->黑色, true, Output.c_str());
			UCanvas::SetCanvas(UCanvas::DebugCanvas);

			//Draw vehicle health, fuel
			[&] {
				UCanvas::SetCanvas(UCanvas::DebugCanvas);
				if (!IsDestructible || Health <= 0.0f)
					return;

				float DrawW = 60;
				float DHealth = DrawW * Health / HealthMax;

				UCanvas::DrawFilled(ActorLocationScreen.X - DrawW / 2, ActorLocationScreen.Y + 15, DHealth, 5, Colo->绿色_);
				UCanvas::DrawRect(ActorLocationScreen.X - DrawW / 2, ActorLocationScreen.Y + 15, DrawW, 5, 1, Colo->黑色);

				float DFuel = DrawW * Fuel / FuelMax;
				UCanvas::DrawFilled(ActorLocationScreen.X - DrawW / 2, ActorLocationScreen.Y + 20, DFuel, 5, Colo->天蓝);
				UCanvas::DrawRect(ActorLocationScreen.X - DrawW / 2, ActorLocationScreen.Y + 20, DrawW, 5, 1, Colo->黑色);
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

		//	UCanvas::DrawText(ItemLocation.X, ItemLocation.Y + 20, Colo->白色, Colo->黑色, true, "%llX"e, ItemPtr); //输出物品地址

			std::string ItemName = off->Debug ? PubgData::GetName(Id) : ItemInfo.Name;
			FLinearColor ItemColor = [&] {
				switch (ItemInfo.ItemPriority) {
				case 1: return Colo->Lv1;
				case 2: return Colo->Lv2;
				case 3: return Colo->Lv3;
				case 4: return Colo->Lv4;
				case 5: return Colo->Lv5;
				default:return Colo->粉色;
				}
			}();
			if (!IsBox) {
				FVector D2D = { ItemLocation.X,ItemLocation.Y,ItemLocation.Y };
				if (off->Debug) {
					//UCanvas::DrawText(100, 500, Colo->白色, Colo->绿色, false, "UWorld->%p"e, Game->UWorld);
					//UCanvas::DrawText(100, 520, Colo->白色, Colo->绿色, false, "GameInstance->%p"e, GameInstance);
					//UCanvas::DrawText(100, 540, Colo->白色, Colo->绿色, false, "LocalPlayers->%p"e, LocalPlayers);
					//UCanvas::DrawText(100, 560, Colo->白色, Colo->绿色, false, "MapName->%s"e, PubgData::GetName(PubgData::GetNameIndex(Game->UWorld)).c_str());
					//UCanvas::DrawText(100, 580, Colo->白色, Colo->绿色, false, "PlayerController->%p"e, PlayerController);
					//UCanvas::DrawText(100, 150, Colo->白色, Colo->绿色, false, "AcknowledgedPawn->%p"e, AcknowledgedPawn);
					//UCanvas::DrawText(100, 600, Colo->白色, Colo->绿色, false, "PlayerCameraManager->%p"e, Game->PlayerCameraManager);

					//UCanvas::DrawText(100, 620, Colo->白色, Colo->绿色, false, "MyPlayerAddress->%p"e, Game->MyPlayerAddress);
					//UCanvas::DrawText(100, 640, Colo->白色, Colo->绿色, false, "CurrentLevel->%p"e, CurrentLevel);
					//UCanvas::DrawText(100, 660, Colo->白色, Colo->绿色, false, "Actor->%p"e, Game->Actor);
					//UCanvas::DrawText(100, 680, Colo->白色, Colo->绿色, false, "ActorArray->%p"e, ActorArray);
					//UCanvas::DrawText(100, 700, Colo->白色, Colo->绿色, false, "ActorCount->%d"e, ActorCount);

					UCanvas::DrawText(ItemLocation.X, ItemLocation.Y, Colo->橙黄, Colo->黑色, true, ItemName.c_str());
				}
				else if (ItemInfo.Type == 1 && off->Attach)//绘制配件
				{
					AddDrawItem(ItemPtr, D2D, ItemColor, ItemName);
				}
				else if (ItemInfo.Type == 2 && off->Throw)//绘制投掷物
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
						UCanvas::DrawText(ItemLocation.X, ItemLocation.Y, ItemColor, Colo->黑色, true, ItemName.c_str());
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
			UCanvas::DrawText(ActorLocationScreen.X, ActorLocationScreen.Y + 13, Colo->桃红, Colo->黑色, true, Output.c_str());
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

		auto Mesh111 = PubgData::GetMesh(AimPlayer);//本人
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
			PubgData::GetBoneMatrix(Mesh111, &AmtPos111, Index);//本人

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
			//printf("进入自瞄线程\n");
			PubgData::PredictPos(AimPlayer, AmtPos);
		
		//	UCanvas::DrawText(100, 560, Colo->白色, Colo->黑色, false, "%f  %f   %f"e, AmtPos111.X, AmtPos111.Y, AmtPos111.Z);
			//弹道追踪(AmtPos111, GEDistance, AmtPos);



		}
	}
	else
	{
		AimPlayer = NULL;
		IsLock = false;
	}
}