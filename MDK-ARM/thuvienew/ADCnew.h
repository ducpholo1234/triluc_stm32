#ifndef __ADCnew_H
#define __ADCnew_H
#include "stdint.h"
#include "stm32f2xx.h"
#include <stdio.h>
	void pump ();
	void compare();
	void energy();
	void data_send(float power,int location);
#endif 