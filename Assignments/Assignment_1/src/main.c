/**************************************************************************/
//Name:  main.c																														//
//Purpose:  Skeleton project with configuration for ADC, DAC, MCG and PIT	//
//Author:  Ethan Hettwer																									//
//Revision:  1.0 15Sept2014 EH Initial Revision														//
//Target:  Freescale K22f																									//
/**************************************************************************/

#include "MK22F51212.h"                 				//Device header
#include "MCG.h"																//Clock header
#include "TimerInt.h"														//Timer Interrupt Header
#include "ADC.h"																//ADC Header
#include "DAC.h"																//DAC Header
#include "uart.h"   

uint16_t adc_measurement;

void PIT0_IRQHandler(void){	//This function is called when the timer interrupt expires
	//Place Interrupt Service Routine Here
	NVIC_ClearPendingIRQ(PIT0_IRQn);							//Clears interrupt flag in NVIC Register
	PIT->CHANNEL[0].TFLG	= PIT_TFLG_TIF_MASK;		//Clears interrupt flag in PIT Register													
}
int main(void){
    MCG_Clock120_Init();
    ADC_Init();
    ADC_Calibrate();
    DAC_Init();
    TimerInt_Init();
    
    UART0_Init();

    UART0_Print("Hello world");

    // Enable clock to PORTE
    SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
    
    // Set PTE1 as GPIO (MUX = 1)
    PORTA->PCR[1] = PORT_PCR_MUX(1);
    
    // Set PTE26 as output
    GPIOA->PDDR |= (1 << 1);
    
    while(1){
        // Toggle LED
        GPIOA->PTOR = (1 << 1);

        // Delay
        for(volatile int i = 0; i < 1000000; i++);
    }
}
