#!/bin/bash
channel=("mubarrel" "muendcap" "elebarrel" "eleendcap")
year=("16" "17" "18")
#year=("17")
for (( j = 0 ; j < ${#year[@]} ; j++ ))
do
        python th2_to_txt.py ${year[$j]} 
done
