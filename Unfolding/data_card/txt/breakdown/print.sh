#!/bin/bash
vars="\
ptlep1
photonet
jet1pt
"
#Mjj
years="\
full
"
#16
#17
#18
for year in $years
do
  for var in $vars
  do
    python extract.py $var $year
  done

done
