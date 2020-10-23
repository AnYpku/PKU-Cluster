#!/bin/sh
ulimit -s unlimited
set -e
cd /afs/cern.ch/work/y/yian/work/PKU-Cluster/aQGC/CMSSW_8_1_0/src
export SCRAM_ARCH=slc6_amd64_gcc530
source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`
cd /afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/Wgamma/test/fT1

#combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint $1 -s -1 -d os_mll_fT1.root -n .TEST_fT1.POINT.${1}
combine --LHCmode LHC-feldman-cousins --clsAcc 0 -T 500 --saveHybridResult --saveToys -M HybridNew -m 125 --singlePoint $1 -s -1 -d os_mll_fT1.root -n .TEST_fT1.POINT.${1}
