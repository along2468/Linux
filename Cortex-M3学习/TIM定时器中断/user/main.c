#include "stm32f10x.h"                  // Device header
#include "buzzer.h"
#include "TIM.h"
#include "Delay.h"
int main(){
buzzer_init();
timer_init();
	while(1){
	TIM2_IRQHandler();
	}
}

