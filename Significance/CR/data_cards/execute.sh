#!/bin/bash
# "genMjj" "genZGmass")
channel=("mubarrel" "muendcap" "elebarrel" "eleendcap")
# "Mjj" "Mva")
year=("16" "17" "18")
#year=("16" "18")
for (( j = 0 ; j < ${#year[@]} ; j++ ))
do
    for (( i = 0 ; i < ${#channel[@]} ; i++ ))
    do
        python th2_to_txt.py ${year[$j]} ${channel[$i]}
    done
done
