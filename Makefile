all: launch

launch: 
	bochs -f os.bxrc -q


debug: 
	bochs -f os-dbg.bxrc -q


.PHONY: clean 

bootimg:
	nasm -fbin src/boot/boot.asm -o src/boot/boot.bin
	dd if=/dev/zero of=src/boot/boot.img bs=1024 count=1440
	dd if=src/boot/boot.bin of=src/boot/boot.img conv=notrunc

clean: 
