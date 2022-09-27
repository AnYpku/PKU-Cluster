#!/bin/bash
#num=`sed -n -e '/lumi/=' mubarrel_16_bin1.txt`
sed 's/lnN.*$//' full16_test.txt >tmp1
sed  's/\s\+$//g' tmp1 >tmp
num=`sed -n -e '/rate/=' tmp`
line=$[$num+1]
echo "$line"
sed -i "1,$line d" tmp
theory=`sed -n -e '/theory/p' tmp`
sed -i '/theory/d' tmp
echo "$theory"
sed -i ':label;N;s/\n/,/;t label' tmp
#sed -i "$ a $theory" tmp
sed -i 's/ST_Stat_control_bin1_eleendcap//g' tmp
mv tmp freezeP_16.txt


