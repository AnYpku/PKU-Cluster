#!/bin/bash

#16
#17
years="\
17
18
"
jetbins="\
0jets
1jets
"

for y in $years
do
  for njets in $jetbins
  do
    combineCards.py emu_${y}_${njets}_CR_bin1.txt emu_${y}_${njets}_CR_bin2.txt  emu_${y}_${njets}_CR_bin3.txt  emu_${y}_${njets}_CR_bin4.txt  emu_${y}_${njets}_CR_bin5.txt  emu_${y}_${njets}_CR_bin6.txt  emu_${y}_${njets}_CR_bin7.txt  emu_${y}_${njets}_CR_bin8.txt  emu_${y}_${njets}_CR_bin9.txt  emu_${y}_${njets}_CR_bin10.txt  emu_${y}_${njets}_CR_bin11.txt  emu_${y}_${njets}_CR_bin12.txt emu_${y}_${njets}_bin1.txt emu_${y}_${njets}_bin2.txt  emu_${y}_${njets}_bin3.txt  emu_${y}_${njets}_bin4.txt  emu_${y}_${njets}_bin5.txt  emu_${y}_${njets}_bin6.txt emu_${y}_${njets}_bin7.txt  emu_${y}_${njets}_bin8.txt  emu_${y}_${njets}_bin9.txt  emu_${y}_${njets}_bin10.txt  emu_${y}_${njets}_bin11.txt emu_${y}_${njets}_bin12.txt -S > shape_${njets}_${y}.txt
    combine -M FitDiagnostics shape_${njets}_${y}.txt --saveShapes -t -1 --expectSignal=1 --saveWithUncertainties -n ${y}_${njets}
  done
done

