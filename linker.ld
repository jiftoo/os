ENTRY(start)

SECTIONS
{
	. = 1M;

	.boot :
	{
		KEEP(*(.multiboot))
	}

	.text :
	{
        KEEP(*(.entry)) /* Put the loading code before everything else. Won't boot otherwise */
		*(.text)
	}
}