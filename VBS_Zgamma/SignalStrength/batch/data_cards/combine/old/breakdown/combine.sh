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
full_RunII.root
full18_test.root
full16_test.root
full17_test.root
"
for rootfile in $files
do
name=`echo $rootfile | awk -F. '{print $1}'`
sed 's/lnN.*$//' ${name}.txt >tmp1 #from lnN to the end of line replaced with space
sed  's/\s\+$//g' tmp1 >tmp        #delete the extra space at the end of line
num=`sed -n -e '/rate/=' tmp`      #print the number of line
line=$[$num+1]
echo "$line"
sed -i "1,$line d" tmp             #delete lines from 1 to $line
theory=`sed -n -e '/theory/p' tmp`
sed -i '/theory/d' tmp             #find lines containing theory and delete it
sed -i '/ST_Stat_control_bin1_eleendcap/d' tmp 
echo "$theory"
sed -i ':label;N;s/\n/,/;t label' tmp #replace \n to ,
#sed -i "$ a $theory" tmp
mv tmp freeze_${name}.txt
NP=`cat freeze_${name}.txt`
#echo "$NP"
#combine -M MultiDimFit --algo grid --points 50 --rMin 0.2 --rMax 4 -m 125 -n nominal ${name}.root --expectSignal=1   #-t -1 

combine -M MultiDimFit --algo none --rMin 0.2 --rMax 4 -m 125 -n bestfit_${name} --saveWorkspace ${name}.root --expectSignal=1  #-t -1 

#combine -M MultiDimFit --algo grid --points 50 --rMin 0.2 --rMax 4 -m 125 -n stat higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeParameters $NP --expectSignal=1 #-t -1 

combine -M MultiDimFit --algo singles --rMin 0.2 --rMax 4 -m 125 -n nominal ${name}.root --expectSignal=1   > tmp_${name}.txt

combine -M MultiDimFit --algo singles --rMin 0.2 --rMax 4 -m 125 -n stat higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeParameters $NP --expectSignal=1 > tmp_freeze_${name}.txt
#-t -1 
sed -n -e '/68%/p' tmp_${name}.txt > result_${name}.txt
sed -n -e '/68%/p' tmp_freeze_${name}.txt > result_freeze_${name}.txt
#plot1DScan.py higgsCombinenominal.MultiDimFit.mH125.root \
#--others 'higgsCombinestat.MultiDimFit.mH125.root:Freeze all:2' \
#--breakdown syst,stat

#combine -M MultiDimFit --algo grid --points 50  --rMin 0.2 --rMax 4 -m 125 -n theory higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeNuisanceGroups theory --expectSignal=1

#plot1DScan.py higgsCombinenominal.MultiDimFit.mH125.root --others \
#'higgsCombinetheory.MultiDimFit.mH125.root:Freeze th.:4' \
#'higgsCombinestat.MultiDimFit.mH125.root:Freeze all:2' \
#--breakdown theory,syst,stat -o scan_freeze_${name}

done
