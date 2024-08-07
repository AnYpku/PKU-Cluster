#!/bin/bash/

#cp ../full* ./
#full17_test.root
#full18_test.root
#full_RunII.root
files="\
full16_test.root
"
for rootfile in $files
do
      name=`echo $rootfile | awk -F. '{print $1}'` 
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

#     combine -M MultiDimFit --algo grid --points 50 --rMin 0.4 --rMax 2 -m 125 -n nominal_${name} ${name}.root --expectSignal=1 -t -1 
#     combine -M MultiDimFit --algo none --rMin 0.4 --rMax 4 -m 125 -n bestfit_${name} --saveWorkspace ${name}.root --expectSignal=1  -t -1
     combine -M MultiDimFit --algo grid --points 50 --rMin 0.4 --rMax 2 -m 125 -n stat_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeParameters $NP --expectSignal=1 -t -1
    plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root \
    --others "higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:2" \
    --breakdown syst,stat -o scan_${name}

     done
