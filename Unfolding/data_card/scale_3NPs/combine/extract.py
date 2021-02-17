import re
import numpy as np
import sys
f=open('/data/pku/home/anying/cms/PKU-Cluster/Unfolding/data_card/scale_3NPs/combine/result_'+sys.argv[1]+"_"+sys.argv[2]+'.txt')
fout = open('./r_%s_%s.txt'%(sys.argv[1],sys.argv[2]),'w')
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
        print arr_Temp
        arr_Temp = np.array(arr_Temp[1:])
	arr_Temp = [float(x) for x in arr_Temp]
        arr[name]=arr_Temp
print arr
print len(arr)
print len(arr['r_Bin1'])
n1=len(arr)+1
n2=len(arr['r_Bin1'])
for i in range(1,n1):
        for j in range(0,n2):
            fout.write('%0.3f\t'%(arr['r_Bin{}'.format(i)][j]))
            if j==n2-1:
                 fout.write('\n')
