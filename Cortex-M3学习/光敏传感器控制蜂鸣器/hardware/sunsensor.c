#include "stm32f10x.h"                  // Device header

void sunsensor_init(){
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
GPIO_InitTypeDef GPIO_InitStruct;
GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12;
GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_Init(GPIOA,&GPIO_InitStruct);	
}
uint8_t SunSenRet(){
uint8_t sunretnumber;
sunretnumber=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12);
return sunretnumber;
}

