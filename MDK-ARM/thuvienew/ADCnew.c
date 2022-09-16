#include "ADCnew.h" 
#include "stdio.h"
#include "adc.h"
#include "dma.h"
#include "gpio.h"
#include "tim.h"
#include <stdio.h>
#include "main.h"
#include "math.h"
#include "usart.h"
#include "string.h"

#define PI 3.1415926535

extern uint32_t ADC_value;
extern uint32_t AD;
uint32_t ADC_punch=0;
float power;
int location;
int create_delay=0;
float count=0,*count1;
int asymptotic_A,asymptotic_B,asymptotic_C;
uint8_t read_signal1,read_signal2,read_signal3,read_signal4,read_signal5;
uint8_t led_trai,led_phai,led_giua,led_duoi;

void define()
{
	asymptotic_A=HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_0);
	asymptotic_B=HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1);
	asymptotic_C=HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2);
	read_signal1=(asymptotic_A==1 & asymptotic_B==0 & asymptotic_C==0);
	read_signal2=(asymptotic_B==1 & asymptotic_A==0 & asymptotic_C==0);
	read_signal3=(asymptotic_C==1 & asymptotic_A==0 & asymptotic_B==0);
	read_signal4=(asymptotic_C==0 & asymptotic_A==1 & asymptotic_B==1);
}
/* ********************************so sanh dieu kien ADC va xac dinh vi tri dam ***************************************************/
void compare ()
{
	define();
	if(ADC_value>870)
	{ 
		if(create_delay==0)	
		{
			 if(read_signal1)
					{
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1);	
						location=4;
						energy();
						count1=&count;
						data_send( power, location);
						HAL_TIM_Base_Start_IT(&htim4);
					}
			
			else if(read_signal2)
					{
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,1);						
						location=3;
						energy();
						count1=&count;
						data_send( power, location);
						HAL_TIM_Base_Start_IT(&htim4);
					}
			else if(read_signal3)
					{
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);
						energy();
						data_send( power, location);
						location=5;
					}
			else if (read_signal4)
					{
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,1);
						energy();
						location=6;
						data_send( power, location);
						HAL_TIM_Base_Start_IT(&htim4);
						}
			else if(	read_signal1)
			{
				if (read_signal4)
					{
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,1);
						energy();
						location=6;
						count1=&count;
						data_send( power, location);
						HAL_TIM_Base_Start_IT(&htim4);
					}
				}
			else if(read_signal2)
			{
				if (read_signal4)
					{
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,1);
						energy();
						location=6;
						data_send( power, location);
						HAL_TIM_Base_Start_IT(&htim4);
					}
				}
			}
		}
	else  
		{
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6,0);
		}
 }
	/* ********************************so sanh dieu kien bom khi**************************************************/
void pump ()
{	
	if ( ADC_value > 850)
	{
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,0);	
	}
 else if(ADC_value <830)
	{
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,1);
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1,0);		
	}
	else 
	{
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_7,0);
	}
}
/* ******************************** tao ngat bang TIMER (0.2s)**************************************************/

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance ==TIM4)
	{
		create_delay++;
		if(create_delay==30)
		{
			create_delay=0;
		count=1.0*count+1;
		HAL_TIM_Base_Stop_IT (&htim4);
		}
	}
}
void energy()
{
	if(ADC_punch!= AD)
	{
		ADC_punch=AD;
	}
		power=(0.0004*PI*1000000*ADC_punch)/4095; 
}


void dataSendEsp32(int location ,float power){
		  char data_adc[5],data_position[5],count_value[10];;
			char pData[]= "luc:";
			char vi_tri[]=" vi tri:";
			char cu_dam[]=" so cu dam:";
			char dataSend[30];
			char data2Send[30];	
			char data3Send[30];	
			sprintf(data_adc,"%0.2f ",power);
			sprintf(data_position," %d",location);
//			sprintf(count_value," %0.2f",*count1);
			strcpy(dataSend,pData);
			strcat(dataSend,data_adc);
			strcpy(data2Send,vi_tri);
			strcat(data2Send,data_position);
//			strcpy(data3Send,cu_dam);
//			strcat(data3Send,count_value);
			HAL_UART_Transmit(&huart1, (uint8_t *)dataSend,strlen((char *)dataSend),10);
			HAL_UART_Transmit(&huart1, (uint8_t *)data2Send,strlen((char *)data2Send),10);
//			HAL_UART_Transmit(&huart1, (uint8_t *)data3Send,strlen((char *)data3Send),10);
}
void data_send(float power,int location){
		
	 dataSendEsp32(location,power);
}