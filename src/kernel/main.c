#include "print.h"
#include "multiboot.h"
#include "string.h"
#include "multiboot.h"
#include "io.h"
#include "int.h"
#include "types.h"
#include "branch.h"

static inline void cpuid(int code, uint32_t *a, uint32_t *d)
{
    asm volatile("cpuid"
                 : "=a"(*a), "=d"(*d)
                 : "a"(code)
                 : "ecx", "ebx");
}

void __attribute__((noreturn)) kmain() // multiboot_info_t info
{
    SetPrintColor(COLOR_WHITE, COLOR_CYAN);
    ClearScreen();

    InitPalette();
    PrintPalette(True);

    BRANCH(InitSerial(), Println("SERIAL INIT OK");, Println("SERIAL INIT FAIL"););
    BRANCH(InitInterrupts(), Println("INTERRUPT INIT OK");, Println("INTERRUPT INIT FAIL"););

    SetPrintColor(COLOR_LIGHT_GREEN, COLOR_CYAN);
    Println("IDLE");

    while (1)
        asm volatile("hlt");
}
