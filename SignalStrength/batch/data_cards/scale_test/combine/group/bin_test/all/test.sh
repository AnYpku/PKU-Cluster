#!/bin/bash
group=("Stat" "theory" "JESR" "luminosity" "pu" "fake" "muon" "egamma" "Others" "pref" "pileupId" )
channel=("mubarrel" "elebarrel" "muendcap" "eleendcap" )
year=("16" "17" "18")
for (( i = 1 ; i < 7 ; i++ ))
do
  for (( j =0 ; j < ${#year[@]} ; j++ ))
  do
    for (( k = 0 ; k< ${#channel[@]}; k++ ))
    do
      combineCards.py ./data_cards/${channel[$k]}_${year[$j]}_bin${i}.txt -S > shape_${channel[$k]}_${year[$j]}_bin${i}.txt
      echo "${channel[$k]}_${year[$j]}_bin${i}.txt"
      combine -M FitDiagnostics -t -1 --expectSignal 1  shape_${channel[$k]}_${year[$j]}_bin${i}.txt  > tmp_${channel[$k]}_${year[$j]}_bin${i}.txt
      sed -n -e '/68\%/p' tmp_${channel[$k]}_${year[$j]}_bin${i}.txt > result_${channel[$k]}_${year[$j]}_bin${i}.txt
    done
  done
done
