#!/usr/bin/env python

from ROOT import gROOT, THStack, TH1D, TList, TFile

print '-----begin to transfer TH2D to txt for Higgs-combine tool----- \n'

f_in = TFile.Open("/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2016/FourChannels/2016muendcap/mjj5007501000_detajj25456_zepp18/aa.root")
tstack = f_in.Get("hs")
t_list = tstack.GetHists()

th1_ST = t_list.At(0)
th1_TTA = t_list.At(1)
th1_VV = t_list.At(2)
th1_WA = t_list.At(3)
th1_non_prompt = t_list.At(4)
th1_ZA = t_list.At(5)
th1_ZA_sig = t_list.At(6)

print '>>>>begin to read bin content to the txt file>>>>'

fakephoton=[1.09,1.10,1.09,1.09,1.10,1.07,1.08]
l1pref    =[1.01,1.02,1.04,1.01,1.02,1.03,1.02]

jes_QCD=[1.07, 1.09, 1.14, 1.19, 1.24, 1.21, 1.35]
jes_EWK=[1.02, 1.01, 1.05, 1.06, 1.02, 1.04, 1.04]
jes_ST =[1.00,1.00,1.00,1.00,1.00,1.00,1.00]
jes_TTA=[1.12,1.12,1.12,1.12,1.12,1.12,1.12]
jes_VV =[1.37,1.37,1.37,1.37,1.37,1.37,1.37]
jer_QCD   =[1.10,1.09,1.00,1.15,1.37,1.22,1.28]
jer       =[1.00,1.03,1.04,1.01,1.03,1.01,1.00]
jer_ST =[1.00,1.00,1.00,1.00,1.00,1.00,1.00]
jer_TTA=[1.06,1.06,1.06,1.06,1.06,1.06,1.06]
jer_VV =[1.38,1.38,1.38,1.38,1.38,1.38,1.38]

pdf_QCD  =[1.01,1.01,1.03,1.01,1.01,1.02,1.01]
scale_QCD=[1.14,1.19,1.24,1.10,1.11,1.18,1.11]
QCDZA_scale_extra_down = [0.976,0.950,0.908,0.999,0.997,0.947,0.999]
QCDZA_scale_extra_up   = [1.031,1.060,1.112,0.997,1.004,1.074,0.999]
pdf_ewk   =[1.04,1.04,1.04,1.04,1.04,1.04,1.05]
scale_ewk =[1.03,1.06,1.09,1.02,1.05,1.10,1.12]
interf    =[1.02,1.02,1.02,1.00,1.00,1.01,1.00]
for i in range(1,8):
   f = open('%s_%s_bin_%d.txt'%('muon16', 'endcap', i),'w')
   f.write('imax 1   number of channels\n')
   f.write('jmax 6   number of processes-1\n')
   f.write('kmax 24  number of nuisance parameters (sources of systematical uncertainties)\n')
   f.write('------------\n')
   f.write('# we have just one channel, in which we observe 0 events\n')
   f.write('bin mb\n')
   bin_content = th1_ST.GetBinContent(i)+th1_TTA.GetBinContent(i)+th1_VV.GetBinContent(i)+th1_WA.GetBinContent(i)+th1_non_prompt.GetBinContent(i)+th1_ZA.GetBinContent(i)+th1_ZA_sig.GetBinContent(i)
# bincontent of each precess
   ST_bincontent = th1_ST.GetBinContent(i) if th1_ST.GetBinContent(i)>0 else 0
   TTA_bincontent = th1_TTA.GetBinContent(i) if th1_TTA.GetBinContent(i)>0 else 0
   VV_bincontent = th1_VV.GetBinContent(i) if th1_VV.GetBinContent(i)>0 else 0
   WA_bincontent = th1_WA.GetBinContent(i) if th1_WA.GetBinContent(i) else 0
   non_prompt_bincontent = th1_non_prompt.GetBinContent(i) if th1_non_prompt.GetBinContent(i)>0 else 0
   ZA_bincontent = th1_ZA.GetBinContent(i) if th1_ZA.GetBinContent(i) else 0
   ZA_sig_bincontent = th1_ZA_sig.GetBinContent(i)  if th1_ZA_sig.GetBinContent(i)>0 else 0
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

   ZA_sig_binerror = th1_ZA_sig.GetBinError(i)/ZA_sig_bincontent if ZA_sig_bincontent>0 else 0
   ZA_sig_binerror = ZA_sig_binerror if ZA_sig_binerror<1 else 1
   ZA_sig_binerror = ZA_sig_binerror+1


   f.write('observation %.2f\n'%bin_content)
   f.write('------------\n')
   f.write('# now we list the expected events for signal and all backgrounds in that bin\n')
   f.write('# the second process line must have a positive number for backgrounds, and 0 for signal\n')
   f.write('# then we list the independent sources of uncertainties, and give their effect (syst. error)\n')
   f.write('# on each process and bin\n')
   f.write('bin\tmb\tmb\tmb\tmb\tmb\tmb\tmb\n')
   f.write('process\tVBS\tQCD\tnon_prompt\tTTA\tVV\tST\tWA\n')
   f.write('process\t0\t1\t2\t3\t4\t5\t6\n')
   f.write('rate\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\n'%(ZA_sig_bincontent, ZA_bincontent, non_prompt_bincontent, TTA_bincontent, VV_bincontent, ST_bincontent, WA_bincontent))
   f.write('------------\n')
   f.write('lumi\tlnN\t1.025\t1.025\t-\t1.025\t1.025\t1.025\t1.025\t#lumi\n')
   if non_prompt_bincontent==0:
       f.write('fake_%s_%s\tlnN\t-\t-\t-\t-\t-\t-\t-\t#0. uncertainty on muon16_endcap\n'%('muon16','endcap'))
   else: 
       f.write('fake_%s_%s\tlnN\t-\t-\t%0.2f\t-\t-\t-\t-\t#0. uncertainty on muon16_endcap\n'%('muon16','endcap',fakephoton[i-1]))
   f.write('VBS_stat_%s_%s_bin_%d\tlnN\t%0.2f\t-\t-\t-\t-\t-\t-\n'%('muon16','endcap',i,ZA_sig_binerror))
   f.write('QCD_stat_%s_%s_bin_%d\tlnN\t-\t%0.2f\t-\t-\t-\t-\t-\n'%('muon16','endcap',i,ZA_binerror))
   f.write('non_prompt_stat_%s_%s_bin_%d\tlnN\t-\t-\t%0.2f\t-\t-\t-\t-\n'%('muon16','endcap',i,non_prompt_binerror))
   f.write('TTA_stat_%s_%s_bin_%d\tlnN\t-\t-\t-\t%0.2f\t-\t-\t-\n'%('muon16','endcap',i,TTA_binerror))
   f.write('VV_stat_%s_%s_bin_%d\tlnN\t-\t-\t-\t-\t%0.2f\t-\t-\n'%('muon16','endcap',i,VV_binerror))
   f.write('ST_stat_%s_%s_bin_%d\tlnN\t-\t-\t-\t-\t-\t%0.2f\t-\n'%('muon16','endcap',i,ST_binerror))
   f.write('WA_stat_%s_%s_bin_%d\tlnN\t-\t-\t-\t-\t-\t-\t%0.2f\n'%('muon16','endcap',i,WA_binerror))
   f.write('JES_16\tlnN\t%0.2f\t%0.2f\t-\t%0.2f\t%0.2f\t%0.2f\t%0.2f\n'%(jes_EWK[i-1],jes_QCD[i-1],jes_TTA[i-1],jes_VV[i-1],jes_ST[i-1],jes_EWK[i-1]))
   f.write('JER_16\tlnN\t%0.2f\t%0.2f\t-\t%0.2f\t%0.2f\t%0.2f\t%0.2f\n'%(jer[i-1],jer_QCD[i-1],jer_TTA[i-1],jer_VV[i-1],jer_ST[i-1],jer[i-1]))
   f.write('QCDZA_pdf\tlnN\t-\t%0.2f\t-\t-\t-\t-\t-\n'%(pdf_QCD[i-1]))
   f.write('QCDZA_scale\tlnN\t-\t%0.2f\t-\t-\t-\t-\t-\n'%(scale_QCD[i-1]))
   f.write('QCDZA_scale_extra\tlnN\t-\t%0.2f/%0.2f\t-\t-\t-\t-\t-\n'%(QCDZA_scale_extra_down[i-1],QCDZA_scale_extra_up[i-1]))
   f.write('signal_pdf\tlnN\t%0.2f\t-\t-\t-\t-\t-\t-\n'%(pdf_ewk[i-1]))
   f.write('signal_scale\tlnN\t%0.2f\t-\t-\t-\t-\t-\t-\n'%(scale_ewk[i-1]))
   f.write('%s_trigger\tlnN\t1.02\t1.02\t-\t1.02\t1.02\t1.02\t1.02\n'%('muon16'))
   f.write('%s_efficiency\tlnN\t1.005\t1.005\t-\t1.005\t1.005\t1.005\t1.005\n'%('muon16'))
   f.write('pileup\tlnN\t1.01\t1.01\t-\t1.01\t1.01\t1.01\t1.01\n')
   f.write('photon_id_16\tlnN\t1.03\t-\t-\t1.03\t1.03\t1.03\t1.03\n')
   f.write('interference\tlnN\t%0.2f\t-\t-\t-\t-\t-\t-\n' %(interf[i-1]))
   f.write('ttgamma_xs\tlnN\t-\t-\t-\t1.1\t-\t-\t-\n')
   f.write('VVgamma_xs\tlnN\t-\t-\t-\t-\t1.1\t-\t-\n')
   f.write('l1prefiring\tlnN\t%0.2f\t%0.2f\t-\t%0.2f\t%0.2f\t%0.2f\t%0.2f\n' %(l1pref[i-1],l1pref[i-1],l1pref[i-1],l1pref[i-1],l1pref[i-1],l1pref[i-1]))
   print 'bin ',i,' ',ZA_sig_binerror,' ',ZA_binerror,' ',non_prompt_binerror,' ',TTA_binerror,' ',VV_binerror,' ',ST_binerror,' ',WA_binerror
   


