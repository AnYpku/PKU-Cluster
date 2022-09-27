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
	TFile * input13 = new TFile ("./puweight.root");//puweight.root
	TH1D* h13 = NULL;
	input13->GetObject("h2",h13);
        cout<<"open the file: puweight.root"<<endl;

	double lep1_phi_station2_tmp = 0;
	double lep2_phi_station2_tmp = 0;

	// for lep and photon scales
	// muon ID
	TFile * f_BF= TFile::Open("./muon_SFs/RunBCDEF_SF_ID.root");
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
		if(jentry%100000==0) cout<<" "<<HLT_Ele1<<" "<<HLT_Mu2<<" "<<fabs(theWeight)/theWeight<<" "<<m_dataset<<" "<<jentry<<" "<<nentries<<endl;

		if(m_dataset.Contains("outDMuonB.root")){ scalef=1.0; run_period=1;}
		if(m_dataset.Contains("outDMuonC.root")){ scalef=1.0; run_period=2;}
		if(m_dataset.Contains("outDMuonD.root")){ scalef=1.0; run_period=3;}
		if(m_dataset.Contains("outDMuonE.root")){ scalef=1.0; run_period=4;}
		if(m_dataset.Contains("outDMuonF.root")){ scalef=1.0; run_period=5;}

		if(m_dataset.Contains("outDEleB.root")){ scalef=1.0; run_period=1;}
		if(m_dataset.Contains("outDEleC.root")){ scalef=1.0; run_period=2;}
		if(m_dataset.Contains("outDEleD.root")){ scalef=1.0; run_period=3;}
		if(m_dataset.Contains("outDEleE.root")){ scalef=1.0; run_period=4;}
		if(m_dataset.Contains("outDEleF.root")){ scalef=1.0; run_period=5;}
		if(m_dataset.Contains("outDEle.root")) { scalef=1.0; run_period=5;}

		if(m_dataset.Contains("outWA.root")){ scalef=1000.*464.3/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outWJets_FX.root")){ scalef=1000.*61526.7/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outWJets_HT.root")){ scalef=1000.*0.008001/float(npp-nmm)*fabs(theWeight)/theWeight;run_period=8; }
		if(m_dataset.Contains("outWJets_MLM.root")){ scalef=1000.*52940.0 /float(npp-nmm)*fabs(theWeight)/theWeight;run_period=8; }
		if(m_dataset.Contains("outZJets_MLM.root")){ scalef=1000.*6225.42/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outZJets_FX.root")){ scalef=1000.*6259.0/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outZA.root")){ scalef=1000.*55.49/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
//		if(m_dataset.Contains("outprivate_ZA.root")){ scalef=1000.*47.46/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
//		if(m_dataset.Contains("outofficial_ZA.root")){ scalef=1000.*47.46/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outTTA.root")){ scalef=1000.*4.078/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outTTJets_FX.root")){ scalef=1000.*831.76/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outSTs.root")){ scalef=1000.*3.74/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outSTt.root")){ scalef=1000.*113.3/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outSTtbar.root")){ scalef=1000.*67.91/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outST_tW.root")){ scalef=1000.*34.91/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outST_tbarW.root")){ scalef=1000.*34.97/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outWW.root")){ scalef=1000.*75.8/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outWZ.root")){ scalef=1000.*27.6/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outZZ.root")){ scalef=1000.*12.14/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("ZA-EWK")){ scalef=1000.*0.1097/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("interference")){ scalef=1000.*0.012/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("ZA-aQGC")){ scalef=1000.*1.073/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outZA-sig-muonid-correct.root")){ scalef=1000.*0.1097/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}

		if(lep1_phi_station2<0) lep1_phi_station2_tmp = lep1_phi_station2+6.28319;
		if(lep2_phi_station2<0) lep2_phi_station2_tmp = lep2_phi_station2+6.28319;
		l1_weight = L1_weight(lep1_phi_station2_tmp, lep2_phi_station2_tmp, lep1_eta_station2, lep2_eta_station2);
		//cout<<"OK1"<<endl;

		if(m_dataset !="outDMuonB.root" && m_dataset !="outDMuonC.root" && m_dataset !="outDMuonD.root" && m_dataset !="outDMuonE.root" && m_dataset !="outDMuonF.root" && m_dataset !="outDMuonG.root" && m_dataset !="outDMuon.root"&&m_dataset !="outDEleB.root" && m_dataset !="outDEleC.root" && m_dataset !="outDEleD.root" && m_dataset !="outDEleE.root" && m_dataset !="outDEleF.root" && m_dataset !="outDEleG.root" && m_dataset !="outDEle.root" ){	
			pileupWeight=h13->GetBinContent(h13->GetXaxis()->FindBin(npT));
			// cout<<pileupWeight<<endl;
		}
		else {pileupWeight=-1;}
		//////  lep and photon scales
		if(lep==11){
		//	cout<<"OK2"<<endl;
			ele1_id_scale=get_ele_ID(etalep1, ptlep1, ID);
			ele2_id_scale=get_ele_ID(etalep2, ptlep2, ID);
			ele1_reco_scale=get_ele_Reco(etalep1, ptlep1,Reco);
			ele2_reco_scale=get_ele_Reco(etalep2, ptlep2,Reco);
		//	cout<<"OK3"<<endl;
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
                if(photonet>500) double photonet_=499;
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
		LEPmu = lep==13 && (HLT_Mu1>0||HLT_Mu3>0) && ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. ;
		LEPele = lep==11 && (HLT_Ele1>0||HLT_Ele2>0) && ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70.;
		SignalRegion= deltaetajj>2.5 && zepp<1.8&&Mjj>500;
		PHOTON= photonet>10 ;
		JET=jet1pt> 10 && jet2pt > 10 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7 ;
                cut0++;
//		if( ! (LEPmu||LEPele) )
//			continue;
                cut1++;
		ExTree->Fill();
	}
	f->Close();
	ID_photon_file->Close();
	Reco_egamma->Close();
	f_BF->Close();
	f_iso_BF->Close();
	Track_eff->Close();
	trigger_eff->Close();
	input13->Close();
//        cout<<"before cut: "<<cut0<<"; after cut: "<<cut1<<endl;
}
