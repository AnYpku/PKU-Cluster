#define xx_cxx
#define Pi 3.1415926
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

	Long64_t nentries = fChain->GetEntries();
	bool LEPmu,LEPele,JET,PHOTON,SignalRegion;
        int cut0=0,cut1=0;

	Long64_t npp = fChain->GetEntries("theWeight>0.");
	Long64_t nmm = fChain->GetEntries("theWeight<0.");
	std::cout<< "numberofnp:" << npp << "  numberofnm:" <<nmm << std::endl;

	TFile*file=new TFile("../PUID/PUIDMaps.root");
	TH2F*h2_eff_mc2017_M=(TH2F*)file->Get("h2_eff_mc2017_M");
	TH2F*h2_mistag_mc2017_M=(TH2F*)file->Get("h2_mistag_mc2017_M");
	TH2F*h2_eff_sf2017_M=(TH2F*)file->Get("h2_eff_sf2017_M");
	TH2F*h2_mistag_sf2017_M=(TH2F*)file->Get("h2_mistag_sf2017_M");
	TH2F*h_sys_M;

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

	// muon hlt
	TFile* trigger_eff = TFile::Open("./muon_SFs/muon_HLT_SF17.root");
	TH2D* HLT_mu=0;
	trigger_eff->GetObject("h2",HLT_mu);
	cout<<"open the muon hlt file: muon_HLT_SF17.root"<<endl;

	// ele id
	TFile * f= TFile::Open("./ele_SFs/2017_ElectronMedium.root");
	TH2F* ID=0;
	f->GetObject("EGamma_SF2D", ID);
	cout<<"open the ele ID file: 2017_ElectronMedium.root"<<endl;

	//ele reco
	TFile* Reco_egamma= TFile::Open("./ele_SFs/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root");
	TH2F* Reco=0;
	Reco_egamma->GetObject("EGamma_SF2D", Reco);
	cout<<"open the ele RECO file: egammaEffi.txt_EGM2D.root"<<endl;

	// ele hlt
	TFile * f1= TFile::Open("./ele_SFs/egammaEffi.txt_EGM2D_leg1.root");
	TFile * f2= TFile::Open("./ele_SFs/egammaEffi.txt_EGM2D_leg2.root");
	TH2F*HLT_MC1=(TH2F*)f1->Get("EGamma_EffMC2D");
	TH2F*HLT_MC2=(TH2F*)f2->Get("EGamma_EffMC2D");
	TH2F*HLT_SF1=(TH2F*)f1->Get("EGamma_SF2D");
	TH2F*HLT_SF2=(TH2F*)f2->Get("EGamma_SF2D");
	cout<<"open the ele hlt file"<<endl;

	//photon id
	TFile* ID_photon_file = TFile::Open("./ele_SFs/2017_PhotonsMedium.root");
	TH2F* ID_photon=0;
	ID_photon_file->GetObject("EGamma_SF2D", ID_photon);
	cout<<"open the photon ID file: 2017_PhotonsMedium.root"<<endl;
	// for lep and photon scales

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {

		// set lep and photon scale to -1 for default
		ele1_id_scale=-1;
		ele2_id_scale=-1;
		ele1_reco_scale=-1;
		ele2_reco_scale=-1;
		muon1_id_scale=-1;
		muon2_id_scale=-1;
		muon1_iso_scale=-1;
		muon2_iso_scale=-1;
		muon_hlt_scale=1;
		ele_hlt_scale=1;
		photon_id_scale=-1;
		photon_veto_scale=-1;
		puIdweight_M=1;

		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		// if (Cut(ientry) < 0) continue;
		if(jentry%10000==0) cout<<" "<<HLT_Ele1<<" "<<HLT_Mu2<<" "<<fabs(theWeight)/theWeight<<" "<<m_dataset<<" "<<jentry<<" "<<nentries<<endl;

		if(m_dataset.Contains("Muon")){ scalef=1.0; run_period=1;}
		if(m_dataset.Contains("Ele")) { scalef=1.0; run_period=5;}

		if(m_dataset.Contains("WA")){ scalef=1000.*464.3/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("ZJets")){ scalef=1000.*6259.0/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("DY")){ scalef=1000.*6077.22/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("ZA17")){ scalef=1000.*55.49/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		//if(m_dataset.Contains("ZA_sherpa")){ scalef=1000.*93.6/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		//if(m_dataset.Contains("ZA-EWK_sherpa")){ scalef=1000.*0.07811/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("ZA-EWK")){ scalef=1000.*0.1143/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("TTA")){ scalef=1000.*4.078/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("TTJets_FX")){ scalef=1000.*831.76/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("STs")){ scalef=1000.*3.74/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("STt")){ scalef=1000.*113.3/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("STbart")){ scalef=1000.*67.91/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("ST_tW")){ scalef=1000.*34.91/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("ST_tbarW")){ scalef=1000.*34.97/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("WW")){ scalef=1000.*75.8/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("WZ")){ scalef=1000.*27.6/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("ZZ")){ scalef=1000.*12.14/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("ZA_aQGC")){ scalef=1000.*1.073/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
		if(m_dataset.Contains("interf")){ scalef=1000.*0.012/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
                if(m_dataset.Contains("WWA")){ scalef=1000.*0.2147/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}
                if(m_dataset.Contains("WZA")){ scalef=1000.*0.04345/float(npp-nmm)*fabs(theWeight)/theWeight; run_period=8;}

		if(m_dataset.Contains("Muon")==0 && m_dataset.Contains("Ele")==0){	
			pileupWeight=h13->GetBinContent(h13->GetXaxis()->FindBin(npT));
			// cout<<pileupWeight<<endl;
		}
		else {pileupWeight=-1;}

		LEPmu = lep==13 && (HLT_Mu1>0||HLT_Mu2>0||HLT_Mu3>0) && ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110 ;
		LEPele = lep==11 && (HLT_Ele1>0||HLT_Ele2>0) && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110;
                PHOTON= photonet>20 && (fabs(photoneta)<1.4442||(fabs(photoneta)>1.566&&fabs(photoneta)<2.5));
		cut0++;
		if( !( (LEPmu||LEPele) && PHOTON) )
			continue;
		//  lep and photon scales
		if(lep==11){
			ele1_id_scale=get_ele_ID(etalep1, ptlep1, ID);
			ele2_id_scale=get_ele_ID(etalep2, ptlep2, ID);
			ele1_reco_scale=get_ele_Reco(etalep1, ptlep1,Reco);
			ele2_reco_scale=get_ele_Reco(etalep2, ptlep2,Reco);
			ele_hlt_scale=get_eleHLT_SF(etalep1,ptlep1,etalep2,ptlep2,HLT_MC1,HLT_SF1,HLT_MC2,HLT_SF2);
		}
		if(lep==13){
			muon1_id_scale=get_muon_ID(etalep1,ptlep1,ID_BF);
			muon2_id_scale=get_muon_ID(etalep2,ptlep2,ID_BF);
			muon1_iso_scale=get_muon_iso(etalep1,ptlep1,iso_BF);
			muon2_iso_scale=get_muon_iso(etalep2,ptlep2,iso_BF);
			muon_hlt_scale=muon_HLT_scale(ptlep1,ptlep2,etalep1,etalep2,HLT_mu);
		}
		if(photonet>0){
			photon_id_scale=get_photon_ID(photoneta,photonet,ID_photon);
			if(fabs(photoneta)<1.4442) photon_veto_scale=0.9862;
			if(fabs(photoneta)<2.5 && fabs(photoneta)>1.566) photon_veto_scale=0.9638;
		}
		puIdweight_M=get_puIdweight(jet1eta,jet1phi,jet1pt,h2_eff_mc2017_M,h2_eff_sf2017_M,h2_mistag_mc2017_M,h2_mistag_sf2017_M,jet1puIdMedium)*get_puIdweight(jet2eta,jet2phi,jet2pt,h2_eff_mc2017_M,h2_eff_sf2017_M,h2_mistag_mc2017_M,h2_mistag_sf2017_M,jet2puIdMedium);
		//  lep and photon scacles
		cut1++;
		ExTree->Fill();
	}
	f->Close();
	ID_photon_file->Close();
	Reco_egamma->Close();
	f_BF->Close();
	f_iso_BF->Close();
	trigger_eff->Close();
	input13->Close();
	cout<<"before cut: "<<cut0<<"; after cut: "<<cut1<<endl;
}

Double_t xx::delta_R(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2)
{       
	Double_t dp = phi1-phi2;
	if(std::fabs(dp) > Pi) dp = 2*Pi - std::fabs(dp);
	Double_t dr = std::sqrt((eta1-eta2)*(eta1-eta2)+dp*dp);
	return dr;
}

Double_t xx::get_puIdweight(double ak4jet_eta,double ak4jet_phi,double ak4jet_pt,TH2F*h2_eff_mc2017,TH2F*h2_eff_sf2017,TH2F*h2_mistag_mc2017,TH2F*h2_mistag_sf2017,double ak4jet_puId){

	double DR1=1e4,DR2=1e4;
	int ip1=-1,ip2=-1;
	double MCweight=1,Dataweight=1,puIdweight=1;
	for(int i=0;i<6;i++){
		double DR1_tmp=delta_R(ak4jet_eta,ak4jet_phi,genjet_eta[i],genjet_phi[i]);
		if(DR1_tmp<DR1){
			DR1=DR1_tmp;
			ip1=i;
		}
	}
	if(DR1<0.4 && ak4jet_pt<50){
		int bin=h2_eff_mc2017->FindBin(ak4jet_pt,ak4jet_eta);
		if(ak4jet_puId==1){
			MCweight=MCweight*h2_eff_mc2017->GetBinContent(bin);
			Dataweight=Dataweight*h2_eff_mc2017->GetBinContent(bin)*h2_eff_sf2017->GetBinContent(bin);
		}
		else{
			MCweight=MCweight*(1-h2_eff_mc2017->GetBinContent(bin));
			Dataweight=Dataweight*(1-h2_eff_mc2017->GetBinContent(bin)*h2_eff_sf2017->GetBinContent(bin));
		}
	}
	else if(DR1>0.4 && ak4jet_pt<50){
		int bin=h2_mistag_mc2017->FindBin(ak4jet_pt,ak4jet_eta);
		if(ak4jet_puId==1){
			MCweight=MCweight*h2_mistag_mc2017->GetBinContent(bin);
			Dataweight=Dataweight*h2_mistag_mc2017->GetBinContent(bin)*h2_mistag_sf2017->GetBinContent(bin);
		}
		else{
			MCweight=MCweight*(1-h2_mistag_mc2017->GetBinContent(bin));
			Dataweight=Dataweight*(1-h2_mistag_mc2017->GetBinContent(bin)*h2_mistag_sf2017->GetBinContent(bin));
		}
	}
	else{
		MCweight=1;
		Dataweight=1;
	}
	if(MCweight!=0) puIdweight=Dataweight/MCweight;
	else puIdweight=1;

	return puIdweight;
}
