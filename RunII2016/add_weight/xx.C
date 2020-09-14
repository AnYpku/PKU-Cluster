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
        TFile * f_BF= TFile::Open("./muon_SFs/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunBCDEF_SF_ID.root");
        TFile * f_GH= TFile::Open("./muon_SFs/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunGH_SF_ID.root");

        TH2D* ID_BF=0;
        TH2D* ID_GH=0;
        f_BF->GetObject("NUM_TightID_DEN_genTracks_eta_pt", ID_BF);
        f_GH->GetObject("NUM_TightID_DEN_genTracks_eta_pt", ID_GH);
	// muon iso
        TFile * f_iso_BF= TFile::Open("./muon_SFs/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunBCDEF_SF_ISO.root");
        TFile * f_iso_GH= TFile::Open("./muon_SFs/EfficienciesStudies_2016_legacy_rereco_rootfiles_RunGH_SF_ISO.root");
        TH2D* iso_BF=0;
        TH2D* iso_GH=0;
        f_iso_BF->GetObject("NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt", iso_BF);
        f_iso_GH->GetObject("NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt", iso_GH);
	// muon hlt

	// ele id
        TFile * f= TFile::Open("./ele_SFs/2016LegacyReReco_ElectronMedium_Fall17V2.root");
        TH2F* ID=0;
        f->GetObject("EGamma_SF2D", ID);
	//ele reco

	//photon id
        TFile* ID_photon_file = TFile::Open("./ele_SFs/Fall17V2_2016_Medium_photons.root");
        TH2F* ID_photon=0;
        ID_photon_file->GetObject("EGamma_SF2D", ID_photon);
	// for lep and photon scales

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry < fChain->GetEntries();jentry++) {
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
                scalef=1;

		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		lep1_phi_station2_tmp = lep1_phi_station2;
		lep2_phi_station2_tmp = lep2_phi_station2;
		// if (Cut(ientry) < 0) continue;

		if(m_dataset.Contains("DMuon")){ scalef=1.0; run_period=1;}

		if(m_dataset.Contains("DEle")){ scalef=1.0; run_period=1;}

		if(m_dataset=="outWAJ2.root"){ scalef=1000.*405.3/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outWAJ-fxfx.root"){ scalef=1000.*178.6/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outWJets.root"){ scalef=1000.*61526.7/float(npp-nmm)*fabs(theWeight)/theWeight;run_period=8; }
		if(m_dataset=="outZJets.root"){ scalef=1000.*5765.4/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("ZJets_FX")){ scalef=1000.*60772.22/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outZA.root"){ scalef=1000.*47.46/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outZA_pweight")){ scalef=1000.*47.46/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outZA_total")){ scalef=1000.*47.46/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outZA-pweight")){ scalef=1000.*47.46/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outTTA.root")){ scalef=1000.*3.697/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outTTJets.root"){ scalef=1000.*831.76/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outSTs.root")){ scalef=1000.*3.36/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outST_tbarW.root")){ scalef=1000.*35.85/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outST_tW.root")){ scalef=1000.*35.85/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outSTt.root")){ scalef=1000.*136.02/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outSTtbar.root")){ scalef=1000.*80.95/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outWW.root"){ scalef=1000.*118.7/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outWZ.root"){ scalef=1000.*47.13/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset=="outZZ.root"){ scalef=1000.*16.523/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outZA-EWK")){ scalef=1000.*0.1097/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("interference")){ scalef=1000.*0.014/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
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
//			ele1_reco_scale=get_ele_Reco(etalep1, ptlep1,Reco);
//			ele2_reco_scale=get_ele_Reco(etalep2, ptlep2,Reco);
		}
		if(lep==13){
			muon1_id_scale=get_muon_ID(etalep1,ptlep1,ID_BF,ID_GH);
			muon2_id_scale=get_muon_ID(etalep2,ptlep2,ID_BF,ID_GH);
			muon1_iso_scale=get_muon_iso(etalep1,ptlep1,iso_BF,iso_GH);
			muon2_iso_scale=get_muon_iso(etalep2,ptlep2,iso_BF,iso_GH);
//			muon1_track_scale=get_muon_track_scale(etalep1,track_SF);
//			muon2_track_scale=get_muon_track_scale(etalep2,track_SF);
//			muon_hlt_scale=muon_HLT_scale(etalep1,etalep2,di_lep_trigger);
		}

		if(photonet>0) photon_id_scale=get_photon_ID(photoneta,photonet,ID_photon);
		//////  lep and photon scacles

		if(jentry%100000==0) cout<<" "<<HLT_Ele1<<" "<<HLT_Mu1<<" "<<fabs(theWeight)/theWeight<<" "<<m_dataset<<" "<<"scalef "<<scalef<<" "<<jentry<<" "<<fChain->GetEntries()<<endl;

                LEPmu = lep==13 && (HLT_Mu2>0 || HLT_Mu1>0) && ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110;
                LEPele = lep==11 && ( HLT_Ele1>0||HLT_Ele2>0) && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 && fabs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70.&&massVlep<110;
                SignalRegion= deltaetajj>2.5 && zepp<1.8&&Mjj>500;
                PHOTON= photonet>20 && (abs(photoneta)<1.4442||(abs(photoneta)>1.566&&abs(photoneta)<2.5));
                JET=jet1pt> 10 && jet2pt > 10 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7 ;
                cut0++;
//                if( !( (LEPmu||LEPele) /*&&PHOTON*/   )  )
//                        continue;
		ExTree->Fill();
	}
	f->Close();
        ID_photon_file->Close();
        f_BF->Close();
        f_GH->Close();
        f_iso_BF->Close();
        f_iso_GH->Close();
	input13->Close();
}
