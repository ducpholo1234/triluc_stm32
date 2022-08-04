#include "ADCnew.h" 
#include "stdio.h"
#include "adc.h"
#include "dma.h"
#include "gpio.h"
#include "tim.h"

	uint32_t AD;
	uint16_t check=0;
void hienthi_adc()
	{
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1,10);
		AD=HAL_ADC_GetValue(&hadc1);
	}
	void XferCpltCallback (DMA_HandleTypeDef *hdma)
{
  AD=AD; 
}
void sosanh ()
{
	if(AD>850)
	{ 
		AD=AD;		
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_0)==1 & HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1|GPIO_PIN_2)==0)
		{
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
			HAL_ADC_Stop(&hadc1);
		}
		else 
		{
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5,GPIO_PIN_RESET);
		}
	 if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)==1 & HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_0|GPIO_PIN_1)==0)
		{
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET); 
			HAL_ADC_Stop(&hadc1);
		}
		else 
		{
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5,GPIO_PIN_RESET);
		}
	 if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1)==1 & HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2|GPIO_PIN_0)==0)
		{
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
			HAL_ADC_Stop(&hadc1);
		}
		else  
		{
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5,GPIO_PIN_RESET);
		}
	}
	else  
	{
		Delay_ms(300);
		hienthi_adc();
		AD=810;
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5,GPIO_PIN_RESET);
	}
}
void Delay_ms(uint16_t ms){
	__HAL_TIM_SetCounter(&htim1,0);
	while(__HAL_TIM_GET_COUNTER(&htim1) < ms);
}