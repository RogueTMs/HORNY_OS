[BITS 32]

[GLOBAL _entry1]
[GLOBAL _set_esp]


; mov esp, _entry1
; jmp _entry1




_set_esp:
    pop edx
    pop eax
    mov esp, edx
    pop edx
    jmp eax

_entry1:
    mov eax, clown
    int 0x69
    ret

clown: 
    dq "Hello, world!"

