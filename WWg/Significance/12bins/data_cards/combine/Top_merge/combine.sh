#!/bin/bash
rm *.txt
cp -f /home/pku/anying/cms/PKU-Cluster/WWg/Significance/test/data_cards/SR/Top_merge/txt/*.txt .
cp -f /home/pku/anying/cms/PKU-Cluster/WWg/Significance/test/data_cards/CR/Top_merge/txt/*.txt .
years="\
18
17
"
#18
#16
for y in $years
do
  combineCards.py *$y*.txt > full${y}_test.txt 
  text2workspace.py  full${y}_test.txt -m 125
  combine -M Significance --expectSignal=1 -t -1 full${y}_test.txt > result${y}_test.txt 
  combine -M Significance --expectSignal=1 -t -1 full${y}_test.txt --freezeParameters all > result${y}_freezeAll.txt
done

combineCards.py emu_*.txt >& full.txt
text2workspace.py full.txt -m 125
combine -M Significance --expectSignal=1 -t -1 full.txt > result_full.txt
combine -M Significance --expectSignal=1 -t -1 full.txt --freezeParameters all > result_full_freezeAll.txt

