#!/bin/bash
year=("16" "17" "18" "_RunII")
#year=("17" "_RunII")
for (( i = 0 ; i < ${#year[@]} ; i++ ))
do
      if [[ -f result_all_full_RunII.txt ]];then
         mv result_all_full_RunII.txt result_all_full_RunII_test.txt
      fi
      sed -n -e '/68\%/p' result_all_full${year[$i]}_test.txt > tmp_all_full${year[$i]}_test.txt
      python extract.py ${year[$i]}
done
