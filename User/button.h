#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#define KEY0 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)
#define KEY1 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)

void Button_Config(void);

#endif
