#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <Arduino.h> // Importante para usar a função millis()

struct BenchmarkInfo {
    unsigned long heapUsage; // Uso atual da heap em bytes
    unsigned long cpuClock; // Clock da CPU em Hertz
};

class Benchmark {
public:
    // Definindo a interface genérica para as funções
    template<typename Func, typename... Args>

    static unsigned long cronometer(Func func, Args... args) {
        uint32_t startTime, endTime, executionCycles;
        noInterrupts();
        startTime = RV_READ_CSR(CSR_PCCR_MACHINE);

        func(args...); 

        endTime = RV_READ_CSR(CSR_PCCR_MACHINE);
        interrupts();
        executionCycles = (endTime - startTime);
        return executionCycles;
    }

    static BenchmarkInfo getInfo() {
        BenchmarkInfo info;
        info.heapUsage = ESP.getFreeHeap(); // Uso atual da heap
        info.cpuClock = ESP.getCpuFreqMHz() * 1000000UL; // Clock da CPU em Hertz
        return info;
    }
    
};

#endif
