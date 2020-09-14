#!/bin/bash
#cd /afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/CMSSW_8_1_0/src
#cmsenv
#cd -
cp /afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2017/FourChannels/2017elebarrel/SR/CR/ele17*control*.txt ./
cp /afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2017/FourChannels/2017eleendcap/SR/CR/ele17*control*.txt ./
cp /afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2017/FourChannels/2017mubarrel/SR/CR/muon17*control*.txt ./
cp /afs/cern.ch/user/y/yian/work/PKU-Cluster/HiggsCombineTools/2017/FourChannels/2017muendcap/SR/CR/muon17*control*.txt ./

combineCards.py muon*17*.txt ele*17*.txt >& full.txt
combine -M Significance full.txt --expectSignal=1 -t -1 > result.txt
