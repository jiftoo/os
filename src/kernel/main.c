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

void kmain() // multiboot_info_t info
{
    ClearScreen();

    BRANCH(InitSerial(), Println("SERIAL INIT OK");, Println("SERIAL INIT FAIL"););
    BRANCH(InitInterrupts(), Println("INTERRUPT INIT OK");, Println("INTERRUPT INIT FAIL"););

    SetPrintColor(PRINT_COLOR_LIGHT_GREEN, PRINT_COLOR_BLACK);
    Println("IDLE");
}
