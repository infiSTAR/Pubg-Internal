#include "Main.h"
#include "xorstr.h"
EXTERN_C ULONG64 DrawLineCall = NULL;
EXTERN_C ULONG64 DrawRectCall = NULL;
EXTERN_C ULONG64 DrawCall = NULL;
ULONG64 UCanvas::Roboto;
ULONG64 UCanvas::Canvas;
ULONG64 UCanvas::DebugCanvas;
ULONG64 UCanvas::CurrentCanvas;
ULONG64 UCanvas::TSLFont;
ULONG64 UCanvas::RobotoTiny;
#include "AntiScreenShot.h"

ULONG_PTR SearchHex111(ULONG_PTR StartAdds, ULONG_PTR EndAdds, const char* Special, size_t spSize) {
	char* p = (char*)StartAdds;
	size_t length = EndAdds - StartAdds - 0x100;
	for (size_t i = 0; i < length; i++)
	{
		if (memcmp(p, Special, spSize) == 0) {
			return (ULONG_PTR)p;
		}
		p++;
	}
	return 0;
}
void PassThread111() {
	
	WaitForSingleObject(GetCurrentThread(), -1);
}
void NewPassScreenShotRestore() {

	const char RestoreShex[16] = { 0x48,0x8B,0x73,0x20,0x48,0x69,0xCF,0xF0,0xD8,0xFF,0xFF,0x48,0x89,0x4C,0x24,0x40 };

	DWORD dwProtect = 0; SIZE_T dwSize = 0;
	MEMORY_BASIC_INFORMATION mbi;
	char* Start = (char*)0x1000;
	while ((ULONG64)Start < Game->GameBase) {

		if (VirtualQuery(Start, &mbi, sizeof(MEMORY_BASIC_INFORMATION)) == sizeof(MEMORY_BASIC_INFORMATION)) {
			if (mbi.State == MEM_COMMIT || mbi.State == MEM_RESERVE) {
				if (mbi.Protect == PAGE_EXECUTE_READ) {
					ULONG_PTR Address = SearchHex111((ULONG_PTR)Start, (ULONG_PTR)(Start + mbi.RegionSize), RestoreShex, 16);
					if (Address > 0) {
						//r15 41 57
						BYTE JmpCode[13] = { 0x49,0xBA,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x41,0x52,0xC3 };
						*(ULONG64*)(JmpCode + 2) = (ULONG64)PassThread111;
						//Driver::WriteMemoryMDL(Address + 9, JmpCode, 13);
						SetRwc RWC(Address, true, 50);
						memcpy((void*)(Address), JmpCode, sizeof(JmpCode));
						RWC.Disable();
						if (*(BYTE*)(Address) == (BYTE)0x49)
						{
							Game->codedll++;
						}

					}
				}
			}
		}
		Start += mbi.RegionSize;
	}
}

void NewPassScreenShotCRC() {

	const char crctu[13] = { 0x41,0x03,0x09,0x4D,0x8D,0x49,0x04,0x48,0x83,0xEA,0x01,0x75,0xF3 };

	DWORD dwProtect = 0; SIZE_T dwSize = 0;
	MEMORY_BASIC_INFORMATION mbi;
	char* Start = (char*)0x1000;
	while ((ULONG64)Start < Game->GameBase) {

		if (VirtualQuery(Start, &mbi, sizeof(MEMORY_BASIC_INFORMATION)) == sizeof(MEMORY_BASIC_INFORMATION)) {
			if (mbi.State == MEM_COMMIT || mbi.State == MEM_RESERVE) {
				if (mbi.Protect == PAGE_EXECUTE_READ) {
					ULONG_PTR Address = SearchHex111((ULONG_PTR)Start, (ULONG_PTR)(Start + mbi.RegionSize), crctu, 13);
					if (Address > 0) {

						BYTE JmpCode[13] = { 0x49,0xBA,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x41,0x52,0xC3 };
						*(ULONG64*)(JmpCode + 2) = (ULONG64)PassThread111;
						//Driver::WriteMemoryMDL(Address + 9, JmpCode, 13);
						SetRwc RWC(Address, true, 50);
						memcpy((void*)(Address), JmpCode, sizeof(JmpCode));
						RWC.Disable();
						if (*(BYTE*)(Address) == (BYTE)0x49)
						{
							Game->codedll++;
						}

					}
				}
			}
		}
		Start += mbi.RegionSize;
	}
}


bool check_rects(float x, float y, float j, float k)
{
	if (((x >= 0 && x <= Game->ScreenCenter.X * 2) && (y >= 0 && y <= Game->ScreenCenter.Y * 2)) || ((j >= 0 && j <= Game->ScreenCenter.X * 2) && (k >= 0 && k <= Game->ScreenCenter.Y * 2)))
		return true;
	else
		return false;
}
void UCanvas::SetCanvas(ULONG64 pCanvas) {
	CurrentCanvas = pCanvas;
}
void UCanvas::Init() {

	NewPassScreenShotCRC();
	NewPassScreenShotRestore();
	DrawLineCall = Game->GameBase + offset_DrawLineCall;
	printf("DrawLineCall:%llX\n", DrawLineCall);

	DrawRectCall = Game->GameBase + offset_DrawRectCall;
	printf("DrawRectCall:%llX\n", DrawRectCall);

	DrawCall = Game->GameBase + offset_DrawCall;
	printf("DrawCall:%llX\n", DrawCall);

	Roboto = *(uint64_t*)(Game->GameBase + offset_Font_Roboto); // PubgData::FindObjectClass(XorString("Roboto"));
	printf("Roboto:%llX\n", Roboto);
	printf("Roboto2:%llX\n" ,*(uint64_t*)(Game->GameBase + offset_Font_Roboto));



	TSLFont = PubgData::FindObjectClass(XorString("TSLFont"));
	printf("TSLFont:%llX\n", TSLFont);

	RobotoTiny = PubgData::FindObjectClass(XorString("RobotoTiny"));
	printf("RobotoTiny:%llX\n", RobotoTiny);

	DebugCanvas = PubgData::FindObjectClass(XorString("DebugCanvasObject"));
	printf("DebugCanvas:%llX\n", DebugCanvas);

	Canvas = PubgData::FindObjectClass(XorString("CanvasObject"));
	//Canvas = Game->GameBase + offset_DebugCanvas;

	printf("Canvas:%llX\n", Canvas);

	CurrentCanvas = DebugCanvas;
}
void UCanvas::DrawLine(float x1, float y1, float x2, float y2, float thickness, FLinearColor color)
{
	if (!check_rects(x1, y1, x2, y2))
		return;
	if (CurrentCanvas)
		Func::DrawLine(CurrentCanvas, x1, y1, x2, y2, &color, thickness);
}
void UCanvas::DrawRect(float x, float y, float w, float h, float thickness, FLinearColor color)
{
	if (!check_rects(x, y, x + w, y + h))
		return;
	if (CurrentCanvas)
	{
		DrawLine(x, y, x + w, y, thickness, color);
		DrawLine(x + w, y + h, x, y + h, thickness, color);
		DrawLine(x + w, y, x + w, y + h, thickness, color);
		DrawLine(x, y, x, y + h, thickness, color);
	}
}
void UCanvas::K2_DrawTexture(ULONG64 RenderTexture, FVector2D ScreenPosition, FVector2D ScreenSize,
	FVector2D CoordinatePosition, FVector2D CoordinateSize, FLinearColor RenderColor, EBlendMode BlendMode,
	float Rotation, FVector2D PivotPoint) {
	if (CurrentCanvas)
	{
		Func::K2_DrawTexture(CurrentCanvas, RenderTexture, ScreenPosition, ScreenSize, CoordinatePosition, CoordinateSize, RenderColor, BlendMode, Rotation, PivotPoint);
	}
}

void UCanvas::DrawFilled(float x, float y, float w, float h, FLinearColor color)
{
	if (!check_rects(x, y, x + w, y + h))
		return;
	if (CurrentCanvas)
	{
		Func::DrawRect(CurrentCanvas, &color, x, y, w, h);
	}
}
void UCanvas::DrawText(float x, float y, FLinearColor Color, FLinearColor BgColor, const char* text, bool bCentreX, bool bCentreY, bool bOutlined)
{
	if (!check_rects(x, y, x, y))
		return;
	if (CurrentCanvas)
		Func::K2_DrawText(CurrentCanvas, Roboto, AnsiToUnicode(text), FVector2D(x, y), Color, 1,FLinearColor(0, 0, 0, 1), FVector2D(), bCentreX, bCentreY, bOutlined, BgColor);
}
void UCanvas::DrawText(float x, float y, FLinearColor Color, FLinearColor BgColor, bool bCentreX, const char* text, ...)
{
	if (!check_rects(x, y, x, y))
		return;
	char szBuffer[4096] = { 0 };
	va_list args;
	va_start(args, text);
	vsprintf_s(szBuffer, text, args);
	va_end(args);
	if (CurrentCanvas)
		Func::K2_DrawText(CurrentCanvas, Roboto, AnsiToUnicode(szBuffer), FVector2D(x, y), Color, 1,FLinearColor(0, 0, 0, 1), FVector2D(), bCentreX, false, true, BgColor);
}
//void UCanvas::DrawTextA(float x, float y, FLinearColor Color, FLinearColor BgColor, const char* text, bool bCentreX, bool bCentreY, bool bOutlined)
//{
//	if (!check_rects(x, y, x, y))
//		return;
//	if (CurrentCanvas)
//		Func::K2_DrawText(CurrentCanvas, TSLFont, AnsiToUnicode(text), FVector2D(x, y), Color, 1, FLinearColor(0, 0, 0, 1), FVector2D(), bCentreX, bCentreY, bOutlined, BgColor);
//}
//void UCanvas::DrawTextA(float x, float y, FLinearColor Color, FLinearColor BgColor, bool bCentreX, const char* text, ...)
//{
//	if (!check_rects(x, y, x, y))
//		return;
//	char szBuffer[4096] = { 0 };
//	va_list args;
//	va_start(args, text);
//	vsprintf_s(szBuffer, text, args);
//	va_end(args);
//	if (CurrentCanvas)
//		Func::K2_DrawText(CurrentCanvas, TSLFont, AnsiToUnicode(szBuffer), FVector2D(x, y), Color, 1, FLinearColor(0, 0, 0, 1), FVector2D(), bCentreX, false, true, BgColor);
//}
//
//void UCanvas::DrawTextB(float x, float y, FLinearColor Color, FLinearColor BgColor, const char* text, bool bCentreX, bool bCentreY, bool bOutlined)
//{
//	if (!check_rects(x, y, x, y))
//		return;
//	if (CurrentCanvas)
//		Func::K2_DrawText(CurrentCanvas, RobotoTiny, AnsiToUnicode(text), FVector2D(x, y), Color, 1, FLinearColor(0, 0, 0, 1), FVector2D(), bCentreX, bCentreY, bOutlined, BgColor);
//}
//void UCanvas::DrawTextB(float x, float y, FLinearColor Color, FLinearColor BgColor, bool bCentreX, const char* text, ...)
//{
//	if (!check_rects(x, y, x, y))
//		return;
//	char szBuffer[4096] = { 0 };
//	va_list args;
//	va_start(args, text);
//	vsprintf_s(szBuffer, text, args);
//	va_end(args);
//	if (CurrentCanvas)
//		Func::K2_DrawText(CurrentCanvas, RobotoTiny, AnsiToUnicode(szBuffer), FVector2D(x, y), Color, 1, FLinearColor(0, 0, 0, 1), FVector2D(), bCentreX, false, true, BgColor);
//}
//void UCanvas::DrawTextB(float x, float y, FLinearColor Color, FLinearColor BgColor, bool bCentreX, bool bCentreY, const char* text, ...)
//{
//	if (!check_rects(x, y, x, y))
//		return;
//	char szBuffer[4096] = { 0 };
//	va_list args;
//	va_start(args, text);
//	vsprintf_s(szBuffer, text, args);
//	va_end(args);
//	if (CurrentCanvas)
//		Func::K2_DrawText(CurrentCanvas, RobotoTiny, AnsiToUnicode(szBuffer), FVector2D(x, y), Color, 1, FLinearColor(0, 0, 0, 1), FVector2D(), bCentreX, bCentreY, true, BgColor);
//}

void UCanvas::DrawCircle(float x, float y, int radius, int numSides, FLinearColor Color)
{
	if (!check_rects(x, y, x, y))
		return;
	if (CurrentCanvas)
	{
		float Step = PI * 2.0 / numSides;
		int Count = 0;
		FVector2D V[128];

		for (float a = 0; a < PI * 2.0; a += Step) {
			float X1 = radius * cos(a) + x;
			float Y1 = radius * sin(a) + y;
			float X2 = radius * cos(a + Step) + x;
			float Y2 = radius * sin(a + Step) + y;
			V[Count].X = X1;
			V[Count].Y = Y1;
			V[Count + 1].X = X2;
			V[Count + 1].Y = Y2;
			DrawLine(V[Count].X, V[Count].Y, X2, Y2, 1.0f, Color);
		}
	}
}
void UCanvas::DrawFillCircle(float x, float y, float radius, FLinearColor Color) {
	if (!check_rects(x, y, x, y))
		return;
	if (CurrentCanvas)
	{
		int tx = 0, ty = radius, d = 3 - 2 * radius;

		while (tx < ty)
		{
			DrawLine(x - ty, y - tx, x + ty, y - tx, 1, Color);
			if (tx != 0)
				DrawLine(x - ty, y + tx, x + ty, y + tx, 1, Color);
			if (d < 0)
				d += 4 * tx + 6;
			else
			{
				DrawLine(x - tx, y - ty, x + tx, y - ty, 1, Color);
				DrawLine(x - tx, y + ty, x + tx, y + ty, 1, Color);
				d += 4 * (tx - ty) + 10;
				ty--;
			}
			tx++;
		}
		if (tx == ty)
		{
			DrawLine(x - ty, y - tx, x + ty, y - tx, 1, Color);
			DrawLine(x - ty, y + tx, x + ty, y + tx, 1, Color);
		}
	}
}
void UCanvas::DrawX(FVector2D center, float len, FLinearColor Color, float thickness) {
	DrawLine(center.X - len, center.Y - len, center.X + len, center.Y + len, thickness, Color);
	DrawLine(center.X + len, center.Y - len, center.X - len, center.Y + len, thickness, Color);
}