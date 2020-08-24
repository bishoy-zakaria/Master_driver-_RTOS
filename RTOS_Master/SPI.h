/*
 * SPI.h
 *
 * Created: 8/16/2020 11:38:22 PM
 *  Author: 20112
 */ 


#ifndef SPI_H_
#define SPI_H_
#include "ATMEGA32_Regs.h"
#include "BIT_Math.h"
#include "STD.h"
#include "DIO.h"

void SPI_Master_Init(void);
void SPI_Slave_Init(void);
void SPI_Start(void);

void SPI_Send_Byte(uint8);
uint8 SPI_Recieve_Byte(void);

void SPI_Send_String(uint8*);
uint8 SPI_Recieve_String(void);



#endif /* SPI_H_ */