/**
 * @file    MK64F12_Project_can_example.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
#include "fsl_flexcan.h"
#include "task.h"
#include "FreeRTOS.h"
#include "fsl_adc16.h"


/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_CAN            CAN0
#define EXAMPLE_CAN_CLK_SOURCE (kFLEXCAN_ClkSrc1)
#define EXAMPLE_CAN_CLK_FREQ   CLOCK_GetFreq(kCLOCK_BusClk)
#define RX_MESSAGE_BUFFER_NUM  (1)
#define TX_MESSAGE_BUFFER_NUM  (3)
#define DLC                    (8)
#define BatLvlTxID             (0x55)
#define KeepAliveTxID          (0x100)
#define FreqRptRxID            (0x25)
#define EnableRxID             (0x80)

/* The CAN clock prescaler = CAN source clock/(baud rate * quantum), and the prescaler must be an integer.
   The quantum default value is set to 10=(3+2+1)+4, because for most platforms the CAN clock frequency is
   a multiple of 10. e.g. 120M CAN source clock/(1M baud rate * 10) is an integer. If the CAN clock frequency
   is not a multiple of 10, users need to set SET_CAN_QUANTUM and define the PSEG1/PSEG2/PROPSEG (classical CAN)
   and FPSEG1/FPSEG2/FPROPSEG (CANFD) vaule. Or can set USE_IMPROVED_TIMING_CONFIG macro to use driver api to
   calculates the improved timing values. */

/* Fix MISRA_C-2012 Rule 17.7. */
#define LOG_INFO (void)PRINTF
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile bool txComplete = pdFALSE;
volatile bool rxComplete = pdFALSE;
flexcan_handle_t flexcanHandle;
flexcan_mb_transfer_t txBatLvlMb, rxFrecRpt, txKeepAliveMb, rxEnable;
flexcan_frame_t txBatLvlFrame, rxFrecRptFrame, txKeepAliveFrame, rxEnableFrame;
uint8_t RxMBID;
uint16_t g_period_ms = 1000;
uint8_t enable_node = 1;
#define DEMO_ADC16_BASE          ADC0
#define DEMO_ADC16_CHANNEL_GROUP 0U
#define DEMO_ADC16_USER_CHANNEL  12U
#define MAX_ADC_VALUE 4095U
#define MAX_PERCENTAGE 100U


/*******************************************************************************
 * Code
 ******************************************************************************/
uint16_t get_adc_value() {
    /* Using ADC polling example code */
    static int adc_init = 0;
    static adc16_config_t adc16ConfigStruct;
    static adc16_channel_config_t adc16ChannelConfigStruct;

    if (adc_init == 0) {
        ADC16_GetDefaultConfig(&adc16ConfigStruct);
        ADC16_Init(DEMO_ADC16_BASE, &adc16ConfigStruct);
        ADC16_EnableHardwareTrigger(DEMO_ADC16_BASE, false); /* Make sure the software trigger is used. */
        adc16ChannelConfigStruct.channelNumber                        = DEMO_ADC16_USER_CHANNEL;
        adc16ChannelConfigStruct.enableInterruptOnConversionCompleted = false;

        adc_init = 1;
    }

    ADC16_SetChannelConfig(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP, &adc16ChannelConfigStruct);
    while (0U == (kADC16_ChannelConversionDoneFlag &
                ADC16_GetChannelStatusFlags(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP)))
    {
    }
    uint16_t adc_value = ADC16_GetChannelConversionValue(DEMO_ADC16_BASE, DEMO_ADC16_CHANNEL_GROUP);
    // PRINTF("ADC Value: %d\r\n", adc_value);
    return adc_value;
}
/*!
 * @brief FlexCAN Call Back function
 */
static void flexcan_callback(CAN_Type *base, flexcan_handle_t *handle, status_t status, uint32_t result, void *userData)
{
    switch (status)
    {
        /* Process FlexCAN Rx event. */
        case kStatus_FLEXCAN_RxIdle:
            if (RX_MESSAGE_BUFFER_NUM == result)
            {
                RxMBID = RX_MESSAGE_BUFFER_NUM;
                rxComplete = pdTRUE;
            }
            break;

            /* Process FlexCAN Tx event. */
        case kStatus_FLEXCAN_TxIdle:
            if (TX_MESSAGE_BUFFER_NUM == result)
            {
                txComplete = pdTRUE;
            }
            break;

        default:
            break;
    }
}

void CAN_Init(void){

    flexcan_config_t flexcanConfig;
    flexcan_rx_mb_config_t mbConfig;
    flexcan_rx_mb_config_t mbConfigEnable;


    /* Init FlexCAN module. */
    /*
     * flexcanConfig.clkSrc                 = kFLEXCAN_ClkSrc0;
     * flexcanConfig.baudRate               = 1000000U;
     * flexcanConfig.baudRateFD             = 2000000U;
     * flexcanConfig.maxMbNum               = 16;
     * flexcanConfig.enableLoopBack         = false;
     * flexcanConfig.enableSelfWakeup       = false;
     * flexcanConfig.enableIndividMask      = false;
     * flexcanConfig.disableSelfReception   = false;
     * flexcanConfig.enableListenOnlyMode   = false;
     * flexcanConfig.enableDoze             = false;
     */
    FLEXCAN_GetDefaultConfig(&flexcanConfig);

#if defined(EXAMPLE_CAN_CLK_SOURCE)
    flexcanConfig.clkSrc = EXAMPLE_CAN_CLK_SOURCE;
#endif
    /*Change CAN BR to 125kbps*/
    flexcanConfig.baudRate = 125000U;
    FLEXCAN_Init(EXAMPLE_CAN, &flexcanConfig, EXAMPLE_CAN_CLK_FREQ);

    /* Setup Rx Message Buffer. */
    mbConfig.format = kFLEXCAN_FrameFormatStandard;
    mbConfig.type   = kFLEXCAN_FrameTypeData;
    mbConfig.id     = FLEXCAN_ID_STD(FreqRptRxID);
    FLEXCAN_SetRxMbConfig(EXAMPLE_CAN, RX_MESSAGE_BUFFER_NUM, &mbConfig, true);
    /* Start receive data through Rx Message Buffer. */
    rxFrecRpt.mbIdx = (uint8_t)RX_MESSAGE_BUFFER_NUM;
    rxFrecRpt.frame = &rxFrecRptFrame;

    mbConfigEnable.format = kFLEXCAN_FrameFormatStandard;
    mbConfigEnable.type   = kFLEXCAN_FrameTypeData;
    mbConfigEnable.id     = FLEXCAN_ID_STD(EnableRxID);
    FLEXCAN_SetRxMbConfig(EXAMPLE_CAN, RX_MESSAGE_BUFFER_NUM, &mbConfigEnable, true);
    /* Start receive data through Rx Message Buffer. */
    rxEnable.mbIdx = (uint8_t)RX_MESSAGE_BUFFER_NUM;
    rxEnable.frame = &rxEnableFrame;

    /* Setup Tx Message Buffer. */
    FLEXCAN_SetTxMbConfig(EXAMPLE_CAN, TX_MESSAGE_BUFFER_NUM, true);
    /* Prepare Tx Frame for sending. */
    txBatLvlFrame.format = (uint8_t)kFLEXCAN_FrameFormatStandard;
    txBatLvlFrame.type   = (uint8_t)kFLEXCAN_FrameTypeData;
    txBatLvlFrame.id     = FLEXCAN_ID_STD(BatLvlTxID);
    txBatLvlFrame.length = (uint8_t)DLC;

    txKeepAliveFrame.format = (uint8_t)kFLEXCAN_FrameFormatStandard;
    txKeepAliveFrame.type   = (uint8_t)kFLEXCAN_FrameTypeData;
    txKeepAliveFrame.id     = FLEXCAN_ID_STD(KeepAliveTxID);
    txKeepAliveFrame.length = (uint8_t)DLC;

    /* Create FlexCAN handle structure and set call back function. */
    FLEXCAN_TransferCreateHandle(EXAMPLE_CAN, &flexcanHandle, flexcan_callback, NULL);
}


void vTaskTxBatLvl(void * pvParameters)
{
    TickType_t xLastWakeTime;
    TickType_t xPeriod = pdMS_TO_TICKS(g_period_ms);
    xLastWakeTime = xTaskGetTickCount();

    /* Enter the loop that defines the task behavior. */
    for(;;){
        xPeriod = pdMS_TO_TICKS(g_period_ms);
        vTaskDelayUntil(&xLastWakeTime, xPeriod);

        uint16_t adc_value = get_adc_value();
        uint8_t adc_percent = adc_value/MAX_ADC_VALUE;

        uint8_t ascii[3];
        ascii[0] = (adc_percent%10) + 0x30;
        ascii[1] = ((uint16_t)adc_percent/10)%10 + 0x30;
        ascii[2] = ((uint16_t)adc_percent/100)%10 + 0x30;

        txBatLvlFrame.dataByte0 = ascii[0];
        txBatLvlFrame.dataByte1 = ascii[1];
        txBatLvlFrame.dataByte2 = ascii[2];

        /* Send data through Tx Message Buffer. */
        txBatLvlMb.mbIdx = (uint8_t)TX_MESSAGE_BUFFER_NUM;
        txBatLvlMb.frame = &txBatLvlFrame;
        (void)FLEXCAN_TransferSendNonBlocking(EXAMPLE_CAN, &flexcanHandle, &txBatLvlMb);
    }
}

void vTaskTxKeepAlive(void * pvParameters)
{
    TickType_t xLastWakeTime;
    static const TickType_t xPeriod = pdMS_TO_TICKS(1000);
    xLastWakeTime = xTaskGetTickCount();

    /* Enter the loop that defines the task behavior. */
    for(;;){
        vTaskDelayUntil(&xLastWakeTime, xPeriod);

        PRINTF("Going to tx\n");

        txKeepAliveFrame.dataByte0 = 0x1;
        txKeepAliveFrame.dataByte1 = 0x0;
        txKeepAliveFrame.dataByte2 = 0x0;

        txKeepAliveMb.mbIdx = (uint8_t)TX_MESSAGE_BUFFER_NUM;
        txKeepAliveMb.frame = &txKeepAliveFrame;
        (void)FLEXCAN_TransferSendNonBlocking(EXAMPLE_CAN, &flexcanHandle, &txKeepAliveMb);
    }
}

void vTaskRxFrecRpt(void * pvParameters)
{
    TickType_t xLastWakeTime;
    const TickType_t xPeriod = pdMS_TO_TICKS(5);
    xLastWakeTime = xTaskGetTickCount();

    /* Enter the loop that defines the task behavior. */
    for(;;){
        vTaskDelayUntil(&xLastWakeTime, xPeriod);

        /* Perform the periodic actions here. */
        (void)FLEXCAN_TransferReceiveNonBlocking(EXAMPLE_CAN, &flexcanHandle, &rxFrecRpt);
        if(rxComplete == pdTRUE){

            if (rxFrecRptFrame.dataByte0 == 1) {
                if (g_period_ms != 1000) {
                    PRINTF("New period is %d\n", rxFrecRptFrame.dataByte0);
                }
                g_period_ms = 1000;
            }
            else if (rxFrecRptFrame.dataByte0 == 2) {
                if (g_period_ms != 100) {
                    PRINTF("New period is %d\n", rxFrecRptFrame.dataByte0);
                }
                g_period_ms = 100;
            }
            else {
                if (g_period_ms != 50) {
                    PRINTF("New period is %d\n", rxFrecRptFrame.dataByte0);
                }
                g_period_ms = 50;
            }

            rxComplete = pdFALSE;
        }
    }
}

void vTaskRxEnable(void * pvParameters)
{
    TickType_t xLastWakeTime;
    const TickType_t xPeriod = pdMS_TO_TICKS(5);
    xLastWakeTime = xTaskGetTickCount();

    /* Enter the loop that defines the task behavior. */
    for(;;){
        vTaskDelayUntil(&xLastWakeTime, xPeriod);

        /* Perform the periodic actions here. */
        (void)FLEXCAN_TransferReceiveNonBlocking(EXAMPLE_CAN, &flexcanHandle, &rxEnable);
        if(rxComplete == pdTRUE){

            enable_node = rxEnableFrame.dataByte0;

            rxComplete = pdFALSE;
        }
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    /* Initialize board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_InitDebugConsole();

    CAN_Init();

    if(xTaskCreate(vTaskTxBatLvl,"TxFrame10ms",(configMINIMAL_STACK_SIZE+100),
                   NULL,(configMAX_PRIORITIES-2),NULL) != pdPASS) {
        PRINTF("FAIL to create vTaskTx10ms");
    }

    if(xTaskCreate(vTaskRxFrecRpt,"rxFrecRptFrame",(configMINIMAL_STACK_SIZE+100),
                   NULL,(configMAX_PRIORITIES-2),NULL) != pdPASS) {
        PRINTF("FAIL to create RxFrame5m");
    }

    if(xTaskCreate(vTaskTxKeepAlive,"vTaskTxKeepAlive",
                   (configMINIMAL_STACK_SIZE+100),NULL,(configMAX_PRIORITIES-2),
                   NULL) != pdPASS) {
        PRINTF("FAIL to create vTaskTxKeepAlive");
    }

    if(xTaskCreate(vTaskRxEnable,"rxEnable",(configMINIMAL_STACK_SIZE+100),NULL,
                   (configMAX_PRIORITIES-2),NULL) != pdPASS) {
        PRINTF("FAIL to create RxEnable");
    }

    /* Start the scheduler. */
    vTaskStartScheduler();

    while (pdTRUE){}
}
