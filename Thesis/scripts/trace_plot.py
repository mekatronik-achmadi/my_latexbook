#!/usr/bin/python

import sys
import numpy as np
import matplotlib.pyplot as plt

def sor_data(vinput,vbsc,vpoff):
	i_max = np.argmax(vinput[:,1],axis=0)
	rdata = vinput[i_max:,1]
	vdata = rdata + vpoff - vbsc
	return vdata

nametrace = sys.argv[1]
trace_input=np.genfromtxt(nametrace)

# backscatter coeffisient (BC) in positive
bsc = 77
# power loss min before offset
p_off= 17.012
# get SOR data
data_trace = sor_data(trace_input,bsc,p_off)

plt.figure()
plt.xlabel('data point (n)')
plt.ylabel('backscatter power (dB)')
plt.plot(data_trace,'k')
plt.show()
