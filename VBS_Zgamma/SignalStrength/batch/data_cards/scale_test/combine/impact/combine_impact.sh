#!/bin/bash/
cp ../full* ./
files="\
full16_test.root
full17_test.root
full18_test.root
full_RunII.root
"
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
sed -i '/theory/d' tmp
sed -i '/ST_Stat_control_bin1_eleendcap/d' tmp
echo "$theory"
sed -i ':label;N;s/\n/,/;t label' tmp
#sed -i "$ a $theory" tmp
mv tmp freeze_${name}.txt
NP=`cat freeze_${name}.txt`
#echo "$NP"

#### draw impact plot####

#combine -M MultiDimFit -m 125 --algo impact -P Scale_QCD ${name}.txt --expectSignal=1 >> impact_${name}.txt
#combine -M MultiDimFit -m 125 --algo impact -P Scale_QCD_extra ${name}.txt --expectSignal=1 >> impact_${name}.txt
combineTool.py -M Impacts -d ${name}.root -t -1 --expectSignal=1 -m 125 --doInitialFit --robustFit 1
combineTool.py -M Impacts -d ${name}.root -t -1 --expectSignal=1 -m 125 --robustFit 1 --doFits --parallel 8
combineTool.py -M Impacts -d ${name}.root -t -1 --expectSignal=1 -m 125 -o impacts_SS_${name}.json
plotImpacts.py -i impacts_SS_${name}.json -o impacts_SS_${name}

######## Uncertainty breakdown##########

#combine -M MultiDimFit --algo grid --points 50 --rMin 0.2 --rMax 4 -m 125 -n nominal ${name}.root --expectSignal=1 

#combine -M MultiDimFit --algo none --rMin 0.2 --rMax 4 -m 125 -n bestfit_${name} --saveWorkspace ${name}.root --expectSignal=1 

#combine -M MultiDimFit --algo grid --points 50 --rMin 0.2 --rMax 4 -m 125 -n stat higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeParameters $NP --expectSignal=1 #-t -1 

#plot1DScan.py higgsCombinenominal.MultiDimFit.mH125.root \
#--others 'higgsCombinestat.MultiDimFit.mH125.root:Freeze all:2' \
#--breakdown syst,stat
#
#combine -M MultiDimFit --algo grid --points 50  --rMin 0.2 --rMax 4 -m 125 -n theory higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeNuisanceGroups theory --expectSignal=1
#
#plot1DScan.py higgsCombinenominal.MultiDimFit.mH125.root --others \
#'higgsCombinetheory.MultiDimFit.mH125.root:Freeze th.:4' \
#'higgsCombinestat.MultiDimFit.mH125.root:Freeze all:2' \
#--breakdown theory,syst,stat -o scan_freeze_${name}

done

#years="\
#16
#17
#18
#"
#for year in $years
#do 
#combine -M MultiDimFit -m 125 --algo impact -P JES_${year} --expectSignal=1 full${year}_test.txt >> impact_JES${year}.txt
#done
