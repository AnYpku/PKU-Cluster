#!/bin/bash
cp -f /data/pku/home/anying/cms/PKU-Cluster/Significance/data_cards/scale_test/txt/*16* .
cp -f /data/pku/home/anying/cms/PKU-Cluster/Significance/data_cards/scale_test/txt/*17* .
cp -f /data/pku/home/anying/cms/PKU-Cluster/Significance/data_cards/scale_test/txt/*18* .
cp -f /data/pku/home/anying/cms/PKU-Cluster/Significance/CR/data_cards/scale_test/txt/*16* .
cp -f /data/pku/home/anying/cms/PKU-Cluster/Significance/CR/data_cards/scale_test/txt/*17* .
cp -f /data/pku/home/anying/cms/PKU-Cluster/Significance/CR/data_cards/scale_test/txt/*18* .
channel=("mubarrel" "muendcap" "elebarrel" "eleendcap")
year=("16" "18" "17")
#year=("17")
for (( j = 0 ; j < ${#year[@]} ; j++ ))
do
    for (( i = 0 ; i < ${#channel[@]} ; i++ ))
    do
#    rm ${channel[$i]}_${year[$j]}.txt
    combineCards.py ${channel[$i]}_${year[$j]}_bin*.txt  >& ${channel[$i]}_${year[$j]}.txt
    combine -M Significance --expectSignal=1 -t -1 ${channel[$i]}_${year[$j]}.txt > result_${channel[$i]}_${year[$j]}.txt
    done
done
