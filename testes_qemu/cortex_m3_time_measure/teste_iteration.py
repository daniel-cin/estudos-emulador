import re
import os
import time
from subprocess import Popen, DEVNULL
import matplotlib.pyplot as plt
import csv
import numpy as np
import sys

log_file= "refined_out_iteration.log"
output_dir = "statistics"
csv_file = "clock_cycle_iteration.csv"
graph_file = "graph_iteration.png"
NUM_ITERATIONS = int(sys.argv[1])

# Remover o arquivo de saída, se existir
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
            "-kernel", "main_iteration.bin"
        ]
        with open(log_path, "a") as output_file:
            process = Popen(command, stdout=output_file, stderr=DEVNULL)
            time.sleep(1)
            process.kill()

import re

def extract_iteration_values(file_path):
    # Padrão de expressão regular para extrair os valores das iterações
    pattern = r'Iteracoes: (\d+)\nCiclos de clock decorridos: (\d+)'

    # Dicionário para armazenar os valores de cada tipo de iteração
    iteration_values = {
        'iteracao_1': [],
        'iteracao_10': [],
        'iteracao_100': [],
        'iteracao_1000': [],
        'iteracao_10000': [],
        'iteracao_100000': [],
        'iteracao_1000000': [] 
    }


    with open(file_path, 'r') as file:
        input_data = file.read()
    
    # Procurar por correspondências no texto de entrada
    matches = re.findall(pattern, input_data)
    # Extrair os valores das iterações e armazená-los no dicionário
    for match in matches:
        iterations = int(match[0])
        clock_cycles = int(match[1])

        if iterations == 1:
            iteration_values['iteracao_1'].append(clock_cycles)
        elif iterations == 10:
            iteration_values['iteracao_10'].append(clock_cycles)
        elif iterations == 100:
            iteration_values['iteracao_100'].append(clock_cycles)
        elif iterations == 1000:
            iteration_values['iteracao_1000'].append(clock_cycles)
        elif iterations == 10000:
            iteration_values['iteracao_10000'].append(clock_cycles)
        elif iterations == 100000:
            iteration_values['iteracao_100000'].append(clock_cycles)
        elif iterations == 1000000:
            iteration_values['iteracao_1000000'].append(clock_cycles)

    return iteration_values

def plot_iteration_values(iteration_values):
    means = []
    stds = []
    for _, values in iteration_values.items():
        means.append(np.mean(values))
        stds.append(np.std(values))

    # Configurar os pontos e as barras de erro
    x = np.arange(len(iteration_values))
    plt.errorbar(x, means, yerr=stds, fmt='o', capsize=5)

    plt.xticks(x, [int(key.split('_')[1]) for key in iteration_values.keys()])
    plt.xlabel('Iteracao')

    plt.ylabel('Ciclos de Clock (Normalizado)')
    plt.title('Valores Medios de Iteracao')
    plt.savefig(graph_path)

def stats(values):
    for key, val in values.items():
        print(key)
        print("Ciclos de clock: {}".format(val))
        mean = np.mean(val)
        median = np.median(val)
        std_dev = np.std(val)
        maxx = max(val)
        minn = min(val)
        print("Estatisticas dos Ciclos de Clock:")
        print("Media:", mean)
        print("Mediana:", median)
        print("Desvio Padrao:", std_dev)
        print("Valor Máximo:", maxx)
        print("Valor Mínimo:", minn)

def gen_csv(iteration_values):
    with open(os.path.join(output_dir, csv_file), 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        iterations = list(iteration_values.keys())
        writer.writerow(iterations)

        max_len = max(len(values) for values in iteration_values.values())
        for i in range(max_len):
            row = [iteration_values[iteration][i] if i < len(iteration_values[iteration]) else '' for iteration in iterations]
            writer.writerow(row)

runQemu()
values = extract_iteration_values(log_path)
stats(values)
gen_csv(values)
plot_iteration_values(values)