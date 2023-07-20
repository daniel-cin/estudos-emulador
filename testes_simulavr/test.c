#include <avr/io.h>

/* This port corresponds to the "-W 0x20,-" command line option. */
#define special_output_port (*((volatile char *)0x20))

void TIMER_start(void);
uint16_t TIMER_stop(void);

void UART_putc(unsigned char data);
void UART_puts(unsigned char* s);
void UART_putU16(uint16_t val);

volatile uint8_t test = 0;

void main(void)
{
    uint16_t val = 0;

    TIMER_start();

    test++;

    val = TIMER_stop();

    UART_puts("Cycles: ");
    UART_putU16(val);
    UART_putc('\r');
    UART_putc('\n');
}

void TIMER_start(void)
{
    /* Reset Timer/Counter1 */
    TCNT1 = 0;

    /* Normal mode, clk/1 (No prescaling) */
    TCCR1B = 0x01;
}

uint16_t TIMER_stop(void)
{
    /* Normal mode, No clock source (Timer/Counter stopped) */
    TCCR1B = 0x00;

    /* Read Timer/Counter1 */
    return TCNT1;
}

void UART_putc(unsigned char data)
{
    special_output_port = data; /* Put data into buffer, sends the data */
}

void UART_puts(unsigned char* s)
{
    // transmit character until NULL is reached
    while(*s > 0) UART_putc(*s++);
}

void UART_putU16(uint16_t val)
{
    uint8_t dig1 = '0', dig2 = '0', dig3 = '0', dig4 = '0';

    // count value in 10000s place
    while(val >= 10000)
    {
        val -= 10000;
        dig1++;
    }

    // count value in 1000s place
    while(val >= 1000)
    {
        val -= 1000;
        dig2++;
    }

    // count value in 100s place
    while(val >= 100)
    {
        val -= 100;
        dig3++;
    }

    // count value in 10s place
    while(val >= 10)
    {
        val -= 10;
        dig4++;
    }

    // was previous value printed?
    uint8_t prevPrinted = 0;

    // print first digit (or ignore leading zeros)
    if(dig1 != '0') {UART_putc(dig1); prevPrinted = 1;}

    // print second digit (or ignore leading zeros)
    if(prevPrinted || (dig2 != '0')) {UART_putc(dig2); prevPrinted = 1;}

    // print third digit (or ignore leading zeros)
    if(prevPrinted || (dig3 != '0')) {UART_putc(dig3); prevPrinted = 1;}

    // print third digit (or ignore leading zeros)
    if(prevPrinted || (dig4 != '0')) {UART_putc(dig4); prevPrinted = 1;}

    // print final digit
    UART_putc(val + '0');
}
