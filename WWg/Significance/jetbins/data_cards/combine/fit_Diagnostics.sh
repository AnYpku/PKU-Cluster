#!/bin/bash

#16
#17
years="\
17
18
"
for y in $years
do
  combineCards.py emu_${y}_CR_bin1.txt emu_${y}_CR_bin2.txt  emu_${y}_CR_bin3.txt  emu_${y}_CR_bin4.txt  emu_${y}_CR_bin5.txt  emu_${y}_CR_bin6.txt  emu_${y}_CR_bin7.txt  emu_${y}_CR_bin8.txt  emu_${y}_CR_bin9.txt  emu_${y}_CR_bin10.txt  emu_${y}_CR_bin11.txt  emu_${y}_CR_bin12.txt emu_${y}_bin1.txt emu_${y}_bin2.txt  emu_${y}_bin3.txt  emu_${y}_bin4.txt  emu_${y}_bin5.txt  emu_${y}_bin6.txt emu_${y}_bin7.txt  emu_${y}_bin8.txt  emu_${y}_bin9.txt  emu_${y}_bin10.txt  emu_${y}_bin11.txt emu_${y}_bin12.txt  emu_${y}_bin13.txt  emu_${y}_bin14.txt   emu_${y}_bin15.txt  emu_${y}_bin16.txt  -S > shape_${y}.txt
  combine -M FitDiagnostics shape_${y}.txt --saveShapes -t -1 --expectSignal=1 --saveWithUncertainties -n ${y}
done

