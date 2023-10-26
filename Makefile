all: launch

# If the first argument is "bootimg"...
ifeq (bootimg, $(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "bootimg"
  BOOTIMG_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
  $(eval $(BOOTIMG_ARGS):;@:)
endif


launch: 
	bochs -f os.bxrc -q


debug: 
	bochsdbg -f os-dbg.bxrc -q


.PHONY: clean 

bootimg:
	nasm -fbin src/boot/$(BOOTIMG_ARGS).asm -o src/boot/boot.bin
	dd if=/dev/zero of=src/boot/$(BOOTIMG_ARGS).img bs=1024 count=1440
	dd if=src/boot/boot.bin of=src/boot/$(BOOTIMG_ARGS).img conv=notrunc


concat:
	dd if=src/boot/bin/binary.bin of=src/boot/boot.img conv=notrunc seek=1


genbin:
	python src/boot/bin/Gener_bin.py

readbin:
	python src/boot/bin/Read_bin.py

kernel:
	gcc -m32 -ffunction-sections -c -o src/boot/kernel.o src/boot/kernel.c
	ld -m i386pe -o src/boot/kernel.tmp -Ttext 0x20200 src/boot/kernel.o
	objcopy -I pe-i386 -O binary src/boot/kernel.tmp src/boot/kernel.bin

	dd if=src/boot/kernel.bin of=src/boot/boot.img conv=notrunc seek=1

clean: 
