Testes feitos no Ubuntu 22.04.2 LTS

Dependências:
- binutils-avr
- gcc-avr
- avr-libc
- simulavr

Para compilar:

    avr-gcc -std=c89 -pedantic -Wall -mmcu=atmega1284 -o test.elf test.c

Para executar:

	simulavr -d atmega1284 -f test.elf -W 0x20,- -T exit
