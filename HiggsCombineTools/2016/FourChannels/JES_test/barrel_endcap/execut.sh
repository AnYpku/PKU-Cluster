#!/bin/bash
#cd /afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/CMSSW_8_1_0/src
#cmsenv
#cd -
function run()
{
	cp $dir1/th2_to_txt.py .
		sed -e 's|\.\/aa\.root|'$dir2'|g' th2_to_txt.py >tmp1
		i=`sed -n -e '/jes_QCD/=' tmp1` 
		echo "$i" > num
		while read line; do
			echo "$line"
		        if [[ $line -lt 100 ]]; then
				sed -e "$line d" tmp1    >tmp2
				sed -e "$line i$qcd" tmp2  >tmp3
			 fi
                done < num

        j=`sed -n -e '/jes_EWK/=' tmp3` 
	echo "$j" > num1
	while read line; do
		echo "$line"
		if [[ $line -lt 100 ]]; then
			sed -e "$line d" tmp3 >tmp4
		        sed -e "$line i$ewk" tmp4 >tmp5
		fi
	done < num1
	cp tmp5 python.py

#	python python.py
#	ls *bin*.txt > filelist
#	for file in `cat filelist`
#	do
#		if [[ -f "$file" ]]; then
#			echo "$file exists"
#	        fi
#	done
}


dir1="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2016/FourChannels/2016eleendcap/mjj5007501000_detajj25456_zepp18"
dir2="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2016/FourChannels/2016eleendcap/mjj5007501000_detajj25456_zepp18/aa.root"
qcd="jes_QCD=[1.03, 1.03, 1.40, 1.14, 1.30, 1.26, 1.25]"
ewk="jes_EWK=[1.02, 1.02, 1.05, 1.04, 1.03, 1.06, 1.03]"
run 
mv python.py python_ee.py

dir1="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2016/FourChannels/2016mubarrel/SR"
dir2="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2016/FourChannels/2016mubarrel/SR/aa.root"
qcd="jes_QCD=[1.09, 1.12, 1.00, 1.31, 1.32, 1.21, 1.55]"
ewk="jes_EWK=[1.03, 1.01, 1.05, 1.06, 1.01, 1.04, 1.04]"
run 
mv python.py python_mb.py
dir1="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2016/FourChannels/2016elebarrel/mjj5007501000_detajj25456_zepp18"
dir2="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2016/FourChannels/2016elebarrel/mjj5007501000_detajj25456_zepp18/aa.root"
qcd="jes_QCD=[1.09, 1.12, 1.00, 1.31, 1.32, 1.21, 1.55]"
ewk="jes_EWK=[1.03, 1.01, 1.05, 1.06, 1.01, 1.04, 1.04]"
run 
mv python.py python_eb.py

dir1="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2016/FourChannels/2016muendcap/mjj5007501000_detajj25456_zepp18"
dir2="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2016/FourChannels/2016muendcap/mjj5007501000_detajj25456_zepp18/aa.root"
qcd="jes_QCD=[1.03, 1.03, 1.40, 1.14, 1.30, 1.26, 1.25]"
ewk="jes_EWK=[1.02, 1.02, 1.05, 1.04, 1.03, 1.06, 1.03]"
run 
mv python.py python_me.py
#python python.py
#run $dir_mb1 $dir_mb2 $barrel_qcd $barrel_ewk
#python python.py
#mv python.py python_mb.py
#
#run $dir_ee1 $dir_ee2 $endcap_qcd $endcap_ewk
#python pytnon.py
#mv python.py python_ee.py
#run $dir_me1 $dir_me2 $endcap_qcd $endcap_ewk
#python python.py
#mv python.py python_me.py
ls py*.py > temp6
for py in `cat temp6`
do
python $py
done
ls *bin*.txt > filelist
for file in `cat filelist`
do
if [[ -f "$file" ]]; then
echo "$file exists"
fi
done
#combineCards.py *.txt >& full.txt
#combine -M Significance full.txt --expectSignal=1 -t -1 > result.txt

