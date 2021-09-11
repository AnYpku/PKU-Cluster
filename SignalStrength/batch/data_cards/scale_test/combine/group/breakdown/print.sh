#!/bin/bash
group=("Stat" "theory" "JESR" "luminosity" "pu" "fake" "muon" "egamma" "Others" "pref" "pileupId" "freezeAll")
year=("16" "17" "18" "_RunII")
#year=("17" "_RunII")
for (( i = 0 ; i < ${#year[@]} ; i++ ))
do
   if [[ -f r_${year[$i]}.txt ]];then
      rm r_${year[$i]}.txt
   fi
   for (( j = 0 ; j < ${#group[@]} ; j++ ))
   do
      if [[ ${year[$i]} =~ "18" ]] && [[ ${group[${j}]} =~ "pref" ]]; then
          continue;
      fi
      if [[ -f result_${group[$j]}_full_RunII.txt ]];then
         mv result_${group[$j]}_full_RunII.txt result_${group[$j]}_full_RunII_test.txt
      fi
      sed -n -e '/68\%/p' result_${group[$j]}_full${year[$i]}_test.txt > tmp_${group[$j]}_full${year[$i]}_test.txt
      python extract.py ${group[$j]} ${year[$i]}
   done
done
