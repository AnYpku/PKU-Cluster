#define xx_cxx
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include "ele_channel_scale.C"
#include "xx.h"
//#include "modify_photon_jets.C"
#define Pi 3.1415926

using namespace std;
void xx::Loop(TString name)
{
   if (fChain == 0) return;

   cut0=0,cut1=0;
   bool LEPele,LEPmu,JET,PHOTON,SignalRegion,DR;
   TFile*file=new TFile("./PUIDMaps.root");
   TH2F*h2_eff_mc2017_L=(TH2F*)file->Get("h2_eff_mc2017_L");
   TH2F*h2_eff_mc2017_M=(TH2F*)file->Get("h2_eff_mc2017_M");
   TH2F*h2_eff_mc2017_T=(TH2F*)file->Get("h2_eff_mc2017_T");
   TH2F*h2_mistag_mc2017_L=(TH2F*)file->Get("h2_mistag_mc2017_L");
   TH2F*h2_mistag_mc2017_M=(TH2F*)file->Get("h2_mistag_mc2017_M");
   TH2F*h2_mistag_mc2017_T=(TH2F*)file->Get("h2_mistag_mc2017_T");
   TH2F*h2_eff_sf2017_L=(TH2F*)file->Get("h2_eff_sf2017_L");
   TH2F*h2_eff_sf2017_M=(TH2F*)file->Get("h2_eff_sf2017_M");
   TH2F*h2_eff_sf2017_T=(TH2F*)file->Get("h2_eff_sf2017_T");
   TH2F*h2_mistag_sf2017_L=(TH2F*)file->Get("h2_mistag_sf2017_L");
   TH2F*h2_mistag_sf2017_M=(TH2F*)file->Get("h2_mistag_sf2017_M");
   TH2F*h2_mistag_sf2017_T=(TH2F*)file->Get("h2_mistag_sf2017_T");

   //photon id
   TFile* ID_photon_file = TFile::Open("../ele_SFs/2017_PhotonsMedium.root");
   TH2F* ID_photon=0;
   ID_photon_file->GetObject("EGamma_SF2D", ID_photon);
   cout<<"open the photon ID file: 2017_PhotonsMedium.root"<<endl;

   Long64_t nbytes = 0, nb = 0;
   int nentries= fChain->GetEntries();
   //  nentries=1000;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
	   Long64_t ientry = LoadTree(jentry);
	   if (ientry < 0) break;
	   nb = fChain->GetEntry(jentry);   nbytes += nb;
	   cut0++;//total events, cut0=t1->GetEntries()

	   if(name.Contains("Muon")) scalef=1;
	   if(name.Contains("Ele")) scalef=1;
           if(photonet>0){
                   photon_id_scale=get_photon_ID(photoneta,photonet,ID_photon);
           }
	   puIdweight_T=1;puIdweight_L=1;puIdweight_M=1;
	   puIdweight_T_new=1;puIdweight_T_JEC_up=1;puIdweight_T_JEC_down=1;puIdweight_T_JER_up=1;puIdweight_T_JER_down=1;
	   puIdweight_M_new=1;puIdweight_M_JEC_up=1;puIdweight_M_JEC_down=1;puIdweight_M_JER_up=1;puIdweight_M_JER_down=1;
	   puIdweight_L_new=1;puIdweight_L_JEC_up=1;puIdweight_L_JEC_down=1;puIdweight_L_JER_up=1;puIdweight_L_JER_down=1;
	   if(drla==10) drla=-1; if(drla2==10) drla2=-1; if(drj1a==10) drj1a=-1;if(drj2a==10) drj2a=-1;
	   LEPele = lep==11 && (HLT_Ele1>0 || HLT_Ele2>0) && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110;
	   LEPmu = lep==13 && (HLT_Mu1>0||HLT_Mu2>0||HLT_Mu3>0) && ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110;
	   PHOTON= photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) );
	   JET=jet1pt>30&& fabs(jet1eta)<4.7 && jet2pt>30 && fabs(jet2eta)<4.7;

	   if(jentry%1000000==0)   cout<<jentry<<"; "<<nentries<<"; cut1 = "<<cut1<<endl;
	   if(  !( ( (LEPmu) || (LEPele) ) && PHOTON ) )
		   continue;
	   if(m_dataset.Contains("ZA")&&m_dataset.Contains("plj")){
		   if(isprompt!=1 ) continue;
	   }
//	   modify_photon_jets();
           puIdweight_T=get_puIdweight(jet1eta,jet1phi,jet1pt,h2_eff_mc2017_T,h2_eff_sf2017_T,h2_mistag_mc2017_T,h2_mistag_sf2017_T,jet1puIdTight)*get_puIdweight(jet2eta,jet2phi,jet2pt,h2_eff_mc2017_T,h2_eff_sf2017_T,h2_mistag_mc2017_T,h2_mistag_sf2017_T,jet2puIdTight);
           puIdweight_M=get_puIdweight(jet1eta,jet1phi,jet1pt,h2_eff_mc2017_M,h2_eff_sf2017_M,h2_mistag_mc2017_M,h2_mistag_sf2017_M,jet1puIdMedium)*get_puIdweight(jet2eta,jet2phi,jet2pt,h2_eff_mc2017_M,h2_eff_sf2017_M,h2_mistag_mc2017_M,h2_mistag_sf2017_M,jet2puIdMedium);
           puIdweight_L=get_puIdweight(jet1eta,jet1phi,jet1pt,h2_eff_mc2017_L,h2_eff_sf2017_L,h2_mistag_mc2017_L,h2_mistag_sf2017_L,jet1puIdLoose)*get_puIdweight(jet2eta,jet2phi,jet2pt,h2_eff_mc2017_L,h2_eff_sf2017_L,h2_mistag_mc2017_L,h2_mistag_sf2017_L,jet2puIdLoose);

           puIdweight_T_new=get_puIdweight(jet1eta_new,jet1phi_new,jet1pt_new,h2_eff_mc2017_T,h2_eff_sf2017_T,h2_mistag_mc2017_T,h2_mistag_sf2017_T,jet1puIdTight_new)*get_puIdweight(jet2eta_new,jet2phi_new,jet2pt_new,h2_eff_mc2017_T,h2_eff_sf2017_T,h2_mistag_mc2017_T,h2_mistag_sf2017_T,jet2puIdTight_new);
           puIdweight_M_new=get_puIdweight(jet1eta_new,jet1phi_new,jet1pt_new,h2_eff_mc2017_M,h2_eff_sf2017_M,h2_mistag_mc2017_M,h2_mistag_sf2017_M,jet1puIdMedium_new)*get_puIdweight(jet2eta_new,jet2phi_new,jet2pt_new,h2_eff_mc2017_M,h2_eff_sf2017_M,h2_mistag_mc2017_M,h2_mistag_sf2017_M,jet2puIdMedium_new);
           puIdweight_L_new=get_puIdweight(jet1eta_new,jet1phi_new,jet1pt_new,h2_eff_mc2017_L,h2_eff_sf2017_L,h2_mistag_mc2017_L,h2_mistag_sf2017_L,jet1puIdLoose_new)*get_puIdweight(jet2eta_new,jet2phi_new,jet2pt_new,h2_eff_mc2017_L,h2_eff_sf2017_L,h2_mistag_mc2017_L,h2_mistag_sf2017_L,jet2puIdLoose_new);

           puIdweight_T_JEC_down=get_puIdweight(jet1eta_JEC_down,jet1phi_JEC_down,jet1pt_JEC_down,h2_eff_mc2017_T,h2_eff_sf2017_T,h2_mistag_mc2017_T,h2_mistag_sf2017_T,jet1puIdTight_JEC_down)*get_puIdweight(jet2eta_JEC_down,jet2phi_JEC_down,jet2pt_JEC_down,h2_eff_mc2017_T,h2_eff_sf2017_T,h2_mistag_mc2017_T,h2_mistag_sf2017_T,jet2puIdTight_JEC_down);
           puIdweight_M_JEC_down=get_puIdweight(jet1eta_JEC_down,jet1phi_JEC_down,jet1pt_JEC_down,h2_eff_mc2017_M,h2_eff_sf2017_M,h2_mistag_mc2017_M,h2_mistag_sf2017_M,jet1puIdMedium_JEC_down)*get_puIdweight(jet2eta_JEC_down,jet2phi_JEC_down,jet2pt_JEC_down,h2_eff_mc2017_M,h2_eff_sf2017_M,h2_mistag_mc2017_M,h2_mistag_sf2017_M,jet2puIdMedium_JEC_down);
           puIdweight_L_JEC_down=get_puIdweight(jet1eta_JEC_down,jet1phi_JEC_down,jet1pt_JEC_down,h2_eff_mc2017_L,h2_eff_sf2017_L,h2_mistag_mc2017_L,h2_mistag_sf2017_L,jet1puIdLoose_JEC_down)*get_puIdweight(jet2eta_JEC_down,jet2phi_JEC_down,jet2pt_JEC_down,h2_eff_mc2017_L,h2_eff_sf2017_L,h2_mistag_mc2017_L,h2_mistag_sf2017_L,jet2puIdLoose_JEC_down);

           puIdweight_T_JEC_up=get_puIdweight(jet1eta_JEC_up,jet1phi_JEC_up,jet1pt_JEC_up,h2_eff_mc2017_T,h2_eff_sf2017_T,h2_mistag_mc2017_T,h2_mistag_sf2017_T,jet1puIdTight_JEC_up)*get_puIdweight(jet2eta_JEC_up,jet2phi_JEC_up,jet2pt_JEC_up,h2_eff_mc2017_T,h2_eff_sf2017_T,h2_mistag_mc2017_T,h2_mistag_sf2017_T,jet2puIdTight_JEC_up);
           puIdweight_M_JEC_up=get_puIdweight(jet1eta_JEC_up,jet1phi_JEC_up,jet1pt_JEC_up,h2_eff_mc2017_M,h2_eff_sf2017_M,h2_mistag_mc2017_M,h2_mistag_sf2017_M,jet1puIdMedium_JEC_up)*get_puIdweight(jet2eta_JEC_up,jet2phi_JEC_up,jet2pt_JEC_up,h2_eff_mc2017_M,h2_eff_sf2017_M,h2_mistag_mc2017_M,h2_mistag_sf2017_M,jet2puIdMedium_JEC_up);
           puIdweight_L_JEC_up=get_puIdweight(jet1eta_JEC_up,jet1phi_JEC_up,jet1pt_JEC_up,h2_eff_mc2017_L,h2_eff_sf2017_L,h2_mistag_mc2017_L,h2_mistag_sf2017_L,jet1puIdLoose_JEC_up)*get_puIdweight(jet2eta_JEC_up,jet2phi_JEC_up,jet2pt_JEC_up,h2_eff_mc2017_L,h2_eff_sf2017_L,h2_mistag_mc2017_L,h2_mistag_sf2017_L,jet2puIdLoose_JEC_up);

           puIdweight_T_JER_down=get_puIdweight(jet1eta_JER_down,jet1phi_JER_down,jet1pt_JER_down,h2_eff_mc2017_T,h2_eff_sf2017_T,h2_mistag_mc2017_T,h2_mistag_sf2017_T,jet1puIdTight_JER_down)*get_puIdweight(jet2eta_JER_down,jet2phi_JER_down,jet2pt_JER_down,h2_eff_mc2017_T,h2_eff_sf2017_T,h2_mistag_mc2017_T,h2_mistag_sf2017_T,jet2puIdTight_JER_down);
           puIdweight_M_JER_down=get_puIdweight(jet1eta_JER_down,jet1phi_JER_down,jet1pt_JER_down,h2_eff_mc2017_M,h2_eff_sf2017_M,h2_mistag_mc2017_M,h2_mistag_sf2017_M,jet1puIdMedium_JER_down)*get_puIdweight(jet2eta_JER_down,jet2phi_JER_down,jet2pt_JER_down,h2_eff_mc2017_M,h2_eff_sf2017_M,h2_mistag_mc2017_M,h2_mistag_sf2017_M,jet2puIdMedium_JER_down);
           puIdweight_L_JER_down=get_puIdweight(jet1eta_JER_down,jet1phi_JER_down,jet1pt_JER_down,h2_eff_mc2017_L,h2_eff_sf2017_L,h2_mistag_mc2017_L,h2_mistag_sf2017_L,jet1puIdLoose_JER_down)*get_puIdweight(jet2eta_JER_down,jet2phi_JER_down,jet2pt_JER_down,h2_eff_mc2017_L,h2_eff_sf2017_L,h2_mistag_mc2017_L,h2_mistag_sf2017_L,jet2puIdLoose_JER_down);

           puIdweight_T_JER_up=get_puIdweight(jet1eta_JER_up,jet1phi_JER_up,jet1pt_JER_up,h2_eff_mc2017_T,h2_eff_sf2017_T,h2_mistag_mc2017_T,h2_mistag_sf2017_T,jet1puIdTight_JER_up)*get_puIdweight(jet2eta_JER_up,jet2phi_JER_up,jet2pt_JER_up,h2_eff_mc2017_T,h2_eff_sf2017_T,h2_mistag_mc2017_T,h2_mistag_sf2017_T,jet2puIdTight_JER_up);
           puIdweight_M_JER_up=get_puIdweight(jet1eta_JER_up,jet1phi_JER_up,jet1pt_JER_up,h2_eff_mc2017_M,h2_eff_sf2017_M,h2_mistag_mc2017_M,h2_mistag_sf2017_M,jet1puIdMedium_JER_up)*get_puIdweight(jet2eta_JER_up,jet2phi_JER_up,jet2pt_JER_up,h2_eff_mc2017_M,h2_eff_sf2017_M,h2_mistag_mc2017_M,h2_mistag_sf2017_M,jet2puIdMedium_JER_up);
           puIdweight_L_JER_up=get_puIdweight(jet1eta_JER_up,jet1phi_JER_up,jet1pt_JER_up,h2_eff_mc2017_L,h2_eff_sf2017_L,h2_mistag_mc2017_L,h2_mistag_sf2017_L,jet1puIdLoose_JER_up)*get_puIdweight(jet2eta_JER_up,jet2phi_JER_up,jet2pt_JER_up,h2_eff_mc2017_L,h2_eff_sf2017_L,h2_mistag_mc2017_L,h2_mistag_sf2017_L,jet2puIdLoose_JER_up);
	   cut1++;//how many events passing the selection 
	   newtree->Fill(); 

   }
   cout<<cut0<<"; "<<cut1<<endl;
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
