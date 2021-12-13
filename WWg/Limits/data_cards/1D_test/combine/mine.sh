operators_and_ranges="\
kc,-80,80
"

#year=("16" "17" "18" "combine")
njets="\
0jets
"
#1jets
#totaljets

year=("18")
rm *.txt
for (( j = 0 ; j < ${#year[@]} ; j++ ))
do 
   for operator_and_range in $operators_and_ranges
   do
       operator=`echo $operator_and_range | awk -F, '{print $1}'`
       lower=`echo $operator_and_range | awk -F, '{print $2}'`
       upper=`echo $operator_and_range | awk -F, '{print $3}'`
       python mine.py $operator $lower $upper ${year[$j]}
       for jets in $njets
       do
           echo "$jets"
           cp ../txt/emu_${year[$j]}_${jets}_mT_bin*.txt ./
           combineCards.py emu_${year[$j]}_${jets}_mT_bin*.txt >& all_${jets}.txt
           text2workspace.py -m 125 all_${jets}.txt -o os_mll_${operator}_${jets}_${year[$j]}.root -P HiggsAnalysis.CombinedLimit.HiggsKappaCPhysicsModel:my_1d_model --PO range_param=[${lower},${upper}] --PO scaling_filename=./wpwp_${operator}_scaling_refined${year[$j]}.root --X-allow-no-background
#           
           combine os_mll_${operator}_${jets}_${year[$j]}.root -M MultiDimFit -P param --floatOtherPOIs=0 --algo=grid --points=100 --cminDefaultMinimizerStrategy=2 -t -1 --expectSignal=1 -n nominal_${jets}_${year[$j]} -m 125
#           combine os_mll_${operator}_${year[$j]}.root -M MultiDimFit -P param --floatOtherPOIs=0 --algo=grid --points=100 --cminDefaultMinimizerStrategy=2 -n nominal_${year[$j]} -m 125
#           
#           combine os_mll_${operator}_${year[$j]}.root -M MultiDimFit -P param --floatOtherPOIs=0 --algo none --cminDefaultMinimizerStrategy=2 -t -1 --expectSignal=1 -n bestfit1_${operator}_${year[$j]} -m 125 --saveWorkspace
#           
#           combine os_mll_${operator}_${year[$j]}.root -M MultiDimFit -P param --floatOtherPOIs=0 --algo none --cminDefaultMinimizerStrategy=2 -t -1 --expectSignal=1 -n bestfit2_${operator}_${year[$j]} -m 125 --saveWorkspace
#           
#           combine  -M MultiDimFit -P param --floatOtherPOIs=0 --algo=grid --points=100  higgsCombinebestfit1_${operator}_${year[$j]}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeParameters $NP1 --cminDefaultMinimizerStrategy=2 -t -1 --expectSignal=1 -n stat_${year[$j]} -m 125
#           
##           combine -M MultiDimFit -P param --floatOtherPOIs=0 --algo=grid --points=100  higgsCombinebestfit2_${operator}_${year[$j]}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeParameters $NP --cminDefaultMinimizerStrategy=2 -t -1 --expectSignal=1 -m 125 -n MCstat_${year[$j]} 
##           
#           mv higgsCombinenominal_${year[$j]}.MultiDimFit.mH125.root higgsCombinenominal.MultiDimFit.mH125.expected.${operator}_${year[$j]}.root
##           mv higgsCombineMCstat_${year[$j]}.MultiDimFit.mH125.root higgsCombineMCstat.MultiDimFit.mH125.expected.${operator}_${year[$j]}.root
#           mv higgsCombinestat_${year[$j]}.MultiDimFit.mH125.root higgsCombinestat.MultiDimFit.mH125.expected.${operator}_${year[$j]}.root
      done
   done
done
python draw_1d_limit_plot.py kc "#Kappa_{c}"  "expected 95% confidence limit" higgsCombinenominal_0jets_18.MultiDimFit.mH125.root "expected 2#DeltaNLL"
