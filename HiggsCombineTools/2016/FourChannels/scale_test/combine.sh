#!/bin/bash
#cd /afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/CMSSW_8_1_0/src
#cmsenv
#cd -

combineCards.py muon*16*.txt ele*16*.txt >& full.txt
combine -M Significance full.txt --expectSignal=1 -t -1 > result.txt
