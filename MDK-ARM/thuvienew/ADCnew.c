#include "ADCnew.h" 
#include "stdio.h"
#include "adc.h"
#include "dma.h"
#include "gpio.h"
#include "tim.h"
#include "stdio.h"
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
 int count=0,count1;
int asymptotic_A,asymptotic_B,asymptotic_C;
uint8_t read_signal1,read_signal2,read_signal3,read_signal4,read_signal5;
uint8_t led_trai,led_phai,led_giua,led_duoi;

void du_lieu(float power,int location);
void dataSendEsp32(float power,int count,int location);
void data_send(float power,int count,int location);
void data_esp ();

char dataSend3[30];
char dataSend[15];
char data2Send[15];
char data_adc[5],data_position[5];

	void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance ==TIM4)
	{
		create_delay++;
		if(create_delay==20)
		{
			create_delay=0;
		HAL_TIM_Base_Stop_IT (&htim4);
			
		}
	}
		
}
/* ********************************ham tao tre bang timer ***************************************************/
void delay_1ms(void){
__HAL_TIM_SetCounter(&htim3, 0);
 while (__HAL_TIM_GetCounter(&htim3)<36000);
}
void delay_ms(int time)
{
while(time--)
{
	delay_1ms();
}
}
/* ********************************dinh nghia ca chan I/O ***************************************************/
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
	count1=count;
	define();
	if(ADC_value>850)
	{ 
		if(create_delay==0)	
		{
			 if(read_signal1)
					{
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,1);	
						location=4;
						HAL_TIM_Base_Start_IT(&htim4);
					}
			else if(read_signal2)
					{
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,1);						
						location=3;
						HAL_TIM_Base_Start_IT(&htim4);
					}
			else if(read_signal3)
					{
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);
						location=5;
						HAL_TIM_Base_Start_IT(&htim4);
					}
			else if (read_signal4)
					{
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,1);
						location=6;
						HAL_TIM_Base_Start_IT(&htim4);
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
/* ******************************** LUC DAM**************************************************/
void energy()
{
	if(ADC_punch!= AD)
	{
		ADC_punch=AD;
	}
power=(0.0004*PI*1000000*ADC_punch)/4095; 
}

/* ********************************truyen data toi esp32 ***************************************************/
void dataSendEsp32(float power,int count,int location){
	 
			char pData[]= "luc:";
			char cu_dam[]=" so dam:";		
			char count_value[5];
			char vi_tri[]=" vi tri: ";
			sprintf(data_adc,"%0.2f ",power);
			strcpy(dataSend,pData);
			strcat(dataSend,data_adc);
			HAL_UART_Transmit(&huart1, (uint8_t *)dataSend,strlen((char *)dataSend),10);
			sprintf(data_position," %d",count);
			strcpy(data2Send,cu_dam);
			strcat(data2Send,data_position);
			HAL_UART_Transmit(&huart1, (uint8_t *)data2Send,strlen((char *)data2Send),10);
			sprintf(count_value," %d ",location);
			strcpy(dataSend3,vi_tri);
			strcat(dataSend3,count_value);
			HAL_UART_Transmit(&huart1, (uint8_t *)dataSend3,strlen((char*)dataSend3),10);
}

void data_send(float power,int count,int location){
		dataSendEsp32(power,count,location);
}
/* ********************************vi tri dam, luc dam,truyen data toi esp32 ***************************************************/
void data_esp ()
{
	if (create_delay ==1)
	{
		count=1.0*count+1;
		energy();
		data_send(power,count,location);
	}
}

/* ********************************test lED ***************************************************/
void test_led()
{ 
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);
	delay_ms(1000);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0);
	delay_ms(1000);
}
/* ********************************test may bom***************************************************/
void test_pump ()
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6,1);
	delay_ms(1000);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6,0);
	delay_ms(1000);
}