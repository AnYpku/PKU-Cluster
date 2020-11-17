#!/bin/sh
ulimit -s unlimited
set -e
cd /home/pku/anying/cms/CMSSW_10_2_18/src
export SCRAM_ARCH=slc6_amd64_gcc700
source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`
cd /home/pku/anying/cms/PKU-Cluster/RunII2017/step1_add_weight
g++ -o run1 `root-config --cflags --glibs` runxx.C
./run1 >> process_run.txt
