.section .vectors, "a"
.align 11 // align to 2KB
.global _vectorTable
_vectorTable:
  // Exception level 1 AArch64
  b sync_el1h
  b irq_el1h
  b fiq_el1h
  b serror_el1h

  // Exception level 0 AArch64
  b sync_el0h
  b irq_el0h
  b fiq_el0h
  b serror_el0h

  // Exception level 1 AArch32
  b sync_el1h_32
  b irq_el1h_32
  b fiq_el1h_32
  b serror_el1h_32

  // Exception level 0 AArch32
  b sync_el0h_32
  b irq_el0h_32
  b fiq_el0h_32
  b serror_el0h_32

// 
// Base handling is done by storing last pointer, calling handler, loading last pointer and then returning, A32 does nothing
//

sync_el1h:
  stp x0, x1, [sp, #-16]!
  bl vectorCallSyncEL1Handler
  ldp x0, x1, [sp], #16
  eret

irq_el1h:
  stp x0, x1, [sp, #-16]!
  bl vectorCallIRQEL1Handler
  ldp x0, x1, [sp], #16
  eret

fiq_el1h:
  stp x0, x1, [sp, #-16]!
  bl vectorCallFIQEL1Handler
  ldp x0, x1, [sp], #16
  eret

serror_el1h:
  stp x0, x1, [sp, #-16]!
  bl vectorCallSErrorEL1Handler
  ldp x0, x1, [sp], #16
  eret

sync_el0h:
  stp x0, x1, [sp, #-16]!
  bl vectorCallSyncEL0Handler
  ldp x0, x1, [sp], #16
  eret

irq_el0h:
  stp x0, x1, [sp, #-16]!
  bl vectorCallIRQEL0Handler
  ldp x0, x1, [sp], #16
  eret

fiq_el0h:
  stp x0, x1, [sp, #-16]!
  bl vectorCallFIQEL0Handler
  ldp x0, x1, [sp], #16
  eret

serror_el0h:
  stp x0, x1, [sp, #-16]!
  bl vectorCallSErrorEL0Handler
  ldp x0, x1, [sp], #16
  eret

sync_el1h_32: ret
irq_el1h_32: ret
fiq_el1h_32: ret
serror_el1h_32: ret
sync_el0h_32: ret
irq_el0h_32: ret
fiq_el0h_32: ret
serror_el0h_32: ret

