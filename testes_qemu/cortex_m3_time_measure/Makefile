ARMGNU = arm-none-eabi
EMU = qemu-system-arm

AOPS = --warn --fatal-warnings -mcpu=cortex-m3
COPS = -Wall -O0 -nostdlib -nostartfiles -ffreestanding  -mcpu=cortex-m3
LIBS= ./Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x -I./Libraries/CMSIS/CM3/CoreSupport

RUNS = 10 # Number of runs for each test

output_dir := statistics

all : main_binary.bin main_iteration.bin

clean:
	rm -f *.bin
	rm -f *.o
	rm -f *.elf
	rm -f *.list
	rm -f *.csv
	rm -r $(output_dir)

vectors.o : vectors.s
	$(ARMGNU)-as $(AOPS) vectors.s -o vectors.o

main_iteration.o : main_iteration.c
	$(ARMGNU)-gcc $(COPS) -I $(LIBS) -mthumb -c main_iteration.c -o main_iteration.o

main_binary.o : main_binary.c
	$(ARMGNU)-gcc $(COPS) -I $(LIBS) -mthumb -c main_binary.c -o main_binary.o

main_iteration.bin : memmap vectors.o main_iteration.o
	$(ARMGNU)-ld -o main_iteration.elf -T memmap vectors.o main_iteration.o
	$(ARMGNU)-objdump -D main_iteration.elf > main_iteration.list
	$(ARMGNU)-objcopy main_iteration.elf main_iteration.bin -O binary

main_binary.bin : memmap vectors.o main_binary.o
	$(ARMGNU)-ld -o main_binary.elf -T memmap vectors.o main_binary.o
	$(ARMGNU)-objdump -D main_binary.elf > main_binary.list
	$(ARMGNU)-objcopy main_binary.elf main_binary.bin -O binary

qemu_binary: main_binary.bin
	$(EMU) -M lm3s6965evb -m 128M -nographic -semihosting --semihosting-config enable=on,target=native -serial mon:stdio -kernel main_binary.bin

qemu_iteration: main_iteration.bin
	$(EMU) -M lm3s6965evb -m 128M -nographic -semihosting --semihosting-config enable=on,target=native -serial mon:stdio -kernel main_iteration.bin

statistics_iteration: teste_iteration.py
	mkdir -p $(output_dir)
	python3 teste_iteration.py $(RUNS)

statistics_binary: teste_binary.py 
	mkdir -p $(output_dir)
	python3 teste_binary.py $(RUNS)

statistics: statistics_iteration statistics_binary