#!/bin/sh
ulimit -s unlimited
set -e
cd /afs/cern.ch/work/y/yian/work/PKU-Cluster/aQGC/CMSSW_8_1_0/src
export SCRAM_ARCH=slc6_amd64_gcc530
source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`
cd /afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/2016/run/combine/test/fM2

if [ $1 -eq 0 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 0.0 -s -1 -d os_mll_fM2.root -n .Test.POINT.0.0
fi
if [ $1 -eq 1 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 0.5 -s -1 -d os_mll_fM2.root -n .Test.POINT.0.5
fi
if [ $1 -eq 2 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 1.0 -s -1 -d os_mll_fM2.root -n .Test.POINT.1.0
fi
if [ $1 -eq 3 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 1.5 -s -1 -d os_mll_fM2.root -n .Test.POINT.1.5
fi
if [ $1 -eq 4 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 2.0 -s -1 -d os_mll_fM2.root -n .Test.POINT.2.0
fi
if [ $1 -eq 5 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 2.5 -s -1 -d os_mll_fM2.root -n .Test.POINT.2.5
fi
if [ $1 -eq 6 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 3.0 -s -1 -d os_mll_fM2.root -n .Test.POINT.3.0
fi
if [ $1 -eq 7 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 3.5 -s -1 -d os_mll_fM2.root -n .Test.POINT.3.5
fi
if [ $1 -eq 8 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 4.0 -s -1 -d os_mll_fM2.root -n .Test.POINT.4.0
fi
if [ $1 -eq 9 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 4.5 -s -1 -d os_mll_fM2.root -n .Test.POINT.4.5
fi
if [ $1 -eq 10 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 5.0 -s -1 -d os_mll_fM2.root -n .Test.POINT.5.0
fi
if [ $1 -eq 11 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 5.5 -s -1 -d os_mll_fM2.root -n .Test.POINT.5.5
fi
if [ $1 -eq 12 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 6.0 -s -1 -d os_mll_fM2.root -n .Test.POINT.6.0
fi
if [ $1 -eq 13 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 6.5 -s -1 -d os_mll_fM2.root -n .Test.POINT.6.5
fi
if [ $1 -eq 14 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 7.0 -s -1 -d os_mll_fM2.root -n .Test.POINT.7.0
fi
if [ $1 -eq 15 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 7.5 -s -1 -d os_mll_fM2.root -n .Test.POINT.7.5
fi
if [ $1 -eq 16 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 8.0 -s -1 -d os_mll_fM2.root -n .Test.POINT.8.0
fi
if [ $1 -eq 17 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 8.5 -s -1 -d os_mll_fM2.root -n .Test.POINT.8.5
fi
if [ $1 -eq 18 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 9.0 -s -1 -d os_mll_fM2.root -n .Test.POINT.9.0
fi
if [ $1 -eq 19 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 9.5 -s -1 -d os_mll_fM2.root -n .Test.POINT.9.5
fi
if [ $1 -eq 20 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 10.0 -s -1 -d os_mll_fM2.root -n .Test.POINT.10.0
fi
if [ $1 -eq 21 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 10.5 -s -1 -d os_mll_fM2.root -n .Test.POINT.10.5
fi
if [ $1 -eq 22 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 11.0 -s -1 -d os_mll_fM2.root -n .Test.POINT.11.0
fi
if [ $1 -eq 23 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 11.5 -s -1 -d os_mll_fM2.root -n .Test.POINT.11.5
fi
if [ $1 -eq 24 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 12.0 -s -1 -d os_mll_fM2.root -n .Test.POINT.12.0
fi
if [ $1 -eq 25 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 12.5 -s -1 -d os_mll_fM2.root -n .Test.POINT.12.5
fi
if [ $1 -eq 26 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 13.0 -s -1 -d os_mll_fM2.root -n .Test.POINT.13.0
fi
if [ $1 -eq 27 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 13.5 -s -1 -d os_mll_fM2.root -n .Test.POINT.13.5
fi
if [ $1 -eq 28 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 14.0 -s -1 -d os_mll_fM2.root -n .Test.POINT.14.0
fi
if [ $1 -eq 29 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 14.5 -s -1 -d os_mll_fM2.root -n .Test.POINT.14.5
fi
if [ $1 -eq 30 ]; then
  combine --LHCmode LHC-limits --clsAcc 0 -T 500 --saveHybridResult -M HybridNew -m 125 --singlePoint 15.0 -s -1 -d os_mll_fM2.root -n .Test.POINT.15.0
fi