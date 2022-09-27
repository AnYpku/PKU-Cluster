#!/bin/bash
vars=("photonet" "mllg" "mll")
year=("17" "18")
njets=("1jets" "2jets")
for (( j = 0 ; j < ${#year[@]} ; j++ ))
do
    python th2_to_txt.py  ${year[$j]} "0jets" "mT_puppi"
    for (( i = 0 ; i < ${#vars[@]} ; i++ ))
    do
        for  (( k = 0 ; k < ${#njets[@]} ; k++ ))
        do
          python th2_to_txt.py ${year[$j]} ${njets[$k]} ${vars[$i]}
        done
    done
done
sh execute16.sh
