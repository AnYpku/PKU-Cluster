operators_and_ranges="\
fT0,-1,1
fT1,-1.5,1.5
fT2,-3,3
fT8,-0.6,0.6
fT9,-1.8,1.8
"

for operator_and_range in $operators_and_ranges
do

operator=`echo $operator_and_range | awk -F, '{print $1}'`
lower=`echo $operator_and_range | awk -F, '{print $2}'`
upper=`echo $operator_and_range | awk -F, '{print $3}'`

#python mine.py $operator $lower $upper
text2workspace.py -m 126 all.txt -o os_mll_${operator}.root -P HiggsAnalysis.CombinedLimit.OneParameterPhysicsModel_combine:my_1d_model --PO range_param=[${lower},${upper}] --PO scaling_filename=./wpwp_${operator}_scaling_refined.root
combine os_mll_${operator}.root -M MultiDimFit -P param --floatOtherPOIs=0 --algo=grid --points=100 --cminDefaultMinimizerStrategy=2 -t -1 --expectSignal=1
mv higgsCombineTest.MultiDimFit.mH120.root higgsCombineTest.MultiDimFit.mH120.expected.${operator}.root

done
