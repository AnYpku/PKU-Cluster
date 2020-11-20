#!/usr/bin/env python

from ROOT import gROOT, THStack, TH1D, TList, TFile
import sys
from math import sqrt
from numpy import sum

def merge_bin(th1):
        nbins=th1.GetNbinsX()
        print 'nbins', nbins
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
f_TTA = TFile.Open(fdir+'hist_TTA16'+sys.argv[2]+'.root')
f_others = TFile.Open(fdir+'hist_others16'+sys.argv[2]+'.root')


th1_ZA_sig=f_EW.Get('hist')
th1_ZA=f_ZA.Get('hist')
th1_non_prompt=f_plj.Get('hist')
th1_others=f_others.Get('hist')

merge_year(th1_ZA_sig,'ZA-EWK')
merge_year(th1_ZA,'ZA')
merge_year(th1_non_prompt,'plj')
merge_year(th1_others,'others')

genbincontent=[]
genbinerror=[]
arr={}
f=open('/home/pku/anying/cms/PKU-Cluster/AQGC/batch/Uncer_aQGC/summary_uncer_'+sys.argv[2]+sys.argv[1]+'.txt')
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
nbins=th1_ZA_sig.GetNbinsX()
print 'nbins', nbins
merge_bin(th1_ZA_sig)
merge_bin(th1_ZA)
merge_bin(th1_non_prompt)
merge_bin(th1_others)

nbins=th1_ZA_sig.GetNbinsX()+1
print 'range in for loop 1 to', nbins
for i in range(1,nbins):
   f = open('./txt/%s_combine_bin%i.txt'%(sys.argv[2],i),'w')
   f.write('imax 1   number of channels\n')
   f.write('jmax 3   number of processes-1\n')
   if sys.argv[1].find("18") == -1:
	f.write('kmax 21  number of nuisance parameters (sources of systematical uncertainties)\n')
   else:
	f.write('kmax 19  number of nuisance parameters (sources of systematical uncertainties)\n')
   f.write('------------\n')
   f.write('# we have just one channel, in which we observe 0 events\n')
   f.write('bin %s%i\n'%(sys.argv[2],i))
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

   data= ZA_sig_bincontent + ZA_bincontent+non_prompt_bincontent+others_bincontent
   f.write('observation %0.2f\n'%(data))
   f.write('------------\n')
   f.write('# now we list the expected events for signal and all backgrounds in that bin\n')
   f.write('# the second process line must have a positive number for backgrounds, and 0 for signal\n')
   f.write('# then we list the independent sources of uncertainties, and give their effect (syst. error)\n')
   f.write('# on each process and bin\n')
   f.write('bin\t')
   f.write('%s%i\t%s%i\t%s%i\t%s%i\n'%(sys.argv[2],i,sys.argv[2],i,sys.argv[2],i,sys.argv[2],i))
   f.write('process\t')
   f.write('Sig\tQCD\tnon_prompt\tothers\n')
   f.write('process\t0\t1\t2\t3\n')
   f.write('rate\t')
   f.write('%0.2f\t%0.2f\t%0.2f\t%0.2f\n'%(ZA_sig_bincontent,ZA_bincontent, non_prompt_bincontent, others_bincontent))
   f.write('------------\n')
   print ZA_sig_bincontent,ZA_bincontent, non_prompt_bincontent, others_bincontent

   f.write('lumi_%s\tlnN\t'%(sys.argv[1]))
   if sys.argv[1].find("17")==-1 and sys.argv[1].find("18")==-1:
       f.write('%0.3f\t%0.3f\t-\t%0.3f\n'%(1.022,1.022,1.022))
   if sys.argv[1].find("16")==-1 and sys.argv[1].find("18")==-1:
       f.write('%0.3f\t%0.3f\t-\t%0.3f\n'%(1.02,1.02,1.02))
   if sys.argv[1].find("16")==-1 and sys.argv[1].find("17")==-1:
       f.write('%0.3f\t%0.3f\t-\t%0.3f\n'%(1.015,1.015,1.015))

   f.write('VBS_Stat_bin%d_%s%s\tlnN\t'%(i,sys.argv[2],sys.argv[1]))
   f.write('%0.2f\t-\t-\t-\n'%(ZA_sig_binerror))
   f.write('QCD_Stat_bin%d_%s%s\tlnN\t'%(i,sys.argv[2],sys.argv[1]))
   f.write('-\t%0.2f\t-\t-\n'%(ZA_binerror))

   f.write('non_prompt_Stat_bin%d_%s%s\tlnN\t'%(i,sys.argv[2],sys.argv[1]))
   f.write('-\t-\t%0.2f\t-\n'%(non_prompt_binerror))

   f.write('others_Stat_bin%d_%s%s\tlnN\t'%(i,sys.argv[2],sys.argv[1]))
   f.write('-\t-\t-\t%0.2f\n'%(others_binerror))

   f.write('fake_%s%s\tlnN\t'%(sys.argv[2],sys.argv[1]))
   if non_prompt_bincontent==0:
       f.write('-\t-\t-\t-\n')
   else: 
        f.write('-\t-\t%0.2f\t-\n'%(arr['fake'][i-1]))

   f.write('JES_%s\tlnN\t'%(sys.argv[1]))
   f.write('%0.2f\t%0.2f\t-\t%0.2f\n'%(arr['jes'+sys.argv[1]+'_ZA-EWK'][i-1],arr['jes'+sys.argv[1]+'_ZA'][i-1],arr['jes'+sys.argv[1]+'_others'][i-1]))

   f.write('JER_%s\tlnN\t'%(sys.argv[1]))
   f.write('%0.2f\t%0.2f\t-\t%0.2f\n'%(arr['jer'+sys.argv[1]+'_ZA-EWK'][i-1],arr['jer'+sys.argv[1]+'_ZA'][i-1],arr['jer'+sys.argv[1]+'_others'][i-1]))
#
   f.write('pdf_EW\tlnN\t')
   f.write('%0.2f\t-\t-\t-\n'%(arr['Sig_pdf'][i-1]))
#
   f.write('pdf_QCD\tlnN\t')
   f.write('-\t%0.2f\t-\t-\n'%(arr['QCD_pdf'][i-1]))
#
   f.write('Scale_EW\tlnN\t')
   f.write('%0.2f\t-\t-\t-\n'%(arr['Sig_scale'][i-1]))
#
   f.write('Scale_QCD\tlnN\t')
   f.write('-\t%0.2f\t-\t-\n'%(arr['QCD_scale'][i-1]))
#
   f.write('Scale_QCD_extra\tlnN\t')
   f.write('-\t%0.2f/%0.2f\t-\t-\n'%(arr['QCD_scale_up'][i-1],arr['QCD_scale_down'][i-1]))
#
   f.write('interf\tlnN\t')
   f.write('%0.2f\t-\t-\t-\n'%(arr['interf'][i-1]))
   
   if sys.argv[2].find("ele") == -1:
        f.write('mu_trigger%s\tlnN\t'%(sys.argv[1]))
#        f.write('mu_trigger\tlnN\t')
        f.write('%0.2f\t%0.2f\t-\t%0.2f\n'%(1.02,1.02,1.02))
        f.write('mu_eff\tlnN\t')
        f.write('%0.3f\t%0.3f\t-\t%0.3f\n'%(arr['muon_all'][0],arr['muon_all'][0],arr['muon_all'][0]))
#
   else:
        f.write('ele_reco\tlnN\t')
        f.write('%0.3f\t%0.3f\t-\t%0.3f\n'%(arr['ele_reco'][0],arr['ele_reco'][0],arr['ele_reco'][0]))
#
        f.write('ele_ID\tlnN\t')
        f.write('%0.2f\t%0.2f\t-\t%0.2f\n'%(arr['ele_ID'][0],arr['ele_ID'][0],arr['ele_ID'][0]))
#
   f.write('photon_id\tlnN\t')
   f.write('%0.3f\t%0.3f\t-\t%0.3f\n'%(arr['photon_ID'][0],arr['photon_ID'][0],arr['photon_ID'][0]))
#
   f.write('pileup\tlnN\t')
   f.write('1.01\t1.01\t-\t1.01\n')
#
   f.write('others_xs\tlnN\t')
   f.write('-\t-\t-\t1.1\n')
   if sys.argv[1].find("18") == -1:
        f.write('l1pref\tlnN\t')
        f.write('%0.2f\t%0.2f\t-\t%0.2f\n'%(arr['l1pref'][i-1],arr['l1pref'][i-1],arr['l1pref'][i-1]))

#   print 'bin ',i,' ',ZA_binerror,' ',non_prompt_binerror,' ',others_binerror,' 
   genbincontent[:]=[]
   genbinerror[:]=[]
   
