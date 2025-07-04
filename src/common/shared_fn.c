#include "shared_fn.h"
#include "../kernel/kernel_vector.h"

volatile int gDelayDone = 0;

uint32_t readCounterFrequency_EL0() {
  uint32_t val;
  asm volatile("mrs %0, cntfrq_el0" : "=r"(val));
  
  return val;
}

uint64_t readCounterCurrentCount_EL0() {
  uint64_t val;
  asm volatile("mrs %0, cntvct_el0" : "=r"(val));

  return val;
}

void writeCounterCompareValue_EL0(const uint64_t val) {
  asm volatile("msr cntv_cval_el0, %0" : : "r"(val));
}

void enableCounter_EL0() {
  uint32_t val = 0;
  asm volatile("mrs %0, cntv_ctl_el0" : "=r"(val));
  val |= 3;
  asm volatile("msr cntv_ctl_el0, %0" : : "r"(val));
}

void disableCounter_EL0() {
  uint32_t val = 0;
  asm volatile("msr cntv_ctl_el0, %0" : : "r"(val));
}

static void _genericTimerIRQHandler() {
  disableCounter_EL0();

  asm volatile("dsb sy");
  gDelayDone = 1;
  asm volatile("isb");
}

void delay_us(uint64_t us) {
  gDelayDone = 0;
  vectorCallIRQEL1Fn = _genericTimerIRQHandler;

  uint64_t frequency = readCounterFrequency_EL0();
  uint64_t now = readCounterCurrentCount_EL0();
  uint64_t ticksToWait = (frequency * us) / 1000000ULL;
  uint64_t target = now + ticksToWait;

  writeCounterCompareValue_EL0(target);
  enableCounter_EL0();

  // Enable IRQ
  asm volatile("msr daifclr, #2");

  while(!gDelayDone) {
    asm volatile("wfi");
    asm volatile("dmb ish");
  }

  // Disable IRQ
  asm volatile("msr daifset, #2");
}

void delay_ms(uint64_t ms) {
  delay_us(ms * 1000);
}
