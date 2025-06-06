cmake_minimum_required(VERSION 3.16)
project(PPDOS C ASM)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-as)
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/src/linker.ld)

file(GLOB_RECURSE HAL_RPI_SOURCE "${CMAKE_SOURCE_DIR}/src/hal/rpi/*.c")

set(C_SOURCES
  ${CMAKE_SOURCE_DIR}/src/kernel/kernel_main.c
  ${HAL_RPI_SOURCE}
)

set(ASM_SOURCES
  ${CMAKE_SOURCE_DIR}/src/bootloader/loader.s
)

foreach(asm_file ${ASM_SOURCES})
  set_source_files_properties(${asm_file} PROPERTIES LANGUAGE ASM)
endforeach()

add_library(baremetal_config INTERFACE)

target_compile_options(baremetal_config INTERFACE 
  $<$<COMPILE_LANGUAGE:C>:-mthumb -mcpu=cortex-a53 -ffreestanding -nostdlib>
)

target_link_options(baremetal_config INTERFACE 
  -mthumb -nostdlib -T ${LINKER_SCRIPT}
)

add_executable(kernel.elf ${C_SOURCES} ${ASM_SOURCES})
target_link_libraries(kernel.elf PRIVATE baremetal_config)

add_custom_command(
  TARGET kernel.elf POST_BUILD
  COMMAND arm-none-eabi-objcopy -O binary kernel.elf kernel.img
  COMMENT "Generating kernel.img"
)
