#!/bin/bash
#cd /afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/CMSSW_8_1_0/src
#cmsenv
#cd -
#cp /afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2016/FourChannels/2016elebarrel/CR/*control*.txt ./
#cp /afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2016/FourChannels/2016eleendcap/CR/*control*.txt ./
#cp /afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2016/FourChannels/2016mubarrel/CR/*control*.txt ./
#cp /afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2016/FourChannels/2016muendcap/CR/*control*.txt ./

combineCards.py muon*.txt ele*.txt >& full.txt
combine -M Significance full.txt --expectSignal=1 -t -1 > result2.txt
