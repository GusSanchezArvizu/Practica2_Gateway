/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v9.0
processor: MK64FN1M0xxx12
package_id: MK64FN1M0VLL12
mcu_data: ksdk2_0
processor_version: 9.0.0
board: FRDM-K64F
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '62', peripheral: UART0, signal: RX, pin_signal: PTB16/SPI1_SOUT/UART0_RX/FTM_CLKIN0/FB_AD17/EWM_IN}
  - {pin_num: '63', peripheral: UART0, signal: TX, pin_signal: PTB17/SPI1_SIN/UART0_TX/FTM_CLKIN1/FB_AD16/EWM_OUT_b}
  - {pin_num: '90', peripheral: ENET, signal: 'TMR_1588, 0', pin_signal: PTC16/UART3_RX/ENET0_1588_TMR0/FB_CS5_b/FB_TSIZ1/FB_BE23_16_BLS15_8_b}
  - {pin_num: '91', peripheral: ENET, signal: 'TMR_1588, 1', pin_signal: PTC17/UART3_TX/ENET0_1588_TMR1/FB_CS4_b/FB_TSIZ0/FB_BE31_24_BLS7_0_b}
  - {pin_num: '92', peripheral: ENET, signal: 'TMR_1588, 2', pin_signal: PTC18/UART3_RTS_b/ENET0_1588_TMR2/FB_TBST_b/FB_CS2_b/FB_BE15_8_BLS23_16_b}
  - {pin_num: '54', peripheral: ENET, signal: RMII_MDC, pin_signal: ADC0_SE9/ADC1_SE9/PTB1/I2C0_SDA/FTM1_CH1/RMII0_MDC/MII0_MDC/FTM1_QD_PHB}
  - {pin_num: '53', peripheral: ENET, signal: RMII_MDIO, pin_signal: ADC0_SE8/ADC1_SE8/PTB0/LLWU_P5/I2C0_SCL/FTM1_CH0/RMII0_MDIO/MII0_MDIO/FTM1_QD_PHA, slew_rate: fast,
    open_drain: enable, drive_strength: low, pull_select: up, pull_enable: enable, passive_filter: disable}
  - {pin_num: '42', peripheral: ENET, signal: RMII_RXD1, pin_signal: CMP2_IN0/PTA12/CAN0_TX/FTM1_CH0/RMII0_RXD1/MII0_RXD1/I2C2_SCL/I2S0_TXD0/FTM1_QD_PHA}
  - {pin_num: '43', peripheral: ENET, signal: RMII_RXD0, pin_signal: CMP2_IN1/PTA13/LLWU_P4/CAN0_RX/FTM1_CH1/RMII0_RXD0/MII0_RXD0/I2C2_SDA/I2S0_TX_FS/FTM1_QD_PHB}
  - {pin_num: '44', peripheral: ENET, signal: RMII_CRS_DV, pin_signal: PTA14/SPI0_PCS0/UART0_TX/RMII0_CRS_DV/MII0_RXDV/I2C2_SCL/I2S0_RX_BCLK/I2S0_TXD1}
  - {pin_num: '45', peripheral: ENET, signal: RMII_TXEN, pin_signal: PTA15/SPI0_SCK/UART0_RX/RMII0_TXEN/MII0_TXEN/I2S0_RXD0}
  - {pin_num: '47', peripheral: ENET, signal: RMII_TXD1, pin_signal: ADC1_SE17/PTA17/SPI0_SIN/UART0_RTS_b/RMII0_TXD1/MII0_TXD1/I2S0_MCLK}
  - {pin_num: '46', peripheral: ENET, signal: RMII_TXD0, pin_signal: PTA16/SPI0_SOUT/UART0_CTS_b/UART0_COL_b/RMII0_TXD0/MII0_TXD0/I2S0_RX_FS/I2S0_RXD1}
  - {pin_num: '39', peripheral: ENET, signal: RMII_RXER, pin_signal: PTA5/USB_CLKIN/FTM0_CH2/RMII0_RXER/MII0_RXER/CMP2_OUT/I2S0_TX_BCLK/JTAG_TRST_b}
  - {pin_num: '38', peripheral: GPIOA, signal: 'GPIO, 4', pin_signal: PTA4/LLWU_P3/FTM0_CH1/NMI_b/EZP_CS_b, slew_rate: fast, open_drain: disable, drive_strength: high,
    pull_select: up, pull_enable: enable, passive_filter: disable}
  - {pin_num: '68', peripheral: GPIOB, signal: 'GPIO, 22', pin_signal: PTB22/SPI2_SOUT/FB_AD29/CMP2_OUT}
  - {pin_num: '65', peripheral: CAN0, signal: RX, pin_signal: PTB19/CAN0_RX/FTM2_CH1/I2S0_TX_FS/FB_OE_b/FTM2_QD_PHB}
  - {pin_num: '64', peripheral: CAN0, signal: TX, pin_signal: PTB18/CAN0_TX/FTM2_CH0/I2S0_TX_BCLK/FB_AD15/FTM2_QD_PHA}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);

    /* PORTA12 (pin 42) is configured as RMII0_RXD1 */
    PORT_SetPinMux(BOARD_INITPINS_RMII0_RXD1_PORT, BOARD_INITPINS_RMII0_RXD1_PIN, kPORT_MuxAlt4);

    /* PORTA13 (pin 43) is configured as RMII0_RXD0 */
    PORT_SetPinMux(BOARD_INITPINS_RMII0_RXD0_PORT, BOARD_INITPINS_RMII0_RXD0_PIN, kPORT_MuxAlt4);

    /* PORTA14 (pin 44) is configured as RMII0_CRS_DV */
    PORT_SetPinMux(BOARD_INITPINS_RMII0_CRS_DV_PORT, BOARD_INITPINS_RMII0_CRS_DV_PIN, kPORT_MuxAlt4);

    /* PORTA15 (pin 45) is configured as RMII0_TXEN */
    PORT_SetPinMux(BOARD_INITPINS_RMII0_TXEN_PORT, BOARD_INITPINS_RMII0_TXEN_PIN, kPORT_MuxAlt4);

    /* PORTA16 (pin 46) is configured as RMII0_TXD0 */
    PORT_SetPinMux(BOARD_INITPINS_RMII0_TXD0_PORT, BOARD_INITPINS_RMII0_TXD0_PIN, kPORT_MuxAlt4);

    /* PORTA17 (pin 47) is configured as RMII0_TXD1 */
    PORT_SetPinMux(BOARD_INITPINS_RMII0_TXD1_PORT, BOARD_INITPINS_RMII0_TXD1_PIN, kPORT_MuxAlt4);

    const port_pin_config_t SW3 = {/* Internal pull-up resistor is enabled */
                                   kPORT_PullUp,
                                   /* Fast slew rate is configured */
                                   kPORT_FastSlewRate,
                                   /* Passive filter is disabled */
                                   kPORT_PassiveFilterDisable,
                                   /* Open drain is disabled */
                                   kPORT_OpenDrainDisable,
                                   /* High drive strength is configured */
                                   kPORT_HighDriveStrength,
                                   /* Pin is configured as PTA4 */
                                   kPORT_MuxAsGpio,
                                   /* Pin Control Register fields [15:0] are not locked */
                                   kPORT_UnlockRegister};
    /* PORTA4 (pin 38) is configured as PTA4 */
    PORT_SetPinConfig(BOARD_INITPINS_SW3_PORT, BOARD_INITPINS_SW3_PIN, &SW3);

    /* PORTA5 (pin 39) is configured as RMII0_RXER */
    PORT_SetPinMux(BOARD_INITPINS_RMII0_RXER_PORT, BOARD_INITPINS_RMII0_RXER_PIN, kPORT_MuxAlt4);

    const port_pin_config_t RMII0_MDIO = {/* Internal pull-up resistor is enabled */
                                          kPORT_PullUp,
                                          /* Fast slew rate is configured */
                                          kPORT_FastSlewRate,
                                          /* Passive filter is disabled */
                                          kPORT_PassiveFilterDisable,
                                          /* Open drain is enabled */
                                          kPORT_OpenDrainEnable,
                                          /* Low drive strength is configured */
                                          kPORT_LowDriveStrength,
                                          /* Pin is configured as RMII0_MDIO */
                                          kPORT_MuxAlt4,
                                          /* Pin Control Register fields [15:0] are not locked */
                                          kPORT_UnlockRegister};
    /* PORTB0 (pin 53) is configured as RMII0_MDIO */
    PORT_SetPinConfig(BOARD_INITPINS_RMII0_MDIO_PORT, BOARD_INITPINS_RMII0_MDIO_PIN, &RMII0_MDIO);

    /* PORTB1 (pin 54) is configured as RMII0_MDC */
    PORT_SetPinMux(BOARD_INITPINS_RMII0_MDC_PORT, BOARD_INITPINS_RMII0_MDC_PIN, kPORT_MuxAlt4);

    /* PORTB16 (pin 62) is configured as UART0_RX */
    PORT_SetPinMux(BOARD_INITPINS_DEBUG_UART_RX_PORT, BOARD_INITPINS_DEBUG_UART_RX_PIN, kPORT_MuxAlt3);

    /* PORTB17 (pin 63) is configured as UART0_TX */
    PORT_SetPinMux(BOARD_INITPINS_DEBUG_UART_TX_PORT, BOARD_INITPINS_DEBUG_UART_TX_PIN, kPORT_MuxAlt3);

    /* PORTB18 (pin 64) is configured as CAN0_TX */
    PORT_SetPinMux(PORTB, 18U, kPORT_MuxAlt2);

    /* PORTB19 (pin 65) is configured as CAN0_RX */
    PORT_SetPinMux(PORTB, 19U, kPORT_MuxAlt2);

    /* PORTB22 (pin 68) is configured as PTB22 */
    PORT_SetPinMux(BOARD_INITPINS_LED_RED_PORT, BOARD_INITPINS_LED_RED_PIN, kPORT_MuxAsGpio);

    /* PORTC16 (pin 90) is configured as ENET0_1588_TMR0 */
    PORT_SetPinMux(BOARD_INITPINS_TMR_1588_0_PORT, BOARD_INITPINS_TMR_1588_0_PIN, kPORT_MuxAlt4);

    /* PORTC17 (pin 91) is configured as ENET0_1588_TMR1 */
    PORT_SetPinMux(BOARD_INITPINS_TMR_1588_1_PORT, BOARD_INITPINS_TMR_1588_1_PIN, kPORT_MuxAlt4);

    /* PORTC18 (pin 92) is configured as ENET0_1588_TMR2 */
    PORT_SetPinMux(PORTC, 18U, kPORT_MuxAlt4);

    SIM->SOPT5 = ((SIM->SOPT5 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT5_UART0TXSRC_MASK)))

                  /* UART 0 transmit data source select: UART0_TX pin. */
                  | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX));
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
