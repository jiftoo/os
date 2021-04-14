#include "print.h"
#include "io.h"

struct TermChar
{
    UByte character;
    UByte color;
};

struct TermChar *buffer = (struct TermChar *)0xb8000;
size_t col = 0;
size_t row = 0;
UByte color = COLOR_WHITE | COLOR_BLACK << 4;

void ClearRow(size_t row)
{
    struct TermChar empty = (struct TermChar){
        character : ' ',
        color : color,
    };

    for (size_t col = 0; col < NUM_COLS; col++)
    {
        buffer[col + NUM_COLS * row] = empty;
    }
}

void ClearScreen()
{
    for (size_t i = 0; i < NUM_ROWS; i++)
    {
        ClearRow(i);
    }
}

void ResetCursor()
{
    col = 0;
    row = 0;
}

void PutNewline()
{
    SerialChar('\n');

    col = 0;

    if (row < NUM_ROWS - 1)
    {
        row++;
        return;
    }

    for (size_t row = 1; row < NUM_ROWS; row++)
    {
        for (size_t col = 0; col < NUM_COLS; col++)
        {
            struct TermChar character = buffer[col + NUM_COLS * row];
            buffer[col + NUM_COLS * (row - 1)] = character;
        }
    }

    ClearRow(NUM_COLS - 1);
}

void PutChar(Char character)
{
    if (character == '\n')
    {
        PutNewline();
        return;
    }

    if (col > NUM_COLS)
    {
        PutNewline();
    }

    buffer[col + NUM_COLS * row] = (struct TermChar){
        character : (UByte)character,
        color : color,
    };
    SerialChar(character);

    col++;
}

void Print(Char *str)
{
    for (size_t i = 0; 1; i++)
    {
        Char character = (UByte)str[i];

        if (character == '\0')
        {
            return;
        }

        PutChar(character);
    }
}
void Println(Char *str)
{
    for (size_t i = 0; 1; i++)
    {
        Char character = (UByte)str[i];

        if (character == '\0')
        {
            PutChar('\n');
            return;
        }

        PutChar(character);
    }
}

void SetPrintColor(UByte foreground, UByte background)
{
    color = foreground + (background << 4);
}

void ScreenColor(UByte color)
{
    for (Size i = 0; i < NUM_ROWS * NUM_COLS; i++)
    {
        buffer[i].color |= color << 4;
    }
}

UByte GetColor()
{
    return color;
}

void RestoreColor(UByte clr)
{
    color = clr;
}