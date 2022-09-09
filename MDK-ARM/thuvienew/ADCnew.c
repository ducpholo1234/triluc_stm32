#include "ADCnew.h" 
#include "stdio.h"
#include "adc.h"
#include "dma.h"
#include "gpio.h"
#include "tim.h"
#include <stdio.h>
#include "main.h"
#include "math.h"

#define PI 3.1415926535

extern uint32_t AC;
extern uint32_t AD;
uint32_t LUC=0;
float LC;
int VT;
int AD23=0;
float dem=0;
/* ********************************so sanh dieu kien ADC va xac dinh vi tri dam ***************************************************/
void sosanh ()
{
	if(AC>865)
	{ 
		if(AD23==0)	
		{
			 if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_0)==1 & HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1|GPIO_PIN_2)==0)
					{
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);	
						VT=4;
						luc();
						HAL_TIM_Base_Start_IT(&htim4);
					}
			
			else if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1)==1 & HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_0|GPIO_PIN_2)==0)
					{
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET);						
						VT=3;
						luc();
						HAL_TIM_Base_Start_IT(&htim4);
					}
			else if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)==1 & HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1|GPIO_PIN_0)==0)
					{
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET);
						luc();
						VT=5;
					}
			else if (HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)==0 & HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1|GPIO_PIN_0)==1)
					{
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
						luc();
						VT=6;
						HAL_TIM_Base_Start_IT(&htim4);
						}
			else if(	HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_0)==1 & HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1|GPIO_PIN_2)==0)
			{
				if (HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)==0 & HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1|GPIO_PIN_0)==1)
					{
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
						luc();
						VT=6;
							HAL_TIM_Base_Start_IT(&htim4);
					}
				}
			else if(	HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1)==1 & HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_0|GPIO_PIN_2)==0)
			{
				if (HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)==0 & HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1|GPIO_PIN_0)==1)
					{
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,GPIO_PIN_SET);
						luc();
						VT=6;
							HAL_TIM_Base_Start_IT(&htim4);
					}
				}
			}
		}
	else  
		{
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6,GPIO_PIN_RESET);
		}
 }
	/* ********************************so sanh dieu kien bom khi**************************************************/
void bom ()
{
	if ( AC > 900)
	{
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
	}
	
 else if(AC <850)
	{
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_SET);	
	}
	else 
	{
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,GPIO_PIN_RESET);
	}
}
/* ******************************** tao ngat bang TIMER (0.2s)**************************************************/

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance ==TIM4)
	{
		AD23++;
		if(AD23==20)
		{
			AD23=0;
		dem=1.0*dem+1;
		HAL_TIM_Base_Stop_IT (&htim4);
		}
	}
}
void luc()
{
	if(LUC!=AC)
	{
		LUC=AC;
	}
		LC=(0.0004*PI*1000000*LUC)/4095; 
}
