#!/bin/bash

years="\
16
17
18
"
for y in $years
do
  combineCards.py emu_18_bin1.txt emu_18_bin2.txt  emu_18_bin3.txt  emu_18_bin4.txt  emu_18_bin5.txt  emu_18_bin6.txt emu_18_bin7.txt  emu_18_bin8.txt  emu_18_bin9.txt  emu_18_bin10.txt  emu_18_bin11.txt emu_18_bin12.txt  emu_18_bin13.txt  emu_18_bin14.txt   emu_18_bin15.txt  emu_18_bin16.txt  -S > shape_${y}.txt
  combine -M FitDiagnostics shape_${y}.txt --saveShapes -t -1 --expectSignal=1 --saveWithUncertainties -n ${y}
done

