/* **************************************************************************************************
* File Name   : Receiver.c
* Author      : Abhijeet Chitagubbi
* Objective   :Read Temperature and Chargerate value from  from a file and calculate Min,Max and average.
* * ************************************************************************************************** */

/**********************************************
Include header files
***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Receive.h"

/***********************************************************************************************************************
Variable declaration
**************************************************************************************************************************/
float MinimumAttributeValueArray[AttributeCount]= {100,100};
float MaximumAttributeValueArray[AttributeCount]= {0,0};
float Temperature[Max_ArraySize]={};
float ChargeRate[Max_ArraySize]={};
int   EntryCount=0;

/***************************************************************************************************************************
Function definitions
****************************************************************************************************************************/

/**************************************************************************************************************************
 * Function: BMS_Readfromdatafile
 * Description: This function reads the BMS parameter readings from the suitable 
   data log file and stores into a buffer  
 * input: void
 * returns: Read status is PASS(True) if the data is PASSfully read from the file.
 ***************************************************************************************************************************/
Status ReadfromConsole()
{
  FILE *Datafile;
  int line=1, Index=0;
  Status ReadStatus= FAIL;

  Datafile=fopen("./Receiver_TextFile/BatteryRx.txt", "r");
  if (Datafile==NULL)
    {
      printf("File open attempt failed\n");

    }
	
  else
    {

	float ReadTemperature=0,ReadChargeRate=0;
         printf("File open attempt PASSful\n");

	      while(line != EOF)
		{
		  line=fscanf(Datafile,"%f %f",&ReadTemperature,&ReadChargeRate);
		  Temperature[Index]=ReadTemperature;
		  ChargeRate[Index]=ReadChargeRate;
		  Index++;
		}
		EntryCount= Index;
		ReadStatus= PASS;
	    }
	
	fclose(Datafile);
	return ReadStatus;
}
/***********************************************************************************************************************************
 * Function: Calculate_TemperatureMinandMaxRange
 * Description: This function calculates the maximum and minimum range of temperature in a given
                data array.
 * input: The number of data values available.	  
 * returns: NULL, it prints the minimum and maximum value on the console
 ***********************************************************************************************************************************/

void Calc_TemperatureMinandMaxRange(int ParameterCount)
{
 Calc_MinParameterValue(Temperature, ParameterCount, &MinimumAttributeValueArray[0]);
 Calc_MaxParameterValue(Temperature, ParameterCount, &MaximumAttributeValueArray[0]);
 printf("Minimum and Maximum Temperature in the given range is %0.2f F and %0.2f F respectively\n",MinimumAttributeValueArray[0],MaximumAttributeValueArray[0]);
}


/**********************************************************************************************************************************
 * Function: Calculate_StateOfChargeMinandMaxRange
 * Description: This function calculates the maximum and minimum range of ChargeRate (State-Of-Charge) in a given
                data array. 
 * input: The number of data values available.  
 * returns: NULL, it prints the minimum and maximum value on the console
 **********************************************************************************************************************************/
void Calc_ChargeRateMinandMaxRange(int ParameterCount)
{
  
  Calc_MinParameterValue(ChargeRate, ParameterCount, &MinimumAttributeValueArray[1]);
  Calc_MaxParameterValue(ChargeRate, ParameterCount, &MaximumAttributeValueArray[1]);
  printf("Minimum and Maximum State-of-Charge in the given range is %0.2f%% and %0.2f%% respectively\n",MinimumAttributeValueArray[1],MaximumAttributeValueArray[1]);
}


/*****************************************************************************************************************************
 * Function: Calculate_MaxParameterValue
 * Description: This function calculates the maximum value of an attribute in a given range. 
 * input: The number of data values available, data values and the threshold/reference value.
 * returns: The maximum value in the given range
 ****************************************************************************************************************************/
 void Calc_MaxParameterValue(float AttributeValue[], int ParameterCount, float *MaximumAttributeValue)
 {
   for(int i=0; i< ParameterCount; i++)
   {
        if(AttributeValue[i] > *MaximumAttributeValue)
        {
            *MaximumAttributeValue = AttributeValue[i];
        }
   }
   
 }


/****************************************************************************************************************************
 * Function: Calculate_MinParameterValue
 * Description: This function calculates the minimum value of an attribute in a given range. 
 * input: The number of data values available, data values and the threshold/reference value.	  
 * returns: The minimum value in the given range
 ****************************************************************************************************************************/
void Calc_MinParameterValue(float AttributeValue[], int ParameterCount, float *MinimumAttributeValue)
 {
  for(int i=0; i< ParameterCount; i++)
   {
     
     if(AttributeValue[i] < *MinimumAttributeValue)
          {
              *MinimumAttributeValue = AttributeValue[i];
          }
   }
}


/*********************************************************************************************************************************
 * Function: Calculate_TemperatureSimpleMovingAverage
 * Description: This function calculates the average value of Temperature over latest 5 data points.   
 * input: The number of data values available.	  
 * returns: The average value of temperature in the given range
 *********************************************************************************************************************************/
void Calc_TemperatureSimpleMovingAverage(int ParameterCount)
{
  float Temperature_SMA= Calc_SimpleMovingAverage(Temperature, ParameterCount);
  printf("Simple moving average of Temperature is %0.2f F\n",Temperature_SMA);
}


/********************************************************************************************************************************
 * Function: Calculate_ChargeRateSimpleMovingAverage
 * Description: This function calculates the average value of ChargeRate over latest 5 data points.
 * input: The number of data values available	  
 * returns: The average value of temperature in the given range
 ******************************************************************************************************************************/
void Calc_ChargeRateSimpleMovingAverage(int ParameterCount)
{
  float ChargeRate_SMA= Calc_SimpleMovingAverage(ChargeRate, ParameterCount);
  printf("Simple moving average of ChargeRate is %0.2f%%\n",ChargeRate_SMA);
}



/***********************************************************************************************
 * Function: Calculate_SimpleMovingAverage
 * Description: This function calculates the average value of an attribute in a over latest 5 data points. 
 * input: The number of data values available.	  
 * returns: The average value of attribute in the given range
 ***********************************************************************************************/

float Calc_SimpleMovingAverage(float AttributeValue[], int ParameterCount)
{
  float AttributeAverage = 0;
  float AttributeSum = 0;
  for(int i=(ParameterCount-5); i< ParameterCount; i++)
   {
     AttributeSum+= AttributeValue[i];
     
   }
   AttributeAverage = AttributeSum/5;

   return AttributeAverage;
  
}



/******************************************************************************************************************************
 * Function: ReceiveDatafromSender
 * Description: This function reads the data from Sender, calculates the Min, max and average value of BMS_attribute.	  
 * returns: The operation was PASSful
 *****************************************************************************************************************************/
Status ReceiveDatafromSender ()
{
    Status ReadStatus= FAIL;
    ReadStatus= ReadfromConsole();
 
    if (ReadStatus)
    	{
	    
	    Calc_TemperatureMinandMaxRange(EntryCount);
	    
	    Calc_ChargeRateMinandMaxRange(EntryCount);
	    
	    Calc_TemperatureSimpleMovingAverage(EntryCount);
	   
	    Calc_ChargeRateSimpleMovingAverage(EntryCount);
        }
    return (ReadStatus);
}
