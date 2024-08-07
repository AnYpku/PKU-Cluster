//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Feb 14 18:15:19 2020 by ROOT version 6.12/07
// from TChain treeDumper/ZPKUCandidates/
//////////////////////////////////////////////////////////

#ifndef ee_h
#define ee_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
//#include <vector>
// Header file for the classes stored in the TTree if any.
#include "vector"
#include <TLorentzVector.h>
using namespace std;
class ee {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
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
   Double_t        Mla2;
   Double_t        Mva;
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
   Double_t        photoneta;
   Double_t        photonphi;
   Double_t        photone;
   Double_t        photonsieie;
   Double_t        photonphoiso;
   Double_t        photonchiso;
   Double_t        photonnhiso;
   Int_t           iphoton;
   Double_t        drla;
   Double_t        drla2;
   Int_t           isTrue;
   Int_t           isprompt;
   Double_t        ak4jet_pt_old[6];
   Double_t        ak4jet_pt_new[6];
   Double_t        ak4jet_pt_JEC_up[6];
   Double_t        ak4jet_pt_JEC_down[6];
   Double_t        ak4jet_pt_JER_up[6];
   Double_t        ak4jet_pt_JER_down[6];
   Double_t        ak4jet_eta[6];
   Double_t        ak4jet_phi[6];
   Double_t        ak4jet_e_old[6];
   Double_t        ak4jet_e_new[6];
   Double_t        ak4jet_e_JEC_up[6];
   Double_t        ak4jet_e_JEC_down[6];
   Double_t        ak4jet_e_JER_up[6];
   Double_t        ak4jet_e_JER_down[6];
   Double_t        ak4jet_csv[6];
   Double_t        ak4jet_icsv[6];
   Double_t        jet1pt;
   Double_t        jet1pt_new;
   Double_t        jet1pt_JEC_up;
   Double_t        jet1pt_JER_up;
   Double_t        jet1pt_JEC_down;
   Double_t        jet1pt_JER_down;
   Double_t        jet1eta;
   Double_t        jet1eta_new;
   Double_t        jet1eta_JEC_up;
   Double_t        jet1eta_JEC_down;
   Double_t        jet1eta_JER_up;
   Double_t        jet1eta_JER_down;
   Double_t        jet1phi;
   Double_t        jet1phi_new;
   Double_t        jet1phi_JEC_up;
   Double_t        jet1phi_JEC_down;
   Double_t        jet1phi_JER_up;
   Double_t        jet1phi_JER_down;
   Double_t        jet1e;
   Double_t        jet1e_new;
   Double_t        jet1e_JEC_up;
   Double_t        jet1e_JER_up;
   Double_t        jet1e_JEC_down;
   Double_t        jet1e_JER_down;
   Double_t        jet1csv;
   Double_t        jet1csv_new;
   Double_t        jet1csv_JEC_up;
   Double_t        jet1csv_JER_up;
   Double_t        jet1csv_JEC_down;
   Double_t        jet1csv_JER_down;
   Double_t        jet1icsv;
   Double_t        jet1icsv_new;
   Double_t        jet1icsv_JEC_up;
   Double_t        jet1icsv_JER_up;
   Double_t        jet1icsv_JEC_down;
   Double_t        jet1icsv_JER_down;
   Double_t        jet2pt;
   Double_t        jet2pt_new;
   Double_t        jet2pt_JEC_up;
   Double_t        jet2pt_JER_up;
   Double_t        jet2pt_JEC_down;
   Double_t        jet2pt_JER_down;
   Double_t        jet2eta;
   Double_t        jet2eta_new;
   Double_t        jet2eta_JEC_up;
   Double_t        jet2eta_JEC_down;
   Double_t        jet2eta_JER_up;
   Double_t        jet2eta_JER_down;
   Double_t        jet2phi;
   Double_t        jet2phi_new;
   Double_t        jet2phi_JEC_up;
   Double_t        jet2phi_JEC_down;
   Double_t        jet2phi_JER_up;
   Double_t        jet2phi_JER_down;
   Double_t        jet2e;
   Double_t        jet2e_new;
   Double_t        jet2e_JEC_up;
   Double_t        jet2e_JER_up;
   Double_t        jet2e_JEC_down;
   Double_t        jet2e_JER_down;
   Double_t        jet2csv;
   Double_t        jet2csv_new;
   Double_t        jet2csv_JEC_up;
   Double_t        jet2csv_JER_up;
   Double_t        jet2csv_JEC_down;
   Double_t        jet2csv_JER_down;
   Double_t        jet2icsv;
   Double_t        jet2icsv_new;
   Double_t        jet2icsv_JEC_up;
   Double_t        jet2icsv_JER_up;
   Double_t        jet2icsv_JEC_down;
   Double_t        jet2icsv_JER_down;
   Double_t        drj1a;
   Double_t        drj1a_new;
   Double_t        drj1a_JEC_up;
   Double_t        drj1a_JEC_down;
   Double_t        drj1a_JER_up;
   Double_t        drj1a_JER_down;
   Double_t        drj2a;
   Double_t        drj2a_new;
   Double_t        drj2a_JEC_up;
   Double_t        drj2a_JEC_down;
   Double_t        drj2a_JER_up;
   Double_t        drj2a_JER_down;
   Double_t        drj1l;
   Double_t        drj1l_new;
   Double_t        drj1l_JEC_up;
   Double_t        drj1l_JEC_down;
   Double_t        drj1l_JER_up;
   Double_t        drj1l_JER_down;
   Double_t        drj2l;
   Double_t        drj2l_new;
   Double_t        drj2l_JEC_up;
   Double_t        drj2l_JEC_down;
   Double_t        drj2l_JER_up;
   Double_t        drj2l_JER_down;
   Double_t        drj1l2;
   Double_t        drj1l2_new;
   Double_t        drj1l2_JEC_up;
   Double_t        drj1l2_JEC_down;
   Double_t        drj1l2_JER_up;
   Double_t        drj1l2_JER_down;
   Double_t        drj2l2;
   Double_t        drj2l2_new;
   Double_t        drj2l2_JEC_up;
   Double_t        drj2l2_JEC_down;
   Double_t        drj2l2_JER_up;
   Double_t        drj2l2_JER_down;
   Double_t        Mjj;
   Double_t        Mjj_new;
   Double_t        Mjj_JEC_up;
   Double_t        Mjj_JEC_down;
   Double_t        Mjj_JER_up;
   Double_t        Mjj_JER_down;
   Double_t        deltaeta;
   Double_t        deltaeta_new;
   Double_t        deltaeta_JEC_up;
   Double_t        deltaeta_JEC_down;
   Double_t        deltaeta_JER_up;
   Double_t        deltaeta_JER_down;
   Double_t        zepp;
   Double_t        zepp_new;
   Double_t        zepp_JEC_up;
   Double_t        zepp_JEC_down;
   Double_t        zepp_JER_up;
   Double_t        zepp_JER_down;
   Double_t        ptlep1;
   Double_t        etalep1;
   Double_t        philep1;
   Double_t        ptlep2;
   Double_t        etalep2;
   Double_t        philep2;
   Double_t        MET_et;
   Double_t        MET_et_new;
   Double_t        MET_et_JEC_up;
   Double_t        MET_et_JEC_down;
   Double_t        MET_et_JER_up;
   Double_t        MET_et_JER_down;
   Double_t        MET_phi;
   Double_t        MET_phi_new;
   Double_t        MET_phi_JEC_up;
   Double_t        MET_phi_JEC_down;
   Double_t        MET_phi_JER_up;
   Double_t        MET_phi_JER_down;
   Int_t           HLT_Ele1;
   Int_t           HLT_Ele2;
   Int_t           HLT_Mu1;
   Int_t           HLT_Mu2;
   Int_t           HLT_Mu3;
   Int_t           HLT_Mu4;
   Int_t           HLT_Mu5;
   Int_t           HLT_Mu6;
   Double_t        lumiWeight;
   Double_t        pileupWeight;
   Double_t        lep1_eta_station2;
   Double_t        lep1_phi_station2;
   Int_t           lep1_sign;
   Double_t        lep2_eta_station2;
   Double_t        lep2_phi_station2;
   Int_t           lep2_sign;
   Double_t        prefWeight;
   Double_t        prefWeightUp;
   Double_t        prefWeightDown;
   vector<double>  *jet1pt_unc_up;
   vector<double>  *jet1eta_unc_up;
   vector<double>  *jet1phi_unc_up;
   vector<double>  *jet1e_unc_up;
   vector<double>  *jet2pt_unc_up;
   vector<double>  *jet2eta_unc_up;
   vector<double>  *jet2phi_unc_up;
   vector<double>  *jet2e_unc_up;
   vector<double>  *jet1pt_unc_down;
   vector<double>  *jet1eta_unc_down;
   vector<double>  *jet1phi_unc_down;
   vector<double>  *jet1e_unc_down;
   vector<double>  *jet2pt_unc_down;
   vector<double>  *jet2eta_unc_down;
   vector<double>  *jet2phi_unc_down;
   vector<double>  *jet2e_unc_down;
   Double_t        jet1pt_val;
   Double_t        jet1e_val;
   Double_t        jet1eta_val;
   Double_t        jet1phi_val;
   Double_t        jet2pt_val;
   Double_t        jet2e_val;
   Double_t        jet2eta_val;
   Double_t        jet2phi_val;

   // List of branches
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
   TBranch        *b_Mla2;   //!
   TBranch        *b_Mva;   //!
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
   TBranch        *b_photoneta;   //!
   TBranch        *b_photonphi;   //!
   TBranch        *b_photone;   //!
   TBranch        *b_photonsieie;   //!
   TBranch        *b_photonphoiso;   //!
   TBranch        *b_photonchiso;   //!
   TBranch        *b_photonnhiso;   //!
   TBranch        *b_iphoton;   //!
   TBranch        *b_drla;   //!
   TBranch        *b_drla2;   //!
   TBranch        *b_isTrue;   //!
   TBranch        *b_isprompt;   //!
   TBranch        *b_ak4jet_pt_old;   //!
   TBranch        *b_ak4jet_pt_new;   //!
   TBranch        *b_ak4jet_pt_JEC_up;   //!
   TBranch        *b_ak4jet_pt_JEC_down;   //!
   TBranch        *b_ak4jet_pt_JER_up;   //!
   TBranch        *b_ak4jet_pt_JER_down;   //!
   TBranch        *b_ak4jet_eta;   //!
   TBranch        *b_ak4jet_phi;   //!
   TBranch        *b_ak4jet_e_old;   //!
   TBranch        *b_ak4jet_e_new;   //!
   TBranch        *b_ak4jet_e_JEC_up;   //!
   TBranch        *b_ak4jet_e_JEC_down;   //!
   TBranch        *b_ak4jet_e_JER_up;   //!
   TBranch        *b_ak4jet_e_JER_down;   //!
   TBranch        *b_ak4jet_csv;   //!
   TBranch        *b_ak4jet_icsv;   //!
   TBranch        *b_jet1pt;   //!
   TBranch        *b_jet1pt_new;   //!
   TBranch        *b_jet1pt_JEC_up;   //!
   TBranch        *b_jet1pt_JER_up;   //!
   TBranch        *b_jet1pt_JEC_down;   //!
   TBranch        *b_jet1pt_JER_down;   //!
   TBranch        *b_jet1eta;   //!
   TBranch        *b_jet1eta_new;   //!
   TBranch        *b_jet1eta_JEC_up;   //!
   TBranch        *b_jet1eta_JEC_down;   //!
   TBranch        *b_jet1eta_JER_up;   //!
   TBranch        *b_jet1eta_JER_down;   //!
   TBranch        *b_jet1phi;   //!
   TBranch        *b_jet1phi_new;   //!
   TBranch        *b_jet1phi_JEC_up;   //!
   TBranch        *b_jet1phi_JEC_down;   //!
   TBranch        *b_jet1phi_JER_up;   //!
   TBranch        *b_jet1phi_JER_down;   //!
   TBranch        *b_jet1e;   //!
   TBranch        *b_jet1e_new;   //!
   TBranch        *b_jet1e_JEC_up;   //!
   TBranch        *b_jet1e_JER_up;   //!
   TBranch        *b_jet1e_JEC_down;   //!
   TBranch        *b_jet1e_JER_down;   //!
   TBranch        *b_jet1csv;   //!
   TBranch        *b_jet1csv_new;   //!
   TBranch        *b_jet1csv_JEC_up;   //!
   TBranch        *b_jet1csv_JER_up;   //!
   TBranch        *b_jet1csv_JEC_down;   //!
   TBranch        *b_jet1csv_JER_down;   //!
   TBranch        *b_jet1icsv;   //!
   TBranch        *b_jet1icsv_new;   //!
   TBranch        *b_jet1icsv_JEC_up;   //!
   TBranch        *b_jet1icsv_JER_up;   //!
   TBranch        *b_jet1icsv_JEC_down;   //!
   TBranch        *b_jet1icsv_JER_down;   //!
   TBranch        *b_jet2pt;   //!
   TBranch        *b_jet2pt_new;   //!
   TBranch        *b_jet2pt_JEC_up;   //!
   TBranch        *b_jet2pt_JER_up;   //!
   TBranch        *b_jet2pt_JEC_down;   //!
   TBranch        *b_jet2pt_JER_down;   //!
   TBranch        *b_jet2eta;   //!
   TBranch        *b_jet2eta_new;   //!
   TBranch        *b_jet2eta_JEC_up;   //!
   TBranch        *b_jet2eta_JEC_down;   //!
   TBranch        *b_jet2eta_JER_up;   //!
   TBranch        *b_jet2eta_JER_down;   //!
   TBranch        *b_jet2phi;   //!
   TBranch        *b_jet2phi_new;   //!
   TBranch        *b_jet2phi_JEC_up;   //!
   TBranch        *b_jet2phi_JEC_down;   //!
   TBranch        *b_jet2phi_JER_up;   //!
   TBranch        *b_jet2phi_JER_down;   //!
   TBranch        *b_jet2e;   //!
   TBranch        *b_jet2e_new;   //!
   TBranch        *b_jet2e_JEC_up;   //!
   TBranch        *b_jet2e_JER_up;   //!
   TBranch        *b_jet2e_JEC_down;   //!
   TBranch        *b_jet2e_JER_down;   //!
   TBranch        *b_jet2csv;   //!
   TBranch        *b_jet2csv_new;   //!
   TBranch        *b_jet2csv_JEC_up;   //!
   TBranch        *b_jet2csv_JER_up;   //!
   TBranch        *b_jet2csv_JEC_down;   //!
   TBranch        *b_jet2csv_JER_down;   //!
   TBranch        *b_jet2icsv;   //!
   TBranch        *b_jet2icsv_new;   //!
   TBranch        *b_jet2icsv_JEC_up;   //!
   TBranch        *b_jet2icsv_JER_up;   //!
   TBranch        *b_jet2icsv_JEC_down;   //!
   TBranch        *b_jet2icsv_JER_down;   //!
   TBranch        *b_drj1a;   //!
   TBranch        *b_drj1a_new;   //!
   TBranch        *b_drj1a_JEC_up;   //!
   TBranch        *b_drj1a_JEC_down;   //!
   TBranch        *b_drj1a_JER_up;   //!
   TBranch        *b_drj1a_JER_down;   //!
   TBranch        *b_drj2a;   //!
   TBranch        *b_drj2a_new;   //!
   TBranch        *b_drj2a_JEC_up;   //!
   TBranch        *b_drj2a_JEC_down;   //!
   TBranch        *b_drj2a_JER_up;   //!
   TBranch        *b_drj2a_JER_down;   //!
   TBranch        *b_drj1l;   //!
   TBranch        *b_drj1l_new;   //!
   TBranch        *b_drj1l_JEC_up;   //!
   TBranch        *b_drj1l_JEC_down;   //!
   TBranch        *b_drj1l_JER_up;   //!
   TBranch        *b_drj1l_JER_down;   //!
   TBranch        *b_drj2l;   //!
   TBranch        *b_drj2l_new;   //!
   TBranch        *b_drj2l_JEC_up;   //!
   TBranch        *b_drj2l_JEC_down;   //!
   TBranch        *b_drj2l_JER_up;   //!
   TBranch        *b_drj2l_JER_down;   //!
   TBranch        *b_drj1l2;   //!
   TBranch        *b_drj1l2_new;   //!
   TBranch        *b_drj1l2_JEC_up;   //!
   TBranch        *b_drj1l2_JEC_down;   //!
   TBranch        *b_drj1l2_JER_up;   //!
   TBranch        *b_drj1l2_JER_down;   //!
   TBranch        *b_drj2l2;   //!
   TBranch        *b_drj2l2_new;   //!
   TBranch        *b_drj2l2_JEC_up;   //!
   TBranch        *b_drj2l2_JEC_down;   //!
   TBranch        *b_drj2l2_JER_up;   //!
   TBranch        *b_drj2l2_JER_down;   //!
   TBranch        *b_Mjj;   //!
   TBranch        *b_Mjj_new;   //!
   TBranch        *b_Mjj_JEC_up;   //!
   TBranch        *b_Mjj_JEC_down;   //!
   TBranch        *b_Mjj_JER_up;   //!
   TBranch        *b_Mjj_JER_down;   //!
   TBranch        *b_deltaeta;   //!
   TBranch        *b_deltaeta_new;   //!
   TBranch        *b_deltaeta_JEC_up;   //!
   TBranch        *b_deltaeta_JEC_down;   //!
   TBranch        *b_deltaeta_JER_up;   //!
   TBranch        *b_deltaeta_JER_down;   //!
   TBranch        *b_zepp;   //!
   TBranch        *b_zepp_new;   //!
   TBranch        *b_zepp_JEC_up;   //!
   TBranch        *b_zepp_JEC_down;   //!
   TBranch        *b_zepp_JER_up;   //!
   TBranch        *b_zepp_JER_down;   //!
   TBranch        *b_ptlep1;   //!
   TBranch        *b_etalep1;   //!
   TBranch        *b_philep1;   //!
   TBranch        *b_ptlep2;   //!
   TBranch        *b_etalep2;   //!
   TBranch        *b_philep2;   //!
   TBranch        *b_MET_et;   //!
   TBranch        *b_MET_et_new;   //!
   TBranch        *b_MET_et_JEC_up;   //!
   TBranch        *b_MET_et_JEC_down;   //!
   TBranch        *b_MET_et_JER_up;   //!
   TBranch        *b_MET_et_JER_down;   //!
   TBranch        *b_MET_phi;   //!
   TBranch        *b_MET_phi_new;   //!
   TBranch        *b_MET_phi_JEC_up;   //!
   TBranch        *b_MET_phi_JEC_down;   //!
   TBranch        *b_MET_phi_JER_up;   //!
   TBranch        *b_MET_phi_JER_down;   //!
   TBranch        *b_HLT_Ele1;   //!
   TBranch        *b_HLT_Ele2;   //!
   TBranch        *b_HLT_Mu1;   //!
   TBranch        *b_HLT_Mu2;   //!
   TBranch        *b_HLT_Mu3;   //!
   TBranch        *b_HLT_Mu4;   //!
   TBranch        *b_HLT_Mu5;   //!
   TBranch        *b_HLT_Mu6;   //!
   TBranch        *b_lumiWeight;   //!
   TBranch        *b_pileupWeight;   //!
   TBranch        *b_lep1_eta_station2;   //!
   TBranch        *b_lep1_phi_station2;   //!
   TBranch        *b_lep1_sign;   //!
   TBranch        *b_lep2_eta_station2;   //!
   TBranch        *b_lep2_phi_station2;   //!
   TBranch        *b_lep2_sign;   //!
   TBranch        *b_prefWeight;   //!
   TBranch        *b_prefWeightUp;   //!
   TBranch        *b_prefWeightDown;   //!
   TBranch        *b_jet1pt_unc_up;   //!
   TBranch        *b_jet1eta_unc_up;   //!
   TBranch        *b_jet1phi_unc_up;   //!
   TBranch        *b_jet1e_unc_up;   //!
   TBranch        *b_jet2pt_unc_up;   //!
   TBranch        *b_jet2eta_unc_up;   //!
   TBranch        *b_jet2phi_unc_up;   //!
   TBranch        *b_jet2e_unc_up;   //!
   TBranch        *b_jet1pt_unc_down;   //!
   TBranch        *b_jet1eta_unc_down;   //!
   TBranch        *b_jet1phi_unc_down;   //!
   TBranch        *b_jet1e_unc_down;   //!
   TBranch        *b_jet2pt_unc_down;   //!
   TBranch        *b_jet2eta_unc_down;   //!
   TBranch        *b_jet2phi_unc_down;   //!
   TBranch        *b_jet2e_unc_down;   //!
   TBranch        *b_jet1pt_val;   //!
   TBranch        *b_jet1e_val;   //!
   TBranch        *b_jet1eta_val;   //!
   TBranch        *b_jet1phi_val;   //!
   TBranch        *b_jet2pt_val;   //!
   TBranch        *b_jet2e_val;   //!
   TBranch        *b_jet2eta_val;   //!
   TBranch        *b_jet2phi_val;   //!

   TString m_dataset;
   ee(TTree *tree=0, TString dataset="");
   virtual ~ee();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Double_t delta_R(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2);
   virtual void     setValue();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void     endJob();

   vector<double> drj1a_up;
   vector<double> drj2a_up;
   vector<double> drj1l1_up;
   vector<double> drj1l2_up;
   vector<double> drj2l1_up;
   vector<double> drj2l2_up;
   vector<double> drj1a_down;
   vector<double> drj2a_down;
   vector<double> drj1l1_down;
   vector<double> drj1l2_down;
   vector<double> drj2l1_down;
   vector<double> drj2l2_down;

   vector<double> Mjj_up; vector<double> detajj_up;vector<double> zepp_up;vector<double> drjj_up;
   vector<double> Mjj_down;vector<double> detajj_down;vector<double> zepp_down;vector<double> drjj_down;
   vector<double> delta_phi_up;vector<double> delta_phi_down;
   double delta_phi;
   Int_t np,nm;

 private:
     TTree *ExTree;
     TFile *fout;
     double scalef;



};

#endif

#ifdef ee_cxx
ee::ee(TTree *tree,TString dataset) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("treeDumper/ZPKUCandidates",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("treeDumper/ZPKUCandidates","");
      chain->Add("ZA-EWK_2_186.root/treeDumper/ZPKUCandidates");
      chain->Add("ZA-EWK_2_187.root/treeDumper/ZPKUCandidates");
      chain->Add("ZA-EWK_2_188.root/treeDumper/ZPKUCandidates");
      tree = chain;
#endif // SINGLE_TREE

   }
   m_dataset=dataset;
   Init(tree);
}

ee::~ee()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t ee::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t ee::LoadTree(Long64_t entry)
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

void ee::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   jet1pt_unc_up = 0;
   jet1eta_unc_up = 0;
   jet1phi_unc_up = 0;
   jet1e_unc_up = 0;
   jet2pt_unc_up = 0;
   jet2eta_unc_up = 0;
   jet2phi_unc_up = 0;
   jet2e_unc_up = 0;
   jet1pt_unc_down = 0;
   jet1eta_unc_down = 0;
   jet1phi_unc_down = 0;
   jet1e_unc_down = 0;
   jet2pt_unc_down = 0;
   jet2eta_unc_down = 0;
   jet2phi_unc_down = 0;
   jet2e_unc_down = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fout = new TFile(m_dataset, "RECREATE");
   ExTree = fChain->CloneTree(0);

   ExTree->Branch("scalef",&scalef,"scalef/D");
   ExTree->Branch("drj1a_up",&drj1a_up);
   ExTree->Branch("drj1l1_up",&drj1l1_up);
   ExTree->Branch("drj1l2_up",&drj1l2_up);
   ExTree->Branch("drj2l1_up",&drj2l1_up);
   ExTree->Branch("drj2l2_up",&drj2l2_up);

   ExTree->Branch("drj1a_down", &drj1a_down);
   ExTree->Branch("drj1l1_down",&drj1l1_down);
   ExTree->Branch("drj1l2_down",&drj1l2_down);
   ExTree->Branch("drj2l1_down",&drj2l1_down);
   ExTree->Branch("drj2l2_down",&drj2l2_down);
   
   ExTree->Branch("drjj_up",&drjj_up);
   ExTree->Branch("zepp_up",&zepp_up);
   ExTree->Branch("delta_phi_up",&delta_phi_up);
   ExTree->Branch("Mjj_up",&Mjj_up);
   ExTree->Branch("detajj_up",&detajj_up);

   ExTree->Branch("drjj_down",&drjj_down);
   ExTree->Branch("zepp_down",&zepp_down);
   ExTree->Branch("delta_phi_down",&delta_phi_down);
   ExTree->Branch("Mjj_down",&Mjj_down);
   ExTree->Branch("detajj_down",&detajj_down);
   
   ExTree->Branch("delta_phi",&delta_phi,"delta_phi/D");
   ExTree->Branch("nm",&nm,"nm/I");
   ExTree->Branch("np",&np,"np/I");
   
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
   fChain->SetBranchAddress("Mla2", &Mla2, &b_Mla2);
   fChain->SetBranchAddress("Mva", &Mva, &b_Mva);
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
   fChain->SetBranchAddress("photoneta", &photoneta, &b_photoneta);
   fChain->SetBranchAddress("photonphi", &photonphi, &b_photonphi);
   fChain->SetBranchAddress("photone", &photone, &b_photone);
   fChain->SetBranchAddress("photonsieie", &photonsieie, &b_photonsieie);
   fChain->SetBranchAddress("photonphoiso", &photonphoiso, &b_photonphoiso);
   fChain->SetBranchAddress("photonchiso", &photonchiso, &b_photonchiso);
   fChain->SetBranchAddress("photonnhiso", &photonnhiso, &b_photonnhiso);
   fChain->SetBranchAddress("iphoton", &iphoton, &b_iphoton);
   fChain->SetBranchAddress("drla", &drla, &b_drla);
   fChain->SetBranchAddress("drla2", &drla2, &b_drla2);
   fChain->SetBranchAddress("isTrue", &isTrue, &b_isTrue);
   fChain->SetBranchAddress("isprompt", &isprompt, &b_isprompt);
   fChain->SetBranchAddress("ak4jet_pt_old", ak4jet_pt_old, &b_ak4jet_pt_old);
   fChain->SetBranchAddress("ak4jet_pt_new", ak4jet_pt_new, &b_ak4jet_pt_new);
   fChain->SetBranchAddress("ak4jet_pt_JEC_up", ak4jet_pt_JEC_up, &b_ak4jet_pt_JEC_up);
   fChain->SetBranchAddress("ak4jet_pt_JEC_down", ak4jet_pt_JEC_down, &b_ak4jet_pt_JEC_down);
   fChain->SetBranchAddress("ak4jet_pt_JER_up", ak4jet_pt_JER_up, &b_ak4jet_pt_JER_up);
   fChain->SetBranchAddress("ak4jet_pt_JER_down", ak4jet_pt_JER_down, &b_ak4jet_pt_JER_down);
   fChain->SetBranchAddress("ak4jet_eta", ak4jet_eta, &b_ak4jet_eta);
   fChain->SetBranchAddress("ak4jet_phi", ak4jet_phi, &b_ak4jet_phi);
   fChain->SetBranchAddress("ak4jet_e_old", ak4jet_e_old, &b_ak4jet_e_old);
   fChain->SetBranchAddress("ak4jet_e_new", ak4jet_e_new, &b_ak4jet_e_new);
   fChain->SetBranchAddress("ak4jet_e_JEC_up", ak4jet_e_JEC_up, &b_ak4jet_e_JEC_up);
   fChain->SetBranchAddress("ak4jet_e_JEC_down", ak4jet_e_JEC_down, &b_ak4jet_e_JEC_down);
   fChain->SetBranchAddress("ak4jet_e_JER_up", ak4jet_e_JER_up, &b_ak4jet_e_JER_up);
   fChain->SetBranchAddress("ak4jet_e_JER_down", ak4jet_e_JER_down, &b_ak4jet_e_JER_down);
   fChain->SetBranchAddress("ak4jet_csv", ak4jet_csv, &b_ak4jet_csv);
   fChain->SetBranchAddress("ak4jet_icsv", ak4jet_icsv, &b_ak4jet_icsv);
   fChain->SetBranchAddress("jet1pt", &jet1pt, &b_jet1pt);
   fChain->SetBranchAddress("jet1pt_new", &jet1pt_new, &b_jet1pt_new);
   fChain->SetBranchAddress("jet1pt_JEC_up", &jet1pt_JEC_up, &b_jet1pt_JEC_up);
   fChain->SetBranchAddress("jet1pt_JER_up", &jet1pt_JER_up, &b_jet1pt_JER_up);
   fChain->SetBranchAddress("jet1pt_JEC_down", &jet1pt_JEC_down, &b_jet1pt_JEC_down);
   fChain->SetBranchAddress("jet1pt_JER_down", &jet1pt_JER_down, &b_jet1pt_JER_down);
   fChain->SetBranchAddress("jet1eta", &jet1eta, &b_jet1eta);
   fChain->SetBranchAddress("jet1eta_new", &jet1eta_new, &b_jet1eta_new);
   fChain->SetBranchAddress("jet1eta_JEC_up", &jet1eta_JEC_up, &b_jet1eta_JEC_up);
   fChain->SetBranchAddress("jet1eta_JEC_down", &jet1eta_JEC_down, &b_jet1eta_JEC_down);
   fChain->SetBranchAddress("jet1eta_JER_up", &jet1eta_JER_up, &b_jet1eta_JER_up);
   fChain->SetBranchAddress("jet1eta_JER_down", &jet1eta_JER_down, &b_jet1eta_JER_down);
   fChain->SetBranchAddress("jet1phi", &jet1phi, &b_jet1phi);
   fChain->SetBranchAddress("jet1phi_new", &jet1phi_new, &b_jet1phi_new);
   fChain->SetBranchAddress("jet1phi_JEC_up", &jet1phi_JEC_up, &b_jet1phi_JEC_up);
   fChain->SetBranchAddress("jet1phi_JEC_down", &jet1phi_JEC_down, &b_jet1phi_JEC_down);
   fChain->SetBranchAddress("jet1phi_JER_up", &jet1phi_JER_up, &b_jet1phi_JER_up);
   fChain->SetBranchAddress("jet1phi_JER_down", &jet1phi_JER_down, &b_jet1phi_JER_down);
   fChain->SetBranchAddress("jet1e", &jet1e, &b_jet1e);
   fChain->SetBranchAddress("jet1e_new", &jet1e_new, &b_jet1e_new);
   fChain->SetBranchAddress("jet1e_JEC_up", &jet1e_JEC_up, &b_jet1e_JEC_up);
   fChain->SetBranchAddress("jet1e_JER_up", &jet1e_JER_up, &b_jet1e_JER_up);
   fChain->SetBranchAddress("jet1e_JEC_down", &jet1e_JEC_down, &b_jet1e_JEC_down);
   fChain->SetBranchAddress("jet1e_JER_down", &jet1e_JER_down, &b_jet1e_JER_down);
   fChain->SetBranchAddress("jet1csv", &jet1csv, &b_jet1csv);
   fChain->SetBranchAddress("jet1csv_new", &jet1csv_new, &b_jet1csv_new);
   fChain->SetBranchAddress("jet1csv_JEC_up", &jet1csv_JEC_up, &b_jet1csv_JEC_up);
   fChain->SetBranchAddress("jet1csv_JER_up", &jet1csv_JER_up, &b_jet1csv_JER_up);
   fChain->SetBranchAddress("jet1csv_JEC_down", &jet1csv_JEC_down, &b_jet1csv_JEC_down);
   fChain->SetBranchAddress("jet1csv_JER_down", &jet1csv_JER_down, &b_jet1csv_JER_down);
   fChain->SetBranchAddress("jet1icsv", &jet1icsv, &b_jet1icsv);
   fChain->SetBranchAddress("jet1icsv_new", &jet1icsv_new, &b_jet1icsv_new);
   fChain->SetBranchAddress("jet1icsv_JEC_up", &jet1icsv_JEC_up, &b_jet1icsv_JEC_up);
   fChain->SetBranchAddress("jet1icsv_JER_up", &jet1icsv_JER_up, &b_jet1icsv_JER_up);
   fChain->SetBranchAddress("jet1icsv_JEC_down", &jet1icsv_JEC_down, &b_jet1icsv_JEC_down);
   fChain->SetBranchAddress("jet1icsv_JER_down", &jet1icsv_JER_down, &b_jet1icsv_JER_down);
   fChain->SetBranchAddress("jet2pt", &jet2pt, &b_jet2pt);
   fChain->SetBranchAddress("jet2pt_new", &jet2pt_new, &b_jet2pt_new);
   fChain->SetBranchAddress("jet2pt_JEC_up", &jet2pt_JEC_up, &b_jet2pt_JEC_up);
   fChain->SetBranchAddress("jet2pt_JER_up", &jet2pt_JER_up, &b_jet2pt_JER_up);
   fChain->SetBranchAddress("jet2pt_JEC_down", &jet2pt_JEC_down, &b_jet2pt_JEC_down);
   fChain->SetBranchAddress("jet2pt_JER_down", &jet2pt_JER_down, &b_jet2pt_JER_down);
   fChain->SetBranchAddress("jet2eta", &jet2eta, &b_jet2eta);
   fChain->SetBranchAddress("jet2eta_new", &jet2eta_new, &b_jet2eta_new);
   fChain->SetBranchAddress("jet2eta_JEC_up", &jet2eta_JEC_up, &b_jet2eta_JEC_up);
   fChain->SetBranchAddress("jet2eta_JEC_down", &jet2eta_JEC_down, &b_jet2eta_JEC_down);
   fChain->SetBranchAddress("jet2eta_JER_up", &jet2eta_JER_up, &b_jet2eta_JER_up);
   fChain->SetBranchAddress("jet2eta_JER_down", &jet2eta_JER_down, &b_jet2eta_JER_down);
   fChain->SetBranchAddress("jet2phi", &jet2phi, &b_jet2phi);
   fChain->SetBranchAddress("jet2phi_new", &jet2phi_new, &b_jet2phi_new);
   fChain->SetBranchAddress("jet2phi_JEC_up", &jet2phi_JEC_up, &b_jet2phi_JEC_up);
   fChain->SetBranchAddress("jet2phi_JEC_down", &jet2phi_JEC_down, &b_jet2phi_JEC_down);
   fChain->SetBranchAddress("jet2phi_JER_up", &jet2phi_JER_up, &b_jet2phi_JER_up);
   fChain->SetBranchAddress("jet2phi_JER_down", &jet2phi_JER_down, &b_jet2phi_JER_down);
   fChain->SetBranchAddress("jet2e", &jet2e, &b_jet2e);
   fChain->SetBranchAddress("jet2e_new", &jet2e_new, &b_jet2e_new);
   fChain->SetBranchAddress("jet2e_JEC_up", &jet2e_JEC_up, &b_jet2e_JEC_up);
   fChain->SetBranchAddress("jet2e_JER_up", &jet2e_JER_up, &b_jet2e_JER_up);
   fChain->SetBranchAddress("jet2e_JEC_down", &jet2e_JEC_down, &b_jet2e_JEC_down);
   fChain->SetBranchAddress("jet2e_JER_down", &jet2e_JER_down, &b_jet2e_JER_down);
   fChain->SetBranchAddress("jet2csv", &jet2csv, &b_jet2csv);
   fChain->SetBranchAddress("jet2csv_new", &jet2csv_new, &b_jet2csv_new);
   fChain->SetBranchAddress("jet2csv_JEC_up", &jet2csv_JEC_up, &b_jet2csv_JEC_up);
   fChain->SetBranchAddress("jet2csv_JER_up", &jet2csv_JER_up, &b_jet2csv_JER_up);
   fChain->SetBranchAddress("jet2csv_JEC_down", &jet2csv_JEC_down, &b_jet2csv_JEC_down);
   fChain->SetBranchAddress("jet2csv_JER_down", &jet2csv_JER_down, &b_jet2csv_JER_down);
   fChain->SetBranchAddress("jet2icsv", &jet2icsv, &b_jet2icsv);
   fChain->SetBranchAddress("jet2icsv_new", &jet2icsv_new, &b_jet2icsv_new);
   fChain->SetBranchAddress("jet2icsv_JEC_up", &jet2icsv_JEC_up, &b_jet2icsv_JEC_up);
   fChain->SetBranchAddress("jet2icsv_JER_up", &jet2icsv_JER_up, &b_jet2icsv_JER_up);
   fChain->SetBranchAddress("jet2icsv_JEC_down", &jet2icsv_JEC_down, &b_jet2icsv_JEC_down);
   fChain->SetBranchAddress("jet2icsv_JER_down", &jet2icsv_JER_down, &b_jet2icsv_JER_down);
   fChain->SetBranchAddress("drj1a", &drj1a, &b_drj1a);
   fChain->SetBranchAddress("drj1a_new", &drj1a_new, &b_drj1a_new);
   fChain->SetBranchAddress("drj1a_JEC_up", &drj1a_JEC_up, &b_drj1a_JEC_up);
   fChain->SetBranchAddress("drj1a_JEC_down", &drj1a_JEC_down, &b_drj1a_JEC_down);
   fChain->SetBranchAddress("drj1a_JER_up", &drj1a_JER_up, &b_drj1a_JER_up);
   fChain->SetBranchAddress("drj1a_JER_down", &drj1a_JER_down, &b_drj1a_JER_down);
   fChain->SetBranchAddress("drj2a", &drj2a, &b_drj2a);
   fChain->SetBranchAddress("drj2a_new", &drj2a_new, &b_drj2a_new);
   fChain->SetBranchAddress("drj2a_JEC_up", &drj2a_JEC_up, &b_drj2a_JEC_up);
   fChain->SetBranchAddress("drj2a_JEC_down", &drj2a_JEC_down, &b_drj2a_JEC_down);
   fChain->SetBranchAddress("drj2a_JER_up", &drj2a_JER_up, &b_drj2a_JER_up);
   fChain->SetBranchAddress("drj2a_JER_down", &drj2a_JER_down, &b_drj2a_JER_down);
   fChain->SetBranchAddress("drj1l", &drj1l, &b_drj1l);
   fChain->SetBranchAddress("drj1l_new", &drj1l_new, &b_drj1l_new);
   fChain->SetBranchAddress("drj1l_JEC_up", &drj1l_JEC_up, &b_drj1l_JEC_up);
   fChain->SetBranchAddress("drj1l_JEC_down", &drj1l_JEC_down, &b_drj1l_JEC_down);
   fChain->SetBranchAddress("drj1l_JER_up", &drj1l_JER_up, &b_drj1l_JER_up);
   fChain->SetBranchAddress("drj1l_JER_down", &drj1l_JER_down, &b_drj1l_JER_down);
   fChain->SetBranchAddress("drj2l", &drj2l, &b_drj2l);
   fChain->SetBranchAddress("drj2l_new", &drj2l_new, &b_drj2l_new);
   fChain->SetBranchAddress("drj2l_JEC_up", &drj2l_JEC_up, &b_drj2l_JEC_up);
   fChain->SetBranchAddress("drj2l_JEC_down", &drj2l_JEC_down, &b_drj2l_JEC_down);
   fChain->SetBranchAddress("drj2l_JER_up", &drj2l_JER_up, &b_drj2l_JER_up);
   fChain->SetBranchAddress("drj2l_JER_down", &drj2l_JER_down, &b_drj2l_JER_down);
   fChain->SetBranchAddress("drj1l2", &drj1l2, &b_drj1l2);
   fChain->SetBranchAddress("drj1l2_new", &drj1l2_new, &b_drj1l2_new);
   fChain->SetBranchAddress("drj1l2_JEC_up", &drj1l2_JEC_up, &b_drj1l2_JEC_up);
   fChain->SetBranchAddress("drj1l2_JEC_down", &drj1l2_JEC_down, &b_drj1l2_JEC_down);
   fChain->SetBranchAddress("drj1l2_JER_up", &drj1l2_JER_up, &b_drj1l2_JER_up);
   fChain->SetBranchAddress("drj1l2_JER_down", &drj1l2_JER_down, &b_drj1l2_JER_down);
   fChain->SetBranchAddress("drj2l2", &drj2l2, &b_drj2l2);
   fChain->SetBranchAddress("drj2l2_new", &drj2l2_new, &b_drj2l2_new);
   fChain->SetBranchAddress("drj2l2_JEC_up", &drj2l2_JEC_up, &b_drj2l2_JEC_up);
   fChain->SetBranchAddress("drj2l2_JEC_down", &drj2l2_JEC_down, &b_drj2l2_JEC_down);
   fChain->SetBranchAddress("drj2l2_JER_up", &drj2l2_JER_up, &b_drj2l2_JER_up);
   fChain->SetBranchAddress("drj2l2_JER_down", &drj2l2_JER_down, &b_drj2l2_JER_down);
   fChain->SetBranchAddress("Mjj", &Mjj, &b_Mjj);
   fChain->SetBranchAddress("Mjj_new", &Mjj_new, &b_Mjj_new);
   fChain->SetBranchAddress("Mjj_JEC_up", &Mjj_JEC_up, &b_Mjj_JEC_up);
   fChain->SetBranchAddress("Mjj_JEC_down", &Mjj_JEC_down, &b_Mjj_JEC_down);
   fChain->SetBranchAddress("Mjj_JER_up", &Mjj_JER_up, &b_Mjj_JER_up);
   fChain->SetBranchAddress("Mjj_JER_down", &Mjj_JER_down, &b_Mjj_JER_down);
   fChain->SetBranchAddress("deltaeta", &deltaeta, &b_deltaeta);
   fChain->SetBranchAddress("deltaeta_new", &deltaeta_new, &b_deltaeta_new);
   fChain->SetBranchAddress("deltaeta_JEC_up", &deltaeta_JEC_up, &b_deltaeta_JEC_up);
   fChain->SetBranchAddress("deltaeta_JEC_down", &deltaeta_JEC_down, &b_deltaeta_JEC_down);
   fChain->SetBranchAddress("deltaeta_JER_up", &deltaeta_JER_up, &b_deltaeta_JER_up);
   fChain->SetBranchAddress("deltaeta_JER_down", &deltaeta_JER_down, &b_deltaeta_JER_down);
   fChain->SetBranchAddress("zepp", &zepp, &b_zepp);
   fChain->SetBranchAddress("zepp_new", &zepp_new, &b_zepp_new);
   fChain->SetBranchAddress("zepp_JEC_up", &zepp_JEC_up, &b_zepp_JEC_up);
   fChain->SetBranchAddress("zepp_JEC_down", &zepp_JEC_down, &b_zepp_JEC_down);
   fChain->SetBranchAddress("zepp_JER_up", &zepp_JER_up, &b_zepp_JER_up);
   fChain->SetBranchAddress("zepp_JER_down", &zepp_JER_down, &b_zepp_JER_down);
   fChain->SetBranchAddress("ptlep1", &ptlep1, &b_ptlep1);
   fChain->SetBranchAddress("etalep1", &etalep1, &b_etalep1);
   fChain->SetBranchAddress("philep1", &philep1, &b_philep1);
   fChain->SetBranchAddress("ptlep2", &ptlep2, &b_ptlep2);
   fChain->SetBranchAddress("etalep2", &etalep2, &b_etalep2);
   fChain->SetBranchAddress("philep2", &philep2, &b_philep2);
   fChain->SetBranchAddress("MET_et", &MET_et, &b_MET_et);
   fChain->SetBranchAddress("MET_et_new", &MET_et_new, &b_MET_et_new);
   fChain->SetBranchAddress("MET_et_JEC_up", &MET_et_JEC_up, &b_MET_et_JEC_up);
   fChain->SetBranchAddress("MET_et_JEC_down", &MET_et_JEC_down, &b_MET_et_JEC_down);
   fChain->SetBranchAddress("MET_et_JER_up", &MET_et_JER_up, &b_MET_et_JER_up);
   fChain->SetBranchAddress("MET_et_JER_down", &MET_et_JER_down, &b_MET_et_JER_down);
   fChain->SetBranchAddress("MET_phi", &MET_phi, &b_MET_phi);
   fChain->SetBranchAddress("MET_phi_new", &MET_phi_new, &b_MET_phi_new);
   fChain->SetBranchAddress("MET_phi_JEC_up", &MET_phi_JEC_up, &b_MET_phi_JEC_up);
   fChain->SetBranchAddress("MET_phi_JEC_down", &MET_phi_JEC_down, &b_MET_phi_JEC_down);
   fChain->SetBranchAddress("MET_phi_JER_up", &MET_phi_JER_up, &b_MET_phi_JER_up);
   fChain->SetBranchAddress("MET_phi_JER_down", &MET_phi_JER_down, &b_MET_phi_JER_down);
   fChain->SetBranchAddress("HLT_Ele1", &HLT_Ele1, &b_HLT_Ele1);
   fChain->SetBranchAddress("HLT_Ele2", &HLT_Ele2, &b_HLT_Ele2);
   fChain->SetBranchAddress("HLT_Mu1", &HLT_Mu1, &b_HLT_Mu1);
   fChain->SetBranchAddress("HLT_Mu2", &HLT_Mu2, &b_HLT_Mu2);
   fChain->SetBranchAddress("HLT_Mu3", &HLT_Mu3, &b_HLT_Mu3);
   fChain->SetBranchAddress("HLT_Mu4", &HLT_Mu4, &b_HLT_Mu4);
   fChain->SetBranchAddress("HLT_Mu5", &HLT_Mu5, &b_HLT_Mu5);
   fChain->SetBranchAddress("HLT_Mu6", &HLT_Mu6, &b_HLT_Mu6);
   fChain->SetBranchAddress("lumiWeight", &lumiWeight, &b_lumiWeight);
   fChain->SetBranchAddress("pileupWeight", &pileupWeight, &b_pileupWeight);
   fChain->SetBranchAddress("lep1_eta_station2", &lep1_eta_station2, &b_lep1_eta_station2);
   fChain->SetBranchAddress("lep1_phi_station2", &lep1_phi_station2, &b_lep1_phi_station2);
   fChain->SetBranchAddress("lep1_sign", &lep1_sign, &b_lep1_sign);
   fChain->SetBranchAddress("lep2_eta_station2", &lep2_eta_station2, &b_lep2_eta_station2);
   fChain->SetBranchAddress("lep2_phi_station2", &lep2_phi_station2, &b_lep2_phi_station2);
   fChain->SetBranchAddress("lep2_sign", &lep2_sign, &b_lep2_sign);
   fChain->SetBranchAddress("prefWeight", &prefWeight, &b_prefWeight);
   fChain->SetBranchAddress("prefWeightUp", &prefWeightUp, &b_prefWeightUp);
   fChain->SetBranchAddress("prefWeightDown", &prefWeightDown, &b_prefWeightDown);
   fChain->SetBranchAddress("jet1pt_unc_up", &jet1pt_unc_up, &b_jet1pt_unc_up);
   fChain->SetBranchAddress("jet1eta_unc_up", &jet1eta_unc_up, &b_jet1eta_unc_up);
   fChain->SetBranchAddress("jet1phi_unc_up", &jet1phi_unc_up, &b_jet1phi_unc_up);
   fChain->SetBranchAddress("jet1e_unc_up", &jet1e_unc_up, &b_jet1e_unc_up);
   fChain->SetBranchAddress("jet2pt_unc_up", &jet2pt_unc_up, &b_jet2pt_unc_up);
   fChain->SetBranchAddress("jet2eta_unc_up", &jet2eta_unc_up, &b_jet2eta_unc_up);
   fChain->SetBranchAddress("jet2phi_unc_up", &jet2phi_unc_up, &b_jet2phi_unc_up);
   fChain->SetBranchAddress("jet2e_unc_up", &jet2e_unc_up, &b_jet2e_unc_up);
   fChain->SetBranchAddress("jet1pt_unc_down", &jet1pt_unc_down, &b_jet1pt_unc_down);
   fChain->SetBranchAddress("jet1eta_unc_down", &jet1eta_unc_down, &b_jet1eta_unc_down);
   fChain->SetBranchAddress("jet1phi_unc_down", &jet1phi_unc_down, &b_jet1phi_unc_down);
   fChain->SetBranchAddress("jet1e_unc_down", &jet1e_unc_down, &b_jet1e_unc_down);
   fChain->SetBranchAddress("jet2pt_unc_down", &jet2pt_unc_down, &b_jet2pt_unc_down);
   fChain->SetBranchAddress("jet2eta_unc_down", &jet2eta_unc_down, &b_jet2eta_unc_down);
   fChain->SetBranchAddress("jet2phi_unc_down", &jet2phi_unc_down, &b_jet2phi_unc_down);
   fChain->SetBranchAddress("jet2e_unc_down", &jet2e_unc_down, &b_jet2e_unc_down);
//   fChain->SetBranchAddress("jet1pt_val", &jet1pt_val, &b_jet1pt_val);
//   fChain->SetBranchAddress("jet1e_val", &jet1e_val, &b_jet1e_val);
//   fChain->SetBranchAddress("jet1eta_val", &jet1eta_val, &b_jet1eta_val);
//   fChain->SetBranchAddress("jet1phi_val", &jet1phi_val, &b_jet1phi_val);
//   fChain->SetBranchAddress("jet2pt_val", &jet2pt_val, &b_jet2pt_val);
//   fChain->SetBranchAddress("jet2e_val", &jet2e_val, &b_jet2e_val);
//   fChain->SetBranchAddress("jet2eta_val", &jet2eta_val, &b_jet2eta_val);
//   fChain->SetBranchAddress("jet2phi_val", &jet2phi_val, &b_jet2phi_val);
   Notify();
}

Bool_t ee::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void ee::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t ee::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
void ee::endJob() {
     fout->cd();
     ExTree->Write();
     fout->Write();
     fout->Close();
     delete fout;
  }



#endif // #ifdef ee_cxx
