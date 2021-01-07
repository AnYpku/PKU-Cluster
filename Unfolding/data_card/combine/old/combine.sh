#!/bin/sh
cp ../CR/txt/*control_bin*.txt ./
combineCards.py ptlep1_16_*bin*.txt >& ptlep1_16.txt
combineCards.py ptlep1_17_*bin*.txt >& ptlep1_17.txt
combineCards.py ptlep1_18_*bin*.txt >& ptlep1_18.txt
combineCards.py ptlep1_16.txt ptlep1_17.txt ptlep1_18.txt >&ptlep1_full.txt

combineCards.py photonet_16_*bin*.txt >& photonet_16.txt
combineCards.py photonet_17_*bin*.txt >& photonet_17.txt
combineCards.py photonet_18_*bin*.txt >& photonet_18.txt
combineCards.py photonet_16.txt photonet_17.txt photonet_18.txt  >& photonet_full.txt

combineCards.py jet1pt_16_*bin*.txt >& jet1pt_16.txt
combineCards.py jet1pt_17_*bin*.txt >& jet1pt_17.txt
combineCards.py jet1pt_18_*bin*.txt >& jet1pt_18.txt
combineCards.py jet1pt_16.txt jet1pt_17.txt jet1pt_18.txt >& jet1pt_full.txt

#########ptlep1
text2workspace.py -m 125 -o ptlep1_16.root ptlep1_16.txt -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO map='.*genbin1.*:r_Bin1[1,-2,4]' --PO map='.*genbin2.*:r_Bin2[1,-2,4]' --PO map='.*genbin3.*:r_Bin3[1,-2,4]' --PO map='.*genbin4.*:r_Bin4[1,-2,4]' 
combine ptlep1_16.root -M MultiDimFit --algo singles -t -1 --setParameters r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1 -m 125 --saveFitResult  > tmp_ptlep1_16.txt 
sed -n -e '/68/p' tmp_ptlep1_16.txt > result_ptlep1_16.txt
mv multidimfit.root multidimfit_ptlep1_16.root

text2workspace.py -m 125 -o ptlep1_17.root ptlep1_17.txt -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO map='.*genbin1.*:r_Bin1[1,-2,4]' --PO map='.*genbin2.*:r_Bin2[1,-2,4]' --PO map='.*genbin3.*:r_Bin3[1,-2,4]' --PO map='.*genbin4.*:r_Bin4[1,-2,4]' 
combine ptlep1_17.root -M MultiDimFit --algo singles -t -1 --setParameters r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1 -m 125 --saveFitResult  > tmp_ptlep1_17.txt 
sed -n -e '/68/p' tmp_ptlep1_17.txt > result_ptlep1_17.txt
mv multidimfit.root multidimfit_ptlep1_17.root

text2workspace.py -m 125 -o ptlep1_18.root ptlep1_18.txt -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO map='.*genbin1.*:r_Bin1[1,-2,4]' --PO map='.*genbin2.*:r_Bin2[1,-2,4]' --PO map='.*genbin3.*:r_Bin3[1,-2,4]' --PO map='.*genbin4.*:r_Bin4[1,-2,4]' 
combine ptlep1_18.root -M MultiDimFit --algo singles -t -1 --setParameters r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1 -m 125 --saveFitResult  > tmp_ptlep1_18.txt 
sed -n -e '/68/p' tmp_ptlep1_18.txt > result_ptlep1_18.txt
mv multidimfit.root multidimfit_ptlep1_18.root

text2workspace.py -m 125 -o ptlep1_full.root ptlep1_full.txt -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO map='.*genbin1.*:r_Bin1[1,-2,4]' --PO map='.*genbin2.*:r_Bin2[1,-2,4]' --PO map='.*genbin3.*:r_Bin3[1,-2,4]' --PO map='.*genbin4.*:r_Bin4[1,-2,4]' 
combine ptlep1_full.root -M MultiDimFit --algo singles -t -1 --setParameters r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1 -m 125 --saveFitResult  > tmp_ptlep1_full.txt 
sed -n -e '/68/p' tmp_ptlep1_full.txt > result_ptlep1_full.txt
mv multidimfit.root multidimfit_ptlep1_full.root

####photonet
text2workspace.py -m 125 -o photonet_16.root photonet_16.txt -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO map='.*genbin1.*:r_Bin1[1,-2,4]' --PO map='.*genbin2.*:r_Bin2[1,-2,4]' --PO map='.*genbin3.*:r_Bin3[1,-2,4]' --PO map='.*genbin4.*:r_Bin4[1,-2,4]' 
combine photonet_16.root -M MultiDimFit --algo singles -t -1 --setParameters r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1 -m 125 --saveFitResult  > tmp_photonet_16.txt 
sed -n -e '/68/p' tmp_photonet_16.txt > result_photonet_16.txt
mv multidimfit.root multidimfit_photonet_16.root

text2workspace.py -m 125 -o photonet_17.root photonet_17.txt -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO map='.*genbin1.*:r_Bin1[1,-2,4]' --PO map='.*genbin2.*:r_Bin2[1,-2,4]' --PO map='.*genbin3.*:r_Bin3[1,-2,4]' --PO map='.*genbin4.*:r_Bin4[1,-2,4]' 
combine photonet_17.root -M MultiDimFit --algo singles -t -1 --setParameters r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1 -m 125 --saveFitResult  > tmp_photonet_17.txt 
sed -n -e '/68/p' tmp_photonet_17.txt > result_photonet_17.txt
mv multidimfit.root multidimfit_photonet_17.root

text2workspace.py -m 125 -o photonet_18.root photonet_18.txt -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO map='.*genbin1.*:r_Bin1[1,-2,4]' --PO map='.*genbin2.*:r_Bin2[1,-2,4]' --PO map='.*genbin3.*:r_Bin3[1,-2,4]' --PO map='.*genbin4.*:r_Bin4[1,-2,4]' 
combine photonet_18.root -M MultiDimFit --algo singles -t -1 --setParameters r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1 -m 125 --saveFitResult  > tmp_photonet_18.txt 
sed -n -e '/68/p' tmp_photonet_18.txt > result_photonet_18.txt
mv multidimfit.root multidimfit_photonet_18.root

text2workspace.py -m 125 -o photonet_full.root photonet_full.txt -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO map='.*genbin1.*:r_Bin1[1,-2,4]' --PO map='.*genbin2.*:r_Bin2[1,-2,4]' --PO map='.*genbin3.*:r_Bin3[1,-2,4]' --PO map='.*genbin4.*:r_Bin4[1,-2,4]' 
combine photonet_full.root -M MultiDimFit --algo singles -t -1 --setParameters r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1 -m 125 --saveFitResult  > tmp_photonet_full.txt 
sed -n -e '/68/p' tmp_photonet_full.txt > result_photonet_full.txt
mv multidimfit.root multidimfit_photonet_full.root

##########jet1pt
text2workspace.py -m 125 -o jet1pt_16.root jet1pt_16.txt -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO map='.*genbin1.*:r_Bin1[1,-2,4]' --PO map='.*genbin2.*:r_Bin2[1,-2,4]' --PO map='.*genbin3.*:r_Bin3[1,-2,4]' --PO map='.*genbin4.*:r_Bin4[1,-2,4]' 
combine jet1pt_16.root -M MultiDimFit --algo singles -t -1 --setParameters r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1 -m 125 --saveFitResult  > tmp_jet1pt_16.txt 
sed -n -e '/68/p' tmp_jet1pt_16.txt > result_jet1pt_16.txt
mv multidimfit.root multidimfit_jet1pt_16.root

text2workspace.py -m 125 -o jet1pt_17.root jet1pt_17.txt -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO map='.*genbin1.*:r_Bin1[1,-2,4]' --PO map='.*genbin2.*:r_Bin2[1,-2,4]' --PO map='.*genbin3.*:r_Bin3[1,-2,4]' --PO map='.*genbin4.*:r_Bin4[1,-2,4]' 
combine jet1pt_17.root -M MultiDimFit --algo singles -t -1 --setParameters r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1 -m 125 --saveFitResult  > tmp_jet1pt_17.txt 
sed -n -e '/68/p'  tmp_jet1pt_17.txt > result_jet1pt_17.txt
mv multidimfit.root multidimfit_jet1pt_17.root

text2workspace.py -m 125 -o jet1pt_18.root jet1pt_18.txt -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO map='.*genbin1.*:r_Bin1[1,-2,4]' --PO map='.*genbin2.*:r_Bin2[1,-2,4]' --PO map='.*genbin3.*:r_Bin3[1,-2,4]' --PO map='.*genbin4.*:r_Bin4[1,-2,4]' 
combine jet1pt_18.root -M MultiDimFit --algo singles -t -1 --setParameters r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1 -m 125 --saveFitResult  > tmp_jet1pt_18.txt 
sed -n -e '/68/p' tmp_jet1pt_18.txt > result_jet1pt_18.txt
mv multidimfit.root multidimfit_jet1pt_18.root

text2workspace.py -m 125 -o jet1pt_full.root jet1pt_full.txt -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO map='.*genbin1.*:r_Bin1[1,-2,4]' --PO map='.*genbin2.*:r_Bin2[1,-2,4]' --PO map='.*genbin3.*:r_Bin3[1,-2,4]' --PO map='.*genbin4.*:r_Bin4[1,-2,4]' 
combine jet1pt_full.root -M MultiDimFit --algo singles -t -1 --setParameters r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1 -m 125 --saveFitResult  > tmp_jet1pt_full.txt 
sed -n -e '/68/p' tmp_jet1pt_full.txt > result_jet1pt_full.txt
mv multidimfit.root multidimfit_jet1pt_full.root

