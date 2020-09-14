#!/bin/bash
cp ../full.txt htt_tt.txt
text2workspace.py htt_tt.txt -m 125
combineTool.py -M Impacts -d htt_tt.root -m 125 --doInitialFit --robustFit 1
combineTool.py -M Impacts -d htt_tt.root -m 125 --robustFit 1 --doFits
combineTool.py -M Impacts -d htt_tt.root -m 125 -o impacts.json
plotImpacts.py -i impacts.json -o impacts
