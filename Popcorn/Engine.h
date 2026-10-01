#pragma once

#include <Windows.h>

#define _USE_MATH_DEFINES
#include <math.h>

enum EBrick_Type
{
    EBT_None,
    EBT_Red,
    EBT_Blue,
};

enum ELetter_Type
{
    ELT_None,
    ELT_O,
};

enum EKey_Type
{
    EKT_Left,
    EKT_Right,
    EKT_Space,
};

const int Timer_ID = WM_USER + 1;
const int Timer_Elapse = 30;

class AsEngine;
class ALevel;
class ABall
{
public:
    ABall();

    void Draw(HDC hdc, RECT &paint_area, AsEngine *engine);
    void Move(AsEngine *engine, ALevel *level);

    HPEN Ball_Pen;
    HBRUSH Ball_Brush;
    double Ball_Direction;

    static const int Ball_Size = 4;

private:
    int Ball_X_Pos, Ball_Y_Pos;
    double Ball_Speed;

    RECT Ball_Rect, Prev_Ball_Rect;
};

class ALevel
{
public:
    void Init();
    void Check_Level_Brick_Hit(int& next_y_pos, double &ball_direction);
    void Draw(HDC hdc, RECT &paint_area);

    static const int Level_Width = 12; // Ширина уровня в ячейках
    static const int Level_Height = 14;  // Высота уровня в ячейках
    static const int Level_X_Offset = 8;
    static const int Level_Y_Offset = 6;
    static const int Cell_Width = 16;
    static const int Cell_Height = 8;

private:
    
    void Draw_Brick(HDC hdc, int x, int y, EBrick_Type brick_type);
    void Set_Brick_Letter_Colors(bool is_switch_color, HPEN &front_pen, HPEN &back_pen, HBRUSH &front_brush, HBRUSH &back_brush);
    void Draw_Brick_Letter(HDC hdc, int x, int y, EBrick_Type brick_type, ELetter_Type letter_type, int rotation_step);

    HPEN Brick_Red_Pen, Brick_Blue_Pen, Letter_Pen;
    HBRUSH Brick_Red_Brush, Brick_Blue_Brush;
    RECT Level_Rect;

    static const int Brick_Width = 15;
    static const int Brick_Height = 7;
};

class AsEngine
{
public:

    AsEngine();
    void Init_Engine(HWND hwnd);
    void Draw_Frame(HDC hdc, RECT &paint_area);
    int On_Key_Down(EKey_Type key_type);
    int On_Timer();

    static void Create_Pen_Brush(unsigned char r, unsigned char g, unsigned char b, HPEN &pen, HBRUSH &brush);

    HWND Hwnd;
    HPEN BG_Pen;
    HBRUSH BG_Brush;

    int Platform_X_Pos;
    int Platform_Width;

    static const int Global_Scale = 3;
    static const int Max_X_Pos = ALevel::Level_X_Offset + ALevel::Cell_Width * ALevel::Level_Width;
    static const int Max_Y_Pos = 199 - ABall::Ball_Size;
    static const int Platform_Y_Pos = 185;
    static const int Border_X_Offset = 6;
    static const int Border_Y_Offset = 4;
    static const int Platform_Height = 7;


private:
    void Redraw_Platform();
    void Draw_Platform(HDC hdc, int x, int y);
    void Draw_Border(HDC hdc, int x, int y, bool is_top_border);
    void Draw_Bounds(HDC hdc, RECT &paint_area);

    HPEN Highlight_Pen, Platform_Circle_Pen, Platform_Inner_Pen, Border_Blue_Pen, Border_White_Pen;
    HBRUSH Platform_Circle_Brush, Platform_Inner_Brush, Border_Blue_Brush, Border_White_Brush;

    int Inner_Width;

    int Platform_X_Step;

    RECT Platform_Rect, Prev_Platform_Rect;
    
    ABall Ball;
    ALevel Level;

    static const int Circle_Size = 7;
};