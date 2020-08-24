#include "PASSWORD.h"
#include "UART.h"
uint8 pass_check(uint8 user_pass)
{
	uint8 check =1;
	
		while(user_pass != '5')
		{
			TX_String("Wrong password");
			check=0;
			break;
		}
	
	return check;
}