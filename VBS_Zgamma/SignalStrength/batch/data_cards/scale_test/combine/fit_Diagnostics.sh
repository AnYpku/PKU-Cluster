#!/bin/bash

combineCards.py mubarrel_16_bin* mubarrel_17_bin* mubarrel_18_bin* elebarrel_16_bin* elebarrel_17_bin* elebarrel_18_bin* muendcap_16_bin* muendcap_17_bin* muendcap_18_bin* eleendcap_16_bin* eleendcap_17_bin* eleendcap_18_bin* *control_bin* >& all.txt

combineCards.py all.txt -S > all_shape.txt

combine -M FitDiagnostics all_shape.txt -t -1 --expectSignal=1 --saveShapes --saveWithUncertainties
