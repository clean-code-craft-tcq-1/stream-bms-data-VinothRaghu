# -*- coding: utf-8 -*-
"""
Created on Wed Jun  9 17:55:43 2021

@author: VNO1COB
"""
import unittest
import sensor_data_sender_validate
import math

class test_battery_sender_readings(unittest.TestCase):
  
  def test_nan_alertType(self):
      with self.assertRaises(ValueError) as context:
            sensor_data_sender_validate.send_bms_data(["ChargeRate" ,"Temperature", "Soc"],math.nan)
      self.assertTrue('Alert type is nan value' in str(context.exception))
  def test_nan_batteryParameter(self):
      with self.assertRaises(ValueError) as context:
            sensor_data_sender_validate.send_bms_data(math.nan,"Console")
      self.assertTrue('battery parameter is nan value' in str(context.exception))
  
  def test_empty_alertType(self):
      with self.assertRaises(ValueError) as context:
            sensor_data_sender_validate.send_bms_data(["ChargeRate" ,"Temperature", "Soc"],"")
      self.assertTrue('Alert type is missing' in str(context.exception))
     
  def test_empty_batteryParam(self):
      with self.assertRaises(ValueError) as context:
            sensor_data_sender_validate.send_bms_data([],"Email")
      self.assertTrue('Battery parameter is missing' in str(context.exception)) 

  def test_wrong_alertType(self):
      with self.assertRaises(KeyError) as context:
            sensor_data_sender_validate.send_bms_data(["ChargeRate" ,"Temperature", "Soc"],"PDF")
      self.assertTrue('Given AlertType is wrong' in str(context.exception))
     
  def test_wrong_batteryParam(self):
      with self.assertRaises(KeyError) as context:
            sensor_data_sender_validate.send_bms_data(["Voltage" ,"Temperature", "Soc"],"Email")
      self.assertTrue('Given Battery paramenter is wrong' in str(context.exception))         
                    
    
  def test_battery_range(self):    
    self.assertTrue(sensor_data_sender_validate.send_bms_data(["Temperature","ChargeRate"],"Console"))    
    
  def test_alertType(self):
      self.assertTrue(sensor_data_sender_validate.send_bms_data(["Temperature", "Soc","ChargeRate"],"Console"))



if __name__ == '__main__':
    unittest.main()