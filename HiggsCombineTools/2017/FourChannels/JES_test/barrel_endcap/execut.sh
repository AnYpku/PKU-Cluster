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


dir1="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2017/FourChannels/2017eleendcap/SR/mjj5007501000_detajj25456_zepp18"
dir2="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2017/FourChannels/2017eleendcap/SR/mjj5007501000_detajj25456_zepp18/aa.root"
qcd="jes_QCD=[1.20, 1.07, 1.13, 1.28, 2.43, 1.39, 2.49]"
ewk="jes_EWK=[1.04, 1.07, 1.05, 1.07, 1.09, 1.08, 1.11]"
run 
mv python.py python_ee.py

dir1="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2017/FourChannels/2017mubarrel/SR/mjj5007501000_detajj25456_zepp18"
dir2="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2017/FourChannels/2017mubarrel/SR/mjj5007501000_detajj25456_zepp18/aa.root"
qcd="jes_QCD=[1.26, 1.15, 1.40, 1.39, 1.81, 1.61, 1.54]"
ewk="jes_EWK=[1.02, 1.05, 1.06, 1.17, 1.09, 1.11, 1.12]"
run 
mv python.py python_mb.py
dir1="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2017/FourChannels/2017elebarrel/SR/mjj5007501000_detajj25456_zepp18"
dir2="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2017/FourChannels/2017elebarrel/SR/mjj5007501000_detajj25456_zepp18/aa.root"
qcd="jes_QCD=[1.26, 1.15, 1.40, 1.39, 1.81, 1.61, 1.54]"
ewk="jes_EWK=[1.02, 1.05, 1.06, 1.17, 1.09, 1.11, 1.12]"
run 
mv python.py python_eb.py

dir1="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2017/FourChannels/2017muendcap/SR/mjj5007501000_detajj25456_zepp18"
dir2="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2017/FourChannels/2017muendcap/SR/mjj5007501000_detajj25456_zepp18/aa.root"
qcd="jes_QCD=[1.20, 1.07, 1.13, 1.28, 2.43, 1.39, 2.49]"
ewk="jes_EWK=[1.04, 1.07, 1.05, 1.07, 1.09, 1.08, 1.11]"
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

