import re
import numpy as np
import sys
#bin num #channel #year
f=open('./txt/result_'+sys.argv[2]+'_'+sys.argv[3]+'_bin'+sys.argv[1]+'.txt')
fout = open('./r_%s%s_bin%s.txt'%(sys.argv[2],sys.argv[3],sys.argv[1]),'w')
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
print sys.argv[1],' ',sys.argv[2],' ',sys.argv[3],' ',arr['Bestfitr'][0],'\t',arr['Bestfitr'][1]
fout.write('%0.4f\t%0.4f\n' %(arr['Bestfitr'][0],arr['Bestfitr'][1]))
