#pragma once

#include "types.h"

#define NUM_COLS 80
#define NUM_ROWS 25

enum
{
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_MAGENTA = 5,
    COLOR_BROWN = 6,
    COLOR_LIGHT_GRAY = 7,
    COLOR_DARK_GRAY = 8,
    COLOR_LIGHT_BLUE = 9,
    COLOR_LIGHT_GREEN = 10,
    COLOR_LIGHT_CYAN = 11,
    COLOR_LIGHT_RED = 12,
    COLOR_PINK = 13,
    COLOR_YELLOW = 14,
    COLOR_WHITE = 15,
};

void ClearScreen();
void ResetCursor();
void PutChar(Char Character);
void Print(Char *string);
void Println(Char *string);
void SetPrintColor(UByte foreground, UByte background);
void ScreenColor(UByte color);