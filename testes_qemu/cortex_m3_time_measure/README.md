# Instruções de execução

## Dependências

Os códigos nesse diretório usam os software QEMU (restrito à emulação de sistema com arquitetura Arm) e o Arm GNU Toolchain. Ambos devem ser instalados para execução dos códigos. As próximas sessões apresentam um tutorial padrão para instalação desses pacotes no Ubuntu 22.04.2 LTS.

### QEMU emulator

Primeiro instale as dependências do QEMU

```console
sudo apt install libpixman-1-dev libcairo2-dev libpango1.0-dev libjpeg8-dev libgif-dev ninja-build
```

Depois instale o emulador de sistema para Arm do QEMU.

```console
sudo apt-get install qemu-system-arm
```

A versão utilizada no desenvolvimento do projeto é a 6.2.0 (Debian 1:6.2+dfsg-2ubuntu6.11).

### Arm GNU Toolchain

Faça o download do arquivo tar.xz correspondente a Linux_x86  no site https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads.

Extraia para alguma pasta, por exemplo /usr/share/, com

```console
sudo tar -xvf arm-gnu-toolchain-12.2.mpacbti-rel1-x86_64-arm-none-eabi.tar.xz -C /usr/share/
```

Crie os links que são necessários para esse projeto:

```console
sudo ln -s /usr/share/arm-gnu-toolchain-12.2.mpacbti-rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-gcc /usr/bin/arm-none-eabi-gcc
sudo ln -s /usr/share/arm-gnu-toolchain-12.2.mpacbti-rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-ld /usr/bin/arm-none-eabi-ld
sudo ln -s /usr/share/arm-gnu-toolchain-12.2.mpacbti-rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-objdump /usr/bin/arm-none-eabi-objdump
sudo ln -s /usr/share/arm-gnu-toolchain-12.2.mpacbti-rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-objcopy /usr/bin/arm-none-eabi-objcopy
sudo ln -s /usr/share/arm-gnu-toolchain-12.2.mpacbti-rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-gdb /usr/bin/arm-none-eabi-gdb
sudo ln -s /usr/share/arm-gnu-toolchain-12.2.mpacbti-rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-as /usr/bin/arm-none-eabi-as
```

A versão desse software utilizada no desenvolvimento do projeto é a 12.2.MPACBTI-Rel1 (Build arm-12-mpacbti.34) 2.40.0.20230307

Obs: nos comandos acima trocar o nome do arquivo caso a versão seja diferente.

## Execução do código

Temos um arquivo makefile que para compilar o código e gerar o binário, basta executar o comando:

```console
$ make
```
e para executar o binário gerado com o qemu, basta executar o comando:

```console  
$ make qemu
```

Para terminar a execução, utilizar o atalho **ctrl+a x** que encerra a instância criada do QEMU.

## Execução dos testes

No arquivo makefile existem alvos que são relacionados a testes, eles fornecem outputs estatísticos a respeito de um algoritmo de busca binaria e de algumas iteraçoes em loop com quantdade de iteraçoes progressivas (1, 10, 100, 1000, ..., 10000000), para validar a linearidade de ciclos de clocks consumidos, por meio do registrador `Systick` do Cortex-M3.
Para rodar os testes, basta executar o comando:

```console
$ make statistics
```
para executar os dois testes citados ou:

```console
$ make statistics_iterative
```

```console
$ make statistics_binary
```

para executar os testes individualmente.

PS: Devido a algum bug o terminal pode ficar travado após a execução dos testes.

O output dos testes vai para o diretorio `statatisctics/`, entre estes outputs estão, os arquivos crus do output direto da sequencia de execução dos batches de testes do QEMU, arquivos CSV com a quantidade de ciclos de clock de cada batch de teste realizado (extraidos dos arquivos crús), e arquivos PNG com os gráficos de cada batch de teste realizado.

Dentro do makefile temos a variavel RUNS que determina qual sera o tamanho dos lotes de testes, inicialmente temos uma amostragem de 10 execuções por teste.

## Referencias uteis para o código

https://developer.arm.com/documentation/dui0552/a/cortex-m3-peripherals/system-timer--systick

https://jacobmossberg.se/posts/2018/08/11/run-c-program-bare-metal-on-arm-cortex-m3.html#files

https://www.youtube.com/watch?v=i8Fl-1avuck