sed -e 's/result/result_stat/g' draw_1d_limit_plot.py  > python_stat.py
year=("16" "17" "18" "combine")
for (( j = 0 ; j < ${#year[@]} ; j++ ))
do
python2.6 python_stat.py fM0 "F_{M0} / #Lambda^{4} (TeV^{-4})"  "expected 95% confidence limit" higgsCombinestat.MultiDimFit.mH125.expected.fM0_${year[$j]}.root "expected 2#DeltaNLL" 
python2.6 python_stat.py fM1 "F_{M1} / #Lambda^{4} (TeV^{-4})"  "expected 95% confidence limit" higgsCombinestat.MultiDimFit.mH125.expected.fM1_${year[$j]}.root "expected 2#DeltaNLL" 
python2.6 python_stat.py fM2 "F_{M2} / #Lambda^{4} (TeV^{-4})"  "expected 95% confidence limit" higgsCombinestat.MultiDimFit.mH125.expected.fM2_${year[$j]}.root "expected 2#DeltaNLL" 
python2.6 python_stat.py fM3 "F_{M3} / #Lambda^{4} (TeV^{-4})"  "expected 95% confidence limit" higgsCombinestat.MultiDimFit.mH125.expected.fM3_${year[$j]}.root "expected 2#DeltaNLL" 
python2.6 python_stat.py fM4 "F_{M4} / #Lambda^{4} (TeV^{-4})"  "expected 95% confidence limit" higgsCombinestat.MultiDimFit.mH125.expected.fM4_${year[$j]}.root "expected 2#DeltaNLL" 
python2.6 python_stat.py fM5 "F_{M5} / #Lambda^{4} (TeV^{-4})"  "expected 95% confidence limit" higgsCombinestat.MultiDimFit.mH125.expected.fM5_${year[$j]}.root "expected 2#DeltaNLL" 
python2.6 python_stat.py fM6 "F_{M6} / #Lambda^{4} (TeV^{-4})"  "expected 95% confidence limit" higgsCombinestat.MultiDimFit.mH125.expected.fM6_${year[$j]}.root "expected 2#DeltaNLL" 
python2.6 python_stat.py fM7 "F_{M7} / #Lambda^{4} (TeV^{-4})"  "expected 95% confidence limit" higgsCombinestat.MultiDimFit.mH125.expected.fM7_${year[$j]}.root "expected 2#DeltaNLL" 
python2.6 python_stat.py fT0 "F_{T0} / #Lambda^{4} (TeV^{-4})"  "expected 95% confidence limit" higgsCombinestat.MultiDimFit.mH125.expected.fT0_${year[$j]}.root "expected 2#DeltaNLL" 
python2.6 python_stat.py fT1 "F_{T1} / #Lambda^{4} (TeV^{-4})"  "expected 95% confidence limit" higgsCombinestat.MultiDimFit.mH125.expected.fT1_${year[$j]}.root "expected 2#DeltaNLL" 
python2.6 python_stat.py fT2 "F_{T2} / #Lambda^{4} (TeV^{-4})"  "expected 95% confidence limit" higgsCombinestat.MultiDimFit.mH125.expected.fT2_${year[$j]}.root "expected 2#DeltaNLL" 
python2.6 python_stat.py fT5 "F_{T5} / #Lambda^{4} (TeV^{-4})"  "expected 95% confidence limit" higgsCombinestat.MultiDimFit.mH125.expected.fT5_${year[$j]}.root "expected 2#DeltaNLL" 
python2.6 python_stat.py fT6 "F_{T6} / #Lambda^{4} (TeV^{-4})"  "expected 95% confidence limit" higgsCombinestat.MultiDimFit.mH125.expected.fT6_${year[$j]}.root "expected 2#DeltaNLL" 
python2.6 python_stat.py fT7 "F_{T7} / #Lambda^{4} (TeV^{-4})"  "expected 95% confidence limit" higgsCombinestat.MultiDimFit.mH125.expected.fT7_${year[$j]}.root "expected 2#DeltaNLL" 
python2.6 python_stat.py fT8 "F_{T8} / #Lambda^{4} (TeV^{-4})"  "expected 95% confidence limit" higgsCombinestat.MultiDimFit.mH125.expected.fT8_${year[$j]}.root "expected 2#DeltaNLL" 
python2.6 python_stat.py fT9 "F_{T9} / #Lambda^{4} (TeV^{-4})"  "expected 95% confidence limit" higgsCombinestat.MultiDimFit.mH125.expected.fT9_${year[$j]}.root "expected 2#DeltaNLL" 
mv result_stat.txt result_stat_${year[$j]}.txt
done
