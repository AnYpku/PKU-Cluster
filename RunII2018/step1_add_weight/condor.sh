#!/bin/sh
ulimit -s unlimited
set -e
cd /afs/cern.ch/user/y/yian/work/RunII2018/CMSSW_10_2_18/src
export SCRAM_ARCH=slc6_amd64_gcc700
source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`
cd /afs/cern.ch/user/y/yian/work/PKU-Cluster/RunII2018/step1_add_weight
g++ -o run `root-config --cflags --glibs` runxx.C
./run >> process_runQCDZA.txt
