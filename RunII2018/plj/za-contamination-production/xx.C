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

        Long64_t npp = fChain->GetEntries("theWeight>0.");
        Long64_t nmm = fChain->GetEntries("theWeight<0.");
        std::cout<< "numberofnp:" << npp << "  numberofnm:" <<nmm << std::endl;
    /*    TFile * input13 = new TFile ("./puweight.root");//puweight.root
        TH1D* h13 = NULL;
        input13->GetObject("h2",h13);
        cout<<"open the file: puweight.root"<<endl;*/

        double lep1_phi_station2_tmp = 0;
        double lep2_phi_station2_tmp = 0;

        // for lep and photon scales
        // muon ID
/*        TFile * f_BF= TFile::Open("./muon_SFs/RunBCDEF_SF_ID.root");
        TH2D* ID_BF=0;
        f_BF->GetObject("NUM_TightID_DEN_genTracks_pt_abseta", ID_BF);
        cout<<"open the muon ID file: RunBCDEF_SF_ID.root"<<endl;

        // muon iso
        TFile * f_iso_BF= TFile::Open("./muon_SFs/RunBCDEF_SF_ISO.root");
        TH2D* iso_BF=0;
        f_iso_BF->GetObject("NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta", iso_BF);
        cout<<"open the muon ISO file: RunBCDEF_SF_ISO.root"<<endl;
        // muon track
        TFile* Track_eff = TFile::Open("./muon_SFs/EfficienciesAndSF_RunBtoF_Nov17Nov2017.root");
        TH1F* track_SF=0;
        TDirectoryFile* d_eff =(TDirectoryFile*)Track_eff->Get("IsoMu27_EtaBins");
        d_eff->GetObject("eta_ratio",track_SF);
        cout<<"open the muon track file: EfficienciesAndSF_RunBtoF_Nov17Nov2017.root"<<endl;

        // muon hlt
        TFile* trigger_eff = TFile::Open("./muon_SFs/di_lep_eff.root");
        TH2D* di_lep_trigger=0;
        trigger_eff->GetObject("h2",di_lep_trigger);
        cout<<"open the muon hlt file: di_lep_eff.root"<<endl;
        // ele id
        TFile * f= TFile::Open("./ele_SFs/2017_ElectronMedium.root");
        TH2F* ID=0;
        f->GetObject("EGamma_SF2D", ID);
        cout<<"open the ele ID file: 2017_ElectronMedium.root"<<endl;

        //ele reco
        TFile* Reco_egamma= TFile::Open("./ele_SFs/egammaEffi.txt_EGM2D.root");
        TH2F* Reco=0;
        Reco_egamma->GetObject("EGamma_SF2D", Reco);
        cout<<"open the ele RECO file: egammaEffi.txt_EGM2D.root"<<endl;

        //photon id
        TFile* ID_photon_file = TFile::Open("./ele_SFs/2017_PhotonsMedium.root");
        TH2F* ID_photon=0;
        ID_photon_file->GetObject("EGamma_SF2D", ID_photon);
        cout<<"open the photon ID file: 2017_PhotonsMedium.root"<<endl;
*/        // for lep and photon scales


	Long64_t nbytes = 0, nb = 0;
//        nentries =10000;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
//		double r1=gRandom->Rndm(jentry);
//		double r2=gRandom->Rndm(jentry*2);

		// set lep and photon scale to -1 for default
		ele1_id_scale=-1;
		ele2_id_scale=-1;
		ele1_reco_scale=-1;
		ele2_reco_scale=-1;
		muon1_id_scale=-1;
		muon2_id_scale=-1;
		muon1_iso_scale=-1;
		muon2_iso_scale=-1;
		muon1_track_scale=-1;
		muon2_track_scale=-1;
		muon_hlt_scale=-1;
		photon_id_scale=-1;

		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		if(jentry%100000==0) cout<<" "<<HLT_Ele2<<" "<<HLT_Mu2<<" "<<fabs(theWeight)/theWeight<<" "<<m_dataset<<" "<<jentry<<" "<<nentries<<endl;
		modify_photon_jets();
		lep1_phi_station2_tmp = lep1_phi_station2;
		lep2_phi_station2_tmp = lep2_phi_station2;
		// if (Cut(ientry) < 0) continue;

//		if(m_dataset.Contains("plj")==1){ scalef=1.0; run_period=6;}

		if(lep1_phi_station2<0) lep1_phi_station2_tmp = lep1_phi_station2+6.28319;
		if(lep2_phi_station2<0) lep2_phi_station2_tmp = lep2_phi_station2+6.28319;
		l1_weight = L1_weight(lep1_phi_station2_tmp, lep2_phi_station2_tmp, lep1_eta_station2, lep2_eta_station2);
		pileupWeight=1;
		
		/*if(lep==11){
			ele1_id_scale=get_ele_ID(etalep1, ptlep1, ID);
			ele2_id_scale=get_ele_ID(etalep2, ptlep2, ID);
			ele1_reco_scale=get_ele_Reco(etalep1, ptlep1,Reco);
			ele2_reco_scale=get_ele_Reco(etalep2, ptlep2,Reco);
		}
		if(lep==13){
                        muon1_id_scale=get_muon_ID(etalep1,ptlep1,ID_BF);
                        muon2_id_scale=get_muon_ID(etalep2,ptlep2,ID_BF);
                        muon1_iso_scale=get_muon_iso(etalep1,ptlep1,iso_BF);
                        muon2_iso_scale=get_muon_iso(etalep2,ptlep2,iso_BF);
                        muon1_track_scale=get_muon_track_scale(etalep1,track_SF);
                        muon2_track_scale=get_muon_track_scale(etalep2,track_SF);
                        muon_hlt_scale=muon_HLT_scale(ptlep1,ptlep2,di_lep_trigger);
		}

		if(photonet>0) photon_id_scale=get_photon_ID(photoneta,photonet,ID_photon);*/
                Set();
		if(isprompt!=1)
			continue;

		newtree->Fill();
	}
/*	f->Close();
	ID_photon_file->Close();
	Reco_egamma->Close();
	f_BF->Close();
	f_iso_BF->Close();
	Track_eff->Close();
	trigger_eff->Close();
	input13->Close();*/
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
