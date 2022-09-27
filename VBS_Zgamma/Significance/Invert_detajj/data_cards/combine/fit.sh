#!/bin/bash
if [[ -f Mjj_*.txt ]];then
   rm Mjj_*.txt
fi
cp ../txt/*.txt .
combineCards.py *.txt >& all.txt
combineCards.py all.txt -S > shape_all.txt
combine -M FitDiagnostics  shape_all.txt --saveShapes -t -1 --expectSignal=1 --saveWithUncertainties
