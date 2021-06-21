#include <stdio.h>


typedef struct
{
	float min;
	float max;
}minMax_st;

typedef enum
{
	FAIL,
	PASS
}Receiver_State;

typedef enum
{
	Temperature,
	Charge_rate
}Data_Type;



#define MAX_SIZE 400
#define TEMP_READING_NUMBER	15
#define CHARGERATE_READING_NUMBER 15

extern float Temperature[MAX_SIZE];
extern float Charge_rate[MAX_SIZE];

extern int lengthOfInputData;
Receiver_State Calc_MaxValue(float InputReading[]);
Receiver_State Calc_MinValue(float InputReading[]);
Receiver_State GetData(char *InputData, float Temperature[], float Charge_rate[]);
Receiver_State Process_ReadData(char *InputData, float Temperature[], float Charge_rate[],Data_Type Data_Received );
Receiver_State Calc_MovingAverage(float arrayvalue[],int lengthofData);
Receiver_State ReadFromConsole(float Temperature[], float Charge_rate[]);
