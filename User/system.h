#include "stm32f10x.h"
#include "uart.h"

#define PEAK 1
#define NULL 2
#define QPLUS 3
#define QMINUS 4

extern u8 controller_status;
extern u8 locking_point;

void SysInit(void);
void LED_Config(void);

void Delay_ms(uint32_t);
void Delay_us(uint32_t);
void Delay(uint32_t);

void StopFlahsingStatusLED(void);
void TIM1_Config(void);
void TIM2_Config(void);
void TIM4_Config(void);
void Status_LED_normalOn(void);
void Status_LED_normalOff(void);
void Status_LED_normalToggle(void);

void Status_LED_FastFlashing(void);
void NoLightErrorLEDOn(void);
void StrongLightErrorLEDOn(void);
void StopErrorFlash(void);
void Peak_LED_On(void);
void Null_LED_On(void);
void QPlus_LED_On(void);
void QMinus_LED_On(void);
void All_Point_LED_Off(void);
