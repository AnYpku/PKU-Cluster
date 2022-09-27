operators_and_ranges="\
fM0,-30,30
fM1,-60,60
fM2,-15,15
fM3,-25,25
fM4,-25,25
fM5,-40,40
fM6,-60,60
fM7,-90,90
fT0,-1,1
fT1,-1.5,1.5
fT2,-3,3
fT5,-1.2,1.2
fT6,-3,3
fT7,-4,4
fT8,-0.6,0.6
fT9,-1.8,1.8
"

year=("16" "17" "18" "combine")
#year=("16")
for (( j = 0 ; j < ${#year[@]} ; j++ ))
do 
   sed 's/lnN.*$//' all_${year[$j]}.txt >tmp1
   sed  's/\s\+$//g' tmp1 >tmp
   num=`sed -n -e '/rate/=' tmp`
   line=$[$num+1]
   echo "$line"
   sed -i "1,$line d" tmp
   sed '/stat/d' tmp > tmp2
   sed -i ':label;N;s/\n/,/;t label' tmp2
   mv tmp2 freeze_MCstat.txt
   sed -i '/others_xs/d' tmp
   sed -i ':label;N;s/\n/,/;t label' tmp
   mv tmp freeze_all.txt
   NP=`cat freeze_MCstat.txt`
   NP1=`cat freeze_all.txt`
#   echo "$NP"
#   echo "$NP1"
   for operator_and_range in $operators_and_ranges
   do
       operator=`echo $operator_and_range | awk -F, '{print $1}'`
       lower=`echo $operator_and_range | awk -F, '{print $2}'`
       upper=`echo $operator_and_range | awk -F, '{print $3}'`
       
       echo "combine os_mll_${operator}_${year[$j]}.root -M MultiDimFit -P param --floatOtherPOIs=0 --algo none --cminDefaultMinimizerStrategy=2 -t -1 --expectSignal=1 -n bestfit1_${operator}_${year[$j]} -m 125 --saveWorkspace"   
       combine os_mll_${operator}_${year[$j]}.root -M MultiDimFit -P param --floatOtherPOIs=0 --algo none --cminDefaultMinimizerStrategy=2 -t -1 --expectSignal=1 -n bestfit1_${operator}_${year[$j]} -m 125 --saveWorkspace
       
       combine os_mll_${operator}_${year[$j]}.root -M MultiDimFit -P param --floatOtherPOIs=0 --algo none --cminDefaultMinimizerStrategy=2 -t -1 --expectSignal=1 -n bestfit2_${operator}_${year[$j]} -m 125 --saveWorkspace
       
       echo "combine  -M MultiDimFit -P param --floatOtherPOIs=0 --algo=grid --points=100  higgsCombinebestfit1_${operator}_${year[$j]}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeParameters $NP1 --cminDefaultMinimizerStrategy=2 -t -1 --expectSignal=1 -n stat_${year[$j]} -m 125"
       combine  -M MultiDimFit -P param --floatOtherPOIs=0 --algo=grid --points=100  higgsCombinebestfit1_${operator}_${year[$j]}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeParameters $NP1 --cminDefaultMinimizerStrategy=2 -t -1 --expectSignal=1 -n stat_${year[$j]} -m 125
       
       echo "combine -M MultiDimFit -P param --floatOtherPOIs=0 --algo=grid --points=100  higgsCombinebestfit2_${operator}_${year[$j]}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeParameters $NP --cminDefaultMinimizerStrategy=2 -t -1 --expectSignal=1 -m 125 -n MCstat_${year[$j]}"
       combine -M MultiDimFit -P param --floatOtherPOIs=0 --algo=grid --points=100  higgsCombinebestfit2_${operator}_${year[$j]}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeParameters $NP --cminDefaultMinimizerStrategy=2 -t -1 --expectSignal=1 -m 125 -n MCstat_${year[$j]} 
       
       mv higgsCombineMCstat_${year[$j]}.MultiDimFit.mH125.root higgsCombineMCstat.MultiDimFit.mH125.expected.${operator}_${year[$j]}.root
       mv higgsCombinestat_${year[$j]}.MultiDimFit.mH125.root higgsCombinestat.MultiDimFit.mH125.expected.${operator}_${year[$j]}.root
   done
done
