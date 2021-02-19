#!/bin/bash
group=("Stat" "theory" "JESR" "luminosity" "pu" "fake" "muon" "egamma" "Others" "pref" "pileupId" )
#year=("16" "17" "18" "_RunII")
year=("17" "_RunII")
for (( i = 0 ; i < ${#year[@]} ; i++ ))
do
      sed -n -e '/68\%/p' result_all_full${year[$i]}_test.txt > tmp_all_full${year[$i]}_test.txt
      python extract.py ${year[$i]}
done
