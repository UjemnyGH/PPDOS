# PPDOS
Simple operating systen for Raspberry Pi

###### What it currently fully support
- Rough implementation of rpi hal library
- GPIO
- SD HCI

This are early stages of development (I literally started writing this project 2 days ago (04.06.2025))

###### Compiling:
Currently you need arm-none-abi-gcc and cmake. Run
```
mkdir build
cd build
cmake ..
cmake --build .
```
and you should have a compiled binaries (kernel.elf) and image (kernel.img) of PPDOS
