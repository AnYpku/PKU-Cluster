#define xx_cxx
#include "xx.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "L1_weight.C"
#include "ele_channel_scale.C"
#include "muon_channel_scale.C"
#include <TRandom.h>
#include <iostream>
//#include "get_rochester_scale.C"
using namespace std;

void xx::Loop()
{
	//   In a ROOT session, you can do:
	//      Root > .L xx.C
	//      Root > xx t
	//      Root > t.GetEntry(12); // Fill t data members with entry number 12
	//      Root > t.Show();       // Show values of entry 12
	//      Root > t.Show(16);     // Read and show values of entry 16
	//      Root > t.Loop();       // Loop on all entries
	//

	//     This is the loop skeleton where:
	//    jentry is the global entry number in the chain
	//    ientry is the entry number in the current Tree
	//  Note that the argument to GetEntry must be:
	//    jentry for TChain::GetEntry
	//    ientry for TTree::GetEntry and TBranch::GetEntry
	//
	//       To read only selected branches, Insert statements like:
	// METHOD1:
	//    fChain->SetBranchStatus("*",0);  // disable all branches
	//    fChain->SetBranchStatus("branchname",1);  // activate branchname
	// METHOD2: replace line
	//    fChain->GetEntry(jentry);       //read all branches
	//by  b_branchname->GetEntry(ientry); //read only this branch
	if (fChain == 0) return;

	Long64_t nentries = fChain->GetEntriesFast();
        bool LEPmu,LEPele,JET,PHOTON,SignalRegion;
        int cut0=0,cut1=0;

	Long64_t npp = fChain->GetEntries("theWeight>0.");
	Long64_t nmm = fChain->GetEntries("theWeight<0.");
	std::cout<< "numberofnp:" << npp << "  numberofnm:" <<nmm << std::endl;
	TFile * input13 = new TFile ("./pu_calc/puweight.root");
	TH1* h13 = NULL;
	input13->GetObject("h2",h13);

	double lep1_phi_station2_tmp = 0;
	double lep2_phi_station2_tmp = 0;

	// for lep and photon scales
	// muon ID
	TFile * f_BF= TFile::Open("./muon_SFs/ID_eff_BCDEF.root");
	TDirectoryFile* d_ID_BF=(TDirectoryFile*)f_BF->Get("MC_NUM_TightID_DEN_genTracks_PAR_pt_eta");
	TFile * f_GH= TFile::Open("./muon_SFs/ID_eff_GH.root");
	TDirectoryFile* d_ID_GH=(TDirectoryFile*)f_GH->Get("MC_NUM_TightID_DEN_genTracks_PAR_pt_eta");

	TH2F* ID_BF=0;
	TH2F* ID_GH=0;
	d_ID_BF->GetObject("abseta_pt_ratio", ID_BF);
	d_ID_GH->GetObject("abseta_pt_ratio", ID_GH);

	// muon iso
	TFile * f_iso_BF= TFile::Open("./muon_SFs/ISO_eff_BCDEF.root");
	TDirectoryFile* d_ISO_BF=(TDirectoryFile*)f_iso_BF->Get("TightISO_TightID_pt_eta");
	TFile * f_iso_GH= TFile::Open("./muon_SFs/ISO_eff_GH.root");
	TDirectoryFile* d_ISO_GH=(TDirectoryFile*)f_iso_GH->Get("TightISO_TightID_pt_eta");
	TH2F* iso_BF=0;
	TH2F* iso_GH=0;
	d_ISO_BF->GetObject("abseta_pt_ratio", iso_BF);
	d_ISO_GH->GetObject("abseta_pt_ratio", iso_GH);

	// muon track
	TFile* Track_eff = TFile::Open("./muon_SFs/Tracking_EfficienciesAndSF_BCDEFGH.root");
	TGraphAsymmErrors* track_SF=0;
	Track_eff->GetObject("ratio_eff_aeta_dr030e030_corr",track_SF);

	// muon hlt
	TFile* trigger_eff = TFile::Open("./muon_SFs/di_lep_trigger.root");
	TH2D* di_lep_trigger=0;
	trigger_eff->GetObject("2Dh2",di_lep_trigger);

	// ele id
	TFile * f= TFile::Open("./ele_SFs/mediumID_egamma.root");
	TH2F* ID=0;
	f->GetObject("EGamma_SF2D", ID);

	//ele reco
	TFile* Reco_egamma= TFile::Open("./ele_SFs/reco_egamma.root");
	TH2F* Reco=0;
	Reco_egamma->GetObject("EGamma_SF2D", Reco);

	//photon id
	TFile* ID_photon_file = TFile::Open("./ele_SFs/photon_ID_SFs.root");
	TH2F* ID_photon=0;
	ID_photon_file->GetObject("EGamma_SF2D", ID_photon);

	// for lep and photon scales

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		double r1=gRandom->Rndm(jentry);
		double r2=gRandom->Rndm(jentry*2);

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
		lep1_phi_station2_tmp = lep1_phi_station2;
		lep2_phi_station2_tmp = lep2_phi_station2;
		// if (Cut(ientry) < 0) continue;
		if(jentry%100000==0) cout<<" "<<HLT_Ele1<<" "<<HLT_Mu1<<" "<<fabs(theWeight)/theWeight<<" "<<m_dataset<<" "<<jentry<<" "<<nentries<<endl;

		if(m_dataset=="outDMuonB.root"){ scalef=1.0; run_period=1;}
		if(m_dataset=="outDMuonC.root"){ scalef=1.0; run_period=2;}
		if(m_dataset=="outDMuonD.root"){ scalef=1.0; run_period=3;}
		if(m_dataset=="outDMuonE.root"){ scalef=1.0; run_period=4;}
		if(m_dataset=="outDMuonF.root"){ scalef=1.0; run_period=5;}
		if(m_dataset=="outDMuonG.root"){ scalef=1.0; run_period=6;}
		if(m_dataset=="outDMuonH.root"){ scalef=1.0; run_period=7;}

		if(m_dataset=="outDEleB.root"){ scalef=1.0; run_period=1;}
		if(m_dataset=="outDEleC.root"){ scalef=1.0; run_period=2;}
		if(m_dataset=="outDEleD.root"){ scalef=1.0; run_period=3;}
		if(m_dataset=="outDEleE.root"){ scalef=1.0; run_period=4;}
		if(m_dataset=="outDEleF.root"){ scalef=1.0; run_period=5;}
		if(m_dataset=="outDEleG.root"){ scalef=1.0; run_period=6;}
		if(m_dataset=="outDEleH.root"){ scalef=1.0; run_period=7;}

		if(m_dataset=="outWAJ2.root"){ scalef=1000.*405.3/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outWAJ-fxfx.root"){ scalef=1000.*178.6/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outWJets.root"){ scalef=1000.*61526.7/float(npp-nmm)*fabs(theWeight)/theWeight;run_period=8; }
		if(m_dataset=="outZJets.root"){ scalef=1000.*5765.4/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outZJets_FX.root"){ scalef=1000.*5765.4/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outZA.root"){ scalef=1000.*47.46/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="out1.root"){ scalef=1000.*47.46/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outprivate_ZA.root"){ scalef=1000.*47.46/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outofficial_ZA.root"){ scalef=1000.*47.46/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outZA_total.root")){ scalef_tmp=1000.*47.46/float(13442644+9239760-2245300-3263486)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("ZA_sherpa")){ scalef= 1000.*87.39/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outTTA.root"){ scalef=1000.*3.697/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outTTJets.root"){ scalef=1000.*831.76/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outSTs.root"){ scalef=1000.*3.36/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outSTtbarw.root"){ scalef=1000.*35.85/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outSTtw.root"){ scalef=1000.*35.85/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outSTt.root"){ scalef=1000.*136.02/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outSTtbar.root"){ scalef=1000.*80.95/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outWW.root"){ scalef=1000.*118.7/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outWZ.root"){ scalef=1000.*47.13/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outZZ.root"){ scalef=1000.*16.523/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("EWK")){ scalef=1000.*0.1097/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("aQGC")){ scalef=1000.*1.411/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outZA-sig-muonid-correct.root"){ scalef=1000.*0.1097/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}

		if(lep1_phi_station2<0) lep1_phi_station2_tmp = lep1_phi_station2+6.28319;
		if(lep2_phi_station2<0) lep2_phi_station2_tmp = lep2_phi_station2+6.28319;
		l1_weight = L1_weight(lep1_phi_station2_tmp, lep2_phi_station2_tmp, lep1_eta_station2, lep2_eta_station2);
		if(m_dataset !="outDMuonB.root" && m_dataset !="outDMuonC.root" && m_dataset !="outDMuonD.root" && m_dataset !="outDMuonE.root" && m_dataset !="outDMuonF.root" && m_dataset !="outDMuonG.root" && m_dataset !="outDMuonH.root"&&m_dataset !="outDEleB.root" && m_dataset !="outDEleC.root" && m_dataset !="outDEleD.root" && m_dataset !="outDEleE.root" && m_dataset !="outDEleF.root" && m_dataset !="outDEleG.root" && m_dataset !="outDEleH.root" ){	
			pileupWeight=h13->GetBinContent(h13->GetXaxis()->FindBin(npT));
			// cout<<pileupWeight<<endl;
		}
		else {pileupWeight=-1;}
		//////  lep and photon scales
		if(lep==11){
			ele1_id_scale=get_ele_ID(etalep1, ptlep1, ID);
			ele2_id_scale=get_ele_ID(etalep2, ptlep2, ID);
			ele1_reco_scale=get_ele_Reco(etalep1, ptlep1,Reco);
			ele2_reco_scale=get_ele_Reco(etalep2, ptlep2,Reco);
		}
		if(lep==13){
			muon1_id_scale=get_muon_ID(etalep1,ptlep1,ID_BF,ID_GH);
			muon2_id_scale=get_muon_ID(etalep2,ptlep2,ID_BF,ID_GH);
			muon1_iso_scale=get_muon_iso(etalep1,ptlep1,iso_BF,iso_GH);
			muon2_iso_scale=get_muon_iso(etalep2,ptlep2,iso_BF,iso_GH);
			muon1_track_scale=get_muon_track_scale(etalep1,track_SF);
			muon2_track_scale=get_muon_track_scale(etalep2,track_SF);
			muon_hlt_scale=muon_HLT_scale(etalep1,etalep2,di_lep_trigger);
		}

		if(photonet>0) photon_id_scale=get_photon_ID(photoneta,photonet,ID_photon);
		//////  lep and photon scacles
/*
		// for rochester muon correstion
		if(m_dataset.Contains("DEle")) {mu1_rochester_scale=-1e2;mu2_rochester_scale=-1e2;}
		if(m_dataset.Contains("DMuon")) {
			mu1_rochester_scale=get_rochester_scale(true, lep1_sign, ptlep1,etalep1, philep1, muon1_trackerLayers, matchedgenMu1_pt,r1, r2);
			mu2_rochester_scale=get_rochester_scale(true, lep2_sign, ptlep2,etalep2, philep2, muon2_trackerLayers, matchedgenMu2_pt,r1, r2);
		}
		if(!(m_dataset.Contains("DEle")||m_dataset.Contains("DMuon")) && lep==13){
			mu1_rochester_scale=get_rochester_scale(false, lep1_sign, ptlep1,etalep1, philep1, muon1_trackerLayers, matchedgenMu1_pt,r1, r2);
                        mu2_rochester_scale=get_rochester_scale(false, lep2_sign, ptlep2,etalep2, philep2, muon2_trackerLayers, matchedgenMu2_pt,r1, r2);
		}
		if(!(m_dataset.Contains("DEle")||m_dataset.Contains("DMuon")) && lep!=13){mu1_rochester_scale=-1e2;mu2_rochester_scale=-1e2;}
*/
                LEPmu = lep==13 && ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. ;
                LEPele = lep==11 && /* HLT_Ele1>0 &&*/ ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70.;
                SignalRegion= deltaetajj>2.5 && zepp<1.8&&Mjj>500;
                PHOTON= photonet>10 ;
                JET=jet1pt> 10 && jet2pt > 10 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7 ;
                cut0++;
//                if( ! (LEPmu||LEPele) )
//                        continue;

		ExTree->Fill();
	}
	f->Close();
	ID_photon_file->Close();
	Reco_egamma->Close();
	f_BF->Close();
	f_GH->Close();
	f_iso_BF->Close();
	f_iso_GH->Close();
	Track_eff->Close();
	trigger_eff->Close();
	input13->Close();
}
