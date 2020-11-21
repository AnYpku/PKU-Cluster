#!/bin/bash
if [[ -f "*.txt" ]]; then
   rm *.txt
fi
cp ../../data_crads/ele/txt/ele17*.txt ./
cp ../../data_crads/muon/txt/mu17*.txt ./
combineCards.py mu17*.txt ele17*.txt >& all17.txt
