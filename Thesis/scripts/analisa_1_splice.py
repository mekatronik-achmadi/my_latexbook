#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt

pos = ['20','40','60','80']
vpos = [0,20,40,60,80]
place = ['05','10','15','20','25']


######################## End Event #############################

A_start = 3500
A_end = 4500

data_base = (
        np.genfromtxt('data_1_base_a-trace.dat')[A_start:A_end,1] +
        np.genfromtxt('data_1_base_b-trace.dat')[A_start:A_end,1] +
        np.genfromtxt('data_1_base_c-trace.dat')[A_start:A_end,1])/3
        
max_base = np.max(data_base)

for i in pos:
    for j in place:
        filepath_a = 'data_1_%s_%s_a-trace.dat' % (i,j)
        filepath_b = 'data_1_%s_%s_b-trace.dat' % (i,j)
        filepath_c = 'data_1_%s_%s_c-trace.dat' % (i,j)
            
        globals()['data_%s_%s' % (i,j)] = (
                np.genfromtxt(filepath_a)[A_start:A_end,1] +
                np.genfromtxt(filepath_b)[A_start:A_end,1] +
                np.genfromtxt(filepath_c)[A_start:A_end,1])/3
                
        globals()['d_%s_%s' % (i,j)] = np.abs(
                np.max(globals()['data_%s_%s' % (i,j)]) - 
                max_base
                )

displace_05 = np.zeros(1)
displace_10 = np.zeros(1)
displace_15 = np.zeros(1)
displace_20 = np.zeros(1)
displace_25 = np.zeros(1)

for i in place:            
    for j in pos:
        globals()['displace_%s' % i] = np.append([globals()['displace_%s' % i]],[globals()['d_%s_%s' % (j,i)]])
          
plt.figure()
plt.xlabel('position (cm)')
plt.ylabel('delta-power (dB)')
plt.plot(vpos,displace_05,'ro-',label='5mm')
plt.plot(vpos,displace_10,'go-',label='10mm')
plt.plot(vpos,displace_15,'bo-',label='15mm')
plt.plot(vpos,displace_20,'ko-',label='20mm')
plt.plot(vpos,displace_25,'yo-',label='25mm')
plt.legend(loc='best')
plt.show()
