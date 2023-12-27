[BITS 32]

[GLOBAL _entry]

_entry:
    mov eax, [esp + 4]
    int 0x69
    ret
