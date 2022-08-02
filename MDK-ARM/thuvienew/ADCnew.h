#ifndef __ADCnew_H
#define __ADCnew_H
#include "stdint.h"
#include "dma.h"

extern uint32_t AD;
void hienthi_adc();
	void XferCpltCallback(DMA_HandleTypeDef *hdma);
	void sosanh ();
//	void dieukien();
#endif 