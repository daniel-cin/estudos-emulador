#include <stdint.h>
#include "stm32f1xx.h"

//#define BUBBLE //SELECIONE AQUI O ALGORITMO
#define BUBBLE_W //SELECIONE AQUI O ALGORITMO
//#define TREE //SELECIONE AQUI O ALGORITMO

#define LED_DELAY 125000UL  // 0.5s
#define LED_ON() (GPIOC->BSRR = GPIO_BSRR_BR13)
#define LED_OFF() (GPIOC->BSRR = GPIO_BSRR_BS13)

/*Variaveis para o teste*/
/*que feio, variaveis globais*/
int arr[] = {74, 39, 102, 57, 86, 91, 32, 65, 78, 23};
int arrW[] = {102, 91, 86, 78, 74, 65, 57, 39, 32, 23};
int n = 10;
int target = 10;

void initLed();
void blinkLed();
void startSysTick();
uint32_t endSysTick();
uint32_t cronometer(void (*targetFunc)());

void binary_search_test();

void bubble_sort_test();

void bubble_sort_worst_test();


int main(void) {
    initLed();
    while (1) {
        blinkLed();
        #if defined(BUBBLE)
            uint32_t cycles = cronometer(bubble_sort_test);
        #elif defined(TREE)
            uint32_t cycles = cronometer(binary_search_test);
        #elif defined(BUBBLE_W)
            uint32_t cycles = cronometer(bubble_sort_worst_test);
        #endif
    }
    return 0;
}

void initLed() {
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;                     // enable clock
    GPIOC->CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13);      // reset PC13
    GPIOC->CRH |= (GPIO_CRH_MODE13_1 | GPIO_CRH_MODE13_0);  // config PC13
}

void blinkLed() {
    static uint32_t led_delay_count = 0;
    led_delay_count = ((led_delay_count + 1) % LED_DELAY);
    if (led_delay_count == 0)
        LED_ON();
    else if (led_delay_count == (LED_DELAY / 2))
        LED_OFF();
}

void startSysTick() {
    SysTick->CTRL = 0;           // Desabilitar o contador
    SysTick->LOAD = 0xFFFFFF;    // Valor máximo de contagem
    SysTick->CTRL = 0x00000005;  // Habilitar o contador com o clock do processador
    SysTick->VAL = 0;
}

uint32_t endSysTick() {
    return 0xFFFFFF - SysTick->VAL;
}

uint32_t cronometer(void (*targetFunc)()) {
    startSysTick();
    targetFunc();
    return endSysTick();
}

/*---Funcoes de teste---*/

void binary_search_test() {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) return;
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
}

void bubble_sort_test() {
    int k, j, aux;
    for (k = 1; k < n; k++) {
        for (j = 0; j < n - k; j++) {
            if (arr[j] > arr[j + 1]) {
                aux = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = aux;
            }
        }
    }
}

void bubble_sort_worst_test() {
    int k, j, aux;
    for (k = 1; k < n; k++) {
        for (j = 0; j < n - k; j++) {
            if (arrW[j] > arrW[j + 1]) {
                aux = arrW[j];
                arrW[j] = arrW[j + 1];
                arrW[j + 1] = aux;
            }
        }
    }
}


