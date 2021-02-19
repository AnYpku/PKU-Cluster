#!/bin/sh
if [[ -f *.txt ]];then
    rm *.txt
fi
cp ../txt/*bin*.txt ./
recovar=("ptlep1" "photonet" "jet1pt")
#year=("16" "17" "18")
year=("17")
for (( i = 0 ; i < 3 ; i++ ))
do
   for (( j = 0 ; j < ${#year[@]} ; j++ ))
   do
       combineCards.py ${recovar[$i]}_${year[$j]}_*bin*.txt >& ${recovar[$i]}_${year[$j]}.txt
       combineCards.py ${recovar[$i]}_${year[$j]}_*bin*.txt >& ${recovar[$i]}_${year[$j]}.txt
       combineCards.py ${recovar[$i]}_${year[$j]}_*bin*.txt >& ${recovar[$i]}_${year[$j]}.txt
       text2workspace.py -m 125 -o ${recovar[$i]}_${year[$j]}.root ${recovar[$i]}_${year[$j]}.txt -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO map='.*genbin1.*:r_Bin1[1,-2,4]' --PO map='.*genbin2.*:r_Bin2[1,-2,4]' --PO map='.*genbin3.*:r_Bin3[1,-2,4]' --PO map='.*genbin4.*:r_Bin4[1,-2,4]' 
       combine ${recovar[$i]}_${year[$j]}.root -M MultiDimFit --algo singles -t -1 --setParameters r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1 -m 125 --saveFitResult  > tmp_${recovar[$i]}_${year[$j]}.txt 
       sed -n -e '/68/p' tmp_${recovar[$i]}_${year[$j]}.txt > result_${recovar[$i]}_${year[$j]}.txt
       mv multidimfit.root multidimfit_${recovar[$i]}_${year[$j]}.root
   done
   combineCards.py ${recovar[$i]}_16.txt ${recovar[$i]}_17.txt ${recovar[$i]}_18.txt >&${recovar[$i]}_full.txt
   text2workspace.py -m 125 -o ${recovar[$i]}_full.root ${recovar[$i]}_full.txt -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO map='.*genbin1.*:r_Bin1[1,-2,4]' --PO map='.*genbin2.*:r_Bin2[1,-2,4]' --PO map='.*genbin3.*:r_Bin3[1,-2,4]' --PO map='.*genbin4.*:r_Bin4[1,-2,4]' 
   combine ${recovar[$i]}_full.root -M MultiDimFit --algo singles -t -1 --setParameters r_Bin1=1,r_Bin2=1,r_Bin3=1,r_Bin4=1 -m 125 --saveFitResult  > tmp_${recovar[$i]}_full.txt 
   sed -n -e '/68/p' tmp_${recovar[$i]}_full.txt > result_${recovar[$i]}_full.txt
   mv multidimfit.root multidimfit_${recovar[$i]}_full.root
done
