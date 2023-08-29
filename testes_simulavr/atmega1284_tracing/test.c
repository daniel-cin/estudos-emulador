#include <avr/io.h>

#define F_CPU 1000000 /* 1MHz */

volatile int test = 0;

int main(void)
{
    DDRA = 0xFF;
    PORTA = 0xFF;
    test++;
    test++;
    test++;
    PORTA = 0x00;
    return 0;
}
