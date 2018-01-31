#include "button.h"
#include "system.h"

void Button_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 	EXTI_InitTypeDef EXTI_InitStructure;
 	//NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_1;  //PB0,PB1
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//EXTI0 configuration
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	//EXTI1 configuration
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}

void EXTI0_IRQHandler(void)
{ 
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)	 
	{	  
		Delay_ms(10);
		if(KEY0==0)
		{
			switch(locking_point)
			{
				case NULL:
				{
					InitShortData1();
					shortDataSend1[0]=USART_SET_POINT;
					shortDataSend1[1]=2;
				  shortDataSend1[2]=2;
					USART1_Tx(shortDataSend1,shortDataLength1);
					All_Point_LED_Off();
					Status_LED_FastFlashing();
					break;
				}
				case PEAK:
				{
					InitShortData1();
					shortDataSend1[0]=USART_SET_POINT;
					shortDataSend1[1]=1;
				  shortDataSend1[2]=1;
					USART1_Tx(shortDataSend1,shortDataLength1);
					All_Point_LED_Off();
					Status_LED_FastFlashing();
					break;
				}
				case QPLUS:
				{
					InitShortData1();
					shortDataSend1[0]=USART_SET_POINT;
					shortDataSend1[1]=1;
				  shortDataSend1[2]=2;
					USART1_Tx(shortDataSend1,shortDataLength1);
					All_Point_LED_Off();
					Status_LED_FastFlashing();
					break;
				}
				case QMINUS:
				{
					InitShortData1();
					shortDataSend1[0]=USART_SET_POINT;
					shortDataSend1[1]=2;
				  shortDataSend1[2]=1;
					USART1_Tx(shortDataSend1,shortDataLength1);
					All_Point_LED_Off();
					Status_LED_FastFlashing();
					break;
				}
				default:
				{
					break;
				}
			}
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line1) != RESET)	 
	{	  
		Delay_ms(10);
		if(KEY1==0)
		{
			switch(locking_point)
			{
				case NULL:
				{
					InitShortData1();
					shortDataSend1[0]=USART_SET_POINT;
					shortDataSend1[1]=1;
				  shortDataSend1[2]=2;
					USART1_Tx(shortDataSend1,shortDataLength1);
					All_Point_LED_Off();
					Status_LED_FastFlashing();
					break;
				}
				case PEAK:
				{
					InitShortData1();
					shortDataSend1[0]=USART_SET_POINT;
					shortDataSend1[1]=2;
				  shortDataSend1[2]=1;
					USART1_Tx(shortDataSend1,shortDataLength1);
					All_Point_LED_Off();
					Status_LED_FastFlashing();
					break;
				}
				case QPLUS:
				{
					InitShortData1();
					shortDataSend1[0]=USART_SET_POINT;
					shortDataSend1[1]=2;
				  shortDataSend1[2]=2;
					USART1_Tx(shortDataSend1,shortDataLength1);
					All_Point_LED_Off();
					Status_LED_FastFlashing();
					break;
				}
				case QMINUS:
				{
					InitShortData1();
					shortDataSend1[0]=USART_SET_POINT;
					shortDataSend1[1]=1;
				  shortDataSend1[2]=1;
					USART1_Tx(shortDataSend1,shortDataLength1);
					All_Point_LED_Off();
					Status_LED_FastFlashing();
					break;
				}
				default:
				{
					break;
				}
			}
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line1);
}
