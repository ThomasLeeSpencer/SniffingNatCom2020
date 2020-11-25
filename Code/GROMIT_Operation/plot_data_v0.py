# -*- coding: utf-8 -*-
"""
Created on July 2017

@author: jordi fonollosa
"""

import os
import numpy as np
import matplotlib.pyplot as plt
import csv
from datetime import datetime, timedelta
import matplotlib.gridspec as gridspec
import matplotlib.dates as mdates

os.chdir('C:/Users/adams/Documents/School/Spring 2018/ME 4699 Undergraduate Research/Testing/10%Ethanol/0.25Hz_90Deg_10000') # <<< your folder here

# close previous figures
plt.close("all")

plt.ion()

file2open = 'Flow2'

data1=[]
time_aux1=[]

with open(file2open, 'r') as f:
    reader = csv.reader(f, delimiter=',')
    next(reader, None)    
    
    for row in reader:
        print(len(row))
        if len(row)==18:
            aux=[]
            for i in range(0,18):
                aux.append(float(row[i]))
            data1.append(aux)
matrix1 = np.array(data1)        
            
time_laptop = matrix1[:,0]/1000.
time_arduino = matrix1[:,1]/1000.
time_sh = time_laptop

# Figure 1: T, RH, CO2 x2
plt.figure(figsize=(10,8))
gs = gridspec.GridSpec(4,10)
ax1=plt.subplot(gs[0,0:10])
ax2=plt.subplot(gs[1,0:10],sharex=ax1)
ax3=plt.subplot(gs[2,0:10],sharex=ax1)
ax4=plt.subplot(gs[3,0:10],sharex=ax1)
[a,b,c,d]=ax1.plot(time_sh, matrix1[:,2:6])
ax1.legend([a,b,c,d],['TGS2600','TGS2602','TGS2610','TGS2611'],bbox_to_anchor=(0.9,1.0), loc=2, borderaxespad=0.,prop={'size':10})
[a,b,c,d]=ax2.plot(time_sh, matrix1[:,6:10])
ax2.legend([a,b,c,d],['TGS2600','TGS2602','TGS2610','TGS2611'],bbox_to_anchor=(0.9,1.0), loc=2, borderaxespad=0.,prop={'size':10})
[a,b,c,d]=ax3.plot(time_sh, matrix1[:,10:14])
ax3.legend([a,b,c,d],['TGS2600','TGS2602','TGS2610','TGS2611'],bbox_to_anchor=(0.9,1.0), loc=2, borderaxespad=0.,prop={'size':10})
[a,b,c,d]=ax4.plot(time_sh, matrix1[:,14:18])
ax4.legend([a,b,c,d],['TGS2600','TGS2602','TGS2610','TGS2611'],bbox_to_anchor=(0.9,1.0), loc=2, borderaxespad=0.,prop={'size':10})

ax4.set_xlabel('Time (s)', fontsize=20)

ax1.text(0.95,0.01,'$V_{heater}=3.75V$',verticalalignment='bottom', horizontalalignment='right',transform=ax1.transAxes)
ax2.text(0.95,0.01,'$V_{heater}=4.39V$',verticalalignment='bottom', horizontalalignment='right',transform=ax2.transAxes)
ax3.text(0.95,0.01,'$V_{heater}=5.01V$',verticalalignment='bottom', horizontalalignment='right',transform=ax3.transAxes)
ax4.text(0.95,0.01,'$V_{heater}=5.62V$',verticalalignment='bottom', horizontalalignment='right',transform=ax4.transAxes)


plt.savefig(str(file2open)+'.png')
