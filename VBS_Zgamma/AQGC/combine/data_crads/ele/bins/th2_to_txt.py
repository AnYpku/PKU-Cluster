#!/usr/bin/env python

from ROOT import gROOT, THStack, TH1D, TList, TFile

print '-----begin to transfer TH2D to txt for Higgs-combine tool----- \n'

f_sig = TFile.Open("ZA-EWK_hist.root")
f_ZA = TFile.Open("ZA_hist.root")
f_plj = TFile.Open("plj_weight_hist.root")
f_others = TFile.Open("bkg_hist.root")

th1_ZA_sig = f_sig.Get("ZA-EWK")
th1_ZA = f_ZA.Get("ZA")
th1_non_prompt = f_plj.Get("plj_weight")
th1_others = f_others.Get("bkg")

print '>>>>begin to read bin content to the txt file>>>>'
jer_EWK=[1.005,1.006,1.027,1.04,1.06]
jer_QCD=[1.09,1.04,1.21,1.07,1.11]
jes_EWK=[1.03,1.04,1.013,1.04,1.06]
jes_QCD=[1.30,1.25,1.33,1.13,1.33]
fake=[1.24,1.20,0,0,0]
pdf_QCD=[1.01,1.01,1.02,1.02,1.03]
pdf_ewk=[1.01,1.01,1.02,1.02,1.03]
scale_QCD=[1.11,1.110,1.04,1.11,1.27]
scale_ewk=[1.027,1.043,1.079,1.023,1.023]
num=th1_others.GetNbinsX()
for i in range(1,num+1):
   f = open('./txt/%s_bin_%d.txt'%('ele_all', i),'w')
   f.write('imax 1   number of channels\n')
   f.write('jmax 3   number of processes-1\n')
   f.write('kmax 5  number of nuisance parameters (sources of systematical uncertainties)\n')
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
   f.write('# now we list the expected events for signal and ele_all backgrounds in that bin\n')
   f.write('# the second process line must have a positive number for backgrounds, and 0 for signal\n')
   f.write('# then we list the independent sources of uncertainties, and give their effect (syst. error)\n')
   f.write('# on each process and bin\n')
   f.write('bin\tmu%i\tmu%i\tmu%i\tmu%i\n'%(i,i,i,i))
   f.write('process\tsig\tQCD\tnon_prompt\tothers\n')
   f.write('process\t0\t1\t2\t3\n')
   f.write('rate\t%0.2f\t%0.2f\t%0.2f\t%0.2f\n'%(ZA_sig_bincontent,ZA_bincontent, non_prompt_bincontent, others_bincontent))
   f.write('------------\n')
   f.write('lumi\tlnN\t1.025\t1.025\t-\t1.025\t#lumi\n')
#   if non_prompt_bincontent==0:
#       f.write('fake_%s_%s\tlnN\t-\t-\t-\t-\t#0. uncertainty on ele_all_full\n'%('ele','full'))
#   else: 
#       f.write('fake_%s_%s\tlnN\t-\t%0.2f\t-\t-\t#0. uncertainty on ele_all_full\n'%('ele','full',fake[i-1]))
   f.write('VBS_stat_%s_%s_bin_%d\tlnN\t%0.2f\t-\t-\t-\n'%('ele_all','full',i,ZA_sig_binerror))
   f.write('QCD_stat_%s_%s_bin_%d\tlnN\t-\t%0.2f\t-\t-\n'%('ele_all','full',i,ZA_binerror))
   f.write('non_prompt_stat_%s_%s_bin_%d\tlnN\t-\t-\t%0.2f\t-\n'%('ele_all','full',i,non_prompt_binerror))
   f.write('others_stat_%s_%s_bin_%d\tlnN\t-\t-\t-\t%0.2f\n'%('ele_all','full',i,others_binerror))
#   f.write('JES_%s\tlnN\t%0.2f\t%0.2f\t-\t%0.2f\n'%('full',jes_EWK[i-1],jes_QCD[i-1],jes_EWK[i-1]))
#   f.write('JER_%s\tlnN\t%0.2f\t%0.2f\t-\t%0.2f\n'%('full',jer_EWK[i-1],jer_QCD[i-1],jer_EWK[i-1]))
#   f.write('QCDZA_pdf\tlnN\t-\t%0.2f\t-\t-\n'%(pdf_QCD[i-1]))
#   f.write('QCDZA_scale\tlnN\t-\t%0.2f\t-\t-\n'%(scale_QCD[i-1]))
#   f.write('signal_pdf\tlnN\t%0.2f\t-\t-\t-\n'%(pdf_ewk[i-1]))
#   f.write('signal_scale\tlnN\t%0.2f\t-\t-\t-\n'%(scale_ewk[i-1]))
#   f.write('ele_trigger\tlnN\t1.02\t1.02\t-\t1.02\n')
#   f.write('ele_efficiency\tlnN\t1.023\t1.023\t-\t1.023\n')
#   f.write('pileup\tlnN\t1.001\t1.001\t-\t1.001\n')
#   f.write('interference\tlnN\t1.01\t-\t-\t-\n')
#   f.write('others_xs\tlnN\t-\t-\t-\t1.1\n')
#   f.write('photon_id_16\tlnN\t1.03\t1.03\t-\t1.03\n')
#   f.write('l1prefiring\tlnN\t1.01\t1.01\t-\t1.01\n')

   print 'bin ',i,' ',ZA_sig_binerror,' ',ZA_binerror,' ',non_prompt_binerror,' ',others_binerror

