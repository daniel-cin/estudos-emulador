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

int main()
{
    char cycles_buffer[16];
    int target = 10;

    // int result = binarySearch(arr, 0, n - 1, target);
    initialize_systick_counter();
    volatile uint32_t cycles = 0;
    // print_uart0(cycles);

    uint32_t Start = SysTick->VAL;
    volatile int result = 0;
    for (size_t i = 0; i < 10; i++)
    {
        for (size_t j = 0; j < 10000; j++)
        {
            result++;
        }
        // cycles = get_cycle_systick_counter();
        // int_to_string(cycles, cycles_buffer);
        // print_uart0(cycles_buffer);
    }
    uint32_t Stop = SysTick->VAL;
    uint32_t Delta = 0x00FFFFFF & (Start - Stop);
    int_to_string(cycles, cycles_buffer);
    print_uart0(cycles_buffer);



    /*--- Captura o contador de ciclos de clock ---*/
    cycles = SysTick->VAL;
    /*--------------------------------------------*/

    int_to_string(cycles, cycles_buffer);
    print_uart0(cycles_buffer);

    return (0);
}
