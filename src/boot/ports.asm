[BITS 32]

; [GLOBAL _notsti]

; _notsti: 
;     sti 
;     ret

[GLOBAL _inb]
[GLOBAL _outb]



_inb:
    mov dx, [esp + 4]
    in al, dx
    ret
    
_outb:
    mov dx, [esp + 4]
    mov al, byte [esp + 8]
    out dx, al
    ret
