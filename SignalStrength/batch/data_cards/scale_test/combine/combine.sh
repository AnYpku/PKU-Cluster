#!/bin/bash/
#rm *.txt
cp ../txt/*16*.txt ./
cp ../CR/txt/*16*.txt ./
cp ../txt/*17*.txt ./
cp ../CR/txt/*17*.txt ./
cp ../txt/*18*.txt ./
cp ../CR/txt/*18*.txt ./
combineCards.py mubarrel_16_* muendcap_16_* elebarrel_16_* eleendcap_16_* >& full16_test.txt
combineCards.py mubarrel_17_* muendcap_17_* elebarrel_17_* eleendcap_17_* >& full17_test.txt
combineCards.py mubarrel_18_* muendcap_18_* elebarrel_18_* eleendcap_18_* >& full18_test.txt
text2workspace.py full16_test.txt -m 125 
text2workspace.py full17_test.txt -m 125 
text2workspace.py full18_test.txt -m 125 
#full_RunII.root
files="\
full18_test.root
full16_test.root
full17_test.root
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
#combine -M MultiDimFit --algo grid --points 50 --rMin 0.2 --rMax 4 -m 125 -n nominal ${name}.root --expectSignal=1 #-t -1 
combineCards.py ${name}.txt -S > shape_${name}.txt
combine -M MultiDimFit --algo none --rMin 0.2 --rMax 4 -m 125 -n bestfit_${name} --saveWorkspace ${name}.root --expectSignal=1  #-t -1 
for (( i = 1 ; i <= 3 ; i++))
do
combine -M MultiDimFit -m 125 --algo impact -P Scale_QCD_band${i} ${name}.txt --expectSignal=1 >>impact_${name}.txt
done
combine -M FitDiagnostics shape_${name}.txt -t -1 --expectSignal 1 > result_${name}.txt
#combine -M MultiDimFit --algo grid --points 50 --rMin 0.2 --rMax 4 -m 125 -n stat higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeParameters $NP --expectSignal=1 #-t -1 

#plot1DScan.py higgsCombinenominal.MultiDimFit.mH125.root \
#--others 'higgsCombinestat.MultiDimFit.mH125.root:Freeze all:2' \
#--breakdown syst,stat

#combine -M MultiDimFit --algo grid --points 50  --rMin 0.2 --rMax 4 -m 125 -n theory higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeNuisanceGroups theory --expectSignal=1

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
