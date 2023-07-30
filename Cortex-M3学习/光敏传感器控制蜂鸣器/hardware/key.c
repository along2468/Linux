#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void key_init(void){

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOC,ENABLE);
GPIO_InitTypeDef GPIO_InitStruct;
GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
GPIO_InitStruct.GPIO_Pin=GPIO_Pin_15 |GPIO_Pin_5;
GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_Init(GPIOA,&GPIO_InitStruct);	
GPIO_Init(GPIOC,&GPIO_InitStruct);
	
}

uint8_t key_GetRet(void){
uint8_t keynumber =0;
if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)==0){
    Delay_ms(20);
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)==0);
	Delay_ms(20);
	return keynumber=1;
	}
if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)==0){
    Delay_ms(20);
	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)==0);
	Delay_ms(20);
	return keynumber=2;
	} 
return keynumber;
}