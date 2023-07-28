# Makefile

Este é um modelo de Makefile para construir projetos de microcontrolador STM32F103C6 (bluepill genérica) usando a ferramenta ARM GCC. Ele inclui suporte para compilar arquivos de origem C e assembly, fazer a ligação e gerar arquivos de saída binários e hexadecimais. Também oferece alvos para limpar o diretório de construção, gravar o firmware e depurar o aplicativo.

## Pré-requisitos

Certifique-se de ter o conjunto de ferramentas ARM GCC instalado em seu sistema. Você pode baixá-lo [aqui](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads). Além disso, verifique se você tem o `st-flash` e o `openocd` instalados para gravar e depurar o microcontrolador STM32.

## Estrutura do Projeto

Ajuste as seguintes variáveis para corresponder à estrutura do seu projeto:

```makefile
ARMCPU   = cortex-m3
STM32MCU = STM32F103x6
LINKERSCRIPT = scripts/STM32F103X6_FLASH.ld

# Diretórios do projeto
SRCDIR   = src
INCDIR   = inc
ASMDIR   = startup
CMSISDIR = cmsis
BUILDDIR = build

# Nome do arquivo de saída
APP_NAME = perf
```

## Compilando o Projeto

Para construir o projeto, basta executar:

```bash
make
```

## Gravando o Firmware

Para gravar o firmware no microcontrolador STM32, execute:

```bash
make flash
```

Isso pressupõe que você tenha o st-flash instalado e disponível no PATH do seu sistema.

## Depurando o Aplicativo

Para depurar o aplicativo usando GDB e OpenOCD, execute:

```bash
make debug
```

Essa rotina executara um arquivo em python que automatiza a rotina de analise de desempenho dos algoritmos.

# hwdebug.py

# README - Script de Medição de Ciclos com GDB

Este é um script em Python que utiliza o GDB (GNU Debugger) para realizar medições de ciclos de CPU em um programa embarcado. O script se conecta a um alvo remoto via GDB e insere pontos de interrupção em locais específicos do código fonte para realizar a medição.

## Dependências

Certifique-se de ter o GDB-multiarch instalado em seu sistema.

## Configuração

O script possui algumas variáveis configuráveis que podem ser ajustadas conforme necessário:

- `n_measures`: O número de medidas que deseja realizar (por padrão, são 10 medições).
- `breakpoint`: Uma lista que contém as linhas do código onde você deseja inserir os pontos de interrupção. Essas linhas devem ser fornecidas na forma de nome do arquivo e número da linha (por exemplo, 'main.c:35').
- `defines`: Uma lista que contém os nomes dos defines que você deseja avaliar para inserir os pontos de interrupção. Por exemplo, 'BUBBLE', 'TREE', 'BUBBLE_W'.

## Funcionamento

O script realiza o seguinte:

1. Define algumas configurações do GDB para desabilitar a confirmação de saída e a paginação do GDB.
2. Conecta-se ao alvo remoto via GDB usando `target remote`.
3. Avalia os defines fornecidos na lista `defines` usando o comando `info macro`. O objetivo é verificar se esses defines estão definidos e, se estiverem, retornar o nome do arquivo e número da linha para inserir os pontos de interrupção.
4. Insere os pontos de interrupção nas linhas do código fonte obtidas na etapa anterior usando o comando `break`.
5. Inicia a execução do programa com o comando `c`.
6. A cada medição, obtém o valor da variável `cycles`, que é a contagem de ciclos de CPU, usando o comando `parse_and_eval`.
7. Armazena o valor da contagem de ciclos em uma lista chamada `measure`.
8. Após todas as medições, o script exibe os valores de medição e encerra o GDB usando o comando `quit`.

