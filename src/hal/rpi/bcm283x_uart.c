#include "bcm283x_uart.h"

void rpi_hal_uart_init(const enum rpi_hal_uart_lineCtl control, const enum rpi_hal_uart_baudrate baudrate) {
  uart.lineCtl = control;
  uart.control = uart_control_reset;
  uart.intBaudrateDiv = baudrate >> 5;
  uart.fracBaudrateDiv = baudrate & 0x3F;
}

void rpi_hal_uart_transmitByte(const rpi_hal_uint8_t data) {
  uart.control = uart_control_transmitEnable | uart_control_enable;

  uart.data = data;

  uart.control = uart_control_reset;
}

rpi_hal_uint8_t rpi_hal_uart_receiveByte() {
  uart.control = uart_control_receiveEnable | uart_control_enable;

  rpi_hal_uint8_t recv = uart.data & 0xFF;

  uart.control = uart_control_reset;

  return recv;
}

void rpi_hal_uart_deinit() {
  uart.lineCtl = uart_lineCtl_reset;
  uart.control = uart_control_reset;
}
