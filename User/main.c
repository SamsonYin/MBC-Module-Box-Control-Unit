//ͷ�ļ�
#include "stm32f10x.h"
#include "system.h"
#include "uart.h"
//#include "GPIOLIKE51.h"

//��������
void LED_Config(void);
//void UART1_Config(void);
//void UART2_Config(void);

//=============================================================================
//�ļ����ƣ�Delay
//���ܸ�Ҫ����ʱ
//����˵����nCount����ʱ����
//�������أ���
//=============================================================================

//void Delay(uint32_t nCount)
//{
//  for(; nCount != 0; nCount--);
//}


//=============================================================================
//�ļ����ƣ�main
//���ܸ�Ҫ��������
//����˵������
//�������أ�int
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
//�ļ����ƣ�GPIO_Configuration
//���ܸ�Ҫ��GPIO��ʼ��
//����˵������
//�������أ���
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

