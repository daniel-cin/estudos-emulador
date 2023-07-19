#include "stm32f10x.h" // Biblioteca específica para a família de microcontroladores STM32F1
#include <stdio.h>

volatile unsigned int * const UART0BASE = (unsigned int *)0x4000C000;

void print_uart0(const char *s) {
    while(*s != '\0') {
        *UART0BASE = (unsigned int)(*s); 
        s++; 
    }
}

void int_to_string(int number, char* buffer) {
    int i = 0;
    int is_negative = 0;

    if (number < 0) {
        is_negative = 1;
        number = -number;
    }

    // Trata o caso especial de 0
    if (number == 0) buffer[i++] = '0';
    else {

        while (number != 0) {
            int digit = number % 10;
            buffer[i++] = digit + '0';
            number /= 10;
        }
        for (int j = 0; j < i / 2; j++) {
            char temp = buffer[j];
            buffer[j] = buffer[i - j - 1];
            buffer[i - j - 1] = temp;
        }
    }
    if (is_negative) buffer[i++] = '-';
    
    buffer[i] = '\0';
}

void iteration(int arr[], int size, int iterations) {
    int i = 0, j = 0;
    for(i = 0; i < iterations; i++) 
        for (j = 0; j < size; j++)
            arr[j]++;

}

void iteration_test(int arr[], int n , int lim) {
    char buffer[10];
    print_uart0("Teste de iteração\n");
    SysTick->CTRL = 0; // Desabilitar o contador
    SysTick->LOAD = 0xFFFFFF; // Valor máximo de contagem
    SysTick->CTRL = 0x00000005; // Habilitar o contador com o clock do processador
    for (int i = 1; i < lim; i = i*10) {
        print_uart0("Iteracoes: ");
        int_to_string(i, buffer);
        print_uart0(buffer);
        print_uart0("\n");
        char cycles_buffer[16];
        
        SysTick->VAL = 0; // Reinicia o valor do contador para zero
        
        iteration(arr, n, 1000000);

        uint32_t cycles = SysTick->VAL; // Captura o contador de ciclos de clock

        int_to_string(cycles, cycles_buffer);
        print_uart0("Ciclos de clock decorridos: ");
        print_uart0(cycles_buffer);
        print_uart0("\n");
    }
}

int main () {
    int arr[] = {2, 5, 8, 10, 40, 50, 60, 70, 80, 90, 100};
    int n = 11;
    iteration_test(arr, n, 1000000000);
    return(0);
}
