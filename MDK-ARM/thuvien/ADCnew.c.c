#include "gpio.h" 
#include "stdio.h"
#include "adc.h"

void hienthi ()
	{
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1,10);
		AD=HAL_ADC_GetValue(&hadc1);
	}