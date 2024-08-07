#!/bin/bash
cp -f /data/pku/home/anying/cms/PKU-Cluster/Significance/CR/data_cards/txt/*16* .
cp -f /data/pku/home/anying/cms/PKU-Cluster/Significance/data_cards/txt/*16* .
cp -f /data/pku/home/anying/cms/PKU-Cluster/Significance/CR/data_cards/txt/*17* .
cp -f /data/pku/home/anying/cms/PKU-Cluster/Significance/data_cards/txt/*17* .
cp -f /data/pku/home/anying/cms/PKU-Cluster/Significance/CR/data_cards/txt/*18* .
cp -f /data/pku/home/anying/cms/PKU-Cluster/Significance/data_cards/txt/*18* .
combineCards.py mu*16*.txt ele*16*.txt >& full16_test.txt
combineCards.py mu*17*.txt ele*17*.txt >& full17_test.txt
combineCards.py mu*18*.txt ele*18*.txt >& full18_test.txt
combineCards.py full16_test.txt full17_test.txt full18_test.txt >& full_RunII.txt

files="\
full16_test.root
full18_test.root
full_RunII.root
full17_test.root
"
for rootfile in $files
do
name=`echo $rootfile | awk -F. '{print $1}'`
sed 's/lnN.*$//' ${name}.txt >tmp1
sed  's/\s\+$//g' tmp1 >tmp
num=`sed -n -e '/rate/=' tmp`
line=$[$num+1]
echo "$line"
sed -i "1,$line d" tmp
theory=`sed -n -e '/theory/p' tmp`
sed -i '/theory/d' tmp
echo "$theory"
sed -n -e '/Stat/p' tmp > tmp2
sed -i ':label;N;s/\n/,/;t label' tmp2
#sed -i "$ a $theory" tmp
mv tmp2 freeze_${name}.txt
NP=`cat freeze_${name}.txt`
#echo "$NP"
combine -M Significance --expectSignal=1 -t -1 ${name}.txt > result_${name}.txt 
#combine -M Significance --expectSignal=1 -t -1 ${name}.txt --freezeParameters all > result_freezeAll${name}.txt 
#combine -M Significance --expectSignal=1 -t -1 ${name}.txt --freezeParameters $NP > result_freezeMCStat${name}.txt 
text2workspace.py ${name}.txt -m 125

#combineTool.py -M Impacts -d ${name}.root -m 125 --doInitialFit --robustFit 1
#combineTool.py -M Impacts -d ${name}.root -m 125 --robustFit 1 --doFits
#combineTool.py -M Impacts -d ${name}.root -m 125 -o impacts_${name}.json
#plotImpacts.py -i impacts_${name}.json -o impacts_${name}
if [[ ${name} = *17* ]];then
   combine -M MultiDimFit -m 125 --algo impact -P pileupId_mis_SR ${name}.txt --expectSignal=1 >> impact_${name}.txt
   combine -M MultiDimFit -m 125 --algo impact -P pileupId_mis_CR ${name}.txt --expectSignal=1 >> impact_${name}.txt
fi
done

years="\
16
17
18
"
#for year in $years
#do
#combine -M MultiDimFit -m 125 --algo impact -P JES_${year} --expectSignal=1 full${year}_test.txt >> impact_JES${year}.txt
#done
