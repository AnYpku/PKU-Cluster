#!/bin/bash
#full16_test.root
#full17_test.root
#full18_test.root
files="\
full_RunII.root
"
for rootfile in $files
do
  name=`echo $rootfile | awk -F. '{print $1}'`
  echo "$name "
  if [[ -f unc_impact_${name}.txt  ]];then
     rm unc_impact_${name}.txt
  fi
  for line in `cat freeze_${name}.txt`
  do
     num=`sed -n "/${line}/=" impacts_SS_${name}.json`
     echo "$line , $num"
     n=$[${num}-1]
     impact_r=`sed -n -e "${n}p" impacts_SS_${name}.json`  
     echo "$line $impact_r" >> unc_impact_${name}.txt
  done
done
