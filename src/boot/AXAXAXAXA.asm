[BITS 32]

[GLOBAL _entry1]
[GLOBAL _entry2]
[GLOBAL _entry3]
[GLOBAL _entry4]
[GLOBAL _set_esp]


; mov esp, _entry1
; jmp _entry1




_set_esp:
    mov ebx, [esp]
    mov eax, [esp + 4]
    mov esp, eax
    jmp ebx

_entry1:
    mov eax, clown
    int 0x69
    ret

_entry2:
    mov eax, hello
    int 0x69
    ret

_entry3:
    mov eax, lambert
    int 0x69
    ret

_entry4:
    mov eax, alo
    int 0x69
    ret

clown: 
    dq "AXAXAXA"

hello:
    dq "Hello, world!"

lambert:
    dq "Lambert, Lambert, *** morzhovyi, Lambert, Lambert - vrednyi ***"

alo:
    dq "**** po lbu ne dalo"