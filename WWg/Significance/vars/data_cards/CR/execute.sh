#!/bin/bash
vars=("ml1g" "ml2g" "mllg")
year=("16" "_pre16" "17" "18")
njets=("0jets" "1jets" "2jets")
for (( j = 0 ; j < ${#year[@]} ; j++ ))
do
    for (( i = 2 ; i < ${#vars[@]} ; i++ ))
    do
        for  (( k = 0 ; k < ${#njets[@]} ; k++ ))
        do
          python th2_to_txt.py ${year[$j]} ${njets[$k]} ${vars[$i]}
        done
    done
done
