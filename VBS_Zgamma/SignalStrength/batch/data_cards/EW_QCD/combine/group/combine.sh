#!/bin/bash/

#cp ../full* ./
files="\
full16_test.root
"
#full17_test.root
#full18_test.root
#full_RunII.root
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
sed -i '/TTA_Stat_bin1_eleendcap/d' tmp
echo "$theory"
sed -i ':label;N;s/\n/,/;t label' tmp
#sed -i "$ a $theory" tmp
mv tmp freeze_${name}.txt
NP=`cat freeze_${name}.txt`
echo "$NP"
#combine -M MultiDimFit --algo grid --points 50 --rMin 0.6 --rMax 3 -m 125 -n nominal_${name} ${name}.root --expectSignal=1  -t -1
#-t -1 
#combine -M MultiDimFit --algo none --rMin 0.6 --rMax 3 -m 125 -n bestfit_${name} --saveWorkspace ${name}.root --expectSignal=1 -t -1 
#-t -1 
combine -M MultiDimFit --algo grid --points 50 --rMin 0.6 --rMax 3 -m 125 -n stat_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeParameters $NP --expectSignal=1 -t -1 


plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root \
--others "higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:2" \
--breakdown syst,stat -o scan_${name}

done
