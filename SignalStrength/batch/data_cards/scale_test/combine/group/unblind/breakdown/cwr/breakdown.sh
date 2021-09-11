#!/bin/bash/

files="\
full_RunII.root
"
#full16_test.root
#full18_test.root
#full17_test.root
for rootfile in $files
do
    echo "$name"
    name=`echo $rootfile | awk -F. '{print $1}'` 

    cp /home/pku/anying/cms/PKU-Cluster/SignalStrength/batch/data_cards/scale_test/combine/unblind/cwr/${name}.txt ./
    cp /home/pku/anying/cms/PKU-Cluster/SignalStrength/batch/data_cards/scale_test/combine/unblind/cwr/${name}.root ./

    sed 's/lnN.*$//' ${name}.txt >tmp1 #replace the content from lnN to the end of the line with none
    sed  's/\s\+$//g' tmp1 >tmp #delete extra space
    num=`sed -n -e '/rate/=' tmp` # print the line number
    line=$[$num+1]
    echo "$line" 
    sed -i "1,$line d" tmp # delete line from 1 to line
    theory=`sed -n -e '/theory/p' tmp` # print the line number
    sed -i '/group/d' tmp  # delete lines with group
    sed -i '/TTA_Stat_control_bin1_eleendcap/d' tmp # delete lines with ST_Stat_control_bin1_eleendcap
    echo "$theory" 
    sed -i ':label;N;s/\n/,/;t label' tmp # replace \n to ,
    mv tmp freeze_${name}.txt
    NP=`cat freeze_${name}.txt`

    echo "combine -M MultiDimFit --algo grid --points 50 --rMin 0.4 --rMax 4 -m 125 ${name}.root -n nominal_${name}.root"
    combine -M MultiDimFit --algo grid --points 50 --rMin 0.4 --rMax 4 -m 125 ${name}.root -n nominal_${name}
############################################################################################################################
    echo "combine -M MultiDimFit --algo singles --rMin 0.4 --rMax 4 -m 125 -n bestfit_${name} --saveWorkspace ${name}.root"
    combine -M MultiDimFit --algo singles --rMin 0.4 --rMax 4 -m 125 -n bestfit_${name} --saveWorkspace ${name}.root 
############################################################################################################################
    echo "combine -M MultiDimFit --algo grid --points 50 --rMin 0.4 --rMax 4 -m 125 -n freezeAll_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeParameters $NP"
    combine -M MultiDimFit --algo grid --points 50 --rMin 0.4 --rMax 4 -m 125 -n freezeAll_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeParameters $NP      
############################################################################################################################
    plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root \
    --others "higgsCombinefreezeAll_${name}.MultiDimFit.mH125.root:Freeze syst:2" \
    --breakdown syst,stat -o scan_freezeAll_${name} > result_freezeAll_${name}.txt

    group=("Stat" "theory" "JESR" "luminosity" "pu" "fake" "muon" "egamma" "Others" "pref" "pileupId" )
    for (( i = 0 ; i < ${#group[@]} ; i++  ))    
    do
      if [[ ${name} =~ "18" ]] && [[ ${group[${i}]} =~ "pref" ]]; then
         continue; 
      fi
      echo "combine -M MultiDimFit --algo grid --points 50 --rMin 0.4 --rMax 4 -m 125 -n freeze_${group[${i}]}_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeNuisanceGroups ${group[${i}]}"
      combine -M MultiDimFit --algo grid --points 50 --rMin 0.4 --rMax 4 -m 125 -n freeze_${group[${i}]}_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeNuisanceGroups ${group[${i}]} 
      plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root \
      --others "higgsCombinefreeze_${group[${i}]}_${name}.MultiDimFit.mH125.root:Freeze ${group[${i}]}:2" \
      --breakdown ${group[${i}]},left -o scan_freeze_${group[${i}]}_${name} > result_freeze_${group[${i}]}_${name}.txt
    done
done
mv -f scan*.pdf figs
mv -f scan*.png figs
mv -f scan*.root figs 
