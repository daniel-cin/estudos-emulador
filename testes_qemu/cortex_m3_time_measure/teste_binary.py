import os
import time
from subprocess import Popen, DEVNULL
import matplotlib.pyplot as plt
import csv
import numpy as np
import sys

log_file= "refined_out_binary.log"
output_dir = "statistics"
csv_file = "clock_cycle_binary.csv"
graph_file = "graph_binary.png"
NUM_ITERATIONS = int(sys.argv[1])

log_path = os.path.join(output_dir, log_file)
graph_path = os.path.join(output_dir, graph_file)
if os.path.exists(log_path):
    os.remove(log_path)
if os.path.exists(graph_path):
    os.remove(graph_path)

def runQemu():
    for i in range(1, NUM_ITERATIONS + 1):
        # Executar o comando qemu-system-arm
        print("Iteration: {}".format(i))
        command = [
            "qemu-system-arm",
            "-M", "lm3s6965evb",
            "-cpu", "cortex-m3",
            "-m", "128M",
            "-nographic",
            "-semihosting",
            "--semihosting-config", "enable=on,target=native",
            "-icount", "shift=1,align=off,sleep=off",
            "-kernel", "main_binary.bin"
        ]
        with open(log_path, "a") as output_file:
            process = Popen(command, stdout=output_file, stderr=DEVNULL)
            time.sleep(0.2)
            process.kill()


def processData():
    clock_cycles = []

    with open(log_path, 'r') as file:
        lines = file.readlines()

    # Extrair os valores dos ciclos de clock
    for line in lines:
        if "Ciclos de clock decorridos:" in line:
            valor_ciclos = int(line.split(":")[1].strip())
            clock_cycles.append(valor_ciclos)
    return clock_cycles

def stats(clock_cycles):
    print("Ciclos de clock: {}".format(clock_cycles))
    mean = np.mean(clock_cycles)
    median = np.median(clock_cycles)
    std_dev = np.std(clock_cycles)
    maxx = max(clock_cycles)
    minn = min(clock_cycles)
    print("Estatísticas dos Ciclos de Clock:")
    print("Média:", mean)
    print("Mediana:", median)
    print("Desvio Padrão:", std_dev)
    print("Valor Máximo:", maxx)
    print("Valor Mínimo:", minn)

def plot(clks):
    plt.plot(clks)
    plt.xlabel('Iteração')
    plt.ylabel('Ciclos de Clock')
    plt.title('Valores dos Ciclos de Clock')
    plt.savefig(graph_path)

def gen_csv(values):
    with open(os.path.join(output_dir, csv_file), mode='w') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['cycles'])
        for value in values:
            writer.writerow([value])

runQemu()
clks = processData()
stats(clks)
gen_csv(clks)
plot(clks)
