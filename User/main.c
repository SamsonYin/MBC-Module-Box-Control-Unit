#include "stm32f10x.h"
#include "system.h"


int main(void)
{
	SysInit();
	while (1)
	{
		Delay_ms(800);
		InitShortData1();
		shortDataSend1[0]=112;
		USART1_Tx(shortDataSend1,shortDataLength1);
		Delay_ms(800);
		InitShortData1();
		shortDataSend1[0]=USART_READ_POINT;
		USART1_Tx(shortDataSend1,shortDataLength1);
  }
}


