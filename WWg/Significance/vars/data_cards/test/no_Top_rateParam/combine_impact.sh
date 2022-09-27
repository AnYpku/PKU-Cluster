#!/bin/bash
years="\
18
"
#16
#17
for y in $years
do
  text2workspace.py  full${y}_photonet_0jets_test.txt -m 125
  combineTool.py -M Impacts -d full${y}_photonet_0jets_test.root -t -1 --expectSignal=1 -m 125 --doInitialFit --robustFit 1
  combineTool.py -M Impacts -d full${y}_photonet_0jets_test.root -t -1 --expectSignal=1 -m 125 --robustFit 1 --doFits --parallel 8
  combineTool.py -M Impacts -d full${y}_photonet_0jets_test.root -t -1 --expectSignal=1 -m 125 -o impacts_${y}.json
  plotImpacts.py -i impacts_${y}.json -o impacts_${y}

done

