#!/bin/bash
#cd /afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/CMSSW_8_1_0/src
#cmsenv
#cd -
dir1="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2016/FourChannels/2016elebarrel/mjj5007501000_detajj25456_zepp18"
dir2="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2016/FourChannels/2016elebarrel/mjj5007501000_detajj25456_zepp18/aa.root"
barrel_qcd="jes_QCD=[1.09, 1.12, 1.00, 1.31, 1.32, 1.21, 1.55]"
barrel_ewk="jes_EWK=[1.03, 1.01, 1.05, 1.06, 1.01, 1.04, 1.04]"
	cp $dir1/th2_to_txt.py .
		sed -e 's|\.\/aa\.root|'$dir2'|g' th2_to_txt.py >tmp1
		i=`sed -n -e '/jes_QCD/=' tmp1` 
		echo "$i" > num
		while read line; do
			echo "$line"
		        if [[ $line -lt 100 ]]; then
				sed -e "$line d" tmp1    >tmp2
				sed -e "$line a$barrel_qcd" tmp2  >tmp3
			 fi
                done < num

        j=`sed -n -e '/jes_EWK/=' tmp3` 
	echo "$j" > num1
	while read line; do
		echo "$line"
		if [[ $line -lt 100 ]]; then
			sed -e "$line d" tmp3 >tmp4
		        sed -e "$line a$barrel_ewk" tmp4 >tmp5
		fi
	done < num1
	cp tmp5 python.py

	python python.py
	ls *bin*.txt > filelist
	for file in `cat filelist`
	do
		if [[ -f "$file" ]]; then
			echo "$file exists"
	        fi
	done
#combineCards.py *.txt >& full.txt
#combine -M Significance full.txt --expectSignal=1 -t -1 > result.txt

