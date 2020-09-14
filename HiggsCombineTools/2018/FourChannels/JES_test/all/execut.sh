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
                                l=$[$line+1]
				sed -i "$line,$l d" tmp1    
#				line=$[$line+1]
				sed -i "$line i$qcd" tmp1
				sed -i "$line i$ewk" tmp1
			 fi
                done < num

	cp tmp1 python.py
}


dir1="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2018/FourChannels/2018eleendcap/SR/mjj5007501000_detajj25456_zepp18"
dir2="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2018/FourChannels/2018eleendcap/SR/mjj5007501000_detajj25456_zepp18/aa.root"
qcd="jes_QCD=[1.21,1.27,1.37,1.52,1.49,1.42,2.05]"
ewk="jes=[1.01,1.05,1.13,1.09,1.01,1.10,1.06]"
run 
mv python.py python_ee.py

dir1="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2018/FourChannels/2018mubarrel/SR/mjj5007501000_detajj25456_zepp18"
dir2="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2018/FourChannels/2018mubarrel/SR/mjj5007501000_detajj25456_zepp18/aa.root"
qcd="jes_QCD=[1.21,1.27,1.37,1.52,1.49,1.42,2.05]"
ewk="jes=[1.01,1.05,1.13,1.09,1.01,1.10,1.06]"
run 
mv python.py python_mb.py
dir1="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2018/FourChannels/2018elebarrel/SR/mjj5007501000_detajj25456_zepp18"
dir2="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2018/FourChannels/2018elebarrel/SR/mjj5007501000_detajj25456_zepp18/aa.root"
qcd="jes_QCD=[1.21,1.27,1.37,1.52,1.49,1.42,2.05]"
ewk="jes=[1.01,1.05,1.13,1.09,1.01,1.10,1.06]"
run 
mv python.py python_eb.py

dir1="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2018/FourChannels/2018muendcap/SR/mjj5007501000_detajj25456_zepp18"
dir2="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2018/FourChannels/2018muendcap/SR/mjj5007501000_detajj25456_zepp18/aa.root"
qcd="jes_QCD=[1.21,1.27,1.37,1.52,1.49,1.42,2.05]"
ewk="jes=[1.01,1.05,1.13,1.09,1.01,1.10,1.06]"
run 
mv python.py python_me.py

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
