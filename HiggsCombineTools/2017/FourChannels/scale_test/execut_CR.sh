#!/bin/bash
#cd /afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/CMSSW_8_1_0/src
#cmsenv
#cd -
function run()
{
	cp $dir1/th2_to_txt.py .
		sed -e 's|\.\/aa\.root|'$dir2'|g' th2_to_txt.py >tmp1
		i=`sed -n -e '/scale_QCD/=' tmp1` 
                sed -i '/QCDZA_scale_extra/d' tmp1
		sed -i '/kmax/s/24/25/g' tmp1
		echo "$i" > num
		mark="write"
		while read line; do
			echo "$line"
                        str=`sed -n "${line}p" tmp1`
			echo "$str"
		        if [[ $line -lt 100 ]]; then
				sed -i "$line d" tmp1    
				sed -i "$line i$band1" tmp1
				sed -i "$line i$band2" tmp1
				sed -i "$line i$band3" tmp1
			 fi
                        if [[ $str == *$mark* ]]; then
                           sed -i "${line}s/scale_QCD/scale_QCD_band1/" tmp1
			   sed -i "${line}s/QCDZA_scale/QCDZA_scale1/" tmp1

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


			fi
                        
                done < num

	cp tmp1 python.py
}


dir1="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2017/FourChannels/2017mubarrel/SR/CR/"
dir2="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2017/FourChannels/2017mubarrel/SR/CR/aa.root"
band1="scale_QCD_band1=[1.011]"
band2="scale_QCD_band2=[1.16]"
band3="scale_QCD_band3=[1.17]"
run 
mv python.py py_CRee.py

dir1="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2017/FourChannels/2017muendcap/SR/CR/"
dir2="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2017/FourChannels/2017muendcap/SR/CR/aa.root"
run 
mv python.py py_CRmb.py

dir1="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2017/FourChannels/2017elebarrel/SR/CR/"
dir2="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2017/FourChannels/2017elebarrel/SR/CR/aa.root"
run 
mv python.py py_CReb.py

dir1="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2017/FourChannels/2017eleendcap/SR/CR/"
dir2="/afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2017/FourChannels/2017eleendcap/SR/CR/aa.root"
run 
mv python.py py_CRme.py

ls py*CR*.py > temp6
for py in `cat temp6`
do
python $py
done
ls *control*.txt > filelist

for file in `cat filelist`
do
if [[ -f "$file" ]]; then
echo "$file exists"
fi
done
