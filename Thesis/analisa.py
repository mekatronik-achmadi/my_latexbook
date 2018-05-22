#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt

from scipy.interpolate import UnivariateSpline as usp

def second_dev(x,y,s_deg,k_deg,n_deg):
    
    plt.close("ori")
    plt.close("usp")
    plt.close("dev")
    
    plt.figure("ori")
    plt.semilogy(x,y,'ro')
    
    y_spl = usp(x,y,s=s_deg,k=k_deg)
    x_range = np.linspace(x[0],x[-1],1000)
    
    plt.figure("usp")
    plt.semilogy(x_range,y_spl(x_range))
    
    y_spl_2d = y_spl.derivative(n=n_deg)
    y_spl_final = usp(x_range,y_spl_2d(x_range),s=0.001,k=3)
    
    plt.figure("dev")
    plt.plot(x_range,y_spl_final(x_range))
    

tes00=np.genfromtxt('tes00-trace.dat')
tes10=np.genfromtxt('tes10-trace.dat')
tes01=np.genfromtxt('tes01-trace.dat')
tes11=np.genfromtxt('tes11-trace.dat')

nstart = 1800
nend = 16500

tes_x = tes00[nstart:nend,0]*1000
ndata = np.zeros(tes_x.shape[0])

for i in range(tes_x.shape[0]):
    ndata[i] = i

tes00y = tes00[nstart:nend,1]
tes10y = tes10[nstart:nend,1]
tes01y = tes01[nstart:nend,1]
tes11y = tes11[nstart:nend,1]

startn = 200
endn = 2400

second_dev(ndata[startn:endn],tes11y[startn:endn],0.075,3,1)