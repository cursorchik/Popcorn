#pragma once

#include <Windows.h>

#include "Config.h"
#include "Level.h"

class ABall
{
public:
	ABall();
	void Init();

	void Draw(HDC hdc, RECT &paint_area);
	void Move(HWND hwnd, ALevel *level, int platform_x_pos, int platform_width);

	HPEN Ball_Pen;
	HBRUSH Ball_Brush;
	double Ball_Direction;

private:
	int Ball_X_Pos, Ball_Y_Pos;
	double Ball_Speed;

	RECT Ball_Rect, Prev_Ball_Rect;
};
