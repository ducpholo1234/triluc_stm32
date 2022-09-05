	#ifndef __KALMAN1_H
	#define __KALMAN1_H

#include "stm32f2xx.h"
#include "string.h"
#include "math.h"
#include "main.h"

float _err_measure;
float _err_estimate;
float _q;
float _current_estimate;
float _last_estimate;
float _kalman_gain;

void SimpleKalmanFilter1(float mea_e,float est_e,float q);

float updateEstimate1(float mea);
void setMeasurementError1(float	mea_e);
void setEstimateError1(float est_e);
void setProcessNoise1(float q);
float getKalmanGain1();
float getEstimateError1();

void SimpleKalmanFilter1(float mea_e,float est_e,float q)
{
	_err_measure=mea_e;
	_err_estimate=est_e;
	_q=q;
}	
float updateEstimate1(float mea)
{

	_kalman_gain=(_err_estimate)/(_err_estimate + _err_measure);
	_current_estimate=(_last_estimate) + _kalman_gain*(mea - _last_estimate);
	_err_estimate=(1.0 - _kalman_gain)*_err_estimate + fabs(_last_estimate - _current_estimate)*_q;
	_last_estimate= (_current_estimate);
	return _current_estimate;
}	
void setMeasurementError1(float	mea_e)
{
	_err_measure=mea_e;
}
void setEstimateError1(float est_e)
{
	_err_estimate=est_e;
}
void setProcessNoise1(float q)
{
	_q=q;
}
float getKalmanGain1()
{
	return _kalman_gain;
}
float getEstimateError1()
{
	return _err_estimate;
}
#endif