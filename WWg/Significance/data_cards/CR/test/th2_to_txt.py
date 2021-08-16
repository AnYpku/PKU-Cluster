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
fdir = '/home/pku/anying/cms/PKU-Cluster/WWg/Significance/CR/root/'
f_WWg = TFile.Open(fdir+'hist_WWG_'+sys.argv[1]+'.root')
f_ZA = TFile.Open(fdir+'hist_ZGJets_'+sys.argv[1]+'.root')
f_plj = TFile.Open(fdir+'hist_plj_'+sys.argv[1]+'.root')
f_fakeL = TFile.Open(fdir+'hist_fakeLepton_'+sys.argv[1]+'.root')
f_TTA = TFile.Open(fdir+'hist_TTGJets_'+sys.argv[1]+'.root')
f_WA = TFile.Open(fdir+'hist_WGJets_'+sys.argv[1]+'.root')
f_VV = TFile.Open(fdir+'hist_VV_'+sys.argv[1]+'.root')
f_ST = TFile.Open(fdir+'hist_ST_'+sys.argv[1]+'.root')
f_tZq = TFile.Open(fdir+'hist_tZq_'+sys.argv[1]+'.root')

th1_WWg=f_WWg.Get('hist_sig')
th1_ZA=f_ZA.Get('hist_bkg')
th1_non_prompt=f_plj.Get('hist_bkg')
th1_fakeL=f_fakeL.Get('hist_bkg')
th1_TTA=f_TTA.Get('hist_bkg')
th1_WA=f_WA.Get('hist_bkg')
th1_VV=f_VV.Get('hist_bkg')
th1_ST=f_ST.Get('hist_bkg')
th1_tZq=f_tZq.Get('hist_bkg')
th1_ST.Add(th1_tZq)
th1_ST.Add(th1_TTA)
th1_ZA.Add(th1_WA)
# the bkg histo and signal histo have already contain the overflow bin in the last bin when creat the histograms 
genbincontent=[]
genbinerror=[]
arr={}
f=open('/home/pku/anying/cms/PKU-Cluster/WWg/Significance/Uncer/Top_CR/summary_uncer_'+sys.argv[1]+'.txt')
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
nbins=th1_WWg.GetNbinsX()
print 'nbins', nbins
#merge_bin(th1_ST)

nbins=th1_WWg.GetNbinsX()+1
print 'range in for loop 1 to', nbins
for i in range(1,nbins):
   f = open('./txt/emu_%s_CR_bin%i.txt'%(sys.argv[1],i),'w')
   f.write('imax 1   number of channels\n')
   f.write('jmax *   number of processes-1\n')
   f.write('kmax *  number of nuisance parameters (sources of systematical uncertainties)\n')
   f.write('------------\n')
   f.write('# we have just one channel, in which we observe 0 events\n')
   f.write('bin emu%s_%i\n'%(sys.argv[1],i))

# bincontent of each precess
   ST_bincontent = th1_ST.GetBinContent(i) if th1_ST.GetBinContent(i)>0 else 0
   TTA_bincontent = th1_TTA.GetBinContent(i) if th1_TTA.GetBinContent(i)>0 else 0
   VV_bincontent = th1_VV.GetBinContent(i) if th1_VV.GetBinContent(i)>0 else 0
   non_prompt_bincontent = th1_non_prompt.GetBinContent(i) if th1_non_prompt.GetBinContent(i)>0 else 0
   fakeL_bincontent = th1_fakeL.GetBinContent(i) if th1_fakeL.GetBinContent(i)>0 else 0
   ZA_bincontent = th1_ZA.GetBinContent(i) if th1_ZA.GetBinContent(i)>0 else 0
   WWg_bincontent = th1_WWg.GetBinContent(i)  if th1_WWg.GetBinContent(i)>0 else 0

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

   fakeL_binerror = th1_fakeL.GetBinError(i)/fakeL_bincontent if fakeL_bincontent>0 else 0
   fakeL_binerror = fakeL_binerror if fakeL_binerror<1 else 1
   fakeL_binerror = fakeL_binerror+1

   ZA_binerror = th1_ZA.GetBinError(i)/ZA_bincontent if ZA_bincontent>0 else 0
   ZA_binerror = ZA_binerror if ZA_binerror<1 else 1
   ZA_binerror = ZA_binerror+1

   WWg_binerror = th1_WWg.GetBinError(i)/WWg_bincontent if WWg_bincontent>0 else 0
   WWg_binerror = WWg_binerror if WWg_binerror<1 else 1
   WWg_binerror = WWg_binerror+1

   data= WWg_bincontent + ZA_bincontent+non_prompt_bincontent+fakeL_bincontent+TTA_bincontent+VV_bincontent+ST_bincontent
   f.write('observation %0.3f\n'%(data))
   f.write('------------\n')
   f.write('# now we list the expected events for signal and all backgrounds in that bin\n')
   f.write('# the second process line must have a positive number for backgrounds, and 0 for signal\n')
   f.write('# then we list the independent sources of uncertainties, and give their effect (syst. error)\n')
   f.write('# on each process and bin\n')
   f.write('bin\t')
   f.write('emu%s_%i\temu%s_%i\temu%s_%i\temu%s_%i\temu%s_%i\temu%s_%i\n'%(sys.argv[1],i,sys.argv[1],i,sys.argv[1],i,sys.argv[1],i,sys.argv[1],i,sys.argv[1],i))
   f.write('process\t')
   f.write('Sig\tVA\tNonprompt_photon\tNonprompt_lepton\tVV\tTop\n')
   f.write('process\t0\t1\t2\t3\t4\t5\n')
   f.write('rate\t')
   f.write('%0.3f\t%0.3f\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(WWg_bincontent,ZA_bincontent, non_prompt_bincontent,fakeL_bincontent, VV_bincontent, ST_bincontent))
   f.write('------------\n')

   f.write('lumi_%s\tlnN\t'%(sys.argv[1]))
   f.write('%0.3f\t%0.3f\t-\t-\t%0.3f\t%0.3f\n'%(1.016,1.016,1.016,1.016))

   f.write('WWG_Stat_CR_bin%d_%s\tlnN\t'%(i,sys.argv[1]))
   f.write('%0.3f\t-\t-\t-\t-\t-\n'%(WWg_binerror))
   f.write('VA_Stat_CR_bin%d_%s\tlnN\t'%(i,sys.argv[1]))
   f.write('-\t%0.3f\t-\t-\t-\t-\n'%(ZA_binerror))

   f.write('Nonprompt_photon_Stat_CR_bin%d_%s\tlnN\t'%(i,sys.argv[1]))
   f.write('-\t-\t%0.3f\t-\t-\t-\n'%(non_prompt_binerror))

   f.write('Nonprompt_lepton_Stat_CR_bin%d_%s\tlnN\t'%(i,sys.argv[1]))
   f.write('-\t-\t-\t%0.3f\t-\t-\t-\n'%(fakeL_binerror))

   f.write('VV_Stat_CR_bin%d_%s\tlnN\t'%(i,sys.argv[1]))
   f.write('-\t-\t-\t-\t%0.3f\t-\n'%(VV_binerror))

   f.write('Top_Stat_CR_bin%d_%s\tlnN\t'%(i,sys.argv[1]))
   f.write('-\t-\t-\t-\t-\t%0.3f\n'%(ST_binerror))

   f.write('fakelepton_unc\tlnN\t')
   if fakeL_bincontent==0:
      f.write('-\t-\t-\t-\t-\t-\n')
   else:
      f.write('-\t-\t1.3\t-\t-\t-\n')

   f.write('fakephoton_%s\tlnN\t'%(sys.argv[1]))
   if non_prompt_bincontent==0:
       f.write('-\t-\t-\t-\t-\t-\n')
   else: 
        f.write('-\t-\t%0.3f\t-\t-\t-\n'%(arr['fakephoton'+sys.argv[1]][i-1]))

   f.write('JES_%s\tlnN\t'%(sys.argv[1]))
   f.write('%0.3f\t%0.3f\t-\t-\t%0.3f\t%0.3f\n'%(arr['jesTotal'+'_WWG'][i-1],arr['jesTotal'+'_ZGJets'][i-1],arr['jesTotal'+'_VV'][i-1],arr['jesTotal'+'_Top'][i-1]))

   f.write('JER_%s\tlnN\t'%(sys.argv[1]))
   f.write('%0.3f\t%0.3f\t-\t-\t%0.3f\t%0.3f\n'%(arr['jer1'+'_WWG'][i-1],arr['jer1'+'_ZGJets'][i-1],arr['jer1'+'_VV'][i-1],arr['jer1'+'_Top'][i-1]))

   f.write('pileup_%s\tlnN\t'%(sys.argv[1]))
   f.write('%0.3f\t%0.3f\t-\t-\t%0.3f\t%0.3f\n'%(arr['pu'+'_WWG'][i-1],arr['pu'+'_ZGJets'][i-1],arr['pu'+'_VV'][i-1],arr['pu'+'_Top'][i-1]))

   f.write('mu_trigger\tlnN\t')
   f.write('%0.3f\t%0.3f\t-\t-\t%0.3f\t%0.3f\n'%(1.01,1.01,1.01,1.01))

   f.write('mu_eff\tlnN\t')
   f.write('%0.3f\t%0.3f\t-\t-\t%0.3f\t%0.3f\n'%(1.01,1.01,1.01,1.01))

   f.write('ele_reco\tlnN\t')
   f.write('%0.3f\t%0.3f\t-\t-\t%0.3f\t%0.3f\n'%(1.01,1.01,1.01,1.01))

   f.write('ele_ID\tlnN\t')
   f.write('%0.3f\t%0.3f\t-\t-\t%0.3f\t%0.3f\n'%(1.016,1.016,1.016,1.016))

   f.write('photon_ID\tlnN\t')
   f.write('%0.3f\t%0.3f\t-\t-\t%0.3f\t%0.3f\n'%(1.02,1.02,1.02,1.02))

#   f.write('mu_trigger\tlnN\t')
#   f.write('%0.3f\t%0.3f\t-\t-\t%0.3f\t%0.3f\t%0.3f\n'%(arr['muon_ZA-EWK_'+'trigger'][i-1],arr['muon_ZA_'+'trigger'][i-1],arr['muon_TTA_'+'trigger'][i-1],arr['muon_VV_'+'trigger'][i-1],arr['muon_ST_'+'trigger'][i-1]))
#
#   f.write('mu_eff\tlnN\t')
#   f.write('%0.3f\t%0.3f\t-\t-\t%0.3f\t%0.3f\t%0.3f\n'%(arr['muon_ZA-EWK_all'][i-1],arr['muon_ZA_all'][i-1],arr['muon_TTA_all'][i-1],arr['muon_VV_all'][i-1],arr['muon_ST_all'][i-1]))
#
#   f.write('ele_reco\tlnN\t')
#   f.write('%0.3f\t%0.3f\t-\t-\t%0.3f\t%0.3f\t%0.3f\n'%(arr['ele_ZA-EWK_reco'][i-1],arr['ele_ZA_reco'][i-1],arr['ele_TTA_reco'][i-1],arr['ele_VV_reco'][i-1],arr['ele_ST_reco'][i-1]))
#
#   f.write('ele_ID\tlnN\t')
#   f.write('%0.3f\t%0.3f\t-\t-\t%0.3f\t%0.3f\t%0.3f\n'%(arr['ele_ZA-EWK_ID'][i-1],arr['ele_ZA_ID'][i-1],arr['ele_TTA_ID'][i-1],arr['ele_VV_ID'][i-1],arr['ele_ST_ID'][i-1]))
#
#   f.write('photon_id\tlnN\t')
#   f.write('%0.3f\t%0.3f\t-\t-\t%0.3f\t%0.3f\t%0.3f\n'%(arr['photon_ZA-EWK_ID'][i-1],arr['photon_ZA_ID'][i-1],arr['photon_TTA_ID'][i-1],arr['photon_VV_ID'][i-1],arr['photon_ST_ID'][i-1]))

   f.write('ttgamma_xs\tlnN\t')
   f.write('-\t-\t-\t-\t1.1\t-\t-\n')

   f.write('VV_xs\tlnN\t')
   f.write('-\t-\t-\t-\t-\t1.1\t-\n')
   f.write('Top_scale rateParam * Top 1.0 [0.1,4]\n')
#   print 'bin ',i,' ',ZA_binerror,' ',non_prompt_binerror,' ',TTA_binerror,' ',VV_binerror,' ',ST_binerror,' ',WA_binerror,' ',WWg_out_binerror
   genbincontent[:]=[]
   genbinerror[:]=[]
   
