format elf64

section ".multiboot"

MB_FLAGS = 0 and (1 shl 2)

header_start:
dd 0xe85250d6
dd MB_FLAGS
dd header_end - header_start
dd 0x100000000 - (0xe85250d6 + MB_FLAGS + (header_end - header_start))
dd 0
dd 0 ; 8?
dd 0
dd 0
dd 0

dd 0 ; video mode
dd 80
dd 50
dd 0
header_end:
