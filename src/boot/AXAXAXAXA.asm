[BITS 32]

[GLOBAL _pr_1]
[GLOBAL _change_esp]

_pr_1:
    mov eax, clown
    int 0x69
    ret

_change_esp:
    mov edx, [esp + 4]
    jmp edx
    ret


clown: 
    dq "Hello, world!"

