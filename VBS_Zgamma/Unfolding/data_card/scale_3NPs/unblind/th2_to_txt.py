#!/usr/bin/env python

from ROOT import gROOT, THStack, TH1D, TList, TFile
import sys
from numpy import sum
print '-----begin to transfer TH2D to txt for Higgs-combine tool----- \n'
print sys.argv[1],' ',sys.argv[2],' ',sys.argv[3]
fdir = '/home/pku/anying/cms/PKU-Cluster/Unfolding/common/root/'
f_EW = TFile.Open(fdir+'hist_ZA-EWK_'+sys.argv[1]+sys.argv[3]+'.root')
f_ZA = TFile.Open(fdir+'hist_ZA_'+sys.argv[2]+sys.argv[3]+'.root')
f_interf = TFile.Open(fdir+'hist_ZA_interf_'+sys.argv[2]+sys.argv[3]+'.root')
f_plj = TFile.Open(fdir+'hist_plj_'+sys.argv[2]+sys.argv[3]+'.root')
f_TTA = TFile.Open(fdir+'hist_TTA_'+sys.argv[2]+sys.argv[3]+'.root')
f_VV = TFile.Open(fdir+'hist_VV_'+sys.argv[2]+sys.argv[3]+'.root')
f_ST = TFile.Open(fdir+'hist_ST_'+sys.argv[2]+sys.argv[3]+'.root')
f_Ele = TFile.Open(fdir+'hist_DEle_'+sys.argv[2]+sys.argv[3]+'.root')
f_Muon = TFile.Open(fdir+'hist_DMuon_'+sys.argv[2]+sys.argv[3]+'.root')

th1_ZA_sig_out=f_EW.Get('hist_'+sys.argv[2])
th1_ZA=f_ZA.Get('hist_'+sys.argv[2])
th1_interf=f_interf.Get('hist_'+sys.argv[2])
th1_ZA.Add(th1_interf)
th1_non_prompt=f_plj.Get('hist_'+sys.argv[2])
th1_TTA=f_TTA.Get('hist_'+sys.argv[2])
th1_VV=f_VV.Get('hist_'+sys.argv[2])
th1_ST=f_ST.Get('hist_'+sys.argv[2])
th1_DEle=f_Ele.Get('hist_'+sys.argv[2])
th1_DMuon=f_Muon.Get('hist_'+sys.argv[2])

# the bkg histo and signal histo have already contain the overflow bin in the last bin when creat the histograms 
genbincontent=[]
genbinerror=[]
arr={}
f=open('/home/pku/anying/cms/PKU-Cluster/Unfolding/Uncer/summary_'+sys.argv[2]+"_"+sys.argv[3]+'.txt')
import re
import numpy as np
for line in f:
        if not line.strip():
            continue
#	print line
	line = line.replace('[','')
        line = line.replace(']','')
        line = line.replace('\n','')
#	print line
	arr_Temp = re.split(',|=',line)
#        print arr_Temp
	name = arr_Temp[0]
        arr_Temp = np.array(arr_Temp[1:])
	#arr_Temp.astype(np.float)
	arr_Temp = [float(x) for x in arr_Temp]
#	print name
	arr[name]=arr_Temp
#print arr 
print '>>>>begin to read bin content to the txt file>>>>'
nbins=th1_ZA_sig_out.GetNbinsX()+1
n_NP=25+nbins-1
jmax=6+nbins-1-1
for i in range(1,nbins):
   f = open('./txt/%s_%s_bin%i.txt'%(sys.argv[2],sys.argv[3],i),'w')
   f.write('imax 1   number of channels\n')
   f.write('jmax %i   number of processes-1\n'%(jmax))
   if sys.argv[3].find("18") == -1 and sys.argv[3].find("17") == -1:#16
	f.write('kmax %i  number of nuisance parameters (sources of systematical uncertainties)\n'%(n_NP+2))
   if sys.argv[3].find("16") == -1 and sys.argv[3].find("18") == -1:#17
	f.write('kmax %i  number of nuisance parameters (sources of systematical uncertainties)\n'%(n_NP+2))
   if sys.argv[3].find("16") == -1 and sys.argv[3].find("17") == -1:#18
	f.write('kmax %i  number of nuisance parameters (sources of systematical uncertainties)\n'%(n_NP+1))
   f.write('------------\n')
   f.write('# we have just one channel, in which we observe 0 events\n')
   f.write('bin recobin%i\n'%(i))
   genhist =f_EW.Get(sys.argv[1]+"_{}".format(i-1)) 
   for k in range(1,nbins):
	   genbincontent.append(genhist.GetBinContent(k))
           genbinerror.append(genhist.GetBinError(k))   
#           print genhist.GetEntries()
# bincontent of each precess
   ST_bincontent = th1_ST.GetBinContent(i) if th1_ST.GetBinContent(i)>0 else 0
   TTA_bincontent = th1_TTA.GetBinContent(i) if th1_TTA.GetBinContent(i)>0 else 0
   VV_bincontent = th1_VV.GetBinContent(i) if th1_VV.GetBinContent(i)>0 else 0
   non_prompt_bincontent = th1_non_prompt.GetBinContent(i) if th1_non_prompt.GetBinContent(i)>0 else 0
   ZA_bincontent = th1_ZA.GetBinContent(i) if th1_ZA.GetBinContent(i)>0 else 0
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

   ZA_binerror = th1_ZA.GetBinError(i)/ZA_bincontent if ZA_bincontent>0 else 0
   ZA_binerror = ZA_binerror if ZA_binerror<1 else 1
   ZA_binerror = ZA_binerror+1

   ZA_sig_out_binerror = th1_ZA_sig_out.GetBinError(i)/ZA_sig_out_bincontent if ZA_sig_out_bincontent>0 else 0
   ZA_sig_out_binerror = ZA_sig_out_binerror if ZA_sig_out_binerror<1 else 1
   ZA_sig_out_binerror = ZA_sig_out_binerror+1
   for j in range(1,nbins):
	   genbinerror[j-1]=genbinerror[j-1]/genbincontent[j-1] if genbincontent[j-1]>0 else 0
	   genbinerror[j-1]=genbinerror[j-1]  if genbinerror[j-1]<1 else 1
	   genbinerror[j-1]=genbinerror[j-1]+1
#          print genbincontent[j-1],' ',genbinerror[j-1]
   data=th1_DMuon.GetBinContent(i)+th1_DEle.GetBinContent(i)
#   data=sum(genbincontent)+ ZA_bincontent+non_prompt_bincontent+TTA_bincontent+VV_bincontent+ST_bincontent+ZA_sig_out_bincontent
   f.write('observation %0.3f\n'%(data))
   f.write('------------\n')
   f.write('# now we list the expected events for signal and all backgrounds in that bin\n')
   f.write('# the second process line must have a positive number for backgrounds, and 0 for signal\n')
   f.write('# then we list the independent sources of uncertainties, and give their effect (syst. error)\n')
   f.write('# on each process and bin\n')
   f.write('bin\t')
   for j in range(1,nbins):
         f.write('recobin%d\t' %(i))
   f.write('recobin%i\trecobin%i\trecobin%i\trecobin%i\trecobin%i\trecobin%i\n'%(i,i,i,i,i,i))
   f.write('process\t')
   for j in range(1,nbins):
         f.write('genbin%i\t' %(j))
   f.write('QCD\tnon_prompt\tTTA\tVV\tST\tSig_out\n')
   f.write('process\t')
   for j in range(1-nbins,0):#nbins=5,-4 to 0, -4,-3,-2,-1
         f.write('%i\t'%(j))
   f.write('0\t1\t2\t3\t4\t5\n')
   f.write('rate\t')
   for j in range(1,nbins):
         f.write('%0.3f\t' %(genbincontent[j-1]))
   f.write('%0.3f\t%0.3f\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(ZA_bincontent, non_prompt_bincontent, TTA_bincontent, VV_bincontent, ST_bincontent, ZA_sig_out_bincontent))
   f.write('------------\n')

   f.write('lumi_%s\tlnN\t'%(sys.argv[3]))
   if sys.argv[3].find("17")==-1 and  sys.argv[3].find("18")==-1:
       for j in range(1,nbins):
             f.write('%0.3f\t'%(1.022))
       f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(1.022,1.022,1.022,1.022,1.022))
   if sys.argv[3].find("16")==-1 and  sys.argv[3].find("18")==-1:
       for j in range(1,nbins):
             f.write('%0.3f\t'%(1.02))
       f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(1.02,1.02,1.02,1.02,1.02))
   if sys.argv[3].find("16")==-1 and  sys.argv[3].find("17")==-1:
       for j in range(1,nbins):
             f.write('%0.3f\t'%(1.015))
       f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(1.015,1.015,1.015,1.015,1.015))

   for j in range(1,nbins):
          f.write('genbin%i_Stat_recobin%d_%s\tlnN\t'%(j,i,sys.argv[3],))
          if j==1:
		  f.write('%0.3f\t'%(genbinerror[j-1]))
                  for k in range(j+1,nbins):
                      f.write('-\t')
                  f.write('-\t-\t-\t-\t-\t-\n')
          if j-1>0:
                  for k in range(1,j+1):
                      if(k<j):
			      f.write('-\t')
                      if(k==j):
                              f.write('%0.3f\t'%(genbinerror[j-1]))
                  if j<(nbins-1):
                      for k in range(j+1,nbins):
                            f.write('-\t')
                  f.write('-\t-\t-\t-\t-\t-\n')

   f.write('QCD_Stat_recobin%d_%s\tlnN\t'%(i,sys.argv[3]))
   for j in range(1,nbins):
         f.write('-\t')
   f.write('%0.3f\t-\t-\t-\t-\t-\n'%(ZA_binerror))

   f.write('non_prompt_Stat_recobin%d_%s\tlnN\t'%(i,sys.argv[3]))
   for j in range(1,nbins):
         f.write('-\t')
   f.write('-\t%0.3f\t-\t-\t-\t-\n'%(non_prompt_binerror))

   f.write('TTA_Stat_recobin%d_%s\tlnN\t'%(i,sys.argv[3]))
   for j in range(1,nbins):
         f.write('-\t')
   f.write('-\t-\t%0.3f\t-\t-\t-\n'%(TTA_binerror))

   f.write('VV_Stat_recobin%d_%s\tlnN\t'%(i,sys.argv[3]))
   for j in range(1,nbins):
         f.write('-\t')
   f.write('-\t-\t-\t%0.3f\t-\t-\n'%(VV_binerror))

   f.write('ST_Stat_recobin%d_%s\tlnN\t'%(i,sys.argv[3]))
   for j in range(1,nbins):
         f.write('-\t')
   f.write('-\t-\t-\t-\t%0.3f\t-\n'%(ST_binerror))


   f.write('ZA_SigOut_Stat_recobin%d_%s\tlnN\t'%(i,sys.argv[3]))
   for j in range(1,nbins):
         f.write('-\t')
   f.write('-\t-\t-\t-\t-\t%0.3f\n'%(ZA_sig_out_binerror))

   f.write('fake_%s\tlnN\t'%(sys.argv[3]))
   for j in range(1,nbins):
         f.write('-\t')
   if non_prompt_bincontent==0:
       f.write('-\t-\t-\t-\t-\t-\n')
   else: 
        f.write('-\t%0.3f\t-\t-\t-\t-\n'%(arr['fake'+sys.argv[3]][i-1]))

   f.write('JES_%s\tlnN\t'%(sys.argv[3]))
   for j in range(1,nbins):
	 f.write('%0.3f\t'%(arr['genbin{}_jes'.format(j)][i-1]))
   f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(arr['jes'+sys.argv[3]+'_ZA'][i-1],arr['jes'+sys.argv[3]+'_TTA'][i-1],arr['jes'+sys.argv[3]+'_VV'][i-1],arr['jes'+sys.argv[3]+'_ST'][i-1],arr['jes'+sys.argv[3]+'_ZA-EWKout'][i-1]))

   f.write('JER_%s\tlnN\t'%(sys.argv[3]))
   for j in range(1,nbins):
	 f.write('%0.3f\t'%(arr['genbin{}_jer'.format(j)][i-1]))
   f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(arr['jer'+sys.argv[3]+'_ZA'][i-1],arr['jer'+sys.argv[3]+'_TTA'][i-1],arr['jer'+sys.argv[3]+'_VV'][i-1],arr['jer'+sys.argv[3]+'_ST'][i-1],arr['jer'+sys.argv[3]+'_ZA-EWKout'][i-1]))
#
   f.write('pdf_EW\tlnN\t')
   for j in range(1,nbins):
	 f.write('%0.3f\t'%(arr['genbin{}_pdf'.format(j)][i-1]))
   f.write('-\t-\t-\t-\t-\t%0.3f\n'%(arr['SigOut_pdf'][i-1]))
#
   f.write('pdf_QCD\tlnN\t')
   for j in range(1,nbins):
         f.write('-\t')
   f.write('%0.3f\t-\t-\t-\t-\t-\n'%(arr['QCD_pdf'][i-1]))
#
   f.write('Scale_EW\tlnN\t')
   for j in range(1,nbins):
	 f.write('%0.3f\t'%(arr['genbin{}_scale'.format(j)][i-1]))
   f.write('-\t-\t-\t-\t-\t%0.3f\n'%(arr['SigOut_scale'][i-1]))
#
   f.write('Scale_muF1\tlnN\t')
   for j in range(1,nbins):
         f.write('-\t')
   f.write('%0.3f\t-\t-\t-\t-\t-\n'%(arr['scale_muF1'][i-1]))
#
   f.write('Scale_muR1\tlnN\t')
   for j in range(1,nbins):
         f.write('-\t')
   f.write('%0.3f\t-\t-\t-\t-\t-\n'%(arr['scale_muR1'][i-1]))
#
   f.write('Scale_muFmuR\tlnN\t')
   for j in range(1,nbins):
         f.write('-\t')
   f.write('%0.3f\t-\t-\t-\t-\t-\n'%(arr['scale_muFmuR'][i-1]))
#
   f.write('mu_trigger\tlnN\t')
   for j in range(1,nbins):
	 f.write('%0.3f\t'%(arr['muon_ZA-EWK_trigger'][i-1]))
   f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(arr['muon_ZA_trigger'][i-1],arr['muon_TTA_trigger'][i-1],arr['muon_VV_trigger'][i-1],arr['muon_ST_trigger'][i-1],arr['muon_ZA-EWK_trigger'][i-1]))
#
   f.write('mu_eff\tlnN\t')
   for j in range(1,nbins):
	 f.write('%0.3f\t'%(arr['muon_ZA-EWK_all'][i-1]))
   f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(arr['muon_ZA_all'][i-1],arr['muon_TTA_all'][i-1],arr['muon_VV_all'][i-1],arr['muon_ST_all'][i-1],arr['muon_VV_all'][i-1]))
#
   f.write('ele_reco\tlnN\t')
   for j in range(1,nbins):
	 f.write('%0.3f\t'%(arr['ele_ZA-EWK_reco'][i-1]))
   f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(arr['ele_ZA_reco'][i-1],arr['ele_TTA_reco'][i-1],arr['ele_VV_reco'][i-1],arr['ele_ST_reco'][i-1],arr['ele_ZA-EWK_reco'][i-1]))
#
   f.write('ele_ID\tlnN\t')
   for j in range(1,nbins):
	 f.write('%0.3f\t'%(arr['ele_ZA-EWK_ID'][i-1]))
   f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(arr['ele_ZA_ID'][i-1],arr['ele_TTA_ID'][i-1],arr['ele_VV_ID'][i-1],arr['ele_ST_ID'][i-1],arr['ele_ZA-EWK_ID'][i-1]))
#
   f.write('photon_id\tlnN\t')
   for j in range(1,nbins):
	 f.write('%0.3f\t'%(arr['photon_ZA-EWK_ID'][i-1]))
   f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(arr['photon_ZA_ID'][i-1],arr['photon_TTA_ID'][i-1],arr['photon_VV_ID'][i-1],arr['photon_ST_ID'][i-1],arr['photon_ZA-EWK_ID'][i-1]))
#
   f.write('pileup\tlnN\t')
   for j in range(1,nbins):
	 f.write('%0.3f\t'%(arr['genbin{}_pu'.format(j)][i-1]))
   f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n' %(arr['pileup_ZA'][i-1],arr['pileup_TTA'][i-1],arr['pileup_VV'][i-1],arr['pileup_ST'][i-1],arr['pileup_ZA-EWK'][i-1]))
#
   f.write('ttgamma_xs\tlnN\t')
   for j in range(1,nbins):
         f.write('-\t')
   f.write('-\t-\t1.1\t-\t-\t-\n')

   f.write('VV_xs\tlnN\t')
   for j in range(1,nbins):
         f.write('-\t')
   f.write('-\t-\t-\t1.1\t-\t-\n')
#
   f.write('pileupId_mis_%s\tlnN\t'%(sys.argv[3]))
   for j in range(1,nbins):
	   f.write('%0.3f\t'%(arr['genbin{}_mis'.format(j)][i-1]))
   f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(arr['ZA_mis'][i-1],arr['TTA_mis'][i-1],arr['VV_mis'][i-1],arr['ST_mis'][i-1],arr['ZA-EWKout_mis'][i-1]))
#
   f.write('pileupId_eff_%s\tlnN\t'%(sys.argv[3]))
   for j in range(1,nbins):
	   f.write('%0.3f\t'%(arr['genbin{}_eff'.format(j)][i-1]))
   f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(arr['ZA_eff'][i-1],arr['TTA_eff'][i-1],arr['VV_eff'][i-1],arr['ST_eff'][i-1],arr['ZA-EWKout_eff'][i-1]))
#
   if sys.argv[3].find("18") == -1:
        f.write('l1pref\tlnN\t')
        for j in range(1,nbins):
	       f.write('%0.3f\t'%(arr['genbin{}_pref'.format(j)][i-1]))
        f.write('%0.3f\t-\t%0.3f\t%0.3f\t%0.3f\t%0.3f\n'%(arr['l1pref_ZA'][i-1],arr['l1pref_TTA'][i-1],arr['l1pref_VV'][i-1],arr['l1pref_ST'][i-1],arr['l1pref_ZA-EWK'][i-1]))

#   print 'bin ',i,' ',ZA_binerror,' ',non_prompt_binerror,' ',TTA_binerror,' ',VV_binerror,' ',ST_binerror,' ',WA_binerror,' ',ZA_sig_out_binerror
   genbincontent[:]=[]
   genbinerror[:]=[]
   


