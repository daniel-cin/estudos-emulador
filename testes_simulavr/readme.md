Testes feitos no Ubuntu 22.04.2 LTS

Dependências:
- binutils-avr
- gcc-avr
- avr-libc
- simulavr

Para compilar:

    avr-gcc -mmcu=atmega328 -o test.elf test.c

Para executar:

	simulavr -d atmega328 -f test.elf -W 0x20,- -T exit