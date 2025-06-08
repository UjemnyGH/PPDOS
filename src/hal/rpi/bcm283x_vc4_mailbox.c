#include "bcm283x_vc4_mailbox.h"

#define MAILBOX_READ    (*(rpi_hal_io32_t*)(RPI_HAL_MAILBOX_BASE))
#define MAILBOX_STATUS  (*(rpi_hal_io32_t*)(RPI_HAL_MAILBOX_BASE + 0x18))
#define MAILBOX_WRITE   (*(rpi_hal_io32_t*)(RPI_HAL_MAILBOX_BASE + 0x20))

#define MAILBOX_FULL    0x80000000
#define MAILBOX_EMPTY   0x40000000

#define MAILBOX_CHANNEL_PROP 8
static rpi_hal_io32_t __attribute__((aligned(16))) gMailboxBuffer[36];

rpi_hal_uint32_t rpi_hal_vc4_mailboxCall(const rpi_hal_uint8_t channel) {
  rpi_hal_uint32_t addr = ((rpi_hal_uint32_t)(unsigned long)gMailboxBuffer) & ~0xF;

  while(MAILBOX_STATUS & MAILBOX_FULL);

  MAILBOX_WRITE = addr | (channel & 0xF);

  while(1) {
    while(MAILBOX_STATUS & MAILBOX_EMPTY);
    rpi_hal_uint32_t response = MAILBOX_READ;

    if((response & 0xF) == channel && (response & ~0xF) == addr)
      return gMailboxBuffer[1] == MAILBOX_FULL;
  }

  return 0;
}

void rpi_hal_vc4_enablePower() {
  gMailboxBuffer[0] = 8 * sizeof(rpi_hal_io32_t); /*Buffer size*/
  gMailboxBuffer[1] = 0;  /*Request code*/

  gMailboxBuffer[2] = 0x00028001; /*Set power state*/
  gMailboxBuffer[3] = 8;
  gMailboxBuffer[4] = 8;
  gMailboxBuffer[5] = 3; /*Device id: 3 for V3D*/
  gMailboxBuffer[6] = 1 << 0; /*Bit 0 as power on*/

  gMailboxBuffer[7] = 0; /*End*/

  rpi_hal_vc4_mailboxCall(MAILBOX_CHANNEL_PROP);
}

void rpi_hal_vc4_setClock(const rpi_hal_uint32_t hz) {
  gMailboxBuffer[0] = 9 * sizeof(rpi_hal_io32_t); /*Buffer size*/
  gMailboxBuffer[1] = 0;  /*Request code*/

  gMailboxBuffer[2] = 0x00038000; /*Set clock rate*/
  gMailboxBuffer[3] = 12;
  gMailboxBuffer[4] = 12;
  gMailboxBuffer[5] = 6; /*Clock id: 6 for V3D*/
  gMailboxBuffer[6] = hz; /*Clock rate*/
  gMailboxBuffer[7] = 0; /*Skip turbo*/

  gMailboxBuffer[8] = 0; /*End*/

  rpi_hal_vc4_mailboxCall(MAILBOX_CHANNEL_PROP);
}
