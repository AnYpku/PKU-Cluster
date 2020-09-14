#!/bin/bash
#combineCards.py ele17_barrel_bin* >& 17eb.txt
#combineCards.py ele17_endcap_bin* >& 17ee.txt
#combineCards.py muon17_barrel_bin* >& 17mb.txt
#combineCards.py muon17_endcap_bin* >& 17me.txt
#
#combineCards.py  ele17_barrel* ele17_endcap* muon17_barrel* muon17_endcap* >& all.txt
#combineCards.py  ele17_barrel_bin* ele17_endcap_bin* muon17_barrel_bin* muon17_endcap_bin* >& total.txt

#combine -M Significance 17mb.txt --expectSignal=1 -t -1
#combine -M Significance 17me.txt --expectSignal=1 -t -1
#combine -M Significance 17eb.txt --expectSignal=1 -t -1
#combine -M Significance 17ee.txt --expectSignal=1 -t -1

#combine -M Significance all.txt  --expectSignal=1 -t -1

text2workspace.py all.txt -m 125

combineTool.py -M Impacts -d all.root -m 125 --doInitialFit --robustFit 1

combineTool.py -M Impacts -d all.root -m 125 --robustFit 1 --doFits

combineTool.py -M Impacts -d all.root -m 125 -o impacts.json

plotImpacts.py -i impacts.json -o impacts

