#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Nov 14 14:44:31 2019

@author: achmadi
"""

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

def get_data(csv_file):
    np_data = pd.read_csv(csv_file,header=1).to_numpy()
    f_data = np_data[:,0]
    l_data = np_data[:,1]
    r_data = np_data[:,2]
    
    return np.vstack((f_data,l_data,r_data))
  
def value_data(fftdata,name=''):
    lmax = np.amax(fftdata[1])
    flmax = fftdata[0][np.argmax(fftdata[1])]
    
    rmax = np.amax(fftdata[2])
    frmax = fftdata[0][np.argmax(fftdata[2])]
    
    freq = (flmax + frmax)/2
    spl = (lmax + rmax)/2
    
    print('%s => freq: %d | spl: %d' % (name,freq,spl))
    return freq,spl

def plot_data(fftdata):
    plt.figure()
    
    plt.subplot(211)
    plt.plot(fftdata[0],fftdata[1],'r')
    plt.xscale('log')
    
    plt.subplot(212)
    plt.plot(fftdata[0],fftdata[2],'b')
    plt.xscale('log')

print('===============')
print('List Value 400Hz:')
value_data(get_data('day_4/newsine400.csv'),'sine400')
value_data(get_data('day_4/fft_sine2.csv'),'sine2')
value_data(get_data('day_4/fft_sine4.csv'),'sine4')
value_data(get_data('day_4/fft_sine8.csv'),'sine8')
value_data(get_data('day_4/fft_sine16.csv'),'sine16')
value_data(get_data('day_4/fft_sine32.csv'),'sine32')
value_data(get_data('day_4/fft_sine0p5.csv'),'sine0p5')
value_data(get_data('day_4/fft_sine0p25.csv'),'sine0p25')

# rangkuman nilai uji frekuensi
scale = np.array([0.25,0.5,1,2,4,8,16,32])
act_freq = np.array([86,172,387,732,1464,2971,5900,11800])  
exp_freq = np.array([100,200,400,800,1600,3200,6400,12800]) 
act_spl = np.array([92,96,97,101,110,91,90,85])

plt.figure()
plt.plot(scale,act_freq,'r-',label='actual')
plt.plot(scale,exp_freq,'b-',label='expected')
plt.xlabel('scaling ratio')
plt.ylabel('frequency (Hz)')
plt.legend(loc='upper left')

plt.figure()
plt.plot(act_freq,act_spl,'g-')
plt.xlabel('frequency (Hz)')
plt.xlim((0,16000))
plt.ylabel('SPL (dB))')
plt.ylim((0,180))

print('===============')
print('List Value 500Hz:')
value_data(get_data('day_4/500Hz/tone1.csv'),'tone1')
value_data(get_data('day_4/500Hz/tone05.csv'),'tone05')
value_data(get_data('day_4/500Hz/tone01.csv'),'tone01')
value_data(get_data('day_4/500Hz/tone005.csv'),'tone005')
value_data(get_data('day_4/500Hz/tone001.csv'),'tone001')
value_data(get_data('day_4/500Hz/tone0005.csv'),'tone0005')
value_data(get_data('day_4/500Hz/tone0001.csv'),'tone0001')
value_data(get_data('day_4/500Hz/tone00005.csv'),'tone00005')
value_data(get_data('day_4/500Hz/tone00001.csv'),'tone00001')

# rangkuman nilai uji amplitudo
sca_ampl = np.array([1,0.5,0.1,0.05,0.01,0.005,0.001,0.0005,0.0001])
act_ampl = np.array([98,82,72,72,58,51,42,47,42]) 

plt.figure()
plt.plot(sca_ampl,act_ampl,'b-')
plt.xlabel('scaling ')
plt.xscale('log')
plt.ylabel('SPL (dB))')
plt.ylim((0,180))