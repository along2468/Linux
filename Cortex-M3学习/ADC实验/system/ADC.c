#include "stm32f10x.h"                  // Device header

void adc_init(){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

RCC_ADCCLKConfig( RCC_PCLK2_Div6);
	GPIO_InitTypeDef gpiostruct;
	gpiostruct.GPIO_Mode=GPIO_Mode_AIN;
	gpiostruct.GPIO_Pin=GPIO_Pin_0;
	gpiostruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpiostruct);
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	ADC_InitTypeDef adc_initstruct;
	adc_initstruct.ADC_ContinuousConvMode=ENABLE;
	adc_initstruct.ADC_DataAlign=ADC_DataAlign_Right;
	adc_initstruct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	adc_initstruct.ADC_Mode=ADC_Mode_AlterTrig;
	adc_initstruct.ADC_NbrOfChannel=DISABLE;
	adc_initstruct.ADC_ScanConvMode=1;
	ADC_Init(ADC1,&adc_initstruct);

ADC_Cmd(ADC1,ENABLE);

//校准
ADC_ResetCalibration(ADC1);//重置校准
while(ADC_GetResetCalibrationStatus(ADC1)==SET);//获取复位状态
ADC_StartCalibration(ADC1);//启动校准
while(ADC_GetCalibrationStatus(ADC1)==SET);//获取校准状态
}

