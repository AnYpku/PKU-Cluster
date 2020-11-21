#!/bin/sh
ulimit -s unlimited
set -e
cd /afs/cern.ch/work/y/yian/work/PKU-Cluster/aQGC/CMSSW_8_1_0/src
export SCRAM_ARCH=slc6_amd64_gcc530
source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`
cd /afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/2016/run/combine/test

if [ $1 -eq 0 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 0.00 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.0.00
fi
if [ $1 -eq 1 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 0.05 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.0.05
fi
if [ $1 -eq 2 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 0.10 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.0.10
fi
if [ $1 -eq 3 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 0.15 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.0.15
fi
if [ $1 -eq 4 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 0.20 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.0.20
fi
if [ $1 -eq 5 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 0.25 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.0.25
fi
if [ $1 -eq 6 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 0.30 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.0.30
fi
if [ $1 -eq 7 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 0.35 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.0.35
fi
if [ $1 -eq 8 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 0.40 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.0.40
fi
if [ $1 -eq 9 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 0.45 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.0.45
fi
if [ $1 -eq 10 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 0.50 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.0.50
fi
if [ $1 -eq 11 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 0.55 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.0.55
fi
if [ $1 -eq 12 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 0.60 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.0.60
fi
if [ $1 -eq 13 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 0.65 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.0.65
fi
if [ $1 -eq 14 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 0.70 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.0.70
fi
if [ $1 -eq 15 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 0.75 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.0.75
fi
if [ $1 -eq 16 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 0.80 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.0.80
fi
if [ $1 -eq 17 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 0.85 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.0.85
fi
if [ $1 -eq 18 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 0.90 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.0.90
fi
if [ $1 -eq 19 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 0.95 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.0.95
fi
if [ $1 -eq 20 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 1.00 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.1.00
fi
if [ $1 -eq 21 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 1.05 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.1.05
fi
if [ $1 -eq 22 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 1.10 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.1.10
fi
if [ $1 -eq 23 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 1.15 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.1.15
fi
if [ $1 -eq 24 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 1.20 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.1.20
fi
if [ $1 -eq 25 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 1.25 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.1.25
fi
if [ $1 -eq 26 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 1.30 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.1.30
fi
if [ $1 -eq 27 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 1.35 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.1.35
fi
if [ $1 -eq 28 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 1.40 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.1.40
fi
if [ $1 -eq 29 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 1.45 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.1.45
fi
if [ $1 -eq 30 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 1.50 -s -1 -d os_mll_fT9.root -n .TEST_fT9.POINT.1.50
fi
