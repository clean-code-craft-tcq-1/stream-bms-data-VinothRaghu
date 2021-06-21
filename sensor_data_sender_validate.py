# -*- coding: utf-8 -*-
"""
Created on Wed Jun  9 13:09:15 2021

@author: VNO1COB
"""
import random
import sender_types
import math

battery_threshold_limit = {'TEMPERATURE': [0, 80],
                        'SOC': [10, 90],
                        'CHARGERATE': [0, 0.8]} 

def random_number_generator(min,max):
  #Generates random numbers between min and max
  if isinstance((min+max) , int):
    return random.sample(range(min, max), 15)
  elif isinstance((min+max) , float):
    random_number=[]
    for i in range(15):
        random_number.append(random.uniform(min,max))
    return random_number   

def send_bms_data(battery_parameters,alert_type):
     if alert_type is math.nan:
         raise ValueError('Alert type is nan value')
     elif battery_parameters is math.nan:
         raise ValueError('battery parameter is nan value')    
     else:
         validate_bms_data(battery_parameters,alert_type)    
         for battery_parameter in battery_parameters:
             parameter_values = generate_bms_data(battery_parameter.upper())      
             publish_data(parameter_values,battery_parameter,alert_type.upper())
     return True
         

def validate_bms_data(battery_parameters,alert_type):
    validate_size(battery_parameters,alert_type)
    validate_bms_keys(battery_parameters,alert_type)
    validate_alertType_key(alert_type)
    
        

def validate_size(battery_parameters,alert_type):   
        if len(battery_parameters)== 0: 
            raise ValueError('Battery parameter is missing')
        elif len(alert_type) == 0:
            raise ValueError('Alert type is missing')
        

    
def validate_bms_keys(battery_parameters,alert_type):
        for item in battery_parameters:
            if not item.upper() in battery_threshold_limit.keys():
                raise KeyError('Given Battery paramenter is wrong')
            
def validate_alertType_key(alert_type):
        if not alert_type.upper() in sender_types.alertTarget_type.keys():
            raise KeyError("Given AlertType is wrong")             
            
def generate_bms_data(battery_parameter):
    min,max = battery_threshold_limit[battery_parameter]
    return random_number_generator(min,max)
 
def publish_data(parameter_values,battery_parameter,alert_type):
    return check_and_alert(parameter_values, battery_parameter,alert_type)

def check_and_alert(parameter_values, battery_parameter,alert_type):
  return (sender_types.alertTarget_type[alert_type](parameter_values,battery_parameter))   
   
