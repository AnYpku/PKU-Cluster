#!/bin/bash/


cp /home/pku/anying/cms/PKU-Cluster/SignalStrength/batch/data_cards/scale_test/unblind/txt/*16*.txt ./txt 
cp /home/pku/anying/cms/PKU-Cluster/SignalStrength/batch/data_cards/scale_test/unblind/txt/*17*.txt ./txt
cp /home/pku/anying/cms/PKU-Cluster/SignalStrength/batch/data_cards/scale_test/unblind/txt/*18*.txt ./txt
cp /home/pku/anying/cms/PKU-Cluster/SignalStrength/batch/CR/data_cards/scale_test/txt/*16*.txt ./txt  
cp /home/pku/anying/cms/PKU-Cluster/SignalStrength/batch/CR/data_cards/scale_test/txt/*17*.txt ./txt
cp /home/pku/anying/cms/PKU-Cluster/SignalStrength/batch/CR/data_cards/scale_test/txt/*18*.txt ./txt
cd ./txt
combineCards.py mubarrel_16_* muendcap_16_* elebarrel_16_* eleendcap_16_* >& full16_test.txt
combineCards.py mubarrel_17_* muendcap_17_* elebarrel_17_* eleendcap_17_* >& full17_test.txt
combineCards.py mubarrel_18_* muendcap_18_* elebarrel_18_* eleendcap_18_* >& full18_test.txt
combineCards.py full16_test.txt full17_test.txt full18_test.txt >&full_RunII.txt
files="\
full16_test.root
full18_test.root
full17_test.root
full_RunII.root
"
cd -
for rootfile in $files
do
    name=`echo $rootfile | awk -F. '{print $1}'` 
    echo "$name"
    mv ./txt/${name}.txt ./
    combineCards.py ${name}.txt -S > shape_${name}.txt
    combine -M FitDiagnostics shape_${name}.txt > result_all_${name}.txt
    combine -M FitDiagnostics --freezeParameters all shape_${name}.txt > result_freezeAll_${name}.txt
    group=("Stat" "theory" "JESR" "luminosity" "pu" "fake" "muon" "egamma" "Others" "pref" "pileupId" )
    for (( i = 0 ; i < ${#group[@]} ; i++  ))    
    do
         if [[ ${name} =~ "18" ]] && [[ ${group[${i}]} =~ "pref" ]]; then
             continue; 
         fi
   	   combine -M FitDiagnostics --freezeNuisanceGroups ${group[${i}]} shape_${name}.txt > result_${group[${i}]}_${name}.txt
	   echo "combine -M FitDiagnostics --freezeNuisanceGroups ${group[${i}]} shape_${name}.txt > result_${group[${i}]}_${name}.txt"

	done
done
