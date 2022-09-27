#fM0,-30,30
#fM1,-60,60
#fM2,-15,15
#fM3,-25,25
#fM4,-25,25
#fM5,-40,40
#fM6,-60,60
#fM7,-90,90
#fT0,-1,1
#fT1,-1.5,1.5
#fT2,-3,3
#fT5,-1.2,1.2
operators_and_ranges="\
fT0,-5,5
fT1,-5,5
fT2,-5,5
fT8,-10,10
fT9,-10,10
"

for operator_and_range in $operators_and_ranges
do

operator=`echo $operator_and_range | awk -F, '{print $1}'`
lower=`echo $operator_and_range | awk -F, '{print $2}'`
upper=`echo $operator_and_range | awk -F, '{print $3}'`

text2workspace.py -m 126 all.txt -o os_mll_${operator}.root -P HiggsAnalysis.CombinedLimit.OneParameterPhysicsModel:my_1d_model --PO range_param=[${lower},${upper}] --PO scaling_filename=./ZZ_scaling_refined_${operator}.root
combine os_mll_${operator}.root -M MultiDimFit -P param --floatOtherPOIs=0 --algo=grid --points=5000 --cminDefaultMinimizerStrategy=2 -t -1 --expectSignal=1
mv higgsCombineTest.MultiDimFit.mH120.root higgsCombineTest.MultiDimFit.mH120.expected.${operator}.root


done
