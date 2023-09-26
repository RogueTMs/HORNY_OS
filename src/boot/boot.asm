[BITS 16]

mov     ax, 0x7C0        ; correct value for ds
mov     ds, ax           ; data segment

cli                      ; clear interrupt-enable flag (desable int)
xor     ax, ax
mov     ss, ax           ; stack segment
mov     sp, 0x7C00       ; stack pointer


mov     ah, 0xE          ; display char
mov     bx, 0            ; counter
mov     cx, 12           ; len of str

print_loop:
  mov    al,  [data+bx]  ; move pointer to next ascii symbol
  cmp    bx, cx
  je     loop            ; jump if equal
  int    0x10            ; BIOS call
  inc    bx
  jmp    print_loop

data:
  db     'Hello world!'  ; define bytes for str

loop:
  jmp    loop

times 510-($-$$) db 0
dw 0xAA55                ; define boot sector
