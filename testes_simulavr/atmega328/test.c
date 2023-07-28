#include <avr/io.h>
#include <stdio.h>
#include "avr-tick-counter.h"


/* This port corresponds to the "-W 0x20,-" command line option. */
#define special_output_port (*((volatile char *)0x20))

int virtual_putchar(char c, FILE *unused)
{
    special_output_port = c;
    return 0;
}

FILE virtual_port = FDEV_SETUP_STREAM(virtual_putchar, NULL, _FDEV_SETUP_WRITE);

volatile uint8_t test = 0;

int main(void)
{
    stdout = &virtual_port;

    StartTickCounter();

    test++;

    StopTickCounter();

    printf("Cycles: %u\r\n", GetTicks());
}
