#! /usr/bin/env python

import sys
import os
import re

import ROOT
from ROOT import *

input_filename_e = '/afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/2017/ele/1bin/paramsets_'+sys.argv[1]+'_el.txt'
input_filename_m = '/afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/2017/muon/1bin/paramsets_'+sys.argv[1]+'_mu.txt'
input_file_e = open(input_filename_e, "r")
input_file_m = open(input_filename_m, "r")

output_filename = 'wpwp_'+sys.argv[1]+'_scaling_refined.root'
outfile_newF = TFile.Open(output_filename,'RECREATE')
nGridPointsForNewF=200
par1GridMin = float(sys.argv[2])
par1GridMax = float(sys.argv[3])
newFormatInput1 = TH1D('aqgc_scaling_bin_1','aqgc_scaling_bin_1',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput2 = TH1D('aqgc_scaling_bin_2','aqgc_scaling_bin_2',nGridPointsForNewF,par1GridMin,par1GridMax)
hists = []
hists.append(newFormatInput1)
hists.append(newFormatInput2)

for l_num, l in enumerate(input_file_m):
	ll = re.split(r'[\s]',l)
	a2_m = float(ll[0])
	a1_m = float(ll[1])
	for bin_x in range(1,nGridPointsForNewF+1):
        	par1_value=hists[l_num].GetXaxis().GetBinCenter(bin_x)#200 ponits from a range, get every point value which is the oprator value
	        yield_bin=1+a1_m*par1_value+a2_m*par1_value*par1_value#get aQGC/SM ratio
	        hists[l_num].SetBinContent(bin_x,yield_bin)
	hists[l_num].Write()#the first five histos are muon channel ZGmass bins


for l_num, l in enumerate(input_file_e):
	ll = re.split(r'[\s]',l)
	a2_e = float(ll[0])
	a1_e = float(ll[1])
	for bin_x in range(1,nGridPointsForNewF+1):
	        par1_value=hists[l_num+1].GetXaxis().GetBinCenter(bin_x)
        	yield_bin=1+a1_e*par1_value+a2_e*par1_value*par1_value
	        hists[l_num+1].SetBinContent(bin_x,yield_bin)
	hists[l_num+1].Write()#the last five histos are electron channel ZGmass bins
