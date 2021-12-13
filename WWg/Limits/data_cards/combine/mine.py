#! /usr/bin/env python

import sys
import os
import re

import ROOT
from ROOT import *

output_filename = 'wpwp_'+sys.argv[1]+'_scaling_refined'+sys.argv[4]+'.root'
outfile_newF = TFile.Open(output_filename,'RECREATE')
nGridPointsForNewF=200
par1GridMin = float(sys.argv[2])
par1GridMax = float(sys.argv[3])

Ntot=24
hists = [ TH1D('aqgc_scaling_bin_'+str(i),'aqgc_scaling_bin_'+str(i),nGridPointsForNewF,par1GridMin,par1GridMax) for i in range(1,Ntot+1)]

#hists = []

#hists.append(newFormatInput1)
#hists.append(newFormatInput2)
#hists.append(newFormatInput3)
#hists.append(newFormatInput4)
#hists.append(newFormatInput5)
#hists.append(newFormatInput6)
#hists.append(newFormatInput7)
#hists.append(newFormatInput8)
#hists.append(newFormatInput9)
#hists.append(newFormatInput10)
#hists.append(newFormatInput11)
#hists.append(newFormatInput12)

for l_num in range(0,Ntot):
	for bin_x in range(1,nGridPointsForNewF+1):
        	par1_value=hists[l_num].GetXaxis().GetBinCenter(bin_x)#200 ponits from a range, get every point value which is the operator value
	        yield_bin=par1_value*par1_value #get aQGC/SM ratio
	        hists[l_num].SetBinContent(bin_x,yield_bin)
	hists[l_num].Write()#the first five histos are muon channel ZGmass bins
