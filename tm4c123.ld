MEMORY
{
    FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = 0x00040000
    RAM (rwx)   : ORIGIN = 0x20000000, LENGTH = 0x00008000
}

ENTRY(ResetISR)

/* Define the sections */
SECTIONS
{
    /* The startup code goes first into FLASH */
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } > FLASH

    /* The program code and other data goes into FLASH */
    .text :
    {
        _text_start = .;
        *(.text*)
        *(.rodata*)
        _etext = .;
    } > FLASH

    /* Initialised data section into RAM */
    .data : AT ( _etext )
    {
        _data_start = .;
        *(.data)
        _data_end = .;
    } > RAM

    /* Uninitialized data section into RAM */
    .bss :
    {
        _bss_start = .;
        *(.bss)
        *(COMMON)
        _bss_end = .;
    } > RAM

    /* User_heap_stack section, used to check that there is enough RAM left */
    ._user_heap_stack :
    {
        _heap_start = .;
        . = ALIGN(8);
        _heap_end = .;
        _stack_start = .;
        . = ALIGN(8);
        _stack_end = .;
    } > RAM

    PROVIDE(_data = _data_start);
    PROVIDE(_edata = _data_end);
    PROVIDE(_bss = _bss_start);
    PROVIDE(_ebss = _bss_end);
}

