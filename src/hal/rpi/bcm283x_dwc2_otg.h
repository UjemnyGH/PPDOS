#ifndef _PPDOS_HAL_BCM283X_DWC2_OTG_
#define _PPDOS_HAL_BCM283X_DWC2_OTG_

#include "bcm283x_regs.h"

typedef struct rpi_hal_dwc2_core_s {
  rpi_hal_io32_t control;
  rpi_hal_io32_t interrupt;
  
  rpi_hal_io32_t ahbCfg;
  rpi_hal_io32_t usbCfg;

  rpi_hal_io32_t resetCtl;
  rpi_hal_io32_t intStat;
  rpi_hal_io32_t intMask;
  
  rpi_hal_io32_t receiveStatRead;
  rpi_hal_io32_t receiveStatPop;

  rpi_hal_io32_t rxFIFOSize;
  rpi_hal_io32_t txFIFOSize;
  rpi_hal_io32_t txFIFOStat;

  rpi_hal_io32_t i2cCtl;
  rpi_hal_io32_t vendorCtl;
  rpi_hal_io32_t genPurpIO; /* 0x4F54280A */
  rpi_hal_io32_t userId;
  rpi_hal_io32_t synopsysId;

  rpi_hal_io32_t hardwareCfg[4];

  rpi_hal_io32_t linkPowerCfg;
  rpi_hal_io32_t powerDown;

  rpi_hal_io32_t dataFIFOCfg;
  rpi_hal_io32_t attachDetectProtCtl;

  rpi_hal_uint32_t RESERVED0[39];

  rpi_hal_io32_t hostTxFIFOSize;
} __attribute__((packed)) rpi_hal_dwc2_core_t;

enum rpi_hal_dwc2_core_ahbCfg {
  dwc2Core_ahbCfg_enableInt         = 0x01,
  dwc2Core_ahbCfg_maxAxiBurstMask   = 0x06,
  dwc2Core_ahbCfg_waitAxiWrites     = 0x08,
  dwc2Core_ahbCfg_enableDMA         = 0x10

  /* There can be more, tho this is currently only to setup HID, later I would add everything */
};

enum rpi_hal_dwc2_core_usbCfg {
  dwc2Core_usbCfg_16BitPhysicalInterface          = 0x00000008,
  dwc2Core_usbCfg_usbInterfaceSelect              = 0x00000010,
  dwc2Core_usbCfg_secureRemoteParingCapable       = 0x00000100,
  dwc2Core_usbCfg_hostNegotiationProtocolCapable  = 0x00000200,
  dwc2Core_usbCfg_usbLowPinInterefaceFullSpeed    = 0x00020000,
  dwc2Core_usbCfg_usbLowPinInterfaceClockSuspend  = 0x00080000,
  dwc2Core_usbCfg_usbLowPinInterfaceVbusDriveExt  = 0x00100000,
  dwc2Core_usbCfg_termSelectDataLinePulse         = 0x00400000
};

enum rpi_hal_dwc2_core_resetCtl {
  dwc2Core_resetCtl_softReset = 0x00000001,
  dwc2Core_resetCtl_txFlush   = 0x00000010,
  dwc2Core_resetCtl_rxFlush   = 0x00000020,
  dwc2Core_resetCtl_idle      = 0x80000000
};

enum rpi_hal_dwc2_core_intStat {
  dwc2Core_intStat_hostModeEnable                 = 0x00000001,
  dwc2Core_intStat_modeMismatch                   = 0x00000002,
  dwc2Core_intStat_otgInt                         = 0x00000004,
  dwc2Core_intStat_startOfFrame                   = 0x00000008,
  dwc2Core_intStat_rxFIFONonEmpty                 = 0x00000010,
  dwc2Core_intStat_txFIFOEmpty                    = 0x00000020,
  dwc2Core_intStat_globalINNAKHandshakeSuccess    = 0x00000040,
  dwc2Core_intStat_globalOUTNAKHandshakeSuccess   = 0x00000080,
  dwc2Core_intStat_usbLowPinInterfaceClockInt     = 0x00000100,
  dwc2Core_intStat_i2cInt                         = 0x00000200,
  dwc2Core_intStat_earlySuspendInt                = 0x00000400,
  dwc2Core_intStat_usbSuspend                     = 0x00000800,
  dwc2Core_intStat_usbResetDetected               = 0x00001000,
  dwc2Core_intStat_enumerationComplete            = 0x00002000,
  dwc2Core_intStat_incompleteOUTPacketDropped     = 0x00004000,
  dwc2Core_intStat_endOfFrame                     = 0x00008000,
  dwc2Core_intStat_restoreDone                    = 0x00010000,
  dwc2Core_intStat_endpointMismatch               = 0x00020000,
  dwc2Core_intStat_inEndpointInt                  = 0x00040000,
  dwc2Core_intStat_outEndpointInt                 = 0x00080000,
  dwc2Core_intStat_incompleteINTransfer           = 0x00100000,
  dwc2Core_intStat_incompleteTransfer             = 0x00200000,
  dwc2Core_intStat_forcedSuspend                  = 0x00400000,
  dwc2Core_intStat_resetDetectedOnUSBBus          = 0x00800000,
  dwc2Core_intStat_portInt                        = 0x01000000,
  dwc2Core_intStat_hostChannelInt                 = 0x02000000,
  dwc2Core_intStat_periodicTxFIFOEmpty            = 0x04000000,
  dwc2Core_intStat_lowPowerModeTransactionReceive = 0x08000000,
  dwc2Core_intStat_connectorIdStatusChange        = 0x10000000,
  dwc2Core_intStat_usbDeviceDisconnected          = 0x20000000,
  dwc2Core_intStat_sessionRequestReceived         = 0x40000000,
  dwc2Core_intStat_remoteWakeupDetected           = 0x80000000
};

typedef struct rpi_hal_dwc2_host_s {
  rpi_hal_io32_t config;
  rpi_hal_io32_t frameInterval;
  rpi_hal_io32_t frameTime;
  rpi_hal_uint32_t RESERVED0;
  rpi_hal_io32_t txFIFOStat;
  rpi_hal_io32_t allChannelsInt;
  rpi_hal_io32_t allChannelsIntMask;
  rpi_hal_io32_t frameListBaseAddr;
  
  rpi_hal_uint32_t RESERVED1[8];

  rpi_hal_io32_t portCtlStat;

  rpi_hal_uint32_t RESERVED2[47];

  struct {
    rpi_hal_io32_t character;
    rpi_hal_io32_t splitCtl;
    rpi_hal_io32_t interrupt;
    rpi_hal_io32_t intMask;
    rpi_hal_io32_t transferSize;
    rpi_hal_io32_t dmaAddr;
    rpi_hal_uint32_t RESERVED3;
    rpi_hal_io32_t dmaBufferAddr;
  } channel[16];
} __attribute__((packed)) rpi_hal_dwc2_host_t;

enum rpi_hal_dwc2_host_config {
  dwc2Host_config_clock30_60MHz = 0x0,
  dwc2Host_config_clock48MHz    = 0x1,
  dwc2Host_config_clock6MHz     = 0x2,
  dwc2Host_config_clockMask     = 0x3,
};

enum rpi_hal_dwc2_host_portCtlStat {
  dwc2Host_portCtlStat_connect            = 0x0001,
  dwc2Host_portCtlStat_connectChanged     = 0x0002,
  dwc2Host_portCtlStat_enable             = 0x0004,
  dwc2Host_portCtlStat_enableChanged      = 0x0008,
  dwc2Host_portCtlStat_overcurrent        = 0x0010,
  dwc2Host_portCtlStat_overcurrentChanged = 0x0020,
  dwc2Host_portCtlStat_reset              = 0x0100,
  dwc2Host_portCtlStat_power              = 0x1000
};

enum rpi_hal_dwc2_host_channel_character {
  dwc2Host_channel_character_maxPacketSizeMask    = 0x000007FF,
  dwc2Host_channel_character_endpointNumberMask   = 0x00007800,
  
  dwc2Host_channel_character_endpointDirectionIn  = 0x00008000,
  dwc2Host_channel_character_lowSpeedDevice       = 0x00020000,
  
  dwc2Host_channel_character_endpointTypeMask     = 0x000C0000,
  dwc2Host_channel_character_multicountMask       = 0x00300000,
  dwc2Host_channel_character_deviceAddressMask    = 0x1FC00000,
  dwc2Host_channel_character_oddFrame             = 0x20000000,
  dwc2Host_channel_character_channelDisable       = 0x40000000,
  dwc2Host_channel_character_channelEnable        = 0x80000000,

  dwc2Host_channel_character_endpointNumberShift  = 11,
  dwc2Host_channel_character_endpointTypeShift    = 18,
  dwc2Host_channel_character_multicountShift      = 20,
  dwc2Host_channel_character_deviceAddressShift   = 22
};

enum rpi_hal_dwc2_host_channel_interrupt {
  dwc2Host_channel_interrupt_transferComplete           = 0x0001,
  dwc2Host_channel_interrupt_channelHalted              = 0x0002,
  dwc2Host_channel_interrupt_ahbError                   = 0x0004,
  dwc2Host_channel_interrupt_stall                      = 0x0008,
  dwc2Host_channel_interrupt_NAKReceived                = 0x0010,
  dwc2Host_channel_interrupt_ACKReceived                = 0x0020,
  dwc2Host_channel_interrupt_notReadyYet                = 0x0040,
  dwc2Host_channel_interrupt_transactionError           = 0x0080,
  dwc2Host_channel_interrupt_babbleError                = 0x0100,
  dwc2Host_channel_interrupt_frameOverrun               = 0x0200,
  dwc2Host_channel_interrupt_dataToggleError            = 0x0400,
  dwc2Host_channel_interrupt_bufferNotAvailable         = 0x0800,
  dwc2Host_channel_interrupt_excessiveTransactionErrors = 0x1000,
  dwc2Host_channel_interrupt_frameListRollover          = 0x2000,
};

typedef struct rpi_hal_dwc2_device_s {
  rpi_hal_io32_t config;
  rpi_hal_io32_t devControl;
  rpi_hal_io32_t status;
  
  rpi_hal_uint32_t RESERVED0;

  rpi_hal_io32_t inEndpointCommonInt;
  rpi_hal_io32_t outEndpointCommonInt;
  rpi_hal_io32_t allEndpointInt;
  rpi_hal_io32_t allEndpointIntMask;

  rpi_hal_io32_t tokenQueueRead1;
  rpi_hal_io32_t tokenQueueRead2;
  rpi_hal_io32_t vbusDischargeTime;
  rpi_hal_io32_t vbusPulsingTime;
  rpi_hal_io32_t tokenQueueRead3;
  rpi_hal_io32_t tokenQueueRead4;

  rpi_hal_uint32_t RESERVED1[50];

  struct {
    rpi_hal_io32_t control;
    rpi_hal_uint32_t RESERVED2;
    rpi_hal_io32_t interrupt;
    rpi_hal_uint32_t RESERVED3;
    rpi_hal_io32_t transferSize;
    rpi_hal_io32_t dmaAddr;
    rpi_hal_io32_t txFIFOStat;
    rpi_hal_uint32_t RESERVED4;
  } inEndpoint[16];

  struct {
    rpi_hal_io32_t control;
    rpi_hal_uint32_t RESERVED5;
    rpi_hal_io32_t interrupt;
    rpi_hal_uint32_t RESERVED6;
    rpi_hal_io32_t transferSize;
    rpi_hal_io32_t dmaAddr;
    rpi_hal_uint32_t RESERVED7[2];
  } outEndpoint[16]; 
} __attribute__((packed)) rpi_hal_dwc2_device_t;

typedef struct rpi_hal_dwc2_power_s {
  rpi_hal_io32_t ctlLegacy;
  rpi_hal_io32_t ctlModern;
} __attribute__((packed)) rpi_hal_dwc2_power_t;

#define dwc2Core      (*(rpi_hal_dwc2_core_t*)RPI_HAL_USB_CORE_BASE)
#define dwc2Host      (*(rpi_hal_dwc2_host_t*)RPI_HAL_USB_HOST_BASE)
#define dwc2Device    (*(rpi_hal_dwc2_device_t*)RPI_HAL_USB_DEVICE_BASE)
#define dwc2Power     (*(rpi_hal_dwc2_power_t*)(RPI_HAL_USB_BASE + 0xE00))

#define dwc2FIFORam(channel_endpoint)   (*(rpi_hal_io32_t*)(RPI_HAL_USB_BASE + 0x1000 + (0x1000 * channel_endpoint)))

void rpi_hal_dwc2_core_config(); 

void rpi_hal_dwc2_core_disableIntMask();

void rpi_hal_dwc2_core_setIntMask(const enum rpi_hal_dwc2_core_intStat mask);

void rpi_hal_dwc2_core_flush(const rpi_hal_uint32_t channel, int tx, int rx);

void rpi_hal_dwc2_core_reset();

rpi_hal_uint32_t rpi_hal_dwc2_core_getHighSpeedPhysicalDeviceType();

rpi_hal_uint32_t rpi_hal_dwc2_core_getFullSpeedPhysicalDeviceType();

void rpi_hal_dwc2_core_init(); 

#endif
