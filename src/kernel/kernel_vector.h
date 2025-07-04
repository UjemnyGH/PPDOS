#ifndef _PPDOS_KERNEL_VECTOR_
#define _PPDOS_KERNEL_VECTOR_

static void (*vectorCallSyncEL0Fn)(void) = 0;
static void (*vectorCallIRQEL0Fn)(void) = 0;
static void (*vectorCallFIQEL0Fn)(void) = 0;
static void (*vectorCallSErrorEL0Fn)(void) = 0;

static void (*vectorCallSyncEL1Fn)(void) = 0;
static void (*vectorCallIRQEL1Fn)(void) = 0;
static void (*vectorCallFIQEL1Fn)(void) = 0;
static void (*vectorCallSErrorEL1Fn)(void) = 0;

void kernel_initializeVectorTable();

#endif
