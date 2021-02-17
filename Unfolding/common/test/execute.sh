#!/bin/bash
if [[ -f Condition_Number_info ]];then
   rm Condition_Number_info
fi
#genvar=("genlep1pt" "genphotonet" "genjet1pt" "genMjj")
genvar=("genlep1pt" "genphotonet" "genjet1pt")
year=("16" "17" "18")
#year=("17")
for (( j = 0 ; j < ${#year[@]} ; j++ ))
do
    for (( i = 0 ; i < ${#genvar[@]} ; i++ ))
    do
#        python cond.py ${genvar[$i]} ${year[$j]} >> Condition_Number_info
        python cond.py ${genvar[$i]} ${year[$j]} 
    done
done
