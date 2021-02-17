#!/bin/bash
combineCards.py all.txt -S > shape_all.txt
combine -M FitDiagnostics  shape_all.txt --saveShapes -t -1 --expectSignal=1 --saveWithUncertainties
