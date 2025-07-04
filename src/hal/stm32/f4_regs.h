#ifndef _PPDOS_HAL_STM32F4_REGISTERS_
#define _PPDOS_HAL_STM32F4_REGISTERS_

typedef volatile unsigned char f4_hal_io8_t;
typedef volatile unsigned short f4_hal_io16_t;
typedef volatile unsigned int f4_hal_io32_t;

typedef unsigned char f4_hal_uint8_t;
typedef unsigned short f4_hal_uint16_t;
typedef unsigned int f4_hal_uint32_t;

// AHB2
#define F4_HAL_USB_OTG_FS_BASE         0x50000000
// AHB1
#define F4_HAL_DMA2_BASE               0x40026400
#define F4_HAL_DMA1_BASE               0x40026000
#define F4_HAL_FLASH_INTERFACE_BASE    0x40023c00
#define F4_HAL_RCC_BASE                0x40023800
#define F4_HAL_CRC_BASE                0x40023000
#define F4_HAL_GPIOH_BASE              0x40021c00
#define F4_HAL_GPIOE_BASE              0x40021000
#define F4_HAL_GPIOD_BASE              0x40020c00
#define F4_HAL_GPIOC_BASE              0x40020800
#define F4_HAL_GPIOB_BASE              0x40020400
#define F4_HAL_GPIOA_BASE              0x40020000
// APB2
#define F4_HAL_SPI5_BASE               0x40015000
#define F4_HAL_TIM11_BASE              0x40014800
#define F4_HAL_TIM10_BASE              0x40014400
#define F4_HAL_TIM9_BASE               0x40014000
#define F4_HAL_EXTI_BASE               0x40013c00
#define F4_HAL_SYSCFG_BASE             0x40013800
#define F4_HAL_SPI4_BASE               0x40013400
#define F4_HAL_SPI1_BASE               0x40013000
#define F4_HAL_SDIO_BASE               0x40012c00
#define F4_HAL_ADC1_BASE               0x40012000
#define F4_HAL_USART6_BASE             0x40011400
#define F4_HAL_USART1_BASE             0x40011000
#define F4_HAL_TIM1_BASE               0x40010000
// APB1
#define F4_HAL_PWR_BASE                0x40007000
#define F4_HAL_I2C3_BASE               0x40005c00
#define F4_HAL_I2C2_BASE               0x40005800
#define F4_HAL_I2C1_BASE               0x40005400
#define F4_HAL_USART2_BASE             0x40004400
#define F4_HAL_I2S3EXT_BASE            0x40004000
#define F4_HAL_SPI3_BASE               0x40003c00
#define F4_HAL_SPI2_BASE               0x40003800
#define F4_HAL_I2S2EXT_BASE            0x40003400
#define F4_HAL_IWDG_BASE               0x40003000
#define F4_HAL_WWDG_BASE               0x40002c00
#define F4_HAL_RTC_BASE                0x40002800
#define F4_HAL_TIM5_BASE               0x40000c00
#define F4_HAL_TIM4_BASE               0x40000800
#define F4_HAL_TIM3_BASE               0x40000400
#define F4_HAL_TIM2_BASE               0x40000000

#endif
