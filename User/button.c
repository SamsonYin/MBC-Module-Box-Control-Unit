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
    Delay_ms(10); 
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)	 
	{	  
		
	}
	EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI1_IRQHandler(void)
{
    Delay_ms(10); 
  if(EXTI_GetITStatus(EXTI_Line1) != RESET)	 
	{	  
		
	}
	EXTI_ClearITPendingBit(EXTI_Line1);
}
