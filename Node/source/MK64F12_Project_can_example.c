/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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


/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_CAN            CAN0
#define EXAMPLE_CAN_CLK_SOURCE (kFLEXCAN_ClkSrc1)
#define EXAMPLE_CAN_CLK_FREQ   CLOCK_GetFreq(kCLOCK_BusClk)
#define RX_MESSAGE_BUFFER_NUM  (9)
#define TX_MESSAGE_BUFFER_NUM  (8)
#define DLC                    (8)
#define MSG1TxID               (0x124)
#define MSG1RxID               (0x123)

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
flexcan_mb_transfer_t txXfer, rxXfer;
flexcan_frame_t txFrame, rxFrame;
uint8_t RxMBID;


/*******************************************************************************
 * Code
 ******************************************************************************/
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
    mbConfig.id     = FLEXCAN_ID_STD(MSG1RxID);
    FLEXCAN_SetRxMbConfig(EXAMPLE_CAN, RX_MESSAGE_BUFFER_NUM, &mbConfig, true);
    /* Start receive data through Rx Message Buffer. */
    rxXfer.mbIdx = (uint8_t)RX_MESSAGE_BUFFER_NUM;
    rxXfer.frame = &rxFrame;

    /* Setup Tx Message Buffer. */
    FLEXCAN_SetTxMbConfig(EXAMPLE_CAN, TX_MESSAGE_BUFFER_NUM, true);
    /* Prepare Tx Frame for sending. */
    txFrame.format = (uint8_t)kFLEXCAN_FrameFormatStandard;
    txFrame.type   = (uint8_t)kFLEXCAN_FrameTypeData;
    txFrame.id     = FLEXCAN_ID_STD(MSG1TxID);
    txFrame.length = (uint8_t)DLC;


    /* Create FlexCAN handle structure and set call back function. */
    FLEXCAN_TransferCreateHandle(EXAMPLE_CAN, &flexcanHandle, flexcan_callback, NULL);
}


void vTaskTx10ms(void * pvParameters)
{
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS(10);
	xLastWakeTime = xTaskGetTickCount();
	static uint8_t TxByte0 = 0;
	static uint16_t TicksCounter = 0;

	 /* Enter the loop that defines the task behavior. */
	 for(;;){
		 vTaskDelayUntil(&xLastWakeTime, xPeriod);

		/*Increment a random value for demo*/
		 TicksCounter++;
		 if(TicksCounter > 300){
			 if(TxByte0 < 100){
				 TxByte0 += 5;
			 }else{
				 TxByte0 = 0;
			 }
			 TicksCounter = 0;
		 }else{}

		 /* Perform the periodic actions here. */
		 txFrame.dataByte0 = TxByte0; txFrame.dataByte1 = 0x019; txFrame.dataByte2 = 0x02;
		 txFrame.dataByte3 = 0x04; txFrame.dataByte4 = 0x04; txFrame.dataByte5 = 0x05;
		 txFrame.dataByte6 = 0x06; txFrame.dataByte7 = 0x07;

		/* Send data through Tx Message Buffer. */
		txXfer.mbIdx = (uint8_t)TX_MESSAGE_BUFFER_NUM;
		txXfer.frame = &txFrame;
		(void)FLEXCAN_TransferSendNonBlocking(EXAMPLE_CAN, &flexcanHandle, &txXfer);
	 }
}


void vTaskRx5ms(void * pvParameters)
{
	TickType_t xLastWakeTime;
	const TickType_t xPeriod = pdMS_TO_TICKS(5);
	xLastWakeTime = xTaskGetTickCount();

	 /* Enter the loop that defines the task behavior. */
	 for(;;){
		 vTaskDelayUntil(&xLastWakeTime, xPeriod);

		 /* Perform the periodic actions here. */
		 (void)FLEXCAN_TransferReceiveNonBlocking(EXAMPLE_CAN, &flexcanHandle, &rxXfer);
		 if(rxComplete == pdTRUE){
			 PRINTF("Message received from MB: %d, ID: 0x%x, data: %x,%x,%x,%x,%x,%x,%x,%x\n",
					 RxMBID, (rxFrame.id>>CAN_ID_STD_SHIFT), rxFrame.dataByte0, rxFrame.dataByte1,
					 rxFrame.dataByte2, rxFrame.dataByte3, rxFrame.dataByte4, rxFrame.dataByte5,
					 rxFrame.dataByte6, rxFrame.dataByte7);

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

    if(xTaskCreate(vTaskTx10ms,"TxFrame10ms",(configMINIMAL_STACK_SIZE+100),NULL,(configMAX_PRIORITIES-1),NULL) != pdPASS){
    	PRINTF("FAIL to create vTaskTx10ms");
    }

    if(xTaskCreate(vTaskRx5ms,"RxFrame5m",(configMINIMAL_STACK_SIZE+100),NULL,(configMAX_PRIORITIES-2),NULL) != pdPASS){
		PRINTF("FAIL to create RxFrame5m");
	}

    /* Start the scheduler. */
     vTaskStartScheduler();

    while (pdTRUE){}
}







