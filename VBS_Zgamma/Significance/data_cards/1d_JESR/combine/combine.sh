#!/bin/bash
#cd /afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/CMSSW_8_1_0/src
#cmsenv
#cd -

files="\
full16_test.root
"
#full17_test.root
#full18_test.root
for rootfile in $files
do
name=`echo $rootfile | awk -F. '{print $1}'`
sed 's/lnN.*$//' ${name}.txt >tmp1
sed  's/\s\+$//g' tmp1 >tmp
num=`sed -n -e '/rate/=' tmp`
line=$[$num+1]
echo "$line"
sed -i "1,$line d" tmp

sed -i ':label;N;s/\n/,/;t label' tmp
mv tmp freeze_${name}.txt
NP=`cat freeze_${name}.txt`
#echo "$NP"
done


#cp /afs/cern.ch/user/y/yian/work/PKU-Cluster/Significance/CR/data_cards/txt/*16* .
#cp /afs/cern.ch/user/y/yian/work/PKU-Cluster/Significance/data_cards/1d_JESR/txt/*16* .
#cp /afs/cern.ch/user/y/yian/work/PKU-Cluster/Significance/CR/data_cards/txt/*17* .
#cp /afs/cern.ch/user/y/yian/work/PKU-Cluster/Significance/data_cards/1d_JESR/txt/*17* .
#cp /afs/cern.ch/user/y/yian/work/PKU-Cluster/Significance/CR/data_cards/txt/*18* .
#cp /afs/cern.ch/user/y/yian/work/PKU-Cluster/Significance/data_cards/1d_JESR/txt/*18* .
#combineCards.py mu*16*.txt ele*16*.txt >& full16_test.txt
#combineCards.py mu*17*.txt ele*17*.txt >& full17_test.txt
#combineCards.py mu*18*.txt ele*18*.txt >& full18_test.txt
#combine -M Significance --expectSignal=1 -t -1 full16_test.txt > result16.txt  
#combine -M Significance --expectSignal=1 -t -1 full17_test.txt > result17.txt
#combine -M Significance --expectSignal=1 -t -1 full18_test.txt > result18.txt
years="\
16
17
18
"
for year in $years
do
combine -M MultiDimFit -m 125 --algo impact -P JES_${year} --expectSignal=1 full${year}_test.txt >> impact_JES${year}.txt
done
