# Funcionamento de main.c 

Este código é escrito para um microcontrolador da família STM32F1 e demonstra o uso do registro SysTick para medir o número de ciclos de clock decorridos durante a execução de um programa.

## Visão geral do código

O código começa incluindo a biblioteca `stm32f10x.h`, que é específica para a família de microcontroladores STM32F1. Também é incluída a biblioteca `stdio.h` para permitir o uso da função `printf` mais tarde.

Em seguida, o código declara e implementa duas funções auxiliares: `binarySearch` e `int_to_string`. A função `binarySearch` realiza uma busca binária em um array ordenado. A função `int_to_string` converte um número inteiro em uma string.

A função principal `main` realiza o seguinte:

1. Declara um array ordenado `arr`, seu tamanho `n` e uma variável `target`.
2. Configura o registrador SysTick para contar os ciclos de clock. Ele desabilita o contador, define o valor máximo de contagem, reinicia o valor atual para zero e habilita o contador usando o clock do processador.
3. Realiza uma busca binária no array usando a função `binarySearch` e armazena o resultado em `result`.
4. Captura o valor atual do contador de ciclos de clock do registrador SysTick.
5. Converte o resultado em uma string usando a função `int_to_string`.
6. Imprime uma mensagem indicando se o elemento foi encontrado no array ou não, juntamente com o valor do resultado.
7. Imprime o número de ciclos de clock decorridos durante a execução do programa.

## Uso do SysTick

O SysTick é um timer interno encontrado em muitos microcontroladores ARM. Ele pode ser usado para medir o tempo ou os ciclos de clock decorridos durante a execução de um programa.

Neste código, o registro SysTick é configurado da seguinte maneira:

```c
SysTick->CTRL = 0; // Desabilitar o contador
SysTick->LOAD = 0xFFFFFF; // Valor máximo de contagem
SysTick->VAL = 0; // Reiniciar o valor atual para zero
SysTick->CTRL = 0x00000005; // Habilitar o contador com o clock do processador
```

1. `SysTick->CTRL = 0` desabilita o contador de SysTick para que possa ser configurado.
2. `SysTick->LOAD = 0xFFFFFF` define o valor máximo de contagem para 0xFFFFFF, o que significa que o contador contará até esse valor e depois será reiniciado.
3. `SysTick->VAL = 0` reinicia o valor atual do contador para zero.
4. `SysTick->CTRL = 0x00000005` habilita o contador SysTick com a fonte de clock do processador.

Após a execução do programa, o valor atual do contador de ciclos de clock é capturado usando a linha de código:


```c
uint32_t cycles = SysTick->VAL;
```


O valor capturado em `cycles` representa o número de ciclos de clock decorridos durante a execução do programa.


# Funcionamento do código Vectors.s

Este é um código Assembly escrito para a arquitetura Cortex-M3. O código define um vetor de inicialização (_start) que é responsável por configurar a pilha e chamar a função `main`. O vetor de inicialização é seguido por uma função `reset`, que chama a função `main`, e uma função `hang`, que cria um loop infinito.

## Visão geral do código

Aqui está uma descrição passo a passo do funcionamento do código:

1. O código começa especificando a arquitetura alvo com a diretiva `.cpu cortex-m3`. Isso informa ao montador que o código deve ser montado para a arquitetura Cortex-M3.

2. A diretiva `.thumb` indica que o código será escrito usando a instrução Thumb da arquitetura Cortex-M3. A instrução Thumb é uma versão de 16 bits das instruções ARM de 32 bits, que é mais compacta e geralmente mais eficiente para microcontroladores com recursos limitados.

3. A função `_start` é definida usando a diretiva `.thumb_func`. Essa função é o ponto de entrada do programa e contém um vetor de inicialização.

4. O vetor de inicialização começa com um rótulo `stacktop` que define o endereço inicial da pilha. Nesse caso, o endereço é definido como `0x20001000`.

5. Em seguida, o vetor de inicialização contém uma sequência de palavras (instruções) que especificam onde o programa deve ir após uma interrupção ocorrer. Neste caso, todas as palavras são definidas como `hang`, o que cria um loop infinito.

6. A função `reset` é definida usando a diretiva `.thumb_func`. Essa função é chamada pelo vetor de inicialização e serve para iniciar a execução do programa.

7. Dentro da função `reset`, a instrução `bl main` é usada para chamar a função `main`. A instrução `bl` (branch with link) é usada para fazer uma chamada de função e armazenar o endereço de retorno em um registrador.

8. Após a chamada da função `main`, a instrução `b hang` é usada para criar um salto para a função `hang`, que é um loop infinito.

9. A função `hang` é definida usando a diretiva `.thumb_func` e contém uma instrução `b .`, que faz um salto para o endereço atual. Isso cria um loop infinito, mantendo o programa em execução indefinidamente.


# Funcionamento do arquivo `memorymap`

O arquivo `memorymap` é um arquivo de configuração usado durante o processo de compilação e vinculação para mapear as seções do programa na memória do microcontrolador.

## Visão geral do arquivo

Descrição do conteúdo do arquivo `memorymap`:

```
MEMORY
{
rom : ORIGIN = 0x00000000, LENGTH = 0x1000
ram : ORIGIN = 0x20000000, LENGTH = 0x1000
}

SECTIONS
{
.text : { (.text) } > rom
.rodata : { (.rodata) } > rom
.bss : { (.bss) } > ram
}
```

O arquivo é dividido em duas seções principais: `MEMORY` e `SECTIONS`.

## Seção MEMORY

A seção `MEMORY` especifica as regiões de memória que serão usadas pelo programa. Neste caso, há duas regiões definidas:

- `rom` : Esta região representa a memória de programa (flash) e é definida com `ORIGIN = 0x00000000` e `LENGTH = 0x1000`. Isso significa que a memória de programa começa no endereço `0x00000000` e tem um tamanho de `0x1000` bytes (4 KB).
- `ram` : Esta região representa a memória RAM e é definida com `ORIGIN = 0x20000000` e `LENGTH = 0x1000`. Isso significa que a memória RAM começa no endereço `0x20000000` e tem um tamanho de `0x1000` bytes (4 KB).

## Seção SECTIONS

A seção `SECTIONS` especifica como as seções do programa são mapeadas nas regiões de memória definidas na seção `MEMORY`.

Neste caso, três seções são definidas:

- `.text` : Esta seção contém o código do programa e é mapeada na região de memória `rom`. O `*(.text*)` indica que todas as subseções com o prefixo `.text` devem ser incluídas nesta seção.
- `.rodata` : Esta seção contém dados somente leitura (constantes) e também é mapeada na região de memória `rom`. O `*(.rodata*)` indica que todas as subseções com o prefixo `.rodata` devem ser incluídas nesta seção.
- `.bss` : Esta seção contém variáveis não inicializadas (zeradas) e é mapeada na região de memória `ram`. O `*(.bss*)` indica que todas as subseções com o prefixo `.bss` devem ser incluídas nesta seção.

## Observações 

O arquivo `memorymap` é usado pelo processo de compilação e vinculação para determinar onde cada seção do programa será armazenada na memória do microcontrolador.

Durante o processo de compilação e vinculação, o arquivo `memorymap` deve ser fornecido como um argumento para o comando `arm-none-eabi-ld` ou similar.

# Funcionamento do código de compilação e emulação

Este Markdown descreve o funcionamento do código de compilação e emulação. O código faz uso das ferramentas `arm-none-eabi` e QEMU para compilar e emular o programa.

## Visão geral

O processo de compilação e emulação é realizado por meio de um arquivo Makefile, que contém regras e comandos para automatizar as tarefas.

Aqui estão os principais comandos utilizados no processo:

- `all` : Define o alvo padrão como `main.bin`, ou seja, ao executar o comando `make` sem nenhum argumento, o arquivo `main.bin` será gerado.

- `clean` : Responsável por limpar os arquivos binários, intermediários e de listagem gerados durante a compilação.

- `vectors.o` e `main.o` : Regras que especificam como compilar os arquivos Assembly `vectors.s` e C `main.c`, respectivamente, em seus respectivos arquivos objeto `.o`.

- `main.bin` : Regra que define como vincular os arquivos objeto `vectors.o` e `main.o` para gerar o executável `main.bin`. Também gera o arquivo de listagem `main.list` e converte o executável em formato binário.

- `qemu` : Regra que inicia a emulação do programa utilizando o QEMU. O arquivo `main.bin` é utilizado como kernel, e são configuradas opções específicas para o modelo do microcontrolador LM3S6965EVB.

## Observações

Ao executar o comando `make`, o código será compilado e o arquivo `main.bin` será gerado. Para iniciar a emulação do programa, utilize o comando `make qemu`, que iniciará o QEMU com as configurações adequadas.


##### (Arquivo gerado por IA)
