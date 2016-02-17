import matplotlib.pyplot as plt
import numpy as np


data = np.genfromtxt('./_build/test.csv', delimiter=',')




plt.plot(data[0], data[1], 'ro-')

plt.axis([0, 20, 0, 1.5])

plt.xlabel('Number of Procs')
plt.ylabel('Time to Process')
plt.grid(True)
fig1 = plt.gcf()
#fig1.savefig('../../figs/test.png')
plt.show()
