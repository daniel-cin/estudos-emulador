Testes feitos no Ubuntu 22.04.2 LTS

Dependências:
- binutils-avr
- gcc-avr
- avr-libc
- simulavr

Para compilar:

    avr-gcc -std=c89 -pedantic -mmcu=atmega328 -o test.elf test.c avr-tick-counter.S

Para executar:

	simulavr -d atmega328 -f test.elf -W 0x20,- -T exit