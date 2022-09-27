#!/bin/bash
channel=("MuonBarrel" "MuonEndcap" "EleBarrel" "EleEndcap")
#year=("16" "17" "18")
year=("18")

for (( j = 0 ; j < ${#channel[@]} ; j++ ))
do
   for (( i = 0 ; i < ${#year[@]} ; i++ ))
   do
     echo "${year[$i]}, ${channel[$j]}" 
#     cd /home/pku/anying/cms/PKU-Cluster/RunII20${year[$i]}/aa2/${channel[$j]}
#     mv -f yields.txt yields_T.txt
#     rm EDBRHistoMaker_a.h
#     cp /home/pku/anying/cms/PKU-Cluster/RunII2017/aa2/${channel[$j]}/EDBRHistoMaker_a.h ./
#     sed -i 's/41.52/59.7/g' EDBRHistoMaker_a.h 
#     sed -i 's/\*prefWeight//g' EDBRHistoMaker_a.h  
#     sed -i 's/jet1puIdTight==1/jet1puIdLoose==1/g' EDBRHistoMaker_a.h
#     sed -i 's/jet2puIdTight==1/jet2puIdLoose==1/g' EDBRHistoMaker_a.h
#     sed -i 's/\*puIdweight_T/\*puIdweight_L/g' EDBRHistoMaker_a.h
#     g++ -o execute_name_a `root-config --cflags --glibs` loopPlot_a.C
#     ./execute_name_a
#     echo | cat yields.txt 
#     echo '******************'

     cd /home/pku/anying/cms/PKU-Cluster/RunII20${year[$i]}/aa2/SR/${channel[$j]}
#     mv -f yields.txt yields_T.txt
     rm EDBRHistoMaker_a.h
     cp /home/pku/anying/cms/PKU-Cluster/RunII2017/aa2/SR/${channel[$j]}/EDBRHistoMaker_a.h ./
     sed -i 's/41.52/59.7/g' EDBRHistoMaker_a.h 
     sed -i 's/\*prefWeight//g' EDBRHistoMaker_a.h
     sed -i 's/jet1puIdTight==1/jet1puIdLoose==1/g' EDBRHistoMaker_a.h
     sed -i 's/jet2puIdTight==1/jet2puIdLoose==1/g' EDBRHistoMaker_a.h
     sed -i 's/\*puIdweight_T/\*puIdweight_L/g' EDBRHistoMaker_a.h
     g++ -o execute_name_a `root-config --cflags --glibs` loopPlot_a.C
     ./execute_name_a
#     echo | cat yields.txt 
#     echo '******************'
   done
done

