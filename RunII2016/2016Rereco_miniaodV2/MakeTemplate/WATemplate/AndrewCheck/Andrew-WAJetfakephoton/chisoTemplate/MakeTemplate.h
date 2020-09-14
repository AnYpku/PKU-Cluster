//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Sep  8 12:34:28 2018 by ROOT version 6.06/01
// from TTree demo/demo
// found on file: outDMuon.root
//////////////////////////////////////////////////////////

#ifndef MakeTemplate_h
#define MakeTemplate_h
#define ptnumber 11
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include "TObject.h"
#include <TH1D.h>
using namespace std;

// Header file for the classes stored in the TTree if any.

class MakeTemplate {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxpassFilter_HBHE = 1;
   const Int_t kMaxpassFilter_HBHEIso = 1;
   const Int_t kMaxpassFilter_globalTightHalo = 1;
   const Int_t kMaxpassFilter_ECALDeadCell = 1;
   const Int_t kMaxpassFilter_badChargedHadron = 1;
   const Int_t kMaxpassFilter_MetbadMuon = 1;
   const Int_t kMaxpassFilter_duplicateMuon = 1;

   // Declaration of leaf types
   Double_t l1_weight;
   Double_t        scalef;
   Int_t           run_period;
   Double_t        ele1_id_scale;
   Double_t        ele2_id_scale;
   Double_t        ele1_reco_scale;
   Double_t        ele2_reco_scale;
   Double_t        photon_id_scale;
   Double_t        muon1_id_scale;
   Double_t        muon2_id_scale;
   Double_t        muon1_iso_scale;
   Double_t        muon2_iso_scale;
   Double_t        muon1_track_scale;
   Double_t        muon2_track_scale;
   Double_t        muon_hlt_scale;
   Int_t           event;
   Int_t           nVtx;
   Double_t        theWeight;
   Double_t        nump;
   Double_t        numm;
   Double_t        npT;
   Int_t           lep;
   Double_t        ptVlep;
   Double_t        yVlep;
   Double_t        phiVlep;
   Double_t        massVlep;
   Double_t        Mla;
   Double_t        Mla_f;
   Double_t        Mla2;
   Double_t        Mla2_f;
   Double_t        Mva;
   Double_t        Mva_f;
   Int_t           nlooseeles;
   Int_t           nloosemus;
   Int_t           ngoodmus;
   Double_t        genphoton_pt[6];
   Double_t        genphoton_eta[6];
   Double_t        genphoton_phi[6];
   Double_t        genjet_pt[6];
   Double_t        genjet_eta[6];
   Double_t        genjet_phi[6];
   Double_t        genjet_e[6];
   Double_t        genmuon_pt[6];
   Double_t        genmuon_eta[6];
   Double_t        genmuon_phi[6];
   Double_t        genmuon_pid[6];
   Double_t        genelectron_pt[6];
   Double_t        genelectron_eta[6];
   Double_t        genelectron_phi[6];
   Double_t        photon_pt[6];
   Double_t        photon_eta[6];
   Double_t        photon_phi[6];
   Double_t        photon_e[6];
   Bool_t          photon_pev[6];
   Bool_t          photon_pevnew[6];
   Bool_t          photon_ppsv[6];
   Bool_t          photon_iseb[6];
   Bool_t          photon_isee[6];
   Double_t        photon_hoe[6];
   Double_t        photon_sieie[6];
   Double_t        photon_sieie2[6];
   Double_t        photon_chiso[6];
   Double_t        photon_nhiso[6];
   Double_t        photon_phoiso[6];
   Int_t           photon_istrue[6];
   Int_t           photon_isprompt[6];
   Double_t        photon_drla[6];
   Double_t        photon_drla2[6];
   Double_t        photon_mla[6];
   Double_t        photon_mla2[6];
   Double_t        photon_mva[6];
   Bool_t          passEleVeto;
   Bool_t          passEleVetonew;
   Bool_t          passPixelSeedVeto;
   Double_t        photonet;
   Double_t        photonet_f;
   Double_t        photoneta;
   Double_t        photoneta_f;
   Double_t        photonphi;
   Double_t        photonphi_f;
   Double_t        photone;
   Double_t        photone_f;
   Double_t        photonsieie;
   Double_t        photonsieie_f;
   Double_t        photonphoiso;
   Double_t        photonphoiso_f;
   Double_t        photonchiso;
   Double_t        photonchiso_f;
   Double_t        photonnhiso;
   Double_t        photonnhiso_f;
   Int_t           iphoton;
   Int_t           iphoton_f;
   Double_t        drla;
   Double_t        drla_f;
   Double_t        drla2;
   Double_t        drla2_f;
   Int_t           isTrue;
   Int_t           isprompt;
   Double_t        ak4jet_pt[6];
   Double_t        ak4jet_eta[6];
   Double_t        ak4jet_phi[6];
   Double_t        ak4jet_e[6];
   Double_t        ak4jet_csv[6];
   Double_t        ak4jet_icsv[6];
   Double_t        jet1pt;
   Double_t        jet1pt_f;
   Double_t        jet1eta;
   Double_t        jet1eta_f;
   Double_t        jet1phi;
   Double_t        jet1phi_f;
   Double_t        jet1e;
   Double_t        jet1e_f;
   Double_t        jet1csv;
   Double_t        jet1csv_f;
   Double_t        jet1icsv;
   Double_t        jet1icsv_f;
   Double_t        jet2pt;
   Double_t        jet2pt_f;
   Double_t        jet2eta;
   Double_t        jet2eta_f;
   Double_t        jet2phi;
   Double_t        jet2phi_f;
   Double_t        jet2e;
   Double_t        jet2e_f;
   Double_t        jet2csv;
   Double_t        jet2csv_f;
   Double_t        jet2icsv;
   Double_t        jet2icsv_f;
   Double_t        drj1a;
   Double_t        drj1a_f;
   Double_t        drj2a;
   Double_t        drj2a_f;
   Double_t        drj1l;
   Double_t        drj1l_f;
   Double_t        drj2l;
   Double_t        drj2l_f;
   Double_t        drj1l2;
   Double_t        drj1l2_f;
   Double_t        drj2l2;
   Double_t        drj2l2_f;
   Double_t        Mjj;
   Double_t        Mjj_f;
   Double_t        deltaetajj;
   Double_t        deltaetajj_f;
   Double_t        zepp;
   Double_t        zepp_f;
   Double_t        ptlep1;
   Double_t        etalep1;
   Double_t        philep1;
   Double_t        ptlep2;
   Double_t        etalep2;
   Double_t        philep2;
   Double_t        ele1_sigmaieie;
   Double_t        ele2_sigmaieie;
   Int_t           muon1_trackerLayers;
   Double_t        matchedgenMu1_pt;
   Int_t           muon2_trackerLayers;
   Double_t        matchedgenMu2_pt;
   Double_t        j1metPhi;
   Double_t        j1metPhi_f;
   Double_t        j2metPhi;
   Double_t        j2metPhi_f;
   Double_t        MET_et;
   Double_t        MET_phi;
   Int_t           HLT_Ele1;
   Int_t           HLT_Ele2;
   Int_t           HLT_Ele3;
   Int_t           HLT_Ele4;
   Int_t           HLT_Ele5;
   Int_t           HLT_Ele6;
   Int_t           HLT_Ele7;
   Int_t           HLT_Mu1;
   Int_t           HLT_Mu2;
   Int_t           HLT_Mu3;
   Int_t           HLT_Mu4;
   Int_t           HLT_Mu5;
   Int_t           HLT_Mu6;
   Int_t           HLT_Mu7;
   Int_t           HLT_Mu8;
   Int_t           HLT_Mu9;
   Int_t           HLT_Mu10;
   Int_t           HLT_Mu11;
   Bool_t          passFilter_HBHE;
   Bool_t          passFilter_HBHEIso;
   Bool_t          passFilter_globalTightHalo;
   Bool_t          passFilter_ECALDeadCell;
   Bool_t          passFilter_GoodVtx;
   Bool_t          passFilter_EEBadSc;
   Bool_t          passFilter_badMuon;
   Bool_t          passFilter_badChargedHadron;
   Bool_t          passFilter_MetbadMuon;
   Bool_t          passFilter_duplicateMuon;
   Double_t        lumiWeight;
   Double_t        pileupWeight;
   Double_t        lep1_eta_station2;
   Double_t        lep1_phi_station2;
   Int_t           lep1_sign;
   Double_t        lep2_eta_station2;
   Double_t        lep2_phi_station2;
   Int_t           lep2_sign;
   Double_t        lhe_ele1_px;
   Double_t        lhe_ele1_py;
   Double_t        lhe_ele1_pz;
   Double_t        lhe_ele1_e;
   Double_t        lhe_ele2_px;
   Double_t        lhe_ele2_py;
   Double_t        lhe_ele2_pz;
   Double_t        lhe_ele2_e;
   Double_t        lhe_mu1_px;
   Double_t        lhe_mu1_py;
   Double_t        lhe_mu1_pz;
   Double_t        lhe_mu1_e;
   Double_t        lhe_mu2_px;
   Double_t        lhe_mu2_py;
   Double_t        lhe_mu2_pz;
   Double_t        lhe_mu2_e;
   Double_t        lhe_jet1_px;
   Double_t        lhe_jet1_py;
   Double_t        lhe_jet1_pz;
   Double_t        lhe_jet1_e;
   Double_t        lhe_jet2_px;
   Double_t        lhe_jet2_py;
   Double_t        lhe_jet2_pz;
   Double_t        lhe_jet2_e;
   Double_t        lhe_photon_px;
   Double_t        lhe_photon_py;
   Double_t        lhe_photon_pz;
   Double_t        lhe_photon_e;

   // List of branches
   TBranch        *b_scalef;   //!
   TBranch        *b_run_period;   //!
   TBranch        *b_ele1_id_scale;   //!
   TBranch        *b_ele2_id_scale;   //!
   TBranch        *b_ele1_reco_scale;   //!
   TBranch        *b_ele2_reco_scale;   //!
   TBranch        *b_photon_id_scale;   //!
   TBranch        *b_muon1_id_scale;   //!
   TBranch        *b_muon2_id_scale;   //!
   TBranch        *b_muon1_iso_scale;   //!
   TBranch        *b_muon2_iso_scale;   //!
   TBranch        *b_muon1_track_scale;   //!
   TBranch        *b_muon2_track_scale;   //!
   TBranch        *b_muon_hlt_scale;   //!
   TBranch        *b_event;   //!
   TBranch        *b_nVtx;   //!
   TBranch        *b_theWeight;   //!
   TBranch        *b_nump;   //!
   TBranch        *b_numm;   //!
   TBranch        *b_npT;   //!
   TBranch        *b_lep;   //!
   TBranch        *b_ptVlep;   //!
   TBranch        *b_yVlep;   //!
   TBranch        *b_phiVlep;   //!
   TBranch        *b_massVlep;   //!
   TBranch        *b_Mla;   //!
   TBranch        *b_Mla_f;   //!
   TBranch        *b_Mla2;   //!
   TBranch        *b_Mla2_f;   //!
   TBranch        *b_Mva;   //!
   TBranch        *b_Mva_f;   //!
   TBranch        *b_nlooseeles;   //!
   TBranch        *b_nloosemus;   //!
   TBranch        *b_ngoodmus;   //!
   TBranch        *b_genphoton_pt;   //!
   TBranch        *b_genphoton_eta;   //!
   TBranch        *b_genphoton_phi;   //!
   TBranch        *b_genjet_pt;   //!
   TBranch        *b_genjet_eta;   //!
   TBranch        *b_genjet_phi;   //!
   TBranch        *b_genjet_e;   //!
   TBranch        *b_genmuon_pt;   //!
   TBranch        *b_genmuon_eta;   //!
   TBranch        *b_genmuon_phi;   //!
   TBranch        *b_genmuon_pid;   //!
   TBranch        *b_genelectron_pt;   //!
   TBranch        *b_genelectron_eta;   //!
   TBranch        *b_genelectron_phi;   //!
   TBranch        *b_photon_pt;   //!
   TBranch        *b_photon_eta;   //!
   TBranch        *b_photon_phi;   //!
   TBranch        *b_photon_e;   //!
   TBranch        *b_photon_pev;   //!
   TBranch        *b_photon_pevnew;   //!
   TBranch        *b_photon_ppsv;   //!
   TBranch        *b_photon_iseb;   //!
   TBranch        *b_photon_isee;   //!
   TBranch        *b_photon_hoe;   //!
   TBranch        *b_photon_sieie;   //!
   TBranch        *b_photon_sieie2;   //!
   TBranch        *b_photon_chiso;   //!
   TBranch        *b_photon_nhiso;   //!
   TBranch        *b_photon_phoiso;   //!
   TBranch        *b_photon_istrue;   //!
   TBranch        *b_photon_isprompt;   //!
   TBranch        *b_photon_drla;   //!
   TBranch        *b_photon_drla2;   //!
   TBranch        *b_photon_mla;   //!
   TBranch        *b_photon_mla2;   //!
   TBranch        *b_photon_mva;   //!
   TBranch        *b_passEleVeto;   //!
   TBranch        *b_passEleVetonew;   //!
   TBranch        *b_passPixelSeedVeto;   //!
   TBranch        *b_photonet;   //!
   TBranch        *b_photonet_f;   //!
   TBranch        *b_photoneta;   //!
   TBranch        *b_photoneta_f;   //!
   TBranch        *b_photonphi;   //!
   TBranch        *b_photonphi_f;   //!
   TBranch        *b_photone;   //!
   TBranch        *b_photone_f;   //!
   TBranch        *b_photonsieie;   //!
   TBranch        *b_photonsieie_f;   //!
   TBranch        *b_photonphoiso;   //!
   TBranch        *b_photonphoiso_f;   //!
   TBranch        *b_photonchiso;   //!
   TBranch        *b_photonchiso_f;   //!
   TBranch        *b_photonnhiso;   //!
   TBranch        *b_photonnhiso_f;   //!
   TBranch        *b_iphoton;   //!
   TBranch        *b_iphoton_f;   //!
   TBranch        *b_drla;   //!
   TBranch        *b_drla_f;   //!
   TBranch        *b_drla2;   //!
   TBranch        *b_drla2_f;   //!
   TBranch        *b_isTrue;   //!
   TBranch        *b_isprompt;   //!
   TBranch        *b_ak4jet_pt;   //!
   TBranch        *b_ak4jet_eta;   //!
   TBranch        *b_ak4jet_phi;   //!
   TBranch        *b_ak4jet_e;   //!
   TBranch        *b_ak4jet_csv;   //!
   TBranch        *b_ak4jet_icsv;   //!
   TBranch        *b_jet1pt;   //!
   TBranch        *b_jet1pt_f;   //!
   TBranch        *b_jet1eta;   //!
   TBranch        *b_jet1eta_f;   //!
   TBranch        *b_jet1phi;   //!
   TBranch        *b_jet1phi_f;   //!
   TBranch        *b_jet1e;   //!
   TBranch        *b_jet1e_f;   //!
   TBranch        *b_jet1csv;   //!
   TBranch        *b_jet1csv_f;   //!
   TBranch        *b_jet1icsv;   //!
   TBranch        *b_jet1icsv_f;   //!
   TBranch        *b_jet2pt;   //!
   TBranch        *b_jet2pt_f;   //!
   TBranch        *b_jet2eta;   //!
   TBranch        *b_jet2eta_f;   //!
   TBranch        *b_jet2phi;   //!
   TBranch        *b_jet2phi_f;   //!
   TBranch        *b_jet2e;   //!
   TBranch        *b_jet2e_f;   //!
   TBranch        *b_jet2csv;   //!
   TBranch        *b_jet2csv_f;   //!
   TBranch        *b_jet2icsv;   //!
   TBranch        *b_jet2icsv_f;   //!
   TBranch        *b_drj1a;   //!
   TBranch        *b_drj1a_f;   //!
   TBranch        *b_drj2a;   //!
   TBranch        *b_drj2a_f;   //!
   TBranch        *b_drj1l;   //!
   TBranch        *b_drj1l_f;   //!
   TBranch        *b_drj2l;   //!
   TBranch        *b_drj2l_f;   //!
   TBranch        *b_drj1l2;   //!
   TBranch        *b_drj1l2_f;   //!
   TBranch        *b_drj2l2;   //!
   TBranch        *b_drj2l2_f;   //!
   TBranch        *b_Mjj;   //!
   TBranch        *b_Mjj_f;   //!
   TBranch        *b_deltaetajj;   //!
   TBranch        *b_deltaetajj_f;   //!
   TBranch        *b_zepp;   //!
   TBranch        *b_zepp_f;   //!
   TBranch        *b_ptlep1;   //!
   TBranch        *b_etalep1;   //!
   TBranch        *b_philep1;   //!
   TBranch        *b_ptlep2;   //!
   TBranch        *b_etalep2;   //!
   TBranch        *b_philep2;   //!
   TBranch        *b_ele1_sigmaieie;   //!
   TBranch        *b_ele2_sigmaieie;   //!
   TBranch        *b_muon1_trackerLayers;   //!
   TBranch        *b_matchedgenMu1_pt;   //!
   TBranch        *b_muon2_trackerLayers;   //!
   TBranch        *b_matchedgenMu2_pt;   //!
   TBranch        *b_j1metPhi;   //!
   TBranch        *b_j1metPhi_f;   //!
   TBranch        *b_j2metPhi;   //!
   TBranch        *b_j2metPhi_f;   //!
   TBranch        *b_MET_et;   //!
   TBranch        *b_MET_phi;   //!
   TBranch        *b_HLT_Ele1;   //!
   TBranch        *b_HLT_Ele2;   //!
   TBranch        *b_HLT_Ele3;   //!
   TBranch        *b_HLT_Ele4;   //!
   TBranch        *b_HLT_Ele5;   //!
   TBranch        *b_HLT_Ele6;   //!
   TBranch        *b_HLT_Ele7;   //!
   TBranch        *b_HLT_Mu1;   //!
   TBranch        *b_HLT_Mu2;   //!
   TBranch        *b_HLT_Mu3;   //!
   TBranch        *b_HLT_Mu4;   //!
   TBranch        *b_HLT_Mu5;   //!
   TBranch        *b_HLT_Mu6;   //!
   TBranch        *b_HLT_Mu7;   //!
   TBranch        *b_HLT_Mu8;   //!
   TBranch        *b_HLT_Mu9;   //!
   TBranch        *b_HLT_Mu10;   //!
   TBranch        *b_HLT_Mu11;   //!
   TBranch        *b_passFilter_HBHE_;   //!
   TBranch        *b_passFilter_HBHEIso_;   //!
   TBranch        *b_passFilter_globalTightHalo_;   //!
   TBranch        *b_passFilter_ECALDeadCell_;   //!
   TBranch        *b_passFilter_GoodVtx;   //!
   TBranch        *b_passFilter_EEBadSc;   //!
   TBranch        *b_passFilter_badMuon;   //!
   TBranch        *b_passFilter_badChargedHadron_;   //!
   TBranch        *b_passFilter_MetbadMuon_;   //!
   TBranch        *b_passFilter_duplicateMuon_;   //!
   TBranch        *b_lumiWeight;   //!
   TBranch        *b_pileupWeight;   //!
   TBranch        *b_lep1_eta_station2;   //!
   TBranch        *b_lep1_phi_station2;   //!
   TBranch        *b_lep1_sign;   //!
   TBranch        *b_lep2_eta_station2;   //!
   TBranch        *b_lep2_phi_station2;   //!
   TBranch        *b_lep2_sign;   //!
   TBranch        *b_lhe_ele1_px;   //!
   TBranch        *b_lhe_ele1_py;   //!
   TBranch        *b_lhe_ele1_pz;   //!
   TBranch        *b_lhe_ele1_e;   //!
   TBranch        *b_lhe_ele2_px;   //!
   TBranch        *b_lhe_ele2_py;   //!
   TBranch        *b_lhe_ele2_pz;   //!
   TBranch        *b_lhe_ele2_e;   //!
   TBranch        *b_lhe_mu1_px;   //!
   TBranch        *b_lhe_mu1_py;   //!
   TBranch        *b_lhe_mu1_pz;   //!
   TBranch        *b_lhe_mu1_e;   //!
   TBranch        *b_lhe_mu2_px;   //!
   TBranch        *b_lhe_mu2_py;   //!
   TBranch        *b_lhe_mu2_pz;   //!
   TBranch        *b_lhe_mu2_e;   //!
   TBranch        *b_lhe_jet1_px;   //!
   TBranch        *b_lhe_jet1_py;   //!
   TBranch        *b_lhe_jet1_pz;   //!
   TBranch        *b_lhe_jet1_e;   //!
   TBranch        *b_lhe_jet2_px;   //!
   TBranch        *b_lhe_jet2_py;   //!
   TBranch        *b_lhe_jet2_pz;   //!
   TBranch        *b_lhe_jet2_e;   //!
   TBranch        *b_lhe_photon_px;   //!
   TBranch        *b_lhe_photon_py;   //!
   TBranch        *b_lhe_photon_pz;   //!
   TBranch        *b_lhe_photon_e;   //!

   MakeTemplate(TTree *tree=0,TString dataset="");
   virtual ~MakeTemplate();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(TString name);
   virtual void     endJob(TString name);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
  
/* Add some variable and histos*/
 Double_t actualWeight;
 Double_t f,t,df,dt,p,file1,file2,file3,n;
 Double_t lowpt[ptnumber]=     {15,20,25,30,35,40,45,50,60,80,120};
 Double_t highpt[ptnumber]=    {20,25,30,35,40,45,50,60,80,120,400};
 Double_t pttruelow[ptnumber]= {15,15,15,30,30,30,30,30,15,15,15};
 Double_t pttruehigh[ptnumber]={30,30,30,60,60,60,60,60,80,30,30};
 Int_t    bin;  
 Double_t xlow; 
 Double_t xhigh;
 vector<double> vector_pt;
 vector<double>::iterator biggest_pt;
 Int_t position,size,m;
 TH1D* h1[ptnumber];
 TH1D* h2[ptnumber];
 TH1D* h3[ptnumber];
 TH1D* h4[ptnumber];
 TH1D* hsieie[ptnumber];
 TCanvas *c1[ptnumber];
 bool LEPdata,LEPmc,Photon_cut[6];
/* Add some variable and histos*/

/* Add some function*/
void histo();
void style();
void select(TTree *tree,TH1D *h1[9],TH1D *h2[9],TH1D *h3[9],TH1D *h4[9]);
void draw(TCanvas *c,TH1D *h1,TH1D *h2,TH1D *h3,TH1D *h4,Double_t ptlow,Double_t pthigh);
void creatfiles();
void ResetVal();
TString m_dataset;
/* Add some function*/
 private:
    TTree *newtree;
    TFile *fout;
    TFile *f1;
    TFile *f2;
    TFile *f3;
    TFile *f4;
};

#endif

#ifdef MakeTemplate_cxx
MakeTemplate::MakeTemplate(TTree *tree,TString dataset) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("outDMuon.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("outDMuon.root");
      }
      f->GetObject("demo",tree);

   }
   m_dataset=dataset;
   Init(tree);
}

MakeTemplate::~MakeTemplate()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MakeTemplate::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MakeTemplate::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void MakeTemplate::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fout = new TFile(m_dataset, "RECREATE");
   newtree = fChain->CloneTree(0);
   newtree->Branch("l1_weight", &l1_weight, "l1_weight/D");
   fChain->SetBranchAddress("scalef", &scalef, &b_scalef);
   fChain->SetBranchAddress("run_period", &run_period, &b_run_period);
   fChain->SetBranchAddress("ele1_id_scale", &ele1_id_scale, &b_ele1_id_scale);
   fChain->SetBranchAddress("ele2_id_scale", &ele2_id_scale, &b_ele2_id_scale);
   fChain->SetBranchAddress("ele1_reco_scale", &ele1_reco_scale, &b_ele1_reco_scale);
   fChain->SetBranchAddress("ele2_reco_scale", &ele2_reco_scale, &b_ele2_reco_scale);
   fChain->SetBranchAddress("photon_id_scale", &photon_id_scale, &b_photon_id_scale);
   fChain->SetBranchAddress("muon1_id_scale", &muon1_id_scale, &b_muon1_id_scale);
   fChain->SetBranchAddress("muon2_id_scale", &muon2_id_scale, &b_muon2_id_scale);
   fChain->SetBranchAddress("muon1_iso_scale", &muon1_iso_scale, &b_muon1_iso_scale);
   fChain->SetBranchAddress("muon2_iso_scale", &muon2_iso_scale, &b_muon2_iso_scale);
   fChain->SetBranchAddress("muon1_track_scale", &muon1_track_scale, &b_muon1_track_scale);
   fChain->SetBranchAddress("muon2_track_scale", &muon2_track_scale, &b_muon2_track_scale);
   fChain->SetBranchAddress("muon_hlt_scale", &muon_hlt_scale, &b_muon_hlt_scale);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
   fChain->SetBranchAddress("theWeight", &theWeight, &b_theWeight);
   fChain->SetBranchAddress("nump", &nump, &b_nump);
   fChain->SetBranchAddress("numm", &numm, &b_numm);
   fChain->SetBranchAddress("npT", &npT, &b_npT);
   fChain->SetBranchAddress("lep", &lep, &b_lep);
   fChain->SetBranchAddress("ptVlep", &ptVlep, &b_ptVlep);
   fChain->SetBranchAddress("yVlep", &yVlep, &b_yVlep);
   fChain->SetBranchAddress("phiVlep", &phiVlep, &b_phiVlep);
   fChain->SetBranchAddress("massVlep", &massVlep, &b_massVlep);
   fChain->SetBranchAddress("Mla", &Mla, &b_Mla);
   fChain->SetBranchAddress("Mla_f", &Mla_f, &b_Mla_f);
   fChain->SetBranchAddress("Mla2", &Mla2, &b_Mla2);
   fChain->SetBranchAddress("Mla2_f", &Mla2_f, &b_Mla2_f);
   fChain->SetBranchAddress("Mva", &Mva, &b_Mva);
   fChain->SetBranchAddress("Mva_f", &Mva_f, &b_Mva_f);
   fChain->SetBranchAddress("nlooseeles", &nlooseeles, &b_nlooseeles);
   fChain->SetBranchAddress("nloosemus", &nloosemus, &b_nloosemus);
   fChain->SetBranchAddress("ngoodmus", &ngoodmus, &b_ngoodmus);
   fChain->SetBranchAddress("genphoton_pt", genphoton_pt, &b_genphoton_pt);
   fChain->SetBranchAddress("genphoton_eta", genphoton_eta, &b_genphoton_eta);
   fChain->SetBranchAddress("genphoton_phi", genphoton_phi, &b_genphoton_phi);
   fChain->SetBranchAddress("genjet_pt", genjet_pt, &b_genjet_pt);
   fChain->SetBranchAddress("genjet_eta", genjet_eta, &b_genjet_eta);
   fChain->SetBranchAddress("genjet_phi", genjet_phi, &b_genjet_phi);
   fChain->SetBranchAddress("genjet_e", genjet_e, &b_genjet_e);
   fChain->SetBranchAddress("genmuon_pt", genmuon_pt, &b_genmuon_pt);
   fChain->SetBranchAddress("genmuon_eta", genmuon_eta, &b_genmuon_eta);
   fChain->SetBranchAddress("genmuon_phi", genmuon_phi, &b_genmuon_phi);
   fChain->SetBranchAddress("genmuon_pid", genmuon_pid, &b_genmuon_pid);
   fChain->SetBranchAddress("genelectron_pt", genelectron_pt, &b_genelectron_pt);
   fChain->SetBranchAddress("genelectron_eta", genelectron_eta, &b_genelectron_eta);
   fChain->SetBranchAddress("genelectron_phi", genelectron_phi, &b_genelectron_phi);
   fChain->SetBranchAddress("photon_pt", photon_pt, &b_photon_pt);
   fChain->SetBranchAddress("photon_eta", photon_eta, &b_photon_eta);
   fChain->SetBranchAddress("photon_phi", photon_phi, &b_photon_phi);
   fChain->SetBranchAddress("photon_e", photon_e, &b_photon_e);
   fChain->SetBranchAddress("photon_pev", photon_pev, &b_photon_pev);
   fChain->SetBranchAddress("photon_pevnew", photon_pevnew, &b_photon_pevnew);
   fChain->SetBranchAddress("photon_ppsv", photon_ppsv, &b_photon_ppsv);
   fChain->SetBranchAddress("photon_iseb", photon_iseb, &b_photon_iseb);
   fChain->SetBranchAddress("photon_isee", photon_isee, &b_photon_isee);
   fChain->SetBranchAddress("photon_hoe", photon_hoe, &b_photon_hoe);
   fChain->SetBranchAddress("photon_sieie", photon_sieie, &b_photon_sieie);
   fChain->SetBranchAddress("photon_sieie2", photon_sieie2, &b_photon_sieie2);
   fChain->SetBranchAddress("photon_chiso", photon_chiso, &b_photon_chiso);
   fChain->SetBranchAddress("photon_nhiso", photon_nhiso, &b_photon_nhiso);
   fChain->SetBranchAddress("photon_phoiso", photon_phoiso, &b_photon_phoiso);
   fChain->SetBranchAddress("photon_istrue", photon_istrue, &b_photon_istrue);
   fChain->SetBranchAddress("photon_isprompt", photon_isprompt, &b_photon_isprompt);
   fChain->SetBranchAddress("photon_drla", photon_drla, &b_photon_drla);
   fChain->SetBranchAddress("photon_drla2", photon_drla2, &b_photon_drla2);
   fChain->SetBranchAddress("photon_mla", photon_mla, &b_photon_mla);
   fChain->SetBranchAddress("photon_mla2", photon_mla2, &b_photon_mla2);
   fChain->SetBranchAddress("photon_mva", photon_mva, &b_photon_mva);
   fChain->SetBranchAddress("passEleVeto", &passEleVeto, &b_passEleVeto);
   fChain->SetBranchAddress("passEleVetonew", &passEleVetonew, &b_passEleVetonew);
   fChain->SetBranchAddress("passPixelSeedVeto", &passPixelSeedVeto, &b_passPixelSeedVeto);
   fChain->SetBranchAddress("photonet", &photonet, &b_photonet);
   fChain->SetBranchAddress("photonet_f", &photonet_f, &b_photonet_f);
   fChain->SetBranchAddress("photoneta", &photoneta, &b_photoneta);
   fChain->SetBranchAddress("photoneta_f", &photoneta_f, &b_photoneta_f);
   fChain->SetBranchAddress("photonphi", &photonphi, &b_photonphi);
   fChain->SetBranchAddress("photonphi_f", &photonphi_f, &b_photonphi_f);
   fChain->SetBranchAddress("photone", &photone, &b_photone);
   fChain->SetBranchAddress("photone_f", &photone_f, &b_photone_f);
   fChain->SetBranchAddress("photonsieie", &photonsieie, &b_photonsieie);
   fChain->SetBranchAddress("photonsieie_f", &photonsieie_f, &b_photonsieie_f);
   fChain->SetBranchAddress("photonphoiso", &photonphoiso, &b_photonphoiso);
   fChain->SetBranchAddress("photonphoiso_f", &photonphoiso_f, &b_photonphoiso_f);
   fChain->SetBranchAddress("photonchiso", &photonchiso, &b_photonchiso);
   fChain->SetBranchAddress("photonchiso_f", &photonchiso_f, &b_photonchiso_f);
   fChain->SetBranchAddress("photonnhiso", &photonnhiso, &b_photonnhiso);
   fChain->SetBranchAddress("photonnhiso_f", &photonnhiso_f, &b_photonnhiso_f);
   fChain->SetBranchAddress("iphoton", &iphoton, &b_iphoton);
   fChain->SetBranchAddress("iphoton_f", &iphoton_f, &b_iphoton_f);
   fChain->SetBranchAddress("drla", &drla, &b_drla);
   fChain->SetBranchAddress("drla_f", &drla_f, &b_drla_f);
   fChain->SetBranchAddress("drla2", &drla2, &b_drla2);
   fChain->SetBranchAddress("drla2_f", &drla2_f, &b_drla2_f);
   fChain->SetBranchAddress("isTrue", &isTrue, &b_isTrue);
   fChain->SetBranchAddress("isprompt", &isprompt, &b_isprompt);
   fChain->SetBranchAddress("ak4jet_pt", ak4jet_pt, &b_ak4jet_pt);
   fChain->SetBranchAddress("ak4jet_eta", ak4jet_eta, &b_ak4jet_eta);
   fChain->SetBranchAddress("ak4jet_phi", ak4jet_phi, &b_ak4jet_phi);
   fChain->SetBranchAddress("ak4jet_e", ak4jet_e, &b_ak4jet_e);
   fChain->SetBranchAddress("ak4jet_csv", ak4jet_csv, &b_ak4jet_csv);
   fChain->SetBranchAddress("ak4jet_icsv", ak4jet_icsv, &b_ak4jet_icsv);
   fChain->SetBranchAddress("jet1pt", &jet1pt, &b_jet1pt);
   fChain->SetBranchAddress("jet1pt_f", &jet1pt_f, &b_jet1pt_f);
   fChain->SetBranchAddress("jet1eta", &jet1eta, &b_jet1eta);
   fChain->SetBranchAddress("jet1eta_f", &jet1eta_f, &b_jet1eta_f);
   fChain->SetBranchAddress("jet1phi", &jet1phi, &b_jet1phi);
   fChain->SetBranchAddress("jet1phi_f", &jet1phi_f, &b_jet1phi_f);
   fChain->SetBranchAddress("jet1e", &jet1e, &b_jet1e);
   fChain->SetBranchAddress("jet1e_f", &jet1e_f, &b_jet1e_f);
   fChain->SetBranchAddress("jet1csv", &jet1csv, &b_jet1csv);
   fChain->SetBranchAddress("jet1csv_f", &jet1csv_f, &b_jet1csv_f);
   fChain->SetBranchAddress("jet1icsv", &jet1icsv, &b_jet1icsv);
   fChain->SetBranchAddress("jet1icsv_f", &jet1icsv_f, &b_jet1icsv_f);
   fChain->SetBranchAddress("jet2pt", &jet2pt, &b_jet2pt);
   fChain->SetBranchAddress("jet2pt_f", &jet2pt_f, &b_jet2pt_f);
   fChain->SetBranchAddress("jet2eta", &jet2eta, &b_jet2eta);
   fChain->SetBranchAddress("jet2eta_f", &jet2eta_f, &b_jet2eta_f);
   fChain->SetBranchAddress("jet2phi", &jet2phi, &b_jet2phi);
   fChain->SetBranchAddress("jet2phi_f", &jet2phi_f, &b_jet2phi_f);
   fChain->SetBranchAddress("jet2e", &jet2e, &b_jet2e);
   fChain->SetBranchAddress("jet2e_f", &jet2e_f, &b_jet2e_f);
   fChain->SetBranchAddress("jet2csv", &jet2csv, &b_jet2csv);
   fChain->SetBranchAddress("jet2csv_f", &jet2csv_f, &b_jet2csv_f);
   fChain->SetBranchAddress("jet2icsv", &jet2icsv, &b_jet2icsv);
   fChain->SetBranchAddress("jet2icsv_f", &jet2icsv_f, &b_jet2icsv_f);
   fChain->SetBranchAddress("drj1a", &drj1a, &b_drj1a);
   fChain->SetBranchAddress("drj1a_f", &drj1a_f, &b_drj1a_f);
   fChain->SetBranchAddress("drj2a", &drj2a, &b_drj2a);
   fChain->SetBranchAddress("drj2a_f", &drj2a_f, &b_drj2a_f);
   fChain->SetBranchAddress("drj1l", &drj1l, &b_drj1l);
   fChain->SetBranchAddress("drj1l_f", &drj1l_f, &b_drj1l_f);
   fChain->SetBranchAddress("drj2l", &drj2l, &b_drj2l);
   fChain->SetBranchAddress("drj2l_f", &drj2l_f, &b_drj2l_f);
   fChain->SetBranchAddress("drj1l2", &drj1l2, &b_drj1l2);
   fChain->SetBranchAddress("drj1l2_f", &drj1l2_f, &b_drj1l2_f);
   fChain->SetBranchAddress("drj2l2", &drj2l2, &b_drj2l2);
   fChain->SetBranchAddress("drj2l2_f", &drj2l2_f, &b_drj2l2_f);
   fChain->SetBranchAddress("Mjj", &Mjj, &b_Mjj);
   fChain->SetBranchAddress("Mjj_f", &Mjj_f, &b_Mjj_f);
   fChain->SetBranchAddress("deltaetajj", &deltaetajj, &b_deltaetajj);
   fChain->SetBranchAddress("deltaetajj_f", &deltaetajj_f, &b_deltaetajj_f);
   fChain->SetBranchAddress("zepp", &zepp, &b_zepp);
   fChain->SetBranchAddress("zepp_f", &zepp_f, &b_zepp_f);
   fChain->SetBranchAddress("ptlep1", &ptlep1, &b_ptlep1);
   fChain->SetBranchAddress("etalep1", &etalep1, &b_etalep1);
   fChain->SetBranchAddress("philep1", &philep1, &b_philep1);
   fChain->SetBranchAddress("ptlep2", &ptlep2, &b_ptlep2);
   fChain->SetBranchAddress("etalep2", &etalep2, &b_etalep2);
   fChain->SetBranchAddress("philep2", &philep2, &b_philep2);
   fChain->SetBranchAddress("ele1_sigmaieie", &ele1_sigmaieie, &b_ele1_sigmaieie);
   fChain->SetBranchAddress("ele2_sigmaieie", &ele2_sigmaieie, &b_ele2_sigmaieie);
   fChain->SetBranchAddress("muon1_trackerLayers", &muon1_trackerLayers, &b_muon1_trackerLayers);
   fChain->SetBranchAddress("matchedgenMu1_pt", &matchedgenMu1_pt, &b_matchedgenMu1_pt);
   fChain->SetBranchAddress("muon2_trackerLayers", &muon2_trackerLayers, &b_muon2_trackerLayers);
   fChain->SetBranchAddress("matchedgenMu2_pt", &matchedgenMu2_pt, &b_matchedgenMu2_pt);
   fChain->SetBranchAddress("j1metPhi", &j1metPhi, &b_j1metPhi);
   fChain->SetBranchAddress("j1metPhi_f", &j1metPhi_f, &b_j1metPhi_f);
   fChain->SetBranchAddress("j2metPhi", &j2metPhi, &b_j2metPhi);
   fChain->SetBranchAddress("j2metPhi_f", &j2metPhi_f, &b_j2metPhi_f);
   fChain->SetBranchAddress("MET_et", &MET_et, &b_MET_et);
   fChain->SetBranchAddress("MET_phi", &MET_phi, &b_MET_phi);
   fChain->SetBranchAddress("HLT_Ele1", &HLT_Ele1, &b_HLT_Ele1);
   fChain->SetBranchAddress("HLT_Ele2", &HLT_Ele2, &b_HLT_Ele2);
   fChain->SetBranchAddress("HLT_Ele3", &HLT_Ele3, &b_HLT_Ele3);
   fChain->SetBranchAddress("HLT_Ele4", &HLT_Ele4, &b_HLT_Ele4);
   fChain->SetBranchAddress("HLT_Ele5", &HLT_Ele5, &b_HLT_Ele5);
   fChain->SetBranchAddress("HLT_Ele6", &HLT_Ele6, &b_HLT_Ele6);
   fChain->SetBranchAddress("HLT_Ele7", &HLT_Ele7, &b_HLT_Ele7);
   fChain->SetBranchAddress("HLT_Mu1", &HLT_Mu1, &b_HLT_Mu1);
   fChain->SetBranchAddress("HLT_Mu2", &HLT_Mu2, &b_HLT_Mu2);
   fChain->SetBranchAddress("HLT_Mu3", &HLT_Mu3, &b_HLT_Mu3);
   fChain->SetBranchAddress("HLT_Mu4", &HLT_Mu4, &b_HLT_Mu4);
   fChain->SetBranchAddress("HLT_Mu5", &HLT_Mu5, &b_HLT_Mu5);
   fChain->SetBranchAddress("HLT_Mu6", &HLT_Mu6, &b_HLT_Mu6);
   fChain->SetBranchAddress("HLT_Mu7", &HLT_Mu7, &b_HLT_Mu7);
   fChain->SetBranchAddress("HLT_Mu8", &HLT_Mu8, &b_HLT_Mu8);
   fChain->SetBranchAddress("HLT_Mu9", &HLT_Mu9, &b_HLT_Mu9);
   fChain->SetBranchAddress("HLT_Mu10", &HLT_Mu10, &b_HLT_Mu10);
   fChain->SetBranchAddress("HLT_Mu11", &HLT_Mu11, &b_HLT_Mu11);
   fChain->SetBranchAddress("passFilter_HBHE", &passFilter_HBHE, &b_passFilter_HBHE_);
   fChain->SetBranchAddress("passFilter_HBHEIso", &passFilter_HBHEIso, &b_passFilter_HBHEIso_);
   fChain->SetBranchAddress("passFilter_globalTightHalo", &passFilter_globalTightHalo, &b_passFilter_globalTightHalo_);
   fChain->SetBranchAddress("passFilter_ECALDeadCell", &passFilter_ECALDeadCell, &b_passFilter_ECALDeadCell_);
   fChain->SetBranchAddress("passFilter_GoodVtx", &passFilter_GoodVtx, &b_passFilter_GoodVtx);
   fChain->SetBranchAddress("passFilter_EEBadSc", &passFilter_EEBadSc, &b_passFilter_EEBadSc);
   fChain->SetBranchAddress("passFilter_badMuon", &passFilter_badMuon, &b_passFilter_badMuon);
   fChain->SetBranchAddress("passFilter_badChargedHadron", &passFilter_badChargedHadron, &b_passFilter_badChargedHadron_);
   fChain->SetBranchAddress("passFilter_MetbadMuon", &passFilter_MetbadMuon, &b_passFilter_MetbadMuon_);
   fChain->SetBranchAddress("passFilter_duplicateMuon", &passFilter_duplicateMuon, &b_passFilter_duplicateMuon_);
   fChain->SetBranchAddress("lumiWeight", &lumiWeight, &b_lumiWeight);
   fChain->SetBranchAddress("pileupWeight", &pileupWeight, &b_pileupWeight);
   fChain->SetBranchAddress("lep1_eta_station2", &lep1_eta_station2, &b_lep1_eta_station2);
   fChain->SetBranchAddress("lep1_phi_station2", &lep1_phi_station2, &b_lep1_phi_station2);
   fChain->SetBranchAddress("lep1_sign", &lep1_sign, &b_lep1_sign);
   fChain->SetBranchAddress("lep2_eta_station2", &lep2_eta_station2, &b_lep2_eta_station2);
   fChain->SetBranchAddress("lep2_phi_station2", &lep2_phi_station2, &b_lep2_phi_station2);
   fChain->SetBranchAddress("lep2_sign", &lep2_sign, &b_lep2_sign);
   fChain->SetBranchAddress("lhe_ele1_px", &lhe_ele1_px, &b_lhe_ele1_px);
   fChain->SetBranchAddress("lhe_ele1_py", &lhe_ele1_py, &b_lhe_ele1_py);
   fChain->SetBranchAddress("lhe_ele1_pz", &lhe_ele1_pz, &b_lhe_ele1_pz);
   fChain->SetBranchAddress("lhe_ele1_e", &lhe_ele1_e, &b_lhe_ele1_e);
   fChain->SetBranchAddress("lhe_ele2_px", &lhe_ele2_px, &b_lhe_ele2_px);
   fChain->SetBranchAddress("lhe_ele2_py", &lhe_ele2_py, &b_lhe_ele2_py);
   fChain->SetBranchAddress("lhe_ele2_pz", &lhe_ele2_pz, &b_lhe_ele2_pz);
   fChain->SetBranchAddress("lhe_ele2_e", &lhe_ele2_e, &b_lhe_ele2_e);
   fChain->SetBranchAddress("lhe_mu1_px", &lhe_mu1_px, &b_lhe_mu1_px);
   fChain->SetBranchAddress("lhe_mu1_py", &lhe_mu1_py, &b_lhe_mu1_py);
   fChain->SetBranchAddress("lhe_mu1_pz", &lhe_mu1_pz, &b_lhe_mu1_pz);
   fChain->SetBranchAddress("lhe_mu1_e", &lhe_mu1_e, &b_lhe_mu1_e);
   fChain->SetBranchAddress("lhe_mu2_px", &lhe_mu2_px, &b_lhe_mu2_px);
   fChain->SetBranchAddress("lhe_mu2_py", &lhe_mu2_py, &b_lhe_mu2_py);
   fChain->SetBranchAddress("lhe_mu2_pz", &lhe_mu2_pz, &b_lhe_mu2_pz);
   fChain->SetBranchAddress("lhe_mu2_e", &lhe_mu2_e, &b_lhe_mu2_e);
   fChain->SetBranchAddress("lhe_jet1_px", &lhe_jet1_px, &b_lhe_jet1_px);
   fChain->SetBranchAddress("lhe_jet1_py", &lhe_jet1_py, &b_lhe_jet1_py);
   fChain->SetBranchAddress("lhe_jet1_pz", &lhe_jet1_pz, &b_lhe_jet1_pz);
   fChain->SetBranchAddress("lhe_jet1_e", &lhe_jet1_e, &b_lhe_jet1_e);
   fChain->SetBranchAddress("lhe_jet2_px", &lhe_jet2_px, &b_lhe_jet2_px);
   fChain->SetBranchAddress("lhe_jet2_py", &lhe_jet2_py, &b_lhe_jet2_py);
   fChain->SetBranchAddress("lhe_jet2_pz", &lhe_jet2_pz, &b_lhe_jet2_pz);
   fChain->SetBranchAddress("lhe_jet2_e", &lhe_jet2_e, &b_lhe_jet2_e);
   fChain->SetBranchAddress("lhe_photon_px", &lhe_photon_px, &b_lhe_photon_px);
   fChain->SetBranchAddress("lhe_photon_py", &lhe_photon_py, &b_lhe_photon_py);
   fChain->SetBranchAddress("lhe_photon_pz", &lhe_photon_pz, &b_lhe_photon_pz);
   fChain->SetBranchAddress("lhe_photon_e", &lhe_photon_e, &b_lhe_photon_e);
   Notify();
}

Bool_t MakeTemplate::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MakeTemplate::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
void MakeTemplate::endJob(TString name) {
   fout->cd();
   newtree->Write();
   fout->Close();
   delete fout;
   if(name.Contains("outZA"))   {f1->Close();delete f1;} 
   if(name.Contains("outZJets")){f2->Close();delete f2;} 
   if(name.Contains("outDMuon")){f3->Close();f4->Close();delete f3;delete f4;}
   cout<<"========end JOB========"<<endl;
  }


Int_t MakeTemplate::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MakeTemplate_cxx
