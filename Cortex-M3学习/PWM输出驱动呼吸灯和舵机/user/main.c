#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "pwm.h"
int main(){
	pwm_init();
	uint16_t i;
	while(1){
	for(i=0;i<=100;i++){
	pwd_setcompare(i);
		Delay_ms(10);
	}
	Delay_ms(100);
	for(i=0;i<=100;i++){
	pwd_setcompare(100-i);
		Delay_ms(10);
	}
	}
}

