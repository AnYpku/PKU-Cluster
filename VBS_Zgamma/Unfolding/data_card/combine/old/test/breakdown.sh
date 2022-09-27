#!/bin/bash
files="\
ptlep1_16.root
"
#ptlep1_17.root 
#ptlep1_18.root
#ptlep1_full.root
#photonet_16.root
#photonet_17.root
#photonet_18.root
#photonet_full.root
#jet1pt_16.root
#jet1pt_17.root
#jet1pt_18.root
#jet1pt_full.root
#"
for rootfile in $files
do
    filename=`echo $rootfile | awk -F. '{print $1}'`
    combine -M MultiDimFit --setParameters=r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1 -t -1 -m 125 $rootfile  -n .snapshot_${filename} --saveWorkspace
    for (( i = 1 ; i <= 1 ; i++ ))
    do
      combine -M MultiDimFit --setParameters=r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1 -t -1 -m 125 --algo=grid --points=100 -P r_Bin${i} --setParameterRanges r_Bin${i}=-2,4 --floatOtherPOIs=1 $rootfile -n .${filename}_rBin${i} 
      combine -M MultiDimFit --setParameters=r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1 -t -1 -m 125 --algo=grid --points=100 --freezeParameters all --snapshotName MultiDimFit -P r_Bin${i} --setParameterRanges r_Bin${i}=-2,4 --floatOtherPOIs=1  higgsCombine.snapshot_${filename}.MultiDimFit.mH125.root -n .freezeAll_${filename}_rBin${i} 
      python plot1DScan.py higgsCombine.${filename}_rBin${i}.MultiDimFit.mH125.root --POI r_Bin${i} -o signal_scan_${filename}_rBin${i}
      python plot1DScan.py higgsCombine.${filename}_rBin${i}.MultiDimFit.mH125.root --others "higgsCombine.freezeAll_${filename}_rBin${i}.MultiDimFit.mH125.root:FreezeAll:2" -o freeze_${filename}_rBin${i} --breakdown Syst,Stat --POI r_Bin${i}
      combine -M MultiDimFit --setParameters=r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1 -t -1 -m 125 --algo singles --freezeParameters all --snapshotName MultiDimFit -P r_Bin${i} --setParameterRanges r_Bin${i}=-2,4 --floatOtherPOIs=1  higgsCombine.snapshot_${filename}.MultiDimFit.mH125.root >> tmp_${filename}.txt
    done
    sed -n -e '/68/p' tmp_${filename}.txt > r_${filename}.txt
done

