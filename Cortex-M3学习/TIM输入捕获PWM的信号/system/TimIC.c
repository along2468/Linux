#include "stm32f10x.h"                  // Device header

void tim_ic_init(){
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef gpio_initstruct;
	gpio_initstruct.GPIO_Mode=GPIO_Mode_IPU;
	gpio_initstruct.GPIO_Pin=GPIO_Pin_0;
	gpio_initstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&gpio_initstruct);

	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef tim_tibasestruct;
	tim_tibasestruct.TIM_ClockDivision=TIM_CKD_DIV1;
	tim_tibasestruct.TIM_CounterMode=TIM_CounterMode_Up;
	tim_tibasestruct.TIM_Period=10000-1;
	tim_tibasestruct.TIM_Prescaler=720-1;
	tim_tibasestruct.TIM_RepetitionCounter=0;
	
	TIM_TimeBaseInit(TIM3,&tim_tibasestruct);
	
	TIM_ICInitTypeDef tim_icinitstruct;
	tim_icinitstruct.TIM_Channel=TIM_Channel_1 ;
	tim_icinitstruct.TIM_ICFilter=0xF;
	tim_icinitstruct.TIM_ICPolarity=TIM_ICPolarity_BothEdge;
	tim_icinitstruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	tim_icinitstruct.TIM_ICSelection=TIM_ICSelection_DirectTI;
    TIM_ICInit(TIM3,&tim_icinitstruct);
	
	TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
	
	TIM_Cmd(TIM3,ENABLE);
	
}

uint16_t getfreq(){
return (100000/TIM_GetCapture1(TIM3));
}