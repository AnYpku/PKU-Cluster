#!/bin/bash
combineCards.py ele18_barrel_bin* >& 18eb.txt
combineCards.py ele18_endcap_bin* >& 18ee.txt
combineCards.py muon18_barrel_bin* >& 18mb.txt
combineCards.py muon18_endcap_bin* >& 18me.txt

combineCards.py  ele18_barrel* ele18_endcap* muon18_barrel* muon18_endcap* >& all.txt
combineCards.py  ele18_barrel_bin* ele18_endcap_bin* muon18_barrel_bin* muon18_endcap_bin* >& total.txt

#combine -M Significance 18mb.txt --expectSignal=1 -t -1
#combine -M Significance 18me.txt --expectSignal=1 -t -1
#combine -M Significance 18eb.txt --expectSignal=1 -t -1
#combine -M Significance 18ee.txt --expectSignal=1 -t -1
#
#combine -M Significance all.txt  --expectSignal=1 -t -1

#text2workspace.py all.txt -m 125
#
#combineTool.py -M Impacts -d all.root -m 125 --doInitialFit --robustFit 1
#
#combineTool.py -M Impacts -d all.root -m 125 --robustFit 1 --doFits
#
#combineTool.py -M Impacts -d all.root -m 125 -o impacts.json
#
#plotImpacts.py -i impacts.json -o impacts
#
