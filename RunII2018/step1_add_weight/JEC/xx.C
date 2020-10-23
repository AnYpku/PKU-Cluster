#define xx_cxx
#include "xx.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
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

	npp = fChain->GetEntries("theWeight>0.");
	nmm = fChain->GetEntries("theWeight<0.");
	std::cout<< "numberofnp:" << npp << "  numberofnm:" <<nmm << std::endl;
	double lep1_phi_station2_tmp = 0;
	double lep2_phi_station2_tmp = 0;
	TFile * input13 = new TFile ("./puweight.root");//puweight.root
	TH1D* h13 = NULL;
	input13->GetObject("h2",h13);
        cout<<"open the file: puweight.root"<<endl;
	// for lep and photon scales
	// muon ID
	TFile * f_BF= TFile::Open("./SF/EfficienciesStudies_2018_rootfiles_RunABCD_SF_ID.root");
	TH2D* ID_BF=0;
	f_BF->GetObject("NUM_TightID_DEN_TrackerMuons_pt_abseta", ID_BF);
	cout<<"open the muon ID file: EfficienciesStudies_2018_rootfiles_RunABCD_SF_ID.root"<<endl;

	// muon iso
	TFile * f_iso_BF= TFile::Open("./SF/EfficienciesStudies_2018_rootfiles_RunABCD_SF_ISO.root");
	TH2D* iso_BF=0;
	f_iso_BF->GetObject("NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta", iso_BF);
	cout<<"open the muon ISO file: EfficienciesStudies_2018_rootfiles_RunABCD_SF_ISO.root"<<endl;
	// ele id
	TFile * f= TFile::Open("./SF/2018_ElectronMedium.root");
	TH2F* ID=0;
	f->GetObject("EGamma_SF2D", ID);
	cout<<"open the ele ID file: 2018_ElectronMedium.root"<<endl;

	//ele reco
	TFile* Reco_egamma= TFile::Open("./SF/egammaEffi.txt_EGM2D_updatedAll.root");
	TH2F* Reco=0;
	Reco_egamma->GetObject("EGamma_SF2D", Reco);
	cout<<"open the ele RECO file: egammaEffi.txt_EGM2D_updatedAll.root"<<endl;

	//photon id
	TFile* ID_photon_file = TFile::Open("./SF/2018_PhotonsMedium.root");
	TH2F* ID_photon=0;
	ID_photon_file->GetObject("EGamma_SF2D", ID_photon);
	cout<<"open the photon ID file: 2018_PhotonsMedium.root"<<endl;
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
		muon_hlt_scale=-1;
		photon_id_scale=-1;
		prefWeight=1;
		prefWeightUp=1;
		prefWeightDown=1;

		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		lep1_phi_station2_tmp = lep1_phi_station2;
		lep2_phi_station2_tmp = lep2_phi_station2;
		// if (Cut(ientry) < 0) continue;

		if(m_dataset.Contains("outDMuonB")){ scalef=1.0; run_period=1;}
		if(m_dataset.Contains("outDMuonC")){ scalef=1.0; run_period=2;}
		if(m_dataset.Contains("outDMuonD")){ scalef=1.0; run_period=3;}
		if(m_dataset.Contains("outDMuonE")){ scalef=1.0; run_period=4;}
		if(m_dataset.Contains("outDMuonA")){ scalef=1.0; run_period=5;}

		if(m_dataset.Contains("outDEleB")){ scalef=1.0; run_period=1;}
		if(m_dataset.Contains("outDEleC")){ scalef=1.0; run_period=2;}
		if(m_dataset.Contains("outDEleD")){ scalef=1.0; run_period=3;}
		if(m_dataset.Contains("outDEleE")){ scalef=1.0; run_period=4;}
		if(m_dataset.Contains("outDEleA")){ scalef=1.0; run_period=5;}
		if(m_dataset.Contains("outDEle.root")) { scalef=1.0; run_period=5;}

		if(m_dataset.Contains("outWA.root")){ scalef=1000.*464.3/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outWJets.root")){ scalef=1000.*61526.7/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outZJets.root")){ scalef=1000.*6259.0/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outZA")){ scalef=1000.*55.49/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("JESR_LoosePt")){ scalef=1000.*152/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("JESR_lowMll")){ scalef=1000.*107.1/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("JESR_lowGPt")){ scalef=1000.*1.0/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outTTA.root")){ scalef=1000.*4.078/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outTTJets.root")){ scalef=1000.*831.76/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outSTs.root")){ scalef=1000.*3.74/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outSTt.root")){ scalef=1000.*113.3/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outSTtbar.root")){ scalef=1000.*67.91/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outST_tW.root")){ scalef=1000.*34.91/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outST_tbarW.root")){ scalef=1000.*34.97/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outWW.root")){ scalef=1000.*75.8/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outWZ.root")){ scalef=1000.*27.6/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outZZ.root")){ scalef=1000.*12.14/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("ZA-EWK")){ scalef=1000.*0.1097/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("intereference")){ scalef=1000.*0.012/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("outZA-aQGC")){ scalef=1000.*1.073/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}

		if(jentry%100000==0) cout<<" "<<HLT_Ele1<<" "<<HLT_Mu2<<" "<<fabs(theWeight)/theWeight<<" npp-nmm "<<npp-nmm<<" "<<m_dataset<<" "<<jentry<<" "<<nentries<<" scalef "<<scalef<<endl;
		if(lep1_phi_station2<0) lep1_phi_station2_tmp = lep1_phi_station2+6.28319;
		if(lep2_phi_station2<0) lep2_phi_station2_tmp = lep2_phi_station2+6.28319;
		//cout<<"OK1"<<endl;

		if((m_dataset.Contains("Mu")==0) || (m_dataset.Contains("Ele")==0) ){	
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
		}

		if(photonet>0) photon_id_scale=get_photon_ID(photoneta,photonet,ID_photon);

		LEPmu = lep==13 && (HLT_Mu1>0||HLT_Mu2>0) && ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. ;
		LEPele = lep==11 && HLT_Ele1>0 && ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70.;
		SignalRegion= fabs(jet1eta-jet2eta)>2.5 && zepp<1.8&&Mjj>500;
		PHOTON= photonet>20 ;
		JET=jet1pt> 10 && jet2pt > 10 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7 ;
                cut0++;
		if( ! ((LEPmu||LEPele)&& PHOTON) )
			continue;
                cut1++;
		newtree->Fill();
	}
	f->Close();
	ID_photon_file->Close();
	Reco_egamma->Close();
	f_BF->Close();
	f_iso_BF->Close();
	input13->Close();
//        cout<<"before cut: "<<cut0<<"; after cut: "<<cut1<<endl;
}
