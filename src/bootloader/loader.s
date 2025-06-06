.section .text
.arm
.global _start
.align 2

_start:
  ldr sp, =stack_top

  bl kernel_main

hang:
  b hang

.section .bss
  .space 4096
stack_top:
