#! /usr/bin/env python

import sys
import os
import re

import ROOT
from ROOT import *

input_filename_e16 = '/home/pku/anying/cms/PKU-Cluster/AQGC/batch/fit/txt/paramsets_'+sys.argv[1]+'_ele16.txt'
input_filename_m16 = '/home/pku/anying/cms/PKU-Cluster/AQGC/batch/fit/txt/paramsets_'+sys.argv[1]+'_muon16.txt'
input_filename_e17 = '/home/pku/anying/cms/PKU-Cluster/AQGC/batch/fit/txt/paramsets_'+sys.argv[1]+'_ele17.txt'
input_filename_m17 = '/home/pku/anying/cms/PKU-Cluster/AQGC/batch/fit/txt/paramsets_'+sys.argv[1]+'_muon17.txt'
input_filename_e18 = '/home/pku/anying/cms/PKU-Cluster/AQGC/batch/fit/txt/paramsets_'+sys.argv[1]+'_ele18.txt'
input_filename_m18 = '/home/pku/anying/cms/PKU-Cluster/AQGC/batch/fit/txt/paramsets_'+sys.argv[1]+'_muon18.txt'

input_file_e16 = open(input_filename_e16, "r")
input_file_m16 = open(input_filename_m16, "r")
input_file_e17 = open(input_filename_e18, "r")
input_file_m17 = open(input_filename_m18, "r")
input_file_e18 = open(input_filename_e18, "r")
input_file_m18 = open(input_filename_m18, "r")

output_filename = 'wpwp_'+sys.argv[1]+'_scaling_refined'+sys.argv[4]+'.root'
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
newFormatInput11 = TH1D('aqgc_scaling_bin_11','aqgc_scaling_bin_11',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput12 = TH1D('aqgc_scaling_bin_12','aqgc_scaling_bin_12',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput13 = TH1D('aqgc_scaling_bin_13','aqgc_scaling_bin_13',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput14 = TH1D('aqgc_scaling_bin_14','aqgc_scaling_bin_14',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput15 = TH1D('aqgc_scaling_bin_15','aqgc_scaling_bin_15',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput16 = TH1D('aqgc_scaling_bin_16','aqgc_scaling_bin_16',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput17 = TH1D('aqgc_scaling_bin_17','aqgc_scaling_bin_17',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput18 = TH1D('aqgc_scaling_bin_18','aqgc_scaling_bin_18',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput19 = TH1D('aqgc_scaling_bin_19','aqgc_scaling_bin_19',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput20 = TH1D('aqgc_scaling_bin_20','aqgc_scaling_bin_20',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput21 = TH1D('aqgc_scaling_bin_21','aqgc_scaling_bin_21',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput22 = TH1D('aqgc_scaling_bin_22','aqgc_scaling_bin_22',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput23 = TH1D('aqgc_scaling_bin_23','aqgc_scaling_bin_23',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput24 = TH1D('aqgc_scaling_bin_24','aqgc_scaling_bin_24',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput25 = TH1D('aqgc_scaling_bin_25','aqgc_scaling_bin_25',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput26 = TH1D('aqgc_scaling_bin_26','aqgc_scaling_bin_26',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput27 = TH1D('aqgc_scaling_bin_27','aqgc_scaling_bin_27',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput28 = TH1D('aqgc_scaling_bin_28','aqgc_scaling_bin_28',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput29 = TH1D('aqgc_scaling_bin_29','aqgc_scaling_bin_29',nGridPointsForNewF,par1GridMin,par1GridMax)
newFormatInput30 = TH1D('aqgc_scaling_bin_30','aqgc_scaling_bin_30',nGridPointsForNewF,par1GridMin,par1GridMax)
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
hists.append(newFormatInput11)
hists.append(newFormatInput12)
hists.append(newFormatInput13)
hists.append(newFormatInput14)
hists.append(newFormatInput15)
hists.append(newFormatInput16)
hists.append(newFormatInput17)
hists.append(newFormatInput18)
hists.append(newFormatInput19)
hists.append(newFormatInput20)
hists.append(newFormatInput21)
hists.append(newFormatInput22)
hists.append(newFormatInput23)
hists.append(newFormatInput24)
hists.append(newFormatInput25)
hists.append(newFormatInput26)
hists.append(newFormatInput27)
hists.append(newFormatInput28)
hists.append(newFormatInput29)
hists.append(newFormatInput30)
for l_num, l in enumerate(input_file_m16):
	ll = re.split(r'[\s]',l)
	a2_m = float(ll[0])
	a1_m = float(ll[1])
	for bin_x in range(1,nGridPointsForNewF+1):
        	par1_value=hists[l_num].GetXaxis().GetBinCenter(bin_x)#200 ponits from a range, get every point value which is the oprator value
	        yield_bin=1+a1_m*par1_value+a2_m*par1_value*par1_value#get aQGC/SM ratio
	        hists[l_num].SetBinContent(bin_x,yield_bin)
	hists[l_num].Write()#the first five histos are muon channel ZGmass bins in 16


for l_num, l in enumerate(input_file_e16):
	ll = re.split(r'[\s]',l)
	a2_e = float(ll[0])
	a1_e = float(ll[1])
	for bin_x in range(1,nGridPointsForNewF+1):
	        par1_value=hists[l_num+5].GetXaxis().GetBinCenter(bin_x)
        	yield_bin=1+a1_e*par1_value+a2_e*par1_value*par1_value
	        hists[l_num+5].SetBinContent(bin_x,yield_bin)
	hists[l_num+5].Write()#the last five histos are electron channel ZGmass bins in 16

for l_num, l in enumerate(input_file_m17):
	ll = re.split(r'[\s]',l)
	a2_m = float(ll[0])
	a1_m = float(ll[1])
	for bin_x in range(1,nGridPointsForNewF+1):
        	par1_value=hists[l_num+10].GetXaxis().GetBinCenter(bin_x)#200 ponits from a range, get every point value which is the oprator value
	        yield_bin=1+a1_m*par1_value+a2_m*par1_value*par1_value#get aQGC/SM ratio
	        hists[l_num+10].SetBinContent(bin_x,yield_bin)
	hists[l_num+10].Write()#the first five histos are muon channel ZGmass bins in 17

for l_num, l in enumerate(input_file_e17):
	ll = re.split(r'[\s]',l)
	a2_e = float(ll[0])
	a1_e = float(ll[1])
	for bin_x in range(1,nGridPointsForNewF+1):
	        par1_value=hists[l_num+15].GetXaxis().GetBinCenter(bin_x)
        	yield_bin=1+a1_e*par1_value+a2_e*par1_value*par1_value
	        hists[l_num+15].SetBinContent(bin_x,yield_bin)
	hists[l_num+15].Write()#the last five histos are electron channel ZGmass bins in 17

for l_num, l in enumerate(input_file_m18):
	ll = re.split(r'[\s]',l)
	a2_m = float(ll[0])
	a1_m = float(ll[1])
	for bin_x in range(1,nGridPointsForNewF+1):
        	par1_value=hists[l_num+20].GetXaxis().GetBinCenter(bin_x)#200 ponits from a range, get every point value which is the oprator value
	        yield_bin=1+a1_m*par1_value+a2_m*par1_value*par1_value#get aQGC/SM ratio
	        hists[l_num+20].SetBinContent(bin_x,yield_bin)
	hists[l_num+20].Write()#the first five histos are muon channel ZGmass bins in 18

for l_num, l in enumerate(input_file_e18):
	ll = re.split(r'[\s]',l)
	a2_e = float(ll[0])
	a1_e = float(ll[1])
	for bin_x in range(1,nGridPointsForNewF+1):
	        par1_value=hists[l_num+25].GetXaxis().GetBinCenter(bin_x)
        	yield_bin=1+a1_e*par1_value+a2_e*par1_value*par1_value
	        hists[l_num+25].SetBinContent(bin_x,yield_bin)
	hists[l_num+25].Write()#the last five histos are electron channel ZGmass bins  in 18
