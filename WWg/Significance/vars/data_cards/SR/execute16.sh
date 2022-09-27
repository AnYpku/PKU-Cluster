#!/bin/bash
vars=("mllg" "photonet" "mll")
year=("16")
njets=("0jets" "1jets" "2jets")
for (( j = 0 ; j < ${#year[@]} ; j++ ))
do
    for (( i = 0 ; i < ${#vars[@]} ; i++ ))
    do
        for  (( k = 0 ; k < ${#njets[@]} ; k++ ))
        do
          python th2_to_txt.py ${year[$j]} ${njets[$k]} ${vars[$i]}
        done
    done
done
