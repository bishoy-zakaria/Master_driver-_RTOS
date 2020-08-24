/*
 * SPI.c
 *
 * Created: 8/16/2020 11:38:37 PM
 *  Author: 20112
 */ 

#include "SPI.h"

void SPI_Master_Init(void)
{
	CLR_BIT(SPCR,7);
	SET_BIT(SPCR,6);
	SET_BIT(SPCR,5);
	SET_BIT(SPCR,4);
	CLR_BIT(SPCR,3);
	CLR_BIT(SPCR,2);
	
	DIO_SetPinDir(DIO_PORTB,DIO_PIN4,DIO_PIN_OUTPUT);
	DIO_SetPinDir(DIO_PORTB,DIO_PIN5,DIO_PIN_OUTPUT);
	DIO_SetPinDir(DIO_PORTB,DIO_PIN6,DIO_PIN_INPUT);
	DIO_SetPinDir(DIO_PORTB,DIO_PIN7,DIO_PIN_OUTPUT);
}

void SPI_Slave_Init(void)
{
	CLR_BIT(SPCR,7);
	SET_BIT(SPCR,6);
	SET_BIT(SPCR,5);
	CLR_BIT(SPCR,4);
	CLR_BIT(SPCR,3);
	CLR_BIT(SPCR,2);
	
	DIO_SetPinDir(DIO_PORTB,DIO_PIN4,DIO_PIN_INPUT);
	DIO_SetPinDir(DIO_PORTB,DIO_PIN5,DIO_PIN_INPUT);
	DIO_SetPinDir(DIO_PORTB,DIO_PIN6,DIO_PIN_OUTPUT);
	DIO_SetPinDir(DIO_PORTB,DIO_PIN7,DIO_PIN_INPUT);
}

void SPI_Start(void)
{  // ********* F/4 *********** 
	CLR_BIT(SPCR,1);
	CLR_BIT(SPCR,0);
	SET_BIT(SPSR,0);
}

void SPI_Send_Byte(uint8 Byte)
{
	SPDR=Byte;
	while ( (GET_BIT(SPSR,7)) != 1 );
	
}
uint8 SPI_Recieve_Byte(void)
{
	uint8 data=0;
	while ( (GET_BIT(SPSR,7)) != 1 );
	data=SPDR;
	return data;
}

void SPI_Send_String(uint8*);
uint8 SPI_Recieve_String(void);
