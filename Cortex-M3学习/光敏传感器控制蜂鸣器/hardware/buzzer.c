#include "stm32f10x.h"                  // Device header

void buzzer_init(void){
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef gpio_initstruct;
	gpio_initstruct.GPIO_Mode=GPIO_Mode_Out_PP;
	gpio_initstruct.GPIO_Pin=GPIO_Pin_11;
	gpio_initstruct.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_Init(GPIOA,&gpio_initstruct);
}
void buzzer_Open(void){
GPIO_SetBits(GPIOA,GPIO_Pin_11);
}
void buzzer_Close(void){
GPIO_ResetBits(GPIOA,GPIO_Pin_11);
}

