#! /usr/bin/env python

import sys
import os
import re

import ROOT
from ROOT import *

input_filename_e = '/afs/cern.ch/user/y/yian/work/PKU-Cluster/RunII2016/AQGC/ele/paramsets_'+sys.argv[1]+'_el.txt'
input_filename_m = '/afs/cern.ch/user/y/yian/work/PKU-Cluster/RunII2016/AQG/muon/paramsets_'+sys.argv[1]+'_mu.txt'
input_file_e = open(input_filename_e, "r")
input_file_m = open(input_filename_m, "r")

output_filename = 'wpwp_'+sys.argv[1]+'_scaling_refined.root'
outfile_newF = TFile.Open(output_filename,'RECREATE')
nGridPointsForNewF=200
par1GridMin = float(sys.argv[2])
par1GridMax = float(sys.argv[3])
newFormatInput1 = TH1D('aqgc_scaling_bin_1','aqgc_scaling_bin_1',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput2 = TH1D('aqgc_scaling_bin_2','aqgc_scaling_bin_2',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput3 = TH1D('aqgc_scaling_bin_3','aqgc_scaling_bin_3',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput4 = TH1D('aqgc_scaling_bin_4','aqgc_scaling_bin_4',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput5 = TH1D('aqgc_scaling_bin_5','aqgc_scaling_bin_5',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput6 = TH1D('aqgc_scaling_bin_6','aqgc_scaling_bin_6',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput7 = TH1D('aqgc_scaling_bin_7','aqgc_scaling_bin_7',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput8 = TH1D('aqgc_scaling_bin_8','aqgc_scaling_bin_8',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput9 = TH1D('aqgc_scaling_bin_9','aqgc_scaling_bin_9',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput10 = TH1D('aqgc_scaling_bin_10','aqgc_scaling_bin_10',nGridPointsForNewF,par1GridMin,par1GridMax)
hists = []
hists.append(newFormatInput1)
hists.append(newFormatInput2)
hists.append(newFormatInput3)
hists.append(newFormatInput4)
hists.append(newFormatInput5)
hists.append(newFormatInput6)
hists.append(newFormatInput7)
hists.append(newFormatInput8)
hists.append(newFormatInput9)
hists.append(newFormatInput10)

for l_num, l in enumerate(input_file_m):
	ll = re.split(r'[\s]',l)
	a2_m = float(ll[0])
	a1_m = float(ll[1])
	for bin_x in range(1,nGridPointsForNewF+1):
        	par1_value=hists[l_num].GetXaxis().GetBinCenter(bin_x)
	        yield_bin=1+a1_m*par1_value+a2_m*par1_value*par1_value
	        hists[l_num].SetBinContent(bin_x,yield_bin)
	hists[l_num].Write()


for l_num, l in enumerate(input_file_e):
	ll = re.split(r'[\s]',l)
	a2_e = float(ll[0])
	a1_e = float(ll[1])
	for bin_x in range(1,nGridPointsForNewF+1):
	        par1_value=hists[l_num+5].GetXaxis().GetBinCenter(bin_x)
        	yield_bin=1+a1_e*par1_value+a2_e*par1_value*par1_value
	        hists[l_num+5].SetBinContent(bin_x,yield_bin)
	hists[l_num+5].Write()
