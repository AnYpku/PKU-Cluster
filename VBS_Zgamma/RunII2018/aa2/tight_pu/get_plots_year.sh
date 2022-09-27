#!/bin/bash
channel=("MuonBarrel" "MuonEndcap" "EleBarrel" "EleEndcap")
#year=("16" "17" "18")
year=("18")

for (( j = 0 ; j < ${#channel[@]} ; j++ ))
do
   for (( i = 0 ; i < ${#year[@]} ; i++ ))
   do
     echo "${year[$i]}, ${channel[$j]}" 
#     cd /home/pku/anying/cms/PKU-Cluster/RunII20${year[$i]}/aa2/tight_pu/${channel[$j]}
#     sed -i 's/jet1puIdLoose==1/jet1puIdTight==1/g' EDBRHistoMaker_a.h
#     sed -i 's/jet2puIdLoose==1/jet2puIdTight==1/g' EDBRHistoMaker_a.h
#     sed -i 's/\*puIdweight_L/\*puIdweight_T/g' EDBRHistoMaker_a.h
#     g++ -o execute_name_a `root-config --cflags --glibs` loopPlot_a.C
#     ./execute_name_a
#     echo | cat yields.txt 
#     echo '******************'

     cd /home/pku/anying/cms/PKU-Cluster/RunII20${year[$i]}/aa2/tight_pu/SR/${channel[$j]}
#     sed -i 's/jet1puIdLoose==1/jet1puIdTight==1/g' EDBRHistoMaker_a.h
#     sed -i 's/jet2puIdLoose==1/jet2puIdTight==1/g' EDBRHistoMaker_a.h
#     sed -i 's/\*puIdweight_L/\*puIdweight_T/g' EDBRHistoMaker_a.h
#     g++ -o execute_name_a `root-config --cflags --glibs` loopPlot_a.C
#     ./execute_name_a
     echo | cat yields.txt 
     echo '******************'
   done
done

