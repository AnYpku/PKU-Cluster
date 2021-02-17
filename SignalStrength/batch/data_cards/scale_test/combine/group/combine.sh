#!/bin/bash/

#cp ../full* ./
files="\
full16_test.root
full17_test.root
full18_test.root
full_RunII.root
"
for rootfile in $files
do
      name=`echo $rootfile | awk -F. '{print $1}'` 
      sed 's/lnN.*$//' ${name}.txt >tmp1 #replace the content from lnN to the end of the line with none
      sed  's/\s\+$//g' tmp1 >tmp #delete extra space
      num=`sed -n -e '/rate/=' tmp` # print the line number
      line=$[$num+1]
      echo "$line" 
      sed -i "1,$line d" tmp # delete line from 1 to line
      theory=`sed -n -e '/theory/p' tmp` # print the line number
      sed -i '/group/d' tmp  # delete lines with group
      sed -i '/ST_Stat_control_bin1_eleendcap/d' tmp # delete lines with ST_Stat_control_bin1_eleendcap
      echo "$theory" 
      sed -i ':label;N;s/\n/,/;t label' tmp # replace \n to ,
      mv tmp freeze_${name}.txt
      NP=`cat freeze_${name}.txt`

#     combine -M MultiDimFit --algo grid --points 50 --rMin 0.2 --rMax 4 -m 125 -n nominal_${name} ${name}.root --expectSignal=1 -t -1 
#     combine -M MultiDimFit --algo none --rMin 0.2 --rMax 4 -m 125 -n bestfit_${name} --saveWorkspace ${name}.root --expectSignal=1  -t -1
#     combine -M MultiDimFit --algo grid --points 50 --rMin 0.2 --rMax 4 -m 125 -n stat_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeParameters $NP --expectSignal=1 -t -1
#    plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root \
#    --others "higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:2" \
#    --breakdown syst,stat -o scan_${name}
    if [[ -f tmp ]] || [[ -f tmp1 ]]; then
        rm tmp1
        rm tmp
    fi
    group=("theory" "JESR" "Stat" "fake" "muon" "egamma" "pref" "pu" "pileupId" "luminosity")
    echo "$name"
    for (( i = 0 ; i < ${#group[@]} ; i++  ))    
    do
         if [[ ${name} =~ "16" ]] && [[ ${group[${i}]} =~ "pileupId" ]]; then
             continue; 
         fi
         if [[ ${name} =~ "18" ]] && [[ ${group[${i}]} =~ "pileupId" ]]; then
             continue; 
         fi
         if [[ ${name} =~ "18" ]] && [[ ${group[${i}]} =~ "pref" ]]; then
             continue; 
         fi
         echo "${group[${i}]}" >> tmp
	 sed -i ':label;N;s/\n/_/;t label' tmp
         name_np=`cat tmp`
         echo "${name_np}"
         echo "${group[${i}]}" >> tmp1
	 sed -i ':label;N;s/\n/,/;t label' tmp1
         freeze_np=`cat tmp1`
         echo "${freeze_np}"
	 combine -M MultiDimFit --algo grid --points 50  --rMin 0.2 --rMax 4 -m 125 -n ${group}_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeNuisanceGroups ${group} --expectSignal=1 -t -1
	 echo "combine -M MultiDimFit --algo grid --points 50  --rMin 0.2 --rMax 4 -m 125 -n ${group}_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeNuisanceGroups ${group} --expectSignal=1 -t -1"

	 plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root \
		 --others "higgsCombine${group}_${name}.MultiDimFit.mH125.root:Freeze ${group}:2" \
		 --breakdown ${group},left -o scan_${group}_${name}

	done
#	if [[ ${name} =~ "16" ]]; then
#	      plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root --others \
#	      "higgsCombinetheory_${name}.MultiDimFit.mH125.root:Freeze theory:1" \
#	      "higgsCombinetheory_JESR_${name}.MultiDimFit.mH125.root:Freeze JESR:2" \
#	      "higgsCombinetheory_JESR_Stat_${name}.MultiDimFit.mH125.root:Freeze MCStat:3" \
#	      "higgsCombinetheory_JESR_Stat_fake_${name}.MultiDimFit.mH125.root:Freeze fake:4" \
#	      "higgsCombinetheory_JESR_Stat_fake_muon_${name}.MultiDimFit.mH125.root:Freeze muon:5" \
#	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_${name}.MultiDimFit.mH125.root:Freeze egamma:6" \
#	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pref_${name}.MultiDimFit.mH125.root:Freeze pref:7" \
#	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pref_pu_${name}.MultiDimFit.mH125.root:Freeze pileup:8" \
#	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pref_pu_luminosity_${name}.MultiDimFit.mH125.root:Freeze lumi:9" \
#	      "higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:11" \
#	      --breakdown theory,JESR,MCStat,fake,muon,egamma,pref,pileup,lumi,others,stat -o scan_freeze_test_${name}
#	fi
#	if [[ ${name} =~ "17" ]]; then
#	      plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root --others \
#	      "higgsCombinetheory_${name}.MultiDimFit.mH125.root:Freeze theory:1" \
#	      "higgsCombinetheory_JESR_${name}.MultiDimFit.mH125.root:Freeze JESR:2" \
#	      "higgsCombinetheory_JESR_Stat_${name}.MultiDimFit.mH125.root:Freeze MCStat:3" \
#	      "higgsCombinetheory_JESR_Stat_fake_${name}.MultiDimFit.mH125.root:Freeze fake:4" \
#	      "higgsCombinetheory_JESR_Stat_fake_muon_${name}.MultiDimFit.mH125.root:Freeze muon:5" \
#	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_${name}.MultiDimFit.mH125.root:Freeze egamma:6" \
#	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pref_${name}.MultiDimFit.mH125.root:Freeze pref:7" \
#	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pref_pu_${name}.MultiDimFit.mH125.root:Freeze pu:8" \
#	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pref_pu_pileupId_${name}.MultiDimFit.mH125.root:Freeze pileupId:9" \
#	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pref_pu_pileupId_luminosity_${name}.MultiDimFit.mH125.root:Freeze lumi:11" \
#	      "higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:12" \
#	      --breakdown theory,JESR,MCStat,fake,muon,egamma,pref,pileup,pileupId,lumi,others,stat -o scan_freeze_test_${name}
#	fi
#	if [[ ${name} =~ "18" ]]; then
#	      plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root --others \
#	      "higgsCombinetheory_${name}.MultiDimFit.mH125.root:Freeze theory:1" \
#	      "higgsCombinetheory_JESR_${name}.MultiDimFit.mH125.root:Freeze JESR:2" \
#	      "higgsCombinetheory_JESR_Stat_${name}.MultiDimFit.mH125.root:Freeze Stat:3" \
#	      "higgsCombinetheory_JESR_Stat_fake_${name}.MultiDimFit.mH125.root:Freeze fake:4" \
#	      "higgsCombinetheory_JESR_Stat_fake_muon_${name}.MultiDimFit.mH125.root:Freeze muon:5" \
#	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_${name}.MultiDimFit.mH125.root:Freeze egamma:6" \
#	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pu_${name}.MultiDimFit.mH125.root:Freeze pileup:7" \
#	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pu_luminosity_${name}.MultiDimFit.mH125.root:Freeze lumi:8" \
#	      "higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:9" \
#	      --breakdown theory,JESR,MCStat,fake,muon,egamma,pileup,lumi,others,stat -o scan_freeze_test_${name}
#	fi
#	if [[ ${name} =~ "RunII" ]]; then
#	      plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root --others \
#	      "higgsCombinetheory_${name}.MultiDimFit.mH125.root:Freeze theory:1" \
#	      "higgsCombinetheory_JESR_${name}.MultiDimFit.mH125.root:Freeze JESR:2" \
#	      "higgsCombinetheory_JESR_Stat_${name}.MultiDimFit.mH125.root:Freeze Stat:3" \
#	      "higgsCombinetheory_JESR_Stat_fake_${name}.MultiDimFit.mH125.root:Freeze fake:4" \
#	      "higgsCombinetheory_JESR_Stat_fake_muon_${name}.MultiDimFit.mH125.root:Freeze muon:5" \
#	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_${name}.MultiDimFit.mH125.root:Freeze egamma:6" \
#	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pref_${name}.MultiDimFit.mH125.root:Freeze pref:7" \
#	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pref_pu_${name}.MultiDimFit.mH125.root:Freeze pileup:8" \
#	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pref_pu_pileupId_${name}.MultiDimFit.mH125.root:Freeze pileupId:9" \
#	      "higgsCombinetheory_JESR_Stat_fake_muon_egamma_pref_pu_pileupId_luminosity_${name}.MultiDimFit.mH125.root:Freeze lumi:11" \
#	      "higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:12" \
#	      --breakdown theory,JESR,MCStat,fake,muon,egamma,pref,pileup,pileupId,lumi,others,stat -o scan_freeze_test_${name}
#	fi
	done
