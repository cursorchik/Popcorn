#include "Engine.h"

AsEngine::AsEngine()
: Hwnd(0), BG_Pen(0), BG_Brush(0)
{
}

void AsEngine::Init_Engine(HWND hwnd)
{// Настройка игры при старте

    Hwnd = hwnd;

    AsConfig::Create_Pen_Brush(15, 63, 31, BG_Pen, BG_Brush);    

    Ball.Init();
    Level.Init();
    Platform.Init();
    Border.Init();

    Platform.Redraw(hwnd);

    SetTimer(Hwnd, Timer_ID, Timer_Elapse, 0);
}

void AsEngine::Draw_Frame(HDC hdc, RECT& paint_area)
{// Отрисовка экрана игры

    Level.Draw(hdc, paint_area);

    Platform.Draw(hdc, BG_Pen, BG_Brush, paint_area);


    //int i = 0;
    //for (i; i < 16; i++)
    //{
    //    Draw_Brick_Letter(hdc, 20 + i * Cell_Width * Global_Scale, 100, EBT_Blue, ELT_O, i);
    //    Draw_Brick_Letter(hdc, 20 + i * Cell_Width * Global_Scale, 200, EBT_Red, ELT_O, i);
    //}

    Ball.Draw(hdc, paint_area, BG_Pen, BG_Brush);

    Border.Draw(hdc, paint_area, BG_Pen, BG_Brush);
}

int AsEngine::On_Key_Down(EKey_Type key_type)
{
    switch (key_type)
    {
        case EKT_Left:
            Platform.X_Pos -= Platform.X_Step;

            if (Platform.X_Pos <= AsConfig::Border_X_Offset)
                Platform.X_Pos = AsConfig::Border_X_Offset;

            Platform.Redraw(Hwnd);
            break;

        case EKT_Right:
            Platform.X_Pos += Platform.X_Step;

            if (Platform.X_Pos >= AsConfig::Max_X_Pos - Platform.Width + 1)
                Platform.X_Pos = AsConfig::Max_X_Pos - Platform.Width + 1;

            Platform.Redraw(Hwnd);
            break;

        case EKT_Space:
            break;
    }

    return 0;
}

int AsEngine::On_Timer()
{
    Ball.Move(Hwnd, &Level, Platform.X_Pos, Platform.Width);

    return 0;
}