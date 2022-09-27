#!/bin/bash
combineCards.py muendcap_16_bin*.txt >& muendcap16.txt
combineCards.py muendcap_17_bin*.txt >& muendcap17.txt
combineCards.py muendcap_18_bin*.txt >& muendcap18.txt

combineCards.py mubarrel_16_bin*.txt >& mubarrel16.txt
combineCards.py mubarrel_17_bin*.txt >& mubarrel17.txt
combineCards.py mubarrel_18_bin*.txt >& mubarrel18.txt

combineCards.py elebarrel_16_bin*.txt >& elebarrel16.txt
combineCards.py elebarrel_17_bin*.txt >& elebarrel17.txt
combineCards.py elebarrel_18_bin*.txt >& elebarrel18.txt

combineCards.py eleendcap_16_bin*.txt >& eleendcap16.txt
combineCards.py eleendcap_17_bin*.txt >& eleendcap17.txt
combineCards.py eleendcap_18_bin*.txt >& eleendcap18.txt

combine -M Significance --expectSignal=1 -t -1 muendcap16.txt
combine -M Significance --expectSignal=1 -t -1 muendcap17.txt
combine -M Significance --expectSignal=1 -t -1 muendcap18.txt

combine -M Significance --expectSignal=1 -t -1 mubarrel16.txt
combine -M Significance --expectSignal=1 -t -1 mubarrel17.txt
combine -M Significance --expectSignal=1 -t -1 mubarrel18.txt

combine -M Significance --expectSignal=1 -t -1 eleendcap16.txt
combine -M Significance --expectSignal=1 -t -1 eleendcap17.txt
combine -M Significance --expectSignal=1 -t -1 eleendcap18.txt

combine -M Significance --expectSignal=1 -t -1 elebarrel16.txt
combine -M Significance --expectSignal=1 -t -1 elebarrel17.txt
combine -M Significance --expectSignal=1 -t -1 elebarrel18.txt
