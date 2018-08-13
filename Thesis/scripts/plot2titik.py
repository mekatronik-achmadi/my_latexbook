#!/usr/bin/python

#!/usr/bin/python

import sys
import numpy as np
import matplotlib.pyplot as plt

def sor_data(vinput,vbsc,vpoff):
	i_max = np.argmax(vinput[:,1],axis=0)
	rdata = vinput[i_max:,1]
	vdata = rdata + vpoff - vbsc
	return vdata
	
tes00=sor_data(np.genfromtxt('tes00-trace.dat'),77,17)
tes10=sor_data(np.genfromtxt('tes10-trace.dat'),77,17)
tes01=sor_data(np.genfromtxt('tes01-trace.dat'),77,17)
tes11=sor_data(np.genfromtxt('tes11-trace.dat'),77,17)

plt.figure()
plt.xlabel('data point (n)')
plt.ylabel('backscatter power (dB)')
plt.plot(
	tes00,'k',
	tes01,'r',
	tes10,'g',
	tes11,'b',
)
plt.show()


