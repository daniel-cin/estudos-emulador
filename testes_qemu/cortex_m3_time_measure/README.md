# Exemplo de leitura de ciclos de clock

#### Versoes dos softwares utilizados

```console
$ arm-none-eabi-gcc --version | head -n1
arm-none-eabi-gcc (15:10.3-2021.07-4) 10.3.1 20210621 (release)

$ arm-none-eabi-ld --version | head -n1
GNU ld (2.38-3ubuntu1+15build1) 2.38

$ arm-none-eabi-objcopy --version | head -n1
GNU objcopy (2.38-3ubuntu1+15build1) 2.38

$ arm-none-eabi-objdump --version | head -n1
GNU objdump (2.38-3ubuntu1+15build1) 2.38

$ qemu-system-arm --version
QEMU emulator version 6.2.0 (Debian 1:6.2+dfsg-2ubuntu6.11)

```

## Execução do código

Temos um arquivo makefile que para compilar o código e gerar o binário, basta executar o comando:

```console
$ make
```
e para executar o binário gerado com o qemu, basta executar o comando:

```console  
$ make qemu
```

## Referencias uteis para o código

https://developer.arm.com/documentation/dui0552/a/cortex-m3-peripherals/system-timer--systick

https://jacobmossberg.se/posts/2018/08/11/run-c-program-bare-metal-on-arm-cortex-m3.html#files

https://www.youtube.com/watch?v=i8Fl-1avuck