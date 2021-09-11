#!/usr/bin/env python

from ROOT import gROOT, THStack, TH1D, TList, TFile
import sys
from math import sqrt
from numpy import sum
def merge_bin(th1): 
        nbins=th1.GetNbinsX() 
        print 'nbins', nbins 
        th1.SetBinContent(nbins-2,th1.GetBinContent(nbins-2)+th1.GetBinContent(nbins-1)+th1.GetBinContent(nbins))
        if th1.GetBinContent(nbins-2)>0: 
           th1.SetBinError(nbins-2,sqrt(th1.GetBinError(nbins-2)*th1.GetBinError(nbins-2)+th1.GetBinError(nbins-1)*th1.GetBinError(nbins-1)+th1.GetBinError(nbins)*th1.GetBinError(nbins))) 
        else: 
           th1.SetBinError(nbins-2,0); 
 
print '-----begin to transfer TH2D to txt for Higgs-combine tool----- \n'

fdir = '../../../QCD/root/'
f_EW = TFile.Open(fdir+'hist_ZA-EWK_'+sys.argv[1]+sys.argv[2]+'.root')
f_ZA = TFile.Open(fdir+'hist_ZA_'+sys.argv[1]+sys.argv[2]+'.root')
f_interf = TFile.Open(fdir+'hist_ZA_interf_'+sys.argv[1]+sys.argv[2]+'.root')
f_plj = TFile.Open(fdir+'hist_plj_'+sys.argv[1]+sys.argv[2]+'.root')
f_TTA = TFile.Open(fdir+'hist_TTA_'+sys.argv[1]+sys.argv[2]+'.root')
f_VV = TFile.Open(fdir+'hist_VV_'+sys.argv[1]+sys.argv[2]+'.root')
f_ST = TFile.Open(fdir+'hist_ST_'+sys.argv[1]+sys.argv[2]+'.root')
if sys.argv[2].find("ele") == -1:
   f_Data = TFile.Open(fdir+'hist_DMuon_'+sys.argv[1]+sys.argv[2]+'.root')
else:
   f_Data = TFile.Open(fdir+'hist_DEle_'+sys.argv[1]+sys.argv[2]+'.root')

th1_ZA_sig_out=f_EW.Get('hist_sigout')
th1_ZA_sig=f_EW.Get('hist_sig')
th1_ZA=f_ZA.Get('hist_sig')
th1_interf=f_interf.Get('hist_sig')
th1_ZA.Add(th1_interf)
th1_ZAout=f_ZA.Get('hist_sigout')
th1_interfout=f_interf.Get('hist_sigout')
th1_ZAout.Add(th1_interfout)
th1_non_prompt=f_plj.Get('hist_bkg')
th1_TTA=f_TTA.Get('hist_bkg')
th1_VV=f_VV.Get('hist_bkg')
th1_ST=f_ST.Get('hist_bkg')
th1_Data=f_Data.Get("hist_bkg")
print 'get histograms'
th1_ZA_sig.Add(th1_ZA)
th1_ZA_sig_out.Add(th1_ZAout)
# the bkg histo and signal histo have already contain the overflow bin in the last bin when creat the histograms 
genbincontent=[]
genbinerror=[]
arr={}
f=open('../../../Uncer/EW_QCD/summary_uncer_'+sys.argv[2]+sys.argv[1]+'.txt')
import re
import numpy as np
for line in f:
        if not line.strip():
            continue
	print line
	line = line.replace('[','')
        line = line.replace(']','')
        line = line.replace('\n','')
	print line
	arr_Temp = re.split(',|=',line)
        print arr_Temp
	name = arr_Temp[0]
        arr_Temp = np.array(arr_Temp[1:])
	#arr_Temp.astype(np.float)
	arr_Temp = [float(x) for x in arr_Temp]
	print name
	arr[name]=arr_Temp
print arr 
print '>>>>begin to read bin content to the txt file>>>>'
merge_bin(th1_ZA_sig) 
merge_bin(th1_ZA_sig_out) 
merge_bin(th1_ZA) 
merge_bin(th1_non_prompt) 
merge_bin(th1_TTA) 
merge_bin(th1_VV) 
merge_bin(th1_ST) 
merge_bin(th1_Data)
nbins=th1_ZA_sig_out.GetNbinsX()-2+1
for i in range(1,nbins):
   f = open('./txt/%s_%s_bin%i.txt'%(sys.argv[2],sys.argv[1],i),'w')
   f.write('imax 1   number of channels\n')
   f.write('jmax 5   number of processes-1\n')
   if sys.argv[1].find("18") == -1 and sys.argv[1].find("17") == -1: #16
        f.write('kmax 21  number of nuisance parameters (sources of systematical uncertainties)\n')
   if sys.argv[1].find("16") == -1 and sys.argv[1].find("18") == -1: #17
        f.write('kmax 21  number of nuisance parameters (sources of systematical uncertainties)\n')
   if sys.argv[1].find("16") == -1 and sys.argv[1].find("17") == -1: #18
        f.write('kmax 20  number of nuisance parameters (sources of systematical uncertainties)\n')
   f.write('------------\n')
   f.write('# we have just one channel, in which we observe 0 events\n')
   f.write('bin %s%i\n'%(sys.argv[2],i))
# bincontent of each precess
   ST_bincontent = th1_ST.GetBinContent(i) if th1_ST.GetBinContent(i)>0 else 0
   TTA_bincontent = th1_TTA.GetBinContent(i) if th1_TTA.GetBinContent(i)>0 else 0
   VV_bincontent = th1_VV.GetBinContent(i) if th1_VV.GetBinContent(i)>0 else 0
   non_prompt_bincontent = th1_non_prompt.GetBinContent(i) if th1_non_prompt.GetBinContent(i)>0 else 0
   ZA_sig_bincontent = th1_ZA_sig.GetBinContent(i)  if th1_ZA_sig.GetBinContent(i)>0 else 0
   ZA_sig_out_bincontent = th1_ZA_sig_out.GetBinContent(i)  if th1_ZA_sig_out.GetBinContent(i)>0 else 0
# bin error

   ST_binerror = th1_ST.GetBinError(i)/ST_bincontent if ST_bincontent>0 else 0
   ST_binerror = ST_binerror if ST_binerror<1 else 1
   ST_binerror = ST_binerror+1

   TTA_binerror = th1_TTA.GetBinError(i)/TTA_bincontent if TTA_bincontent>0 else 0
   TTA_binerror = TTA_binerror if TTA_binerror<1 else 1
   TTA_binerror = TTA_binerror+1

   VV_binerror = th1_VV.GetBinError(i)/VV_bincontent if VV_bincontent>0 else 0
   VV_binerror = VV_binerror if VV_binerror<1 else 1
   VV_binerror = VV_binerror+1


   non_prompt_binerror = th1_non_prompt.GetBinError(i)/non_prompt_bincontent if non_prompt_bincontent>0 else 0
   non_prompt_binerror = non_prompt_binerror if non_prompt_binerror<1 else 1
   non_prompt_binerror =non_prompt_binerror+1

   ZA_sig_binerror = th1_ZA_sig.GetBinError(i)/ZA_sig_bincontent if ZA_sig_bincontent>0 else 0
   ZA_sig_binerror = ZA_sig_binerror if ZA_sig_binerror<1 else 1
   ZA_sig_binerror = ZA_sig_binerror+1

   ZA_sig_out_binerror = th1_ZA_sig_out.GetBinError(i)/ZA_sig_out_bincontent if ZA_sig_out_bincontent>0 else 0
   ZA_sig_out_binerror = ZA_sig_out_binerror if ZA_sig_out_binerror<1 else 1
   ZA_sig_out_binerror = ZA_sig_out_binerror+1

   data= th1_Data.GetBinContent(i)
   f.write('observation %0.3f\n'%(data))
   f.write('------------\n')
   f.write('# now we list the expected events for signal and all backgrounds in that bin\n')
   f.write('# the second process line must have a positive number for backgrounds, and 0 for signal\n')
   f.write('# then we list the independent sources of uncertainties, and give their effect (syst. error)\n')
   f.write('# on each process and bin\n')
   f.write('bin\t')
   f.write('%s%i\t%s%i\t%s%i\t%s%i\t%s%i\t%s%i\n'%(sys.argv[2],i,sys.argv[2],i,sys.argv[2],i,sys.argv[2],i,sys.argv[2],i,sys.argv[2],i))
   f.write('process\t')
   f.write('ZA\tnon_prompt\tTTA\tVV\tST\tSig_out\n')
   f.write('process\t0\t1\t2\t3\t4\t5\n')
   f.write('rate\t')
   f.write('%0.3f\t%0.3f\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(ZA_sig_bincontent, non_prompt_bincontent, TTA_bincontent, VV_bincontent, ST_bincontent, ZA_sig_out_bincontent))
   f.write('------------\n')

   f.write('lumi_%s\tlnN\t'%(sys.argv[1]))
   if sys.argv[1].find("17")==-1 and sys.argv[1].find("18")==-1:#16
       f.write('%0.3f\t%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\n'%(1.022,1.022,1.022,1.022,1.022))
   if sys.argv[1].find("16")==-1 and sys.argv[1].find("18")==-1:#17
       f.write('%0.3f\t%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\n'%(1.02,1.02,1.02,1.02,1.02))
   if sys.argv[1].find("16")==-1 and sys.argv[1].find("17")==-1:#18
       f.write('%0.3f\t%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\n'%(1.015,1.015,1.015,1.015,1.015))

   f.write('ZA_Stat_bin%d_%s%s\tlnN\t'%(i,sys.argv[2],sys.argv[1]))
   f.write('%0.3f\t-\t-\t-\t-\t-\n'%(ZA_sig_binerror))

   f.write('non_prompt_Stat_bin%d_%s%s\tlnN\t'%(i,sys.argv[2],sys.argv[1]))
   f.write('-\t%0.3f\t-\t-\t-\t-\n'%(non_prompt_binerror))

   f.write('TTA_Stat_bin%d_%s%s\tlnN\t'%(i,sys.argv[2],sys.argv[1]))
   f.write('-\t-\t%0.3f\t-\t-\t-\n'%(TTA_binerror))

   f.write('VV_Stat_bin%d_%s%s\tlnN\t'%(i,sys.argv[2],sys.argv[1]))
   f.write('-\t-\t-\t%0.3f\t-\t-\n'%(VV_binerror))

   f.write('ST_Stat_bin%d_%s%s\tlnN\t'%(i,sys.argv[2],sys.argv[1]))
   f.write('-\t-\t-\t-\t%0.3f\t-\n'%(ST_binerror))

   f.write('ZA_SigOut_Stat_bin%d_%s%s\tlnN\t'%(i,sys.argv[2],sys.argv[1]))
   f.write('-\t-\t-\t-\t-\t%0.3f\n'%(ZA_sig_out_binerror))
   f.write('Stat group = ZA_Stat_bin%d_%s%s  '%(i,sys.argv[2],sys.argv[1]))
   if non_prompt_bincontent>0:
      f.write('non_prompt_Stat_bin%d_%s%s '%(i,sys.argv[2],sys.argv[1]))
   if TTA_bincontent>0.1:
      f.write('TTA_Stat_bin%d_%s%s '%(i,sys.argv[2],sys.argv[1]))
   if VV_bincontent>0:
      f.write('VV_Stat_bin%d_%s%s '%(i,sys.argv[2],sys.argv[1]))
   if ST_bincontent>0:
      f.write('ST_Stat_bin%d_%s%s '%(i,sys.argv[2],sys.argv[1]))
   if ZA_sig_out_bincontent>0:
      f.write('ZA_SigOut_Stat_bin%d_%s%s '%(i,sys.argv[2],sys.argv[1]))
   f.write('\n')
   f.write('fake_%s%s\tlnN\t'%(sys.argv[2],sys.argv[1]))
   if non_prompt_bincontent==0:
       f.write('-\t-\t-\t-\t-\t-\n')
   else: 
        f.write('-\t%0.3f\t-\t-\t-\t-\n'%(arr['fake'+sys.argv[1]][i-1]))
        f.write('fake group = fake_%s%s \n'%(sys.argv[2],sys.argv[1]))

   f.write('JES_%s\tlnN\t'%(sys.argv[1]))
   f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(arr['jes'+sys.argv[1]+'_ZA'][i-1],arr['jes'+sys.argv[1]+'_TTA'][i-1],arr['jes'+sys.argv[1]+'_VV'][i-1],arr['jes'+sys.argv[1]+'_ST'][i-1],arr['jes'+sys.argv[1]+'_ZAout'][i-1]))

   f.write('JER_%s\tlnN\t'%(sys.argv[1]))
   f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(arr['jer'+sys.argv[1]+'_ZA'][i-1],arr['jer'+sys.argv[1]+'_TTA'][i-1],arr['jer'+sys.argv[1]+'_VV'][i-1],arr['jer'+sys.argv[1]+'_ST'][i-1],arr['jer'+sys.argv[1]+'_ZAout'][i-1]))
   f.write('JESR group = JES_%s JER_%s\n'%(sys.argv[1],sys.argv[1]))
#
   f.write('pdf_ZA\tlnN\t')
   f.write('%0.3f\t-\t-\t-\t-\t%0.3f\n'%(arr['ZA_pdf'][i-1],arr['SigOut_pdf'][i-1]))
#
   f.write('Scale_ZA\tlnN\t')
   f.write('%0.3f\t-\t-\t-\t-\t%0.3f\n'%(arr['ZA_scale'][i-1],arr['SigOut_scale'][i-1]))

   f.write('theory group = pdf_ZA  Scale_ZA\n')

   f.write('photon_id\tlnN\t')
   f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(arr['photon_ZA_ID'][i-1],arr['photon_TTA_ID'][i-1],arr['photon_VV_ID'][i-1],arr['photon_ST_ID'][i-1],arr['photon_ZA_ID'][i-1]))
#
   if sys.argv[2].find("ele") == -1: 
      f.write('mu_eff\tlnN\t')
      f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(arr['muon_ZA_all'][i-1],arr['muon_TTA_all'][i-1],arr['muon_VV_all'][i-1],arr['muon_ST_all'][i-1],arr['muon_ZA_all'][i-1]))
      f.write('mu_trigger\tlnN\t')
      f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(arr['muon_ZA_trigger'][i-1],arr['muon_TTA_trigger'][i-1],arr['muon_VV_trigger'][i-1],arr['muon_ST_trigger'][i-1],arr['muon_ZA_trigger'][i-1]))
      f.write('muon group = mu_eff mu_trigger\n')
#   
   else: 
      f.write('ele_reco\tlnN\t')
      f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(arr['ele_ZA_reco'][i-1],arr['ele_TTA_reco'][i-1],arr['ele_VV_reco'][i-1],arr['ele_ST_reco'][i-1],arr['ele_ZA_reco'][i-1]))
#
      f.write('ele_ID\tlnN\t')
      f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(arr['ele_ZA_ID'][i-1],arr['ele_TTA_ID'][i-1],arr['ele_VV_ID'][i-1],arr['ele_ST_ID'][i-1],arr['ele_ZA_ID'][i-1]))
      f.write('egamma group = ele_reco ele_ID photon_id\n')
#
   f.write('pileup\tlnN\t')
   f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(arr['pu_ZA'][i-1],arr['pu_TTA'][i-1],arr['pu_VV'][i-1],arr['pu_ST'][i-1],arr['pu_ZA'][i-1]))
#
   f.write('ttgamma_xs\tlnN\t')
   f.write('-\t-\t1.1\t-\t-\t-\n')

   f.write('VV_xs\tlnN\t')
   f.write('-\t-\t-\t1.1\t-\t-\n')
#
   f.write('pileupId_eff_%s\tlnN\t'%(sys.argv[1]))
   f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(arr['ZA_eff'][i-1],arr['TTA_eff'][i-1],arr['VV_eff'][i-1],arr['ST_eff'][i-1],arr['ZAout_eff'][i-1]))
#
   f.write('pileupId_mis_%s\tlnN\t'%(sys.argv[1]))
   f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(arr['ZA_mis'][i-1],arr['TTA_mis'][i-1],arr['VV_mis'][i-1],arr['ST_mis'][i-1],arr['ZAout_mis'][i-1]))
#
   f.write('Others group =  ttgamma_xs VV_xs \n')
   f.write('luminosity group = lumi_%s \n'%(sys.argv[1]))
   f.write('pileupId group = pileupId_mis_%s pileupId_eff_%s\n'%(sys.argv[1],sys.argv[1]))
   f.write('pu group = pileup \n')
   if sys.argv[1].find("18") == -1:
        f.write('l1pref\tlnN\t')
        f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(arr['l1pref_ZA'][i-1],arr['l1pref_TTA'][i-1],arr['l1pref_VV'][i-1],arr['l1pref_ST'][i-1],arr['l1pref_ZA'][i-1]))
        f.write('pref group = l1pref \n')
#   print 'bin ',i,' ',ZA_binerror,' ',non_prompt_binerror,' ',TTA_binerror,' ',VV_binerror,' ',ST_binerror,' ',WA_binerror,' ',ZA_sig_out_binerror
   genbincontent[:]=[]
   genbinerror[:]=[]
   


