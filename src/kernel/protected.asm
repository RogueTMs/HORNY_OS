[BITS 16]

gdt_start:
  dq 0x0                           ; null descriptor
gdt_code:
  dq 0x30A60000000000
gdt_data:
  dq 0xC2920000000000

gdt_end:                           ; ??

lgdt [gdt_descriptor]              ;

gdt_descriptor:
  dw gdt_end - gdt_start - 1       ; labels arithmetic
  dd gdt_start + 0x20000           ; GDT linear address in VBR copy

CODE_SEG equ gdt_code - gdt_start  ; def constants
DATA_SEG equ gdt_data - gdt_start


jmp CODE_SEG:protected_mode_tramplin + 0x7c00

[BITS 32]

protected_mode_tramplin:
  mov ds,  DATA_SEG
  mov ss,  DATA_SEG
  mov es,  DATA_SEG
  mov fs,  DATA_SEG
  mov gs,  DATA_SEG
  mov esp, 0x20000

  jmp CODE_SEG:0x20200
