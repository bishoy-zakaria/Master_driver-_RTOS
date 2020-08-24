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
TaskHandle_t* Task1_LCD_LED_Selection         = NULL;
TaskHandle_t* Task2_UART_RX_LED_Selection     = NULL;
TaskHandle_t* Task3_SPI_Trans_LED_Selection   = NULL;
TaskHandle_t* Task4_Acknoledge                = NULL;
TaskHandle_t* Task5_LCD_LED_Operation         = NULL;
TaskHandle_t* Task6_UART_RX_LED_Operation     = NULL;
TaskHandle_t* Task7_SPI_Trans_LED_Operation   = NULL;



void Task_init(void* ptr_0)
{
	while (1)
	{
		LCD_Init();
		UART_Init();
		UART_Start();
		SPI_Master_Init();
		SPI_Start();
		vTaskSuspend(Task_initialization );
		
	}
}

void Task1_LCD_LED_Sel(void* ptr_6)
{
	while (1)
	{
		LCD_Clear();
		LCD_WriteString("LED1: 1");
	    LCD_GoTo(1,0);
	    LCD_WriteString("LED2: 2");
	    vTaskDelay(20);
	    
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
		SPI_Send_Byte(UART_data);
		vTaskDelay(7);
	}
	
}

void Task4_ACK(void* ptr_9)
{
	while (1)
	{
		SPI_data = SPI_Recieve_Byte();
	    vTaskDelay(21);
	}
	
}

void Task5_LCD_LED_Operat(void* ptr_10)
{
	while (1)
	{
		LCD_Clear();
		LCD_WriteString("LED ON:O");
		LCD_GoTo(1,0);
		LCD_WriteString("LED2 CLOSE:C");
		vTaskDelay(58 );
		
	}
}

void Task6_UART_RX_LED_Operat(uint8* ptr_11)
{
	while(1)
	{
		UART_data = RX_Byte();
		vTaskDelay(38);
		
	}
}

void Task7_SPI_Trans_LED_Operat (uint8* ptr_7)
{
	while (1)
	{
		*ptr_7 = SPI_Recieve_Byte();
		vTaskDelay(42 );
	}
	
}




int main(void)
{
	
	xTaskCreate( Task_init,
	"initialization",
	configMINIMAL_STACK_SIZE,
	NULL,
	8,
	Task_initialization
	);
	
	xTaskCreate( Task1_LCD_LED_Sel,
	"message to select your led",
	configMINIMAL_STACK_SIZE,
	NULL,
	7,
	Task1_LCD_LED_Selection
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
	6,
	Task3_SPI_Trans_LED_Selection
	);
	
	xTaskCreate( Task4_ACK,
	"acknowledge to ensure the connection",
	configMINIMAL_STACK_SIZE,
	NULL,
	5,
	Task4_Acknoledge
	);
	
	xTaskCreate( Task5_LCD_LED_Operat,
	"message to select the operation of the led",
	configMINIMAL_STACK_SIZE,
	NULL,
	4,
	Task5_LCD_LED_Operation 
	);
	
	xTaskCreate( Task6_UART_RX_LED_Operat,
	"select the operation of the led",
	configMINIMAL_STACK_SIZE,
	NULL,
	3,
	Task6_UART_RX_LED_Operation
	);
	
	xTaskCreate( Task7_SPI_Trans_LED_Operat,
	" SPI transmit to select the operation of the led",
	configMINIMAL_STACK_SIZE,
	NULL,
	2,
	Task7_SPI_Trans_LED_Operation
	);
	
	
	vTaskStartScheduler();
	
	
    while (1) 
    {
    }
}

