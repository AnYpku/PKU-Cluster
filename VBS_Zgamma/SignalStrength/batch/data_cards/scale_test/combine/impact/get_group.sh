#!/bin/bash
files="\
full16_test.root
full17_test.root
full18_test.root
full_RunII.root
"
for rootfile in $files
do
  name=`echo $rootfile | awk -F. '{print $1}'`
  echo "$name "
  group=("Stat" "theory" "JESR" "luminosity" "pu" "fake" "muon" "egamma" "Others" "pref" "pileupId" )
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
	 if [[ -f ${group[${i}]}_$name.txt ]]; then
	 rm ${group[${i}]}_*.txt
	 fi
	 line=`sed -n -e "/${group[${i}]} group/p" $name.txt`
         echo "$line" >> ${group[${i}]}_$name.txt
	 sed -i 's/ /\n/g' ${group[${i}]}_$name.txt
	 sed -i '1,3d' ${group[${i}]}_$name.txt
         sed -i 's/pileupId/puId/g' ${group[${i}]}_$name.txt
         if [[ ${name} =~ "RunII" ]]; then
	    mv ${group[${i}]}_full_RunII.txt ${group[${i}]}_full_RunII_test.txt
         fi
	 done

done
