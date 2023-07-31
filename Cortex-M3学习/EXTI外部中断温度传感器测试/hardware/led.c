#include "stm32f10x.h"                  // Device header

void led_init(){
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
GPIO_InitTypeDef gpio_initstruct;
gpio_initstruct.GPIO_Mode=GPIO_Mode_Out_PP;
gpio_initstruct.GPIO_Pin=GPIO_Pin_8;
gpio_initstruct.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_Init(GPIOA,&gpio_initstruct);
}
void led_open(){
GPIO_SetBits(GPIOA,GPIO_Pin_8);
}
void led_close(){
GPIO_ResetBits(GPIOA,GPIO_Pin_8);
}
void led_turn(){
if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_8)==1){
GPIO_ResetBits(GPIOA,GPIO_Pin_8);
}else{
GPIO_SetBits(GPIOA,GPIO_Pin_8);
}
}