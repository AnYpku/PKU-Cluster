#!/bin/bash
if [[ -f "*.txt" ]]; then
   rm *.txt
fi
cp ../../data_crads/ele/txt/*.txt ./
cp ../../data_crads/muon/txt/mu18*.txt ./
combineCards.py mu18*.txt ele*.txt >& all18.txt

