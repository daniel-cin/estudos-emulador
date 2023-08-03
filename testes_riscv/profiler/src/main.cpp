#include <Arduino.h>
#include "Benchmark.h"
#include <vector>    // Para utilizar o vetor de tempos
#include <array>     // Para utilizar o array de funções

#define N 10

/*Variaveis para o teste*/
/*que feio, variaveis globais*/
int alea[N] = {74, 39, 102, 57, 86, 91, 32, 65, 78, 23};
int worst[N] = {102, 91, 86, 78, 74, 65, 57, 39, 32, 23};
int target = 10;

/*Prototipos das funcoes de teste*/
void binary_search_test(int arr[], int target);
void bubble_sort_test(int arr[]);
void sum_test();

/*Prototipos das funcoes auxiliares*/
void copyArray(int ref[], int cpy[]);

void setup() {
    Serial.begin(115200);
    Serial.println("Starting ...");
}

void loop() {

    // Medindo o tempo das funções com seus respectivos parâmetros usando a classe Benchmark
    unsigned long mTime = Benchmark::cronometer(bubble_sort_test, alea);

    // Imprimindo os tempos medidos no Monitor Serial
    Serial.printf("Execution Time: %u cycles\n", mTime);
    delay(1000);
}

void copyArray(int ref[], int arrCpy[]) {
    for (int i = 0; i < N; i++) {
        arrCpy[i] = ref[i];
    }
}

/*---Funcoes de teste---*/

void binary_search_test(int arr[], int target) {
    int left = 0;
    int right = N - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) return;
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
}

void printArray(int arr[]) {
    for (int i = 0; i < N; i++) {
        Serial.printf("%d ", arr[i]);
    }
    Serial.println();
}

void bubble_sort_test(int arr[]) {
    int k, j, aux;
    int arrCpy[N];
    copyArray(arr, arrCpy);
    for (k = 1; k < N; k++) {
        for (j = 0; j < N - k; j++) {
            if (arrCpy[j] > arrCpy[j + 1]) {
                aux = arrCpy[j];
                arrCpy[j] = arrCpy[j + 1];
                arrCpy[j + 1] = aux;
            }
        }
    }
}

void sum_test() {
    int sum =  2 + 2;
}

