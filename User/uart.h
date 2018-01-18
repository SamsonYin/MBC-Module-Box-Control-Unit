#ifndef _USART_H_
#define _USART_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#define UPPER_LIMIT	1
#define LOWER_LIMIT	2

#define USART_READ_RES				101
#define USART_READ_DC					102
#define USART_READ_POWER			103
#define USART_READ_BIAS			  104
#define USART_READ_VPI				105
#define USART_SET_MODE				107
#define USART_SET_DC					108
#define USART_SET_POLAR				109
#define USART_RESET						110
#define USART_JUMP_VPI				111
#define USART_READ_STATUS			112
#define USART_SET_CHANNEL_BIAS 113
#define USART_SET_DITHER_AMP  114
#define USART_PAUSE_CONTROL		115
#define USART_RESUME_CONTROL	116
#define USART_SET_VERSION			117

#define USART_READ_TWOK				150
#define USART_WRITE_DACRANGE	151
#define USART_READ_DACRANGE		152
#define USART_SET_DCDEC				153

#define USART_READ_ADCRESULT	200

#define shortDataLength1 7
#define shortDataLength2 9

extern uint8_t USARTBuffer1[9];     // The data received from MATLAB
extern uint8_t USARTBuffer2[7];
extern int USARTDataCount1;              // To count until 7 bytes are received
extern int USARTDataCount2;  
extern u8 shortDataSend1[shortDataLength1];             //  The adc converted results to be sent back to MATLAB
extern u8 shortDataSend2[shortDataLength2];
extern float ditherAmplitude;
extern u32 float_hex;
//extern ControllerState previousState;

void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART1_Config(void);
void USART2_Config(void);
void USART1_FunctionHandler(void);
void USART2_FunctionHandler(void);
void ClearUSARTBuffer1(void);
void ClearUSARTBuffer2(void);
extern void InitShortData1(void);
extern void InitShortData2(void);
extern void USART1_Tx(u8 data[],u16 noOfBytes);
extern void USART2_Tx(u8 data[],u16 noOfBytes);


//#include "stm32f10x.h"	
//#include "stdio.h"
//extern u8 USART_RX_BUF[64];     //���ջ���,���63���ֽ�.ĩ�ֽ�Ϊ���з� 
//extern u8 USART_RX_STA;         //����״̬���	

//void uart_init(u32 bound);

//#endif

//#ifndef __SYS_H
//#define __SYS_H	
//#include "stm32f10x.h"
////////////////////////////////////////////////////////////////////////////////////	 
////������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
////ALIENTEK Mini STM32������
////ϵͳʱ�ӳ�ʼ��		   
////����ԭ��@ALIENTEK
////������̳:www.openedv.com
////�޸�����:2010/5/27
////�汾��V1.4
////��Ȩ���У�����ؾ���
////Copyright(C) ����ԭ�� 2009-2019
////All rights reserved
////******************************************************************************** 
//#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
//#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
//#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
////IO�ڵ�ַӳ��
//#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
//#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
//#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
//#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
//#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
//#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
//#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

//#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
//#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
//#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
//#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
//#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
//#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
//#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
// 
////IO�ڲ���,ֻ�Ե�һ��IO��!
////ȷ��n��ֵС��16!
//#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
//#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

//#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
//#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

//#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
//#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

//#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
//#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

//#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
//#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

//#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
//#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

//#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
//#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����



//void NVIC_Configuration(void);



#endif
