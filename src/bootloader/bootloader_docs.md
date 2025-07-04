# Bootloader documentation

[**Home**](src/home_docs.md)

[**Common**](src/common/common_docs.md)
[**Drivers**](src/drivers/drivers_docs.md)
[**Filesystem**](src/filesystem/filesystem_docs.md)
[**HAL**](src/hal/hal_docs.md)
[**Kernel**](src/kernel/kernel_docs.md)

Bootloader is really small, just enought to run kernel_main() in [kernel_main.c](src/kernel/kernel_main.c)

Bootloader consist currently 2 files:
- [loader.s](src/bootloader/loader.s) - loads and runs void kernel_main()
- [vectorTable.s](src/bootloader/vectorTable.s) - loads interrupts for vector table
