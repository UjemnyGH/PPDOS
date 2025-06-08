# PPDOS
Simple operating systen for Raspberry Pi

###### What it currently fully support
- Rough implementation of rpi hal library
- GPIO
- SD HCI
- SPI
- Basic VC4 initialization over mailbox

This are early stages of development (I literally started writing this project 2 days ago (04.06.2025))

###### Compiling:
Currently you need aarch64-none-elf-gcc and cmake. Run
```
Open kernel/hal_config.h
in kernel/hal_config.h uncomment your Raspberry Pi or CPU(I use PPDOS_USE_RPI_ZERO_2_W, so comment that out if you using other rpi)

mkdir build
cd build
cmake ..
cmake --build .
```
and you should have a compiled binaries (kernel8.elf) and image (kernel8.img) of PPDOS
Then you need to only replace kerlen8.img in boot partition
