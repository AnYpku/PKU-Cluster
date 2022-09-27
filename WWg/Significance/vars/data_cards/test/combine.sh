#!/bin/bash
if [[ -f *.txt ]]; then
rm *.txt
fi
cp -f /home/pku/anying/cms/PKU-Cluster/WWg/Significance/vars/data_cards/SR/txt/*.txt .
cp -f /home/pku/anying/cms/PKU-Cluster/WWg/Significance/vars/data_cards/CR/txt/*.txt .
years="\
16
17
18
"
jetbins="\
0jets
1jets
2jets
"
vars="\
mll
photonet
mllg
"
for var in $vars
do
  for y in $years
  do
    for njets in $jetbins
    do
      echo "${y} ${njets} ${var}"
      if [[ ${njets} == "0jets" ]];then
         combineCards.py emu_${y}_${njets}_${var}_bin*.txt emu_${y}_${njets}_mT_puppi_CR_bin* > full${y}_${var}_${njets}_test.txt 
      else 
         combineCards.py emu_${y}_${njets}_${var}_bin*.txt emu_${y}_${njets}_${var}_CR_bin* > full${y}_${var}_${njets}_test.txt
      fi
      text2workspace.py  full${y}_${var}_${njets}_test.txt -m 125
      combine -M Significance --expectSignal=1 -t -1 full${y}_${var}_${njets}_test.txt > result${y}_${var}_${njets}_test.txt 
      combine -M Significance --expectSignal=1 -t -1 full${y}_${var}_${njets}_test.txt --freezeParameters all > result${y}_${var}_${njets}_freezeAll.txt
    done
  done
done


