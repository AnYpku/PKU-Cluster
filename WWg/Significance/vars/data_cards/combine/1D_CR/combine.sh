#!/bin/bash
if [[ -f *.txt ]] ;then
  rm *.txt
fi
if [[ -f *.root ]] ;then
  rm *.root
fi
cp -f /home/pku/anying/cms/PKU-Cluster/WWg/Significance/data_cards/SR/txt/*.txt .
cp -f /home/pku/anying/cms/PKU-Cluster/WWg/Significance/data_cards/CR/1D/txt/*.txt .
years="\
18
"
#16
#17
for y in $years
do
  combineCards.py *18*.txt > full${y}_test.txt 
  text2workspace.py  full${y}_test.txt -m 125
  combine -M Significance --expectSignal=1 -t -1 full${y}_test.txt > result${y}_test.txt 
  combine -M Significance --expectSignal=1 -t -1 full${y}_test.txt --freezeParameters all > result${y}_freezeAll.txt
done

