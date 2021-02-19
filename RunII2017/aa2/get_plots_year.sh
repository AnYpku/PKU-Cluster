#!/bin/bash
channel=("MuonBarrel" "MuonEndcap" "EleBarrel" "EleEndcap")
#year=("16" "17" "18")
year=("17")

for (( j = 0 ; j < ${#channel[@]} ; j++ ))
do
   for (( i = 0 ; i < ${#year[@]} ; i++ ))
   do
     echo "${year[$i]}, ${channel[$j]}" 
     cd /home/pku/anying/cms/PKU-Cluster/RunII20${year[$i]}/aa2/${channel[$j]}
     sed -i 's/400/500/g' EDBRHistoMaker_a.h 
     g++ -o execute_name_a `root-config --cflags --glibs` loopPlot_a.C
     ./execute_name_a
#     echo | cat yields.txt 
#     echo '******************'

     cd /home/pku/anying/cms/PKU-Cluster/RunII20${year[$i]}/aa2/SR/${channel[$j]}
     rm loopPlot_a.C
     cp ../../${channel[$j]}/loopPlot_a.C ./
     g++ -o execute_name_a `root-config --cflags --glibs` loopPlot_a.C
     ./execute_name_a
#     echo | cat yields.txt 
#     echo '******************'
   done
done

