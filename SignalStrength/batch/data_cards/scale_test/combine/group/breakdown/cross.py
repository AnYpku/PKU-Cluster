import re
import numpy as np
import sys
from math import sqrt
from numpy import sum
f=open('./r_'+sys.argv[1]+'.txt','r')
arr1=[]
arr2=[]
arr3=[]
for line in f:
    line=line.split()
    arr1.append(float(line[1]))
    arr2.append(float(line[2]))
    arr3.append(float(line[3]))
num=len(arr1)
s=0
for i in range(0,num-1):
   print arr1[i]
   one=arr1[i]*arr1[i]
   s=s+one
unc=sqrt(s)
print s,'',unc


