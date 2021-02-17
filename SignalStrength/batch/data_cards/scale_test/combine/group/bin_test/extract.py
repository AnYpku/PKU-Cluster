import re
import numpy as np
import sys
from math import sqrt
from numpy import sum
#group #bin num #channel #year
f=open('./txt/result_'+sys.argv[1]+'_'+sys.argv[3]+'_'+sys.argv[4]+'_bin'+sys.argv[2]+'.txt')
fout = open('./r_%s_%s_%s_bin%s.txt'%(sys.argv[3],sys.argv[4],sys.argv[1],sys.argv[2]),'w')
fout1 = open('./r_%s_%s_bin%s.txt'%(sys.argv[3],sys.argv[4],sys.argv[2]),'a')
f1=open('./all/r_'+sys.argv[3]+sys.argv[4]+'_bin'+sys.argv[2]+'.txt')
arr1=[]
for line in f1:
    line=line.split()
    arr1.append(float(line[0]))
    arr1.append(float(line[1]))
arr={}
for line in f:
        if not line.strip():
            continue
        line = line.replace(' ','')
        line= line.replace('(','')
        line= line.replace('68%','')
        line= line.replace(')','')
        line= line.replace('CL','')
	arr_Temp = re.split(':',line)
        name=arr_Temp[0]
        arr_Temp = re.split('/|-',arr_Temp[1])
#        print arr_Temp
        arr_Temp = np.array(arr_Temp[1:])
	arr_Temp = [float(x) for x in arr_Temp]
        arr[name]=arr_Temp
#print arr
print 'total unc. bin',sys.argv[2],sys.argv[3],sys.argv[4],arr1[0],' ',arr1[1]
print 'freeze ',sys.argv[1],' bin',sys.argv[2],' ',arr['Bestfitr'][0],' ',arr['Bestfitr'][1]
print '---------------------------------------------------\n'

#sys_up
#sys_down
if arr1[0]-arr['Bestfitr'][0]>0:
   sys_up=sqrt(arr1[0]*arr1[0]-arr['Bestfitr'][0]*arr['Bestfitr'][0])
else:
   sys_up=0
if arr1[1]-arr['Bestfitr'][1]>0:
   sys_down=sqrt(arr1[1]*arr1[1]-arr['Bestfitr'][1]*arr['Bestfitr'][1])
else:
   sys_down=0
a1=sum(arr1)/2
a=sum(arr['Bestfitr'])/2
sys1=sqrt(a1*a1-a*a)

fout.write('%s\t%0.4f\t%0.4f\t%0.4f\t%0.4f\n' %(sys.argv[1],arr['Bestfitr'][0],arr['Bestfitr'][1],sys_down,sys_up))
fout1.write('%s\t%0.4f\t%0.4f\n' %(sys.argv[1],sys_down,sys_up))
