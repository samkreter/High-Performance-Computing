import matplotlib.pyplot as plt
import numpy as np



data = np.genfromtxt('../hw3Data/avgTest.csv', delimiter=' ')
dataMultiFIle = np.genfromtxt('../hw3Data/avgMultiFile.csv',delimiter=' ')


plt.plot(data[0], data[1], 'ro-',label="Threads")
plt.plot(data[0], data[2], 'go-',label="OpenMP")
plt.plot(data[0], data[3], 'bo-',label="Process")


plt.axis([0,20, 0, .1])
plt.xticks(np.arange(0,20,2))

plt.xlabel('Number of Procs/Threads')
plt.ylabel('Time to Process')
plt.grid(True)
plt.title('Process Different Number of Threads/Procs')
plt.legend(loc='upper center', fancybox=True, shadow=True, ncol=5, fontsize=11)
fig1 = plt.gcf()


fig1.savefig('../hw3Data/multiProc.png')

plt.show()

plt.plot(dataMultiFIle[0],dataMultiFIle[1],'ro-',label="Threads")
plt.plot(dataMultiFIle[0],dataMultiFIle[3],'go-',label="OpenMP")
plt.plot(dataMultiFIle[0],dataMultiFIle[5],'bo-',label="Process")


plt.xlabel('Number of lines in file')
plt.ylabel('Time to Process')
plt.title('Process Different File Sizes')
#plt.axis([2000, 9000, 0, .45])
plt.grid(True)
plt.legend(loc='upper left', fancybox=True, shadow=True, ncol=5, fontsize=11)
fig2 = plt.gcf()
fig2.savefig('../hw3Data/multiFileProcessing.png')
plt.show()


plt.plot(dataMultiFIle[0],dataMultiFIle[2],'ro-',label="Threads")
plt.plot(dataMultiFIle[0],dataMultiFIle[4],'go-',label="OpenMP")
plt.plot(dataMultiFIle[0],dataMultiFIle[6],'bo-',label="Process")


plt.xlabel('Number of lines in file')
plt.ylabel('Time to Process')
plt.title('Parsing Different File Sizes')
# plt.axis([2000, 9000, 0, .45])
plt.grid(True)
plt.legend(loc='upper center', fancybox=True, shadow=True, ncol=5, fontsize=11)
fig3 = plt.gcf()
fig2.savefig('../hw3Data/multiFileReading.png')
plt.show()
