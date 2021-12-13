#!/bin/bash
vars=("mT")
year=("17" "18")
njets=("0jets" "1jets" "totaljets")
for (( j = 1 ; j < ${#year[@]} ; j++ ))
do
    for (( i = 0 ; i < ${#vars[@]} ; i++ ))
    do
        for  (( k = 0 ; k < ${#njets[@]} ; k++ ))
        do
          python th2_to_txt.py ${year[$j]} ${njets[$k]} ${vars[$i]}
        done
    done
done
