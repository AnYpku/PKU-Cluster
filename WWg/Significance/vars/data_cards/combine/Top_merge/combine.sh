#!/bin/bash
rm *.txt
cp -f /home/pku/anying/cms/PKU-Cluster/WWg/Significance/vars/data_cards/SR/Top_merge/txt/*.txt .
cp -f /home/pku/anying/cms/PKU-Cluster/WWg/Significance/vars/data_cards/CR/Top_merge/txt/*.txt .
rm emu_17_0jets_mllg_CR_bin9.txt
years="\
17
18
"
jetbins="\
0jets
1jets
"
vars="\
mllg
ml1g
ml2g
"
for var in $vars
do
  for y in $years
  do
    for njets in $jetbins
    do
      echo "${y} ${njets} ${var}"
      combineCards.py emu_${y}_${njets}_${var}_*bin*.txt > full${y}_${var}_${njets}_test.txt 
      text2workspace.py  full${y}_${var}_${njets}_test.txt -m 125
      combine -M Significance --expectSignal=1 -t -1 full${y}_${var}_${njets}_test.txt > result${y}_${var}_${njets}_test.txt 
      combine -M Significance --expectSignal=1 -t -1 full${y}_${var}_${njets}_test.txt --freezeParameters all > result${y}_${var}_${njets}_freezeAll.txt
    done
  done
  combineCards.py emu_17*_0jets_${var}_*bin*.txt emu_17*_1jets_${var}_*bin*.txt emu_18*_0jets_${var}_*bin*.txt emu_18*_1jets_${var}_*bin*.txt >& full_${var}.txt
  text2workspace.py full_${var}.txt -m 125
  combine -M Significance --expectSignal=1 -t -1 full_${var}.txt > result_full_${var}.txt
  combine -M Significance --expectSignal=1 -t -1 full_${var}.txt --freezeParameters all > result_full_${var}_freezeAll.txt
done


