#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "Receive.h"

int lengthOfInputData=0;
minMax_st minMax_data;
float Temperature[MAX_SIZE]={};
float Charge_rate[MAX_SIZE]={};

//Receiver_State (*FindMinMaxofInput[])(float InputReading[])={Calc_MinValue,Calc_MaxValue};
	

Receiver_State ReadFromConsole(float Temperature[], float  Charge_rate[])
{
	char InputData[1024];
	Receiver_State ReadConsoleSuccess= FAIL;
   while (scanf("%s\n", InputData) !=EOF) 
   {
	  ReadConsoleSuccess= Process_ReadData(InputData, Temperature, Charge_rate);
   }
   return ReadConsoleSuccess;
}

Receiver_State Process_ReadData(char *InputData, float Temperature[], float Charge_rate[])
{
	int ResultComparetemp,ResultCompareCharge_rate=0;
	Receiver_State ProcessedDataSuccess= FAIL;
	Data_Type Data_Received;
	const char * InputArray_Dontprocess[] = { "Charge_rate","Temperature" };
	
	   ResultComparetemp=strcmp(InputData, InputArray_Dontprocess[0]); 
	   ResultCompareCharge_rate= strcmp(InputData, InputArray_Dontprocess[1]);
	   if(( ResultComparetemp == 0) )
	   {
		  ProcessedDataSuccess=PASS;
		  
  	   }
	   else
	   {
		 Data_Received = Temp_data;
		 ProcessedDataSuccess=  GetData(InputData, Temperature, Charge_rate, Data_Received );
	   }
	   
	    if( (ResultCompareCharge_rate ==0))
	   {
		  ProcessedDataSuccess=PASS;
		  
  	   }
	   else
	   {
		 Data_Received = ChargeRate;
		 ProcessedDataSuccess=  GetData(InputData, Temperature, Charge_rate, Data_Received );
	   }
	   
	   return ProcessedDataSuccess;
}  

Receiver_State GetData(char *InputData, float Temperature[], float Charge_rate[], Data_Type Data_Received)
{
	Receiver_State BatteryData= FAIL;
	Data_Type Data_Received;
	int InputStringlen=0;
	static int Temperature_index=0;
	static int Charge_rate_index=0;
	static int paramindex=0;
	
    InputStringlen = strlen(InputData);
    InputData[InputStringlen-1] = '\0';

    if(Data_Received == Temp_data )
    {
		while ( Temperature_index <= TEMP_READING_NUMBER )
			{
 	   Temperature[Temperature_index]= strtod(InputData,NULL);
	   printf("the value of the temp is %0.6f\n", Temperature[Temperature_index]);
	   Temperature_index++;
	   (void)Calc_MovingAverage(Temperature, Temperature_index);
		}
	   
	   BatteryData=PASS;
    }
	
    if(Data_Received == ChargeRate ) 
    {
		while ( Charge_rate_index <= CHARGERATE_READING_NUMBER )
		{
	   Charge_rate[Charge_rate_index]=strtod(InputData,NULL);
	   printf("the value of the Charge_rate is %0.6f\n", Charge_rate[Charge_rate_index]);
	   Charge_rate_index++;
	   (void)Calc_MovingAverage(Charge_rate,Charge_rate_index);
		}
	   
	   BatteryData=PASS;
    }
    paramindex++;


    return BatteryData;
		   
}


Receiver_State Calc_MinValue(float InputReading[])
{

	Receiver_State MinValue= FAIL;
	int Loop_index=0;
	minMax_data.min=InputReading[0];
	for(Loop_index=1; Loop_index< lengthOfInputData; Loop_index++)
	{
		if(minMax_data.min>InputReading[Loop_index])
			minMax_data.min=InputReading[Loop_index];
		MinValue=PASS;
	}
	printf("the value of the min is %f\n", minMax_data.min);
	return MinValue;
}

Receiver_State Calc_MaxValue(float InputReading[])
{
	Receiver_State MaxValue= FAIL;
	int Loop_index=0;
	minMax_data.max=InputReading[0];
	for(Loop_index=1; Loop_index<lengthOfInputData; Loop_index++)
	{
		if(minMax_data.max<InputReading[Loop_index])
			minMax_data.max=InputReading[Loop_index];
		MaxValue=PASS;
	}
	printf("the value of the max is %f\n", minMax_data.max);
	return MaxValue;
}

Receiver_State Calc_MovingAverage(float arrayvalue[], int lengthofData)
{
	static int Loop_counter=0;
	static int index=0;
	Receiver_State MovingAverage_Status= FAIL;
	float Average_Val=0;
    static int Modvalue=0;
	static int Array_index=0;
    float Average_Arr[1024]={};


    for(; (lengthofData>=5)&&(Loop_counter<lengthofData);Loop_counter++)
	 {
		Modvalue++;
		if(Modvalue%5==0)
		{
			Average_Val=arrayvalue[Loop_counter]+arrayvalue[Loop_counter-1]+arrayvalue[Loop_counter-2]+arrayvalue[Loop_counter-3]+arrayvalue[Loop_counter-4];
			Average_Val=(float)Average_Val/5.00;
		    Modvalue--;
		    Average_Arr[Array_index]=Average_Val;
			Array_index++;
		    MovingAverage_Status=PASS;
			
		}

	 }
	 for(; (lengthofData>=5)&&(index<lengthofData);index++)
     printf("the value of the average is %f\n", Average_Arr[index]);
	return MovingAverage_Status;
}
