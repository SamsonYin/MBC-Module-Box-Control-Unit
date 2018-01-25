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

extern u8 timtest;
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

#endif
