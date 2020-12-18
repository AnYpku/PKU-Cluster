#!/bin/bash
genvar=("genlep1pt" "genphotonet" "genjet1pt" "genMjj")
recovar=("ptlep1" "photonet" "jet1pt" "Mjj")
#genvar=("genMjj")
#recovar=("Mjj")
# "Mjj" "Mva")
year=("16" "17" "18")
channel=("mubarrel" "elebarrel" "muendcap" "eleendcap")
for (( j = 0 ; j < ${#year[@]} ; j++ ))
do
    for (( i = 0 ; i < ${#genvar[@]} ; i++ ))
    do
        for(( k = 0 ; k < ${#channel[@]} ; k++ ))
        do
        python th2_to_txt.py ${genvar[$i]} ${recovar[$i]} ${year[$j]} ${channel[$j]}
        done
    done
done
