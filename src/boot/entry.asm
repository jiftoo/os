format elf64
use32

section ".entry"
extrn long_mode_start

public start
start:
	mov esp, stack_top

	call check_multiboot
	call check_cpuid
	call check_long_mode

	call setup_page_tables
	call enable_paging

	lgdt [gdt64.desc] ;[gdt64.pointer]

    push ebx
    push gdt64.code
    push gdt64.data
    mov edi, esp
	jmp gdt64.code:long_mode_start
	hlt

check_multiboot:
	cmp eax, 0x36d76289
	jne .no_multiboot
	ret
.no_multiboot:
	mov al, "M"
	jmp error

check_cpuid:
	pushfd
	pop eax
	mov ecx, eax
	xor eax, 1 shl 21
	push eax
	popfd
	pushfd
	pop eax
	push ecx
	popfd
	cmp eax, ecx
	je .no_cpuid
	ret
.no_cpuid:
	mov al, "C"
	jmp error

check_long_mode:
	mov eax, 0x80000000
	cpuid
	cmp eax, 0x80000001
	jb .no_long_mode

	mov eax, 0x80000001
	cpuid
	test edx, 1 shl 29
	jz .no_long_mode
	
	ret
.no_long_mode:
	mov al, "L"
	jmp error

setup_page_tables:
	mov eax, page_table_l3
	or eax, 11b ; present, writable
	mov [page_table_l4], eax
	
	mov eax, page_table_l2
	or eax, 11b ; present, writable
	mov [page_table_l3], eax

	mov ecx, 0 ; counter
.loop:
	mov eax, 0x200000 ; 2MiB
	mul ecx
	or eax, 10000011b ; present, writable, huge page
	mov [page_table_l2 + ecx * 8], eax

	inc ecx ; increment counter
	cmp ecx, 512 ; checks if the whole table is mapped
	jne .loop ; if not, continue

	ret

enable_paging:
	; pass page table location to cpu
	mov eax, page_table_l4
	mov cr3, eax

	; enable PAE
	mov eax, cr4
	or eax, 1 shl 5
	mov cr4, eax

	; enable long mode
	mov ecx, 0xC0000080
	rdmsr
	or eax, 1 shl 8
	wrmsr

	; enable paging
	mov eax, cr0
	or eax, 1 shl 31
	mov cr0, eax

	ret

error:
	; print "ERR: X" where X is the error code
	mov dword [0xb8000], 0x4f524f45
	mov dword [0xb8004], 0x4f3a4f52
	mov dword [0xb8008], 0x4f204f20
	mov byte  [0xb800a], al
	hlt

section ".bss" align 4096
align 4096
page_table_l4:
	rb 4096
page_table_l3:
	rb 4096
page_table_l2:
	rb 4096
stack_bottom:
	rb 4096 * 4
stack_top:

; section ".rodata"
; gdt64:
; 	dq 0 ; zero entry
; CODE_SEGMENT = $ - gdt64
; 	dq (1 shl 43) or (1 shl 44) or (1 shl 47) or (1 shl 53) ; code segment
; .pointer:
; 	dw $ - gdt64 - 1 ; length
; 	dq gdt64 ; address

gdt64:
    dq 0x0000000000000000       ; Null Descriptor
.code = $ - gdt64             ; Code segment
    dq 0x0020980000000000
.data = $ - gdt64             ; Data segment
    dq 0x0000920000000000
.desc:
    dw $ - gdt64 - 1            ; 16-bit Size (Limit)
    dq gdt64                    ; 64-bit Base Address