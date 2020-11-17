import re
from math import sqrt
import numpy as np
import sys
f=open('/afs/cern.ch/user/y/yian/work/PKU-Cluster/SignalStrength/batch/data_cards/combine/breakdown/result_'+sys.argv[1]+'.txt')
fout = open('./r_%s.txt'%(sys.argv[1]),'w')
f1=open('/afs/cern.ch/user/y/yian/work/PKU-Cluster/SignalStrength/batch/data_cards/combine/breakdown/result_freeze_'+sys.argv[1]+'.txt')
f2=open('./r_sys_%s.txt' %(sys.argv[1]),'w')
arr1={}
for line in f1:
        if not line.strip():
            continue
        line = line.replace(' ','')
        line= line.replace('(','')
        line= line.replace('68%','')
        line= line.replace(')','')
	arr_Temp = re.split(':',line)
        name=arr_Temp[0]
        arr_Temp = re.split('/|-',arr_Temp[1])
#        print arr_Temp
        arr_Temp = np.array(arr_Temp[1:])
	arr_Temp = [float(x) for x in arr_Temp]
        arr1[name]=arr_Temp
print arr1
arr={}
for line in f:
        if not line.strip():
            continue
        line = line.replace(' ','')
        line= line.replace('(','')
        line= line.replace('68%','')
        line= line.replace(')','')
	arr_Temp = re.split(':',line)
        name=arr_Temp[0]
        arr_Temp = re.split('/|-',arr_Temp[1])
#        print arr_Temp
        arr_Temp = np.array(arr_Temp[1:])
	arr_Temp = [float(x) for x in arr_Temp]
        arr[name]=arr_Temp
print arr
#print len(arr)
print len(arr['r'])
print len(arr1['r'])
n1=len(arr)+1
n2=len(arr['r'])
sys_up=[]
sys_down=[]
for i in range(1,n1):
        for j in range(0,n2):
            if j==0:
                  sys_down.append(sqrt(arr['r'][j]**2-arr1['r'][j]**2))
            if j==1:
                  sys_up.append(sqrt(arr['r'][j]**2-arr1['r'][j]**2))
            fout.write('%0.3f\t'%(arr['r'][j]))
            
            if j==n2-1:
                 fout.write('\n')
print sys_down
print sys_up
for i in range (0,len(sys_up)):
      f2.write('%0.3f\t%0.3f\n'%(sys_down[i],sys_up[i]))
