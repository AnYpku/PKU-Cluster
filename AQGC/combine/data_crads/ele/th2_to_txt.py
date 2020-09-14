#!/usr/bin/env python

from ROOT import gROOT, THStack, TH1D, TList, TFile

print '-----begin to transfer TH2D to txt for Higgs-combine tool----- \n'

dir16="/afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/2016/data_crads/ele/"
dir17="/afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/2017/data_crads/ele/"
dir18="/afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/2018/data_crads/ele/"

#######################2016 histograoms#######################
f_sig16 = TFile.Open(dir16+"ZA-EWK_hist.root")
f_ZA16 = TFile.Open(dir16+"ZA_total_hist.root")
f_plj16 = TFile.Open(dir16+"plj_weight_hist.root")
f_others16 = TFile.Open(dir16+"others_hist.root")

th1_ZA_sig = f_sig16.Get("ZA-EWK")
th1_ZA = f_ZA16.Get("ZA_total")
th1_non_prompt = f_plj16.Get("plj_weight")
th1_others = f_others16.Get("others")

#######################2017 histograoms#######################
f_sig17 = TFile.Open(dir17+"ZA-EWK_hist.root")
f_ZA17 = TFile.Open(dir17+"ZA_hist.root")
f_plj17 = TFile.Open(dir17+"plj_weight_hist.root")
f_others17 = TFile.Open(dir17+"bkg_hist.root")

th1_ZA_sig17 = f_sig17.Get("ZA-EWK")
th1_ZA17 = f_ZA17.Get("ZA")
th1_non_prompt17 = f_plj17.Get("plj_weight")
th1_others17 = f_others17.Get("bkg")

#######################2018 histograoms#######################
f_sig18 = TFile.Open(dir18+"ZA-EWK_hist.root")
f_ZA18 = TFile.Open(dir18+"ZA_hist.root")
f_plj18 = TFile.Open(dir18+"plj_weight_hist.root")
f_others18 = TFile.Open(dir18+"bkg_hist.root")

th1_ZA_sig18 = f_sig18.Get("ZA-EWK")
th1_ZA18 = f_ZA18.Get("ZA")
th1_non_prompt18 = f_plj18.Get("plj_weight")
th1_others18 = f_others18.Get("bkg")

#########################Add histograms####################
print 'sig histo'
th1_ZA_sig.Add(th1_ZA_sig17)
th1_ZA_sig.Add(th1_ZA_sig18)
print 'ZA histo'
th1_ZA.Add(th1_ZA17)
th1_ZA.Add(th1_ZA18)
print 'plj histo'
th1_non_prompt.Add(th1_non_prompt17)
th1_non_prompt.Add(th1_non_prompt18)
print 'bkg histo'
th1_others.Add(th1_others17)
th1_others.Add(th1_others18)

print '>>>>begin to read bin content to the txt file>>>>'
fake   =[1.36,1.36,1.41,1.32,1.40,1.41]
interf =[1.02,1.02,1.01,1.00,1.00,1.00]
l1pref= [0.03,0.03,0.03,0.04,0.04,0.02]

jes_EWK=[1.02,1.03,1.03,1.03,1.04,1.04]
jes_QCD=[1.23,1.27,1.22,1.23,1.18,1.33]
jer_EWK=[1.00,1.01,1.01,1.00,1.01,1.01]
jer_QCD=[1.12,1.09,1.12,1.09,1.15,1.26]
pdf_QCD=[1.01,1.03,1.01,1.07,1.02,1.03]
pdf_ewk=[1.01,1.01,1.01,1.01,1.02,1.03]
scale_ewk=[1.07,1.08,1.09,1.10,1.11,1.14]
scale_QCD=[1.12,1.17,1.13,1.15,1.17,1.11]
#QCDZA_scale_extra_down = [0.981,0.950,0.977,0.957,.020];
#QCDZA_scale_extra_up = [1.02,1.024,1.062,1.105,0.986];
kk=th1_others.GetNbinsX()+1
for i in range(1,kk):
   f = open('./txt/%s_bin_%d.txt'%('ele', i),'w')
   f.write('imax 1   number of channels\n')
   f.write('jmax 3   number of processes-1\n')
   f.write('kmax 25  number of nuisance parameters (sources of systematical uncertainties)\n')
   f.write('------------\n')
   f.write('# we have just one channel, in which we observe 0 events\n')
   f.write('bin ele%i\n'%(i))
# bincontent of each precess
   others_bincontent = th1_others.GetBinContent(i) if th1_others.GetBinContent(i)>0 else 0
   non_prompt_bincontent = th1_non_prompt.GetBinContent(i) if th1_non_prompt.GetBinContent(i)>0 else 0
   ZA_bincontent = th1_ZA.GetBinContent(i) if th1_ZA.GetBinContent(i)>0 else 0
   ZA_sig_bincontent = th1_ZA_sig.GetBinContent(i)  if th1_ZA_sig.GetBinContent(i)>0 else 0
   fr=1-th1_ZA_sig18.GetBinContent(i)/th1_ZA_sig.GetBinContent(i)
   l1pref[i-1]=l1pref[i-1]*fr+1
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
   bin_content = others_bincontent+non_prompt_bincontent+ZA_bincontent+ZA_sig_bincontent

   f.write('observation %.2f\n'%bin_content)
   f.write('------------\n')
   f.write('# now we list the expected events for signal and all backgrounds in that bin\n')
   f.write('# the second process line must have a positive number for backgrounds, and 0 for signal\n')
   f.write('# then we list the independent sources of uncertainties, and give their effect (syst. error)\n')
   f.write('# on each process and bin\n')
   f.write('bin\tele%i\tele%i\tele%i\tele%i\n'%(i,i,i,i))
   f.write('process\tsig\tQCD\tnon_prompt\tothers\n')
   f.write('process\t0\t1\t2\t3\n')
   f.write('rate\t%0.2f\t%0.2f\t%0.2f\t%0.2f\n'%(ZA_sig_bincontent,ZA_bincontent, non_prompt_bincontent, others_bincontent))
   f.write('------------\n')
   f.write('lumi\tlnN\t1.025\t1.025\t-\t1.025\t#lumi\n')
   if non_prompt_bincontent==0:
       f.write('fake_%s_%s\tlnN\t-\t-\t-\t-\t#0. uncertainty on ele_RunII\n'%('ele','RunII'))
   else: 
       f.write('fake_%s_%s\tlnN\t-\t%0.2f\t-\t-\t#0. uncertainty on ele_RunII\n'%('ele','RunII',fake[i-1]))
   f.write('VBS_stat_%s_%s_bin_%d\tlnN\t%0.2f\t-\t-\t-\n'%('ele','RunII',i,ZA_sig_binerror))
   f.write('QCD_stat_%s_%s_bin_%d\tlnN\t-\t%0.2f\t-\t-\n'%('ele','RunII',i,ZA_binerror))
   f.write('non_prompt_stat_%s_%s_bin_%d\tlnN\t-\t-\t%0.2f\t-\n'%('ele','RunII',i,non_prompt_binerror))
   f.write('others_stat_%s_%s_bin_%d\tlnN\t-\t-\t-\t%0.2f\n'%('ele','RunII',i,others_binerror))
   f.write('JES_%s\tlnN\t%0.2f\t%0.2f\t-\t%0.2f\n'%('RunII',jes_EWK[i-1],jes_QCD[i-1],jes_EWK[i-1]))
   f.write('JER_%s\tlnN\t%0.2f\t%0.2f\t-\t%0.2f\n'%('RunII',jer_EWK[i-1],jer_QCD[i-1],jer_EWK[i-1]))
   f.write('QCDZA_pdf\tlnN\t-\t%0.2f\t-\t-\n'%(pdf_QCD[i-1]))
   f.write('QCDZA_scale\tlnN\t-\t%0.2f\t-\t-\n'%(scale_QCD[i-1]))
   f.write('signal_pdf\tlnN\t%0.2f\t-\t-\t-\n'%(pdf_ewk[i-1]))
   f.write('signal_scale\tlnN\t%0.2f\t-\t-\t-\n'%(scale_ewk[i-1]))
   f.write('ele16_trigger\tlnN\t1.02\t1.02\t-\t1.02\n')
   f.write('ele17_trigger\tlnN\t1.02\t1.02\t-\t1.02\n')
   f.write('ele18_trigger\tlnN\t1.02\t1.02\t-\t1.02\n')
   f.write('ele16_efficiency\tlnN\t1.023\t1.023\t-\t1.023\n')
   f.write('ele17_efficiency\tlnN\t1.023\t1.023\t-\t1.023\n')
   f.write('ele18_efficiency\tlnN\t1.023\t1.023\t-\t1.023\n')
   f.write('pileup\tlnN\t1.001\t1.001\t-\t1.001\n')
   f.write('photon_id_16\tlnN\t1.03\t1.03\t-\t1.03\n')
   f.write('photon_id_17\tlnN\t1.03\t1.03\t-\t1.03\n')
   f.write('photon_id_18\tlnN\t1.03\t1.03\t-\t1.03\n')
   f.write('interference\tlnN\t%0.2f\t-\t-\t-\n'%(interf[i-1]))
   f.write('others_xs\tlnN\t-\t-\t-\t1.1\n')
   f.write('l1prefiring\tlnN\t%0.2f\t%0.2f\t-\t%0.2f\n'%(l1pref[i-1],l1pref[i-1],l1pref[i-1]))

   print 'bin ',i,' ',ZA_sig_binerror,' ',ZA_binerror,' ',non_prompt_binerror,' ',others_binerror

