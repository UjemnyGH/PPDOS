.section .text.boot
.global _start

_start:
  mrs x1, mpidr_el1
  and x1, x1, #3
  cbz x1, 2f

1: wfe
  b 1b
2:
  ldr x1, =_start
  mov sp, x1

  ldr x1, =__bss_start
  ldr x2, =__bss_size
3: cbz x2, 4f
  str xzr, [x1], #8
  sub x2, x2, #1
  cbnz x2, 3b

  mrs x0, SCTLR_EL1
  bic x0, x0, #(1 << 0)
  bic x0, x0, #(1 << 2)
  bic x0, x0, #(1 << 12)
  msr SCTLR_EL1, x0
  isb

4:  bl kernel_main

  b 1b
