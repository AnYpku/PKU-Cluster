#!/usr/bin/env python

from ROOT import gROOT, THStack, TH1D, TList, TFile

print '-----begin to transfer TH2D to txt for Higgs-combine tool----- \n'
dir16="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/data_card/2016/Mva/"
dir17="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/data_card/2017/Mva/"
dir18="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/data_card/2018/Mva/"
f_in16 = TFile.Open(dir16+"aa.root")
f_data16 = TFile.Open(dir16+"hist_Data.root")
f_sig16 = TFile.Open(dir16+"root/hist_ZA-EWK.root")
tstack16 = f_in16.Get("hs")
hist_data = f_data16.Get("hist");
t_list16 = tstack16.GetHists()

f_in17 = TFile.Open(dir17+"aa.root")
f_data17 = TFile.Open(dir17+"hist_Data.root")
f_sig17 = TFile.Open(dir17+"root/hist_ZA-EWK.root")
tstack17 = f_in17.Get("hs")
hist_data17 = f_data17.Get("hist");
t_list17 = tstack17.GetHists()

f_in18 = TFile.Open(dir18+"aa.root")
f_data18 = TFile.Open(dir18+"hist_Data.root")
f_sig18 = TFile.Open(dir18+"root/hist_ZA-EWK.root")
tstack18 = f_in18.Get("hs")
hist_data18 = f_data18.Get("hist");
t_list18 = tstack18.GetHists()

th1_ST = t_list16.At(0)
th1_TTA = t_list16.At(1)
th1_VV = t_list16.At(2)
th1_WA = t_list16.At(3)
th1_non_prompt = t_list16.At(4)
th1_ZA = t_list16.At(5)
th1_ZA_sig = t_list16.At(6)
th1_ZA_sig_out = t_list16.At(7)

th1_ST17 = t_list17.At(0)
th1_TTA17 = t_list17.At(1)
th1_VV17 = t_list17.At(2)
th1_WA17 = t_list17.At(3)
th1_non_prompt17 = t_list17.At(4)
th1_ZA17 = t_list17.At(5)
th1_ZA_sig17 = t_list17.At(6)
th1_ZA_sig_out17 = t_list17.At(7)

th1_ST18 = t_list18.At(0)
th1_TTA18 = t_list18.At(1)
th1_VV18 = t_list18.At(2)
th1_WA18 = t_list18.At(3)
th1_non_prompt18 = t_list18.At(4)
th1_ZA18 = t_list18.At(5)
th1_ZA_sig18 = t_list18.At(6)
th1_ZA_sig_out18 = t_list18.At(7)

th1_ST.Add(th1_ST17)
th1_ST.Add(th1_ST18)
th1_TTA.Add(th1_TTA17)
th1_TTA.Add(th1_TTA18)
th1_VV.Add(th1_VV17)
th1_VV.Add(th1_VV18)
th1_WA.Add(th1_WA17)
th1_WA.Add(th1_WA18)
th1_non_prompt.Add(th1_non_prompt17)
th1_non_prompt.Add(th1_non_prompt18)
th1_ZA.Add(th1_ZA17)
th1_ZA.Add(th1_ZA18)
th1_ZA_sig.Add(th1_ZA_sig17)
th1_ZA_sig.Add(th1_ZA_sig18)
th1_ZA_sig_out.Add(th1_ZA_sig_out17)
th1_ZA_sig_out.Add(th1_ZA_sig_out18)
hist_data.Add(hist_data17)
hist_data.Add(hist_data18)
genbin=[]
print '>>>>begin to read bin content to the txt file>>>>'
jer=[1.005,1.002,1.005,1.026,1.019,1.003,1.003,1.005,1.005]
jes=[1.013,1.025,1.028,1.017,1.008,1.035,1.035,1.078,1.043]
jet=[1.067,1.078,1.151,1.07,1.083,1.063,1.067,1.068,1.065]
pdf_QCD=[1.012,1.02,1.025,1.020,1.044,1.027,1.023,1.021,1.018]
pdf_ewk=[1.035,1.036,1.039,1.041,1.037,1.04,1.052,1.064,1.041]
scale_QCD=[1.094,1.13,1.3,1.138,1.163,1.137,1.041,1.178,1.159]
scale_ewk=[1.027,1.043,1.079,1.023,1.044,1.091,1.075,1.042,1.126]

for i in range(1,3):
   f = open('./txt/%s_bin_%d.txt'%('Mva', i),'w')
   f.write('imax 1   number of channels\n')
   f.write('jmax 8   number of processes-1\n')
   f.write('kmax 1  number of nuisance parameters (sources of systematical uncertainties)\n')
   f.write('------------\n')
   f.write('# we have just one channel, in which we observe 0 events\n')
   f.write('bin recobin%i\n'%(i))
   bin_content = hist_data.GetBinContent(i) 
   genhist =f_sig16.Get("hist5_{}".format(i)) 
   genhist17 =f_sig17.Get("hist5_{}".format(i)) 
   genhist18 =f_sig18.Get("hist5_{}".format(i)) 
   for k in range(1,3):
	   genbin.append(genhist.GetBinContent(k)+genhist17.GetBinContent(k)+genhist18.GetBinContent(k))
# bincontent of each precess
   ST_bincontent = th1_ST.GetBinContent(i) if th1_ST.GetBinContent(i)>0 else 0
   TTA_bincontent = th1_TTA.GetBinContent(i) if th1_TTA.GetBinContent(i)>0 else 0
   VV_bincontent = th1_VV.GetBinContent(i) if th1_VV.GetBinContent(i)>0 else 0
   WA_bincontent = th1_WA.GetBinContent(i) if th1_WA.GetBinContent(i) else 0
   non_prompt_bincontent = th1_non_prompt.GetBinContent(i) if th1_non_prompt.GetBinContent(i)>0 else 0
   ZA_bincontent = th1_ZA.GetBinContent(i) if th1_ZA.GetBinContent(i) else 0
   ZA_sig_bincontent = th1_ZA_sig.GetBinContent(i)  if th1_ZA_sig.GetBinContent(i)>0 else 0
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

   ZA_sig_binerror = th1_ZA_sig.GetBinError(i)/ZA_sig_bincontent if ZA_sig_bincontent>0 else 0
   ZA_sig_binerror = ZA_sig_binerror if ZA_sig_binerror<1 else 1
   ZA_sig_binerror = ZA_sig_binerror+1

   ZA_sig_out_binerror = th1_ZA_sig_out.GetBinError(i)/ZA_sig_out_bincontent if ZA_sig_out_bincontent>0 else 0
   ZA_sig_out_binerror = ZA_sig_out_binerror if ZA_sig_out_binerror<1 else 1
   ZA_sig_out_binerror = ZA_sig_out_binerror+1

   f.write('observation %.2f\n'%bin_content)
   f.write('------------\n')
   f.write('# now we list the expected events for signal and all backgrounds in that bin\n')
   f.write('# the second process line must have a positive number for backgrounds, and 0 for signal\n')
   f.write('# then we list the independent sources of uncertainties, and give their effect (syst. error)\n')
   f.write('# on each process and bin\n')
   f.write('bin\trecobin%i\trecobin%i\trecobin%i\trecobin%i\trecobin%i\trecobin%i\trecobin%i\trecobin%i\trecobin%i\n'%(i,i,i,i,i,i,i,i,i))
   f.write('process\tgenbin1\tgenbin2\tQCD\tnon_prompt\tTTA\tVV\tST\tWA\tSig_out\n')
   f.write('process\t-2\t-1\t0\t1\t2\t3\t4\t5\t6\n')
#   f.write('rate\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\n'%(genbincontent[0],genbincontent[1],genbincontent[2],genbincontent[3],genbincontent[4],genbincontent[5],ZA_bincontent, non_prompt_bincontent, TTA_bincontent, VV_bincontent, ST_bincontent, WA_bincontent))
   f.write('rate\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\t%0.2f\n'%(genbin[0],genbin[1],ZA_bincontent, non_prompt_bincontent, TTA_bincontent, VV_bincontent, ST_bincontent, WA_bincontent,ZA_sig_out_bincontent))
   f.write('------------\n')
   f.write('lumi\tlnN\t1.025\t1.025\t1.025\t-\t1.025\t1.025\t1.025\t1.025\t1.025\t#lumi\n')
#   f.write('QCD_%s_%s\tlnN\t-\t1.07\t-\t-\t-\t-\t-\t#0.06 uncertainty on QCD ZA cross section in muon_barrel\n'%('muon','barrel'))
#   if non_prompt_bincontent==0:
#       f.write('fake_%s_%s\tlnN\t-\t-\t-\t-\t-\t-\t-\t#0. uncertainty on muon_barrel\n'%('muon','barrel'))
#   else: 
#       f.write('fake_%s_%s\tlnN\t-\t-\t%0.2f\t-\t-\t-\t-\t#0. uncertainty on muon_barrel\n'%('muon','barrel',jet[i-1]))
#   f.write('VBS_stat_%s_%s_bin_%d\tlnN\t%0.2f\t-\t-\t-\t-\t-\t-\n'%('muon','barrel',i,ZA_sig_binerror))
#   f.write('QCD_stat_%s_%s_bin_%d\tlnN\t-\t%0.2f\t-\t-\t-\t-\t-\n'%('muon','barrel',i,ZA_binerror))
#   f.write('non_prompt_stat_%s_%s_bin_%d\tlnN\t-\t-\t%0.2f\t-\t-\t-\t-\n'%('muon','barrel',i,non_prompt_binerror))
#   f.write('TTA_stat_%s_%s_bin_%d\tlnN\t-\t-\t-\t%0.2f\t-\t-\t-\n'%('muon','barrel',i,TTA_binerror))
#   f.write('VV_stat_%s_%s_bin_%d\tlnN\t-\t-\t-\t-\t%0.2f\t-\t-\n'%('muon','barrel',i,VV_binerror))
#   f.write('ST_stat_%s_%s_bin_%d\tlnN\t-\t-\t-\t-\t-\t%0.2f\t-\n'%('muon','barrel',i,ST_binerror))
#   f.write('WA_stat_%s_%s_bin_%d\tlnN\t-\t-\t-\t-\t-\t-\t%0.2f\n'%('muon','barrel',i,WA_binerror))
#   f.write('JES_%s_%s\tlnN\t%0.2f\t-\t-\t%0.2f\t%0.2f\t%0.2f\t%0.2f\n'%('muon','barrel',jes[i-1],jes[i-1],jes[i-1],jes[i-1],jes[i-1]))
#   f.write('JER_%s_%s\tlnN\t%0.2f\t-\t-\t%0.2f\t%0.2f\t%0.2f\t%0.2f\n'%('muon','barrel',jer[i-1],jer[i-1],jer[i-1],jer[i-1],jer[i-1]))
#   f.write('QCDZA_pdf_%s_%s\tlnN\t-\t%0.2f\t-\t-\t-\t-\t-\n'%('muon','barrel',pdf_QCD[i-1]))
#   f.write('QCDZA_scale_%s_%s\tlnN\t-\t%0.2f\t-\t-\t-\t-\t-\n'%('muon','barrel',scale_QCD[i-1]))
#   f.write('pdf_%s_%s\tlnN\t%0.2f\t-\t-\t%0.2f\t%0.2f\t%0.2f\t%0.2f\n'%('muon','barrel',pdf_ewk[i-1],pdf_ewk[i-1],pdf_ewk[i-1],pdf_ewk[i-1],pdf_ewk[i-1]))
#   f.write('scale_%s_%s\tlnN\t%0.2f\t-\t-\t%0.2f\t%0.2f\t%0.2f\t%0.2f\n'%('muon','barrel',scale_ewk[i-1],scale_ewk[i-1],scale_ewk[i-1],scale_ewk[i-1],scale_ewk[i-1]))
#   f.write('trigger\tlnN\t1.02\t-\t-\t1.02\t1.02\t1.02\t1.02\n')
#   f.write('lepton_efficiency\tlnN\t1.005\t-\t-\t1.005\t1.005\t1.005\t1.005\n')
#   f.write('pileup\tlnN\t1.001\t-\t-\t1.001\t1.001\t1.001\t1.001\n')
#   f.write('photon_id\tlnN\t1.03\t-\t-\t1.03\t1.03\t1.03\t1.03\n')
#   f.write('interference\tlnN\t1.01\t-\t-\t-\t-\t-\t-\n')
#   f.write('ttgamma_xs\tlnN\t-\t-\t-\t1.1\t-\t-\t-\n')

   print 'bin ',i,' ',ZA_sig_binerror,' ',ZA_binerror,' ',non_prompt_binerror,' ',TTA_binerror,' ',VV_binerror,' ',ST_binerror,' ',WA_binerror,' ',ZA_sig_out_binerror
   genbin[:]=[]
   


