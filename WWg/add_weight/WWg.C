#define WWg_cxx
#include "WWg.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include "ele_channel_scale.C"
#include "muon_channel_scale.C"
using namespace std;
void WWg::Loop(TString name,double nevents)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();

   // muon ID
   TFile * f_muonID= TFile::Open("./SFs/Efficiencies_muon_generalTracks_Z_Run2018_UL_ID.root");
   TH2F* muon_ID=0;
   f_muonID->GetObject("NUM_TightID_DEN_TrackerMuons_abseta_pt",muon_ID);
   cout<<"open the muon ID file: Efficiencies_muon_generalTracks_Z_Run2018_UL_ID.root; "<<muon_ID->GetSum()<<endl;

   // muon iso
   TFile * f_muonIso= TFile::Open("./SFs/Efficiencies_muon_generalTracks_Z_Run2018_UL_ISO.root");
   TH2F* muon_ISO=0;
   f_muonIso->GetObject("NUM_TightRelIso_DEN_TightIDandIPCut_abseta_pt", muon_ISO);
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
   Bool_t BSL=0;
   int tot=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      Init();
      if(name.Contains("Mu")) { scalef=1.0;}
      if(name.Contains("Ele")){ scalef=1.0;}
      if(name.Contains("WW")&&name.Contains("G")==0) { scalef=1000.*75.8/float(nevents)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("WZ")) { scalef=1000.*27.6/float(nevents)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("ZZ")) { scalef=1000.*12.14/float(nevents)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("TTG")){ scalef=1000.*4.078/float(nevents)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("tZq")){ scalef=1000.*0.0758/float(nevents)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("TTWJets")){ scalef=1000.*0.2043/float(nevents)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("TG")==1 && name.Contains("TTG")==0 ){ scalef=1000.*2.967/float(nevents)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("ZGJets")){ scalef=1000.*55.49/float(nevents)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("WGJets")){ scalef=1000.*489/float(nevents)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("DY")) { scalef=1000.*6077.22/float(nevents)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("WJets") && name.Contains("TTW")==0 ){ scalef=1000.*61526.7/float(nevents)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("TTJets")){ scalef=1000.*831.76/float(nevents)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("WWG"))   { scalef=1000*0.402852/float(nevents)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("ST_tW"))   { scalef=1000.*34.91/float(nevents)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("ST_tbarW"))   { scalef=1000.*34.91/float(nevents)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("STt"))   { scalef=1000.*113.3/float(nevents)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("STbart"))   { scalef=1000.*67.91/float(nevents)*fabs(gen_weight)/gen_weight;}
      if(name.Contains("STs"))   { scalef=1000.*3.74/float(nevents)*fabs(gen_weight)/gen_weight;}
      ele_id_scale=get_ele_ID(lep2eta,lep2pt,ele_ID);
      ele_reco_scale=get_ele_Reco(lep2eta,lep2pt,ele_Reco);
      muon_id_scale=get_muon_ID(lep1eta,lep1pt,muon_ID);
      muon_iso_scale=get_muon_iso(lep1eta,lep1pt,muon_ISO);
      photon_id_scale=get_photon_ID(photoneta,photonet,photon_ID);
      if(fabs(photoneta)<1.4442) photon_veto_scale=0.96284181;
      if(fabs(photoneta)<2.5 && fabs(photoneta)>1.566) photon_veto_scale=0.88641977; 

      if(jentry%10000==0) cout<<jentry<<" "<<nentries<<" "<<scalef<<endl;

      BSL = (channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && /*lep1_is_tight==1 && lep2_is_tight==1 &&*/ lep1_charge*lep2_charge<0 && drll>0.5 && lep1pt>20 && lep2pt>25 && fabs(lep1eta) < 2.4 && fabs(lep1eta) < 2.5 && n_loose_ele==1 && n_loose_mu==1 && ptll>30 && mll>20 /*&& n_photon>0  && photonet > 20. && ( (fabs(photoneta) < 1.4442) || ( fabs(photoneta) < 2.5 && fabs(photoneta)>1.566 )) && drl1a>0.5 && drl2a>0.5*/ /*&& photon_selection==1*/);
      if( !( BSL ) )
	      continue;
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
