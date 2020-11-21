#!/bin/sh
ulimit -s unlimited
set -e
set INPUT_FILE="wpwp_fT9_scaling_refined.root"
cd /afs/cern.ch/work/y/yian/work/PKU-Cluster/aQGC/CMSSW_8_1_0/src
export SCRAM_ARCH=slc6_amd64_gcc530
source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`
cd /afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/2016/run/combine/test
eval combine --LHCmode LHC-limits --clsAcc 0 -T 20 --saveHybridResult -M HybridNew -m 125 --singlePoint 0.99 -s -1 -d os_mll_fT9.root -n .Test.POINT.0.99
