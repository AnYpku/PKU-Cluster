#!/bin/bash
if [[ -f "*.txt" ]]; then
   rm *.txt
fi
cp ../../data_crads/ele/txt/ele*.txt ./
cp ../../data_crads/muon/txt/mu*.txt ./
combineCards.py mu*.txt ele*.txt >& all.txt
