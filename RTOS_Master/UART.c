/*
 * UART.c
 *
 * Created: 7/31/2020 12:57:02 PM
 *  Author: 20112
 */ 

#include "UART.h"
#include "LCD.h"
#include <avr/interrupt.h>

void (*UART_ptr)(uint8);

volatile uint8* TX_ptr=0;
volatile uint8* RX_ptr=0;

volatile uint8 RX_arr[12];

void UART_Init(void)
{
	/* **************************** INIT ********************* */
	UDR=0X0000;
	
	SET_BIT(UCSRC,7);
	CLR_BIT(UCSRC,6);
	CLR_BIT(UCSRC,5);
	CLR_BIT(UCSRC,4);
	CLR_BIT(UCSRC,3);
	SET_BIT(UCSRC,2);
	SET_BIT(UCSRC,1);
	
	/* ***************************** INTERRUPT **************** */
	
	CLR_BIT(UCSRB,5);
	CLR_BIT(UCSRB,7);
	//SET_BIT(SREG,7);
	
	SET_BIT(UCSRB,3);
	SET_BIT(UCSRB,4);
	
	DIO_SetPinDir(DIO_PORTD,DIO_PIN1,DIO_PIN_OUTPUT);
	DIO_SetPinDir(DIO_PORTD,DIO_PIN0,DIO_PIN_INPUT);
}

void UART_Start(void)
{
	UBRR= 103;
}

void TX_Byte(uint8 BYTE)
{
	// *TX_ptr = BYTE;
	while(GET_BIT(UCSRA,5) == 0);
	UDR=BYTE;
	
}

void TX_String(uint8* ptr)
{
	uint8 TX_counter=0;
	while (ptr[TX_counter] != '\0')
	{
		
		TX_Byte(ptr[TX_counter]);
        TX_counter++;
	}
}

uint8 RX_Byte(void)
{
	while(GET_BIT(UCSRA,7) == 0);
	return UDR;
	//return *RX_ptr;
}
void RX_Integer(uint8*);

uint8 RX_String(void)
{
	uint8 RX_counter=0;
	    while (RX_Byte() != '\0')	
		{
			RX_arr[RX_counter]=RX_Byte();
			RX_counter++;
		}
		
	return & RX_arr ;
}


void UART_call_back_func(void(*ptr)(uint8))
{
	UART_ptr=ptr;
}

ISR(USART_UDRE_vect)
{
	TX_ptr=&UDR;
}
	
ISR(USART_RXC_vect)
{
	RX_ptr=&UDR;
	(*UART_ptr)(RX_Byte());
	
}