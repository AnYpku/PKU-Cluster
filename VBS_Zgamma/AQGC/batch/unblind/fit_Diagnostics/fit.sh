#!/bin/bash
year=("16" "17" "18" "combine")
for (( j = 0 ; j < ${#year[@]} ; j++ ))
do
   cp /home/pku/anying/cms/PKU-Cluster/AQGC/batch/unblind/combine/all_${year[$j]}.txt ./
   combineCards.py all_${year[$j]}.txt -S > shape_all_${year[$j]}.txt
   combine -M FitDiagnostics  shape_all_${year[$j]}.txt --saveShapes  --saveWithUncertainties
   mv fitDiagnostics.root fitDiagnostics_${year[$j]}.root
done
