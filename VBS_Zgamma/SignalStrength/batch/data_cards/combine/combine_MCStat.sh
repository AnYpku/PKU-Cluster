#!/bin/bash/
#cp ../txt/*16*.txt ./
#cp ../../CR/data_cards/txt/*16*.txt ./
#cp ../txt/*17*.txt ./
#cp ../../CR/data_cards/txt/*17*.txt ./
#cp ../txt/*18*.txt ./
#cp ../../CR/data_cards/txt/*18*.txt ./
#combineCards.py mubarrel_16_* muendcap_16_* elebarrel_16_* eleendcap_16_* >& full16_test.txt
#combineCards.py mubarrel_17_* muendcap_17_* elebarrel_17_* eleendcap_17_* >& full17_test.txt
#combineCards.py mubarrel_18_* muendcap_18_* elebarrel_18_* eleendcap_18_* >& full18_test.txt
#text2workspace.py full16_test.txt -m 125 
#text2workspace.py full17_test.txt -m 125 
#text2workspace.py full18_test.txt -m 125 
files="\
full16_test.root
full17_test.root
full18_test.root
"
#full16_test.root
#full17_test.root
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
echo "$theory"
sed -n '/Stat/p' tmp > tmp2
sed -i ':label;N;s/\n/,/;t label' tmp2
#sed -i "$ a $theory" tmp
mv tmp2 freeze_${name}.txt
NP=`cat freeze_${name}.txt`
echo "$NP"
combine -M MultiDimFit --algo grid --points 50 --rMin 0 --rMax 4 -m 125 -n nominal ${name}.root --expectSignal=1 #-t -1 
combine -M MultiDimFit --algo none --rMin 0 --rMax 4 -m 125 -n bestfit_${name} --saveWorkspace ${name}.root  --expectSignal=1 #-t -1
combine -M MultiDimFit --algo grid --points 50 --rMin 0 --rMax 4 -m 125 -n stat higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeParameters $NP --expectSignal=1 #-t -1 

plot1DScan.py higgsCombinenominal.MultiDimFit.mH125.root \
--others 'higgsCombinestat.MultiDimFit.mH125.root:Freeze all:2' \
--breakdown MC-stat,syst-no-MCStat -o scan_freezeMCStat_${name}

#combine -M MultiDimFit --algo grid --points 50  --rMin 0 --rMax 4 -m 125 -n theory higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeNuisanceGroups theory

#plot1DScan.py higgsCombinenominal.MultiDimFit.mH125.root --others \
#'higgsCombinetheory.MultiDimFit.mH125.root:Freeze th.:4' \
#'higgsCombinestat.MultiDimFit.mH125.root:Freeze all:2' \
#--breakdown theory,syst,stat -o scan_freeze_${name}

done
