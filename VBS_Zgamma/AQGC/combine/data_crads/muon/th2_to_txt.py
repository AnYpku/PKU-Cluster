#!/usr/bin/env python

from ROOT import gROOT, THStack, TH1D, TList, TFile
def merge_hist(th1,sample):
    dir17="/data/pku/home/anying/cms/PKU-Cluster/AQGC/2017/data_crads/muon/"
    dir18="/data/pku/home/anying/cms/PKU-Cluster/AQGC/2018/data_crads/muon/"
    f2=TFile.Open(dir17+sample+"_hist.root")
    f3=TFile.Open(dir18+sample+"_hist.root")
    th2=f2.Get(sample)
    th3=f3.Get(sample)
    th1.Add(th2,1)
    th1.Add(th3,1)
print '-----begin to transfer TH2D to txt for Higgs-combine tool----- \n'


dir16="/data/pku/home/anying/cms/PKU-Cluster/AQGC/2016/data_crads/muon/"
#######################2016 histograoms#######################
f_sig16 = TFile.Open(dir16+"ZA-EWK_hist.root")
f_ZA16 = TFile.Open(dir16+"ZA_hist.root")
f_plj16 = TFile.Open(dir16+"plj_hist.root")
f_others16 = TFile.Open(dir16+"bkg_hist.root")

th1_ZA_sig = f_sig16.Get("ZA-EWK")
th1_ZA = f_ZA16.Get("ZA")
th1_non_prompt = f_plj16.Get("plj")
th1_others = f_others16.Get("bkg")
#########################Add histograms####################
merge_hist(th1_ZA_sig,"ZA-EWK")
merge_hist(th1_ZA,"ZA")
merge_hist(th1_non_prompt,"plj")
merge_hist(th1_others,"bkg")

print '>>>>begin to read bin content to the txt file>>>>'
fake   =[1.234,1.224,1.334,1.305,1.206]
interf =[1.048,1.050,1.029,1.009,1.035]
l1pref= [1.017,1.018,1.020,1.018,1.016]

jes_EWK=[1.022,1.030,1.015,1.017,1.023]
jes_QCD=[1.233,1.176,1.190,1.123,1.203]
jes_others=[1.282,1.282,1.000,1.282,1.282]
jer_EWK=[1.004,1.007,1.005,1.009,1.015]
jer_QCD=[1.158,1.150,1.073,1.049,1.465]
jer_others=[1.261,1.261,1.000,1.261,1.261]
pdf_QCD=[1.010,1.041,1.057,1.023,1.027]
pdf_ewk=[1.011,1.011,1.012,1.014,1.021]
scale_ewk=[1.077,1.090,1.102,1.115,1.136]
scale_QCD=[1.140,1.135,1.113,1.135,1.152]
kk=th1_others.GetNbinsX()+1
for i in range(1,kk):
   f = open('./txt/%s_bin_%d.txt'%('mu', i),'w')
   f.write('imax 1   number of channels\n')
   f.write('jmax 3   number of processes-1\n')
   f.write('kmax 21  number of nuisance parameters (sources of systematical uncertainties)\n')
   f.write('------------\n')
   f.write('# we have just one channel, in which we observe 0 events\n')
   f.write('bin mu%i\n'%(i))
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
   bin_content = others_bincontent+non_prompt_bincontent+ZA_bincontent+ZA_sig_bincontent

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
   f.write('lumi16\tlnN\t1.006\t1.006\t-\t1.006\t#lumi\n')
   f.write('lumi17\tlnN\t1.005\t1.005\t-\t1.005\t#lumi\n')
   f.write('lumi18\tlnN\t1.004\t1.004\t-\t1.004\t#lumi\n')
   if non_prompt_bincontent==0:
       f.write('fake_%s_%s\tlnN\t-\t-\t-\t-\t#0. uncertainty on mu_RunII\n'%('mu','RunII'))
   else: 
       f.write('fake_%s_%s\tlnN\t-\t%0.2f\t-\t-\t#0. uncertainty on mu_RunII\n'%('mu','RunII',fake[i-1]))
   f.write('VBS_stat_%s_%s_bin_%d\tlnN\t%0.2f\t-\t-\t-\n'%('mu','RunII',i,ZA_sig_binerror))
   f.write('QCD_stat_%s_%s_bin_%d\tlnN\t-\t%0.2f\t-\t-\n'%('mu','RunII',i,ZA_binerror))
   f.write('non_prompt_stat_%s_%s_bin_%d\tlnN\t-\t-\t%0.2f\t-\n'%('mu','RunII',i,non_prompt_binerror))
   f.write('others_stat_%s_%s_bin_%d\tlnN\t-\t-\t-\t%0.2f\n'%('mu','RunII',i,others_binerror))
   f.write('JES_%s\tlnN\t%0.2f\t%0.2f\t-\t%0.2f\n'%('RunII',jes_EWK[i-1],jes_QCD[i-1],jes_others[i-1]))
   f.write('JER_%s\tlnN\t%0.2f\t%0.2f\t-\t%0.2f\n'%('RunII',jer_EWK[i-1],jer_QCD[i-1],jer_others[i-1]))
   f.write('QCDZA_pdf\tlnN\t-\t%0.2f\t-\t-\n'%(pdf_QCD[i-1]))
   f.write('QCDZA_scale\tlnN\t-\t%0.2f\t-\t-\n'%(scale_QCD[i-1]))
   f.write('signal_pdf\tlnN\t%0.2f\t-\t-\t-\n'%(pdf_ewk[i-1]))
   f.write('signal_scale\tlnN\t%0.2f\t-\t-\t-\n'%(scale_ewk[i-1]))
   f.write('mu_trigger\tlnN\t1.02\t1.02\t-\t1.02\n')
   f.write('mu_all\tlnN\t1.01\t1.01\t-\t1.01\n')
   f.write('pileup\tlnN\t1.01\t1.01\t-\t1.01\n')
   f.write('photon_id\tlnN\t1.03\t1.03\t-\t1.03\n')
   f.write('interference\tlnN\t%0.2f\t-\t-\t-\n'%(interf[i-1]))
   f.write('others_xs\tlnN\t-\t-\t-\t1.1\n')
   f.write('l1prefiring\tlnN\t%0.2f\t%0.2f\t-\t%0.2f\n'%(l1pref[i-1],l1pref[i-1],l1pref[i-1]))

   print 'bin ',i,' ',ZA_sig_binerror,' ',ZA_binerror,' ',non_prompt_binerror,' ',others_binerror

