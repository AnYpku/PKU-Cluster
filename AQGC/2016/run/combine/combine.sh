#!/bin/bash
if [[ -f "*.txt" ]]; then
   rm *.txt
fi
cp ../../data_crads/ele/txt/ele16*.txt ./
cp ../../data_crads/muon/txt/mu16*.txt ./
combineCards.py mu16*.txt ele*.txt >& all16.txt
