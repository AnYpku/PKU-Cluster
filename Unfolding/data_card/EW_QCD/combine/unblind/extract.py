import re
import numpy as np
import sys
f=open('/data/pku/home/anying/cms/PKU-Cluster/Unfolding/data_card/EW_QCD/combine/unblind/result_'+sys.argv[1]+"_"+sys.argv[2]+'.txt')
fout = open('./r_%s_%s.txt'%(sys.argv[1],sys.argv[2]),'w')
fout1 = open('./s_%s_%s.txt'%(sys.argv[1],sys.argv[2]),'w')
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
        if len(arr_Temp)>3:
           arr_Temp = np.array(arr_Temp[1:])
           arr_Temp[0]='-'+arr_Temp[0]
           arr_Temp[1]='-'+arr_Temp[1]
	else:
           arr_Temp = np.array(arr_Temp[0:])
           arr_Temp[1]='-'+arr_Temp[1]
	arr_Temp = [float(x) for x in arr_Temp]
        print name,arr_Temp
        arr[name]=arr_Temp
print sys.argv[1],sys.argv[2]
print arr
print len(arr)
print len(arr['r_Bin1'])
n1=len(arr)+1
n2=len(arr['r_Bin1'])
fout1.write('\n')
for i in range(1,n1):
	fout.write('%0.3f\t'%(arr['r_Bin{}'.format(i)][0]))
	fout1.write('%s\t%0.3f\t'%('r_Bin{}'.format(i),arr['r_Bin{}'.format(i)][0]))
        for j in range(1,n2):
            fout.write('%0.3f\t'%(arr['r_Bin{}'.format(i)][j]))
            fout1.write('%0.3f\t'%(arr['r_Bin{}'.format(i)][j]))
            if j==n2-1:
                 fout.write('\n')
                 fout1.write('\n')
