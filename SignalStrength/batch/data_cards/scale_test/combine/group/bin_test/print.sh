#!/bin/bash
group=("Stat" "theory" "JESR" "luminosity" "pu" "fake" "muon" "egamma" "Others" "pref" "pileupId" "freezeAll")
year=("16" "17" "18" )
channel=("mubarrel" "elebarrel" "muendcap" "eleendcap" )
for (( i = 1 ; i < 8 ; i++ ))
do
  for (( j =0 ; j < ${#year[@]} ; j++ ))
  do
    for (( k = 0 ; k< ${#channel[@]}; k++ ))
    do
      if [[ -f r_${channel[$k]}_${year[$j]}_bin${i}.txt ]];then
         rm r_${channel[$k]}_${year[$j]}_bin${i}.txt
      fi
      for (( ik = 0 ; ik < ${#group[@]} ; ik++ ))
      do
         if [[ ${year[$j]} =~ "16"  ]] && [[ ${group[${ik}]} =~ "pileupId" ]]; then
             continue;
         fi
         if [[ ${year[$j]} =~ "18"  ]] && [[ ${group[${ik}]} =~ "pileupId" ]]; then
             continue;
         fi
         if [[ ${year[$j]} =~ "18"  ]] && [[ ${group[${ik}]} =~ "pref" ]]; then
             continue;
         fi
         if [[ ${channel[$k]} =~ "ele"  ]] && [[ ${group[${ik}]} =~ "muon" ]]; then
             continue;
         fi
	 python extract.py ${group[$ik]} ${i} ${channel[$k]}  ${year[$j]} 
       done
         python cross.py ${i} ${channel[$k]}  ${year[$j]} > tmp
         line=`sed '2p' tmp`
         num=`sed -n -e '$=' r_${channel[$k]}_${year[$j]}_bin${i}.txt`
         sed -i "$num i $line" r_${channel[$k]}_${year[$j]}_bin${i}.txt
         sed -i '1 i group positive negative ' r_${channel[$k]}_${year[$j]}_bin${i}.txt
         result=`sed -n '1p' all/txt/result_${channel[$k]}_${year[$j]}_bin${i}.txt`
         n=`sed -n -e '$=' r_${channel[$k]}_${year[$j]}_bin${i}.txt`
         sed -i "$n a $result" r_${channel[$k]}_${year[$j]}_bin${i}.txt
         sed -i 's/luminosity/lumi/g' r_${channel[$k]}_${year[$j]}_bin${i}.txt
   done
 done
done
