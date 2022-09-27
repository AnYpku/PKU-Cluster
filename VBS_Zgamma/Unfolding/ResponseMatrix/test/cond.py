import numpy as np
from ROOT import gROOT, THStack, TH1D, TList, TFile
import sys
from math import sqrt
from numpy import sum
def get_con(hist):
	nrows=hist.GetNbinsY()
        ncols=hist.GetNbinsX()
	matrix = [[0 for i in xrange(nrows)] for i in xrange(ncols)]
        for i in range(0,nrows):
	    for j in range(0,ncols):
                matrix[i][j]=hist.GetBinContent(j+1,i+1)
        M = np.array(matrix) 
        result =  np.linalg.cond(M)
	print result
        print(M)
f=TFile.Open('rm_'+sys.argv[1]+sys.argv[2]+'.root')
hist=f.Get('hist_'+sys.argv[1])
print sys.argv[1],' ',sys.argv[2]
get_con(hist)
print '#################################################'

