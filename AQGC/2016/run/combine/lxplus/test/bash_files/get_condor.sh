operators_and_ranges="\
fM0,20,0.5
fM1,40,1
fM2,15,0.5
fM3,20,0.5
fM4,20,0.5
fM5,25,0.5
fM6,40,1
fM7,60,1
fT0,1.0,0.05
fT1,1.5,0.05
fT2,2.0,0.05
fT5,1.0,0.05
fT6,2.0,0.05
fT7,3.0,0.05
fT8,0.6,0.05
fT9,1.5,0.05
"
for operator_and_range in $operators_and_ranges
do

operator=`echo $operator_and_range | awk -F, '{print $1}'`
upper=`echo $operator_and_range | awk -F, '{print $2}'`
step=`echo $operator_and_range | awk -F, '{print 3}'`
echo "$operator,$upper,$step"
combineTool.py -d os_mll_${operator}.root -M HybridNew --LHCmode LHC-limits --clsAcc 0  -T 500 -s -1 --singlePoint 0:${upper}:${step} --saveHybridResult -m 125 --job-mode condor --task-name condor-${operator}

done 
