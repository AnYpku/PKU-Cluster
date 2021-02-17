#!/bin/bash
channel=("MuonBarrel" "MuonEndcap" "EleBarrel" "EleEndcap")

for (( j = 0 ; j < ${#channel[@]} ; j++ ))
do
     cd /home/pku/anying/cms/PKU-Cluster/CombineDraw/${channel[$j]}
#     echo "${year[$i]}, ${channel[$j]}" 
#     echo | cat yields.txt 
#     echo '******************'
#     rm EDBRHistoPlotter.h
#     cp /data/pku/home/anying/cms/PKU-Cluster/CombineDraw/EDBRHistoPlotter.h ./ 
#     sed -i 's/400/500/g' EDBRHistoMaker_a.h 
      g++ -o execute_name_a `root-config --cflags --glibs` loopPlot_a.C
      ./execute_name_a

     cd /home/pku/anying/cms/PKU-Cluster/CombineDraw/SR/${channel[$j]}
     g++ -o execute_name_a `root-config --cflags --glibs` loopPlot_a.C
     ./execute_name_a
done

