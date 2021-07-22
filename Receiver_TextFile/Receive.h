/* **************************************************************************************************

* File Name   : Receive.h
* Author      : Abhijeet Chitagubbi

* * ************************************************************************************************** */

/**********************************************
Include header files
***********************************************/

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum {
  FAIL,
  PASS
} Status;

#define Max_ArraySize 1024
#define AttributeCount 2
extern float Temperature[Max_ArraySize];
extern float ChargeRate[Max_ArraySize];
extern int EntryCount;
extern float MinimumAttributeValueArray[AttributeCount];
extern float MaximumAttributeValueArray[AttributeCount];


extern Status ReadfromConsole();
extern void Calc_TemperatureMinandMaxRange(int ParameterCount);
extern void Calc_ChargeRateMinandMaxRange(int ParameterCount);
extern void Calc_MaxParameterValue(float AttributeValue[Max_ArraySize], int ParameterCount, float *MaximumAttributeValue);
extern void Calc_MinParameterValue(float AttributeValue[Max_ArraySize], int ParameterCount, float *MinimumAttributeValue);
extern void Calc_TemperatureSimpleMovingAverage(int ParameterCount);
extern void Calc_ChargeRateSimpleMovingAverage(int ParameterCount);
extern float Calc_SimpleMovingAverage(float AttributeValue[Max_ArraySize], int ParameterCount);
extern Status ReceiveDatafromSender();
