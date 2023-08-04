#include "stm32f10x.h"                  // Device header

uint16_t temperature_getvalue(){
uint16_t Vsense;
ADC_SoftwareStartConvCmd(ADC1,ENABLE);//触发转换
while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==SET);//等待转换完成
Vsense=ADC_GetConversionValue(ADC1);
return ((1.43-Vsense)/4.3+25);
}