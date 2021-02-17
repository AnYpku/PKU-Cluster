#!/bin/bash/

#cp ../full* ./
files="\
full16_test.root
full17_test.root
full18_test.root
full_RunII.root
"
#group=("Stat" "theory" "JESR" "fake" "muon" "egamma" "pref" "pu" "pileupId" "Others")

for rootfile in $files
do
        #
name=`echo $rootfile | awk -F. '{print $1}'`
if [[ $name =~ "17" ]]; then
        combine -M MultiDimFit --algo grid --points 50  --rMin 0.2 --rMax 4 -m 125 -n all_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeNuisanceGroups theory,JESR,Stat,egamma,muon,pref,pu,pileupId,fake,Others --expectSignal=1 -t -1
        plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root --others \
        "higgsCombineall_${name}.MultiDimFit.mH125.root:Freeze groups:4" \
        "higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:2" \
        --breakdown groups,syst,stat -o scan_freeze_all_${name}
fi
if [[ $name =~ "16" ]]; then
        combine -M MultiDimFit --algo grid --points 50  --rMin 0.2 --rMax 4 -m 125 -n all_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeNuisanceGroups theory,JESR,Stat,egamma,muon,pref,pu,fake,Others --expectSignal=1 -t -1
        plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root --others \
        "higgsCombineall_${name}.MultiDimFit.mH125.root:Freeze groups:4" \
        "higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:2" \
        --breakdown groups,syst,stat -o scan_freeze_all_${name}
fi
#
if [[ $name =~ "18" ]]; then
        combine -M MultiDimFit --algo grid --points 50  --rMin 0.2 --rMax 4 -m 125 -n all_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeNuisanceGroups theory,JESR,Stat,egamma,muon,pu,fake,Others --expectSignal=1 -t -1
        plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root --others \
        "higgsCombineall_${name}.MultiDimFit.mH125.root:Freeze groups:4" \
        "higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:2" \
        --breakdown groups,syst,stat -o scan_freeze_all_${name}
fi
#        plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root \
#        --others "higgsCombine${group[${i}]}_${name}.MultiDimFit.mH125.root:Freeze all:2" \
#        --breakdown ${group[${i}]},left -o scan_${group[${i}]}_${name}
#
done
