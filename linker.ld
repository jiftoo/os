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
        KEEP(*(.entry)) /* Won't boot otherwise i put the loading code in .entry and include it here */
		*(.text)
	}
}