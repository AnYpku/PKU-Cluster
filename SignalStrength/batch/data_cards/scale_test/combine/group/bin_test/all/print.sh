#!/bin/bash
group=("Stat" "theory" "JESR" "luminosity" "pu" "fake" "muon" "egamma" "Others" "pref" "pileupId" )
year=("16" "17" "18" )
channel=("mubarrel" "elebarrel" "muendcap" "eleendcap" )
for (( i = 1 ; i < 7 ; i++ ))
do
  for (( j =0 ; j < ${#year[@]} ; j++ ))
  do
    for (( k = 0 ; k< ${#channel[@]}; k++ ))
    do
      python extract.py ${i} ${channel[$k]} ${year[$j]}
    done
   done
done
