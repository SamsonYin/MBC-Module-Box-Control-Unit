#include "stm32f10x.h"
#include "system.h"


int main(void)
{
	SysInit();
	Status_LED_FastFlashing();
	Delay_ms(1000);
	Delay_ms(1000);
	Delay_ms(1000);
	InitShortData1();
	shortDataSend1[0]=USART_READ_POINT;
	USART1_Tx(shortDataSend1,shortDataLength1);
	while (1)                                                                                    
	{
		if((controller_status != 2) && (controller_status != 5) && (controller_status != 6))
		{
			Delay_ms(1000);
			Delay_ms(1000);
			Delay_ms(1000);
			shortDataSend1[0]=112;
			USART1_Tx(shortDataSend1,shortDataLength1);
		}
  }
}


