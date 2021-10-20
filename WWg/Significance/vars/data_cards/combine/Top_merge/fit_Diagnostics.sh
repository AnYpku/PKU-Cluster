#!/bin/bash

years="\
17
18
"
jetbins="\
0jets
1jets
"
vars="\
ml1g
ml2g
mllg
"

for var in $vars
do
  for njets in $jetbins
  do
    for y in $years
    do
       if [[ -f file_CR_${y}_${njets}_${var} ]];then
          rm file_CR_${y}_${njets}_${var}
       fi
       if [[ -f file_SR_${y}_${njets}_${var} ]];then
          rm file_SR_${y}_${njets}_${var}
       fi
       for (( i = 0 ; i < 14 ; i++ ))
       do
           file_CR="emu_${y}_${njets}_${var}_CR_bin${i}.txt"
           file_SR="emu_${y}_${njets}_${var}_bin${i}.txt"
           if [[ -f $file_CR  ]];then
              echo "${file_CR}" >> file_CR_${y}_${njets}_${var}
           fi
           if [[ -f $file_SR  ]];then
              echo "${file_SR}" >> file_SR_${y}_${njets}_${var}
           fi
       done
       sed -i ':label;N;s/\n/ /;t label' file_SR_${y}_${njets}_${var}
       sed -i ':label;N;s/\n/ /;t label' file_CR_${y}_${njets}_${var}
       f_CR=`cat file_CR_${y}_${njets}_${var}`
       f_SR=`cat file_SR_${y}_${njets}_${var}`
       combineCards.py $f_CR $f_SR -S > shape_${y}_${njets}_${var}.txt
       combine -M FitDiagnostics shape_${y}_${njets}_${var}.txt --saveShapes -t -1 --expectSignal=1 --saveWithUncertainties -n ${y}_${njets}_${var}
    done
  done
  f17=`cat file_CR_17_0jets_${var} file_CR_17_1jets_${var} file_SR_17_0jets_${var} file_SR_17_1jets_${var}`
  f18=`cat file_CR_18_0jets_${var} file_CR_18_1jets_${var} file_SR_18_0jets_${var} file_SR_18_1jets_${var}`
  combineCards.py $f17 -S > shape_17_${var}.txt
  combineCards.py $f18 -S > shape_18_${var}.txt
  combine -M FitDiagnostics shape_17_${var}.txt --saveShapes -t -1 --expectSignal=1 --saveWithUncertainties -n ${var}
  combine -M FitDiagnostics shape_18_${var}.txt --saveShapes -t -1 --expectSignal=1 --saveWithUncertainties -n ${var}
done

