import matplotlib.pyplot as plt
import numpy as np



data = np.genfromtxt('test.csv', delimiter=',')
dataMultiFIle = np.genfromtxt('multiFile.csv',delimiter=',')





plt.plot(data[0], data[1], 'ro-')

plt.axis([0,20, 0, .3])
plt.xticks(np.arange(0,20,2))

plt.xlabel('Number of Procs')
plt.ylabel('Time to Process')
plt.grid(True)
fig1 = plt.gcf()
fig1.savefig('../figs/multiProc.png')

plt.show()

plt.plot(dataMultiFIle[0],[ np.log2(i) for i in dataMultiFIle[1]],'ro-')
plt.plot(dataMultiFIle[0],[ np.log2(i) for i in dataMultiFIle[2]],'go-')

plt.xlabel('Number of lines in file')
plt.ylabel('Time to Process')
# plt.axis([2000, 9000, 0, .45])
plt.grid(True)
fig2 = plt.gcf()
fig2.savefig('../figs/multiFile.png')
plt.show()

