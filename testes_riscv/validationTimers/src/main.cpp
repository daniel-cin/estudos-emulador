#include <Arduino.h>

#include "esp_bt.h"
#include "esp_wifi.h"
#include "esp32-hal-cpu.h"

void disableWifi();
void disableBluetooth();
uint32_t validation1();
uint32_t validation2();
uint32_t validation3();
uint32_t validation4();


void setup() {
    Serial.begin(115200);
    Serial.println("Starting ...");
    setCpuFrequencyMhz(80);
    Serial.printf("ESP.getCpuFreqMHz(): %u\n", ESP.getCpuFreqMHz());
    
    disableBluetooth();
    disableWifi();
}

void loop() {
    uint32_t validation_cycles1 = validation1();
    uint32_t validation_cycles2 = validation2();
    uint32_t validation_cycles3 = validation3();
    uint32_t validation_cycles4 = validation4();
    Serial.printf("validation1: %u\n", validation_cycles1);
    Serial.printf("validation2: %u\n", validation_cycles2);
    Serial.printf("validation3: %u\n", validation_cycles3);
    Serial.printf("validation4: %u\n", validation_cycles4);
    delay(1000);
}

void disableWifi() {
    esp_wifi_stop();
    esp_wifi_deinit();
}

void disableBluetooth() {
    esp_bt_controller_disable();
    esp_bt_controller_deinit();
}

void nops() {
    __asm__ __volatile__ (
    " nop\n"
  );
}

uint32_t validation1() {
    uint32_t startTime, endTime, executionCycles;
    noInterrupts();
    startTime = ESP.getCycleCount();

    __asm__ __volatile__ (" nop\n");
    
    endTime = ESP.getCycleCount();
    interrupts();
    executionCycles = (endTime - startTime);
    return executionCycles;
}

uint32_t validation2() {
    uint32_t startTime, endTime, executionCycles;
    noInterrupts();
    startTime = esp_cpu_get_ccount();

    __asm__ __volatile__ (" nop\n");

    endTime = esp_cpu_get_ccount();
    interrupts();
    executionCycles = (endTime - startTime);
    return executionCycles;
}

uint32_t validation3() {
    uint32_t startTime, endTime, executionCycles;
    noInterrupts();
    startTime = cpu_hal_get_cycle_count();

    __asm__ __volatile__ (" nop\n");

    endTime = cpu_hal_get_cycle_count();
    interrupts();
    executionCycles = (endTime - startTime);
    return executionCycles;
}

uint32_t validation4() {
    uint32_t startTime, endTime, executionCycles;
    noInterrupts();
    startTime = RV_READ_CSR(CSR_PCCR_MACHINE);

    __asm__ __volatile__ (" nop\n");

    endTime = RV_READ_CSR(CSR_PCCR_MACHINE);
    interrupts();
    executionCycles = (endTime - startTime);
    return executionCycles;
}
