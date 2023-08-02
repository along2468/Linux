#include "stm32f10x.h"                  // Device header

void pwm_init(){
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
TIM_InternalClockConfig(TIM2);	
GPIO_InitTypeDef gpio_initstruct;
	gpio_initstruct.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出
	gpio_initstruct.GPIO_Pin=GPIO_Pin_0;
	gpio_initstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_initstruct);
TIM_TimeBaseInitTypeDef tim_initstruct;
    tim_initstruct.TIM_ClockDivision=TIM_CKD_DIV1;
	tim_initstruct.TIM_CounterMode=TIM_CounterMode_Up;//向上计数
	tim_initstruct.TIM_Period=20000-1;//ARR
	tim_initstruct.TIM_Prescaler=72-1;//PSC
	tim_initstruct.TIM_RepetitionCounter=0;
TIM_TimeBaseInit(TIM2,&tim_initstruct);
	
	
	TIM_OCInitTypeDef tim_ocinitstruct;  //输出比较
	TIM_OCStructInit(&tim_ocinitstruct);
	tim_ocinitstruct.TIM_OCMode=TIM_OCMode_PWM1;
	tim_ocinitstruct.TIM_OCPolarity=TIM_OCPolarity_High;
	tim_ocinitstruct.TIM_OutputState=TIM_OutputState_Enable;
	tim_ocinitstruct.TIM_Pulse=90;//CCR
	TIM_OC1Init(TIM2,&tim_ocinitstruct);
	
	TIM_Cmd(TIM2,ENABLE);
}
//设置CCR的值,占空比=CCR/(ARR+1),ARR是自动重装载寄存器的值
void pwd_setcompare(uint16_t compare){
TIM_SetCompare1(TIM2,compare);
}


