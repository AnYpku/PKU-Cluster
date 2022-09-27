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

#year=("16" "17" "18" "combine")
year=("combine")
for (( j = 0 ; j < ${#year[@]} ; j++ ))
do 
   cd ../txt
   if [[ -f all_test.txt ]];then
         rm all_test.txt
   fi
   if [[ ${year[$j]} = "combine" ]];then
       combineCards.py mu*16*.txt ele*16*.txt mu*17*.txt ele*17*.txt mu*18*.txt ele*18*.txt >& all_test.txt
   else
       combineCards.py mu*${year[$j]}*.txt ele*${year[$j]}*.txt >& all_${year[$j]}.txt
   fi
   cd -
   cp ../txt/all_test.txt ./
   sed 's/lnN.*$//' all_test.txt >tmp1
   sed  's/\s\+$//g' tmp1 >tmp
   num=`sed -n -e '/rate/=' tmp`
   line=$[$num+1]
   echo "$line"
   sed -i "1,$line d" tmp
   sed '/Stat/d' tmp > tmp2
   sed -i ':label;N;s/\n/,/;t label' tmp2
   mv tmp2 freeze_Stat.txt
   sed -i '/VV_xs/d' tmp
   sed -i ':label;N;s/\n/,/;t label' tmp
   mv tmp freeze_all.txt
   sed -i 's/others_xs,//g' freeze_all.txt
   NP=`cat freeze_Stat.txt`
   NP1=`cat freeze_all.txt`
#   echo "$NP"
#   echo "$NP1"
   for operator_and_range in $operators_and_ranges
   do
       operator=`echo $operator_and_range | awk -F, '{print $1}'`
       lower=`echo $operator_and_range | awk -F, '{print $2}'`
       upper=`echo $operator_and_range | awk -F, '{print $3}'`
       python mine_combine.py $operator $lower $upper test
       text2workspace.py -m 125 all_test.txt -o os_mll_${operator}_test.root -P HiggsAnalysis.CombinedLimit.OneParameterPhysicsModel_all:my_1d_model --PO range_param=[${lower},${upper}] --PO scaling_filename=./wpwp_${operator}_scaling_refinedtest.root --X-allow-no-background
#       echo "text2workspace.py -m 125 all_${year[$j]}.txt -o os_mll_${operator}_${year[$j]}.root -P HiggsAnalysis.CombinedLimit.OneParameterPhysicsModel:my_1d_model --PO range_param=[${lower},${upper}] --PO scaling_filename=./wpwp_${operator}_scaling_refined${year[$j]}.root"
#       
       combine os_mll_${operator}_test.root -M MultiDimFit -P param --floatOtherPOIs=0 --algo=grid --points=100 --cminDefaultMinimizerStrategy=2 -t -1 --expectSignal=1 -n nominal_test -m 125
       
       combine os_mll_${operator}_test.root -M MultiDimFit -P param --floatOtherPOIs=0 --algo none --cminDefaultMinimizerStrategy=2 -t -1 --expectSignal=1 -n bestfit1_${operator}_test -m 125 --saveWorkspace
       
       combine os_mll_${operator}_test.root -M MultiDimFit -P param --floatOtherPOIs=0 --algo none --cminDefaultMinimizerStrategy=2 -t -1 --expectSignal=1 -n bestfit2_${operator}_test -m 125 --saveWorkspace
       
       combine  -M MultiDimFit -P param --floatOtherPOIs=0 --algo=grid --points=100  higgsCombinebestfit1_${operator}_test.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeParameters $NP1 --cminDefaultMinimizerStrategy=2 -t -1 --expectSignal=1 -n stat_test -m 125
       
#       
       mv higgsCombinenominal_test.MultiDimFit.mH125.root higgsCombinenominal.MultiDimFit.mH125.expected.${operator}_test.root
       mv higgsCombinestat_test.MultiDimFit.mH125.root higgsCombinestat.MultiDimFit.mH125.expected.${operator}_test.root
   done
done
