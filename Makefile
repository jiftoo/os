x86_asm_src := $(shell find src -name *.asm)
x86_asm_obj := $(patsubst src/%.asm, build/obj/%.o, $(x86_asm_src))

x86_64_c_src := $(shell find src -name *.c)
x86_64_c_obj := $(patsubst src/%.c, build/obj/%.o, $(x86_64_c_src))

#TODO: Update whenever
x86_64_obj := $(x86_64_c_obj) $(x86_asm_obj)

$(x86_64_c_obj): build/obj/%.o : src/%.c
	@mkdir -p $(dir $@) && \
	x86_64-elf-gcc -mno-red-zone -std=gnu99 -Werror=implicit-function-declaration -Wall -Wextra -c -I src/kernel/h -ffreestanding $(patsubst build/obj/%.o, src/%.c, $@) -o $@

$(x86_asm_obj): build/obj/%.o : src/%.asm
	@mkdir -p $(dir $@) && \
	fasm $(patsubst build/obj/%.o, src/%.asm, $@) $@ 1> /dev/null

.PHONY: build
build: $(x86_64_obj) $(x86_asm_obj)
	@x86_64-elf-ld -nostdlib -n -o bin/kernel.bin -T linker.ld $(x86_64_obj) && \
	cp bin/kernel.bin build/grub/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o bin/kernel.iso build/grub > /dev/null 2>&1 && \
	rm -r build/obj/* && \
	rm build/grub/boot/kernel.bin 
