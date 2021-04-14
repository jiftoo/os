#include "types.h"
#include "io.h"
#include "print.h"
#include "string.h"

typedef struct __attribute__((packed))
{
    UShort offset_1;
    UShort selector;
    UShort type;
    UShort offset_2;
    UInt offset_3;
    UInt zero; // bruh it's an int
} IDT_ENTRY;

typedef struct __attribute__((packed))
{
    UShort limit;
    ULong base;
} IDTPointer;

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15(); // 'Unknown interrupt'
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

extern void irq60();
extern void irq69();

extern void LoadIDT();

typedef struct
{
    ULong gs, fs, es, ds;
    ULong rax, rbx, rcx, rdx, rbp, rsi, rdi, /*rsp*/ r8, r9, r10, r11, r12, r13, r14, r15;
    ULong intNum, errCode;
    ULong rip, cs, eflags, rsp, ss;
} Registers;

Char *interruptMessages[] = {
    "Division By Zero",       //0
    "Debug",                  //1
    "Non Maskable Interrupt", //2
    "Breakpoint",             //3
    "Into Detected Overflow", //4
    "Out of Bounds",          //5
    "Invalid Opcode",         //6
    "No Coprocessor",         //7

    "Double Fault",                //8
    "Coprocessor Segment Overrun", //9
    "Bad TSS",                     //10
    "Segment Not Present",         //11
    "Stack Fault",                 //12
    "General Protection Fault",    //13
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
};

#define STRNUMBAS(str, num, buf)      \
    Print(str);                       \
    Print(" - ");                     \
    Print(IntToString(num, buf, 10)); \
    Print(" 0x");                     \
    Print(IntToString(num, buf, 16)); \
    Print(" b");                      \
    Println(IntToString(num, buf, 2));

#define STRNUMBASNO2(str, num, buf)   \
    Print(str);                       \
    Print(" - ");                     \
    Print(IntToString(num, buf, 10)); \
    Print(" 0x");                     \
    Println(IntToString(num, buf, 16));

void FaultHandler(Registers *regs) // 0-31 CPU isr
{
    SetPrintColor(COLOR_WHITE, COLOR_LIGHT_RED);
    ClearScreen();
    ResetCursor();
    Char buf[256];
    Print(" ------ FATAL EXCEPTION: '");
    Print(interruptMessages[regs->intNum]);
    Println("' ------");
    STRNUMBAS("Int:  ", regs->intNum, buf);
    STRNUMBAS("Err:  ", regs->errCode, buf);
    STRNUMBAS("RIP:  ", regs->rip, buf);
    STRNUMBAS("CS:   ", regs->cs, buf);
    STRNUMBAS("Eflg: ", regs->eflags, buf);
    STRNUMBAS("RSP:  ", regs->rsp, buf);
    STRNUMBAS("SS:   ", regs->ss, buf);

    STRNUMBASNO2("R15:  ", regs->r15, buf);
    STRNUMBASNO2("R14:  ", regs->r14, buf);
    STRNUMBASNO2("R13:  ", regs->r13, buf);
    STRNUMBASNO2("R12:  ", regs->r12, buf);
    STRNUMBASNO2("R11:  ", regs->r11, buf);
    STRNUMBASNO2("R10:  ", regs->r10, buf);
    STRNUMBASNO2("R09:  ", regs->r9, buf);
    STRNUMBASNO2("R08:  ", regs->r8, buf);
    STRNUMBASNO2("RSI:  ", regs->rsi, buf);
    STRNUMBASNO2("RDI:  ", regs->rdi, buf);
    STRNUMBASNO2("RBP:  ", regs->rbp, buf);
    STRNUMBASNO2("RDX:  ", regs->rdx, buf);
    STRNUMBASNO2("RCX:  ", regs->rcx, buf);
    STRNUMBASNO2("RBP:  ", regs->rbp, buf);
    STRNUMBASNO2("RAX:  ", regs->rax, buf);

    PutChar('\n');

    while (1)
        asm volatile("hlt");
}

void IrqHandler(Registers *regs) // 0-31 CPU isr // Registers numbah
{
    OutByte(0x20, 0x20);
    if (regs->errCode >= 8)
    {
        OutByte(0xA0, 0x20);
    }
}

IDTPointer IDTPtr;
IDT_ENTRY IDT[256];
void *IrqHandlers[256] = {0};

#define INTERRUPT_GATE 0x8e00
#define TRAP_GATE 0x8f00

#define Interrupt(n, h) _EnableInterrupt(n, (ULong)h, INTERRUPT_GATE)
#define Interrupt_sf(n, h, t) _EnableInterrupt(n, (ULong)h, t)
void _EnableInterrupt(UByte number, ULong handler, UShort type)
{
    IDT[number].offset_1 = (UShort)handler;
    IDT[number].selector = 0x08;
    IDT[number].type = type;
    IDT[number].offset_2 = (UShort)(handler >> 16);
    IDT[number].offset_3 = (UInt)(handler >> 32);
    IDT[number].zero = 0;

    // UShort offset_1;
    // UShort selector;
    // UShort type;
    // UShort offset_2;
    // UInt offset_3;
    // UInt zero;
}

Bool InitInterrupts()
{
    IDTPtr.limit = sizeof(IDT_ENTRY) * 256 - 1;
    IDTPtr.base = (ULong)&IDT;

    LoadIDT();

    for (UInt i = 0; i < 255; i++)
    {
        Interrupt(i, isr15);
    }

    Interrupt(0, isr0);
    Interrupt(1, isr1);
    Interrupt(2, isr2);
    Interrupt(3, isr3);
    Interrupt(4, isr4);
    Interrupt(5, isr5);
    Interrupt(6, isr6);
    Interrupt(7, isr7);
    Interrupt(8, isr8);
    Interrupt(9, isr9);
    Interrupt(10, isr10);
    Interrupt(11, isr11);
    Interrupt(12, isr12);
    Interrupt(13, isr13);
    Interrupt(14, isr14);
    Interrupt(15, isr15);
    Interrupt(16, isr16);
    Interrupt(17, isr17);
    Interrupt(18, isr18);
    Interrupt(19, isr19);
    Interrupt(20, isr20);
    Interrupt(21, isr21);
    Interrupt(22, isr22);
    Interrupt(23, isr23);
    Interrupt(24, isr24);
    Interrupt(25, isr25);
    Interrupt(26, isr26);
    Interrupt(27, isr27);
    Interrupt(28, isr28);
    Interrupt(29, isr29);
    Interrupt(30, isr30);
    Interrupt(31, isr31);

    // Remap PIC
    OutByte(0x20, 0x11);
    OutByte(0xA0, 0x11);
    OutByte(0x21, 0x20);
    OutByte(0xA1, 40);
    OutByte(0x21, 0x04);
    OutByte(0xA1, 0x02);
    OutByte(0x21, 0x01);
    OutByte(0xA1, 0x01);
    OutByte(0x21, 0x0);
    OutByte(0xA1, 0x0);

    Interrupt(32, irq0);
    Interrupt(33, irq1);
    Interrupt(34, irq2);
    Interrupt(35, irq3);
    Interrupt(36, irq4);
    Interrupt(37, irq5);
    Interrupt(38, irq6);
    Interrupt(39, irq7);
    Interrupt(40, irq8);
    Interrupt(41, irq9);
    Interrupt(42, irq10);
    Interrupt(43, irq11);
    Interrupt(44, irq12);
    Interrupt(45, irq13);
    Interrupt(46, irq14);
    Interrupt(47, irq15);

    Interrupt(60, irq60);
    Interrupt(69, irq69);

    asm volatile("sti");

    return True;
}