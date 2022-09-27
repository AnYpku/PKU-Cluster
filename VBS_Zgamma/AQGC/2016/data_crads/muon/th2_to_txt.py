#!/usr/bin/env python

from ROOT import gROOT, THStack, TH1D, TList, TFile
print '-----begin to transfer TH2D to txt for Higgs-combine tool----- \n'

f_sig = TFile.Open("ZA-EWK_hist.root")
f_ZA = TFile.Open("ZA_hist.root")
f_plj = TFile.Open("plj_hist.root")
f_others = TFile.Open("bkg_hist.root")

th1_ZA_sig = f_sig.Get("ZA-EWK")
th1_ZA = f_ZA.Get("ZA")
th1_non_prompt = f_plj.Get("plj")
th1_others = f_others.Get("bkg")

print '>>>>begin to read bin content to the txt file>>>>'
fake=[1.187,1.233,1.316,1.000,1.000]
jer_EWK=[1.002,1.004,1.009,1.023,1.004]
jer_QCD=[1.091,1.089,1.059,1.310,1.451]
jer_others=[1.315,1.315,1.000,1.315,1.000]
jes_EWK=[1.018,1.017,1.019,1.023,1.000]
jes_QCD=[1.092,1.189,1.083,1.284,1.041]
jes_others=[1.143,1.143,1.000,1.143,1.000]
pdf_QCD=[1.010,1.041,1.057,1.023,1.027]
pdf_ewk=[1.039,1.040,1.044,1.051,1.074]
scale_QCD=[1.125,1.122,1.255,1.030,1.215]
scale_ewk=[1.075,1.089,1.100,1.125,1.129]
l1pref=[1.024,1.026,1.027,1.027,1.025]
interf=[1.044,1.015,1.027,1.015,1.090]
for i in range(1,6):
   f = open('./txt/%s_bin_%d.txt'%('mu16', i),'w')
   f.write('imax 1   number of channels\n')
   f.write('jmax 3   number of processes-1\n')
   f.write('kmax 19  number of nuisance parameters (sources of systematical uncertainties)\n')
   f.write('------------\n')
   f.write('# we have just one channel, in which we observe 0 events\n')
   f.write('bin mu%i\n'%(i))
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
   f.write('bin\tmu%i\tmu%i\tmu%i\tmu%i\n'%(i,i,i,i))
   f.write('process\tsig\tQCD\tnon_prompt\tothers\n')
   f.write('process\t0\t1\t2\t3\n')
   f.write('rate\t%0.2f\t%0.2f\t%0.2f\t%0.2f\n'%(ZA_sig_bincontent,ZA_bincontent, non_prompt_bincontent, others_bincontent))
   f.write('------------\n')
   f.write('lumi16\tlnN\t1.022\t1.022\t-\t1.022\t#lumi\n')
   if non_prompt_bincontent==0:
       f.write('fake_%s_%s\tlnN\t-\t-\t-\t-\t#0. uncertainty on mu_16\n'%('mu','16'))
   else: 
       f.write('fake_%s_%s\tlnN\t-\t%0.2f\t-\t-\t#0. uncertainty on mu_16\n'%('mu','16',fake[i-1]))
   f.write('VBS_stat_%s_%s_bin_%d\tlnN\t%0.2f\t-\t-\t-\n'%('mu','16',i,ZA_sig_binerror))
   f.write('QCD_stat_%s_%s_bin_%d\tlnN\t-\t%0.2f\t-\t-\n'%('mu','16',i,ZA_binerror))
   f.write('non_prompt_stat_%s_%s_bin_%d\tlnN\t-\t-\t%0.2f\t-\n'%('mu','16',i,non_prompt_binerror))
   f.write('others_stat_%s_%s_bin_%d\tlnN\t-\t-\t-\t%0.2f\n'%('mu','16',i,others_binerror))
   f.write('JES_%s\tlnN\t%0.2f\t%0.2f\t-\t%0.2f\n'%('16',jes_EWK[i-1],jes_QCD[i-1],jes_EWK[i-1]))
   f.write('JER_%s\tlnN\t%0.2f\t%0.2f\t-\t%0.2f\n'%('16',jer_EWK[i-1],jer_QCD[i-1],jer_EWK[i-1]))
   f.write('QCDZA_pdf\tlnN\t-\t%0.2f\t-\t-\n'%(pdf_QCD[i-1]))
   f.write('QCDZA_scale\tlnN\t-\t%0.2f\t-\t-\n'%(scale_QCD[i-1]))
   f.write('signal_pdf\tlnN\t%0.2f\t-\t-\t-\n'%(pdf_ewk[i-1]))
   f.write('signal_scale\tlnN\t%0.2f\t-\t-\t-\n'%(scale_ewk[i-1]))
   f.write('mu_trigger\tlnN\t1.02\t1.02\t-\t1.02\n')
   f.write('mu_all\tlnN\t1.01\t1.01\t-\t1.01\n')
   f.write('pileup\tlnN\t1.01\t1.01\t-\t1.01\n')
   f.write('photon_id\tlnN\t1.03\t1.03\t-\t1.03\n')
   f.write('interference\tlnN\t%0.3f\t-\t-\t-\n'%(interf[i-1]))
   f.write('others_xs\tlnN\t-\t-\t-\t1.1\n')
   f.write('l1prefiring\tlnN\t%0.3f\t%0.3f\t-\t%0.3f\n'%(l1pref[i-1],l1pref[i-1],l1pref[i-1]))
   print 'bin ',i,' ',ZA_sig_binerror,' ',ZA_binerror,' ',non_prompt_binerror,' ',others_binerror

