format elf64
use64
section ".entry"

extrn kmain
extrn Println
public long_mode_start

bruhmoment_message: db "You're back in long.asm bruh"

long_mode_start:
    
    mov rax, rsp

    push 0x10
    push rax
    pushf
    push 0x08
    push .reload_segments
    iretq

.reload_segments:
    mov ax, 0x10
    mov ss, ax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call kmain

    mov rdi, [bruhmoment_message]
    call Println

    hlt