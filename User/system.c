#include "system.h"
#include "uart.h"
#include "button.h"

static u8  fac_us = 0;//SysTick->Load value for 1us
static u16 fac_ms = 0;//SysTick->Load value for 1ms

u8 controller_status = 0;
u8 locking_point = 0;

void RCC_Config(void);
void SysNVIC_Config(void);
void Delay_Init(u8 SYSCLK);
	
void SysInit(void)
{
	SystemInit();
	RCC_Config();
	Delay_Init(72);
	LED_Config();
	SysNVIC_Config();
	Button_Config();
	USART1_Config();
	USART2_Config();
	TIM1_Config();
	TIM2_Config();
	TIM4_Config();
}

void SysNVIC_Config(void)
{

	NVIC_InitTypeDef NVIC_InitStructure;
//	SCB->AIRCR = 0x05FA0000 | 0x400;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   
	//USART1 IR	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;      
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1; //Pority 0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;    
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     
	NVIC_Init(&NVIC_InitStructure);
	
	//USART2 IR
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;      
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1; //Pority 0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;    
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;     
	NVIC_Init(&NVIC_InitStructure);
	
	//EXTI0 IR
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure); 
	
	//EXTI1 IR
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;			
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure); 
}

void TIM2_Config(void)  //light too weak flashing
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	/* Time base configuration */
	//AHB1 runs at 36MHz, 
	//timer clock = 72MHz =AHB1 CLK * 2 , since AHB1 PRESC = 2 (!1)
	TIM_Cmd(TIM2, DISABLE);
	TIM_TimeBaseStructure.TIM_Prescaler = 8000 - 1; 
  TIM_TimeBaseStructure.TIM_Period = 9000 - 1;  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //no division
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	/* TIM IT enable */
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	/* Enable TIM2 for flashing LED */
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		Status_LED_normalToggle();
	}
}

void TIM4_Config(void)  //light too strong flashing
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	/* TIM4 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	/* Time base configuration */
	//AHB1 runs at 36MHz, 
	//timer clock = 72MHz =AHB1 CLK * 2 , since AHB1 PRESC = 2 (!1)
	TIM_Cmd(TIM4, DISABLE);
	TIM_TimeBaseStructure.TIM_Prescaler = 16000 - 1; 
  TIM_TimeBaseStructure.TIM_Period = 13500 - 1;  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //no division
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	/* TIM IT enable */
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
	/* Enable TIM4 for flashing LED */
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		Status_LED_normalToggle();
	}
}

void TIM1_Config(void)  //light too strong flashing
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	/* TIM1 clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	/* Time base configuration */
	//AHB1 runs at 72MHz, 
	//timer clock = 72MHz =AHB1 CLK , since AHB1 PRESC = 1 
	TIM_Cmd(TIM1, DISABLE);
	TIM_TimeBaseStructure.TIM_Prescaler = 4800-1; 
  TIM_TimeBaseStructure.TIM_Period = 3000-1;  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //no division
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;  //Set to 0 means interrupt handler will be executed in every timer overflow event.This parameter must be set,or the interrupt handler won't be executed in every overflow event.
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);
	/* TIM IT enable */
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	
	/* Enable TIM1 for flashing LED */
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void TIM1_UP_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
		Status_LED_normalToggle();
	}
}

void Status_LED_FastFlashing(void)
{
	StopErrorFlash();
	TIM_Cmd(TIM1, ENABLE); //Start timer1, flashing LEDs
}

void Status_LED_normalOn(void)
{
	StopErrorFlash();
	//GPIO_ResetBits(GPIOC, GPIO_Pin_13); //should be checked when LED pin changes.
	GPIO_SetBits(GPIOC, GPIO_Pin_13); //should be checked when LED pin changes.
}

void Status_LED_normalOff(void)
{
	StopErrorFlash();
	//GPIO_SetBits(GPIOC, GPIO_Pin_13); //should be checked when LED pin changes.
	GPIO_ResetBits(GPIOC, GPIO_Pin_13); //should be checked when LED pin changes.
}

void Status_LED_normalToggle(void)
{
	GPIOC->ODR ^= GPIO_Pin_13;
	//GPIO_ToggleBits(GPIOB, GPIO_Pin_14); //should be checked when LED pin changes.
}

void NoLightErrorLEDOn(void)
{
	StopErrorFlash();
	TIM_Cmd(TIM2, ENABLE);
}

void StrongLightErrorLEDOn(void)
{
	StopErrorFlash();
	TIM_Cmd(TIM4, ENABLE);
}

void StopErrorFlash(void)
{
	TIM_Cmd(TIM1, DISABLE);
	TIM_Cmd(TIM2, DISABLE);
	TIM_Cmd(TIM4, DISABLE);
}

void Null_LED_On(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
	GPIO_SetBits(GPIOB, GPIO_Pin_6);
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);
	GPIO_ResetBits(GPIOB, GPIO_Pin_8);
}

void Peak_LED_On(void)
{
	GPIO_SetBits(GPIOB, GPIO_Pin_5);
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);
	GPIO_ResetBits(GPIOB, GPIO_Pin_8);
}

void QPlus_LED_On(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);
	GPIO_SetBits(GPIOB, GPIO_Pin_7);
	GPIO_ResetBits(GPIOB, GPIO_Pin_8);
}

void QMinus_LED_On(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);
	GPIO_SetBits(GPIOB, GPIO_Pin_8);
}

void All_Point_LED_Off(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);
	GPIO_ResetBits(GPIOB, GPIO_Pin_8);
}

void RCC_Config(void)
{
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);
	while(SUCCESS != RCC_WaitForHSEStartUp()){}
	//设置FLASH储存器延时时钟周期数
	FLASH_SetLatency(FLASH_Latency_2);    //FLASH_Latency_2  2延时周期
	//选择FLASH预取指换缓存的模式 
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);     //预取指缓存使能
	/*设置PLL时钟源及倍频系数*/  
	/* Fcpu = (PLL_src * PLL_MUL) = (8 Mhz / 1) * (9) = 72Mhz   */ 
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);            
	/* Enable PLL */
	RCC_PLLCmd(ENABLE); 
	 /*检查指定的RCC标志位(PLL准备好标志)设置与否*/    
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) {}
	/* Set system clock dividers */
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK2Config(RCC_HCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div2);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   
	/* Embedded Flash Configuration */
	FLASH_SetLatency(FLASH_Latency_2);                           
	FLASH_HalfCycleAccessCmd(FLASH_HalfCycleAccess_Disable);
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
	/*SYSCLK configuration*/
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
}

void LED_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE); 						 
//=============================================================================
//Status_LED -> PC13
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

void Delay_Init(u8 SYSCLK)
{
//	SysTick->CTRL&=0xfffffffb;//bit2清空,选择外部时钟  HCLK/8
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
	fac_us=SYSCLK/8;		    
	fac_ms=(u16)fac_us*1000;
}

void Delay_ms(uint32_t msTime) 
{
	u32 temp;		   
	SysTick->LOAD=(u32)msTime*fac_ms;//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           //清空计数器
	SysTick->CTRL=0x01 ;          //开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	  
	
}

void Delay_us(uint32_t usTime)
{
	u32 temp;	    	 
	SysTick->LOAD=usTime*fac_us; //时间加载	  		 
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL=0x01 ;      //开始倒数 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	
}

void Delay(uint32_t shortDelay)
{
	while (shortDelay--){};
}

void System_Reset(void)
{
	Delay_ms(1000);
	__set_FAULTMASK(1);
	NVIC_SystemReset();
	
}
