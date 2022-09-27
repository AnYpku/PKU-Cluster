import re
import numpy as np
import sys
from math import sqrt
from numpy import sum
f=open('/home/pku/anying/cms/PKU-Cluster/SignalStrength/batch/data_cards/scale_test/combine/group/unblind/breakdown/cwr/tmp_'+sys.argv[1]+"_"+sys.argv[2]+'.txt')
fout = open('./r_%s_%s.txt'%(sys.argv[1],sys.argv[2]),'w')
fout1 = open('./r_%s.txt'%(sys.argv[2]),'a')
arr={}
for line in f:
        if not line.strip():
            continue
#        print line
        line = line.replace(' ','')
        line= line.replace('tot','')
        line= line.replace('part','')
        if line.find("high")==-1:
           line= line.replace('low','')
           name='low'
	   arr_Temp = re.split('err',line)
           arr_Temp = np.array(arr_Temp[1:])
	   arr_Temp = [float(x) for x in arr_Temp]
           arr[name]=arr_Temp
        else:
           line= line.replace('high','')
           name='high'
	   arr_Temp = re.split('err',line)
           arr_Temp = np.array(arr_Temp[1:])
	   arr_Temp = [float(x) for x in arr_Temp]
           arr[name]=arr_Temp
#        print arr_Temp
#print sys.argv[2],sys.argv[1],arr
print 'total unc.',sys.argv[2],' ',arr['high'][0],arr['low'][0]
print 'freeze ',sys.argv[1],sys.argv[2],' ',arr['high'][1],' ',arr['low'][1]
print '---------------------------------------------------\n'
if abs(arr['high'][0])>abs(arr['high'][1]):
   sys_up=sqrt(arr['high'][0]*arr['high'][0]-arr['high'][1]*arr['high'][1])
else:
   sys_up=0
if abs(arr['low'][0])>abs(arr['low'][1]):
   sys_down=sqrt(arr['low'][0]*arr['low'][0]-arr['low'][1]*arr['low'][1])
else:
   sys_down=0
fout.write('%s\t%0.4f\t%0.4f\t%0.4f\t%0.4f\n' %(sys.argv[1],arr['high'][1],arr['low'][1],sys_down,sys_up))
fout1.write('%s\t%0.4f\t%0.4f\n' %(sys.argv[1],sys_up,sys_down))
