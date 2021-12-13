#!/bin/bash
rm *.txt
cp -f /home/pku/anying/cms/PKU-Cluster/WWg/Significance/vars/data_cards/SR/txt/*.txt .
cp -f /home/pku/anying/cms/PKU-Cluster/WWg/Significance/vars/data_cards/2jetsSR/txt/*.txt .
years="\
16
_pre16
17
18
"
jetbins="\
0jets
"

#1jets
#2jets
vars="\
mllg
"
#ml1g
#ml2g

for var in $vars
do
  for y in $years
  do
    for njets in $jetbins
    do
      echo "${y} ${njets} ${var}"
      combineCards.py emu_${y}_${njets}_${var}_*bin*.txt emu_${y}_2jets_${var}_CR_bin* > full${y}_${var}_${njets}_test.txt 
      text2workspace.py  full${y}_${var}_${njets}_test.txt -m 125
      combine -M Significance --expectSignal=1 -t -1 full${y}_${var}_${njets}_test.txt > result${y}_${var}_${njets}_test.txt 
      combine -M Significance --expectSignal=1 -t -1 full${y}_${var}_${njets}_test.txt --freezeParameters all > result${y}_${var}_${njets}_freezeAll.txt
    done
  done
done


