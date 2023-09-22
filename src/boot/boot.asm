[BITS 16] ; Указываем, что пишем 16-битный код реального режима 8086


cli ; Отключение прерывания от переферийных устройств
xor ax, ax  ; Делаем 0 в ax
mov ss, ax  
mov sp, 0x7C00


mov ax, 0x7C0
mov ds, ax

mov ah, 0xE ; AH - идентифицирует конкретную функцию, 0xE - display char

mov al, 72  ; AL - ASCII-код символа
int 0x10    ; INT - команда генерации прерывания (системный вызов),
            ; 0x10 - вектор видеосервисов (множество функций печати)


mov al, 101
int 0x10

mov al, 108
int 0x10

mov al, 108
int 0x10

mov al, 111
int 0x10

mov al, 32
int 0x10

mov al,  119
int 0x10

mov al, 111
int 0x10

mov  al, 114
int 0x10

mov al, 108
int 0x10

mov al, 100
int 0x10 

mov al, 33
int 0x10

loop:       ; Бесконечный цикл
  jmp loop

times 510-($-$$) db 0 ; заполняем байтами 0x00 до 510 байт
dw 0xAA55 ; определяем загрузочный сектор
