#!/bin/sh
ulimit -s unlimited
set -e
cd /afs/cern.ch/work/y/yian/work/PKU-Cluster/aQGC/CMSSW_8_1_0/src
export SCRAM_ARCH=slc6_amd64_gcc530
source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`
cd /afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/2016/run/combine/test

if [ $1 -eq 0 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 0 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.0
fi
if [ $1 -eq 1 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 1 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.1
fi
if [ $1 -eq 2 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 2 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.2
fi
if [ $1 -eq 3 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 3 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.3
fi
if [ $1 -eq 4 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 4 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.4
fi
if [ $1 -eq 5 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 5 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.5
fi
if [ $1 -eq 6 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 6 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.6
fi
if [ $1 -eq 7 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 7 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.7
fi
if [ $1 -eq 8 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 8 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.8
fi
if [ $1 -eq 9 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 9 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.9
fi
if [ $1 -eq 10 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 10 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.10
fi
if [ $1 -eq 11 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 11 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.11
fi
if [ $1 -eq 12 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 12 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.12
fi
if [ $1 -eq 13 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 13 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.13
fi
if [ $1 -eq 14 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 14 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.14
fi
if [ $1 -eq 15 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 15 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.15
fi
if [ $1 -eq 16 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 16 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.16
fi
if [ $1 -eq 17 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 17 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.17
fi
if [ $1 -eq 18 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 18 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.18
fi
if [ $1 -eq 19 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 19 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.19
fi
if [ $1 -eq 20 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 20 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.20
fi
if [ $1 -eq 21 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 21 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.21
fi
if [ $1 -eq 22 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 22 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.22
fi
if [ $1 -eq 23 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 23 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.23
fi
if [ $1 -eq 24 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 24 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.24
fi
if [ $1 -eq 25 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 25 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.25
fi
if [ $1 -eq 26 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 26 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.26
fi
if [ $1 -eq 27 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 27 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.27
fi
if [ $1 -eq 28 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 28 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.28
fi
if [ $1 -eq 29 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 29 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.29
fi
if [ $1 -eq 30 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 30 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.30
fi
if [ $1 -eq 31 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 31 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.31
fi
if [ $1 -eq 32 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 32 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.32
fi
if [ $1 -eq 33 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 33 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.33
fi
if [ $1 -eq 34 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 34 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.34
fi
if [ $1 -eq 35 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 35 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.35
fi
if [ $1 -eq 36 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 36 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.36
fi
if [ $1 -eq 37 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 37 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.37
fi
if [ $1 -eq 38 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 38 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.38
fi
if [ $1 -eq 39 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 39 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.39
fi
if [ $1 -eq 40 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 40 -s -1 -d os_mll_fM6.root -n .TEST_fM6.POINT.40
fi