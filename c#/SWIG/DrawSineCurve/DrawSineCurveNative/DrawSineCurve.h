// 2016-07-14T10:51+08:00
#pragma once

#define WIN32_LEAN_AND_MEAN
#define STRICT 1
#include <Windows.h>
#include <windowsx.h>

enum PenStyle
{
	Solid = 0, //PS_SOLID,
	Dash = 1, //PS_DASH,
	Dot = 2, //PS_DOT,
	DashDot = 3, //PS_DASHDOT,
	DashDotDot = 4, //PS_DASHDOTDOT,
};

struct PenProperty
{
	COLORREF Color;
	int Width;
	PenStyle Style;
};

void DrawSineCurve(HDC hdc, const RECT &rc, const PenProperty &pen, int xTicksCount = 1000);
