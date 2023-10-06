[BITS 16]
; TODO: determine where we should check the "64kb"-problem

; mov [BOOT_DRIVE], dl

mov     ax, 0x7C0        ; correct value for ds
mov     ds, ax           ; data segment
mov     ax, 0x2000       ; correct value for stack segment
mov     es, ax           ; extra segment

cli                      ; clear interrupt-enable flag (desable int)
xor     ax, ax
mov     ss, ax           ; stack segment
mov     sp, 0x7C00       ; stack pointer


disk_load:
	xor 	cx, cx
	mov     ah, 0x02            ; BIOS read sector from drive
	mov     al, 0x01            ; amount of sectors
	mov     ch, 0x00            ; cylinder number
	mov     dh, 0               ; head number
	mov     cl, 0x1            ; starting sector number (from 2 to 18)
	xor     bx, bx              ; clear bx (bx - cyl counter in bytes)
	


MAIN:

	read_loop:

	;  384 * 1024 / 512 = 768 sectors
	;  768 / 36 = 21.33 cyls
	;  start = 0x20000
	;  end   = 0x80000
	;  clear all reg before work
	;  
	
	
	read_num:
		int    0x13
		; jc     errmsglb            ; error check

		add    cl, 1                ; next sector
		cmp    cl, 0x13             ; if 19th sector -> end
		je     check_head           ; then check if we need to change head num


	check_head:
		mov    cl, 0x1
		cmp    dh, 0
		je     inc_head            ; change dh to 1
		jne    dec_head            ; change dh to 0 and go to next cyl

	inc_head:
		inc    dh                  ; head -> 1
		;jmp    check_pos_es
		jmp     read_loop
	dec_head:
		mov    di, es
		add    di, 0x20              ; 512 bytes
		cmp    di, 0x8000
		ja    end_of_reading
		jne   read_loop

		mov    es, di
		xor    di, di

		inc    ch                  ; get next cyl
		dec    dh                  ; head -> 0
		;jmp    check_pos_es
		jmp      read_loop

	end_of_reading:

		; TODO: take check sum
		; calc_sum:
		;	sum_loop:
		;		........
		;		cmp ex(or bx?), 0x8000
		;		....
		;		jmp end_loop



calc_sum:
	
	prepare: 
		mov ax, 0x2000
		mov es, ax
		xor dx, dx
		xor bx, bx
		
	addition:
		add dx, [es:bx]
		inc bx
		cmp bx, 0x10
		
		je move_es
		
		jmp addition
		
		move_es:
			mov ax, es
			inc ax 
			cmp ax, 0x8001
			je check_loop
			mov es, ax
			xor bx, bx
			jmp addition
	
			
		

; TODO: add "give a 3rd chance"
errmsglb: db "error", 0


; global vars
; BOOT_DRIVE: db 0

check_loop:
	mov ah, 0xE
	mov al, 'A'
	int 0x10
	end_loop:
		jmp end_loop
	; jmp end_loop

times 510-($-$$) db 0
dw 0xAA55                           ; define boot sector
