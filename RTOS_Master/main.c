/*
 * RTOS_Master.c
 *
 * Created: 8/23/2020 6:57:22 PM
 * Author : 20112
 */ 

#include "FreeRTOS.h"
#include "task.h"
#include "UART.h"
#include "SPI.h"
#include "LCD.h"

uint8 UART_data=0;
uint8 SPI_data=0;

TaskHandle_t* Task_initialization             = NULL;
TaskHandle_t* Task2_UART_RX_LED_Selection     = NULL;
TaskHandle_t* Task3_SPI_Trans_LED_Selection   = NULL;
TaskHandle_t* Task6_UART_RX_LED_Operation     = NULL;



void Task_init(void* ptr_0)
{
	while (1)
	{
		LCD_Init();
		UART_Init();
		UART_Start();
		SPI_Master_Init();
		SPI_Start();
		
		LCD_Clear();
		LCD_WriteString("TASK_I");
		
		vTaskSuspend(Task_initialization );
		
	}
}


void Task2_UART_RX_LED_Sel(void* ptr_7)
{
	while(1)
	{
		UART_data = RX_Byte();
		
		vTaskDelay(3);
	}
	
}

void Task3_SPI_Trans_LED_Sel(void* ptr_8)
{
	while (1)
	{
		LCD_Clear();
		LCD_WriteString("LED1: 1");
		LCD_GoTo(1,0);
		LCD_WriteString("LED2: 2");
		SPI_Send_Byte(UART_data);
		vTaskDelay(5);
		
	}
	
}



void Task6_UART_RX_LED_Operat(uint8* ptr_11)
{
	while(1)
	{
		LCD_Clear();
		LCD_WriteString("LED ON:O");
		LCD_GoTo(1,0);
		LCD_WriteString("LED CLOSE:C");
		UART_data = RX_Byte();
		vTaskDelay(10);
		
	}
}





int main(void)
{
	
	xTaskCreate( Task_init,
	"initialization",
	configMINIMAL_STACK_SIZE,
	NULL,
	4,
	Task_initialization
	);
	
	
	xTaskCreate( Task2_UART_RX_LED_Sel,
	"select your led",
	configMINIMAL_STACK_SIZE,
	NULL,
	1,
	Task2_UART_RX_LED_Selection
	);
	
	xTaskCreate( Task3_SPI_Trans_LED_Sel,
	"SPI Transmit the selection of led",
	configMINIMAL_STACK_SIZE,
	NULL,
	3,
	Task3_SPI_Trans_LED_Selection
	);
	
	
	xTaskCreate( Task6_UART_RX_LED_Operat,
	"select the operation of the led",
	configMINIMAL_STACK_SIZE,
	NULL,
	2,
	Task6_UART_RX_LED_Operation
	);
	
	
	
	vTaskStartScheduler();
	
	
    while (1) 
    {
    }
}

