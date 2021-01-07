#!/bin/bash
channel=("mu"  "ele")
year=("16" "17" "18")
#year=("17")
for (( i = 0 ; i < ${#channel[@]} ; i++ ))
do
    python to_txt_all.py "" ${channel[$i]}
    for (( j = 0 ; j < ${#year[@]} ; j++ ))
    do
      python to_txt.py ${year[$j]} ${channel[$i]}
    done
done
