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
   Long64_t npp = fChain->GetEntries("gen_weight>0.");
   Long64_t nmm = fChain->GetEntries("gen_weight<0.");
   Bool_t HLT_mm=0,HLT_ee=0,HLT_emu=0;
   Bool_t BSL=0,LEP=0,PHOTON=0,missET=0;
   int tot=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      Init();
      HLT_mm = (HLT_IsoMu24) || (HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
      HLT_ee = (HLT_Ele32_WPTight_Gsf) || (HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
      HLT_emu = (HLT_Ele32_WPTight_Gsf) || (HLT_IsoMu24) || (HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL); 
      if(name.Contains("Ele")||name.Contains("Muon")) scalef=1;
      if( !(lepton1_isprompt==1&&lepton2_isprompt==1) || (photon_isprompt!=1 || photon_gen_matching<1) )
           scalef_tmp = scalef_tmp * (-1);
      if(jentry%10000==0) cout<<jentry<<" "<<nentries<<" "<<scalef_tmp<<endl;
      BSL = (n_loose_ele+n_loose_mu)==2 && (HLT_mm || HLT_ee || HLT_emu);
      LEP = /*pass_selection>0 &&*/ lep1pt > 20. && lep2pt > 25. && fabs(lep1eta) < 2.4 && fabs(lep2eta) < 2.5 && (n_loose_ele+n_loose_mu)==2 && mll>20 && ptll>30;
      PHOTON = n_photon>0 && photonet > 20. &&( (fabs(photoneta) < 1.4442) || ( fabs(photoneta)<2.5&&fabs(photoneta)>1.566 ) );
      missET = (met>20 || puppimet>20);
      if( !( LEP /*&& PHOTON*/ && missET ) )
	      continue;
      ele_id_scale=get_ele_ID(lep2eta,lep2pt,ele_ID);
      ele_reco_scale=get_ele_Reco(lep2eta,lep2pt,ele_Reco);
      muon_id_scale=get_muon_ID(lep1eta,lep1pt,muon_ID);
      muon_iso_scale=get_muon_iso(lep2eta,lep2pt,muon_ISO);
      photon_id_scale=get_photon_ID(photoneta,photonet,photon_ID);
      if(fabs(photoneta)<1.4442) photon_veto_scale=0.96284181;
      if(fabs(photoneta)<2.5 && fabs(photoneta)>1.566) photon_veto_scale=0.88641977;
      ExTree->Fill();
      tot++;
      // if (Cut(ientry) < 0) continue;
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
