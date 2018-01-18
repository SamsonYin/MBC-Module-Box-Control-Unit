//头文件
#include "stm32f10x.h"
#include "system.h"
#include "uart.h"
//#include "GPIOLIKE51.h"

//函数声明
void LED_Config(void);
//void UART1_Config(void);
//void UART2_Config(void);

//=============================================================================
//文件名称：Delay
//功能概要：延时
//参数说明：nCount：延时长短
//函数返回：无
//=============================================================================

//void Delay(uint32_t nCount)
//{
//  for(; nCount != 0; nCount--);
//}


//=============================================================================
//文件名称：main
//功能概要：主函数
//参数说明：无
//函数返回：int
//=============================================================================
int main(void)
{
	SysInit();
	LED_Config();
	while (1)
	{
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		GPIO_ResetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);
		InitShortData1();
		shortDataSend1[0]=0x17;
		shortDataSend1[6]=0x11;
		USART1_Tx(shortDataSend1,shortDataLength1);
		InitShortData2();
		shortDataSend2[0]=0x01;
		USART2_Tx(shortDataSend2,shortDataLength2);
		//USART_SendData(USART1,0x12);  
		Delay_ms(1000);
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		GPIO_SetBits(GPIOB,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);
		InitShortData1();
		shortDataSend1[0]=0x88;
		shortDataSend1[6]=0x22;
		USART1_Tx(shortDataSend1,shortDataLength1);
		InitShortData2();
		shortDataSend2[0]=0x55;
		USART2_Tx(shortDataSend2,shortDataLength2);
		//USART_SendData(USART1,0x15);
		Delay_ms(1000);
    }
}

//=============================================================================
//文件名称：GPIO_Configuration
//功能概要：GPIO初始化
//参数说明：无
//函数返回：无
//=============================================================================
void LED_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE); 						 
//=============================================================================
//LED -> PC13
//=============================================================================			 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}

