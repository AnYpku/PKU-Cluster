#!/bin/bash
#genvar=("genlep1pt" "genphotonet" "genjet1pt" "genMjj")
 genvar=("genmassVlep" "genZGmass")
#recovar=("ptlep1" "photonet" "jet1pt" "Mjj")
recovar=("massVlep" "Mva")
year=("16" "17" "18")
for (( j = 0 ; j < ${#year[@]} ; j++ ))
do
    for (( i = 0 ; i < ${#genvar[@]} ; i++ ))
    do
        python th2_to_txt.py ${genvar[$i]} ${recovar[$i]} ${year[$j]}
    done
done
