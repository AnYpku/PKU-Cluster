#define xx_cxx
//#include "xx.h"
#include "modify_photon_jets.C"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "L1_weight.C"
#include "ele_channel_scale.C"
#include "muon_channel_scale.C"
#include <iostream>
#include "TRandom.h"

void xx::Loop()
{
	if (fChain == 0) return;

	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;
        Long64_t npp = fChain->GetEntries("theWeight>0.");
        Long64_t nmm = fChain->GetEntries("theWeight<0.");
        std::cout<< "numberofnp:" << npp << "  numberofnm:" <<nmm << std::endl;

        double lep1_phi_station2_tmp = 0;
        double lep2_phi_station2_tmp = 0;

	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);
		if(jentry%100000==0) cout<<" "<<HLT_Ele2<<" "<<HLT_Mu2<<" "<<fabs(theWeight)/theWeight<<" "<<m_dataset<<" "<<jentry<<" "<<nentries<<endl;
		modify_photon_jets();
		lep1_phi_station2_tmp = lep1_phi_station2;
		lep2_phi_station2_tmp = lep2_phi_station2;
		// if (Cut(ientry) < 0) continue;

		if(m_dataset.Contains("plj")==1){ scalef=1.0; run_period=6;}

		if(lep1_phi_station2<0) lep1_phi_station2_tmp = lep1_phi_station2+6.28319;
		if(lep2_phi_station2<0) lep2_phi_station2_tmp = lep2_phi_station2+6.28319;
		l1_weight = L1_weight(lep1_phi_station2_tmp, lep2_phi_station2_tmp, lep1_eta_station2, lep2_eta_station2);
		pileupWeight=1;
                Set();

		newtree->Fill();
	}
}
void xx::Set(){

	ele1_id_scale=1;
	ele2_id_scale=1;
	ele1_reco_scale=1;
	ele2_reco_scale=1;
	muon1_id_scale=1;
	muon2_id_scale=1;
	muon1_iso_scale=1;
	muon2_iso_scale=1;
	muon1_track_scale=1;
	muon2_track_scale=1;
	muon_hlt_scale=1;
    }
