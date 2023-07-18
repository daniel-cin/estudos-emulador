#!/bin/bash

input_file="out.log"
output_file="refined_out.csv"

extract_value() {
  local line="$1"
  local value=$(echo "$line" | grep -oP '\d+')
  echo "$value"
}

# Função para calcular estatísticas do arquivo
calculate_statistics() {
  # Extrair os valores numéricos e armazenar em um array
  values=()
  while IFS= read -r line; do
    if [[ $line == *"Ciclos de clock decorridos:"* ]]; then
      value=$(extract_value "$line")
      if [[ $value -eq 0 ]]; then
        # Executar o QEMU novamente
        qemu-system-arm -M lm3s6965evb -m 128M -nographic -semihosting --semihosting-config enable=on,target=native -kernel main.bin >> out.log &
        sleep 0.2
        killall qemu-system-arm
        sleep 0.2
        # Extrair o valor novamente
        value=$(extract_value "$line")
      fi
      values+=("$value")
    fi
  done < "$input_file"

  # Calcular estatísticas
  count=${#values[@]}
  sum=0
  for value in "${values[@]}"; do
    sum=$(echo "$sum + $value" | bc)
  done
  average=$(echo "scale=2; $sum / $count" | bc)
  variance=0
  for value in "${values[@]}"; do
    variance=$(echo "$variance + ($value - $average)^2" | bc)
  done
  variance=$(echo "scale=2; $variance / $count" | bc)
  stddev=$(echo "scale=2; sqrt($variance)" | bc)

  # Salvar os valores e as estatísticas em um arquivo de dados
  echo -e "Valor\n${values[*]}" > "$output_file"
  echo -e "Estatística,Valor\nMédia,$average\nDesvio Padrão,$stddev" >> "$output_file"
}

rm -f "$input_file"
rm -f "$output_file"

for i in {1..50}; do
    qemu-system-arm -M lm3s6965evb -m 128M -nographic -semihosting --semihosting-config enable=on,target=native -kernel main.bin >> out.log &
    sleep 0.2
    killall qemu-system-arm
    sleep 0.2
done

killall qemu-system-arm

while IFS= read -r line; do
  if [[ $line == *"Ciclos de clock decorridos:"* ]]; then
    value=$(extract_value "$line")
    echo "$value" >> "$output_file"
  fi
done < "$input_file"

calculate_statistics "$output_file"
