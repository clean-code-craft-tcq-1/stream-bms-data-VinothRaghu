/* **************************************************************************************************
* File Name   : Receiver.c
* Author      : Abhijeet Chitagubbi
* Objective   :Read Temperature and Chargerate value from  from a file and calculate Min,Max and average.
* * ************************************************************************************************** */


/* **************************************** Standard Header Files **************************************************** */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* **************************************** Local Header Files **************************************************** */
#include "Receive.h"

/* **************************************** Declarations **************************************************** */
float Temperature[MAX_VAL] = {};
float ChargeRate[MAX_VAL] = {};
int linecount = 0;


/* **************************************** Function Pointer Array **************************************************** */
Receiver_State (*ReceiverDataRead[])(float Temperature[],float ChargeRate[])={ReadData};
Receiver_State(*ReceiverOutput[])(float Temperature[],float ChargeRate[])={OutToConsole};


/* **************************************** Read Values from File **************************************************** */
Receiver_State ReadData(float Temperature[],float ChargeRate[])
{

    float TempVal,ChargeRateVal = 0;
    int Index = 0;
    int Line_Identifier = 1;

    Receiver_State ReadStatus= FAIL;
    FILE * file=fopen( "BatteryRx.txt","r");
	
    if (file==NULL) 
    { 	
	printf("\t\t**DATA READ FAILURE**\t\t\n");
	ReadStatus= FAIL;  
    }
    else 
    {
        while(Line_Identifier != EOF)
         {
        	Line_Identifier = fscanf(file, "%f\t\t%f\n", &TempVal,&ChargeRateVal);
            	Temperature[Index]=TempVal;
            	ChargeRate[Index]=ChargeRateVal;
		Index++;
		linecount=Index;
          }
	    
        printf("\t\t**DATA READ PASS**\t\t\n");
        ReadStatus= PASS;
      }
    fclose(file);
    return ReadStatus;
}


/* **************************************** Input BMS Values  **************************************************** */
Receiver_State InputValue(Receiver_InType InVal)
{
    Receiver_State FileReadSuccess = FAIL;
    FileReadSuccess=(*ReceiverDataRead[InVal])(Temperature,ChargeRate);
    return FileReadSuccess;
}


/* **************************************** Output BMS Values **************************************************** */
Receiver_State OutputValue(Receiver_OutType OutVal)
{

    Receiver_State WriteStatus = FAIL;
    WriteStatus=(*ReceiverOutput[OutVal])(Temperature,ChargeRate);
    return WriteStatus;

}

/* **************************************** Output to Console **************************************************** */

Receiver_State OutToConsole(float Temperature[],float ChargeRate[])
{
	int avg_index =0;
	float TempAvg, ChargerateAvg, TempSum, ChargeSum = 0;
    for(int Index=0;Index<linecount;Index++)
    {
        printf("Temperature value == %f \t ChargeRate value == %f \t\n",Temperature[Index],ChargeRate[Index]);
	
    }
	
	while ( avg_index > 4 )
	{
		TempSum = Temperature[avg_index] +Temperature[avg_index-1]+Temperature[avg_index-2]+Temperature[avg_index-3]+Temperature[avg_index-4];
		ChargeSum = ChargeRate[avg_index] + ChargeRate[avg_index-1]  + ChargeRate[avg_index-2] + ChargeRate[avg_index-3] + ChargeRate[avg_index-4];
	}
	
	TempAvg = TempSum/5;
	ChargerateAvg = ChargeSum/5;
	
	printf(" SMA Temperature value == %f \n",TempAvg);
	printf(" SMA ChargerateAvg value == %f \n",ChargerateAvg);
	
    return PASS;
}
