cmake_minimum_required(VERSION 3.16)
project(PPDOS C ASM)

set(EXE_NAME kernel8)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER aarch64-none-elf-gcc)
set(CMAKE_ASM_COMPILER aarch64-none-elf-as)
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/src/linker.ld)

file(GLOB_RECURSE HAL_RPI_SOURCE "${CMAKE_SOURCE_DIR}/src/hal/rpi/*.c")
file(GLOB_RECURSE COMMON_SOURCE "${CMAKE_SOURCE_DIR}/src/common/*.c")
file(GLOB_RECURSE FILESYSTEM_SOURCE "${CMAKE_SOURCE_DIR}/src/filesystem/*.c")

set(C_SOURCES
  ${CMAKE_SOURCE_DIR}/src/kernel/kernel_main.c
  ${CMAKE_SOURCE_DIR}/src/drivers/st7735s.c
  ${CMAKE_SOURCE_DIR}/src/drivers/pcd8544.c
  ${CMAKE_SOURCE_DIR}/src/drivers/hd44780.c
  ${CMAKE_SOURCE_DIR}/src/drivers/usb.c
  ${HAL_RPI_SOURCE}
  ${COMMON_SOURCE}
  ${FILESYSTEM_SOURCE}
)

set(ASM_SOURCES
  ${CMAKE_SOURCE_DIR}/src/bootloader/loader.s
)

foreach(asm_file ${ASM_SOURCES})
  set_source_files_properties(${asm_file} PROPERTIES LANGUAGE ASM)
endforeach()

add_library(baremetal_config INTERFACE)

target_compile_options(baremetal_config INTERFACE 
  $<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-a53 -ffreestanding -nostdlib>
)

target_link_options(baremetal_config INTERFACE 
  -nostdlib -T ${LINKER_SCRIPT}
)

add_executable(${EXE_NAME}.elf ${C_SOURCES} ${ASM_SOURCES})
target_link_libraries(${EXE_NAME}.elf PRIVATE baremetal_config)

add_custom_command(
  TARGET ${EXE_NAME}.elf POST_BUILD
  COMMAND aarch64-none-elf-objcopy -O binary ${EXE_NAME}.elf ${EXE_NAME}.img
  COMMENT "Generating kernel.img"
)
