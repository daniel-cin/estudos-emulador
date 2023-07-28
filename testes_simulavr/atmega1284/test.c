#include <avr/io.h>
#include <stdio.h>


/* This port corresponds to the "-W 0x20,-" command line option. */
#define special_output_port (*((volatile char *)0x20))

int virtual_putchar(char c, FILE *unused)
{
    special_output_port = c;
    return 0;
}

FILE virtual_port = FDEV_SETUP_STREAM(virtual_putchar, NULL, _FDEV_SETUP_WRITE);


void TIMER_start(void);
uint16_t TIMER_stop(void);


volatile uint8_t test = 0;

int main(void)
{
    uint16_t val = 0;

    stdout = &virtual_port;

    TIMER_start();

    test++;

    val = TIMER_stop();
    
    printf("Cycles: %u\r\n", val);

    return 0;
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
