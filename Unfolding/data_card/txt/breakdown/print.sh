#!/bin/bash
vars="\
ptlep1
photonet
jet1pt
"
#Mjj
years="\
16
17
18
"
#full
for year in $years
do
  for var in $vars
  do
    python extract.py $var $year
  done

done
