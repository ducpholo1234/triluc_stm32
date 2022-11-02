#ifndef __ADCnew_H
#define __ADCnew_H
#include "stdint.h"
#include "stm32f2xx.h"
#include <stdio.h>
	void pump ();
	void compare();
	void energy();
	void data_send(float power,int count,int location);
	void du_lieu(float power,int count);
	void data_esp ();
	void test_led();
	void test_pump();
	void evenPunch ();
	void delay_ms(int time);
#endif 