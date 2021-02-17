#!/bin/bash/

#cp ../full* ./
files="\
full16_test.root
full17_test.root
full18_test.root
full_RunII.root
"
group=("Stat" "theory" "JESR" "fake" "muon" "egamma" "pref" "pu" "pileupId" "Others")
#group=("egamma")

for rootfile in $files
do
    name=`echo $rootfile | awk -F. '{print $1}'`
    sed 's/lnN.*$//' ${name}.txt >tmp1
    sed  's/\s\+$//g' tmp1 >tmp
    num=`sed -n -e '/rate/=' tmp`
    line=$[$num+1]
    echo "$line"
    sed -i "1,$line d" tmp
    theory=`sed -n -e '/theory/p' tmp`
    sed -i '/group/d' tmp
    sed -i '/ST_Stat_control_bin1_eleendcap/d' tmp
    echo "$theory"
    sed -i ':label;N;s/\n/,/;t label' tmp
    #sed -i "$ a $theory" tmp
    mv tmp freeze_${name}.txt
    NP=`cat freeze_${name}.txt`
    #echo "$NP"
    
#    combine -M MultiDimFit --algo grid --points 50 --rMin 0.2 --rMax 4 -m 125 -n nominal_${name} ${name}.root --expectSignal=1 -t -1 
#    combine -M MultiDimFit --algo none --rMin 0.2 --rMax 4 -m 125 -n bestfit_${name} --saveWorkspace ${name}.root --expectSignal=1  -t -1 
#    combine -M MultiDimFit --algo grid --points 50 --rMin 0.2 --rMax 4 -m 125 -n stat_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeParameters $NP --expectSignal=1 -t -1 
    #
#    plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root \
#    --others "higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:2" \
#    --breakdown syst,stat -o scan_${name}
    for (( i = 0 ; i < ${#group[@]} ; i++  ))    
    do
#        combine -M MultiDimFit --algo grid --points 50  --rMin 0.2 --rMax 4 -m 125 -n ${group[${i}]}_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeNuisanceGroups ${group[${i}]} --expectSignal=1 -t -1
        #
#        plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root --others \
#        "higgsCombine${group[${i}]}_${name}.MultiDimFit.mH125.root:Freeze ${group[${i}]}:4" \
#        "higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:2" \
#        --breakdown ${group[${i}]},syst,stat -o scan_freeze_${group[${i}]}_${name}
#
        plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root \
        --others "higgsCombine${group[${i}]}_${name}.MultiDimFit.mH125.root:Freeze all:2" \
        --breakdown ${group[${i}]},left -o scan_${group[${i}]}_${name}
#
    done
done
