#!/bin/sh
if [[ -f *Mjj*.txt ]];then
    rm *Mjj*.txt
fi
cp ../../CR/txt/*control_bin*.txt ./
cp ../../txt/*bin*.txt ./
recovar=( "Mjj" )
year=("16" "17" "18")
for (( i = 0 ; i < 1 ; i++ ))
do
   for (( j = 0 ; j < ${#year[@]} ; j++ ))
   do
       combineCards.py ${recovar[$i]}_${year[$j]}_*bin*.txt >& ${recovar[$i]}_${year[$j]}.txt
       combineCards.py ${recovar[$i]}_${year[$j]}_*bin*.txt >& ${recovar[$i]}_${year[$j]}.txt
       combineCards.py ${recovar[$i]}_${year[$j]}_*bin*.txt >& ${recovar[$i]}_${year[$j]}.txt
       text2workspace.py -m 125 -o ${recovar[$i]}_${year[$j]}.root ${recovar[$i]}_${year[$j]}.txt -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO map='.*genbin1.*:r_Bin1[1,-2,4]' --PO map='.*genbin2.*:r_Bin2[1,-2,4]' --PO map='.*genbin3.*:r_Bin3[1,-2,4]' --PO map='.*genbin4.*:r_Bin4[1,-2,4]' --PO map='.*genbin5.*:r_Bin5[1,-2,4]' --PO map='.*genbin6.*:r_Bin6[1,-2,4]' --PO map='.*genbin7.*:r_Bin7[1,-2,4]'
       combine ${recovar[$i]}_${year[$j]}.root -M MultiDimFit --algo singles -t -1 --setParameters r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4,r_Bin5=1,r_Bin6=1,r_Bin7=1 -m 125 --saveFitResult  > tmp_${recovar[$i]}_${year[$j]}.txt 
       sed -n -e '/68/p' tmp_${recovar[$i]}_${year[$j]}.txt > result_${recovar[$i]}_${year[$j]}.txt
       mv multidimfit.root multidimfit_${recovar[$i]}_${year[$j]}.root
   done
   combineCards.py ${recovar[$i]}_16.txt ${recovar[$i]}_17.txt ${recovar[$i]}_18.txt >&${recovar[$i]}_full.txt
   text2workspace.py -m 125 -o Mjj_full.root Mjj_full.txt -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO map='.*genbin1.*:r_Bin1[1,-2,4]' --PO map='.*genbin2.*:r_Bin2[1,-2,4]' --PO map='.*genbin3.*:r_Bin3[1,-2,4]' --PO map='.*genbin4.*:r_Bin4[1,-2,4]' --PO map='.*genbin5.*:r_Bin5[1,-2,4]' --PO map='.*genbin6.*:r_Bin6[1,-2,4]' --PO map='.*genbin7.*:r_Bin7[1,-2,4]'
   combine Mjj_full.root -M MultiDimFit --algo singles -t -1 --setParameters r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1,r_Bin5=1,r_Bin6=1,r_Bin7=1 -m 125 --saveFitResult  > tmp_Mjj_full.txt 
   sed -n -e '/68/p'  tmp_Mjj_full.txt > result_Mjj_full.txt
   mv multidimfit.root multidimfit_Mjj_full.root
done
