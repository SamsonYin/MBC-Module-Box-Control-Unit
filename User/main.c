#include "stm32f10x.h"
#include "system.h"


int main(void)
{
	SysInit();
	Status_LED_FastFlashing();
	while (1)
	{
//		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
//		GPIO_ResetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);
//		InitShortData1();
//		shortDataSend1[0]=0x17;
//		shortDataSend1[6]=0x11;
//		USART1_Tx(shortDataSend1,shortDataLength1);
//		InitShortData2();
//		shortDataSend2[0]=0x01;
//		USART2_Tx(shortDataSend2,shortDataLength2); 
		//Delay_ms(1000);
//		GPIO_SetBits(GPIOC,GPIO_Pin_13);
//		GPIO_SetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);
//		InitShortData1();
//		shortDataSend1[0]=0x88;
//		shortDataSend1[6]=0x22;
//		USART1_Tx(shortDataSend1,shortDataLength1);
//		InitShortData2();
//		shortDataSend2[0]=0x55;
//		USART2_Tx(shortDataSend2,shortDataLength2);
		//Delay_ms(1000);
    }
}


