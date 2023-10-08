[BITS 16]

mov     ax, 0x7C0        ; correct value for ds
mov     ds, ax           ; data segment
mov     ax, 0x2000       ; correct value for stack segment
mov     es, ax           ; extra segment

cli                      ; clear interrupt-enable flag (desable int)
xor     ax, ax
mov     ss, ax           ; stack segment
mov     sp, 0x7C00       ; stack pointer

mov     di, 0x2000


disk_load:
	mov     ch, 0x00            ; cylinder number
	mov     dh, 0               ; head number
	mov     cl, 0x1             ; starting sector number
	


MAIN:

	read_loop:

	;  384 * 1024 / 512 = 768 sectors
	;  768 / 36 = 21.33 cyls
	;  start = 0x20000
	;  end   = 0x80000
	  
	mov        si, 0x0003			; errors counter
	
	read_num:
		mov     ah, 0x02            ; BIOS read sector from drive
		mov     al, 0x01            ; amount of sectors
		int    0x13

		jc     errmsglb             ; error check

		add    di, 0x20             ; 512 bytes
		mov    es, di
		cmp    di, 0x8000
		je 	   end_of_reading

		inc    cl                   ; next sector
		cmp    cl, 0x13             ; if 19th sector -> end
		je 	   check_head
		jmp    read_loop
		

	check_head:
		mov    cl, 0x1				; update head
		inc    dh
		cmp    dh, 0x2
		je     change_cyl
		jmp    read_loop


	change_cyl:
		xor    dh, dh
		inc    ch                   ; get next cyl

		jmp   read_loop



end_of_reading:

	prepare: 
		mov ax, 0x2000
		mov es, ax
		xor dx, dx
		xor bx, bx
		
	addition:
		add dl, BYTE[es:bx]
		inc bx
		cmp bx, 0x10
		
		je move_es
		
		jmp addition
		
		move_es:
			mov ax, es
			inc ax 
			mov es, ax
			cmp ax, 0x8000 
			je check_loop
			xor bx, bx
			jmp addition
	
errmsglb:
	dec    si
	cmp    si, 0x0
	jne    read_num
	int	   0x18 




check_loop:
	mov ah, 0xE
	mov al, 'A'
	int 0x10
	end_loop:
		jmp end_loop
		

times 510-($-$$) db 0
dw 0xAA55                           ; define boot sector
