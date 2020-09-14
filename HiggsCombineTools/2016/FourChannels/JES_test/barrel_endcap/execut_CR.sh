#!/bin/bash
#cd /afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/CMSSW_8_1_0/src
#cmsenv
#cd -
function run()
{
	cp $dir1/th2_to_txt.py .
	sed -e 's|\.\/aa\.root|'$dir2'|g' th2_to_txt.py >tmp1
        sed -e 's/stat/stat_control/g' tmp1 >tmp2
	cp tmp2 python.py

#	python python.py
#	ls *bin*.txt > filelist
#	for file in `cat filelist`
#	do
#		if [[ -f "$file" ]]; then
#			echo "$file exists"
#	        fi
#	done
}


dir1="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2016/FourChannels/2016elebarrel/CR/"
dir2="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2016/FourChannels/2016elebarrel/CR/aa.root"
run 
mv python.py python_ebCR.py

dir1="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2016/FourChannels/2016eleendcap/CR/"
dir2="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2016/FourChannels/2016eleendcap/CR/aa.root"
run 
mv python.py python_eeCR.py
dir1="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2016/FourChannels/2016mubarrel/CR/"
dir2="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2016/FourChannels/2016mubarrel/CR/aa.root"
run 
mv python.py python_mbCR.py

dir1="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2016/FourChannels/2016muendcap/CR/"
dir2="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2016/FourChannels/2016muendcap/CR/aa.root"
run 
mv python.py python_meCR.py
rm tmp*
ls py*CR.py > temp6
for py in `cat temp6`
do
python $py
done
#ls *control*bin*.txt > filelist
#for file in `cat filelist`
#do
#if [[ -f "$file" ]]; then
#echo "$file exists"
#fi
#done

