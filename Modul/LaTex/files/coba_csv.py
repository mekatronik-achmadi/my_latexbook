#/usr/bin/python
import numpy as np
import matplotlib.pyplot as plt
x = np.around(np.linspace(0,1,20), decimals=2)
y = np.around(np.sin(x), decimals=2)
z = np.transpose((x,y))
np.savetxt('coba.csv', z, delimiter=';',fmt='%5.2f')
plt.plot(x,y)
plt.show()
