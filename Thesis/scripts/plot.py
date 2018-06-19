#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt

tes_base=np.genfromtxt('tes_sm_10-trace.dat')
tes_0=np.genfromtxt('tes_sm_01-trace.dat')
tes_1=np.genfromtxt('tes_sm_11-trace.dat')

tes_x = tes_0[:,0]*1000
ndata = np.zeros(tes_x.shape[0])

plt.figure(0)
plt.plot(
        tes_x,tes_base[0:,1],'r',
        tes_x,tes_0[:,1],'b',
        tes_x,tes_1[:,1],'k'
     )