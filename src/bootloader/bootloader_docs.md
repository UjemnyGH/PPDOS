# Bootloader documentation

[**Home**](../../home_docs.md)

[**Common**](../common/common_docs.md)
[**Drivers**](../drivers/drivers_docs.md)
[**Filesystem**](../filesystem/filesystem_docs.md)
[**HAL**](../hal/hal_docs.md)
[**Kernel**](../kernel/kernel_docs.md)

Bootloader is really small, just enought to run kernel_main() in [kernel_main.c](../../kernel/kernel_main.c)

Bootloader currently consist 2 files:
- [loader.s](../bootloader/loader.s) - loads and runs void kernel_main()
- [vectorTable.s](../bootloader/vectorTable.s) - loads interrupts for vector table
