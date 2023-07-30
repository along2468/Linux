#include "stm32f10x.h"                  // Device header

void LED_init(void){
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
GPIO_InitTypeDef GPIO_initstruct;
GPIO_initstruct.GPIO_Mode=GPIO_Mode_Out_PP;
GPIO_initstruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;
GPIO_initstruct.GPIO_Speed=GPIO_Speed_50MHz;
GPIO_Init(GPIOB,&GPIO_initstruct);
}
void LED1_Open(void){
GPIO_SetBits(GPIOB,GPIO_Pin_0);
}
void LED1_Close(void){
GPIO_ResetBits(GPIOB,GPIO_Pin_0);
}
void LED2_Open(void){
GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_SET);
}
void LED2_Close(void){
GPIO_WriteBit(GPIOB,GPIO_Pin_1,Bit_RESET);
}
void LED1_turn(void){
if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_0)==0){
GPIO_SetBits(GPIOB,GPIO_Pin_0);
}else{
GPIO_ResetBits(GPIOB,GPIO_Pin_0);
}
}
void LED2_turn(void){
if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_1)==0){
GPIO_SetBits(GPIOB,GPIO_Pin_1);
}else{
GPIO_ResetBits(GPIOB,GPIO_Pin_1);
}
}
