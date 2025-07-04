#include "kernel_vector.h"

/**
 * These function handle running interrupts, they are used inside bootloader/vectorTable.s asm source file
 */

void vectorCallSyncEL0Handler() {
  if(vectorCallSyncEL0Fn)
    vectorCallSyncEL0Fn();
}

void vectorCallIRQEL0Handler() {
  if(vectorCallIRQEL0Fn)
    vectorCallIRQEL0Fn();
}

void vectorCallFIQEL0Handler() {
  if(vectorCallFIQEL0Fn)
    vectorCallFIQEL0Fn();
}

void vectorCallSErrorEL0Handler() {
  if(vectorCallSErrorEL0Fn)
    vectorCallSErrorEL0Fn();
}

void vectorCallSyncEL1Handler() {
  if(vectorCallSyncEL1Fn)
    vectorCallSyncEL1Fn();
}

void vectorCallIRQEL1Handler() {
  if(vectorCallIRQEL1Fn)
    vectorCallIRQEL1Fn();
}

void vectorCallFIQEL1Handler() {
  if(vectorCallFIQEL1Fn)
    vectorCallFIQEL1Fn();
}

void vectorCallSErrorEL1Handler() {
  if(vectorCallSErrorEL1Fn)
    vectorCallSErrorEL1Fn();
}

extern unsigned long long _vectorTable;

void kernel_initializeVectorTable() {
  asm volatile("msr VBAR_EL1, %0" : : "r"(&_vectorTable));
  asm volatile("isb");
}
