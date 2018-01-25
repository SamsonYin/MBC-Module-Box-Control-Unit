#include "stm32f10x.h"
#include "uart.h"

void SysInit(void);

void Delay_ms(uint32_t);
void Delay_us(uint32_t);
void Delay(uint32_t);

void StopFlahsingStatusLED(void);
void TIM2_Config(void);
void TIM4_Config(void);
void Status_LED_normalOn(void);
void Status_LED_normalOff(void);
void Status_LED_normalToggle(void);

void NoLightErrorLEDOn(void);
void StrongLightErrorLEDOn(void);
void StopErrorFlash(void);
