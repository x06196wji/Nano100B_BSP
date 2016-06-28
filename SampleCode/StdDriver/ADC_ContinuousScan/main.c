/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * $Revision: 10 $
 * $Date: 15/06/16 7:22p $
 * @brief    Convert ADC channel 0, 1, 2 in Continuous Scan mode and print conversion results.
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "Nano100Series.h"

volatile uint8_t u8ADF;

void ADC_IRQHandler(void);

void ADC_IRQHandler(void)
{
    uint32_t u32Flag;

    // Get ADC conversion finish interrupt flag
    u32Flag = ADC_GET_INT_FLAG(ADC, ADC_ADF_INT);

    if(u32Flag & ADC_ADF_INT) {
        uint32_t u32Result;

        u32Result = ADC_GET_CONVERSION_DATA(ADC, 0);
        printf("Channel 0 conversion result is 0x%x\n",u32Result);
        u32Result = ADC_GET_CONVERSION_DATA(ADC, 1);
        printf("Channel 1 conversion result is 0x%x\n",u32Result);
        u32Result = ADC_GET_CONVERSION_DATA(ADC, 2);
        printf("Channel 2 conversion result is 0x%x\n",u32Result);
    }

    ADC_CLR_INT_FLAG(ADC, u32Flag);
}

/*---------------------------------------------------------------------------------------------------------*/
/* Init System Clock                                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set HCLK source form HXT and HCLK source divide 1  */
    CLK_SetHCLK(CLK_CLKSEL0_HCLK_S_HXT,CLK_HCLK_CLK_DIVIDER(1));

    /* Enable external 12MHz HXT, 32KHz LXT and HIRC */
    CLK_EnableXtalRC(CLK_PWRCTL_HXT_EN_Msk | CLK_PWRCTL_LXT_EN_Msk | CLK_PWRCTL_HIRC_EN_Msk);

    /* Waiting for clock ready */
    CLK_WaitClockReady(CLK_CLKSTATUS_HXT_STB_Msk | CLK_CLKSTATUS_LXT_STB_Msk | CLK_CLKSTATUS_HIRC_STB_Msk);

    /*  Set HCLK frequency 42MHz */
    CLK_SetCoreClock(42000000);

    /* Enable IP clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Enable ADC clock */
    CLK_EnableModuleClock(ADC_MODULE);

    /* Select IP clock source */
    CLK_SetModuleClock(UART0_MODULE,CLK_CLKSEL1_UART_S_HXT,CLK_UART_CLK_DIVIDER(1));

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Set PA multi-function pins for UART0 RXD and TXD */
    SYS->PB_L_MFP &= ~( SYS_PB_L_MFP_PB0_MFP_Msk | SYS_PB_L_MFP_PB1_MFP_Msk);
    SYS->PB_L_MFP |= (SYS_PB_L_MFP_PB0_MFP_UART0_RX | SYS_PB_L_MFP_PB1_MFP_UART0_TX );

    /* Set PB multi-function pins for Clock Output */
    SYS->PB_H_MFP = ( SYS->PB_H_MFP & ~SYS_PB_H_MFP_PB12_MFP_Msk ) |  SYS_PB_H_MFP_PB12_MFP_CKO;

    /* Set PA multi-function pins for ADC */
    SYS->PA_L_MFP &= ~(SYS_PA_L_MFP_PA0_MFP_Msk | SYS_PA_L_MFP_PA1_MFP_Msk | SYS_PA_L_MFP_PA2_MFP_Msk);
    SYS->PA_L_MFP |= SYS_PA_L_MFP_PA0_MFP_ADC_CH0 | SYS_PA_L_MFP_PA1_MFP_ADC_CH1 | SYS_PA_L_MFP_PA2_MFP_ADC_CH2;

    /* Disable PA.0 PA.1 PA.2 digital input path */
    PA->OFFD |= (((1<<0)|(1<<1)|(1<<2)) << GP_OFFD_OFFD_Pos);

    /* Lock protected registers */
    SYS_LockReg();
}

void UART0_Init()
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    UART_Open(UART0, 115200);
}

int32_t main (void)
{
    /* Init System, IP clock and multi-function I/O
       In the end of SYS_Init() will issue SYS_LockReg()
       to lock protected register. If user want to write
       protected register, please issue SYS_UnlockReg()
       to unlock protected register if necessary */
    SYS_Init();

    /* Init UART0 for printf */
    UART0_Init();

    printf("\nThis sample code demonstrate ADC continuous scan conversion\n");
    printf("It convert channel 0,1,2 continuously and print conversion result\n");

    // Enable channel 0,1,2
    ADC_Open(ADC, ADC_INPUT_MODE_SINGLE_END, ADC_OPERATION_MODE_CONTINUOUS, (ADC_CH_0_MASK | ADC_CH_1_MASK | ADC_CH_2_MASK));

    // Set reference voltage to AVDD
    ADC_SET_REF_VOLTAGE(ADC, ADC_REFSEL_POWER);

    // Power on ADC
    ADC_POWER_ON(ADC);

    // Enable ADC ADC_IF interrupt
    ADC_EnableInt(ADC, ADC_ADF_INT);
    NVIC_EnableIRQ(ADC_IRQn);

    ADC_START_CONV(ADC);

    while(1);
}

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/


