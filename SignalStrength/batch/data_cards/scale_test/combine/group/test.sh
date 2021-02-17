#!/bin/bash/

#cp ../full* ./
files="\
full16_test.root
"
#full17_test.root
#full18_test.root
#full_RunII.root
for rootfile in $files
do
     name=`echo $rootfile | awk -F. '{print $1}'` 
#     combine -M MultiDimFit --algo grid --points 50 --rMin 0.2 --rMax 4 -m 125 -n nominal_${name} ${name}.root --expectSignal=1 -t -1 
#     combine -M MultiDimFit --algo none --rMin 0.2 --rMax 4 -m 125 -n bestfit_${name} --saveWorkspace ${name}.root --expectSignal=1  -t -1
#     combine -M MultiDimFit --algo grid --points 50 --rMin 0.2 --rMax 4 -m 125 -n stat_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeParameters $NP --expectSignal=1 -t -1
#    plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root \
#    --others "higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:2" \
#    --breakdown syst,stat -o scan_${name}
#    if [[ -f tmp ]]; then
#        rm tmp1
#        rm tmp
#    fi
#    group=("theory" "JESR" "Stat" "fake" "muon" "egamma" "pref" "pu" "pileupId" "luminosity")
#    echo "$name"
#    for (( i = 0 ; i < ${#group[@]} ; i++  ))    
#    do
#         if [[ ${name} =~ "16" ]] && [[ ${group[${i}]} =~ "pileupId" ]]; then
#             continue; 
#         fi
#         if [[ ${name} =~ "18" ]] && [[ ${group[${i}]} =~ "pileupId" ]]; then
#             continue; 
#         fi
#         if [[ ${name} =~ "18" ]] && [[ ${group[${i}]} =~ "pref" ]]; then
#             continue; 
#         fi
#         echo "${group[${i}]}" >> tmp
#	 sed -i ':label;N;s/\n/_/;t label' tmp
#         name_np=`cat tmp`
#         echo "${name_np}"
#         echo "${group[${i}]}" >> tmp1
#	 sed -i ':label;N;s/\n/,/;t label' tmp1
#         freeze_np=`cat tmp1`
#         echo "${freeze_np}"
#	 combine -M MultiDimFit --algo grid --points 50  --rMin 0.2 --rMax 4 -m 125 -n ${name_np}_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeNuisanceGroups ${freeze_np} --expectSignal=1 -t -1
#	 echo "combine -M MultiDimFit --algo grid --points 50  --rMin 0.2 --rMax 4 -m 125 -n ${name_np}_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeNuisanceGroups ${freeze_np} --expectSignal=1 -t -1"
#
#	 plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root \
#		 --others "higgsCombine${name_np}_${name}.MultiDimFit.mH125.root:Freeze ${name_np}:2" \
#		 --breakdown ${name_np},left -o scan_${group[${i}]}_${name}
#
#	done
	if [[ ${name} =~ "16" ]]; then
	      plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root --others \
	      "higgsCombinetheory_${name}.MultiDimFit.mH125.root:Freeze theory:1" \
	      "higgsCombinetheory_JESR_${name}.MultiDimFit.mH125.root:Freeze JESR:2" \
	      "higgsCombinetheory_JESR_Stat_${name}.MultiDimFit.mH125.root:Freeze Stat:3" \
	      "higgsCombinetheory_JESR_Stat_fake_${name}.MultiDimFit.mH125.root:Freeze fake:4" \
	      "higgsCombinetheory_JESR_Stat_fake_muon_${name}.MultiDimFit.mH125.root:Freeze muon:5" \
	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_${name}.MultiDimFit.mH125.root:Freeze egamma:6" \
	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pref_${name}.MultiDimFit.mH125.root:Freeze pref:7" \
	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pref_pu_${name}.MultiDimFit.mH125.root:Freeze pu:8" \
	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pref_pu_luminosity_${name}.MultiDimFit.mH125.root:Freeze luminosity:9" \
	      "higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:10" \
	      --breakdown theory,JESR,MCStat,fake,muon,egamma,pref,pileup,lumi,syst,stat -o scan_freeze_test_${name}
	fi
	if [[ ${name} =~ "17" ]]; then
	      plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root --others \
	      "higgsCombinetheory_${name}.MultiDimFit.mH125.root:Freeze theory:1" \
	      "higgsCombinetheory_JESR_${name}.MultiDimFit.mH125.root:Freeze JESR:2" \
	      "higgsCombinetheory_JESR_Stat_${name}.MultiDimFit.mH125.root:Freeze Stat:3" \
	      "higgsCombinetheory_JESR_Stat_fake_${name}.MultiDimFit.mH125.root:Freeze fake:4" \
	      "higgsCombinetheory_JESR_Stat_fake_muon_${name}.MultiDimFit.mH125.root:Freeze muon:5" \
	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_${name}.MultiDimFit.mH125.root:Freeze egamma:6" \
	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pref_${name}.MultiDimFit.mH125.root:Freeze pref:7" \
	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pref_pu_${name}.MultiDimFit.mH125.root:Freeze pu:8" \
	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pref_pu_pileupId_${name}.MultiDimFit.mH125.root:Freeze pileupId:9" \
	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pref_pu_pileupId_luminosity_${name}.MultiDimFit.mH125.root:Freeze luminosity:10" \
	      "higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:11" \
	      --breakdown theory,JESR,MCStat,fake,muon,egamma,pref,pileup,pileupId,lumi,syst,stat -o scan_freeze_test_${name}
	fi
	if [[ ${name} =~ "18" ]]; then
	      plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root --others \
	      "higgsCombinetheory_${name}.MultiDimFit.mH125.root:Freeze theory:1" \
	      "higgsCombinetheory_JESR_${name}.MultiDimFit.mH125.root:Freeze JESR:2" \
	      "higgsCombinetheory_JESR_Stat_${name}.MultiDimFit.mH125.root:Freeze Stat:3" \
	      "higgsCombinetheory_JESR_Stat_fake_${name}.MultiDimFit.mH125.root:Freeze fake:4" \
	      "higgsCombinetheory_JESR_Stat_fake_muon_${name}.MultiDimFit.mH125.root:Freeze muon:5" \
	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_${name}.MultiDimFit.mH125.root:Freeze egamma:6" \
	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pu_${name}.MultiDimFit.mH125.root:Freeze pu:7" \
	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pu_luminosity_${name}.MultiDimFit.mH125.root:Freeze luminosity:8" \
	      "higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:9" \
	      --breakdown theory,JESR,MCStat,fake,muon,egamma,pileup,lumi,syst,stat -o scan_freeze_test_${name}
	fi
	if [[ ${name} =~ "RunII" ]]; then
	      plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root --others \
	      "higgsCombinetheory_${name}.MultiDimFit.mH125.root:Freeze theory:1" \
	      "higgsCombinetheory_JESR_${name}.MultiDimFit.mH125.root:Freeze JESR:2" \
	      "higgsCombinetheory_JESR_Stat_${name}.MultiDimFit.mH125.root:Freeze Stat:3" \
	      "higgsCombinetheory_JESR_Stat_fake_${name}.MultiDimFit.mH125.root:Freeze fake:4" \
	      "higgsCombinetheory_JESR_Stat_fake_muon_${name}.MultiDimFit.mH125.root:Freeze muon:5" \
	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_${name}.MultiDimFit.mH125.root:Freeze egamma:6" \
	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pref_${name}.MultiDimFit.mH125.root:Freeze pref:7" \
	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pref_pu_${name}.MultiDimFit.mH125.root:Freeze pu:8" \
	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pref_pu_pileupId_${name}.MultiDimFit.mH125.root:Freeze pileupId:9" \
	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pref_pu_pileupId_luminosity_${name}.MultiDimFit.mH125.root:Freeze luminosity:10" \
	      "higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:11" \
	      --breakdown theory,JESR,MCStat,fake,muon,egamma,pref,pileup,pileupId,lumi,syst,stat -o scan_freeze_test_${name}
	fi
	done
