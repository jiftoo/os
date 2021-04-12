#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define BYTE_MAX  0x7F
#define BYTE_MIN -0x80
#define UBYTE_MAX 0xFF

typedef int8_t Byte;
typedef uint8_t UByte;

#define SHORT_MAX  0x7FFF
#define SHORT_MIN -0x8000
#define USHORT_MAX  0xFFFF

typedef int16_t Short;
typedef uint16_t UShort;

#define INT_MAX   0x7FFFFFFF
#define INT_MIN  -0x80000000
#define UINT_MAX 0xFFFFFFFF

typedef int32_t Int;
typedef uint32_t UInt;

#define LONG_MAX  0x7FFFFFFFFFFFFFFF
#define LONG_MIN -0x8000000000000000
#define ULONG_MAX 0xFFFFFFFFFFFFFFFF

typedef int64_t Long;
typedef uint64_t ULong;

#ifdef SIZE_MAX
#undef SIZE_MAX
#endif
#define SIZE_MAX 0xffffffff

typedef UInt Size;

#define TRUE 1
#define FALSE 0
#define True 1
#define False 0
typedef bool Bool;

#define CHAR_MAX  0x7F
#define CHAR_MIN -0x80
typedef char Char;