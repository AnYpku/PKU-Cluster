#!/bin/bash
#cd /afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/CMSSW_8_1_0/src
#cmsenv
#cd -
function run()
{
		cp th2_to_txt.py tmp1
	        sed -i "16 i$band1" tmp1
	        sed -i "16 i$band2" tmp1
	        sed -i "16 i$band3" tmp1
                sed -i '/Scale_QCD_extra/d' tmp1
		i=`sed -n -e '/Scale_QCD/=' tmp1` 
		echo "$i" > num
		while read line; do
                           sed -i "${line}s/QCD_scale/scale_QCD_band1/" tmp1
                           sed -i "${line}s/Scale_QCD/QCDZA_scale1/" tmp1

#			   sed -i "1,21h;22h;23,33H;44G" tmp1 
#			   sed -i "1,${line}h;${line}H;${line}G" tmp1 
			   sed -i "${line}h;${line}G" tmp1 
			   sed -i "${line}h;${line}G" tmp1 
			   l=$[$line+1]
                           sed -i "${l}s/scale_QCD_band1/scale_QCD_band2/" tmp1
                           sed -i "${l}s/QCDZA_scale1/QCDZA_scale2/" tmp1
			   m=$[$l+1]
                           sed -i "${m}s/scale_QCD_band1/scale_QCD_band3/" tmp1
                           sed -i "${m}s/QCDZA_scale1/QCDZA_scale3/" tmp1
                done < num

	cp tmp1 python.py
}


band1="scale_QCD_band1=[1.028,1.056,1.091,1.032,1.065,1.033,1.004]"
band2="scale_QCD_band2=[1.132,1.141,1.163,1.113,1.097,1.130,1.121]"
band3="scale_QCD_band3=[1.162,1.199,1.258,1.081,1.165,1.164,1.117]"

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
