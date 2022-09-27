#define xx_cxx
//#include "xx.h"
#include "modify_photon_jets.C"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include "TRandom.h"

void xx::Loop()
{
	if (fChain == 0) return;

	Long64_t nentries = fChain->GetEntries();

        Long64_t npp = fChain->GetEntries("theWeight>0.");
        Long64_t nmm = fChain->GetEntries("theWeight<0.");
        std::cout<< "numberofnp:" << npp << "  numberofnm:" <<nmm << std::endl;

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		if(jentry%100000==0) cout<<" "<<HLT_Ele1<<" "<<HLT_Mu2<<" "<<fabs(theWeight)/theWeight<<" "<<m_dataset<<" "<<jentry<<" "<<nentries<<endl;
		modify_photon_jets();
		
		if(isprompt!=1) continue;

		ExTree->Fill();
	}
}
void xx::Set(){
	photon_veto_scale=1;
	ele1_id_scale=1;
	ele2_id_scale=1;
	ele1_reco_scale=1;
	ele2_reco_scale=1;
	muon1_id_scale=1;
	muon2_id_scale=1;
	muon1_iso_scale=1;
	muon2_iso_scale=1;
	muon_hlt_scale=1;
}
