ARMGNU = arm-none-eabi
EMU = qemu-system-arm

AOPS = --warn --fatal-warnings -mcpu=cortex-m3
COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding  -mcpu=cortex-m3
LIBS= ./Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x -I./Libraries/CMSIS/CM3/CoreSupport

all : main.bin

clean:
	rm -f *.bin
	rm -f *.o
	rm -f *.elf
	rm -f *.list
	rm -f *.csv

vectors.o : vectors.s
	$(ARMGNU)-as $(AOPS) vectors.s -o vectors.o

main.o : main.c
	$(ARMGNU)-gcc $(COPS) -I $(LIBS) -mthumb -c main.c -o main.o

main.bin : memmap vectors.o main.o
	$(ARMGNU)-ld -o main.elf -T memmap vectors.o main.o
	$(ARMGNU)-objdump -D main.elf > main.list
	$(ARMGNU)-objcopy main.elf main.bin -O binary

qemu: main.bin
	$(EMU) -M lm3s6965evb -m 128M -nographic -semihosting --semihosting-config enable=on,target=native -serial mon:stdio -kernel main.bin

test_qemu: test.sh
	./test.sh