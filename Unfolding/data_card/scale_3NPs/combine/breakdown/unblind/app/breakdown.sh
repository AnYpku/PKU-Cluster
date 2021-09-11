#!/bin/bash
files="\
Mjj_full.root
photonet_full.root
jet1pt_full.root
ptlep1_16.root
ptlep1_17.root 
ptlep1_18.root
ptlep1_full.root
"
for rootfile in $files
do
    cp ../../unblind/$rootfile ./
    filename=`echo $rootfile | awk -F. '{print $1}'`
    echo "${filename}"
    if [[ $rootfile =~ "Mjj" ]];then
        combine -M MultiDimFit --setParameters=r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1,r_Bin5=1,r_Bin6=1,r_Bin7=1 -m 125 $rootfile  -n .snapshot_${filename} --saveWorkspace
        num=7
        init=7
    else
        combine -M MultiDimFit --setParameters=r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1 -m 125 $rootfile  -n .snapshot_${filename} --saveWorkspace
	num=4
        init=1
    fi
    for (( i = $init ; i <= $num ; i++ ))
    do
        if [[ $rootfile =~ "Mjj" ]];then
             combine -M MultiDimFit --setParameters=r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1,r_Bin5=1,r_Bin6=1,r_Bin7=1 -m 125 --algo=grid --points=50 -P r_Bin${i} --setParameterRanges r_Bin${i}=-20,20 --floatOtherPOIs=1 $rootfile -n .${filename}_rBin${i} 
             combine -M MultiDimFit --setParameters=r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1,r_Bin5=1,r_Bin6=1,r_Bin7=1 -m 125 --algo=grid --points=50 --freezeParameters all --snapshotName MultiDimFit -P r_Bin${i} --setParameterRanges r_Bin${i}=-20,20 --floatOtherPOIs=1  higgsCombine.snapshot_${filename}.MultiDimFit.mH125.root -n .freezeAll_${filename}_rBin${i} 

             combine -M MultiDimFit --setParameters=r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1,r_Bin5=1,r_Bin6=1,r_Bin7=1 -m 125 --algo singles --freezeParameters all --snapshotName MultiDimFit -P r_Bin${i} --setParameterRanges r_Bin${i}=-20,20 --floatOtherPOIs=1  higgsCombine.snapshot_${filename}.MultiDimFit.mH125.root >> tmp_${filename}.txt
        else
             combine -M MultiDimFit --setParameters=r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1 -m 125 --algo=grid --points=50 -P r_Bin${i} --setParameterRanges r_Bin${i}=-20,20 --floatOtherPOIs=1 $rootfile -n .${filename}_rBin${i} 
             combine -M MultiDimFit --setParameters=r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1 -m 125 --algo=grid --points=50 --freezeParameters all --snapshotName MultiDimFit -P r_Bin${i} --setParameterRanges r_Bin${i}=-20,20 --floatOtherPOIs=1  higgsCombine.snapshot_${filename}.MultiDimFit.mH125.root -n .freezeAll_${filename}_rBin${i} 

             combine -M MultiDimFit --setParameters=r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1 -m 125 --algo singles --freezeParameters all --snapshotName MultiDimFit -P r_Bin${i} --setParameterRanges r_Bin${i}=-20,20 --floatOtherPOIs=1  higgsCombine.snapshot_${filename}.MultiDimFit.mH125.root >> tmp_${filename}.txt
        fi
	python plot1DScan.py higgsCombine.${filename}_rBin${i}.MultiDimFit.mH125.root --POI r_Bin${i} -o signal_scan_${filename}_rBin${i}
	python plot1DScan.py higgsCombine.${filename}_rBin${i}.MultiDimFit.mH125.root --others "higgsCombine.freezeAll_${filename}_rBin${i}.MultiDimFit.mH125.root:FreezeAll:2" -o freeze_${filename}_rBin${i} --breakdown Syst,Stat --POI r_Bin${i}
    done
    sed -n -e '/68/p' tmp_${filename}.txt > r_${filename}.txt
done

