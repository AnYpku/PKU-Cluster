#!/bin/bash
group=("Stat" "theory" "JESR" "luminosity" "pu" "fake" "muon" "egamma" "Others" "pref" "pileupId" "freezeAll")
#year=("16" "17" "18" "_RunII")
#year=("full16_test" "full17_test" "full18_test" "full_RunII")
year=("full18_test")
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
      if [[ ${group[${j}]} =~ "All" ]]; then
         sed -n -e '/tot/p' result_freezeAll_${year[$i]}.txt > tmp_freezeAll_${year[$i]}.txt
      else 
         sed -n -e '/tot/p' result_freeze_${group[$j]}_${year[$i]}.txt > tmp_${group[$j]}_${year[$i]}.txt
      fi
      python extract.py ${group[$j]} ${year[$i]}
   done
done
