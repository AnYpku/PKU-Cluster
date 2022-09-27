import re
from math import sqrt
import numpy as np
import sys
f=open('/data/pku/home/anying/cms/PKU-Cluster/Unfolding/data_card/EW_QCD/combine/breakdown/unblind/r_'+sys.argv[1]+"_"+sys.argv[2]+'.txt')
fout = open('./r_stat_%s_%s.txt'%(sys.argv[1],sys.argv[2]),'w')
f1=open('../../unblind/r_'+sys.argv[1]+"_"+sys.argv[2]+'.txt')
f2=open('./r_sys_%s_%s.txt' %(sys.argv[1],sys.argv[2]),'w')
arr1=[]
arr2=[]
arr3=[]
for line in f1:
    line=line.split()
#    print line
    arr1.append(float(line[1]))
    arr2.append(float(line[2]))
    arr3.append(float(line[0]))
print sys.argv[1],sys.argv[2],arr1
print sys.argv[1],sys.argv[2],arr2
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
        if len(arr_Temp)>3:
           arr_Temp = np.array(arr_Temp[2:])
           arr_Temp[0]='-'+arr_Temp[0]
        else:
           arr_Temp = np.array(arr_Temp[1:])
           arr_Temp[0]='-'+arr_Temp[0]
	arr_Temp = [float(x) for x in arr_Temp]
        arr[name]=arr_Temp
print arr
#print len(arr)
print len(arr['r_Bin1'])
n1=len(arr)+1
n2=len(arr['r_Bin1'])
#print len(arr1)
sys_up=[]
sys_down=[]
for i in range(1,n1):
        for j in range(0,n2):
            if j==0:
                  if abs(arr1[i-1])>abs(arr['r_Bin{}'.format(i)][j]):
                     dn_tmp=sqrt(arr1[i-1]**2-arr['r_Bin{}'.format(i)][j]**2) 
		  else:
                     dn_tmp=0
                  print sys.argv[1],sys.argv[2],' down unc. ',arr1[i-1],arr['r_Bin{}'.format(i)][j],dn_tmp
                  sys_down.append(dn_tmp)
            if j==1:
                  if abs(arr2[i-1])>abs(arr['r_Bin{}'.format(i)][j]):
                     up_tmp=sqrt(arr2[i-1]**2-arr['r_Bin{}'.format(i)][j]**2)                     
                  else:
                     up_tmp=0
                  print sys.argv[1],sys.argv[2],' up unc. ',arr2[i-1],arr['r_Bin{}'.format(i)][j],up_tmp
                  sys_up.append(up_tmp)
            fout.write('%0.3f\t'%(arr['r_Bin{}'.format(i)][j]))
            
            if j==n2-1:
                 fout.write('\n')
print ' dn unc. ',sys_down
print ' up unc. ',sys_up
for i in range (0,len(sys_up)):
      f2.write('%0.3f\t%0.3f\n'%(sys_down[i],sys_up[i]))
print '########################################################end##########################################'
