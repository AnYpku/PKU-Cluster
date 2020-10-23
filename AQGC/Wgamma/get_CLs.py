import sys
import os

fx=open('/afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/Wgamma/'+sys.argv[1]+'/list_point_'+sys.argv[1]+'.txt')
num=0
x=[]
xerr=[]
data=[]
err=[]
fout=open('./'+sys.argv[1]+'_CLs.txt','w')
for line in fx:
  print num, line
  filename = '/afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/Wgamma/'+sys.argv[1]+'/out/condor-'+sys.argv[1]+'.'+sys.argv[2]+'.'+str(num)+'.out'

  if (os.path.isfile(filename)):
     fy = open(filename, 'r')
     for l in fy:
      if l[0:3]=='CLs':
         elements = l.split()
#         print 'for job ',num,' aC parameter=',line,' CLs=',elements[2],' err=',elements[4]
         data.append(float(elements[2]))
         err.append(float(elements[4]))
     x.append(float(line))
     xerr.append(0)
     print x[-1],data[-1],err[-1]
     fout.write('%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(x[-1],data[-1],xerr[-1],err[-1]))
  else:
       ftmp='/afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/2016/run/combine/test/'+sys.argv[1]+'/out/condor-'+sys.argv[1]+'.'+sys.argv[2]+'.'+str(num)+'.out'
       print ftmp, 'does not exist'
  num=num+1
print num, 'jobs totally for operator', sys.argv[1] 
'''
import ROOT
from array import array
import numpy

g = ROOT.TGraphErrors(len(x), array('d',x), array('d',data), array('d',numpy.zeros(len(x))),array('d',err))

C=ROOT.TCanvas()
C.Draw()
g.Draw("ALE")

C.Print("results.pdf")
'''

