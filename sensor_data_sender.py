# -*- coding: utf-8 -*-
"""
Created on Wed Jun  9 13:07:45 2021

@author: VNO1COB
"""
import sensor_data_sender_validate
   
def main():    
  sensor_data_sender_validate.send_bms_data(["ChargeRate" ,"Temperature"],"Console")
  


if __name__ == '__main__':
  main()  
