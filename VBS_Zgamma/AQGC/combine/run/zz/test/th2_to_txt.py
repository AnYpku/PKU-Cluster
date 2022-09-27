#!/usr/bin/env python

from ROOT import gROOT, THStack, TH1D, TList, TFile, TH1F

print '-----begin to transfer TH2D to txt for Higgs-combine tool----- \n'

f1 = TFile.Open("chAll.root")

th1_ZA_sig = f1.Get("diboson")
th1_ZA = f1.Get("QCD_gg")
th1_non_prompt = f1.Get("QCD_qq")

print '>>>>begin to read bin content to the txt file>>>>'
for i in range(1,7):
   f = open('./%s_bin_%d.txt'%('chAll', i),'w')
   f.write('imax 1   number of channels\n')
   f.write('jmax 2   number of processes-1\n')
   f.write('kmax 1  number of nuisance parameters (sources of systematical uncertainties)\n')
   f.write('------------\n')
   f.write('# we have just one channel, in which we observe 0 events\n')
   f.write('bin chAll%i\n'%(i))
   bin_content = th1_non_prompt.GetBinContent(i)+th1_ZA.GetBinContent(i)+th1_ZA_sig.GetBinContent(i)
# bincontent of each precess
   non_prompt_bincontent = th1_non_prompt.GetBinContent(i) if th1_non_prompt.GetBinContent(i)>0 else 0
   ZA_bincontent = th1_ZA.GetBinContent(i) if th1_ZA.GetBinContent(i) else 0
   ZA_sig_bincontent = th1_ZA_sig.GetBinContent(i)  if th1_ZA_sig.GetBinContent(i)>0 else 0
# bin error

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
   f.write('bin\tchAll%i\tchAll%i\tchAll%i\n'%(i,i,i))
   f.write('process\tsig\tQCDgg\tQCDqq\n')
   f.write('process\t0\t1\t2\n')
   f.write('rate\t%0.2f\t%0.2f\t%0.2f\n'%(ZA_sig_bincontent,ZA_bincontent, non_prompt_bincontent, ))
   f.write('------------\n')
   f.write('lumi\tlnN\t1.06\t1.06\t-\t#lumi\n')
#   f.write('VBS_stat_%s_%s_bin_%d\tlnN\t%0.2f\t-\t-\n'%('chAll','18',i,ZA_sig_binerror))
#   f.write('QCDgg_stat_%s_%s_bin_%d\tlnN\t-\t%0.2f\t-\n'%('chAll','18',i,ZA_binerror))
#   f.write('QCDqq_stat_%s_%s_bin_%d\tlnN\t-\t-\t%0.2f\n'%('chAll','18',i,non_prompt_binerror))

   print 'bin ',i,' ',ZA_sig_binerror,' ',ZA_binerror,' ',non_prompt_binerror,' '

