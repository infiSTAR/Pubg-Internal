#pragma once
#undef DrawText
namespace UCanvas
{
	extern ULONG64 Canvas;
	extern ULONG64 DebugCanvas;
	extern ULONG64 CurrentCanvas;
	extern ULONG64 Roboto;
	extern ULONG64 TSLFont;
	extern ULONG64 RobotoTiny;

	void Init();
	void SetCanvas(ULONG64 pCanvas);
	void DrawLine(float x1, float y1, float x2, float y2, float thickness, FLinearColor color);
	void DrawRect(float x, float y, float w, float h, float thickness, FLinearColor color);
	void K2_DrawTexture(ULONG64 RenderTexture, FVector2D ScreenPosition, FVector2D ScreenSize, FVector2D CoordinatePosition, FVector2D CoordinateSize, FLinearColor RenderColor, EBlendMode BlendMode, float Rotation, FVector2D PivotPoint);
	void DrawFilled(float x, float y, float w, float h, FLinearColor color);
	void DrawText(float x, float y, FLinearColor Color, FLinearColor BgColor, bool bCentreX, const char* text, ...);
	/*void DrawTextA(float x, float y, FLinearColor Color, FLinearColor BgColor, bool bCentreX, const char* text, ...);
	void DrawTextB(float x, float y, FLinearColor Color, FLinearColor BgColor, bool bCentreX, const char* text, ...);
	void DrawTextB(float x, float y, FLinearColor Color, FLinearColor BgColor, bool bCentreX, bool bCentreY, const char* text, ...);*/
	void DrawText(float x, float y, FLinearColor Color, FLinearColor BgColor, const char* text, bool bCentreX, bool bCentreY, bool bOutlined);
	//void DrawTextA(float x, float y, FLinearColor Color, FLinearColor BgColor, const char* text, bool bCentreX, bool bCentreY, bool bOutlined);
	//void DrawTextB(float x, float y, FLinearColor Color, FLinearColor BgColor, const char* text, bool bCentreX, bool bCentreY, bool bOutlined);
	void DrawCircle(float x, float y, int radius, int numSides, FLinearColor Color);
	void DrawFillCircle(float x, float y, float radius, FLinearColor Color);
	void DrawX(FVector2D center, float len, FLinearColor Color, float thickness);

};
