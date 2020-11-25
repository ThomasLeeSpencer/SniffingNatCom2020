# -*- coding: utf-8 -*-
"""
Created on July 2017

@author: jordi fonollosa
"""

import datetime, threading, time
import serial
import os

######################
## Working directory
######################
os.chdir('C:/Users/adams/Documents/School/Spring 2018/ME 4699 Undergraduate Research/Testing/10%Ethanol/0.25Hz_90Deg_10000') # <<< your folder here

######################
## Specify here sampling time and total acquisition time
######################
sampling_time= 0.05 # in seconds. Minimum value 10ms
total_time = 210 #in seconds

######################
## open the serial port that your ardiono is connected to.
######################
ser = serial.Serial('COM3', 115200, timeout=0.5); # Establish the connection on a specific port
#ser.flushInput()
#ser.flushOutput()

print(ser.readline())
time.sleep(.1)
print(ser.readline())
time.sleep(.1)

######################
## Create / open file
######################
tini=time.strftime("%d-%m-%Y // %H:%M:%S")
print ("###"+tini)
fname1=time.strftime("%d%m%Y") ## The filename is the date of the day. 
fname2=time.strftime("%H%M%S") ## And the time.
fname = fname1+'_'+fname2
with open(fname, 'a') as fa:
    fa.write("###"+tini+'\n') ## Write the header for the new measurement in the file.
    

######################
## Start acquisition
######################
next_call = time.time()
time_ini = next_call

def foo():
  global next_call
  #print datetime.datetime.now()
  #print next_call
  next_call = next_call+sampling_time
  
  ser.write('R\n'.encode()) #request data 
  print(ser.read()) #uncomment this to print data on the terminal
  with open(fname, 'a') as fa:
      fa.write(str((next_call-time_ini)*1000.)+',')
      fa.write(ser.readline().decode()+'\n') #read incoming data and write it to the txt file
  
  #control sign. Execution is fine
  if (int(((next_call-time_ini)/sampling_time)%100)==0):
      print (((next_call-time_ini)/sampling_time))
  
  if (next_call<time_ini+total_time):
      threading.Timer( next_call - time.time(), foo ).start()
  else:
      ser.close() ## close the port

          


foo()







