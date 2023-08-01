#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "buzzer.h"
void timer_init(){
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
TIM_InternalClockConfig(TIM2);
	TIM_TimeBaseInitTypeDef tim_timebasestruct;
	tim_timebasestruct.TIM_ClockDivision=TIM_CKD_DIV1;
	tim_timebasestruct.TIM_CounterMode=TIM_CounterMode_Up;
	tim_timebasestruct.TIM_Period=10000-1;//ARR
	tim_timebasestruct.TIM_Prescaler=3400-1;//PSC
	tim_timebasestruct.TIM_RepetitionCounter=0;
TIM_TimeBaseInit(TIM2,&tim_timebasestruct);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_Initstruct;
	NVIC_Initstruct.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_Initstruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_Initstruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_Initstruct);

TIM_Cmd(TIM2,ENABLE);
}

void TIM2_IRQHandler(){
if(TIM_GetITStatus(TIM2,TIM_IT_Update)==1){
buzzer_open();
Delay_ms(500);
buzzer_close();
}
TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}