#include "Main.h"
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
GameData* Game = new GameData();
ColorData* Colo = new ColorData();
CheatSwitch* off = new CheatSwitch();

EXTERN_C void __fastcall Fn_DrawLine(ULONG64 UCanvas, float StartScreenX, float StartScreenY, float EndScreenX, float EndScreenY, const FLinearColor* LineColor, float LineThickness);
EXTERN_C void __fastcall Fn_DrawRect(ULONG64 UCanvas, const FLinearColor* RectColor, float ScreenX, float ScreenY, float ScreenW, float ScreenH);

BOOL Func::SGetWindowInfo(PWINDOWINFO pwi) {
	return SpoofCall<BOOL>(GetWindowInfo, Game->hWnd, pwi);
}
BOOL Func::SGetCursorPos(LPPOINT lpPoint) {
	return SpoofCall<BOOL>(GetCursorPos,lpPoint);
}
SHORT Func::GetAsyncKeyState2(int vKey) {
	if (SGetForegroundWindow() == Game->hWnd)
		return SpoofCall<SHORT>(GetAsyncKeyState, vKey);
	return NULL;
}
ULONG64 Func::GetIconTexture(ULONG64 Value) {
	auto VTable = Read<PULONG64>(Value);
	if (VTable && VTable[12])
		return SpoofCall<ULONG64>(VTable[12], Value);
	return 0;
}
void Func::DrawLine(ULONG64 UCanvas, float StartScreenX, float StartScreenY, float EndScreenX, float EndScreenY, const FLinearColor* LineColor, float LineThickness) {
	return SpoofCall<void>(Fn_DrawLine, UCanvas, StartScreenX, StartScreenY, EndScreenX, EndScreenY, LineColor, LineThickness);
}
void Func::DrawRect(ULONG64 UCanvas, const FLinearColor* RectColor, float ScreenX, float ScreenY, float ScreenW, float ScreenH) {
	return SpoofCall<void>(Fn_DrawRect, UCanvas, RectColor, ScreenX, ScreenY, ScreenW, ScreenH);
}
void Func::K2_DrawText(ULONG64 UCanvas, ULONG64 RenderFont, struct FString RenderText, class FVector2D ScreenPosition, struct FLinearColor RenderColor,
	float Kerning, struct FLinearColor ShadowColor, class FVector2D ShadowOffset, bool bCentreX, bool bCentreY, bool bOutlined, struct FLinearColor OutlineColor) {

	return SpoofCall<void>(Game->GameBase + offset_K2_DrawText, UCanvas, RenderFont, RenderText, ScreenPosition, RenderColor,
		Kerning, ShadowColor, ShadowOffset, bCentreX, bCentreY, bOutlined, OutlineColor);
}
void Func::K2_DrawTexture(ULONG64 UCanvas, ULONG64 RenderTexture, class FVector2D ScreenPosition, class FVector2D ScreenSize,
	class FVector2D CoordinatePosition, class FVector2D& CoordinateSize, struct FLinearColor RenderColor, EBlendMode BlendMode,
	float Rotation, class FVector2D& PivotPoint) {

	return SpoofCall<void>(Game->GameBase + offset_K2_DrawTexture, UCanvas, RenderTexture, ScreenPosition, ScreenSize, CoordinatePosition,
		CoordinateSize, RenderColor, BlendMode, Rotation, PivotPoint);
}
void* MemSet(void* dest, int c, size_t count)
{
	char* bytes = (char*)dest;
	while (count--)
	{
		*bytes++ = (char)c;
	}
	return dest;
}
void* MemCpy(void* memTo, const void* memFrom, size_t size)
{
	if (!memTo || !memFrom)
		return nullptr;
	const char* temFrom = (const char*)memFrom;
	char* temTo = (char*)memTo;
	while (size-- > 0)
		*temTo++ = *temFrom++;
	return memTo;
}
bool ReadMemory(uint64_t ptr, void* Buffer, uint32_t Size) {
	if (ptr < 0x1000000 - 0x8 || ptr > 0x7FFFFFF00000 + 0x8) {
		MemSet(Buffer, 0, Size);
		return true;
	}
	else {
		if (SpoofCall<BOOL>(IsBadHugeReadPtr, (PVOID)ptr, Size)) {
			//SpoolCall<BOOL>(IsBadHugeReadPtr, (PVOID)ptr, Size)
			//if (vSouleIsBadReadPtr((PVOID)ptr, size)) {
			MemSet(Buffer, 0, Size);
			return true;
		}
		else {
			MemCpy(Buffer, (void*)ptr, Size);
			return true;
		}
	}
}
bool WriteMemory(uint64_t ptr, void* Buffer, uint32_t Size) {
	if (ptr < 0x1000000 - 0x8 || ptr > 0x7FFFFFF00000 + 0x8) {
		MemSet(Buffer, 0, Size);
		return true;
	}
	else {
		if (SpoofCall<BOOL>(IsBadHugeReadPtr, (PVOID)ptr, Size)) {
			//if (vSouleIsBadReadPtr((PVOID)ptr, size)) {
			MemSet(Buffer, 0, Size);
			return true;
		}
		else {
			MemCpy((void*)ptr, Buffer, Size);
			return true;
		}
	}
}
HWND Func::SGetForegroundWindow() {
	return SpoofCall<HWND>(GetForegroundWindow);
}
bool Func::LineTraceSingle(FVector TraceStart, FVector TraceEnd)
{
	FHitResult UnKnowFHitResult = { 0 };
	return !SpoofCall<bool>(Game->GameBase + offset_LineTraceSingle, Game->UWorld, &TraceStart, &TraceEnd, 0, true,Game->Actor, 0, &UnKnowFHitResult, true);
}
bool Func::LineTraceSingle(FVector TraceStart, FVector TraceEnd, FHitResult* OutFHitResult)
{
	return !SpoofCall<bool>(Game->GameBase + offset_LineTraceSingle, Game->UWorld, &TraceStart, &TraceEnd, 0, true, Game->Actor, 0, OutFHitResult, true);
}
void Func::HideInList(HMODULE hModule)
{

	PM_PEB pM_PEB = (PM_PEB)__readgsqword(0x60);
	PM_M_PEB_LDR_DATA pLdr = pM_PEB->LoaderData;
	PM_LDR_MODULE pModule = (PM_LDR_MODULE)pLdr->InLoadOrderModuleList.Flink;
	PM_LDR_MODULE pFirstModule = (PM_LDR_MODULE)&pLdr->InLoadOrderModuleList;
	LIST_ENTRY le;

	do
	{
		if (pModule->BaseAddress == (PVOID)hModule)
		{
			
			memcpy(&le, &pModule->InInitializationOrderModuleList, sizeof(le));
			pModule->InInitializationOrderModuleList.Blink->Flink = le.Flink;
			pModule->InInitializationOrderModuleList.Flink->Blink = le.Blink;

			memcpy(&le, &pModule->InLoadOrderModuleList, sizeof(le));
			pModule->InLoadOrderModuleList.Blink->Flink = le.Flink;
			pModule->InLoadOrderModuleList.Flink->Blink = le.Blink;

			memcpy(&le, &pModule->InMemoryOrderModuleList, sizeof(le));
			pModule->InMemoryOrderModuleList.Blink->Flink = le.Flink;
			pModule->InMemoryOrderModuleList.Flink->Blink = le.Blink;
		}
		pModule = (PM_LDR_MODULE)pModule->InLoadOrderModuleList.Flink;
	} while (pFirstModule != pModule);
}