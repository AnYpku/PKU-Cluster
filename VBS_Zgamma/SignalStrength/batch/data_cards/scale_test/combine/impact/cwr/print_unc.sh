#!/bin/bash/
year=("16" "17" "18" "_RunII")
group=("Stat" "theory" "JESR" "luminosity" "pu" "fake" "muon" "egamma" "Others" "pref" "pileupId" )
for (( j = 0 ; j < ${#year[@]} ; j++ ))
do
if [[ -f all_unc*.txt ]]; then
  rm all_unc*.txt
fi
    for (( i = 0 ; i < ${#group[@]} ; i++  ))
    do
         if [[ ${name} =~ "16" ]] && [[ ${group[${i}]} =~ "pileupId" ]]; then
             continue;
         fi
         if [[ ${name} =~ "18" ]] && [[ ${group[${i}]} =~ "pileupId" ]]; then
             continue;
         fi
         if [[ ${name} =~ "18" ]] && [[ ${group[${i}]} =~ "pref" ]]; then
             continue;
         fi
         python extract.py ${year[${j}]}  ${group[${i}]}
    done
done
