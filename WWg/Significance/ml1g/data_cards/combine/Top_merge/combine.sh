#!/bin/bash
rm *.txt
cp -f /home/pku/anying/cms/PKU-Cluster/WWg/Significance/ml1g/data_cards/SR/Top_merge/txt/*.txt .
cp -f /home/pku/anying/cms/PKU-Cluster/WWg/Significance/ml1g/data_cards/CR/Top_merge/txt/*.txt .
years="\
18
17
"
jetbins="\
0jets
1jets
"
#18
#16
for y in $years
do
  for njets in $jetbins
  do
    combineCards.py *${y}_${njets}*bin*.txt > full${y}_${njets}_test.txt 
    text2workspace.py  full${y}_${njets}_test.txt -m 125
    combine -M Significance --expectSignal=1 -t -1 full${y}_${njets}_test.txt > result${y}_${njets}_test.txt 
    combine -M Significance --expectSignal=1 -t -1 full${y}_${njets}_test.txt --freezeParameters all > result${y}_${njets}_freezeAll.txt
  done
done

combineCards.py emu_*.txt >& full.txt
text2workspace.py full.txt -m 125
combine -M Significance --expectSignal=1 -t -1 full.txt > result_full.txt
combine -M Significance --expectSignal=1 -t -1 full.txt --freezeParameters all > result_full_freezeAll.txt

