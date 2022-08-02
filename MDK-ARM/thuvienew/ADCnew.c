#include "ADCnew.h" 
#include "stdio.h"
#include "adc.h"
#include "dma.h"
#include "gpio.h"
	uint32_t AD;
	uint16_t check=0;
//	uint32_t A,B,C,D;
void hienthi_adc()
	{
		HAL_ADC_Start(&hadc1);
		HAL_ADC_PollForConversion(&hadc1,10);
		AD=HAL_ADC_GetValue(&hadc1);
	}
	void XferCpltCallback (DMA_HandleTypeDef *hdma)
{
  AD=AD; //we reach this only if DMA transfer was correct
}

void sosanh ()
{
//	 A=AD+30;
//	 B=AD+40;
//	 C=AD+50;
//	 D=AD+60;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);
	if(AD>970)
	{ 
		AD=AD;		
		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0)==1 & HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1|GPIO_PIN_2)==0)
		{
				check=1;
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
		}
		else 
		{
		///		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);
		}
	 if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2)==1 & HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0|GPIO_PIN_1)==0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4,GPIO_PIN_SET); // thay dòng này
		}
		else 
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);
		}
	 if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1)==1 & HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2|GPIO_PIN_0)==0)
		{
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);
		}
		else  
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);
		}

	}
	else  
	{
		AD=940;
		 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);
	}
}
void dieukien ()
{
}
