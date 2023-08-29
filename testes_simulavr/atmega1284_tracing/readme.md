Testes feitos no Ubuntu 22.04.2 LTS

Dependências:
- binutils-avr
- gcc-avr
- avr-libc
- simulavr
- gtkwave

Para compilar:

    avr-gcc -std=c89 -pedantic -Wall -mmcu=atmega1284 -o test.elf test.c

Para executar:

	simulavr -d atmega1284 -F 1000000 -c vcd:infile.txt:outfile.vcd -t steps.txt -f test.elf -T exit

Para analisar:

    gtkwave outfile.vcd
