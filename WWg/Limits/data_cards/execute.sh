#!/bin/bash
vars=("drll")
year=("17" "18")
njets=("0jets" "1jets")
quarks=("HGC" "HGU" "HGS" "HGD")
for (( j = 1 ; j < ${#year[@]} ; j++ ))
do
    for (( i = 0 ; i < ${#vars[@]} ; i++ ))
    do
        for  (( k = 0 ; k < ${#njets[@]} ; k++ ))
        do
           for (( n = 0 ; n < ${#quarks[@]} ; n++ ))
           do
                python th2_to_txt.py ${year[$j]} ${njets[$k]} ${vars[$i]} ${quarks[$n]}
          done
        done
    done
done
