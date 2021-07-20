#define WWg_cxx
#include "WWg.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include "ele_channel_scale.C"
#include "muon_channel_scale.C"
using namespace std;
void WWg::Loop(TString name)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   
   // muon ID
   TFile * f_muonID= TFile::Open("./SFs/Efficiencies_muon_generalTracks_Z_Run2018_UL_ID.root");
   TH2F* muon_ID=0;
   f_muonID->GetObject("NUM_MediumID_DEN_TrackerMuons_abseta_pt",muon_ID);
   cout<<"open the muon ID file: Efficiencies_muon_generalTracks_Z_Run2018_UL_ID.root; "<<muon_ID->GetSum()<<endl;

   // muon iso
   TFile * f_muonIso= TFile::Open("./SFs/Efficiencies_muon_generalTracks_Z_Run2018_UL_ISO.root");
   TH2F* muon_ISO=0;
   f_muonIso->GetObject("NUM_TightRelIso_DEN_MediumID_abseta_pt", muon_ISO);
   cout<<"open the muon ISO file: Efficiencies_muon_generalTracks_Z_Run2018_UL_ISO.root"<<endl;    
  
   // ele id
   TFile * f_eleID= TFile::Open("./SFs/egammaEffi.txt_Ele_Medium_EGM2D.root");
   TH2F* ele_ID=0;
   f_eleID->GetObject("EGamma_SF2D", ele_ID);
   cout<<"open the ele ID file: egammaEffi.txt_Ele_Medium_EGM2D.root"<<endl;

   //ele reco
   TFile* f_eleReco = TFile::Open("./SFs/egammaEffi_ptAbove20.txt_EGM2D_UL2018.root");
   TH2F* ele_Reco=0;
   f_eleReco->GetObject("EGamma_SF2D", ele_Reco);
   cout<<"open the ele RECO file: egammaEffi_ptAbove20.txt_EGM2D_UL2018.root"<<endl;
   
   //photon id
   TFile* f_photonID = TFile::Open("./SFs/egammaEffi.txt_EGM2D_Pho_Med_UL18.root");
   TH2F* photon_ID=0;
   f_photonID->GetObject("EGamma_SF2D", photon_ID);
   cout<<"open the photon ID file: egammaEffi.txt_EGM2D_Pho_Med_UL18.root"<<endl;

   Long64_t nbytes = 0, nb = 0;
   int tot=0;
   Double_t eff_b_jet_medium[10] = {0.565127, 0.663282, 0.714194, 0.737916, 0.750325, 0.745599, 0.701239, 0.590619, 0.390365, 0.216667};
   Double_t pt_bin[11]  = {20, 30, 50, 70, 100, 140, 200, 300, 600, 1000, 1500};
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%10000==0) cout<<jentry<<" "<<nentries<<" "<<scalef<<endl;
      for(int i=0;i<nJet;i++){
      }
      ExTree->Fill();
      tot++;
   }
   f_muonID->Close();
   f_muonIso->Close();
   f_eleID->Close();
   f_eleReco->Close();
   f_photonID->Close();
   cout<<nentries<<" "<<tot<<endl;
}
void WWg::Init(){
	ele_id_scale=1;
	ele_reco_scale=1;
	muon_id_scale=1;
	muon_iso_scale=1;
	photon_id_scale=1;
	photon_veto_scale=1;
}
