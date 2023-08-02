#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "pwm.h"
#include "TimIC.h"
int main(){
	tim_ic_init();
	pwm_init();
	while(1){
	getfreq();
	}
}


