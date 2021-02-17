#!/bin/bash
channel=("mubarrel" "muendcap" "elebarrel" "eleendcap")
year=("16" "18")
#year=("17")
for (( j = 0 ; j < ${#year[@]} ; j++ ))
do
    for (( i = 0 ; i < ${#channel[@]} ; i++ ))
    do
#    rm ${channel[$i]}_${year[$j]}.txt
    combineCards.py ${channel[$i]}_${year[$j]}_bin*.txt  >& ${channel[$i]}_${year[$j]}.txt
    combine -M Significance --expectSignal=1 -t -1 ${channel[$i]}_${year[$j]}.txt > result_${channel[$i]}_${year[$j]}.txt
    done
done
