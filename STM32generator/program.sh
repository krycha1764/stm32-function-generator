#!/bin/sh

arm-none-eabi-objcopy -I ihex ./Debug/STM32generator.hex -O binary STM32generator.bin
dfu-util -a 0 -i 0 -s 0x08000000:leave -D STM32generator.bin
