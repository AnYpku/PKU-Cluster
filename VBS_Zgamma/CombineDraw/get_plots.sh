#!/bin/bash
channel=("MuonBarrel" "MuonEndcap" "EleBarrel" "EleEndcap")

for (( j = 0 ; j < ${#channel[@]} ; j++ ))
do
#     cd /home/pku/anying/cms/PKU-Cluster/CombineDraw/${channel[$j]}
#     sed -i 's/400/500/g' EDBRHistoMaker_a.h 
#     sed -i 's/puIdweight_M/puIdweight_T/g' EDBRHistoMaker_a.h
#     sed -i 's/puIdweight_M/puIdweight_T/g' EDBRHistoMaker_a.h 
#     sed -i 's/puIdMedium/puIdTight/g' EDBRHistoMaker_a.h
#     echo "${year[$i]}, ${channel[$j]}" 
#     echo | cat yields.txt 
#     echo '******************'
#      g++ -o execute_name_a `root-config --cflags --glibs` loopPlot_a.C
#      ./execute_name_a
     
     cd /home/pku/anying/cms/PKU-Cluster/CombineDraw/SR/${channel[$j]}
     rm EDBRHistoPlotter.h
     rm CMS_lumi.C
     cp /home/pku/anying/cms/PKU-Cluster/CombineDraw/SR/CMS_lumi.C ./
     cp /home/pku/anying/cms/PKU-Cluster/CombineDraw/SR/EDBRHistoPlotter.h ./
     sed -i 's/137.1/137/g' loopPlot_a.C
     g++ -o execute_name_a `root-config --cflags --glibs` loopPlot_a.C
     ./execute_name_a
done

