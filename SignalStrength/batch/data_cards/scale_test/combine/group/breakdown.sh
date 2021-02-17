#!/bin/bash/

#cp ../full* ./
#full16_test.root
files="\
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

     combine -M MultiDimFit --algo grid --points 50 --rMin 0.4 --rMax 2 -m 125 -n nominal_${name} ${name}.root --expectSignal=1 -t -1 
     combine -M MultiDimFit --algo none --rMin 0.4 --rMax 4 -m 125 -n bestfit_${name} --saveWorkspace ${name}.root --expectSignal=1  -t -1
#     combine -M MultiDimFit --algo grid --points 50 --rMin 0.4 --rMax 2 -m 125 -n stat_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeParameters $NP --expectSignal=1 -t -1
#    plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root \
#    --others "higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:2" \
#    --breakdown syst,stat -o scan_${name}
    if [[ -f tmp ]] || [[ -f tmp1 ]]; then
        rm tmp1
        rm tmp
    fi
    group=("MCStat" "theory" "JESR" "luminosity" "pu" "fake" "muon" "egamma" "pref" "pileupId" )
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
	 combine -M MultiDimFit --algo grid --points 50  --rMin 0.4 --rMax 2 -m 125 -n ${name_np}_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeNuisanceGroups ${freeze_np} --expectSignal=1 -t -1
	 echo "combine -M MultiDimFit --algo grid --points 50  --rMin 0.4 --rMax 2 -m 125 -n ${name_np}_${name} higgsCombinebestfit_${name}.MultiDimFit.mH125.root --snapshotName MultiDimFit --freezeNuisanceGroups ${freeze_np} --expectSignal=1 -t -1"

#	 plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root \
#		 --others "higgsCombine${name_np}_${name}.MultiDimFit.mH125.root:Freeze ${name_np}:2" \
#		 --breakdown ${name_np},left -o scan_${name_np}_${name}

	done
	if [[ ${name} =~ "16" ]]; then
	      plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root --others \
	      "higgsCombinefake_${name}.MultiDimFit.mH125.root:Freeze fake:1" \
	      "higgsCombinefake_muon_${name}.MultiDimFit.mH125.root:Freeze muon:2" \
	      "higgsCombinefake_muon_egamma_${name}.MultiDimFit.mH125.root:Freeze egamma:3" \
	      "higgsCombinefake_muon_egamma_pu_${name}.MultiDimFit.mH125.root:Freeze pileup:4" \
	      "higgsCombinefake_muon_egamma_pu_luminosity_${name}.MultiDimFit.mH125.root:Freeze lumi:5" \
	      "higgsCombinefake_muon_egamma_pu_luminosity_Stat_${name}.MultiDimFit.mH125.root:Freeze MCStat:6" \
	      "higgsCombinefake_muon_egamma_pu_luminosity_Stat_theory_${name}.MultiDimFit.mH125.root:Freeze theory:7" \
	      "higgsCombinefake_muon_egamma_pu_luminosity_Stat_theory_JESR_${name}.MultiDimFit.mH125.root:Freeze JESR:8" \
	      "higgsCombinefake_muon_egamma_pu_luminosity_Stat_theory_JESR_pref_${name}.MultiDimFit.mH125.root:Freeze pref:9" \
	      "higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:11" \
	      --breakdown fake,muon,egamma,pu,lumi,MCStat,theory,JESR,pref,others,stat -o scan_freeze_test_${name}
	fi
	if [[ ${name} =~ "17" ]]; then
	      plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root --others \
	      "higgsCombinefake_${name}.MultiDimFit.mH125.root:Freeze fake:1" \
	      "higgsCombinefake_muon_${name}.MultiDimFit.mH125.root:Freeze muon:2" \
	      "higgsCombinefake_muon_egamma_${name}.MultiDimFit.mH125.root:Freeze egamma:3" \
	      "higgsCombinefake_muon_egamma_pu_${name}.MultiDimFit.mH125.root:Freeze pileup:4" \
	      "higgsCombinefake_muon_egamma_pu_luminosity_${name}.MultiDimFit.mH125.root:Freeze lumi:5" \
	      "higgsCombinefake_muon_egamma_pu_luminosity_Stat_${name}.MultiDimFit.mH125.root:Freeze MCStat:6" \
	      "higgsCombinefake_muon_egamma_pu_luminosity_Stat_theory_${name}.MultiDimFit.mH125.root:Freeze theory:7" \
	      "higgsCombinefake_muon_egamma_pu_luminosity_Stat_theory_JESR_${name}.MultiDimFit.mH125.root:Freeze JESR:8" \
	      "higgsCombinefake_muon_egamma_pu_luminosity_Stat_theory_JESR_pref_${name}.MultiDimFit.mH125.root:Freeze pref:9" \
	      "higgsCombinefake_muon_egamma_pu_luminosity_Stat_theory_JESR_pref_pileupId_${name}.MultiDimFit.mH125.root:Freeze pref:11" \
	      "higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:12" \
	      --breakdown fake,muon,egamma,pu,lumi,MCStat,theory,JESR,pref,pileupId,others,stat -o scan_freeze_test_${name}
	fi
	if [[ ${name} =~ "18" ]]; then
	      plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root --others \
	      "higgsCombinefake_${name}.MultiDimFit.mH125.root:Freeze fake:1" \
	      "higgsCombinefake_muon_${name}.MultiDimFit.mH125.root:Freeze muon:2" \
	      "higgsCombinefake_muon_egamma_${name}.MultiDimFit.mH125.root:Freeze egamma:3" \
	      "higgsCombinefake_muon_egamma_pu_${name}.MultiDimFit.mH125.root:Freeze pileup:4" \
	      "higgsCombinefake_muon_egamma_pu_luminosity_${name}.MultiDimFit.mH125.root:Freeze lumi:5" \
	      "higgsCombinefake_muon_egamma_pu_luminosity_Stat_${name}.MultiDimFit.mH125.root:Freeze MCStat:6" \
	      "higgsCombinefake_muon_egamma_pu_luminosity_Stat_theory_${name}.MultiDimFit.mH125.root:Freeze theory:7" \
	      "higgsCombinefake_muon_egamma_pu_luminosity_Stat_theory_JESR_${name}.MultiDimFit.mH125.root:Freeze JESR:8" \
	      "higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:11" \
	      --breakdown fake,muon,egamma,pu,lumi,MCStat,theory,JESR,others,stat -o scan_freeze_test_${name}
	fi
	if [[ ${name} =~ "RunII" ]]; then
	      plot1DScan.py higgsCombinenominal_${name}.MultiDimFit.mH125.root --others \
	      "higgsCombinefake_${name}.MultiDimFit.mH125.root:Freeze fake:1" \
	      "higgsCombinefake_muon_${name}.MultiDimFit.mH125.root:Freeze muon:2" \
	      "higgsCombinefake_muon_egamma_${name}.MultiDimFit.mH125.root:Freeze egamma:3" \
	      "higgsCombinefake_muon_egamma_pu_${name}.MultiDimFit.mH125.root:Freeze pileup:4" \
	      "higgsCombinefake_muon_egamma_pu_luminosity_${name}.MultiDimFit.mH125.root:Freeze lumi:5" \
	      "higgsCombinefake_muon_egamma_pu_luminosity_Stat_${name}.MultiDimFit.mH125.root:Freeze MCStat:6" \
	      "higgsCombinefake_muon_egamma_pu_luminosity_Stat_theory_${name}.MultiDimFit.mH125.root:Freeze theory:7" \
	      "higgsCombinefake_muon_egamma_pu_luminosity_Stat_theory_JESR_${name}.MultiDimFit.mH125.root:Freeze JESR:8" \
	      "higgsCombinefake_muon_egamma_pu_luminosity_Stat_theory_JESR_pref_${name}.MultiDimFit.mH125.root:Freeze pref:9" \
	      "higgsCombinefake_muon_egamma_pu_luminosity_Stat_theory_JESR_pref_pileupId_${name}.MultiDimFit.mH125.root:Freeze pref:11" \
	      "higgsCombinestat_${name}.MultiDimFit.mH125.root:Freeze all:12" \
	      --breakdown fake,muon,egamma,pu,lumi,MCStat,theory,JESR,pref,pileupId,others,stat -o scan_freeze_test_${name}
	fi
	done
