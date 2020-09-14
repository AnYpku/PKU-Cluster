#!/bin/bash
wget https://melu.web.cern.ch/melu/combine_8TeV_13TeV/13TeV/ele_barrel_control.txt
wget https://melu.web.cern.ch/melu/combine_8TeV_13TeV/13TeV/ele_endcap_control.txt
wget https://melu.web.cern.ch/melu/combine_8TeV_13TeV/13TeV/muon_barrel_control.txt
wget https://melu.web.cern.ch/melu/combine_8TeV_13TeV/13TeV/muon_endcap_control.txt
for((i=1;i<=8;i++));
do 
wget https://melu.web.cern.ch/melu/combine_8TeV_13TeV/13TeV/ele_endcap_bin_$i.txt
wget https://melu.web.cern.ch/melu/combine_8TeV_13TeV/13TeV/ele_barrel_bin_$i.txt
wget https://melu.web.cern.ch/melu/combine_8TeV_13TeV/13TeV/muon_endcap_bin_$i.txt
wget https://melu.web.cern.ch/melu/combine_8TeV_13TeV/13TeV/muon_barrel_bin_$i.txt
done

