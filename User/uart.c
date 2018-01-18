#include "uart.h"

uint8_t USARTBuffer1[9];     // The data received from MATLAB
uint8_t USARTBuffer2[7];     // The data received from MATLAB
int USARTDataCount1;              // To count until 7 bytes are received
int USARTDataCount2;
u8 shortDataSend1[shortDataLength1];
u8 shortDataSend2[shortDataLength2];

u8 USARTDataDiscardFlag1 = 0;
u8 USARTDataDiscardFlag2 = 0;

void InitShortData1(void);
void InitShortData2(void);
void USART1_Tx(u8 data[],u16 noOfBytes);
void USART2_Tx(u8 data[],u16 noOfBytes);
void ClearUSARTBuffer1(void);
void ClearUSARTBuffer2(void);

void TIM9_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	/* TIM9 clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
	/* Time base configuration */
	//APB2 runs at 84MHz, 
	TIM_Cmd(TIM9, DISABLE);
	TIM_TimeBaseStructure.TIM_Prescaler = 4200 - 1; // 84MHz/4200 = 20kHz
  TIM_TimeBaseStructure.TIM_Period = 4000 - 1;  // 20kHz/4000 = 5Hz
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //no division
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);
	/* TIM IT enable */
	TIM_ITConfig(TIM9, TIM_IT_Update, ENABLE);
	
	/* Enable TIM9 for USART received data counting */
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_BRK_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//TIM_Cmd(TIM9, DISABLE);
}

void TIM1_BRK_IRQHandler(void)
{
//	if (TIM_GetITStatus(TIM9, TIM_IT_Update) != RESET)
//	{
//		TIM_ClearITPendingBit(TIM9, TIM_IT_Update);
//		if(USARTDataDiscardFlag != 0)
//		{
//			if(!((USARTDataCount == 0)||(USARTDataCount == 7)))
//			{
//				ClearUSARTBuffer();
//			}
//		}
//		else
//		{
//			USARTDataDiscardFlag = 1;
//		}
//	}
}

void USART1_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef	USART1_InitStructure;
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  
	//USART_DeInit(USART1);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);  
	//PA9 TXD2  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	
	//PA10 RXD2  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
	GPIO_Init(GPIOA, &GPIO_InitStructure);  
	
	USART1_InitStructure.USART_BaudRate = 57600;
	USART1_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART1_InitStructure.USART_StopBits = USART_StopBits_1;
	USART1_InitStructure.USART_Parity = USART_Parity_No;
	USART1_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART1_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1,&USART1_InitStructure);   
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_ClearFlag(USART1,USART_FLAG_RXNE);
//	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
//	USART_ClearFlag(USART1,USART_FLAG_TC);
	USART_Cmd(USART1,ENABLE);
	
	//TIM9_Config();
}

void USART2_Config(void)
{
	USART_InitTypeDef USART_InitStructure;  
	GPIO_InitTypeDef GPIO_InitStructure;
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);   
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);     
      
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;   
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  
//	GPIO_Init(GPIOA, &GPIO_InitStructure); 

	//PA2 TXD2  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
	GPIO_Init(GPIOA, &GPIO_InitStructure);    

	//PA3 RXD2  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
	GPIO_Init(GPIOA, &GPIO_InitStructure);     
  
	USART_InitStructure.USART_BaudRate = 57600;  
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;  
	USART_InitStructure.USART_StopBits = USART_StopBits_1;  
	USART_InitStructure.USART_Parity = USART_Parity_No;  
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  
	USART_Init(USART2, &USART_InitStructure);   

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); 
	USART_ClearFlag(USART2,USART_FLAG_RXNE);
	USART_Cmd(USART2, ENABLE);
}

void USART1_IRQHandler(void)
{
	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==SET)
	{		
		u8 tempBuffer=0;	
		USART_ClearFlag(USART1,USART_FLAG_RXNE);			
//		if((TIM9->CR1&TIM_CR1_CEN) != 0x0001)
//		{
//			TIM_Cmd(TIM9, ENABLE);
//			USARTDataDiscardFlag = 0;
//		}
		tempBuffer=USART_ReceiveData(USART1);
		USARTBuffer1[USARTDataCount1] = tempBuffer;
		USARTDataCount1++;		 
		if (USARTDataCount1==7)
		{  
//			if(currentState != USART_STATE)
//			{
//				previousState = currentState;
//			}
//			else
//			{
//				previousState = INIT_STATE;
//			}
//			currentState = USART_STATE;
			USARTDataCount1 = 0;
			USARTDataDiscardFlag1 = 0;
			//TIM_Cmd(TIM9, DISABLE);
			USART1_FunctionHandler();
		}	
	}
//	if(USART_GetFlagStatus(USART1,USART_FLAG_TC)==SET)
//	{
//		USART_ClearFlag(USART1,USART_FLAG_TC);
//		USART_SendData(USART1,0x12); 
//	}
}

void USART2_IRQHandler(void)
{
	if(USART_GetFlagStatus(USART2,USART_FLAG_RXNE)==SET)
	{		
		u8 tempBuffer=0;	
		USART_ClearFlag(USART2,USART_FLAG_RXNE);			
//		if((TIM9->CR1&TIM_CR1_CEN) != 0x0001)
//		{
//			TIM_Cmd(TIM9, ENABLE);
//			USARTDataDiscardFlag = 0;
//		}
		tempBuffer=USART_ReceiveData(USART2);
		USARTBuffer2[USARTDataCount2] = tempBuffer;
		USARTDataCount2++;		 
		if (USARTDataCount2==7)
		{  
//			if(currentState != USART_STATE)
//			{
//				previousState = currentState;
//			}
//			else
//			{
//				previousState = INIT_STATE;
//			}
//			currentState = USART_STATE;
			USARTDataCount2 = 0;
			USARTDataDiscardFlag2 = 0;
			//TIM_Cmd(TIM9, DISABLE);
			USART2_FunctionHandler();
		}	
	}
}

void USART1_FunctionHandler(void)
{
	
}

void USART2_FunctionHandler(void)
{
	
}

void InitShortData1(void)
{	
	u8 i;
	for (i=0;i<shortDataLength1;i++)
	{
		shortDataSend1[i] = 0;
	}
}

void InitShortData2(void)
{	
	u8 i;
	for (i=0;i<shortDataLength2;i++)
	{
		shortDataSend2[i] = 0;
	}
}

void ClearUSARTBuffer1(void)
{
	u8 i;
	for(i = 0; i < 7; i++)
	{
		USARTBuffer1[i] = 0;
	}
	USARTDataCount1=0;
	USARTDataDiscardFlag1 = 0;
	//TIM_Cmd(TIM9, DISABLE);
}

void ClearUSARTBuffer2(void)
{
	u8 i;
	for(i = 0; i < 7; i++)
	{
		USARTBuffer2[i] = 0;
	}
	USARTDataCount2=0;
	USARTDataDiscardFlag2 = 0;
	//TIM_Cmd(TIM9, DISABLE);
}

void USART1_Tx(u8 data[],u16 noOfBytes)
{
	u16 ptr = 0;
	while (ptr < noOfBytes)
	{
		while(RESET == USART_GetFlagStatus(USART1,USART_FLAG_TXE));
		USART_SendData(USART1,data[ptr]);
		ptr++;
	}
}

void USART2_Tx(u8 data[],u16 noOfBytes)
{
	u16 ptr = 0;
	while (ptr < noOfBytes)
	{
		while(RESET == USART_GetFlagStatus(USART2,USART_FLAG_TXE));
		USART_SendData(USART2,data[ptr]);
		ptr++;
	}
}

//#include "uart.h"
//int fputc(int ch, FILE *f)
//{
//	USART_SendData(USART1, (uint8_t) ch);

//	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
//   
//    return ch;
//}
//int GetKey (void)  { 

//    while (!(USART1->SR & USART_FLAG_RXNE));

//    return ((int)(USART1->DR & 0x1FF));
//}

//u8 USART_RX_BUF[64];     //接收缓冲,最大64个字节.
////接收状态
////bit7，接收完成标志
////bit6，接收到0x0d
////bit5~0，接收到的有效字节数目
//u8 USART_RX_STA=0;       //接收状态标记

//void uart_init(u32 bound){
//    //GPIO端口设置
//    GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	 
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
//     //USART1_TX   PA.9
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
//   
//    //USART1_RX	  PA.10
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);  

//   //Usart1 NVIC 配置

//    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//

//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//	NVIC_Init(&NVIC_InitStructure);	//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器USART1
//  
//   //USART 初始化设置
//   
//	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	USART_InitStructure.USART_Parity = USART_Parity_No;
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

//    USART_Init(USART1, &USART_InitStructure);
//   

//    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
//   
//    USART_Cmd(USART1, ENABLE);                    //使能串口 

//}

//void USART1_IRQHandler(void)                	//串口1中断服务程序
//	{
//	u8 Res;
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
//		{
//		Res =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据
//		
//		if((USART_RX_STA&0x80)==0)//接收未完成
//			{
//			if(USART_RX_STA&0x40)//接收到了0x0d
//				{
//				if(Res!=0x0a)USART_RX_STA=0;//接收错误,重新开始
//				else USART_RX_STA|=0x80;	//接收完成了 
//				}
//			else //还没收到0X0D
//				{	
//				if(Res==0x0d)USART_RX_STA|=0x40;
//				else
//					{
//					USART_RX_BUF[USART_RX_STA&0X3F]=Res ;
//					USART_RX_STA++;
//					if(USART_RX_STA>63)USART_RX_STA=0;//接收数据错误,重新开始接收	  
//					}		 
//				}
//			}   		 
//     } 
//} 

