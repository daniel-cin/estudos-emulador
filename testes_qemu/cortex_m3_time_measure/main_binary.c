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


int binarySearch(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

void binary_search_test(int arr[], int n) {
    char buffer[10];
    char cycles_buffer[16];
    int target = 10;
    print_uart0("Teste busca binária\n");
    SysTick->CTRL = 0; // Desabilitar o contador
    SysTick->LOAD = 0xFFFFFF; // Valor máximo de contagem
    SysTick->CTRL = 0x00000005; // Habilitar o contador com o clock do processador

    SysTick->VAL = 0; // Reinicia o valor do contador para zero
    

    int result = binarySearch(arr, 0, n - 1, target);

    
    uint32_t cycles = SysTick->VAL; // Pega o valor atual do contador


    int_to_string(result, buffer);

    if (result == -1)
        print_uart0("Elemento não está presente no array");
    else{
        print_uart0("Elemento está presente no index ");
        print_uart0(buffer);
    }
    print_uart0("\n");

    
    int_to_string(cycles, cycles_buffer);
    print_uart0("Ciclos de clock decorridos: ");
    print_uart0(cycles_buffer);
    print_uart0("\n");
}

int main () {
    int arr[] = {2, 5, 8, 10, 40};
    int n = 5;
    binary_search_test(arr, n);
    return(0);
}
