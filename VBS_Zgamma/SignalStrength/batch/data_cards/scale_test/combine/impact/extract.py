import re
import numpy as np
import sys
from math import sqrt
from numpy import sum
f=open('unc_impact_full'+sys.argv[1]+'_test.txt','r')
arr={}
for line in f:
    line = line.replace(':',' ')
    line = line.replace('"','')
    line = line.replace(',','')
    line = line.split()
    name = line[0]
    arr_Temp = np.array(line[2:])
    arr_Temp = [float(x) for x in arr_Temp]
    arr[name]=arr_Temp
#print arr
s=0
f1=open(sys.argv[2]+'_full'+sys.argv[1]+'_test.txt','r')
fout=open('all_unc'+sys.argv[1]+'.txt','a')
for line in f1:
    if not line.strip():
       continue
    line = line.split()
    print line[0]
    name=line[0]
    print arr[name]
    one=arr[name][0]*arr[name][0]
    s=s+one
unc=sqrt(s)
fout.write('%s\t%0.4f\n'%(sys.argv[2],unc))
print s,' ',unc

