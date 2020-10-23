#!/bin/bash
#cd /afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/CMSSW_8_1_0/src
#cmsenv
#cd -
function run()
{
		cp th2_to_txt.py tmp1
                sed -i '/Scale_QCD_extra/d' tmp1
                sed -i '/theory/d' tmp1
		i=`sed -n -e '/Scale_QCD/=' tmp1` 
		echo "$i" > num
		while read line; do
                           sed -i "${line}s/QCD_scale/scale_band1/" tmp1
                           sed -i "${line}s/Scale_QCD/QCDZA_Scale_band1/" tmp1

#			   sed -i "1,21h;22h;23,33H;44G" tmp1 
#			   sed -i "1,${line}h;${line}H;${line}G" tmp1 
			   sed -i "${line}h;${line}G" tmp1 
			   sed -i "${line}h;${line}G" tmp1 
			   l=$[$line+1]
                           sed -i "${l}s/scale_band1/scale_band2/" tmp1
                           sed -i "${l}s/QCDZA_Scale_band1/QCDZA_Scale_band2/" tmp1
			   m=$[$l+1]
                           sed -i "${m}s/scale_band1/scale_band3/" tmp1
                           sed -i "${m}s/QCDZA_Scale_band1/QCDZA_Scale_band3/" tmp1
                done < num

	cp tmp1 python.py
}

channel=("mubarrel" "muendcap" "elebarrel" "eleendcap")
# "Mjj" "Mva")
year=("16" "17" "18")
#year=("16")

run
for (( j = 0 ; j < ${#year[@]} ; j++ ))
do
    for (( i = 0 ; i < ${#channel[@]} ; i++ ))
    do
         cp python.py python_${year[$j]}_${channel[$i]}.py
         python python_${year[$j]}_${channel[$i]}.py ${year[$j]} ${channel[$i]}
    done
done
#ls *bin*.txt > filelist
#
#for file in `cat filelist`
#do
#if [[ -f "$file" ]]; then
#echo "$file exists"
#fi
#done
