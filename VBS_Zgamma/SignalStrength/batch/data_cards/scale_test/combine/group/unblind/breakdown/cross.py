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
num=len(arr1)
s1=0
s2=0
for i in range(0,num-1):
   print arr1[i],arr2[i]
   one=arr1[i]*arr1[i]
   s1=s1+one
   two=arr2[i]*arr2[i]
   s2=s2+two
unc1=sqrt(s1)
unc2=sqrt(s2)
print arr1[num-1],arr2[num-1]
print unc1,' ',unc2


