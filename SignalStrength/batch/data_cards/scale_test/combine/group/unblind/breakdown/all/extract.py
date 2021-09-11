import re
import numpy as np
import sys
f=open('./tmp_all_full'+sys.argv[1]+'_test.txt')
fout = open('./r_%s.txt'%(sys.argv[1]),'w')
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
        print arr_Temp
        arr_Temp = np.array(arr_Temp[1:])
	arr_Temp = [float(x) for x in arr_Temp]
        arr[name]=arr_Temp
print arr
print arr['r'][0],'\t',arr['r'][1]
fout.write('%0.4f\t%0.4f\n' %(arr['r'][0],arr['r'][1]))
