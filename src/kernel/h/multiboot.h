#pragma once

/* The section header table for ELF. */
typedef struct elf_section_header_table
{
    ULong num;
    ULong size;
    ULong addr;
    ULong shndx;
} elf_section_header_table_t;

typedef struct multiboot_info
{
    ULong flags;
    ULong mem_lower;
    ULong mem_upper;
    ULong boot_device;
    ULong cmdline;
    ULong mods_count;
    ULong mods_addr;
    elf_section_header_table_t elf_sec;
    ULong mmap_length;
    ULong mmap_addr;
} multiboot_info_t;