#include "stm32f10x.h"                  // Device header

void pwm_init(){

RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_initstruct;
	GPIO_initstruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_initstruct.GPIO_Pin=GPIO_Pin_1;
	GPIO_initstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_initstruct);
	
	TIM_InternalClockConfig(TIM2);//使能内部时钟
	TIM_TimeBaseInitTypeDef tim_initstruct;
	tim_initstruct.TIM_ClockDivision=TIM_CKD_DIV1;
	tim_initstruct.TIM_CounterMode=TIM_CounterMode_Up;
	tim_initstruct.TIM_Period=10000-1;
	tim_initstruct.TIM_Prescaler=720-1;
	tim_initstruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&tim_initstruct);
	
	TIM_OCInitTypeDef tim_ocinitstruct;
	tim_ocinitstruct.TIM_OCMode=TIM_OCMode_PWM1;
	tim_ocinitstruct.TIM_OCPolarity=TIM_OCPolarity_High;
	tim_ocinitstruct.TIM_OutputState=TIM_OutputState_Enable;
	tim_ocinitstruct.TIM_Pulse=5000;
	TIM_OC2Init(TIM2,&tim_ocinitstruct);
TIM_Cmd(TIM2,ENABLE);

}

