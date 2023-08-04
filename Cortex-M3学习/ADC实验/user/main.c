#include "stm32f10x.h"                  // Device header
#include "ADC.h"
#include "Delay.h"
#include "temperature.h"

int main(){
	uint16_t tem_value;
	adc_init();
	ADC_TempSensorVrefintCmd(ENABLE);
	while(1){
	tem_value=temperature_getvalue();
	
	}
}