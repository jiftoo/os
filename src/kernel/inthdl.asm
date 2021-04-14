format elf64
use64
section ".text"

public LoadIDT

extrn IDTPtr

extrn Print

public isr_handler_stub
public irq_common_stub

extrn FaultHandler
extrn IrqHandler

macro PUSHAQ {
    push   rax
    push   rbx
    push   rcx
    push   rdx
    push   rbp
    push   rsi
    push   rdi
    ; push   rsp
    push   r8
    push   r9
    push   r10
    push   r11
    push   r12
    push   r13
    push   r14
    push   r15
}

macro POPAQ {
    pop       r15
    pop       r14
    pop       r13
    pop       r12
    pop       r11
    pop       r10
    pop       r9
    pop       r8
    ; pop       rsp
    pop       rdi
    pop       rsi
    pop       rbp
    pop       rdx
    pop       rcx
    pop       rbx
    pop       rax
}

isr_handler_stub:
    PUSHAQ
    mov rdi, rsp ; pass the argument to C funciton
    call FaultHandler
    POPAQ
    add rsp, 16 ; i'm not sure about the size
    iretq
    ret

irq_common_stub:
    PUSHAQ
    mov rdi, rsp ; pass the argument to C funciton
    call IrqHandler
    POPAQ
    add rsp, 16 ;; ^
    iretq
    ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

LoadIDT:
        lidt [IDTPtr]
        ret

public isr0
public isr1
public isr2
public isr3
public isr4
public isr5
public isr6
public isr7
public isr8
public isr9
public isr10
public isr11
public isr12
public isr13
public isr14
public isr15
public isr16
public isr17
public isr18
public isr19
public isr20
public isr21
public isr22
public isr23
public isr24
public isr25
public isr26
public isr27
public isr28
public isr29
public isr30
public isr31

public irq0
public irq1
public irq2
public irq3
public irq4
public irq5
public irq6
public irq7
public irq8
public irq9
public irq10
public irq11
public irq12
public irq13
public irq14
public irq15

public irq69
public irq60

isr0:
    cli
    push 0
    push 0
    jmp isr_handler_stub

; 1: Debug Exception
isr1:
    cli
    push 0
    push 1
    jmp isr_handler_stub

; 2: Non Maskable Interrupt Exception
isr2:
    cli
    push 0
    push 2
    jmp isr_handler_stub

; 3: Int 3 Exception
isr3:
    cli
    push 0
    push 3
    jmp isr_handler_stub

; 4: INTO Exception
isr4:
    cli
    push 2
    push 4
    jmp isr_handler_stub

; 5: Out of Bounds Exception
isr5:
    cli
    push 0
    push 5
    jmp isr_handler_stub

; 6: Invalid Opcode Exception
isr6:
    cli
    push 0
    push 6
    jmp isr_handler_stub

; 7: Coprocessor Not Available Exception
isr7:
    cli
    push 0
    push 7
    jmp isr_handler_stub

; 8: Double Fault Exception (With Error Code!)
isr8:
    cli
    push 8
    jmp isr_handler_stub

; 9: Coprocessor Segment Overrun Exception
isr9:
    cli
    push 0
    push 9
    jmp isr_handler_stub

; 10: Bad TSS Exception (With Error Code!)
isr10:
    cli
    push 10
    jmp isr_handler_stub

; 11: Segment Not Present Exception (With Error Code!)
isr11:
    cli
    push 11
    jmp isr_handler_stub

; 12: Stack Fault Exception (With Error Code!)
isr12:
    cli
    push 12
    jmp isr_handler_stub

; 13: General Protection Fault Exception (With Error Code!)
isr13:
    cli
    push 13
    jmp isr_handler_stub

; 14: Page Fault Exception (With Error Code!)
isr14:
    cli
    push 14
    jmp isr_handler_stub

; 15: Unknown Interrupt
; Do nothing
isr15:
    cli
    iretq

; 16: Floating Point Exception
isr16:
    cli
    push 0
    push 16
    jmp isr_handler_stub

; 17: Alignment Check Exception
isr17:
    cli
    push 0
    push 17
    jmp isr_handler_stub

; 18: Machine Check Exception
isr18:
    cli
    push 0
    push 18
    jmp isr_handler_stub

; 19: Reserved
isr19:
    cli
    push 0
    push 19
    jmp isr_handler_stub

; 20: Reserved
isr20:
    cli
    push 0
    push 20
    jmp isr_handler_stub

; 21: Reserved
isr21:
    cli
    push 0
    push 21
    jmp isr_handler_stub

; 22: Reserved
isr22:
    cli
    push 0
    push 22
    jmp isr_handler_stub

; 23: Reserved
isr23:
    cli
    push 0
    push 23
    jmp isr_handler_stub

; 24: Reserved
isr24:
    cli
    push 0
    push 24
    jmp isr_handler_stub

; 25: Reserved
isr25:
    cli
    push 0
    push 25
    jmp isr_handler_stub

; 26: Reserved
isr26:
    cli
    push 0
    push 26
    jmp isr_handler_stub

; 27: Reserved
isr27:
    cli
    push 0
    push 27
    jmp isr_handler_stub

; 28: Reserved
isr28:
    cli
    push 0
    push 28
    jmp isr_handler_stub

; 29: Reserved
isr29:
    cli
    push 0
    push 29
    jmp isr_handler_stub

; 30: Reserved
isr30:
    cli
    push 0
    push 30
    jmp isr_handler_stub

; 31: Reserved
isr31:
    cli
    push 0
    push 31
    jmp isr_handler_stub


; IRQ handlers
irq0:
        cli
        push 0
        push 32
        jmp irq_common_stub

irq1:
        cli
        push 1
        push 33
        jmp irq_common_stub

irq2:
        cli
        push 2
        push 34
        jmp irq_common_stub

irq3:
        cli
        push 3
        push 35
        jmp irq_common_stub

irq4:
        cli
        push 4
        push 36
        jmp irq_common_stub

irq5:
        cli
        push 5
        push 37
        jmp irq_common_stub

irq6:
        cli
        push 6
        push 38
        jmp irq_common_stub

irq7:
        cli
        push 7
        push 39
        jmp irq_common_stub

irq8:
        cli
        push 8
        push 40
        jmp irq_common_stub

irq9:
        cli
        push 9
        push 41
        jmp irq_common_stub

irq10:
        cli
        push 10
        push 42
        jmp irq_common_stub

irq11:
        cli
        push 11
        push 43
        jmp irq_common_stub

irq12:
        cli
        push 12
        push 44
        jmp irq_common_stub

irq13:
        cli
        push 13
        push 45
        jmp irq_common_stub

irq14:
        cli
        push 14
        push 46
        jmp irq_common_stub

irq15:
        cli
        push 15
        push 47
        jmp irq_common_stub



irq60:
        cli
        push 60
        push 60
        jmp irq_common_stub

irq69:
        cli
        push 69
        push 69
        jmp irq_common_stub
