#include "stm32f10x.h"                  // Device header
#include "led.h"
#include "Delay.h"
#include "temperature.h"

int main(){

led_init();
temperature_init();
	led_open();
	while(1){
	if(EXTI_GetITStatus(EXTI_Line5)== SET){
	TIM5_IRQHandler();
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
	}
}

