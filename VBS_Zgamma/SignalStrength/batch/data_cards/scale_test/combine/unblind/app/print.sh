#!/bin/bash
group=("Stat" "theory" "JESR" "luminosity" "pu" "fake" "muon" "egamma" "Others" "pref" "pileupId" )
year=("16" "17" "18" "_RunII")
#year=("16")
for (( i = 0 ; i < ${#year[@]} ; i++ ))
do
      cp ../
      sed -n -e '/68\%/p' result_full${year[$i]}_test.txt > tmp_full${year[$i]}_test.txt
      python extract.py ${year[$i]}
done
