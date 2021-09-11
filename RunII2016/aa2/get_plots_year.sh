#!/bin/bash
channel=("MuonBarrel" "MuonEndcap" "EleBarrel" "EleEndcap")
#year=("16" "17" "18")
year=("16")

for (( j = 0 ; j < ${#channel[@]} ; j++ ))
do
   for (( i = 0 ; i < ${#year[@]} ; i++ ))
   do
     echo "${year[$i]}, ${channel[$j]}" 
#     cd /home/pku/anying/cms/PKU-Cluster/RunII20${year[$i]}/aa2/${channel[$j]}
#     rm EDBRHistoMaker_a.h
#     cp /home/pku/anying/cms/PKU-Cluster/RunII2017/aa2/${channel[$j]}/EDBRHistoMaker_a.h ./
#     sed -i 's/400/500/g' EDBRHistoMaker_a.h 
#     sed -i 's/jet1puIdTight==1/jet1puIdMedium==1/g' EDBRHistoMaker_a.h 
#     sed -i 's/jet2puIdTight==1/jet2puIdMedium==1/g' EDBRHistoMaker_a.h 
#     sed -i 's/\*puIdweight_T/\*puIdweight_M/g' EDBRHistoMaker_a.h
#     g++ -o execute_name_a `root-config --cflags --glibs` loopPlot_a.C
#     ./execute_name_a
#     echo | cat yields.txt 
#     echo '******************'

     cd /home/pku/anying/cms/PKU-Cluster/RunII20${year[$i]}/aa2/SR/${channel[$j]}
     sed -i 's/actualWeight\=0/actualWeight\=1/g' EDBRHistoMaker_a.h
     g++ -o execute_name_a `root-config --cflags --glibs` loopPlot_a.C
     ./execute_name_a
#     echo | cat yields.txt 
#     echo '******************'
   done
done

