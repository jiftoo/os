#pragma once
#include "types.h"

UByte InByte(UShort port);
void OutByte(UShort port, UByte data);
void SerialPrint(Char *str);
void SerialPrintln(Char *str);
void SerialChar(Char ch);

Bool InitSerial();