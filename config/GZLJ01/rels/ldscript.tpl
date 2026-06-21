SECTIONS
{
    GROUP:
    {
        .init :{}
        .text ALIGN(0x4):{}
        .ctors ALIGN(0x4):{}
        .dtors ALIGN(0x4):{}
        .rodata ALIGN(0x8):{}
        .data ALIGN(0x8):{ *(.data) *(extabindex) *(extab) }
        .bss ALIGN(0x8):{}
    }
}

FORCEACTIVE
{
	$FORCEACTIVE
}
