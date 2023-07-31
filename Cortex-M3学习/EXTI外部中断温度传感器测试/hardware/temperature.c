#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
void temperature_init(){
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_InitTypeDef gpio_initstruct;
	gpio_initstruct.GPIO_Mode=GPIO_Mode_IPD;
	gpio_initstruct.GPIO_Pin=GPIO_Pin_5;
	gpio_initstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&gpio_initstruct);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);
	
	EXTI_InitTypeDef exti_initstruct;
	exti_initstruct.EXTI_Line=EXTI_Line5;
	exti_initstruct.EXTI_LineCmd=ENABLE;
	exti_initstruct.EXTI_Mode=EXTI_Mode_Interrupt;
	exti_initstruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&exti_initstruct);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitTypeDef nvic_initstruct;
	nvic_initstruct.NVIC_IRQChannel=TIM5_IRQn;
	nvic_initstruct.NVIC_IRQChannelCmd=ENABLE;
	nvic_initstruct.NVIC_IRQChannelPreemptionPriority=1;
	nvic_initstruct.NVIC_IRQChannelSubPriority=1;
}

void  TIM5_IRQHandler (){

for(int i=0;i<4;i++){
    led_open();
	Delay_ms(50);
	led_close();
}
}


