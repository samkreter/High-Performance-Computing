import matplotlib.pyplot as plt
import numpy as np


data = np.genfromtxt('_build/test.csv', delimiter=',')



plt.plot(data[0], data[1], 'ro-')
plt.axis([0, 20, 0, 0.2])
plt.show()