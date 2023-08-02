#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "pwm.h"
#include "servo.h"
int main(){
	servo_init();
	uint16_t i;
	while(1){
		for(i=0;i<=180;i=i+30){
		setsingle(i);
		}
		Delay_ms(10);
		setsingle(180);
		}
	}


