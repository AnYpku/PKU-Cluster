// calculate JEC and JER uncertainty, only for signal sample
#include <iostream>
#include "TFile.h"
#include "TBranch.h"
#include "TChain.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TH1D.h"

double large(double a1, double a2){
        if(a1>a2) return a1;
        else return a2;
        }

void Jecr(){
	double Pi = 3.141593;
	TString dir = "/home/pku/anying/cms/file_in_cms/files_weighted/";
//	TString filename = "outJEC-ZA-EWK_meng.root";
	TString filename = "outZA-EWK_JEC_meng.root";

	TFile *output = new TFile("output.root", "RECREATE");

	TFile *infile = TFile::Open(dir+filename);
	TTree *fChain = (TTree*)infile->Get("demo");

	Double_t scalef;
	Int_t nVtx;
	Double_t theWeight;
	Double_t lumiWeight;
	Double_t pileupWeight;
	Int_t HLT_Ele1;
	Int_t HLT_Mu2;
	Int_t HLT_Mu5;
	Double_t nump;
	Double_t numm;
	Double_t npT;
	Int_t lep;
	Int_t run_period;
	Double_t ptVlep;
	Double_t yVlep;
	Double_t phiVlep;
	Double_t massVlep;
	Double_t ptlep1;
	Double_t etalep1;
	Double_t philep1;
	Double_t ptlep2;
	Double_t etalep2;
	Double_t philep2;
	Double_t drla;
	Double_t drla2;
	Double_t drj1a;
	Double_t drj1a_new;
	Double_t drj1a_JEC_up;
	Double_t drj1a_JEC_down;
	Double_t drj1a_JER_up;
	Double_t drj1a_JER_down;
	Double_t drj2a;
	Double_t drj2a_new;
	Double_t drj2a_JEC_up;
	Double_t drj2a_JEC_down;
	Double_t drj2a_JER_up;
	Double_t drj2a_JER_down;
	Double_t drj1l;
	Double_t drj1l_new;
	Double_t drj1l_JEC_up;
	Double_t drj1l_JEC_down;
	Double_t drj1l_JER_up;
	Double_t drj1l_JER_down;
	Double_t drj1l2;
	Double_t drj1l2_new;
	Double_t drj1l2_JEC_up;
	Double_t drj1l2_JEC_down;
	Double_t drj1l2_JER_up;
	Double_t drj1l2_JER_down;
	Double_t drj2l;
	Double_t drj2l_new;
	Double_t drj2l_JEC_up;
	Double_t drj2l_JEC_down;
	Double_t drj2l_JER_up;
	Double_t drj2l_JER_down;
	Double_t drj2l2;
	Double_t drj2l2_new;
	Double_t drj2l2_JEC_up;
	Double_t drj2l2_JEC_down;
	Double_t drj2l2_JER_up;
	Double_t drj2l2_JER_down;
	Int_t nlooseeles;
	Int_t nloosemus;
	Double_t MET_et;
	Double_t MET_et_new;
	Double_t MET_et_JEC_up;
	Double_t MET_et_JEC_down;
	Double_t MET_et_JER_up;
	Double_t MET_et_JER_down;
	Double_t photonet;
	Double_t photoneta;
	Double_t photonphi;
	Double_t photone;
	Double_t photonsieie;
	Double_t photonphoiso;
	Double_t photonchiso;
	Double_t photonnhiso;
	Int_t isprompt;
	Double_t jet1pt;
	Double_t jet1pt_new;
	Double_t jet1pt_JEC_up;
	Double_t jet1pt_JEC_down;
	Double_t jet1pt_JER_up;
	Double_t jet1pt_JER_down;
	Double_t jet1eta;
	Double_t jet1eta_new;
	Double_t jet1eta_JEC_up;
	Double_t jet1eta_JEC_down;
	Double_t jet1eta_JER_up;
	Double_t jet1eta_JER_down;
	Double_t jet1phi;
	Double_t jet1phi_new;
	Double_t jet1phi_JEC_up;
	Double_t jet1phi_JEC_down;
	Double_t jet1phi_JER_up;
	Double_t jet1phi_JER_down;
	Double_t jet1e;
	Double_t jet1e_new;
	Double_t jet1e_JEC_up;
	Double_t jet1e_JEC_down;
	Double_t jet1e_JER_up;
	Double_t jet1e_JER_down;
	Double_t jet2pt;
	Double_t jet2pt_new;
	Double_t jet2pt_JEC_up;
	Double_t jet2pt_JEC_down;
	Double_t jet2pt_JER_up;
	Double_t jet2pt_JER_down;
	Double_t jet2eta;
	Double_t jet2eta_new;
	Double_t jet2eta_JEC_up;
	Double_t jet2eta_JEC_down;
	Double_t jet2eta_JER_up;
	Double_t jet2eta_JER_down;
	Double_t jet2phi;
	Double_t jet2phi_new;
	Double_t jet2phi_JEC_up;
	Double_t jet2phi_JEC_down;
	Double_t jet2phi_JER_up;
	Double_t jet2phi_JER_down;
	Double_t jet2e;
	Double_t jet2e_new;
	Double_t jet2e_JEC_up;
	Double_t jet2e_JEC_down;
	Double_t jet2e_JER_up;
	Double_t jet2e_JER_down;
	Double_t Mjj;
	Double_t Mjj_new;
	Double_t Mjj_JEC_up;
	Double_t Mjj_JEC_down;
	Double_t Mjj_JER_up;
	Double_t Mjj_JER_down;
	Double_t zepp;
	Double_t zepp_new;
	Double_t zepp_JEC_up;
	Double_t zepp_JEC_down;
	Double_t zepp_JER_up;
	Double_t zepp_JER_down;
	Double_t deltaeta;
	Double_t deltaeta_new;
	Double_t deltaeta_JEC_up;
	Double_t deltaeta_JEC_down;
	Double_t deltaeta_JER_up;
	Double_t deltaeta_JER_down;
	Double_t actualWeight;
	Double_t detajj;
	Double_t detajj_new;
	Double_t detajj_JEC_up;
	Double_t detajj_JEC_down;
	Double_t detajj_JER_up;
	Double_t detajj_JER_down;
	Double_t delta_phi;
	Double_t delta_phi_new;
	Double_t delta_phi_JEC_up;
	Double_t delta_phi_JEC_down;
	Double_t delta_phi_JER_up;
	Double_t delta_phi_JER_down;
	Double_t drjj;
	Double_t drjj_new;
	Double_t drjj_JEC_up;
	Double_t drjj_JEC_down;
	Double_t drjj_JER_up;
	Double_t drjj_JER_down;
	Double_t l1_weight;
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

	Double_t        genphoton_pt[6] ;
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
        Double_t        genelectron_phi[6] ;


	TBranch *b_scalef;   //!
	TBranch *b_nVtx;   //!
	TBranch *b_theWeight;   //!
	TBranch *b_lumiWeight;   //!
	TBranch *b_pileupWeight;   //!
	TBranch *b_HLT_Ele1;   //!
	TBranch *b_HLT_Mu2;   //!
	TBranch *b_HLT_Mu5;   //!
	TBranch *b_nump;   //!
	TBranch *b_numm;   //!
	TBranch *b_npT;   //!
	TBranch *b_lep;   //!
	TBranch *b_run_period;
	TBranch *b_ptVlep;   //!
	TBranch *b_yVlep;   //!
	TBranch *b_phiVlep;   //!
	TBranch *b_massVlep;   //!
	TBranch *b_ptlep1;   //!
	TBranch *b_etalep1;   //!
	TBranch *b_philep1;   //!
	TBranch *b_ptlep2;   //!
	TBranch *b_etalep2;   //!
	TBranch *b_philep2;   //!
	TBranch *b_drla;
	TBranch *b_drla2;
	TBranch *b_drj1a;
	TBranch *b_drj1a_new;
	TBranch *b_drj1a_JEC_up;
	TBranch *b_drj1a_JEC_down;
	TBranch *b_drj1a_JER_up;
	TBranch *b_drj1a_JER_down;
	TBranch *b_drj2a;
	TBranch *b_drj2a_new;
	TBranch *b_drj2a_JEC_up;
	TBranch *b_drj2a_JEC_down;
	TBranch *b_drj2a_JER_up;
	TBranch *b_drj2a_JER_down;
	TBranch *b_drj1l;
	TBranch *b_drj1l_new;
	TBranch *b_drj1l_JEC_up;
	TBranch *b_drj1l_JEC_down;
	TBranch *b_drj1l_JER_up;
	TBranch *b_drj1l_JER_down;
	TBranch *b_drj1l2;
	TBranch *b_drj1l2_new;
	TBranch *b_drj1l2_JEC_up;
	TBranch *b_drj1l2_JEC_down;
	TBranch *b_drj1l2_JER_up;
	TBranch *b_drj1l2_JER_down;
	TBranch *b_drj2l;
	TBranch *b_drj2l_new;
	TBranch *b_drj2l_JEC_up;
	TBranch *b_drj2l_JEC_down;
	TBranch *b_drj2l_JER_up;
	TBranch *b_drj2l_JER_down;
	TBranch *b_drj2l2;
	TBranch *b_drj2l2_new;
	TBranch *b_drj2l2_JEC_up;
	TBranch *b_drj2l2_JEC_down;
	TBranch *b_drj2l2_JER_up;
	TBranch *b_drj2l2_JER_down;
	TBranch *b_nlooseeles;   //!
	TBranch *b_nloosemus;   //!
	TBranch *b_MET_et;   //!
	TBranch *b_MET_et_new;
	TBranch *b_MET_et_JEC_up;
	TBranch *b_MET_et_JEC_down;
	TBranch *b_MET_et_JER_up;
	TBranch *b_MET_et_JER_down;
	TBranch *b_photonet;   //!
	TBranch *b_photoneta;   //!
	TBranch *b_photonphi;
	TBranch *b_photone;
	TBranch *b_photonsieie;   //!
	TBranch *b_photonphoiso;   //!
	TBranch *b_photonchiso;   //!
	TBranch *b_photonnhiso;   //!
	TBranch *b_isprompt;   //!
	TBranch *b_jet1pt;   //!
	TBranch *b_jet1pt_new;
	TBranch *b_jet1pt_JEC_up;
	TBranch *b_jet1pt_JEC_down;
	TBranch *b_jet1pt_JER_up;
	TBranch *b_jet1pt_JER_down;
	TBranch *b_jet1eta;   //!
	TBranch *b_jet1eta_new;
	TBranch *b_jet1eta_JEC_up;
	TBranch *b_jet1eta_JEC_down;
	TBranch *b_jet1eta_JER_up;
	TBranch *b_jet1eta_JER_down;
	TBranch *b_jet1phi;
	TBranch *b_jet1phi_new;
	TBranch *b_jet1phi_JEC_up;
	TBranch *b_jet1phi_JEC_down;
	TBranch *b_jet1phi_JER_up;
	TBranch *b_jet1phi_JER_down;
	TBranch *b_jet1e;
	TBranch *b_jet1e_new;
	TBranch *b_jet1e_JEC_up;
	TBranch *b_jet1e_JEC_down;
	TBranch *b_jet1e_JER_up;
	TBranch *b_jet1e_JER_down;
	TBranch *b_jet2pt;   //!
	TBranch *b_jet2pt_new;
	TBranch *b_jet2pt_JEC_up;
	TBranch *b_jet2pt_JEC_down;
	TBranch *b_jet2pt_JER_up;
	TBranch *b_jet2pt_JER_down;
	TBranch *b_jet2eta;   //!
	TBranch *b_jet2eta_new;
	TBranch *b_jet2eta_JEC_up;
	TBranch *b_jet2eta_JEC_down;
	TBranch *b_jet2eta_JER_up;
	TBranch *b_jet2eta_JER_down;
	TBranch *b_jet2phi;
	TBranch *b_jet2phi_new;
	TBranch *b_jet2phi_JEC_up;
	TBranch *b_jet2phi_JEC_down;
	TBranch *b_jet2phi_JER_up;
	TBranch *b_jet2phi_JER_down;
	TBranch *b_jet2e;
	TBranch *b_jet2e_new;
	TBranch *b_jet2e_JEC_up;
	TBranch *b_jet2e_JEC_down;
	TBranch *b_jet2e_JER_up;
	TBranch *b_jet2e_JER_down;
	TBranch *b_Mjj;    //!
	TBranch *b_Mjj_new;
	TBranch *b_Mjj_JEC_up;
	TBranch *b_Mjj_JEC_down;
	TBranch *b_Mjj_JER_up;
	TBranch *b_Mjj_JER_down;
	TBranch *b_zepp;
	TBranch *b_zepp_new;
	TBranch *b_zepp_JEC_up;
	TBranch *b_zepp_JEC_down;
	TBranch *b_zepp_JER_up;
	TBranch *b_zepp_JER_down;
	TBranch *b_deltaeta;
	TBranch *b_deltaeta_new;
	TBranch *b_deltaeta_JEC_up;
	TBranch *b_deltaeta_JEC_down;
	TBranch *b_deltaeta_JER_up;
	TBranch *b_deltaeta_JER_down;
	TBranch *b_l1_weight;
	TBranch *b_ele1_id_scale;
	TBranch *b_ele2_id_scale;
	TBranch *b_ele1_reco_scale;
	TBranch *b_ele2_reco_scale;
	TBranch *b_photon_id_scale;
	TBranch *b_muon1_id_scale;
	TBranch *b_muon2_id_scale;
	TBranch *b_muon1_iso_scale;
	TBranch *b_muon2_iso_scale;
	TBranch *b_muon1_track_scale;
	TBranch *b_muon2_track_scale;
	TBranch *b_muon_hlt_scale;

	fChain->SetBranchAddress("scalef", &scalef, &b_scalef);
	fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
	fChain->SetBranchAddress("theWeight", &theWeight, &b_theWeight);
	fChain->SetBranchAddress("lumiWeight", &lumiWeight, &b_lumiWeight);
	fChain->SetBranchAddress("pileupWeight", &pileupWeight, &b_pileupWeight);
	fChain->SetBranchAddress("HLT_Ele1", &HLT_Ele1, &b_HLT_Ele1);
	fChain->SetBranchAddress("HLT_Mu2", &HLT_Mu2, &b_HLT_Mu2);
	fChain->SetBranchAddress("HLT_Mu5", &HLT_Mu5, &b_HLT_Mu5);
	fChain->SetBranchAddress("nump", &nump, &b_nump);
	fChain->SetBranchAddress("numm", &numm, &b_numm);
	fChain->SetBranchAddress("npT", &npT, &b_npT);
	fChain->SetBranchAddress("lep", &lep, &b_lep);
	fChain->SetBranchAddress("run_period", &run_period, &b_run_period);
	fChain->SetBranchAddress("ptVlep", &ptVlep, &b_ptVlep);
	fChain->SetBranchAddress("yVlep", &yVlep, &b_yVlep);
	fChain->SetBranchAddress("phiVlep", &phiVlep, &b_phiVlep);
	fChain->SetBranchAddress("massVlep", &massVlep, &b_massVlep);
	fChain->SetBranchAddress("ptlep1", &ptlep1, &b_ptlep1);
	fChain->SetBranchAddress("etalep1", &etalep1, &b_etalep1);
	fChain->SetBranchAddress("philep1", &philep1, &b_philep1);
	fChain->SetBranchAddress("ptlep2", &ptlep2, &b_ptlep2);
	fChain->SetBranchAddress("etalep2", &etalep2, &b_etalep2);
	fChain->SetBranchAddress("philep2", &philep2, &b_philep2);
	fChain->SetBranchAddress("drla", &drla, &b_drla);
	fChain->SetBranchAddress("drla2", &drla2, &b_drla2);
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
	fChain->SetBranchAddress("nlooseeles", &nlooseeles, &b_nlooseeles);
	fChain->SetBranchAddress("nloosemus", &nloosemus, &b_nloosemus);
	fChain->SetBranchAddress("MET_et", &MET_et, &b_MET_et);
	fChain->SetBranchAddress("MET_et_new", &MET_et_new, &b_MET_et_new);
	fChain->SetBranchAddress("MET_et_JEC_up", &MET_et_JEC_up, &b_MET_et_JEC_up);
	fChain->SetBranchAddress("MET_et_JEC_down", &MET_et_JEC_down, &b_MET_et_JEC_down);
	fChain->SetBranchAddress("MET_et_JER_up", &MET_et_JER_up, &b_MET_et_JER_up);
	fChain->SetBranchAddress("MET_et_JER_down", &MET_et_JER_down, &b_MET_et_JER_down);
	fChain->SetBranchAddress("photonet", &photonet, &b_photonet);
	fChain->SetBranchAddress("photoneta", &photoneta, &b_photoneta);
	fChain->SetBranchAddress("photonphi", &photonphi, &b_photonphi);
	fChain->SetBranchAddress("photone", &photone, &b_photone);
	fChain->SetBranchAddress("photonsieie", &photonsieie, &b_photonsieie);
	fChain->SetBranchAddress("photonphoiso", &photonphoiso, &b_photonphoiso);
	fChain->SetBranchAddress("photonchiso", &photonchiso, &b_photonchiso);
	fChain->SetBranchAddress("photonnhiso", &photonnhiso, &b_photonnhiso);
	fChain->SetBranchAddress("isprompt", &isprompt, &b_isprompt);
	fChain->SetBranchAddress("jet1pt", &jet1pt, &b_jet1pt);
	fChain->SetBranchAddress("jet1pt_new", &jet1pt_new, &b_jet1pt_new);
	fChain->SetBranchAddress("jet1pt_JEC_up", &jet1pt_JEC_up, &b_jet1pt_JEC_up);
	fChain->SetBranchAddress("jet1pt_JEC_down", &jet1pt_JEC_down, &b_jet1pt_JEC_down);
	fChain->SetBranchAddress("jet1pt_JER_up", &jet1pt_JER_up, &b_jet1pt_JER_up);
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
	fChain->SetBranchAddress("jet1e_JEC_down", &jet1e_JEC_down, &b_jet1e_JEC_down);
	fChain->SetBranchAddress("jet1e_JER_up", &jet1e_JER_up, &b_jet1e_JER_up);
	fChain->SetBranchAddress("jet1e_JER_down", &jet1e_JER_down, &b_jet1e_JER_down);
	fChain->SetBranchAddress("jet2pt", &jet2pt, &b_jet2pt);
	fChain->SetBranchAddress("jet2pt_new", &jet2pt_new, &b_jet2pt_new);
	fChain->SetBranchAddress("jet2pt_JEC_up", &jet2pt_JEC_up, &b_jet2pt_JEC_up);
	fChain->SetBranchAddress("jet2pt_JEC_down", &jet2pt_JEC_down, &b_jet2pt_JEC_down);
	fChain->SetBranchAddress("jet2pt_JER_up", &jet2pt_JER_up, &b_jet2pt_JER_up);
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
	fChain->SetBranchAddress("jet2e_JEC_down", &jet2e_JEC_down, &b_jet2e_JEC_down);
	fChain->SetBranchAddress("jet2e_JER_up", &jet2e_JER_up, &b_jet2e_JER_up);
	fChain->SetBranchAddress("jet2e_JER_down", &jet2e_JER_down, &b_jet2e_JER_down);
	fChain->SetBranchAddress("Mjj", &Mjj, &b_Mjj);
	fChain->SetBranchAddress("Mjj_new", &Mjj_new, &b_Mjj_new);
	fChain->SetBranchAddress("Mjj_JEC_up", &Mjj_JEC_up, &b_Mjj_JEC_up);
	fChain->SetBranchAddress("Mjj_JEC_down", &Mjj_JEC_down, &b_Mjj_JEC_down);
	fChain->SetBranchAddress("Mjj_JER_up", &Mjj_JER_up, &b_Mjj_JER_up);
	fChain->SetBranchAddress("Mjj_JER_down", &Mjj_JER_down, &b_Mjj_JER_down);
	fChain->SetBranchAddress("zepp", &zepp, &b_zepp);
	fChain->SetBranchAddress("zepp_new", &zepp_new, &b_zepp_new);
	fChain->SetBranchAddress("zepp_JEC_up", &zepp_JEC_up, &b_zepp_JEC_up);
	fChain->SetBranchAddress("zepp_JEC_down", &zepp_JEC_down, &b_zepp_JEC_down);
	fChain->SetBranchAddress("zepp_JER_up", &zepp_JER_up, &b_zepp_JER_up);
	fChain->SetBranchAddress("zepp_JER_down", &zepp_JER_down, &b_zepp_JER_down);
	fChain->SetBranchAddress("deltaeta", &deltaeta, &b_deltaeta);
	fChain->SetBranchAddress("deltaeta_new", &deltaeta_new, &b_deltaeta_new);
	fChain->SetBranchAddress("deltaeta_JEC_up", &deltaeta_JEC_up, &b_deltaeta_JEC_up);
	fChain->SetBranchAddress("deltaeta_JEC_down", &deltaeta_JEC_down, &b_deltaeta_JEC_down);
	fChain->SetBranchAddress("deltaeta_JER_up", &deltaeta_JER_up, &b_deltaeta_JER_up);
	fChain->SetBranchAddress("deltaeta_JER_down", &deltaeta_JER_down, &b_deltaeta_JER_down);
	fChain->SetBranchAddress("l1_weight", &l1_weight, &b_l1_weight);	
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
	fChain->SetBranchAddress("genphoton_pt",genphoton_pt);
        fChain->SetBranchAddress("genphoton_eta",genphoton_eta);
        fChain->SetBranchAddress("genphoton_phi",genphoton_phi);
        fChain->SetBranchAddress("genjet_pt",genjet_pt);
        fChain->SetBranchAddress("genjet_eta",genjet_eta);
        fChain->SetBranchAddress("genjet_phi",genjet_phi);
        fChain->SetBranchAddress("genjet_e",genjet_e);
        fChain->SetBranchAddress("genmuon_pt",genmuon_pt);
        fChain->SetBranchAddress("genmuon_eta",genmuon_eta);
        fChain->SetBranchAddress("genmuon_phi",genmuon_phi);
        fChain->SetBranchAddress("genelectron_pt",genelectron_pt);
        fChain->SetBranchAddress("genelectron_eta",genelectron_eta);
        fChain->SetBranchAddress("genelectron_phi",genelectron_phi);


	TLorentzVector j1p4, j2p4, photonp4, Zp4;
	Long64_t nentries = fChain->GetEntriesFast();

	//double bins[13]={150, 175, 200, 225, 250, 275, 300, 325, 350, 375, 400,1000, 2000};
	TH1D *mjj = new TH1D("mjj", "mjj", 9,0,9);
	TH1D *mjj_new = new TH1D("mjj_new", "mjj_new", 9,0,9);
	TH1D *mjj_JEC_up = new TH1D("mjj_JEC_up", "mjj_JEC_up", 9,0,9);
	TH1D *mjj_JEC_down = new TH1D("mjj_JEC_down", "mjj_JEC_down", 9,0,9);
	TH1D *mjj_JER_up = new TH1D("mjj_JER_up", "mjj_JER_up", 9,0,9);
	TH1D *mjj_JER_down = new TH1D("mjj_JER_down", "mjj_JER_down",9,0,9);

	//variables for ID/ISO... scale
	Double_t l1_weight_tmp=0;
	int sig_count =0;
	Double_t photon_eveto = 0.9938;

	int ele_count=0;
        int ele_count1=0;
        int ele_count2=0;
        int ele_count3=0;
        TLorentzVector j1, j2, l1, l2, photon_p4;
        double ZGmass=-1.;

	for (Long64_t jentry =0; jentry < nentries; jentry++){
		if(jentry%10000==0) std::cout<<"processing entry: "<<jentry<<std::endl;
		fChain->GetEntry(jentry);

	
		ZGmass=-1.;
                j1.SetPtEtaPhiE(0,0,0,0);
                j2.SetPtEtaPhiE(0,0,0,0);
                l1.SetPtEtaPhiE(0,0,0,0);
                l2.SetPtEtaPhiE(0,0,0,0);
                photon_p4.SetPtEtaPhiE(0,0,0,0);
                bool in_acceptance = false;
                if(genphoton_pt[0]>0 && genjet_pt[0] >=30 &&genjet_pt[1] >=30 && genmuon_pt[0]>0 &&genmuon_pt[1]>0 ){
                        if(large(genelectron_pt[0],genelectron_pt[1])<large(genmuon_pt[0],genmuon_pt[1])){
                                l1.SetPtEtaPhiM(genmuon_pt[0],genmuon_eta[0],genmuon_phi[0],0.1);
                                l2.SetPtEtaPhiM(genmuon_pt[1],genmuon_eta[1],genmuon_phi[1],0.1);
                                TLorentzVector photon_temp;
                                for(int iphoton=0;iphoton<6;iphoton++){
					if(genphoton_pt[iphoton]<0) continue;
                                        photon_temp.SetPtEtaPhiM(genphoton_pt[iphoton],genphoton_eta[iphoton],genphoton_phi[iphoton],0);
                                        if((l1.DeltaR(photon_temp)<0.1 || l2.DeltaR(photon_temp)<0.1) && l1.DeltaR(photon_temp)<l2.DeltaR(photon_temp)) {l1+=photon_temp;continue;}
                                        if((l1.DeltaR(photon_temp)<0.1 || l2.DeltaR(photon_temp)<0.1) && l1.DeltaR(photon_temp)>=l2.DeltaR(photon_temp)) {l2+=photon_temp;continue;}
                                }
                                if(l1.Pt()>=20 && l2.Pt()>=20 && fabs(l1.Eta())<=2.4 && fabs(l2.Eta())<=2.4 && (l1+l2).M()>=70 && (l1+l2).M()<=110)                     {       ele_count1++;
                                        int good_photon=-1;
                                        for(int iphoton=0;iphoton<6;iphoton++){
						if(good_photon!=-1)continue;
                                                TLorentzVector photon_temp;
                                                if(genphoton_pt[iphoton]<20 || fabs(genphoton_eta[iphoton]) >2.5 || (fabs(genphoton_eta[iphoton])<1.566 &&fabs(genphoton_eta[iphoton])>1.4442) ) continue;
                                                photon_temp.SetPtEtaPhiM(genphoton_pt[iphoton],genphoton_eta[iphoton],genphoton_phi[iphoton],0);
                                                if(l1.DeltaR(photon_temp)<0.7 || l2.DeltaR(photon_temp)<0.7) continue;
                                                if(good_photon==-1)photon_p4.SetPtEtaPhiM(genphoton_pt[iphoton],genphoton_eta[iphoton],genphoton_phi[iphoton],0);
						if(good_photon!=-1 && photon_temp.Pt()>photon_p4.Pt()) photon_p4.SetPtEtaPhiM(genphoton_pt[iphoton],genphoton_eta[iphoton],genphoton_phi[iphoton],0);
                                                good_photon=iphoton;
                                        }
                                        if(good_photon!=-1){
                                                ele_count2++;
                                                for(int ijet=0;ijet<6;ijet++){
							if(j1.Pt()!=0 && j2.Pt()!=0) continue;
                                                        TLorentzVector jet_temp;
                                                        if(genjet_pt[ijet]<30 || fabs(genjet_eta[ijet])>4.7) continue;
                                                        jet_temp.SetPtEtaPhiE(genjet_pt[ijet],genjet_eta[ijet],genjet_phi[ijet],genjet_e[ijet]);
                                                        if(j1.Pt()==0 && l1.DeltaR(jet_temp)>0.5 && l2.DeltaR(jet_temp)>0.5 &&photon_p4.DeltaR(jet_temp)>0.5) j1.SetPtEtaPhiE(genjet_pt[ijet],genjet_eta[ijet],genjet_phi[ijet],genjet_e[ijet]);
                                                        if(j1.Pt()!=0 &&l1.DeltaR(jet_temp)>0.5 && l2.DeltaR(jet_temp)>0.5 &&photon_p4.DeltaR(jet_temp)>0.5 &&j1.DeltaR(jet_temp)>0.5) j2.SetPtEtaPhiE(genjet_pt[ijet],genjet_eta[ijet],genjet_phi[ijet],genjet_e[ijet]);
                                                }
                                                if(j1.Pt()>0 && j2.Pt()>0){
                                                        ele_count3++;
                                                        ZGmass=(l1+l2+photon_p4).M();
                                                        if((j1+j2).M()>=500 && fabs(j1.Eta()-j2.Eta())>=2.5 && ZGmass>=100 &&fabs(genphoton_eta[good_photon])<=1.4442){in_acceptance = true;ele_count++;}
                                                }
                                        }
                                }
                        }
                }
                // in-acceptance signal
//                if(!in_acceptance) continue;


		scalef=0.000365678;
		actualWeight = lumiWeight * pileupWeight * scalef;

		if(l1_weight==0) l1_weight_tmp=0.524;
                if(l1_weight==0.5) l1_weight_tmp=0.762;
                if(l1_weight==1) l1_weight_tmp=1;
//                actualWeight = actualWeight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon1_track_scale*muon2_track_scale*muon_hlt_scale*photon_id_scale*photon_eveto*l1_weight_tmp;

		// old jet info 
		detajj = fabs(jet1eta - jet2eta);
                if (fabs(jet1phi-jet2phi)>Pi) drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*Pi-fabs(jet1phi-jet2phi))*(2*Pi-fabs(jet1phi-jet2phi)));
                else drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)));

                j1p4.SetPtEtaPhiE(jet1pt, jet1eta, jet1phi, jet1e);
                j2p4.SetPtEtaPhiE(jet2pt, jet2eta, jet2phi, jet2e);
                photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
                Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, massVlep);
                delta_phi=fabs((Zp4+photonp4).Phi()-(j1p4+j2p4).Phi());
                if (delta_phi>Pi) delta_phi=2*Pi-delta_phi;

		// smeared jet info
                detajj_new = fabs(jet1eta_new - jet2eta_new);
                if (fabs(jet1phi_new-jet2phi_new)>Pi) drjj_new = sqrt((jet1eta_new-jet2eta_new)*(jet1eta_new-jet2eta_new)+(2*Pi-fabs(jet1phi_new-jet2phi_new))*(2*Pi-fabs(jet1phi_new-jet2phi_new)));
                else drjj_new = sqrt((jet1eta_new-jet2eta_new)*(jet1eta_new-jet2eta_new)+(fabs(jet1phi_new-jet2phi_new))*(fabs(jet1phi_new-jet2phi_new)));

                j1p4.SetPtEtaPhiE(jet1pt_new, jet1eta_new, jet1phi_new, jet1e_new);
                j2p4.SetPtEtaPhiE(jet2pt_new, jet2eta_new, jet2phi_new, jet2e_new);
                photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
                Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, massVlep);
                delta_phi_new=fabs((Zp4+photonp4).Phi()-(j1p4+j2p4).Phi());
                if (delta_phi_new>Pi) delta_phi_new=2*Pi-delta_phi_new;
		
		
		// smeared jet JEC up info
                detajj_JEC_up = fabs(jet1eta_JEC_up - jet2eta_JEC_up);
                if (fabs(jet1phi_JEC_up-jet2phi_JEC_up)>Pi) drjj_JEC_up = sqrt((jet1eta_JEC_up-jet2eta_JEC_up)*(jet1eta_JEC_up-jet2eta_JEC_up)+(2*Pi-fabs(jet1phi_JEC_up-jet2phi_JEC_up))*(2*Pi-fabs(jet1phi_JEC_up-jet2phi_JEC_up)));
                else drjj_JEC_up = sqrt((jet1eta_JEC_up-jet2eta_JEC_up)*(jet1eta_JEC_up-jet2eta_JEC_up)+(fabs(jet1phi_JEC_up-jet2phi_JEC_up))*(fabs(jet1phi_JEC_up-jet2phi_JEC_up)));

                j1p4.SetPtEtaPhiE(jet1pt_JEC_up, jet1eta_JEC_up, jet1phi_JEC_up, jet1e_JEC_up);
                j2p4.SetPtEtaPhiE(jet2pt_JEC_up, jet2eta_JEC_up, jet2phi_JEC_up, jet2e_JEC_up);
                photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
                Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, massVlep);
                delta_phi_JEC_up=fabs((Zp4+photonp4).Phi()-(j1p4+j2p4).Phi());
                if (delta_phi_JEC_up>Pi) delta_phi_JEC_up=2*Pi-delta_phi_JEC_up;
		
		// smeared jet JEC down info
                detajj_JEC_down = fabs(jet1eta_JEC_down - jet2eta_JEC_down);
                if (fabs(jet1phi_JEC_down-jet2phi_JEC_down)>Pi) drjj_JEC_down = sqrt((jet1eta_JEC_down-jet2eta_JEC_down)*(jet1eta_JEC_down-jet2eta_JEC_down)+(2*Pi-fabs(jet1phi_JEC_down-jet2phi_JEC_down))*(2*Pi-fabs(jet1phi_JEC_down-jet2phi_JEC_down)));
                else drjj_JEC_down = sqrt((jet1eta_JEC_down-jet2eta_JEC_down)*(jet1eta_JEC_down-jet2eta_JEC_down)+(fabs(jet1phi_JEC_down-jet2phi_JEC_down))*(fabs(jet1phi_JEC_down-jet2phi_JEC_down)));

                j1p4.SetPtEtaPhiE(jet1pt_JEC_down, jet1eta_JEC_down, jet1phi_JEC_down, jet1e_JEC_down);
                j2p4.SetPtEtaPhiE(jet2pt_JEC_down, jet2eta_JEC_down, jet2phi_JEC_down, jet2e_JEC_down);
                photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
                Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, massVlep);
                delta_phi_JEC_down=fabs((Zp4+photonp4).Phi()-(j1p4+j2p4).Phi());
                if (delta_phi_JEC_down>Pi) delta_phi_JEC_down=2*Pi-delta_phi_JEC_down;
		
		// smeared jet JER up info
                detajj_JER_up = fabs(jet1eta_JER_up - jet2eta_JER_up);
                if (fabs(jet1phi_JER_up-jet2phi_JER_up)>Pi) drjj_JER_up = sqrt((jet1eta_JER_up-jet2eta_JER_up)*(jet1eta_JER_up-jet2eta_JER_up)+(2*Pi-fabs(jet1phi_JER_up-jet2phi_JER_up))*(2*Pi-fabs(jet1phi_JER_up-jet2phi_JER_up)));
                else drjj_JER_up = sqrt((jet1eta_JER_up-jet2eta_JER_up)*(jet1eta_JER_up-jet2eta_JER_up)+(fabs(jet1phi_JER_up-jet2phi_JER_up))*(fabs(jet1phi_JER_up-jet2phi_JER_up)));

                j1p4.SetPtEtaPhiE(jet1pt_JER_up, jet1eta_JER_up, jet1phi_JER_up, jet1e_JER_up);
                j2p4.SetPtEtaPhiE(jet2pt_JER_up, jet2eta_JER_up, jet2phi_JER_up, jet2e_JER_up);
                photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
                Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, massVlep);
                delta_phi_JER_up=fabs((Zp4+photonp4).Phi()-(j1p4+j2p4).Phi());
                if (delta_phi_JER_up>Pi) delta_phi_JER_up=2*Pi-delta_phi_JER_up;
		
		// smeared jet JER down info
                detajj_JER_down = fabs(jet1eta_JER_down - jet2eta_JER_down);
                if (fabs(jet1phi_JER_down-jet2phi_JER_down)>Pi) drjj_JER_down = sqrt((jet1eta_JER_down-jet2eta_JER_down)*(jet1eta_JER_down-jet2eta_JER_down)+(2*Pi-fabs(jet1phi_JER_down-jet2phi_JER_down))*(2*Pi-fabs(jet1phi_JER_down-jet2phi_JER_down)));
                else drjj_JER_down = sqrt((jet1eta_JER_down-jet2eta_JER_down)*(jet1eta_JER_down-jet2eta_JER_down)+(fabs(jet1phi_JER_down-jet2phi_JER_down))*(fabs(jet1phi_JER_down-jet2phi_JER_down)));

                j1p4.SetPtEtaPhiE(jet1pt_JER_down, jet1eta_JER_down, jet1phi_JER_down, jet1e_JER_down);
                j2p4.SetPtEtaPhiE(jet2pt_JER_down, jet2eta_JER_down, jet2phi_JER_down, jet2e_JER_down);
                photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
                Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, massVlep);
                delta_phi_JER_down=fabs((Zp4+photonp4).Phi()-(j1p4+j2p4).Phi());
                if (delta_phi_JER_down>Pi) delta_phi_JER_down=2*Pi-delta_phi_JER_down;
		

		// fill histo old jet 
		if ( HLT_Mu2 > 0 && lep == 13 && nlooseeles == 0 && nloosemus < 3 && massVlep > 70 && massVlep < 110 && ptlep1 > 20. && ptlep2 > 20. && fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4&& photonet > 20. && fabs(photoneta) < 1.4442 && jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7 && Mjj > 150 && drla > 0.7 && drla2 > 0.7 && drj1a > 0.5 && drj2a > 0.5 && drjj> 0.5 && drj1l > 0.5 && drj2l > 0.5 && drj1l2 > 0.5 && drj2l2 > 0.5/* && deltaeta > 1.9 && delta_phi >2.14 && zepp < 1.18 */) {
			if(Mjj>500) sig_count++; 
			if(Mjj>=500&&Mjj<800&&deltaeta>=2.5&&deltaeta<4.5) mjj->Fill(0.5,actualWeight);
			if(Mjj>=800&&Mjj<1200&&deltaeta>=2.5&&deltaeta<4.5) mjj->Fill(1.5,actualWeight);
			if(Mjj>=1200&&deltaeta>=2.5&&deltaeta<4.5) mjj->Fill(2.5,actualWeight);
			if(Mjj>=500&&Mjj<800&&deltaeta>=4.5&&deltaeta<6) mjj->Fill(3.5,actualWeight);
			if(Mjj>=800&&Mjj<1200&&deltaeta>=4.5&&deltaeta<6) mjj->Fill(4.5,actualWeight);
			if(Mjj>=1200&&deltaeta>=4.5&&deltaeta<6) mjj->Fill(5.5,actualWeight);
			if(Mjj>=500&&Mjj<800&&deltaeta>=6) mjj->Fill(6.5,actualWeight);
			if(Mjj>=800&&Mjj<1200&&deltaeta>=6) mjj->Fill(7.5,actualWeight);
			if(Mjj>=1200&&deltaeta>=6) mjj->Fill(8.5,actualWeight);
		}


		// fill histo smeared jet 
		if ( HLT_Mu2 > 0 && lep == 13 && nlooseeles == 0 && nloosemus < 3 && massVlep > 70 && massVlep < 110 && ptlep1 > 20. && ptlep2 > 20. && fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4&& photonet > 20. && fabs(photoneta) < 1.4442 && jet1pt_new> 30 && jet2pt_new > 30 && fabs(jet1eta_new)< 4.7 && fabs(jet2eta_new)<4.7 && Mjj_new > 150 && drla > 0.7 && drla2 > 0.7 && drj1a_new > 0.5 && drj2a_new > 0.5 && drjj_new> 0.5 && drj1l_new > 0.5 && drj2l_new > 0.5 && drj1l2_new > 0.5 && drj2l2_new > 0.5 /*&& deltaeta_new > 1.9 && delta_phi_new >2.14 && zepp_new < 1.18 */) {
			if(Mjj_new>=500&&Mjj_new<800&&deltaeta_new>=2.5&&deltaeta_new<4.5) mjj_new->Fill(0.5,actualWeight);
                        if(Mjj_new>=800&&Mjj_new<1200&&deltaeta_new>=2.5&&deltaeta_new<4.5) mjj_new->Fill(1.5,actualWeight);
                        if(Mjj_new>=1200&&deltaeta_new>=2.5&&deltaeta_new<4.5) mjj_new->Fill(2.5,actualWeight);
                        if(Mjj_new>=500&&Mjj_new<800&&deltaeta_new>=4.5&&deltaeta_new<6) mjj_new->Fill(3.5,actualWeight);
                        if(Mjj_new>=800&&Mjj_new<1200&&deltaeta_new>=4.5&&deltaeta_new<6) mjj_new->Fill(4.5,actualWeight);
                        if(Mjj_new>=1200&&deltaeta_new>=4.5&&deltaeta_new<6) mjj_new->Fill(5.5,actualWeight);
                        if(Mjj_new>=500&&Mjj_new<800&&deltaeta_new>=6) mjj_new->Fill(6.5,actualWeight);
                        if(Mjj_new>=800&&Mjj_new<1200&&deltaeta_new>=6) mjj_new->Fill(7.5,actualWeight);
                        if(Mjj_new>=1200&&deltaeta_new>=6) mjj_new->Fill(8.5,actualWeight);
		}

		// fill histo smeared jet JEC up
		if ( HLT_Mu2 > 0 && lep == 13 && nlooseeles == 0 && nloosemus < 3 && massVlep > 70 && massVlep < 110 && ptlep1 > 20. && ptlep2 > 20. && fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4&& photonet > 20. && fabs(photoneta) < 1.4442 && jet1pt_JEC_up> 30 && jet2pt_JEC_up > 30 && fabs(jet1eta_JEC_up)< 4.7 && fabs(jet2eta_JEC_up)<4.7 && Mjj_JEC_up > 150 && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_up > 0.5 && drj2a_JEC_up > 0.5 && drjj_JEC_up> 0.5 && drj1l_JEC_up > 0.5 && drj2l_JEC_up > 0.5 && drj1l2_JEC_up > 0.5 && drj2l2_JEC_up > 0.5/* && deltaeta_new_JEC_up > 1.9 && delta_phi_JEC_up >2.14  && zepp_JEC_up < 1.18*/) {
			if(Mjj_JEC_up>=500&&Mjj_JEC_up<800&&deltaeta_JEC_up>=2.5&&deltaeta_JEC_up<4.5) mjj_JEC_up->Fill(0.5,actualWeight);
                        if(Mjj_JEC_up>=800&&Mjj_JEC_up<1200&&deltaeta_JEC_up>=2.5&&deltaeta_JEC_up<4.5) mjj_JEC_up->Fill(1.5,actualWeight);
                        if(Mjj_JEC_up>=1200&&deltaeta_JEC_up>=2.5&&deltaeta_JEC_up<4.5) mjj_JEC_up->Fill(2.5,actualWeight);
                        if(Mjj_JEC_up>=500&&Mjj_JEC_up<800&&deltaeta_JEC_up>=4.5&&deltaeta_JEC_up<6) mjj_JEC_up->Fill(3.5,actualWeight);
                        if(Mjj_JEC_up>=800&&Mjj_JEC_up<1200&&deltaeta_JEC_up>=4.5&&deltaeta_JEC_up<6) mjj_JEC_up->Fill(4.5,actualWeight);
                        if(Mjj_JEC_up>=1200&&deltaeta_JEC_up>=4.5&&deltaeta_JEC_up<6) mjj_JEC_up->Fill(5.5,actualWeight);
                        if(Mjj_JEC_up>=500&&Mjj_JEC_up<800&&deltaeta_JEC_up>=6) mjj_JEC_up->Fill(6.5,actualWeight);
                        if(Mjj_JEC_up>=800&&Mjj_JEC_up<1200&&deltaeta_JEC_up>=6) mjj_JEC_up->Fill(7.5,actualWeight);
                        if(Mjj_JEC_up>=1200&&deltaeta_JEC_up>=6) mjj_JEC_up->Fill(8.5,actualWeight);
		}

		// fill histo smeared jet JEC down 
		if ( HLT_Mu2 > 0 && lep == 13 && nlooseeles == 0 && nloosemus < 3 && massVlep > 70 && massVlep < 110 && ptlep1 > 20. && ptlep2 > 20. && fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4&& photonet > 20. && fabs(photoneta) < 1.4442 && jet1pt_JEC_down> 30 && jet2pt_JEC_down > 30 && fabs(jet1eta_JEC_down)< 4.7 && fabs(jet2eta_JEC_down)<4.7 && Mjj_JEC_down > 150 && drla > 0.7 && drla2 > 0.7 && drj1a_JEC_down > 0.5 && drj2a_JEC_down > 0.5  && drjj_JEC_down> 0.5 && drj1l_JEC_down > 0.5 && drj2l_JEC_down > 0.5 && drj1l2_JEC_down > 0.5 && drj2l2_JEC_down > 0.5 /*&& deltaeta_JEC_down > 1.9 && delta_phi_JEC_down >2.14 && zepp_JEC_down < 1.18*/) {
			if(Mjj_JEC_down>=500&&Mjj_JEC_down<800&&deltaeta_JEC_down>=2.5&&deltaeta_JEC_down<4.5) mjj_JEC_down->Fill(0.5,actualWeight);
                        if(Mjj_JEC_down>=800&&Mjj_JEC_down<1200&&deltaeta_JEC_down>=2.5&&deltaeta_JEC_down<4.5) mjj_JEC_down->Fill(1.5,actualWeight);
                        if(Mjj_JEC_down>=1200&&deltaeta_JEC_down>=2.5&&deltaeta_JEC_down<4.5) mjj_JEC_down->Fill(2.5,actualWeight);
                        if(Mjj_JEC_down>=500&&Mjj_JEC_down<800&&deltaeta_JEC_down>=4.5&&deltaeta_JEC_down<6) mjj_JEC_down->Fill(3.5,actualWeight);
                        if(Mjj_JEC_down>=800&&Mjj_JEC_down<1200&&deltaeta_JEC_down>=4.5&&deltaeta_JEC_down<6) mjj_JEC_down->Fill(4.5,actualWeight);
                        if(Mjj_JEC_down>=1200&&deltaeta_JEC_down>=4.5&&deltaeta_JEC_down<6) mjj_JEC_down->Fill(5.5,actualWeight);
                        if(Mjj_JEC_down>=500&&Mjj_JEC_down<800&&deltaeta_JEC_down>=6) mjj_JEC_down->Fill(6.5,actualWeight);
                        if(Mjj_JEC_down>=800&&Mjj_JEC_down<1200&&deltaeta_JEC_down>=6) mjj_JEC_down->Fill(7.5,actualWeight);
                        if(Mjj_JEC_down>=1200&&deltaeta_JEC_down>=6) mjj_JEC_down->Fill(8.5,actualWeight);
		}

		// fill histo smeared jet JER up
		if ( HLT_Mu2 > 0 && lep == 13 && nlooseeles == 0 && nloosemus < 3 && massVlep > 70 && massVlep < 110 && ptlep1 > 20. && ptlep2 > 20. && fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4&& photonet > 20. && fabs(photoneta) < 1.4442 && jet1pt_JER_up> 30 && jet2pt_JER_up > 30 && fabs(jet1eta_JER_up)< 4.7 && fabs(jet2eta_JER_up)<4.7 && Mjj_JER_up > 150 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_up > 0.5 && drj2a_JER_up > 0.5  && drjj_JER_up> 0.5 && drj1l_JER_up > 0.5 && drj2l_JER_up > 0.5 && drj1l2_JER_up > 0.5 && drj2l2_JER_up > 0.5 /*&& deltaeta_JER_up > 1.9 && delta_phi_JER_up >2.14 && zepp_JER_up < 1.18*/) {
			if(Mjj_JER_up>=500&&Mjj_JER_up<800&&deltaeta_JER_up>=2.5&&deltaeta_JER_up<4.5) mjj_JER_up->Fill(0.5,actualWeight);
                        if(Mjj_JER_up>=800&&Mjj_JER_up<1200&&deltaeta_JER_up>=2.5&&deltaeta_JER_up<4.5) mjj_JER_up->Fill(1.5,actualWeight);
                        if(Mjj_JER_up>=1200&&deltaeta_JER_up>=2.5&&deltaeta_JER_up<4.5) mjj_JER_up->Fill(2.5,actualWeight);
                        if(Mjj_JER_up>=500&&Mjj_JER_up<800&&deltaeta_JER_up>=4.5&&deltaeta_JER_up<6) mjj_JER_up->Fill(3.5,actualWeight);
                        if(Mjj_JER_up>=800&&Mjj_JER_up<1200&&deltaeta_JER_up>=4.5&&deltaeta_JER_up<6) mjj_JER_up->Fill(4.5,actualWeight);
                        if(Mjj_JER_up>=1200&&deltaeta_JER_up>=4.5&&deltaeta_JER_up<6) mjj_JER_up->Fill(5.5,actualWeight);
                        if(Mjj_JER_up>=500&&Mjj_JER_up<800&&deltaeta_JER_up>=6) mjj_JER_up->Fill(6.5,actualWeight);
                        if(Mjj_JER_up>=800&&Mjj_JER_up<1200&&deltaeta_JER_up>=6) mjj_JER_up->Fill(7.5,actualWeight);
                        if(Mjj_JER_up>=1200&&deltaeta_JER_up>=6) mjj_JER_up->Fill(8.5,actualWeight);
		}

		// fill histo smeared jet JER down
		if ( HLT_Mu2 > 0 && lep == 13 && nlooseeles == 0 && nloosemus < 3 && massVlep > 70 && massVlep < 110 && ptlep1 > 20. && ptlep2 > 20. && fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4&& photonet > 20. && fabs(photoneta) < 1.4442 && jet1pt_JER_down> 30 && jet2pt_JER_down > 30 && fabs(jet1eta_JER_down)< 4.7 && fabs(jet2eta_JER_down)<4.7 && Mjj_JER_down > 150 && drla > 0.7 && drla2 > 0.7 && drj1a_JER_down > 0.5 && drj2a_JER_down > 0.5  && drjj_JER_down> 0.5 && drj1l_JER_down > 0.5 && drj2l_JER_down > 0.5 && drj1l2_JER_down > 0.5 && drj2l2_JER_down > 0.5/* && deltaeta_JER_down > 1.9 && delta_phi_JER_down >2.14 && zepp_JER_down < 1.18*/) {
			if(Mjj_JER_down>=500&&Mjj_JER_down<800&&deltaeta_JER_down>=2.5&&deltaeta_JER_down<4.5) mjj_JER_down->Fill(0.5,actualWeight);
                        if(Mjj_JER_down>=800&&Mjj_JER_down<1200&&deltaeta_JER_down>=2.5&&deltaeta_JER_down<4.5) mjj_JER_down->Fill(1.5,actualWeight);
                        if(Mjj_JER_down>=1200&&deltaeta_JER_down>=2.5&&deltaeta_JER_down<4.5) mjj_JER_down->Fill(2.5,actualWeight);
                        if(Mjj_JER_down>=500&&Mjj_JER_down<800&&deltaeta_JER_down>=4.5&&deltaeta_JER_down<6) mjj_JER_down->Fill(3.5,actualWeight);
                        if(Mjj_JER_down>=800&&Mjj_JER_down<1200&&deltaeta_JER_down>=4.5&&deltaeta_JER_down<6) mjj_JER_down->Fill(4.5,actualWeight);
                        if(Mjj_JER_down>=1200&&deltaeta_JER_down>=4.5&&deltaeta_JER_down<6) mjj_JER_down->Fill(5.5,actualWeight);
                        if(Mjj_JER_down>=500&&Mjj_JER_down<800&&deltaeta_JER_down>=6) mjj_JER_down->Fill(6.5,actualWeight);
                        if(Mjj_JER_down>=800&&Mjj_JER_down<1200&&deltaeta_JER_down>=6) mjj_JER_down->Fill(7.5,actualWeight);
                        if(Mjj_JER_down>=1200&&deltaeta_JER_down>=6) mjj_JER_down->Fill(8.5,actualWeight);
		}
	}

	output->cd();

	std::cout<<"sig_count "<<sig_count<<std::endl;
	mjj->Write();
        mjj_new->Write();
        mjj_JEC_up->Write();
        mjj_JEC_down->Write();
        mjj_JER_up->Write();
        mjj_JER_down->Write();
}

int JECR(){
        Jecr();
        return 1;
}
