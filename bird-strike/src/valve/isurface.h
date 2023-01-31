#pragma once
#include "../valve/ccolor.h"
#include "../util/memory.h"

class ISurface
{
public:
	enum EFontFlag
	{
		FONT_FLAG_NONE,
		FONT_FLAG_ITALIC = 0x001,
		FONT_FLAG_UNDERLINE = 0x002,
		FONT_FLAG_STRIKEOUT = 0x004,
		FONT_FLAG_SYMBOL = 0x008,
		FONT_FLAG_ANTIALIAS = 0x010,
		FONT_FLAG_GAUSSIANBLUR = 0x020,
		FONT_FLAG_ROTARY = 0x040,
		FONT_FLAG_DROPSHADOW = 0x080,
		FONT_FLAG_ADDITIVE = 0x100,
		FONT_FLAG_OUTLINE = 0x200,
		FONT_FLAG_CUSTOM = 0x400,
		FONT_FLAG_BITMAP = 0x800,
	};

	enum EFontDrawType : std::int32_t
	{
		FONT_DRAW_DEFAULT = 0,
		FONT_DRAW_NONADDITIVE,
		FONT_DRAW_ADDITIVE
	};

	constexpr void DrawSetColor(int r, int g, int b, int a = 255) noexcept
	{
		Memory::CallVirtual<void>(this, 15, r, g, b, a);
	}

	constexpr void DrawFilledRect(int x, int y, int xx, int yy) noexcept
	{
		Memory::CallVirtual<void>(this, 16, x, y, xx, yy);
	}

	constexpr void DrawOutlinedRect(int x, int y, int xx, int yy) noexcept
	{
		Memory::CallVirtual<void>(this, 18, x, y, xx, yy);
	}
	void DrawSetColor(CColor col)
	{
		Memory::CallVirtual<void>(this, 14, col);
	}
	
	void DrawLine(int x0, int y0, int x1, int y1)
	{
		Memory::CallVirtual<void>(this, 19, x0, y0, x1, y1);
	}
	void DrawSetTextFont(unsigned long hFont)
	{
		Memory::CallVirtual<void>(this, 23, hFont);
	}
	void DrawSetTextColor(CColor col)
	{
		Memory::CallVirtual<void>(this, 24, col);
	}
	void DrawSetTextPos(int x, int y)
	{
		Memory::CallVirtual<void>(this, 264, x, y);
	}
	void DrawPrintText(wchar_t* text, int textLen, EFontDrawType drawType = FONT_DRAW_DEFAULT)
	{
		Memory::CallVirtual<void>(this, 28, text, textLen, drawType);
	}
	DWORD FontCreate() 
	{
		return Memory::CallVirtual<DWORD>(this, 71);
	}
	void SetFontGlyphSet(unsigned long font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0)
	{
		Memory::CallVirtual<void>(this, 72, font, windowsFontName, tall, weight, blur, scanlines, flags, nRangeMin, nRangeMax);
	}
	void GetTextSize(unsigned long font, const wchar_t* text, int& wide, int& tall)
	{
		Memory::CallVirtual<void>(this, 79, font, text, wide, tall);
	}
};