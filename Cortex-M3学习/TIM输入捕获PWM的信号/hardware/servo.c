#include "stm32f10x.h"                  // Device header
#include "pwm.h"

void servo_init(){
pwm_init();
}

void setsingle(uint8_t single){
TIM_SetCompare1(TIM2,single/180*2000+500);

}