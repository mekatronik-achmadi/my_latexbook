#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt

tes_base=np.genfromtxt('data_base_a-trace.dat')

plt.figure()
plt.plot(tes_base[0:,1])
