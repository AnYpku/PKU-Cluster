#!/usr/bin/env python

from ROOT import gROOT, THStack, TH1D, TList, TFile
import sys
from math import sqrt
from numpy import sum

def merge_bin(th1):
        nbins=th1.GetNbinsX()
#        print 'nbins', nbins
        th1.SetBinContent(nbins,th1.GetBinContent(nbins)+th1.GetBinContent(nbins+1))
        if th1.GetBinContent(nbins)>0:
           th1.SetBinError(nbins,sqrt(th1.GetBinError(nbins)*th1.GetBinError(nbins)+th1.GetBinError(nbins+1)*th1.GetBinError(nbins+1)))
        else:
           th1.SetBinError(nbins,0);
def merge_year(th1,sample):
      f2=TFile.Open(fdir+'hist_'+sample+'17'+sys.argv[2]+'.root')
      f3=TFile.Open(fdir+'hist_'+sample+'18'+sys.argv[2]+'.root')
      th2=f2.Get("hist")
      th3=f3.Get("hist")
      th1.Add(th2)
      th1.Add(th3)
print '-----begin to transfer TH2D to txt for Higgs-combine tool----- \n'
fdir = '/home/pku/anying/cms/PKU-Cluster/AQGC/batch/hist_root/'
f_EW = TFile.Open(fdir+'hist_ZA-EWK16'+sys.argv[2]+'.root')
f_ZA = TFile.Open(fdir+'hist_ZA16'+sys.argv[2]+'.root')
f_plj = TFile.Open(fdir+'hist_plj16'+sys.argv[2]+'.root')
f_others = TFile.Open(fdir+'hist_others16'+sys.argv[2]+'.root')

th1_ZA_sig=f_EW.Get('hist')
th1_ZA=f_ZA.Get('hist')
th1_non_prompt=f_plj.Get('hist')
th1_others=f_others.Get('hist')
merge_year(th1_ZA_sig,'ZA-EWK')
merge_year(th1_ZA,'ZA')
merge_year(th1_non_prompt,'plj')
merge_year(th1_others,'others')
print 'get histograms'

genbincontent=[]
genbinerror=[]
arr={}
f=open('/home/pku/anying/cms/PKU-Cluster/AQGC/batch/Uncer_aQGC/summary_uncer_'+sys.argv[2]+sys.argv[1]+'.txt')
import re
import numpy as np
for line in f:
        if not line.strip():
            continue
        line = line.replace('[','')
        line = line.replace(']','')
        line = line.replace('\n','')
#      print line
        arr_Temp = re.split(',|=',line)
#        print arr_Temp
        name = arr_Temp[0]
        arr_Temp = np.array(arr_Temp[1:])
        arr_Temp = [float(x) for x in arr_Temp]
#       print name
        arr[name]=arr_Temp
#print arr 
print '>>>>begin to read bin content to the txt file>>>>'
nbins=th1_ZA_sig.GetNbinsX()
merge_bin(th1_ZA_sig)
merge_bin(th1_ZA)
merge_bin(th1_non_prompt)
merge_bin(th1_others)

nbins=th1_ZA_sig.GetNbinsX()+1
for i in range(1,nbins):
   f = open('./txt/%s%s_bin_%d.txt'%(sys.argv[2],sys.argv[1], i),'w')
   f.write('imax 1   number of channels\n')
   f.write('jmax 3   number of processes-1\n')
   f.write('kmax 23  number of nuisance parameters (sources of systematical uncertainties)\n')
   f.write('------------\n')
   f.write('# we have just one channel, in which we observe 0 events\n')
   f.write('bin %s%i\n'%(sys.argv[2],i))
   bin_content = th1_others.GetBinContent(i)+th1_non_prompt.GetBinContent(i)+th1_ZA.GetBinContent(i)+th1_ZA_sig.GetBinContent(i)
# bincontent of each precess
   others_bincontent = th1_others.GetBinContent(i) if th1_others.GetBinContent(i)>0 else 0
   non_prompt_bincontent = th1_non_prompt.GetBinContent(i) if th1_non_prompt.GetBinContent(i)>0 else 0
   ZA_bincontent = th1_ZA.GetBinContent(i) if th1_ZA.GetBinContent(i)>0 else 0
   ZA_sig_bincontent = th1_ZA_sig.GetBinContent(i)  if th1_ZA_sig.GetBinContent(i)>0 else 0
# bin error
   others_binerror = th1_others.GetBinError(i)/others_bincontent if others_bincontent>0 else 0
   others_binerror = others_binerror if others_binerror<1 else 1
   others_binerror = others_binerror+1

   non_prompt_binerror = th1_non_prompt.GetBinError(i)/non_prompt_bincontent if non_prompt_bincontent>0 else 0
   non_prompt_binerror = non_prompt_binerror if non_prompt_binerror<1 else 1
   non_prompt_binerror =non_prompt_binerror+1

   ZA_binerror = th1_ZA.GetBinError(i)/ZA_bincontent if ZA_bincontent>0 else 0
   ZA_binerror = ZA_binerror if ZA_binerror<1 else 1
   ZA_binerror = ZA_binerror+1

   ZA_sig_binerror = th1_ZA_sig.GetBinError(i)/ZA_sig_bincontent if ZA_sig_bincontent>0 else 0
   ZA_sig_binerror = ZA_sig_binerror if ZA_sig_binerror<1 else 1
   ZA_sig_binerror = ZA_sig_binerror+1


   f.write('observation %.2f\n'%bin_content)
   f.write('------------\n')
   f.write('# now we list the expected events for signal and all backgrounds in that bin\n')
   f.write('# the second process line must have a positive number for backgrounds, and 0 for signal\n')
   f.write('# then we list the independent sources of uncertainties, and give their effect (syst. error)\n')
   f.write('# on each process and bin\n')
   f.write('bin\t%s%i\t%s%i\t%s%i\t%s%i\n'%(sys.argv[2],i,sys.argv[2],i,sys.argv[2],i,sys.argv[2],i))
   f.write('process\tsig\tQCD\tnon_prompt\tothers\n')
   f.write('process\t0\t1\t2\t3\n')
   f.write('rate\t%0.2f\t%0.2f\t%0.2f\t%0.2f\n'%(ZA_sig_bincontent,ZA_bincontent, non_prompt_bincontent, others_bincontent))
   f.write('------------\n')
   f.write('lumi16\tlnN\t%0.3f\t%0.3f\t-\t%0.3f\t#lumi\n'%(arr['lumi16'][0],arr['lumi16'][0],arr['lumi16'][0]))
   f.write('lumi17\tlnN\t%0.3f\t%0.3f\t-\t%0.3f\t#lumi\n'%(arr['lumi17'][0],arr['lumi17'][0],arr['lumi17'][0]))
   f.write('lumi18\tlnN\t%0.3f\t%0.3f\t-\t%0.3f\t#lumi\n'%(arr['lumi18'][0],arr['lumi18'][0],arr['lumi18'][0]))
   if non_prompt_bincontent==0:
       f.write('fake_%s_%s\tlnN\t-\t-\t-\t-\t#0. uncertainty on %s%s\n'%(sys.argv[2],sys.argv[1],sys.argv[2],sys.argv[1]))
   else:
       f.write('fake_%s_%s\tlnN\t-\t-\t-\t-\t#0. uncertainty on %s%s\n'%(sys.argv[2],sys.argv[1],sys.argv[2],sys.argv[1]))
   f.write('VBS_stat_%s_%s_bin_%d\tlnN\t%0.2f\t-\t-\t-\n'%(sys.argv[2],sys.argv[1],i,ZA_sig_binerror))
   f.write('QCD_stat_%s_%s_bin_%d\tlnN\t-\t%0.2f\t-\t-\n'%(sys.argv[2],sys.argv[1],i,ZA_binerror))
   f.write('non_prompt_stat_%s_%s_bin_%d\tlnN\t-\t-\t%0.2f\t-\n'%(sys.argv[2],sys.argv[1],i,non_prompt_binerror))
   f.write('others_stat_%s_%s_bin_%d\tlnN\t-\t-\t-\t%0.2f\n'%(sys.argv[2],sys.argv[1],i,others_binerror))
   f.write('JES_%s\tlnN\t%0.2f\t%0.2f\t-\t%0.2f\n'%(sys.argv[1],arr['jes'+sys.argv[1]+'_ZA-EWK'][i-1],arr['jes'+sys.argv[1]+'_ZA'][i-1],arr['jes'+sys.argv[1]+'_others'][i-1]))
   f.write('JER_%s\tlnN\t%0.2f\t%0.2f\t-\t%0.2f\n'%(sys.argv[1],arr['jer'+sys.argv[1]+'_ZA-EWK'][i-1],arr['jer'+sys.argv[1]+'_ZA'][i-1],arr['jer'+sys.argv[1]+'_others'][i-1]))
   f.write('QCDZA_pdf\tlnN\t-\t%0.2f\t-\t-\n'%(arr['QCD_pdf'][i-1]))
   f.write('QCDZA_scale\tlnN\t-\t%0.2f\t-\t-\n'%(arr['Sig_scale'][i-1]))
   f.write('signal_pdf\tlnN\t%0.2f\t-\t-\t-\n'%(arr['Sig_pdf'][i-1]))
   f.write('signal_scale\tlnN\t%0.2f\t-\t-\t-\n'%(arr['Sig_scale'][i-1]))
   f.write('interference\tlnN\t%0.3f\t-\t-\t-\n'%(arr['interf'][i-1]))
   if sys.argv[2].find("ele") == -1:
      f.write('muon_all\tlnN\t%0.3f\t%0.3f\t-\t%0.3f\n'%(arr['muon_all'][0],arr['muon_all'][0],arr['muon_all'][0]))
      f.write('muon_trigger\tlnN\t%0.3f\t%0.3f\t-\t%0.3f\n'%(arr['muon_trigger'][0],arr['muon_trigger'][0],arr['muon_trigger'][0]))
   else:
      f.write('ele_ID\tlnN\t%0.3f\t%0.3f\t-\t%0.3f\n'%(arr['ele_ID'][0],arr['ele_ID'][0],arr['ele_ID'][0]))
      f.write('ele_reco\tlnN\t%0.3f\t%0.3f\t-\t%0.3f\n'%(arr['ele_reco'][0],arr['ele_reco'][0],arr['ele_reco'][0]))

   f.write('photon_id\tlnN\t%0.3f\t%0.3f\t-\t%0.3f\n'%(arr['photon_ID'][0],arr['photon_ID'][0],arr['photon_ID'][0]))
   f.write('l1prefiring\tlnN\t%0.3f\t%0.3f\t-\t%0.3f\n'%(arr['l1pref'][i-1],arr['l1pref'][i-1],arr['l1pref'][i-1]))
   f.write('puId_eff\tlnN\t%0.3f\t%0.3f\t-\t%0.3f\n'%(arr['ZA-EWK_eff'][i-1],arr['ZA_eff'][i-1],arr['others_eff'][i-1]))
   f.write('puId_mis\tlnN\t%0.3f\t%0.3f\t-\t%0.3f\n'%(arr['ZA-EWK_mis'][i-1],arr['ZA_mis'][i-1],arr['others_mis'][i-1]))
   f.write('pileup\tlnN\t1.02\t1.02\t-\t1.02\n')
   f.write('others_xs\tlnN\t-\t-\t-\t1.1\n')

   print 'bin ',i,' ',ZA_sig_binerror,' ',ZA_binerror,' ',non_prompt_binerror,' ',others_binerror

