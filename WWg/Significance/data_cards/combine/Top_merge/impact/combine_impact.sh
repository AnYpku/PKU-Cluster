#!/bin/bash
years="\
17
18
"
#16
#17
if [[ -f *.root ]];then
  rm *.root
fi
for y in $years
do
 
  cp ../full${y}_test.root ./
  combineTool.py -M Impacts -d full${y}_test.root -t -1 --expectSignal=1 -m 125 --doInitialFit --robustFit 1
  combineTool.py -M Impacts -d full${y}_test.root -t -1 --expectSignal=1 -m 125 --robustFit 1 --doFits --parallel 8
  combineTool.py -M Impacts -d full${y}_test.root -t -1 --expectSignal=1 -m 125 -o impacts_${y}.json
  plotImpacts.py -i impacts_${y}.json -o impacts_${y}

done

