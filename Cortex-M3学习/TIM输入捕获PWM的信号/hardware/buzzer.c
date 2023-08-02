#include "stm32f10x.h"                  // Device header

void buzzer_init(){
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
GPIO_InitTypeDef GPIO_InitStruct;
GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;
GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_Init(GPIOB,&GPIO_InitStruct);
}

void buzzer_open(){
GPIO_SetBits(GPIOB,GPIO_Pin_5);
}
void buzzer_close(){
GPIO_ResetBits(GPIOB,GPIO_Pin_5);
}

