import matplotlib.pyplot as plt
import numpy as np



data = np.genfromtxt('test.csv', delimiter=',')
dataMultiFIle = np.genfromtxt('multiFile.csv',delimiter=',')





plt.plot(data[0], data[1], 'ro-')

plt.axis([0, 20, 0, .3])

plt.xlabel('Number of Procs')
plt.ylabel('Time to Process')
plt.grid(True)
fig1 = plt.gcf()
fig1.savefig('../figs/multiProc.png')

plt.show()

plt.plot(dataMultiFIle[0],dataMultiFIle[1],'ro-')

plt.xlabel('Number of lines in file')
plt.ylabel('Time to Process')
plt.axis([2000, 9000, 0, .45])
plt.grid(True)
fig2 = plt.gcf()
fig2.savefig('../figs/multiFile.png')

plt.show()
