qemu-system-arm -M lm3s6965evb -m 128M \
 -nographic -semihosting --semihosting-config enable=on,target=native -serial mon:stdio \
 -kernel test_program.bin 