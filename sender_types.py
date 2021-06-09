# -*- coding: utf-8 -*-
"""
Created on Wed Jun  9 13:13:09 2021

@author: VNO1COB
"""
import time

def check_and_alert(parameter_values, battery_parameter,alert_type):
  return (alertTarget_type[alert_type](parameter_values,battery_parameter))   
   
def send_to_console(parameter_values,battery_parameter):
  print(battery_parameter)
  for item in parameter_values:
      print(str(item))
      time.sleep(0.2)
  return True
  
def send_to_controller(breachType):
  header = 0xfeed
  print(f'{header}, {breachType}')
  return True   

def send_to_email(breachType):
   print("Hello}")
   return True

alertTarget_type = {
        'EMAIL': send_to_email,
        'CONTROLLER' : send_to_controller,
        'CONSOLE' : send_to_console
        }