#! /usr/bin/env python

import sys
import os
import re

import ROOT
from ROOT import *

input_filename_16e = '/afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/2016/ele/paramsets_'+sys.argv[1]+'_el.txt'
input_filename_16m = '/afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/2016/muon/paramsets_'+sys.argv[1]+'_mu.txt'
input_filename_17e = '/afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/2017/ele/paramsets_'+sys.argv[1]+'_el.txt'
input_filename_17m = '/afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/2017/muon/paramsets_'+sys.argv[1]+'_mu.txt'
input_filename_18e = '/afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/2018/ele/paramsets_'+sys.argv[1]+'_el.txt'
input_filename_18m = '/afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/2018/muon/paramsets_'+sys.argv[1]+'_mu.txt'
input_file_16e = open(input_filename_16e, "r")
input_file_16m = open(input_filename_16m, "r")
input_file_17e = open(input_filename_17e, "r")
input_file_17m = open(input_filename_17m, "r")
input_file_18e = open(input_filename_18e, "r")
input_file_18m = open(input_filename_18m, "r")

output_filename = 'wpwp_'+sys.argv[1]+'_scaling_refined.root'
outfile_newF = TFile.Open(output_filename,'RECREATE')
nGridPointsForNewF=200
par1GridMin = float(sys.argv[2])
par1GridMax = float(sys.argv[3])

hists = []
for i in range(1,31):
	hists.append(ROOT.TH1D("aqgc_scaling_bin_{}".format(i),"aqgc_scaling_bin_{}".format(i),nGridPointsForNewF,par1GridMin,par1GridMax))

#########################2016#################################
for l_num, l in enumerate(input_file_16m):
	ll = re.split(r'[\s]',l)
	a2_16m = float(ll[0])
	a1_16m = float(ll[1])
	for bin_x in range(1,nGridPointsForNewF+1):
        	par1_value=hists[l_num].GetXaxis().GetBinCenter(bin_x)#200 ponits from a range, get every point value which is the oprator value
	        yield_bin=1+a1_16m*par1_value+a2_16m*par1_value*par1_value#get aQGC/SM ratio
	        hists[l_num].SetBinContent(bin_x,yield_bin)
	hists[l_num].Write()#the first five histos are muon channel ZGmass bins


for l_num, l in enumerate(input_file_16e):
	ll = re.split(r'[\s]',l)
	a2_16e = float(ll[0])
	a1_16e = float(ll[1])
	for bin_x in range(1,nGridPointsForNewF+1):
	        par1_value=hists[l_num+5].GetXaxis().GetBinCenter(bin_x)
        	yield_bin=1+a1_16e*par1_value+a2_16e*par1_value*par1_value
	        hists[l_num+5].SetBinContent(bin_x,yield_bin)
	hists[l_num+5].Write()#the last five histos are electron channel ZGmass bins
#########################2016#################################

#########################2017#################################
for l_num, l in enumerate(input_file_17m):
	ll = re.split(r'[\s]',l)
	a2_17m = float(ll[0])
	a1_17m = float(ll[1])
	for bin_x in range(1,nGridPointsForNewF+1):
        	par1_value=hists[l_num+10].GetXaxis().GetBinCenter(bin_x)#200 ponits from a range, get every point value which is the oprator value
	        yield_bin=1+a1_17m*par1_value+a2_17m*par1_value*par1_value#get aQGC/SM ratio
	        hists[l_num+10].SetBinContent(bin_x,yield_bin)
	hists[l_num+10].Write()#the first five histos are muon channel ZGmass bins

for l_num, l in enumerate(input_file_17e):
	ll = re.split(r'[\s]',l)
	a2_17e = float(ll[0])
	a1_17e = float(ll[1])
	for bin_x in range(1,nGridPointsForNewF+1):
	        par1_value=hists[l_num+15].GetXaxis().GetBinCenter(bin_x)
        	yield_bin=1+a1_17e*par1_value+a2_17e*par1_value*par1_value
	        hists[l_num+15].SetBinContent(bin_x,yield_bin)
	hists[l_num+15].Write()#the last five histos are electron channel ZGmass bins
#########################2017#################################

#########################2018#################################
for l_num, l in enumerate(input_file_18m):
	ll = re.split(r'[\s]',l)
	a2_18m = float(ll[0])
	a1_18m = float(ll[1])
	for bin_x in range(1,nGridPointsForNewF+1):
        	par1_value=hists[l_num+20].GetXaxis().GetBinCenter(bin_x)#200 ponits from a range, get every point value which is the oprator value
	        yield_bin=1+a1_18m*par1_value+a2_18m*par1_value*par1_value#get aQGC/SM ratio
	        hists[l_num+20].SetBinContent(bin_x,yield_bin)
	hists[l_num+20].Write()#the first five histos are muon channel ZGmass bins

for l_num, l in enumerate(input_file_18e):
	ll = re.split(r'[\s]',l)
	a2_18e = float(ll[0])
	a1_18e = float(ll[1])
	for bin_x in range(1,nGridPointsForNewF+1):
	        par1_value=hists[l_num+25].GetXaxis().GetBinCenter(bin_x)
        	yield_bin=1+a1_18e*par1_value+a2_18e*par1_value*par1_value
	        hists[l_num+25].SetBinContent(bin_x,yield_bin)
	hists[l_num+25].Write()#the last five histos are electron channel ZGmass bins
#########################2018#################################
