#!/bin/bash/

#cp ../../txt/*16*.txt ./
#cp ../../../CR/data_cards/txt/*16*.txt ./
#cp ../../txt/*17*.txt ./
#cp ../../../CR/data_cards/txt/*17*.txt ./
#cp ../../txt/*18*.txt ./
#cp ../../../CR/data_cards/txt/*18*.txt ./
#combineCards.py mubarrel_16_* muendcap_16_* elebarrel_16_* eleendcap_16_* >& full16_test.txt
#combineCards.py mubarrel_17_* muendcap_17_* elebarrel_17_* eleendcap_17_* >& full17_test.txt
#combineCards.py mubarrel_18_* muendcap_18_* elebarrel_18_* eleendcap_18_* >& full18_test.txt
#combineCards.py mubarrel_16_* muendcap_16_* elebarrel_16_* eleendcap_16_* mubarrel_17_* muendcap_17_* elebarrel_17_* eleendcap_17_* mubarrel_18_* muendcap_18_* elebarrel_18_* eleendcap_18_*>& full_RunII.txt
#text2workspace.py full16_test.txt -m 125 
#text2workspace.py full17_test.txt -m 125 
#text2workspace.py full18_test.txt -m 125 
#text2workspace.py full_RunII.txt -m 125 
files="\
full_RunII.root
"
#full16_test.root
#full17_test.root
#full18_test.root
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
combine -M MultiDimFit --algo grid --points 50 --rMin 0.2 --rMax 4 -m 125 -n nominal_${name} ${name}.root --expectSignal=1 
#-t -1 
combine -M MultiDimFit --algo none --rMin 0.2 --rMax 4 -m 125 -n bestfit_${name} --saveWorkspace ${name}.root --expectSignal=1  
#-t -1 
combine -M MultiDimFit --algo grid --points 50 --rMin 0.2 --rMax 4 -m 125 -n stat_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeParameters $NP --expectSignal=1 #-t -1 


#combine -M MultiDimFit --algo grid --points 50  --rMin 0.2 --rMax 4 -m 125 -n theory_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeNuisanceGroups theory --expectSignal=1

#combine -M MultiDimFit --algo grid --points 50  --rMin 0.2 --rMax 4 -m 125 -n Stat_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeNuisanceGroups Stat --expectSignal=1

#combine -M MultiDimFit --algo grid --points 50  --rMin 0.2 --rMax 4 -m 125 -n JESR_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeNuisanceGroups JESR --expectSignal=1

#combine -M MultiDimFit --algo grid --points 50  --rMin 0.2 --rMax 4 -m 125 -n muon_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeNuisanceGroups muon --expectSignal=1

#combine -M MultiDimFit --algo grid --points 50  --rMin 0.2 --rMax 4 -m 125 -n ele_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeNuisanceGroups egamma --expectSignal=1

#combine -M MultiDimFit --algo grid --points 50  --rMin 0.2 --rMax 4 -m 125 -n Others_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeNuisanceGroups Others --expectSignal=1

#combine -M MultiDimFit --algo grid --points 50  --rMin 0.2 --rMax 4 -m 125 -n fake_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeNuisanceGroups fake --expectSignal=1

plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root \
--others "higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:2" \
--breakdown syst,stat -o scan_${name}

#plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root --others \
#"higgsCombinetheory_${name}.MultiDimFit.mH125.root:Freeze th.:4" \
#"higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:2" \
#--breakdown theory,syst,stat -o scan_freeze_theory_${name}
#
#plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root --others \
#"higgsCombineStat_${name}.MultiDimFit.mH125.root:Freeze MCstat.:4" \
#"higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:2" \
#--breakdown MCstat,syst,stat -o scan_freeze_MCstat_${name}
#
#plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root --others \
#"higgsCombineJESR_${name}.MultiDimFit.mH125.root:Freeze JESR.:4" \
#"higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:2" \
#--breakdown JESR,syst,stat -o scan_freeze_JESR_${name}
#
#plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root --others \
#"higgsCombineele_${name}.MultiDimFit.mH125.root:Freeze egamma:4" \
#"higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:2" \
#--breakdown egammaEff,syst,stat -o scan_freeze_egamma_${name}
#
#plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root --others \
#"higgsCombinemuon_${name}.MultiDimFit.mH125.root:Freeze muon:4" \
#"higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:2" \
#--breakdown muonEff,syst,stat -o scan_freeze_muon_${name}
#
#plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root --others \
#"higgsCombineOthers_${name}.MultiDimFit.mH125.root:Freeze Others.:4" \
#"higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:2" \
#--breakdown Others,syst,stat -o scan_freeze_Others_${name}

#plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root --others \
#"higgsCombinefake_${name}.MultiDimFit.mH125.root:Freeze Others.:4" \
#"higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:2" \
#--breakdown Others,syst,stat -o scan_freeze_fake_${name}
done
