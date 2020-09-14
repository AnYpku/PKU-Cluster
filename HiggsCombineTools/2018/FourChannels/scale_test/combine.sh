#!/bin/bash
#cd /afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/CMSSW_8_1_0/src
#cmsenv
#cd -
 #sh execut.sh
 #sh execut_CR.sh
combineCards.py muon*18*.txt ele*18*.txt >& full.txt
combine -M Significance full.txt --expectSignal=1 -t -1 > result.txt
