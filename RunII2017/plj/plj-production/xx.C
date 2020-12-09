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

	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;
        Long64_t npp = fChain->GetEntries("theWeight>0.");
        Long64_t nmm = fChain->GetEntries("theWeight<0.");
        std::cout<< "numberofnp:" << npp << "  numberofnm:" <<nmm << std::endl;
         
        Bool_t LEPmu=0,LEPele=0,PHOTON=0;

	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);
		if(jentry%100000==0) cout<<" "<<HLT_Ele2<<" "<<HLT_Mu2<<" "<<fabs(theWeight)/theWeight<<" "<<m_dataset<<" "<<jentry<<" "<<nentries<<endl;
		modify_photon_jets();
		// if (Cut(ientry) < 0) continue;
		if(m_dataset.Contains("plj")==1){ scalef=1.0; run_period=6;}
		pileupWeight=1;
                Set();
                LEPmu = lep==13 && (HLT_Mu1>0||HLT_Mu2>0||HLT_Mu3>0) && ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110 ;
                LEPele = lep==11 && (HLT_Ele1>0||HLT_Ele2>0) && ptlep1 > 25. && ptlep2 > 25 && fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70.&& massVlep<110;
		PHOTON=photonet>20 &&  ( fabs(photoneta)<1.4442 || ( fabs(photoneta)<2.5 && fabs(photoneta)>1.566) );
                if( !( (LEPmu||LEPele) && PHOTON ) )
                    continue;
		ExTree->Fill();
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
	muon_hlt_scale=1;
	photon_id_scale=1;
	photon_veto_scale=1;
	ele_hlt_scale=1;
	scalef=1;
	puIdweight_L=1;
	puIdweight_M=1;
	puIdweight_T=1;
    }
