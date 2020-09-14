#!/bin/bash
#cd /afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/CMSSW_8_1_0/src
#cmsenv
#cd -
cp /afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2018/FourChannels/2018elebarrel/SR/CR/*18*control*.txt ./
cp /afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2018/FourChannels/2018eleendcap/SR/CR/*18*control*.txt ./
cp /afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2018/FourChannels/2018mubarrel/SR/CR/*18*control*.txt ./
cp /afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2018/FourChannels/2018muendcap/SR/CR/*18*control*.txt ./

combineCards.py muon*18*.txt ele*18*.txt >& full.txt
combine -M Significance full.txt --expectSignal=1 -t -1 > result.txt
