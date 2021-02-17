#!/bin/bash
group=("Stat" "theory" "JESR" "luminosity" "pu" "fake" "muon" "egamma" "Others" "pref" "pileupId" )
#channel=("mubarrel" "elebarrel" "muendcap" "eleendcap" )
channel=( "eleendcap" )
#year=("16" "17" "18")
year=("17")
for (( i = 3 ; i < 4 ; i++ ))
do
  for (( j =0 ; j < ${#year[@]} ; j++ ))
  do
    for (( k = 0 ; k< ${#channel[@]}; k++ ))
    do
      combineCards.py ./data_cards/${channel[$k]}_${year[$j]}_bin${i}.txt -S > shape_${channel[$k]}_${year[$j]}_bin${i}.txt
      combine -M FitDiagnostics -t -1 --expectSignal 1 --freezeParameters all shape_${channel[$k]}_${year[$j]}_bin${i}.txt  > tmp_freezeAll_${channel[$k]}_${year[$j]}_bin${i}.txt
      sed -n -e '/68\%/p'  tmp_freezeAll_${channel[$k]}_${year[$j]}_bin${i}.txt  > result_freezeAll_${channel[$k]}_${year[$j]}_bin${i}.txt
      for (( ik = 0 ; ik < ${#group[@]} ; ik++  ))
      do
         if [[ ${year[$j]} =~ "16"  ]] && [[ ${group[${ik}]} =~ "pileupId" ]]; then
             continue;
         fi
         if [[ ${year[$j]} =~ "18"  ]] && [[ ${group[${ik}]} =~ "pileupId" ]]; then
             continue;
         fi
         if [[ ${year[$j]} =~ "18"  ]] && [[ ${group[${ik}]} =~ "pref" ]]; then
             continue;
         fi
         if [[ ${channel[$k]} =~ "ele"  ]] && [[ ${group[${ik}]} =~ "muon" ]]; then
             continue;
         fi
         echo "${channel[$k]}_${year[$j]}_bin${i}.txt ${group[${ik}]}"
         combine -M FitDiagnostics -t -1 --expectSignal 1 --freezeNuisanceGroups ${group[${ik}]} shape_${channel[$k]}_${year[$j]}_bin${i}.txt  > tmp_${group[${ik}]}_${channel[$k]}_${year[$j]}_bin${i}.txt
         sed -n -e '/68\%/p' tmp_${group[${ik}]}_${channel[$k]}_${year[$j]}_bin${i}.txt > result_${group[${ik}]}_${channel[$k]}_${year[$j]}_bin${i}.txt
      done
    done
  done
done
