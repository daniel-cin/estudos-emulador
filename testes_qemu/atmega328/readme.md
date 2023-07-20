Testes feitos no Ubuntu 22.04.2 LTS

Dependências:
- binutils-avr
- gcc-avr
- avr-libc
- qemu-system-avr

Para compilar:

    avr-gcc -mmcu=atmega328 -o test.elf test.c

Para executar:

	qemu-system-avr -M uno -nographic -bios test.elf