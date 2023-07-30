#include "stm32f10x.h"
#include "Delay.h"
#include "key.h"
#include "LED.h"
#include "buzzer.h"
#include "sunsensor.h"

uint8_t sunretumber;
uint8_t keynumber;
int main(){
	key_init();
    LED_init(); 
	buzzer_init();
	sunsensor_init();
while(1){
	keynumber=key_GetRet();
	if(keynumber==1){
    LED1_turn();
	}
	if(keynumber==2){
	LED2_turn();
	}
	
	sunretumber=SunSenRet();
	if(sunretumber==1){
	buzzer_Open();
	}else{
	buzzer_Close();
	}
}
}



