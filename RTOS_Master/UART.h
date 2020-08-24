/*
 * UART.h
 *
 * Created: 7/31/2020 12:56:05 PM
 *  Author: 20112
 */ 


#ifndef UART_H_
#define UART_H_

#include "ATMEGA32_Regs.h"
#include "STD.h"
#include "BIT_Math.h"
#include "DIO.h"

void UART_Init(void);

void UART_Start(void);

void TX_Byte(uint8 BYTE);
void TX_String(uint8* ptr);

uint8 RX_Byte(void);
void RX_Integer(uint8*);
uint8 RX_String(void);

void UART_call_back_func(void(*ptr)(uint8));


#endif /* UART_H_ */