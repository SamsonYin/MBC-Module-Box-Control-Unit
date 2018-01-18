#include "system.h"
#include "uart.h"
#include "button.h"

static u8  fac_us=0;//us延时倍乘数
static u16 fac_ms=0;

void RCC_Config(void);
void SysNVIC_Config(void);
void Delay_Init(u8 SYSCLK);
	
void SysInit(void)
{
	SystemInit();
	RCC_Config();
	Delay_Init(72);
	SysNVIC_Config();
	Button_Config();
	USART1_Config();
	USART2_Config();
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
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;    
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
	
	//TIM2 IR
//	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //Pority 2
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
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
