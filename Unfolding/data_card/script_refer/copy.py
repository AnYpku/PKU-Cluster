#!/usr/bin/env python

from ROOT import gROOT, THStack, TH1D, TList, TFile

print '-----begin to transfer TH2D to txt for Higgs-combine tool----- \n'

fdir = '/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/common/'
f_EW = TFile.Open(fdir+'hist_ZA-EWK_'+sys.argv[1]+sys.argv[3]+'.root')
f_ZA = TFile.Open(fdir+'hist_ZA_'+sys.argv[2]+sys.argv[3]+'.root')
f_plj = TFile.Open(fdir+'hist_plj_weight_'+sys.argv[2]+sys.argv[2]+'.root')
f_TTA = TFile.Open(fdir+'hist_TTA_'+sys.argv[2]+sys.argv[3]+'.root')
f_VV = TFile.Open(fdir+'hist_VV_'+sys.argv[2]+sys.argv[3]+'.root')
f_ST = TFile.Open(fdir+'hist_ST_'+sys.argv[2]+sys.argv[3]+'.root')
f_WA = TFile.Open(fdir+'hist_WA_'+sys.argv[2]+sys.argv[3]+'.root')

th1_sig_out=f_EW.Get('hist_'+sys.argv[2])
th1_ZA=f_ZA.Get('hist_'+sys.argv[2])
th1_plj=f_plj.Get('hist_'+sys.argv[2])
th1_TTA=f_TTA.Get('hist_'+sys.argv[2])
th1_VV=f_VV.Get('hist_'+sys.argv[2])
th1_ST=f_ST.Get('hist_'+sys.argv[2])
th1_WA=f_WA.Get('hist_'+sys.argv[2])
hist_data
genbincontent=[]
genbinerror=[]
arr={}
f=open('txt')
import re
import numpy as np
for line in f:
	arr_Temp = re.split('=|[|]| |,',line)
	name = arr_Temp[0]
        arr_Temp = np.array(arr_Temp[1:])
	arr_Temp.astype(np.float)
	arr[name]=arr_Temp
print arr 
print '>>>>begin to read bin content to the txt file>>>>'
nbins=th1_sig_out.GetNbinsX()+1
for i in range(1,nbins):
   f = open('./txt/%s_bin_%d.txt'%(sys.argv[1], i),'w')
   f.write('imax 1   number of channels\n')
   f.write('jmax 10   number of processes-1\n')
   f.write('kmax 1  number of nuisance parameters (sources of systematical uncertainties)\n')
   f.write('------------\n')
   f.write('# we have just one channel, in which we observe 0 events\n')
   f.write('bin recobin%i\n'%(i))
   bin_content = hist_data.GetBinContent(i) 
   genhist =f_sig.Get(sys.argv[1]+"_{}".format(i)) 
   for k in range(1,nbins):
	   genbincontent.append(genhist.GetBinContent(k))
           genbinerror.append(genhist.GetBinError(k))   
# bincontent of each precess
   ST_bincontent = th1_ST.GetBinContent(i) if th1_ST.GetBinContent(i)>0 else 0
   TTA_bincontent = th1_TTA.GetBinContent(i) if th1_TTA.GetBinContent(i)>0 else 0
   VV_bincontent = th1_VV.GetBinContent(i) if th1_VV.GetBinContent(i)>0 else 0
   WA_bincontent = th1_WA.GetBinContent(i) if th1_WA.GetBinContent(i) else 0
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

   WA_binerror = th1_WA.GetBinError(i)/WA_bincontent if WA_bincontent>0 else 0
   WA_binerror = WA_binerror if WA_binerror<1 else 1
   WA_binerror = WA_binerror+1

   non_prompt_binerror = th1_non_prompt.GetBinError(i)/non_prompt_bincontent if non_prompt_bincontent>0 else 0
   non_prompt_binerror = non_prompt_binerror if non_prompt_binerror<1 else 1
   non_prompt_binerror =non_prompt_binerror+1

   ZA_binerror = th1_ZA.GetBinError(i)/ZA_bincontent if ZA_bincontent>0 else 0
   ZA_binerror = ZA_binerror if ZA_binerror<1 else 1
   ZA_binerror = ZA_binerror+1

   ZA_sig_out_binerror = th1_ZA_sig_out.GetBinError(i)/ZA_sig_out_bincontent if ZA_sig_out_bincontent>0 else 0
   ZA_sig_out_binerror = ZA_sig_out_binerror if ZA_sig_out_binerror<1 else 1
   ZA_sig_out_binerror = ZA_sig_out_binerror+1
   genbinerror[i]=genbinerror[i]/genbincontent[i] if genbincontent>0 else 0
   genbinerror[i]=genbinerror[i]  if genbinerror[i]<1 else 1
   genbinerror[i]=genbinerror[i]+1
   f.write('observation 0\n')
   f.write('------------\n')
   f.write('# now we list the expected events for signal and all backgrounds in that bin\n')
   f.write('# the second process line must have a positive number for backgrounds, and 0 for signal\n')
   f.write('# then we list the independent sources of uncertainties, and give their effect (syst. error)\n')
   f.write('# on each process and bin\n')
   f.write('bin\t')
   for j in range(1,nbins)
         f.write('recobin%d\t',i)
   f.write('recobin%i\trecobin%i\trecobin%i\trecobin%i\trecobin%i\trecobin%i\trecobin%i\n'%(i,i,i,i,i,i,i))
   f.write('process\t')
   for j in range(1,nbins)
         f.write('genbin%d\t',j)
   f.write('QCD\tnon_prompt\tTTA\tVV\tST\tWA\tSig_out\n')
   f.write('process\t')
   for j in range(1-nbins,1)
         f.write('%d\t'%(j))
   f.write('0\t1\t2\t3\t4\t5\t6\n')
   f.write('rate\t')
   for j in range(1,nbins)
         f.write('%0.2f\t',%(genbin[j-1]))
   f.write('%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\n'%(ZA_bincontent, non_prompt_bincontent, TTA_bincontent, VV_bincontent, ST_bincontent, WA_bincontent,ZA_sig_out_bincontent))
   f.write('------------\n')

   f.write('lumi\tlnN\t')
   for j in range(1,nbins)
         f.write('1.025\t')
   f.write('1.025\t-\t1.025\t1.025\t1.025\t1.025\t1.025\n')

   f.write('genbin_Stat_recobin%d_%s\tlnN\t'%(i,sys.argv[3],))
   for j in range(1,nbins)
          f.write('%0.2f\t'%(genbinerror[i-1]))
   f.write('-\t-\t-\t-\t-\t-\t-\n'%(i,sys.argv[3],genbinerror[0]))

   f.write('Bkg_Stat_recobin%d_%s\tlnN\t'%(i,sys.argv[3]))
   for j in range(1,nbins)
         f.write('-\t')
   f.write('%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\n'%(ZA_binerror,non_prompt_binerror,TTA_binerror,VV_binerror,ST_binerror,WA_binerror,ZA_sig_out_binerror))

   f.write('fake_%s\tlnN\t'%(sys.argv[3]))
   for j in range(1,nbins)
         f.write('-\t')
   if non_prompt_bincontent==0:
       f.write('-\t-\t-\t-\t-\t-\t-\n')
   else: 
       f.write('-\%0.2f\t-\t-\t-\t-\t-\n'%(fake[i-1]))

   f.write('JES_%s'%(sys.argv[3]))
   for j in range(1,nbins)
         f.write('-\t')
   f.write('%0.2f\t-\%0.2f-\t%0.2f\t%0.2f\t%0.2f\t%0.2f\n'%(jes_QCD[i-1],jes_TTA[i-1],jes_VV[i-1],jes_ST[i-1],jes_EW[i-1],jes_EW[i-1]))

   f.write('JER_%s'%(sys.argv[3]))
   for j in range(1,nbins)
         f.write('-\t')
   f.write('%0.2f\t-\%0.2f-\t%0.2f\t%0.2f\t%0.2f\t%0.2f\n'%(jer_QCD[i-1],jer_TTA[i-1],jer_VV[i-1],jer_ST[i-1],jer_EW[i-1],jer_EW[i-1]))

   f.write('QCD_pdf_%s\tlnN\t'%(sys.argv[3]))
   for j in range(1,nbins)
         f.write('%0.2f\t'%(pdf_gen[i-1]))
   f.write('%0.2f\t-\t-\t-\t-\t-\%0.2f\n'%(pdf_QCD[i-1],pdf_SigOut[i-1]))

   f.write('Scale_pdf_%s\tlnN\t'%(sys.argv[3]))
   for j in range(1,nbins)
         f.write('%0.2f\t'%(pdf_gen[i-1]))
   f.write('%0.2f\t-\t-\t-\t-\t-\%0.2f\n'%(scale_QCD[i-1],scale_SigOut[i-1]))

   f.write('mu_trigger_%s\tlnN\t'%(sys.argv[3]))
   for j in range(1,nbins)
         f.write('-\t')
   f.write('1.02\t-\t1.02\t1.02\t1.02\t1.02\t1.02\n')

   f.write('mu_eff_%s\tlnN\t'%(sys.argv[3]))
   for j in range(1,nbins)
         f.write('-\t')
   f.write('1.005\t-\t1.005\t1.005\t1.005\t1.005\t1.005\n')

   f.write('ele_trigger_%s\tlnN\t'%(sys.argv[3]))
   for j in range(1,nbins)
         f.write('-\t')
   f.write('1.02\t-\t1.02\t1.02\t1.02\t1.02\t1.02\n')

   f.write('ele_eff_%s\tlnN\t'%(sys.argv[3]))
   for j in range(1,nbins)
         f.write('-\t')
   f.write('1.023\t-\t1.023\t1.023\t1.023\t1.023\t1.023\n')

   f.write('pileup\tlnN\t')
   for j in range(1,nbins)
         f.write('-\t')
   f.write('1.001\t-\t1.001\t1.001\t1.001\t1.001\t1.001\n')

   f.write('photon_id_%s\tlnN\t'%(sys.argv[3]))
   for j in range(1,nbins)
         f.write('-\t')
   f.write('1.03\t-\t1.03\t1.03\t1.03\t1.03\t1.03\n')

   f.write('bkg_xs\tlnN\t')
   for j in range(1,nbins)
         f.write('-\t')
   f.write('-\t-\t1.1\t1.1\t-\t-\t-\n')
   if sys.argv[3].find("18") == -1:
        f.write('l1pref\tlnN\t')
        for j in range(1,nbins)
               f.write('-\t')
        f.write('%0.2f\t-\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\n'%(l1pref[i-1],l1pref[i-1],l1pref[i-1],l1pref[i-1],l1pref[i-1],l1pref[i-1]))

   print 'bin ',i,' ',ZA_binerror,' ',non_prompt_binerror,' ',TTA_binerror,' ',VV_binerror,' ',ST_binerror,' ',WA_binerror,' ',ZA_sig_out_binerror
   genbincontent[:]=[]
   genbinerror[:]=[]
   


