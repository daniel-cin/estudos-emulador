#include "stm32f10x.h" // Biblioteca específica para a família de microcontroladores STM32F1
// #define UART0BASE 0x4000C000
#include <stdio.h>


// ---- GLOBAL VARIABLES ----
volatile unsigned int *const UART0BASE = (unsigned int *)0x4000C000;
// volatile uint32_t cycles = SysTick->VAL;

int binarySearch(int arr[], int left, int right, int target)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return mid;
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

void print_uart0(const char *s)
{
    while (*s != '\0')
    {
        *UART0BASE = (unsigned int)(*s);
        s++;
    }
}

void int_to_string(int number, char *buffer)
{
    int i = 0;
    int is_negative = 0;

    if (number < 0)
    {
        is_negative = 1;
        number = -number;
    }

    // Trata o caso especial de 0
    if (number == 0)
        buffer[i++] = '0';
    else
    {

        while (number != 0)
        {
            int digit = number % 10;
            buffer[i++] = digit + '0';
            number /= 10;
        }
        for (int j = 0; j < i / 2; j++)
        {
            char temp = buffer[j];
            buffer[j] = buffer[i - j - 1];
            buffer[i - j - 1] = temp;
        }
    }
    if (is_negative)
        buffer[i++] = '-';

    buffer[i] = '\0';
}



void uint32_to_string(uint32_t number, char *buffer)
{
    int i = 0;
    int is_negative = 0;

    if (number < 0)
    {
        is_negative = 1;
        number = -number;
    }

    // Trata o caso especial de 0
    if (number == 0)
        buffer[i++] = '0';
    else
    {

        while (number != 0)
        {
            int digit = number % 10;
            buffer[i++] = digit + '0';
            number /= 10;
        }
        for (int j = 0; j < i / 2; j++)
        {
            char temp = buffer[j];
            buffer[j] = buffer[i - j - 1];
            buffer[i - j - 1] = temp;
        }
    }
    if (is_negative)
        buffer[i++] = '-';

    buffer[i] = '\0';
}
/**
 * Configurar o contador de ciclos de clock
 *
 *  * @note inicializar o contador somente ume vez na rotina
 */
void initialize_systick_counter()
{
    SysTick->CTRL = 0;          // Desabilitar o contador
    SysTick->LOAD = 0xFFFFFF;   // Valor máximo de contagem
    SysTick->VAL = 0;           // Reiniciar o valor atual para zero
    SysTick->CTRL = 0x00000005; // Habilitar o contador com o clock do processador
}

/**
 * Receber o valor atual do registrados de contagem de ciclos
 *
 */
uint32_t get_cycle_systick_counter()
{
    return SysTick->VAL;
}

void print_uint32_t(uint32_t num){
    print_uart0(' - ');
    static char cycles_buffer[16];
    int_to_string(num, cycles_buffer);
    print_uart0(cycles_buffer);
}

int main()
{
    char cycles_buffer[16];

    // INICIALIZAR CLOCK
    initialize_systick_counter();
    volatile uint32_t cycles = 0;

    // ROTINA BENCHMARK
    uint32_t Start = SysTick->VAL;
    print_uart0("START= ");
    int_to_string(Start, cycles_buffer);
    print_uart0(cycles_buffer);
    print_uart0("\n");

    volatile int result = 0;
    volatile uint32_t a = 0;
    volatile uint32_t b = 0;
    volatile uint32_t c = 0;
    volatile uint32_t res = 0;
    a = 15;
    b = 2000;
    c = 100000000;
    res = a+b+c;

    // for (size_t i = 0; i < 1; i++)
    // {
    //     for (size_t j = 0; j < 20; j++)
    //     {
    //         result++;
    //     }
    // }
    uint32_t Stop = SysTick->VAL;
    print_uart0("Stop= ");
    int_to_string(Stop, cycles_buffer);
    print_uart0(cycles_buffer);
    print_uart0("\n");
    
    uint32_t Delta = 0x00FFFFFF & (Start - Stop);
    print_uart0("Delta= ");
    int_to_string(Delta, cycles_buffer);
    print_uart0(cycles_buffer);
    print_uart0("\n");

    // PRINTA NA TELA - CYCLES
    // int_to_string(Delta, cycles_buffer);
    // print_uart0(cycles_buffer);
    
    // PRINTA NA TELA - RES
    int_to_string(res, cycles_buffer);
    print_uart0("\nRES: ");
    print_uart0(cycles_buffer);


    // cycles = SysTick->VAL;
    // int cycles_int = (int) cycles;

    // int_to_string(cycles_int, cycles_buffer);
    // print_uart0(cycles_buffer);



    /*--- Captura o contador de ciclos de clock ---*/
    /*--------------------------------------------*/

    // int_to_string(cycles, cycles_buffer);

    return (0);
}
