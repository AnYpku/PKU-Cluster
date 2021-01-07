year=("16" "17" "18" "combine")
operator=("M0" "M1" "M2" "M3" "M4" "M5" "M6" "M7" "T0" "T1" "T2" "T5" "T6" "T7" "T8" "T9")
for (( j = 0 ; j < ${#year[@]} ; j++ ))
do
    for (( i = 0 ; i < ${#operator[@]} ; i++ ))
    do
      python2.6 draw_1d_limit_plot.py f${operator[$i]} "F_{${operator[$i]}} / #Lambda^{4} (TeV^{-4})"  "expected 95% confidence limit" ../root_fromCombine/higgsCombinenominal.MultiDimFit.mH125.expected.f${operator[$i]}_${year[$j]}.root "expected 2#DeltaNLL" 
     mv deltaNLL_f${operator[$i]}_expected.pdf deltaNLL_f${operator[$i]}_expected_${year[$j]}.pdf
   done
mv result.txt result_${year[$j]}.txt
done
