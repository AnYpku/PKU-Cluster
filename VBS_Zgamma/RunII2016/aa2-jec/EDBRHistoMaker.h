#include "TGraphAsymmErrors.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTree.h"
#include "TChain.h"
#include "math.h"
#include "TLorentzVector.h"
#include "RoccoR.C"
#include "get_rochester_scale.C"
#define Pi 3.1415926
using namespace std;
/// The large arrays that were here are now GONE.
/// Instead, we have this helper that holds the
/// information of all our histograms.

class HistoFactory {
	public:
		std::vector<std::string> vars;
		std::vector<int> nBins;
		std::vector<double> minBin;
		std::vector<double> maxBin;
		void setHisto(std::string s, int n, double min, double max) {
			vars.push_back(s);
			nBins.push_back(n);
			minBin.push_back(min);
			maxBin.push_back(max);
		}
};

class EDBRHistoMaker {
	public:
		EDBRHistoMaker(TTree *tree = 0, TFile *fileTMP = 0, TH1F* hR1 = 0, std::string out_name_="", RoccoR* rc_in=0);
		virtual ~EDBRHistoMaker();

		/// This is the tree structure. This comes directly from MakeClass
		TTree* fChain;   //!pointer to the analyzed TTree or TChain
		TFile* fileTMP_;
		TH1F* hR1_;
		Int_t fCurrent; //!current Tree number in a TChain
		bool setUnitaryWeights_;

		// Declaration of leaf types
		Double_t drll;
		Double_t muon1_rochester;
                Double_t muon2_rochester;
                Double_t deltaetajj;
                Double_t actualWeight;
                Double_t detajj;
                Double_t ZGmass;//need to be modified for rochester
                Double_t delta_phi;//need to be modified for rochester
                Double_t drjj;

   Double_t l1_weight;
   Double_t scalef;
   Double_t test;
   Double_t run_period;
   Int_t           event;
   Int_t           nVtx;
   Double_t        theWeight;
   Double_t        nump;
   Double_t        numm;
   Double_t        pweight[703];
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
   Double_t        jet1pt_f;
   Double_t        jet1pt_new_f;
   Double_t        jet1pt_JEC_up_f;
   Double_t        jet1pt_JER_up_f;
   Double_t        jet1pt_JEC_down_f;
   Double_t        jet1pt_JER_down_f;
   Double_t        jet1eta;
   Double_t        jet1eta_new;
   Double_t        jet1eta_JEC_up;
   Double_t        jet1eta_JEC_down;
   Double_t        jet1eta_JER_up;
   Double_t        jet1eta_JER_down;
   Double_t        jet1eta_f;
   Double_t        jet1eta_new_f;
   Double_t        jet1eta_JEC_up_f;
   Double_t        jet1eta_JEC_down_f;
   Double_t        jet1eta_JER_up_f;
   Double_t        jet1eta_JER_down_f;
   Double_t        jet1phi;
   Double_t        jet1phi_new;
   Double_t        jet1phi_JEC_up;
   Double_t        jet1phi_JEC_down;
   Double_t        jet1phi_JER_up;
   Double_t        jet1phi_JER_down;
   Double_t        jet1phi_f;
   Double_t        jet1phi_new_f;
   Double_t        jet1phi_JEC_up_f;
   Double_t        jet1phi_JEC_down_f;
   Double_t        jet1phi_JER_up_f;
   Double_t        jet1phi_JER_down_f;
   Double_t        jet1e;
   Double_t        jet1e_new;
   Double_t        jet1e_JEC_up;
   Double_t        jet1e_JER_up;
   Double_t        jet1e_JEC_down;
   Double_t        jet1e_JER_down;
   Double_t        jet1e_f;
   Double_t        jet1e_new_f;
   Double_t        jet1e_JEC_up_f;
   Double_t        jet1e_JER_up_f;
   Double_t        jet1e_JEC_down_f;
   Double_t        jet1e_JER_down_f;
   Double_t        jet1csv;
   Double_t        jet1csv_new;
   Double_t        jet1csv_JEC_up;
   Double_t        jet1csv_JER_up;
   Double_t        jet1csv_JEC_down;
   Double_t        jet1csv_JER_down;
   Double_t        jet1csv_f;
   Double_t        jet1csv_new_f;
   Double_t        jet1csv_JEC_up_f;
   Double_t        jet1csv_JER_up_f;
   Double_t        jet1csv_JEC_down_f;
   Double_t        jet1csv_JER_down_f;
   Double_t        jet1icsv;
   Double_t        jet1icsv_new;
   Double_t        jet1icsv_JEC_up;
   Double_t        jet1icsv_JER_up;
   Double_t        jet1icsv_JEC_down;
   Double_t        jet1icsv_JER_down;
   Double_t        jet1icsv_f;
   Double_t        jet1icsv_new_f;
   Double_t        jet1icsv_JEC_up_f;
   Double_t        jet1icsv_JER_up_f;
   Double_t        jet1icsv_JEC_down_f;
   Double_t        jet1icsv_JER_down_f;
   Double_t        jet2pt;
   Double_t        jet2pt_new;
   Double_t        jet2pt_JEC_up;
   Double_t        jet2pt_JER_up;
   Double_t        jet2pt_JEC_down;
   Double_t        jet2pt_JER_down;
   Double_t        jet2pt_f;
   Double_t        jet2pt_new_f;
   Double_t        jet2pt_JEC_up_f;
   Double_t        jet2pt_JER_up_f;
   Double_t        jet2pt_JEC_down_f;
   Double_t        jet2pt_JER_down_f;
   Double_t        jet2eta;
   Double_t        jet2eta_new;
   Double_t        jet2eta_JEC_up;
   Double_t        jet2eta_JEC_down;
   Double_t        jet2eta_JER_up;
   Double_t        jet2eta_JER_down;
   Double_t        jet2eta_f;
   Double_t        jet2phi;
   Double_t        jet2phi_new;
   Double_t        jet2phi_JEC_up;
   Double_t        jet2phi_JEC_down;
   Double_t        jet2phi_JER_up;
   Double_t        jet2phi_JER_down;
   Double_t        jet2phi_f;
   Double_t        jet2phi_new_f;
   Double_t        jet2phi_JEC_up_f;
   Double_t        jet2phi_JEC_down_f;
   Double_t        jet2phi_JER_up_f;
   Double_t        jet2phi_JER_down_f;
   Double_t        jet2eta_new_f;
   Double_t        jet2eta_JEC_up_f;
   Double_t        jet2eta_JEC_down_f;
   Double_t        jet2eta_JER_up_f;
   Double_t        jet2eta_JER_down_f;
   Double_t        jet2e;
   Double_t        jet2e_new;
   Double_t        jet2e_JEC_up;
   Double_t        jet2e_JER_up;
   Double_t        jet2e_JEC_down;
   Double_t        jet2e_JER_down;
   Double_t        jet2e_f;
   Double_t        jet2e_new_f;
   Double_t        jet2e_JEC_up_f;
   Double_t        jet2e_JER_up_f;
   Double_t        jet2e_JEC_down_f;
   Double_t        jet2e_JER_down_f;
   Double_t        jet2csv;
   Double_t        jet2csv_new;
   Double_t        jet2csv_JEC_up;
   Double_t        jet2csv_JER_up;
   Double_t        jet2csv_JEC_down;
   Double_t        jet2csv_JER_down;
   Double_t        jet2csv_f;
   Double_t        jet2csv_new_f;
   Double_t        jet2csv_JEC_up_f;
   Double_t        jet2csv_JER_up_f;
   Double_t        jet2csv_JEC_down_f;
   Double_t        jet2csv_JER_down_f;
   Double_t        jet2icsv;
   Double_t        jet2icsv_new;
   Double_t        jet2icsv_JEC_up;
   Double_t        jet2icsv_JER_up;
   Double_t        jet2icsv_JEC_down;
   Double_t        jet2icsv_JER_down;
   Double_t        jet2icsv_f;
   Double_t        jet2icsv_new_f;
   Double_t        jet2icsv_JEC_up_f;
   Double_t        jet2icsv_JER_up_f;
   Double_t        jet2icsv_JEC_down_f;
   Double_t        jet2icsv_JER_down_f;
   Double_t        drj1a;
   Double_t        drj1a_new;
   Double_t        drj1a_JEC_up;
   Double_t        drj1a_JEC_down;
   Double_t        drj1a_JER_up;
   Double_t        drj1a_JER_down;
   Double_t        drj1a_f;
   Double_t        drj1a_new_f;
   Double_t        drj1a_JEC_up_f;
   Double_t        drj1a_JEC_down_f;
   Double_t        drj1a_JER_up_f;
   Double_t        drj1a_JER_down_f;
   Double_t        drj2a;
   Double_t        drj2a_new;
   Double_t        drj2a_JEC_up;
   Double_t        drj2a_JEC_down;
   Double_t        drj2a_JER_up;
   Double_t        drj2a_JER_down;
   Double_t        drj2a_f;
   Double_t        drj2a_new_f;
   Double_t        drj2a_JEC_up_f;
   Double_t        drj2a_JEC_down_f;
   Double_t        drj2a_JER_up_f;
   Double_t        drj2a_JER_down_f;
   Double_t        drj1l;
   Double_t        drj1l_new;
   Double_t        drj1l_JEC_up;
   Double_t        drj1l_JEC_down;
   Double_t        drj1l_JER_up;
   Double_t        drj1l_JER_down;
   Double_t        drj1l_f;
   Double_t        drj1l_new_f;
   Double_t        drj1l_JEC_up_f;
   Double_t        drj1l_JEC_down_f;
   Double_t        drj1l_JER_up_f;
   Double_t        drj1l_JER_down_f;
   Double_t        drj2l;
   Double_t        drj2l_new;
   Double_t        drj2l_JEC_up;
   Double_t        drj2l_JEC_down;
   Double_t        drj2l_JER_up;
   Double_t        drj2l_JER_down;
   Double_t        drj2l_f;
   Double_t        drj2l_new_f;
   Double_t        drj2l_JEC_up_f;
   Double_t        drj2l_JEC_down_f;
   Double_t        drj2l_JER_up_f;
   Double_t        drj2l_JER_down_f;
   Double_t        drj1l2;
   Double_t        drj1l2_new;
   Double_t        drj1l2_JEC_up;
   Double_t        drj1l2_JEC_down;
   Double_t        drj1l2_JER_up;
   Double_t        drj1l2_JER_down;
   Double_t        drj1l2_f;
   Double_t        drj1l2_new_f;
   Double_t        drj1l2_JEC_up_f;
   Double_t        drj1l2_JEC_down_f;
   Double_t        drj1l2_JER_up_f;
   Double_t        drj1l2_JER_down_f;
   Double_t        drj2l2;
   Double_t        drj2l2_new;
   Double_t        drj2l2_JEC_up;
   Double_t        drj2l2_JEC_down;
   Double_t        drj2l2_JER_up;
   Double_t        drj2l2_JER_down;
   Double_t        drj2l2_f;
   Double_t        drj2l2_new_f;
   Double_t        drj2l2_JEC_up_f;
   Double_t        drj2l2_JEC_down_f;
   Double_t        drj2l2_JER_up_f;
   Double_t        drj2l2_JER_down_f;
   Double_t        Mjj;
   Double_t        Mjj_new;
   Double_t        Mjj_JEC_up;
   Double_t        Mjj_JEC_down;
   Double_t        Mjj_JER_up;
   Double_t        Mjj_JER_down;
   Double_t        Mjj_f;
   Double_t        Mjj_new_f;
   Double_t        Mjj_JEC_up_f;
   Double_t        Mjj_JEC_down_f;
   Double_t        Mjj_JER_up_f;
   Double_t        Mjj_JER_down_f;
   Double_t        deltaeta;
   Double_t        deltaeta_new;
   Double_t        deltaeta_JEC_up;
   Double_t        deltaeta_JEC_down;
   Double_t        deltaeta_JER_up;
   Double_t        deltaeta_JER_down;
   Double_t        deltaeta_f;
   Double_t        deltaeta_new_f;
   Double_t        deltaeta_JEC_up_f;
   Double_t        deltaeta_JEC_down_f;
   Double_t        deltaeta_JER_up_f;
   Double_t        deltaeta_JER_down_f;
   Double_t        zepp;
   Double_t        zepp_new;
   Double_t        zepp_JEC_up;
   Double_t        zepp_JEC_down;
   Double_t        zepp_JER_up;
   Double_t        zepp_JER_down;
   Double_t        zepp_f;
   Double_t        zepp_new_f;
   Double_t        zepp_JEC_up_f;
   Double_t        zepp_JEC_down_f;
   Double_t        zepp_JER_up_f;
   Double_t        zepp_JER_down_f;
   Double_t        ptlep1;
   Double_t        etalep1;
   Double_t        philep1;
   Double_t        ptlep2;
   Double_t        etalep2;
   Double_t        philep2;
   Double_t        j1metPhi;
   Double_t        j1metPhi_new;
   Double_t        j1metPhi_JEC_up;
   Double_t        j1metPhi_JEC_down;
   Double_t        j1metPhi_JER_up;
   Double_t        j1metPhi_JER_down;
   Double_t        j1metPhi_f;
   Double_t        j1metPhi_new_f;
   Double_t        j1metPhi_JEC_up_f;
   Double_t        j1metPhi_JEC_down_f;
   Double_t        j1metPhi_JER_up_f;
   Double_t        j1metPhi_JER_down_f;
   Double_t        j2metPhi;
   Double_t        j2metPhi_new;
   Double_t        j2metPhi_JEC_up;
   Double_t        j2metPhi_JEC_down;
   Double_t        j2metPhi_JER_up;
   Double_t        j2metPhi_JER_down;
   Double_t        j2metPhi_f;
   Double_t        j2metPhi_new_f;
   Double_t        j2metPhi_JEC_up_f;
   Double_t        j2metPhi_JEC_down_f;
   Double_t        j2metPhi_JER_up_f;
   Double_t        j2metPhi_JER_down_f;
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
   Int_t           HLT_Mu7;
   Int_t           HLT_Mu8;
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
// lep and photon scales
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
// lep and photn scales

// for muon rochester correction
   Int_t           muon1_trackerLayers;
   Double_t        matchedgenMu1_pt;
   Int_t           muon2_trackerLayers;
   Double_t        matchedgenMu2_pt;
// Double_t      mu1_rochester_scale;
// Double_t      mu2_rochester_scale;
// for muon rochester correction

   // List of branches
   TBranch        *b_ele1_id_scale;
   TBranch        *b_ele2_id_scale;
   TBranch        *b_ele1_reco_scale;
   TBranch        *b_ele2_reco_scale;
   TBranch        *b_photon_id_scale;
   TBranch        *b_muon1_id_scale;
   TBranch        *b_muon2_id_scale;
   TBranch        *b_muon1_iso_scale;
   TBranch        *b_muon2_iso_scale;
   TBranch        *b_muon1_track_scale;
   TBranch        *b_muon2_track_scale;
   TBranch        *b_muon_hlt_scale;

   TBranch        *b_scalef;
   TBranch        *b_event;   //!
   TBranch        *b_nVtx;   //!
   TBranch        *b_theWeight;   //!
   TBranch        *b_nump;   //!
   TBranch        *b_numm;   //!
   TBranch        *b_pweight;   //!
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
   TBranch        *b_jet1pt_f;   //!
   TBranch        *b_jet1pt_new_f;   //!
   TBranch        *b_jet1pt_JEC_up_f;   //!
   TBranch        *b_jet1pt_JER_up_f;   //!
   TBranch        *b_jet1pt_JEC_down_f;   //!
   TBranch        *b_jet1pt_JER_down_f;   //!
   TBranch        *b_jet1eta;   //!
   TBranch        *b_jet1eta_new;   //!
   TBranch        *b_jet1eta_JEC_up;   //!
   TBranch        *b_jet1eta_JEC_down;   //!
   TBranch        *b_jet1eta_JER_up;   //!
   TBranch        *b_jet1eta_JER_down;   //!
   TBranch        *b_jet1eta_f;   //!
   TBranch        *b_jet1eta_new_f;   //!
   TBranch        *b_jet1eta_JEC_up_f;   //!
   TBranch        *b_jet1eta_JEC_down_f;   //!
   TBranch        *b_jet1eta_JER_up_f;   //!
   TBranch        *b_jet1eta_JER_down_f;   //!
   TBranch        *b_jet1phi;   //!
   TBranch        *b_jet1phi_new;   //!
   TBranch        *b_jet1phi_JEC_up;   //!
   TBranch        *b_jet1phi_JEC_down;   //!
   TBranch        *b_jet1phi_JER_up;   //!
   TBranch        *b_jet1phi_JER_down;   //!
   TBranch        *b_jet1phi_f;   //!
   TBranch        *b_jet1phi_new_f;   //!
   TBranch        *b_jet1phi_JEC_up_f;   //!
   TBranch        *b_jet1phi_JEC_down_f;   //!
   TBranch        *b_jet1phi_JER_up_f;   //!
   TBranch        *b_jet1phi_JER_down_f;   //!
   TBranch        *b_jet1e;   //!
   TBranch        *b_jet1e_new;   //!
   TBranch        *b_jet1e_JEC_up;   //!
   TBranch        *b_jet1e_JER_up;   //!
   TBranch        *b_jet1e_JEC_down;   //!
   TBranch        *b_jet1e_JER_down;   //!
   TBranch        *b_jet1e_f;   //!
   TBranch        *b_jet1e_new_f;   //!
   TBranch        *b_jet1e_JEC_up_f;   //!
   TBranch        *b_jet1e_JER_up_f;   //!
   TBranch        *b_jet1e_JEC_down_f;   //!
   TBranch        *b_jet1e_JER_down_f;   //!
   TBranch        *b_jet1csv;   //!
   TBranch        *b_jet1csv_new;   //!
   TBranch        *b_jet1csv_JEC_up;   //!
   TBranch        *b_jet1csv_JER_up;   //!
   TBranch        *b_jet1csv_JEC_down;   //!
   TBranch        *b_jet1csv_JER_down;   //!
   TBranch        *b_jet1csv_f;   //!
   TBranch        *b_jet1csv_new_f;   //!
   TBranch        *b_jet1csv_JEC_up_f;   //!
   TBranch        *b_jet1csv_JER_up_f;   //!
   TBranch        *b_jet1csv_JEC_down_f;   //!
   TBranch        *b_jet1csv_JER_down_f;   //!
   TBranch        *b_jet1icsv;   //!
   TBranch        *b_jet1icsv_new;   //!
   TBranch        *b_jet1icsv_JEC_up;   //!
   TBranch        *b_jet1icsv_JER_up;   //!
   TBranch        *b_jet1icsv_JEC_down;   //!
   TBranch        *b_jet1icsv_JER_down;   //!
   TBranch        *b_jet1icsv_f;   //!
   TBranch        *b_jet1icsv_new_f;   //!
   TBranch        *b_jet1icsv_JEC_up_f;   //!
   TBranch        *b_jet1icsv_JER_up_f;   //!
   TBranch        *b_jet1icsv_JEC_down_f;   //!
   TBranch        *b_jet1icsv_JER_down_f;   //!
   TBranch        *b_jet2pt;   //!
   TBranch        *b_jet2pt_new;   //!
   TBranch        *b_jet2pt_JEC_up;   //!
   TBranch        *b_jet2pt_JER_up;   //!
   TBranch        *b_jet2pt_JEC_down;   //!
   TBranch        *b_jet2pt_JER_down;   //!
   TBranch        *b_jet2pt_f;   //!
   TBranch        *b_jet2pt_new_f;   //!
   TBranch        *b_jet2pt_JEC_up_f;   //!
   TBranch        *b_jet2pt_JER_up_f;   //!
   TBranch        *b_jet2pt_JEC_down_f;   //!
   TBranch        *b_jet2pt_JER_down_f;   //!
   TBranch        *b_jet2eta;   //!
   TBranch        *b_jet2eta_new;   //!
   TBranch        *b_jet2eta_JEC_up;   //!
   TBranch        *b_jet2eta_JEC_down;   //!
   TBranch        *b_jet2eta_JER_up;   //!
   TBranch        *b_jet2eta_JER_down;   //!
   TBranch        *b_jet2eta_f;   //!
   TBranch        *b_jet2phi;   //!
   TBranch        *b_jet2phi_new;   //!
   TBranch        *b_jet2phi_JEC_up;   //!
   TBranch        *b_jet2phi_JEC_down;   //!
   TBranch        *b_jet2phi_JER_up;   //!
   TBranch        *b_jet2phi_JER_down;   //!
   TBranch        *b_jet2phi_f;   //!
   TBranch        *b_jet2phi_new_f;   //!
   TBranch        *b_jet2phi_JEC_up_f;   //!
   TBranch        *b_jet2phi_JEC_down_f;   //!
   TBranch        *b_jet2phi_JER_up_f;   //!
   TBranch        *b_jet2phi_JER_down_f;   //!
   TBranch        *b_jet2eta_new_f;   //!
   TBranch        *b_jet2eta_JEC_up_f;   //!
   TBranch        *b_jet2eta_JEC_down_f;   //!
   TBranch        *b_jet2eta_JER_up_f;   //!
   TBranch        *b_jet2eta_JER_down_f;   //!
   TBranch        *b_jet2e;   //!
   TBranch        *b_jet2e_new;   //!
   TBranch        *b_jet2e_JEC_up;   //!
   TBranch        *b_jet2e_JER_up;   //!
   TBranch        *b_jet2e_JEC_down;   //!
   TBranch        *b_jet2e_JER_down;   //!
   TBranch        *b_jet2e_f;   //!
   TBranch        *b_jet2e_new_f;   //!
   TBranch        *b_jet2e_JEC_up_f;   //!
   TBranch        *b_jet2e_JER_up_f;   //!
   TBranch        *b_jet2e_JEC_down_f;   //!
   TBranch        *b_jet2e_JER_down_f;   //!
   TBranch        *b_jet2csv;   //!
   TBranch        *b_jet2csv_new;   //!
   TBranch        *b_jet2csv_JEC_up;   //!
   TBranch        *b_jet2csv_JER_up;   //!
   TBranch        *b_jet2csv_JEC_down;   //!
   TBranch        *b_jet2csv_JER_down;   //!
   TBranch        *b_jet2csv_f;   //!
   TBranch        *b_jet2csv_new_f;   //!
   TBranch        *b_jet2csv_JEC_up_f;   //!
   TBranch        *b_jet2csv_JER_up_f;   //!
   TBranch        *b_jet2csv_JEC_down_f;   //!
   TBranch        *b_jet2csv_JER_down_f;   //!
   TBranch        *b_jet2icsv;   //!
   TBranch        *b_jet2icsv_new;   //!
   TBranch        *b_jet2icsv_JEC_up;   //!
   TBranch        *b_jet2icsv_JER_up;   //!
   TBranch        *b_jet2icsv_JEC_down;   //!
   TBranch        *b_jet2icsv_JER_down;   //!
   TBranch        *b_jet2icsv_f;   //!
   TBranch        *b_jet2icsv_new_f;   //!
   TBranch        *b_jet2icsv_JEC_up_f;   //!
   TBranch        *b_jet2icsv_JER_up_f;   //!
   TBranch        *b_jet2icsv_JEC_down_f;   //!
   TBranch        *b_jet2icsv_JER_down_f;   //!
   TBranch        *b_drj1a;   //!
   TBranch        *b_drj1a_new;   //!
   TBranch        *b_drj1a_JEC_up;   //!
   TBranch        *b_drj1a_JEC_down;   //!
   TBranch        *b_drj1a_JER_up;   //!
   TBranch        *b_drj1a_JER_down;   //!
   TBranch        *b_drj1a_f;   //!
   TBranch        *b_drj1a_new_f;   //!
   TBranch        *b_drj1a_JEC_up_f;   //!
   TBranch        *b_drj1a_JEC_down_f;   //!
   TBranch        *b_drj1a_JER_up_f;   //!
   TBranch        *b_drj1a_JER_down_f;   //!
   TBranch        *b_drj2a;   //!
   TBranch        *b_drj2a_new;   //!
   TBranch        *b_drj2a_JEC_up;   //!
   TBranch        *b_drj2a_JEC_down;   //!
   TBranch        *b_drj2a_JER_up;   //!
   TBranch        *b_drj2a_JER_down;   //!
   TBranch        *b_drj2a_f;   //!
   TBranch        *b_drj2a_new_f;   //!
   TBranch        *b_drj2a_JEC_up_f;   //!
   TBranch        *b_drj2a_JEC_down_f;   //!
   TBranch        *b_drj2a_JER_up_f;   //!
   TBranch        *b_drj2a_JER_down_f;   //!
   TBranch        *b_drj1l;   //!
   TBranch        *b_drj1l_new;   //!
   TBranch        *b_drj1l_JEC_up;   //!
   TBranch        *b_drj1l_JEC_down;   //!
   TBranch        *b_drj1l_JER_up;   //!
   TBranch        *b_drj1l_JER_down;   //!
   TBranch        *b_drj1l_f;   //!
   TBranch        *b_drj1l_new_f;   //!
   TBranch        *b_drj1l_JEC_up_f;   //!
   TBranch        *b_drj1l_JEC_down_f;   //!
   TBranch        *b_drj1l_JER_up_f;   //!
   TBranch        *b_drj1l_JER_down_f;   //!
   TBranch        *b_drj2l;   //!
   TBranch        *b_drj2l_new;   //!
   TBranch        *b_drj2l_JEC_up;   //!
   TBranch        *b_drj2l_JEC_down;   //!
   TBranch        *b_drj2l_JER_up;   //!
   TBranch        *b_drj2l_JER_down;   //!
   TBranch        *b_drj2l_f;   //!
   TBranch        *b_drj2l_new_f;   //!
   TBranch        *b_drj2l_JEC_up_f;   //!
   TBranch        *b_drj2l_JEC_down_f;   //!
   TBranch        *b_drj2l_JER_up_f;   //!
   TBranch        *b_drj2l_JER_down_f;   //!
   TBranch        *b_drj1l2;   //!
   TBranch        *b_drj1l2_new;   //!
   TBranch        *b_drj1l2_JEC_up;   //!
   TBranch        *b_drj1l2_JEC_down;   //!
   TBranch        *b_drj1l2_JER_up;   //!
   TBranch        *b_drj1l2_JER_down;   //!
   TBranch        *b_drj1l2_f;   //!
   TBranch        *b_drj1l2_new_f;   //!
   TBranch        *b_drj1l2_JEC_up_f;   //!
   TBranch        *b_drj1l2_JEC_down_f;   //!
   TBranch        *b_drj1l2_JER_up_f;   //!
   TBranch        *b_drj1l2_JER_down_f;   //!
   TBranch        *b_drj2l2;   //!
   TBranch        *b_drj2l2_new;   //!
   TBranch        *b_drj2l2_JEC_up;   //!
   TBranch        *b_drj2l2_JEC_down;   //!
   TBranch        *b_drj2l2_JER_up;   //!
   TBranch        *b_drj2l2_JER_down;   //!
   TBranch        *b_drj2l2_f;   //!
   TBranch        *b_drj2l2_new_f;   //!
   TBranch        *b_drj2l2_JEC_up_f;   //!
   TBranch        *b_drj2l2_JEC_down_f;   //!
   TBranch        *b_drj2l2_JER_up_f;   //!
   TBranch        *b_drj2l2_JER_down_f;   //!
   TBranch        *b_Mjj;   //!
   TBranch        *b_Mjj_new;   //!
   TBranch        *b_Mjj_JEC_up;   //!
   TBranch        *b_Mjj_JEC_down;   //!
   TBranch        *b_Mjj_JER_up;   //!
   TBranch        *b_Mjj_JER_down;   //!
   TBranch        *b_Mjj_f;   //!
   TBranch        *b_Mjj_new_f;   //!
   TBranch        *b_Mjj_JEC_up_f;   //!
   TBranch        *b_Mjj_JEC_down_f;   //!
   TBranch        *b_Mjj_JER_up_f;   //!
   TBranch        *b_Mjj_JER_down_f;   //!
   TBranch        *b_deltaeta;   //!
   TBranch        *b_deltaeta_new;   //!
   TBranch        *b_deltaeta_JEC_up;   //!
   TBranch        *b_deltaeta_JEC_down;   //!
   TBranch        *b_deltaeta_JER_up;   //!
   TBranch        *b_deltaeta_JER_down;   //!
   TBranch        *b_deltaeta_f;   //!
   TBranch        *b_deltaeta_new_f;   //!
   TBranch        *b_deltaeta_JEC_up_f;   //!
   TBranch        *b_deltaeta_JEC_down_f;   //!
   TBranch        *b_deltaeta_JER_up_f;   //!
   TBranch        *b_deltaeta_JER_down_f;   //!
   TBranch        *b_zepp;   //!
   TBranch        *b_zepp_new;   //!
   TBranch        *b_zepp_JEC_up;   //!
   TBranch        *b_zepp_JEC_down;   //!
   TBranch        *b_zepp_JER_up;   //!
   TBranch        *b_zepp_JER_down;   //!
   TBranch        *b_zepp_f;   //!
   TBranch        *b_zepp_new_f;   //!
   TBranch        *b_zepp_JEC_up_f;   //!
   TBranch        *b_zepp_JEC_down_f;   //!
   TBranch        *b_zepp_JER_up_f;   //!
   TBranch        *b_zepp_JER_down_f;   //!
   TBranch        *b_ptlep1;   //!
   TBranch        *b_etalep1;   //!
   TBranch        *b_philep1;   //!
   TBranch        *b_ptlep2;   //!
   TBranch        *b_etalep2;   //!
   TBranch        *b_philep2;   //!
   TBranch        *b_j1metPhi;   //!
   TBranch        *b_j1metPhi_new;   //!
   TBranch        *b_j1metPhi_JEC_up;   //!
   TBranch        *b_j1metPhi_JEC_down;   //!
   TBranch        *b_j1metPhi_JER_up;   //!
   TBranch        *b_j1metPhi_JER_down;   //!
   TBranch        *b_j1metPhi_f;   //!
   TBranch        *b_j1metPhi_new_f;   //!
   TBranch        *b_j1metPhi_JEC_up_f;   //!
   TBranch        *b_j1metPhi_JEC_down_f;   //!
   TBranch        *b_j1metPhi_JER_up_f;   //!
   TBranch        *b_j1metPhi_JER_down_f;   //!
   TBranch        *b_j2metPhi;   //!
   TBranch        *b_j2metPhi_new;   //!
   TBranch        *b_j2metPhi_JEC_up;   //!
   TBranch        *b_j2metPhi_JEC_down;   //!
   TBranch        *b_j2metPhi_JER_up;   //!
   TBranch        *b_j2metPhi_JER_down;   //!
   TBranch        *b_j2metPhi_f;   //!
   TBranch        *b_j2metPhi_new_f;   //!
   TBranch        *b_j2metPhi_JEC_up_f;   //!
   TBranch        *b_j2metPhi_JEC_down_f;   //!
   TBranch        *b_j2metPhi_JER_up_f;   //!
   TBranch        *b_j2metPhi_JER_down_f;   //!
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
   TBranch        *b_HLT_Mu7;   //!
   TBranch        *b_HLT_Mu8;   //!
   TBranch        *b_passFilter_HBHE_;   //!
   TBranch        *b_passFilter_HBHEIso_;   //!
   TBranch        *b_passFilter_globalTightHalo_;   //!
   TBranch        *b_passFilter_ECALDeadCell_;   //!
   TBranch        *b_passFilter_GoodVtx_;   //!
   TBranch        *b_passFilter_EEBadSc_;   //!
   TBranch        *b_passFilter_badMuon_;   //!
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
//for muon rochester correction
   TBranch        *b_muon1_trackerLayers;   //!
   TBranch        *b_matchedgenMu1_pt;   //!
   TBranch        *b_muon2_trackerLayers;   //!
   TBranch        *b_matchedgenMu2_pt;   //!

		// Basic functions directly from MakeClass
		Int_t GetEntry(Long64_t entry);
		Long64_t LoadTree(Long64_t entry);
		void Init(TTree *tree);
		void Loop(std::string outFileName);
		void Loop_SFs_mc(std::string outFileName);
		// Our added functions
		void createAllHistos();
		void printAllHistos();
		void saveAllHistos(std::string outFileName);
		void setUnitaryWeights(bool setuniw = false) {
			setUnitaryWeights_ = setuniw;
		}

		int check(double pt, std::vector<double> * ptZ) {
			int goodw = 1;
			for (unsigned int i = 0; i < ptZ->size(); i++) {
				if (pt == ptZ->at(i)) {
					goodw = 0;
					break;
				}
			}

			return goodw;
		}
		// Our added variables
		int nVars;
		bool debug_;

		///meng
		TTree *treename;
		TFile *fout;
		std::string out_name;
		void endjob(){
			fout->cd();
			treename->Write();
			fout->Write();
			fout->Close();
			delete fout;
		}
		///lu
		// fro rochester correction
		RoccoR rc;
		double get_rochester_scale(bool isdata, double charge_temp, double pt, double eta, double phi, int nl, double genPt, double r1, double r2);


		// The histograms
		HistoFactory hs;
		std::map<std::string, TH1D*> theHistograms;
		TH2D *hmjmzz;
		TH1D *hmzzNEW;
};

void EDBRHistoMaker::Init(TTree *tree) {
	// The Init() function is called when the selector needs to initialize
	// a new tree or chain. Typically here the branch addresses and branch
	// pointers of the tree will be set.
	// It is normally not necessary to make changes to the generated
	// code, but the routine can be extended by the user if needed.
	// Init() will be called many times when running on PROOF
	// (once per file to be processed).

	// Set branch addresses and branch pointers
	if (!tree)
		return;
	fChain = tree;
	fCurrent = -1;
	fChain->SetMakeClass(1);

	fout = new TFile(out_name.c_str(), "RECREATE");
	cout<<"begin make outfile tree"<<endl;
	treename = fChain->CloneTree(0);
	cout<<"make outfile tree end"<<endl;
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
   fChain->SetBranchAddress("scalef", &scalef, &b_scalef);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
   fChain->SetBranchAddress("theWeight", &theWeight, &b_theWeight);
   fChain->SetBranchAddress("nump", &nump, &b_nump);
   fChain->SetBranchAddress("numm", &numm, &b_numm);
   fChain->SetBranchAddress("pweight", pweight, &b_pweight);
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
   fChain->SetBranchAddress("jet1pt_f", &jet1pt_f, &b_jet1pt_f);
   fChain->SetBranchAddress("jet1pt_new_f", &jet1pt_new_f, &b_jet1pt_new_f);
   fChain->SetBranchAddress("jet1pt_JEC_up_f", &jet1pt_JEC_up_f, &b_jet1pt_JEC_up_f);
   fChain->SetBranchAddress("jet1pt_JER_up_f", &jet1pt_JER_up_f, &b_jet1pt_JER_up_f);
   fChain->SetBranchAddress("jet1pt_JEC_down_f", &jet1pt_JEC_down_f, &b_jet1pt_JEC_down_f);
   fChain->SetBranchAddress("jet1pt_JER_down_f", &jet1pt_JER_down_f, &b_jet1pt_JER_down_f);
   fChain->SetBranchAddress("jet1eta", &jet1eta, &b_jet1eta);
   fChain->SetBranchAddress("jet1eta_new", &jet1eta_new, &b_jet1eta_new);
   fChain->SetBranchAddress("jet1eta_JEC_up", &jet1eta_JEC_up, &b_jet1eta_JEC_up);
   fChain->SetBranchAddress("jet1eta_JEC_down", &jet1eta_JEC_down, &b_jet1eta_JEC_down);
   fChain->SetBranchAddress("jet1eta_JER_up", &jet1eta_JER_up, &b_jet1eta_JER_up);
   fChain->SetBranchAddress("jet1eta_JER_down", &jet1eta_JER_down, &b_jet1eta_JER_down);
   fChain->SetBranchAddress("jet1eta_f", &jet1eta_f, &b_jet1eta_f);
   fChain->SetBranchAddress("jet1eta_new_f", &jet1eta_new_f, &b_jet1eta_new_f);
   fChain->SetBranchAddress("jet1eta_JEC_up_f", &jet1eta_JEC_up_f, &b_jet1eta_JEC_up_f);
   fChain->SetBranchAddress("jet1eta_JEC_down_f", &jet1eta_JEC_down_f, &b_jet1eta_JEC_down_f);
   fChain->SetBranchAddress("jet1eta_JER_up_f", &jet1eta_JER_up_f, &b_jet1eta_JER_up_f);
   fChain->SetBranchAddress("jet1eta_JER_down_f", &jet1eta_JER_down_f, &b_jet1eta_JER_down_f);
   fChain->SetBranchAddress("jet1phi", &jet1phi, &b_jet1phi);
   fChain->SetBranchAddress("jet1phi_new", &jet1phi_new, &b_jet1phi_new);
   fChain->SetBranchAddress("jet1phi_JEC_up", &jet1phi_JEC_up, &b_jet1phi_JEC_up);
   fChain->SetBranchAddress("jet1phi_JEC_down", &jet1phi_JEC_down, &b_jet1phi_JEC_down);
   fChain->SetBranchAddress("jet1phi_JER_up", &jet1phi_JER_up, &b_jet1phi_JER_up);
   fChain->SetBranchAddress("jet1phi_JER_down", &jet1phi_JER_down, &b_jet1phi_JER_down);
   fChain->SetBranchAddress("jet1phi_f", &jet1phi_f, &b_jet1phi_f);
   fChain->SetBranchAddress("jet1phi_new_f", &jet1phi_new_f, &b_jet1phi_new_f);
   fChain->SetBranchAddress("jet1phi_JEC_up_f", &jet1phi_JEC_up_f, &b_jet1phi_JEC_up_f);
   fChain->SetBranchAddress("jet1phi_JEC_down_f", &jet1phi_JEC_down_f, &b_jet1phi_JEC_down_f);
   fChain->SetBranchAddress("jet1phi_JER_up_f", &jet1phi_JER_up_f, &b_jet1phi_JER_up_f);
   fChain->SetBranchAddress("jet1phi_JER_down_f", &jet1phi_JER_down_f, &b_jet1phi_JER_down_f);
   fChain->SetBranchAddress("jet1e", &jet1e, &b_jet1e);
   fChain->SetBranchAddress("jet1e_new", &jet1e_new, &b_jet1e_new);
   fChain->SetBranchAddress("jet1e_JEC_up", &jet1e_JEC_up, &b_jet1e_JEC_up);
   fChain->SetBranchAddress("jet1e_JER_up", &jet1e_JER_up, &b_jet1e_JER_up);
   fChain->SetBranchAddress("jet1e_JEC_down", &jet1e_JEC_down, &b_jet1e_JEC_down);
   fChain->SetBranchAddress("jet1e_JER_down", &jet1e_JER_down, &b_jet1e_JER_down);
   fChain->SetBranchAddress("jet1e_f", &jet1e_f, &b_jet1e_f);
   fChain->SetBranchAddress("jet1e_new_f", &jet1e_new_f, &b_jet1e_new_f);
   fChain->SetBranchAddress("jet1e_JEC_up_f", &jet1e_JEC_up_f, &b_jet1e_JEC_up_f);
   fChain->SetBranchAddress("jet1e_JER_up_f", &jet1e_JER_up_f, &b_jet1e_JER_up_f);
   fChain->SetBranchAddress("jet1e_JEC_down_f", &jet1e_JEC_down_f, &b_jet1e_JEC_down_f);
   fChain->SetBranchAddress("jet1e_JER_down_f", &jet1e_JER_down_f, &b_jet1e_JER_down_f);
   fChain->SetBranchAddress("jet1csv", &jet1csv, &b_jet1csv);
   fChain->SetBranchAddress("jet1csv_new", &jet1csv_new, &b_jet1csv_new);
   fChain->SetBranchAddress("jet1csv_JEC_up", &jet1csv_JEC_up, &b_jet1csv_JEC_up);
   fChain->SetBranchAddress("jet1csv_JER_up", &jet1csv_JER_up, &b_jet1csv_JER_up);
   fChain->SetBranchAddress("jet1csv_JEC_down", &jet1csv_JEC_down, &b_jet1csv_JEC_down);
   fChain->SetBranchAddress("jet1csv_JER_down", &jet1csv_JER_down, &b_jet1csv_JER_down);
   fChain->SetBranchAddress("jet1csv_f", &jet1csv_f, &b_jet1csv_f);
   fChain->SetBranchAddress("jet1csv_new_f", &jet1csv_new_f, &b_jet1csv_new_f);
   fChain->SetBranchAddress("jet1csv_JEC_up_f", &jet1csv_JEC_up_f, &b_jet1csv_JEC_up_f);
   fChain->SetBranchAddress("jet1csv_JER_up_f", &jet1csv_JER_up_f, &b_jet1csv_JER_up_f);
   fChain->SetBranchAddress("jet1csv_JEC_down_f", &jet1csv_JEC_down_f, &b_jet1csv_JEC_down_f);
   fChain->SetBranchAddress("jet1csv_JER_down_f", &jet1csv_JER_down_f, &b_jet1csv_JER_down_f);
   fChain->SetBranchAddress("jet1icsv", &jet1icsv, &b_jet1icsv);
   fChain->SetBranchAddress("jet1icsv_new", &jet1icsv_new, &b_jet1icsv_new);
   fChain->SetBranchAddress("jet1icsv_JEC_up", &jet1icsv_JEC_up, &b_jet1icsv_JEC_up);
   fChain->SetBranchAddress("jet1icsv_JER_up", &jet1icsv_JER_up, &b_jet1icsv_JER_up);
   fChain->SetBranchAddress("jet1icsv_JEC_down", &jet1icsv_JEC_down, &b_jet1icsv_JEC_down);
   fChain->SetBranchAddress("jet1icsv_JER_down", &jet1icsv_JER_down, &b_jet1icsv_JER_down);
   fChain->SetBranchAddress("jet1icsv_f", &jet1icsv_f, &b_jet1icsv_f);
   fChain->SetBranchAddress("jet1icsv_new_f", &jet1icsv_new_f, &b_jet1icsv_new_f);
   fChain->SetBranchAddress("jet1icsv_JEC_up_f", &jet1icsv_JEC_up_f, &b_jet1icsv_JEC_up_f);
   fChain->SetBranchAddress("jet1icsv_JER_up_f", &jet1icsv_JER_up_f, &b_jet1icsv_JER_up_f);
   fChain->SetBranchAddress("jet1icsv_JEC_down_f", &jet1icsv_JEC_down_f, &b_jet1icsv_JEC_down_f);
   fChain->SetBranchAddress("jet1icsv_JER_down_f", &jet1icsv_JER_down_f, &b_jet1icsv_JER_down_f);
   fChain->SetBranchAddress("jet2pt", &jet2pt, &b_jet2pt);
   fChain->SetBranchAddress("jet2pt_new", &jet2pt_new, &b_jet2pt_new);
   fChain->SetBranchAddress("jet2pt_JEC_up", &jet2pt_JEC_up, &b_jet2pt_JEC_up);
   fChain->SetBranchAddress("jet2pt_JER_up", &jet2pt_JER_up, &b_jet2pt_JER_up);
   fChain->SetBranchAddress("jet2pt_JEC_down", &jet2pt_JEC_down, &b_jet2pt_JEC_down);
   fChain->SetBranchAddress("jet2pt_JER_down", &jet2pt_JER_down, &b_jet2pt_JER_down);
   fChain->SetBranchAddress("jet2pt_f", &jet2pt_f, &b_jet2pt_f);
   fChain->SetBranchAddress("jet2pt_new_f", &jet2pt_new_f, &b_jet2pt_new_f);
   fChain->SetBranchAddress("jet2pt_JEC_up_f", &jet2pt_JEC_up_f, &b_jet2pt_JEC_up_f);
   fChain->SetBranchAddress("jet2pt_JER_up_f", &jet2pt_JER_up_f, &b_jet2pt_JER_up_f);
   fChain->SetBranchAddress("jet2pt_JEC_down_f", &jet2pt_JEC_down_f, &b_jet2pt_JEC_down_f);
   fChain->SetBranchAddress("jet2pt_JER_down_f", &jet2pt_JER_down_f, &b_jet2pt_JER_down_f);
   fChain->SetBranchAddress("jet2eta", &jet2eta, &b_jet2eta);
   fChain->SetBranchAddress("jet2eta_new", &jet2eta_new, &b_jet2eta_new);
   fChain->SetBranchAddress("jet2eta_JEC_up", &jet2eta_JEC_up, &b_jet2eta_JEC_up);
   fChain->SetBranchAddress("jet2eta_JEC_down", &jet2eta_JEC_down, &b_jet2eta_JEC_down);
   fChain->SetBranchAddress("jet2eta_JER_up", &jet2eta_JER_up, &b_jet2eta_JER_up);
   fChain->SetBranchAddress("jet2eta_JER_down", &jet2eta_JER_down, &b_jet2eta_JER_down);
   fChain->SetBranchAddress("jet2eta_f", &jet2eta_f, &b_jet2eta_f);
   fChain->SetBranchAddress("jet2phi", &jet2phi, &b_jet2phi);
   fChain->SetBranchAddress("jet2phi_new", &jet2phi_new, &b_jet2phi_new);
   fChain->SetBranchAddress("jet2phi_JEC_up", &jet2phi_JEC_up, &b_jet2phi_JEC_up);
   fChain->SetBranchAddress("jet2phi_JEC_down", &jet2phi_JEC_down, &b_jet2phi_JEC_down);
   fChain->SetBranchAddress("jet2phi_JER_up", &jet2phi_JER_up, &b_jet2phi_JER_up);
   fChain->SetBranchAddress("jet2phi_JER_down", &jet2phi_JER_down, &b_jet2phi_JER_down);
   fChain->SetBranchAddress("jet2phi_f", &jet2phi_f, &b_jet2phi_f);
   fChain->SetBranchAddress("jet2phi_new_f", &jet2phi_new_f, &b_jet2phi_new_f);
   fChain->SetBranchAddress("jet2phi_JEC_up_f", &jet2phi_JEC_up_f, &b_jet2phi_JEC_up_f);
   fChain->SetBranchAddress("jet2phi_JEC_down_f", &jet2phi_JEC_down_f, &b_jet2phi_JEC_down_f);
   fChain->SetBranchAddress("jet2phi_JER_up_f", &jet2phi_JER_up_f, &b_jet2phi_JER_up_f);
   fChain->SetBranchAddress("jet2phi_JER_down_f", &jet2phi_JER_down_f, &b_jet2phi_JER_down_f);
   fChain->SetBranchAddress("jet2eta_new_f", &jet2eta_new_f, &b_jet2eta_new_f);
   fChain->SetBranchAddress("jet2eta_JEC_up_f", &jet2eta_JEC_up_f, &b_jet2eta_JEC_up_f);
   fChain->SetBranchAddress("jet2eta_JEC_down_f", &jet2eta_JEC_down_f, &b_jet2eta_JEC_down_f);
   fChain->SetBranchAddress("jet2eta_JER_up_f", &jet2eta_JER_up_f, &b_jet2eta_JER_up_f);
   fChain->SetBranchAddress("jet2eta_JER_down_f", &jet2eta_JER_down_f, &b_jet2eta_JER_down_f);
   fChain->SetBranchAddress("jet2e", &jet2e, &b_jet2e);
   fChain->SetBranchAddress("jet2e_new", &jet2e_new, &b_jet2e_new);
   fChain->SetBranchAddress("jet2e_JEC_up", &jet2e_JEC_up, &b_jet2e_JEC_up);
   fChain->SetBranchAddress("jet2e_JER_up", &jet2e_JER_up, &b_jet2e_JER_up);
   fChain->SetBranchAddress("jet2e_JEC_down", &jet2e_JEC_down, &b_jet2e_JEC_down);
   fChain->SetBranchAddress("jet2e_JER_down", &jet2e_JER_down, &b_jet2e_JER_down);
   fChain->SetBranchAddress("jet2e_f", &jet2e_f, &b_jet2e_f);
   fChain->SetBranchAddress("jet2e_new_f", &jet2e_new_f, &b_jet2e_new_f);
   fChain->SetBranchAddress("jet2e_JEC_up_f", &jet2e_JEC_up_f, &b_jet2e_JEC_up_f);
   fChain->SetBranchAddress("jet2e_JER_up_f", &jet2e_JER_up_f, &b_jet2e_JER_up_f);
   fChain->SetBranchAddress("jet2e_JEC_down_f", &jet2e_JEC_down_f, &b_jet2e_JEC_down_f);
   fChain->SetBranchAddress("jet2e_JER_down_f", &jet2e_JER_down_f, &b_jet2e_JER_down_f);
   fChain->SetBranchAddress("jet2csv", &jet2csv, &b_jet2csv);
   fChain->SetBranchAddress("jet2csv_new", &jet2csv_new, &b_jet2csv_new);
   fChain->SetBranchAddress("jet2csv_JEC_up", &jet2csv_JEC_up, &b_jet2csv_JEC_up);
   fChain->SetBranchAddress("jet2csv_JER_up", &jet2csv_JER_up, &b_jet2csv_JER_up);
   fChain->SetBranchAddress("jet2csv_JEC_down", &jet2csv_JEC_down, &b_jet2csv_JEC_down);
   fChain->SetBranchAddress("jet2csv_JER_down", &jet2csv_JER_down, &b_jet2csv_JER_down);
   fChain->SetBranchAddress("jet2csv_f", &jet2csv_f, &b_jet2csv_f);
   fChain->SetBranchAddress("jet2csv_new_f", &jet2csv_new_f, &b_jet2csv_new_f);
   fChain->SetBranchAddress("jet2csv_JEC_up_f", &jet2csv_JEC_up_f, &b_jet2csv_JEC_up_f);
   fChain->SetBranchAddress("jet2csv_JER_up_f", &jet2csv_JER_up_f, &b_jet2csv_JER_up_f);
   fChain->SetBranchAddress("jet2csv_JEC_down_f", &jet2csv_JEC_down_f, &b_jet2csv_JEC_down_f);
   fChain->SetBranchAddress("jet2csv_JER_down_f", &jet2csv_JER_down_f, &b_jet2csv_JER_down_f);
   fChain->SetBranchAddress("jet2icsv", &jet2icsv, &b_jet2icsv);
   fChain->SetBranchAddress("jet2icsv_new", &jet2icsv_new, &b_jet2icsv_new);
   fChain->SetBranchAddress("jet2icsv_JEC_up", &jet2icsv_JEC_up, &b_jet2icsv_JEC_up);
   fChain->SetBranchAddress("jet2icsv_JER_up", &jet2icsv_JER_up, &b_jet2icsv_JER_up);
   fChain->SetBranchAddress("jet2icsv_JEC_down", &jet2icsv_JEC_down, &b_jet2icsv_JEC_down);
   fChain->SetBranchAddress("jet2icsv_JER_down", &jet2icsv_JER_down, &b_jet2icsv_JER_down);
   fChain->SetBranchAddress("jet2icsv_f", &jet2icsv_f, &b_jet2icsv_f);
   fChain->SetBranchAddress("jet2icsv_new_f", &jet2icsv_new_f, &b_jet2icsv_new_f);
   fChain->SetBranchAddress("jet2icsv_JEC_up_f", &jet2icsv_JEC_up_f, &b_jet2icsv_JEC_up_f);
   fChain->SetBranchAddress("jet2icsv_JER_up_f", &jet2icsv_JER_up_f, &b_jet2icsv_JER_up_f);
   fChain->SetBranchAddress("jet2icsv_JEC_down_f", &jet2icsv_JEC_down_f, &b_jet2icsv_JEC_down_f);
   fChain->SetBranchAddress("jet2icsv_JER_down_f", &jet2icsv_JER_down_f, &b_jet2icsv_JER_down_f);
   fChain->SetBranchAddress("drj1a", &drj1a, &b_drj1a);
   fChain->SetBranchAddress("drj1a_new", &drj1a_new, &b_drj1a_new);
   fChain->SetBranchAddress("drj1a_JEC_up", &drj1a_JEC_up, &b_drj1a_JEC_up);
   fChain->SetBranchAddress("drj1a_JEC_down", &drj1a_JEC_down, &b_drj1a_JEC_down);
   fChain->SetBranchAddress("drj1a_JER_up", &drj1a_JER_up, &b_drj1a_JER_up);
   fChain->SetBranchAddress("drj1a_JER_down", &drj1a_JER_down, &b_drj1a_JER_down);
   fChain->SetBranchAddress("drj1a_f", &drj1a_f, &b_drj1a_f);
   fChain->SetBranchAddress("drj1a_new_f", &drj1a_new_f, &b_drj1a_new_f);
   fChain->SetBranchAddress("drj1a_JEC_up_f", &drj1a_JEC_up_f, &b_drj1a_JEC_up_f);
   fChain->SetBranchAddress("drj1a_JEC_down_f", &drj1a_JEC_down_f, &b_drj1a_JEC_down_f);
   fChain->SetBranchAddress("drj1a_JER_up_f", &drj1a_JER_up_f, &b_drj1a_JER_up_f);
   fChain->SetBranchAddress("drj1a_JER_down_f", &drj1a_JER_down_f, &b_drj1a_JER_down_f);
   fChain->SetBranchAddress("drj2a", &drj2a, &b_drj2a);
   fChain->SetBranchAddress("drj2a_new", &drj2a_new, &b_drj2a_new);
   fChain->SetBranchAddress("drj2a_JEC_up", &drj2a_JEC_up, &b_drj2a_JEC_up);
   fChain->SetBranchAddress("drj2a_JEC_down", &drj2a_JEC_down, &b_drj2a_JEC_down);
   fChain->SetBranchAddress("drj2a_JER_up", &drj2a_JER_up, &b_drj2a_JER_up);
   fChain->SetBranchAddress("drj2a_JER_down", &drj2a_JER_down, &b_drj2a_JER_down);
   fChain->SetBranchAddress("drj2a_f", &drj2a_f, &b_drj2a_f);
   fChain->SetBranchAddress("drj2a_new_f", &drj2a_new_f, &b_drj2a_new_f);
   fChain->SetBranchAddress("drj2a_JEC_up_f", &drj2a_JEC_up_f, &b_drj2a_JEC_up_f);
   fChain->SetBranchAddress("drj2a_JEC_down_f", &drj2a_JEC_down_f, &b_drj2a_JEC_down_f);
   fChain->SetBranchAddress("drj2a_JER_up_f", &drj2a_JER_up_f, &b_drj2a_JER_up_f);
   fChain->SetBranchAddress("drj2a_JER_down_f", &drj2a_JER_down_f, &b_drj2a_JER_down_f);
   fChain->SetBranchAddress("drj1l", &drj1l, &b_drj1l);
   fChain->SetBranchAddress("drj1l_new", &drj1l_new, &b_drj1l_new);
   fChain->SetBranchAddress("drj1l_JEC_up", &drj1l_JEC_up, &b_drj1l_JEC_up);
   fChain->SetBranchAddress("drj1l_JEC_down", &drj1l_JEC_down, &b_drj1l_JEC_down);
   fChain->SetBranchAddress("drj1l_JER_up", &drj1l_JER_up, &b_drj1l_JER_up);
   fChain->SetBranchAddress("drj1l_JER_down", &drj1l_JER_down, &b_drj1l_JER_down);
   fChain->SetBranchAddress("drj1l_f", &drj1l_f, &b_drj1l_f);
   fChain->SetBranchAddress("drj1l_new_f", &drj1l_new_f, &b_drj1l_new_f);
   fChain->SetBranchAddress("drj1l_JEC_up_f", &drj1l_JEC_up_f, &b_drj1l_JEC_up_f);
   fChain->SetBranchAddress("drj1l_JEC_down_f", &drj1l_JEC_down_f, &b_drj1l_JEC_down_f);
   fChain->SetBranchAddress("drj1l_JER_up_f", &drj1l_JER_up_f, &b_drj1l_JER_up_f);
   fChain->SetBranchAddress("drj1l_JER_down_f", &drj1l_JER_down_f, &b_drj1l_JER_down_f);
   fChain->SetBranchAddress("drj2l", &drj2l, &b_drj2l);
   fChain->SetBranchAddress("drj2l_new", &drj2l_new, &b_drj2l_new);
   fChain->SetBranchAddress("drj2l_JEC_up", &drj2l_JEC_up, &b_drj2l_JEC_up);
   fChain->SetBranchAddress("drj2l_JEC_down", &drj2l_JEC_down, &b_drj2l_JEC_down);
   fChain->SetBranchAddress("drj2l_JER_up", &drj2l_JER_up, &b_drj2l_JER_up);
   fChain->SetBranchAddress("drj2l_JER_down", &drj2l_JER_down, &b_drj2l_JER_down);
   fChain->SetBranchAddress("drj2l_f", &drj2l_f, &b_drj2l_f);
   fChain->SetBranchAddress("drj2l_new_f", &drj2l_new_f, &b_drj2l_new_f);
   fChain->SetBranchAddress("drj2l_JEC_up_f", &drj2l_JEC_up_f, &b_drj2l_JEC_up_f);
   fChain->SetBranchAddress("drj2l_JEC_down_f", &drj2l_JEC_down_f, &b_drj2l_JEC_down_f);
   fChain->SetBranchAddress("drj2l_JER_up_f", &drj2l_JER_up_f, &b_drj2l_JER_up_f);
   fChain->SetBranchAddress("drj2l_JER_down_f", &drj2l_JER_down_f, &b_drj2l_JER_down_f);
   fChain->SetBranchAddress("drj1l2", &drj1l2, &b_drj1l2);
   fChain->SetBranchAddress("drj1l2_new", &drj1l2_new, &b_drj1l2_new);
   fChain->SetBranchAddress("drj1l2_JEC_up", &drj1l2_JEC_up, &b_drj1l2_JEC_up);
   fChain->SetBranchAddress("drj1l2_JEC_down", &drj1l2_JEC_down, &b_drj1l2_JEC_down);
   fChain->SetBranchAddress("drj1l2_JER_up", &drj1l2_JER_up, &b_drj1l2_JER_up);
   fChain->SetBranchAddress("drj1l2_JER_down", &drj1l2_JER_down, &b_drj1l2_JER_down);
   fChain->SetBranchAddress("drj1l2_f", &drj1l2_f, &b_drj1l2_f);
   fChain->SetBranchAddress("drj1l2_new_f", &drj1l2_new_f, &b_drj1l2_new_f);
   fChain->SetBranchAddress("drj1l2_JEC_up_f", &drj1l2_JEC_up_f, &b_drj1l2_JEC_up_f);
   fChain->SetBranchAddress("drj1l2_JEC_down_f", &drj1l2_JEC_down_f, &b_drj1l2_JEC_down_f);
   fChain->SetBranchAddress("drj1l2_JER_up_f", &drj1l2_JER_up_f, &b_drj1l2_JER_up_f);
   fChain->SetBranchAddress("drj1l2_JER_down_f", &drj1l2_JER_down_f, &b_drj1l2_JER_down_f);
   fChain->SetBranchAddress("drj2l2", &drj2l2, &b_drj2l2);
   fChain->SetBranchAddress("drj2l2_new", &drj2l2_new, &b_drj2l2_new);
   fChain->SetBranchAddress("drj2l2_JEC_up", &drj2l2_JEC_up, &b_drj2l2_JEC_up);
   fChain->SetBranchAddress("drj2l2_JEC_down", &drj2l2_JEC_down, &b_drj2l2_JEC_down);
   fChain->SetBranchAddress("drj2l2_JER_up", &drj2l2_JER_up, &b_drj2l2_JER_up);
   fChain->SetBranchAddress("drj2l2_JER_down", &drj2l2_JER_down, &b_drj2l2_JER_down);
   fChain->SetBranchAddress("drj2l2_f", &drj2l2_f, &b_drj2l2_f);
   fChain->SetBranchAddress("drj2l2_new_f", &drj2l2_new_f, &b_drj2l2_new_f);
   fChain->SetBranchAddress("drj2l2_JEC_up_f", &drj2l2_JEC_up_f, &b_drj2l2_JEC_up_f);
   fChain->SetBranchAddress("drj2l2_JEC_down_f", &drj2l2_JEC_down_f, &b_drj2l2_JEC_down_f);
   fChain->SetBranchAddress("drj2l2_JER_up_f", &drj2l2_JER_up_f, &b_drj2l2_JER_up_f);
   fChain->SetBranchAddress("drj2l2_JER_down_f", &drj2l2_JER_down_f, &b_drj2l2_JER_down_f);
   fChain->SetBranchAddress("Mjj", &Mjj, &b_Mjj);
   fChain->SetBranchAddress("Mjj_new", &Mjj_new, &b_Mjj_new);
   fChain->SetBranchAddress("Mjj_JEC_up", &Mjj_JEC_up, &b_Mjj_JEC_up);
   fChain->SetBranchAddress("Mjj_JEC_down", &Mjj_JEC_down, &b_Mjj_JEC_down);
   fChain->SetBranchAddress("Mjj_JER_up", &Mjj_JER_up, &b_Mjj_JER_up);
   fChain->SetBranchAddress("Mjj_JER_down", &Mjj_JER_down, &b_Mjj_JER_down);
   fChain->SetBranchAddress("Mjj_f", &Mjj_f, &b_Mjj_f);
   fChain->SetBranchAddress("Mjj_new_f", &Mjj_new_f, &b_Mjj_new_f);
   fChain->SetBranchAddress("Mjj_JEC_up_f", &Mjj_JEC_up_f, &b_Mjj_JEC_up_f);
   fChain->SetBranchAddress("Mjj_JEC_down_f", &Mjj_JEC_down_f, &b_Mjj_JEC_down_f);
   fChain->SetBranchAddress("Mjj_JER_up_f", &Mjj_JER_up_f, &b_Mjj_JER_up_f);
   fChain->SetBranchAddress("Mjj_JER_down_f", &Mjj_JER_down_f, &b_Mjj_JER_down_f);
   fChain->SetBranchAddress("deltaeta", &deltaeta, &b_deltaeta);
   fChain->SetBranchAddress("deltaeta_new", &deltaeta_new, &b_deltaeta_new);
   fChain->SetBranchAddress("deltaeta_JEC_up", &deltaeta_JEC_up, &b_deltaeta_JEC_up);
   fChain->SetBranchAddress("deltaeta_JEC_down", &deltaeta_JEC_down, &b_deltaeta_JEC_down);
   fChain->SetBranchAddress("deltaeta_JER_up", &deltaeta_JER_up, &b_deltaeta_JER_up);
   fChain->SetBranchAddress("deltaeta_JER_down", &deltaeta_JER_down, &b_deltaeta_JER_down);
   fChain->SetBranchAddress("deltaeta_f", &deltaeta_f, &b_deltaeta_f);
   fChain->SetBranchAddress("deltaeta_new_f", &deltaeta_new_f, &b_deltaeta_new_f);
   fChain->SetBranchAddress("deltaeta_JEC_up_f", &deltaeta_JEC_up_f, &b_deltaeta_JEC_up_f);
   fChain->SetBranchAddress("deltaeta_JEC_down_f", &deltaeta_JEC_down_f, &b_deltaeta_JEC_down_f);
   fChain->SetBranchAddress("deltaeta_JER_up_f", &deltaeta_JER_up_f, &b_deltaeta_JER_up_f);
   fChain->SetBranchAddress("deltaeta_JER_down_f", &deltaeta_JER_down_f, &b_deltaeta_JER_down_f);
   fChain->SetBranchAddress("zepp", &zepp, &b_zepp);
   fChain->SetBranchAddress("zepp_new", &zepp_new, &b_zepp_new);
   fChain->SetBranchAddress("zepp_JEC_up", &zepp_JEC_up, &b_zepp_JEC_up);
   fChain->SetBranchAddress("zepp_JEC_down", &zepp_JEC_down, &b_zepp_JEC_down);
   fChain->SetBranchAddress("zepp_JER_up", &zepp_JER_up, &b_zepp_JER_up);
   fChain->SetBranchAddress("zepp_JER_down", &zepp_JER_down, &b_zepp_JER_down);
   fChain->SetBranchAddress("zepp_f", &zepp_f, &b_zepp_f);
   fChain->SetBranchAddress("zepp_new_f", &zepp_new_f, &b_zepp_new_f);
   fChain->SetBranchAddress("zepp_JEC_up_f", &zepp_JEC_up_f, &b_zepp_JEC_up_f);
   fChain->SetBranchAddress("zepp_JEC_down_f", &zepp_JEC_down_f, &b_zepp_JEC_down_f);
   fChain->SetBranchAddress("zepp_JER_up_f", &zepp_JER_up_f, &b_zepp_JER_up_f);
   fChain->SetBranchAddress("zepp_JER_down_f", &zepp_JER_down_f, &b_zepp_JER_down_f);
   fChain->SetBranchAddress("ptlep1", &ptlep1, &b_ptlep1);
   fChain->SetBranchAddress("etalep1", &etalep1, &b_etalep1);
   fChain->SetBranchAddress("philep1", &philep1, &b_philep1);
   fChain->SetBranchAddress("ptlep2", &ptlep2, &b_ptlep2);
   fChain->SetBranchAddress("etalep2", &etalep2, &b_etalep2);
   fChain->SetBranchAddress("philep2", &philep2, &b_philep2);
   fChain->SetBranchAddress("j1metPhi", &j1metPhi, &b_j1metPhi);
   fChain->SetBranchAddress("j1metPhi_new", &j1metPhi_new, &b_j1metPhi_new);
   fChain->SetBranchAddress("j1metPhi_JEC_up", &j1metPhi_JEC_up, &b_j1metPhi_JEC_up);
   fChain->SetBranchAddress("j1metPhi_JEC_down", &j1metPhi_JEC_down, &b_j1metPhi_JEC_down);
   fChain->SetBranchAddress("j1metPhi_JER_up", &j1metPhi_JER_up, &b_j1metPhi_JER_up);
   fChain->SetBranchAddress("j1metPhi_JER_down", &j1metPhi_JER_down, &b_j1metPhi_JER_down);
   fChain->SetBranchAddress("j1metPhi_f", &j1metPhi_f, &b_j1metPhi_f);
   fChain->SetBranchAddress("j1metPhi_new_f", &j1metPhi_new_f, &b_j1metPhi_new_f);
   fChain->SetBranchAddress("j1metPhi_JEC_up_f", &j1metPhi_JEC_up_f, &b_j1metPhi_JEC_up_f);
   fChain->SetBranchAddress("j1metPhi_JEC_down_f", &j1metPhi_JEC_down_f, &b_j1metPhi_JEC_down_f);
   fChain->SetBranchAddress("j1metPhi_JER_up_f", &j1metPhi_JER_up_f, &b_j1metPhi_JER_up_f);
   fChain->SetBranchAddress("j1metPhi_JER_down_f", &j1metPhi_JER_down_f, &b_j1metPhi_JER_down_f);
   fChain->SetBranchAddress("j2metPhi", &j2metPhi, &b_j2metPhi);
   fChain->SetBranchAddress("j2metPhi_new", &j2metPhi_new, &b_j2metPhi_new);
   fChain->SetBranchAddress("j2metPhi_JEC_up", &j2metPhi_JEC_up, &b_j2metPhi_JEC_up);
   fChain->SetBranchAddress("j2metPhi_JEC_down", &j2metPhi_JEC_down, &b_j2metPhi_JEC_down);
   fChain->SetBranchAddress("j2metPhi_JER_up", &j2metPhi_JER_up, &b_j2metPhi_JER_up);
   fChain->SetBranchAddress("j2metPhi_JER_down", &j2metPhi_JER_down, &b_j2metPhi_JER_down);
   fChain->SetBranchAddress("j2metPhi_f", &j2metPhi_f, &b_j2metPhi_f);
   fChain->SetBranchAddress("j2metPhi_new_f", &j2metPhi_new_f, &b_j2metPhi_new_f);
   fChain->SetBranchAddress("j2metPhi_JEC_up_f", &j2metPhi_JEC_up_f, &b_j2metPhi_JEC_up_f);
   fChain->SetBranchAddress("j2metPhi_JEC_down_f", &j2metPhi_JEC_down_f, &b_j2metPhi_JEC_down_f);
   fChain->SetBranchAddress("j2metPhi_JER_up_f", &j2metPhi_JER_up_f, &b_j2metPhi_JER_up_f);
   fChain->SetBranchAddress("j2metPhi_JER_down_f", &j2metPhi_JER_down_f, &b_j2metPhi_JER_down_f);
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
   fChain->SetBranchAddress("HLT_Mu7", &HLT_Mu7, &b_HLT_Mu7);
   fChain->SetBranchAddress("HLT_Mu8", &HLT_Mu8, &b_HLT_Mu8);
   fChain->SetBranchAddress("passFilter_HBHE", &passFilter_HBHE, &b_passFilter_HBHE_);
   fChain->SetBranchAddress("passFilter_HBHEIso", &passFilter_HBHEIso, &b_passFilter_HBHEIso_);
   fChain->SetBranchAddress("passFilter_globalTightHalo", &passFilter_globalTightHalo, &b_passFilter_globalTightHalo_);
   fChain->SetBranchAddress("passFilter_ECALDeadCell", &passFilter_ECALDeadCell, &b_passFilter_ECALDeadCell_);
   fChain->SetBranchAddress("passFilter_GoodVtx", &passFilter_GoodVtx, &b_passFilter_GoodVtx_);
   fChain->SetBranchAddress("passFilter_EEBadSc", &passFilter_EEBadSc, &b_passFilter_EEBadSc_);
   fChain->SetBranchAddress("passFilter_badMuon", &passFilter_badMuon, &b_passFilter_badMuon_);
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
   // for muon rochester correction
   fChain->SetBranchAddress("muon1_trackerLayers", &muon1_trackerLayers, &b_muon1_trackerLayers);
   fChain->SetBranchAddress("matchedgenMu1_pt", &matchedgenMu1_pt, &b_matchedgenMu1_pt);
   fChain->SetBranchAddress("muon2_trackerLayers", &muon2_trackerLayers, &b_muon2_trackerLayers);
   fChain->SetBranchAddress("matchedgenMu2_pt", &matchedgenMu2_pt, &b_matchedgenMu2_pt);
}

EDBRHistoMaker::EDBRHistoMaker(TTree* tree, TFile* fileTMP, TH1F* hR1, std::string out_name_, RoccoR* rc_in) {
	fChain = 0;

	// Which category do we want to analyze?
	fileTMP_ = fileTMP;
	hR1_ = hR1;
	out_name = "./output-slimmed-rootfiles/"+out_name_;
	rc = *rc_in;
	debug_ = true;
	Init(tree);
	createAllHistos();
	printAllHistos();
}

double EDBRHistoMaker::get_rochester_scale(bool isdata, double charge_temp, double pt, double eta, double phi, int nl, double genPt, double r1, double r2){
	int charge = int(charge_temp/fabs(charge_temp));
	// data correction
	if(isdata) return rc.kScaleDT(charge, pt, eta, phi, 0, 0);

	// MC with genPt avalible
	if((!isdata) && genPt>0&&fabs(genPt-pt)/pt<0.1)
        return rc.kScaleFromGenMC(charge, pt, eta, phi, nl, genPt, r1, 0, 0);

	// MC without genPT avalible
	if((!isdata) && !(genPt>0&&fabs(genPt-pt)/pt<0.1))
        return rc.kScaleAndSmearMC(charge, pt, eta, phi, nl, r1, r2, 0, 0);
}
EDBRHistoMaker::~EDBRHistoMaker() {
	if (!fChain)
		return;
	delete fChain->GetCurrentFile();
}

Int_t EDBRHistoMaker::GetEntry(Long64_t entry) {
	// Read contents of entry.
	if (!fChain)
		return 0;
	return fChain->GetEntry(entry);
}

Long64_t EDBRHistoMaker::LoadTree(Long64_t entry) {
	// Set the environment to read one entry
	if (!fChain)
		return -5;
	Long64_t centry = fChain->LoadTree(entry);
	if (centry < 0)
		return centry;
	if (fChain->GetTreeNumber() != fCurrent) {
		fCurrent = fChain->GetTreeNumber();
	}
	return centry;
}

//-------------------------
// Infrastructure functions
//-------------------------

void EDBRHistoMaker::createAllHistos() {

	/// This part substitutes the big arrays that used to be 
	/// in the beginning of this file.
	/// Much simpler to create histos now: just add them to
	/// hs with hs.setHisto(name,nbins,min,max);
	hs.setHisto("ptVlep", 15, 0, 450);
	hs.setHisto("etaVlep", 12, -1.5, 1.5);
	hs.setHisto("phiVlep", 16, -3.14, 3.14);
	hs.setHisto("massVlep", 20, 70, 110);
	hs.setHisto("photonet", 8, 25, 105);
	hs.setHisto("photoneta", 12, -1.5, 1.5);
	hs.setHisto("photonphi", 16, -3.14, 3.14);
	hs.setHisto("photonsieie", 10, 0, 0.01022);
	hs.setHisto("photonnhiso", 10, 0, 3);
	hs.setHisto("photonchiso", 10, 0, 0.441);
	hs.setHisto("photonphoiso", 10, 0, 3);
	hs.setHisto("ptlep1", 10, 20, 300);
	hs.setHisto("etalep1", 12, -2.4, 2.4);
	hs.setHisto("philep1", 16, -3.14, 3.14);
	hs.setHisto("ptlep2", 10, 20, 300);
	hs.setHisto("etalep2", 12, -2.4, 2.4);
	hs.setHisto("philep2", 16, -3.14, 3.14);
	hs.setHisto("jet1pt", 9, 30, 300);
	hs.setHisto("jet1eta", 16, -4.7, 4.7);
	hs.setHisto("jet2pt", 9, 30, 300);
	hs.setHisto("jet2eta", 16, -4.7, 4.7);
	hs.setHisto("Mjj", 5, 150, 400);
	hs.setHisto("ZGmass", 8, 70, 400);
	hs.setHisto("nVtx", 18, 0, 36);
	hs.setHisto("zepp", 9, 0, 4.5);
	hs.setHisto("delta_phi", 10, 0, 3.15);
	hs.setHisto("detajj", 8, 0, 8);
	char buffer[256];
	char buffer2[256];

	nVars = hs.vars.size();

	for (int i = 0; i != nVars; ++i) {
		sprintf(buffer, "%s_mu", hs.vars[i].c_str());
		//    sprintf(buffer,"%s_el",hs.vars[i].c_str());
		sprintf(buffer2, "%s;%s;Number of events;", hs.vars[i].c_str(),
				hs.vars[i].c_str());
		TH1D* histogram = new TH1D(buffer, buffer2, hs.nBins[i], hs.minBin[i],
				hs.maxBin[i]);
		histogram->SetStats(kFALSE);
		histogram->SetDirectory(0);
		//histogram->Sumw2();
		theHistograms[hs.vars[i]] = histogram;
	}

}

void EDBRHistoMaker::printAllHistos() {
	printf("We have %i histograms \n", int(theHistograms.size()));
	typedef std::map<std::string, TH1D*>::iterator it_type;
	for (it_type iterator = theHistograms.begin();
			iterator != theHistograms.end(); iterator++) {
	}
}

void EDBRHistoMaker::saveAllHistos(std::string outFileName) {

	TFile* outFile = TFile::Open(outFileName.c_str(), "RECREATE");

	for (int i = 0; i != nVars; ++i) {
		std::string name = hs.vars[i];
		const TH1D* thisHisto = this->theHistograms[name];
		thisHisto->Write();
	}
	outFile->Close();
}

///----------------------------------------------------------------
/// This is the important function, the loop over all events.
/// Here we fill the histograms according to cuts, weights,
/// and can also filter out events on an individual basis.
///----------------------------------------------------------------
void EDBRHistoMaker::Loop(std::string outFileName) {

	if (fChain == 0)
		return;
	int numbe_out = 0;
	Long64_t nentries = fChain->GetEntriesFast();
	std::cout << "nentries" << nentries << std::endl;
	Long64_t npp = fChain->GetEntries("theWeight>0.");
	Long64_t nmm = fChain->GetEntries("theWeight<0.");
	Double_t nn;
	std::cout << "numberofnp:" << npp << "  numberofnm:" << nmm << std::endl;
	Long64_t nbytes = 0, nb = 0;
	TLorentzVector Zp4, photonp4, jet1p4, jet2p4,lep1p4,lep2p4;
	for (Long64_t jentry = 0; jentry < nentries; jentry++) {
	double r1=gRandom->Rndm(jentry);
	double r2=gRandom->Rndm(jentry*2);
		drll=-1e2;
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0)
			break;
		nb = fChain->GetEntry(jentry);
		nbytes += nb;
		//rochester correction
		muon1_rochester=get_rochester_scale(true, lep1_sign, ptlep1,etalep1, philep1, muon1_trackerLayers, matchedgenMu1_pt,r1, r2);
		muon2_rochester=get_rochester_scale(true, lep2_sign, ptlep2,etalep2, philep2, muon2_trackerLayers, matchedgenMu2_pt,r1, r2);
		ptlep1*=muon1_rochester;
		ptlep2*=muon2_rochester;

		lep1p4.SetPtEtaPhiM(ptlep1, etalep1, philep1, 0.105666);
		lep2p4.SetPtEtaPhiM(ptlep2, etalep2, philep2, 0.105666);
		massVlep=(lep1p4+lep2p4).M();
		yVlep=(lep1p4+lep2p4).Eta();
		phiVlep=(lep1p4+lep2p4).Phi();
		ptVlep=(lep1p4+lep2p4).Pt();
		//rochester correction

		if (jentry % 1000000 == 0)
			std::cout << "Entry num " << jentry << std::endl;

		if (theWeight > 0)
			nn = 1;
		else
			nn = -1;

		actualWeight = lumiWeight * pileupWeight * scalef;
		detajj = fabs(jet1eta - jet2eta);
		if (fabs(jet1phi-jet2phi)>Pi) drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*Pi-fabs(jet1phi-jet2phi))*(2*Pi-fabs(jet1phi-jet2phi)));
                else drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)));

		if (fabs(philep1-philep2)>Pi) drll = sqrt((etalep1-etalep2)*(etalep1-etalep2)+(2*Pi-fabs(philep1-philep2))*(2*Pi-fabs(philep1-philep2)));
                else drll = sqrt((etalep1-etalep2)*(etalep1-etalep2)+(fabs(philep1-philep2))*(fabs(philep1-philep2)));

		Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, massVlep);
		photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
		jet1p4.SetPtEtaPhiE(jet1pt, jet1eta, jet1phi, jet1e);
		jet2p4.SetPtEtaPhiE(jet2pt, jet2eta, jet2phi, jet2e);
		delta_phi=fabs((Zp4+photonp4).Phi()-(jet1p4+jet2p4).Phi());
		ZGmass=(Zp4+photonp4).M();
		if (delta_phi>Pi) delta_phi=2*Pi-delta_phi;

		if (setUnitaryWeights_) {
			if (jentry == 0)
				printf("Unitary weights set!\n");
			actualWeight = 1;
		}
		int iswjets = 0;
                int isnotwets = 0;
                int iszjets = 0;
                int isttjets = 0;

                TString filename = fileTMP_->GetName();
                if (filename.Contains("WJets") && isprompt != 1) {
                        iswjets = 1;
                }
                if (filename.Contains("ZJets") && isprompt != 1) {
                        iszjets = 1;
                }
                if (filename.Contains("TTJets") && isprompt != 1) {
                        isttjets = 1;
                }
                if (!(filename.Contains("WJets")) && !(filename.Contains("ZJets"))
                                && !(filename.Contains("TTJets"))) {
                        isnotwets = 1;
                }
		if (drll>0.3 && lep == 13 &&  ((HLT_Mu1 > 0)|| (HLT_Mu2 > 0)) && ptlep1 > 20. && ptlep2 > 20. && fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep > 70. && massVlep < 110. && photonet > 20.&& fabs(photoneta) < 1.4442/* && jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7 && Mjj > 150*/) {
			numbe_out++;
			treename->Fill();
		}
		else
			continue;

		if (isnotwets > 0 || iswjets > 0 || iszjets > 0 || isttjets > 0) {
			(theHistograms["ptVlep"])->Fill(ptVlep, actualWeight);
			(theHistograms["etaVlep"])->Fill(yVlep, actualWeight);
			(theHistograms["phiVlep"])->Fill(phiVlep, actualWeight);
			(theHistograms["massVlep"])->Fill(massVlep, actualWeight);
			(theHistograms["photonet"])->Fill(photonet, actualWeight);
			(theHistograms["photoneta"])->Fill(photoneta, actualWeight);
			(theHistograms["photonphi"])->Fill(photonphi, actualWeight);
			(theHistograms["photonsieie"])->Fill(photonsieie, actualWeight);
			(theHistograms["photonphoiso"])->Fill(photonphoiso, actualWeight);
			(theHistograms["photonchiso"])->Fill(photonchiso, actualWeight);
			(theHistograms["photonnhiso"])->Fill(photonnhiso, actualWeight);
			(theHistograms["ptlep1"])->Fill(ptlep1, actualWeight);
			(theHistograms["etalep1"])->Fill(etalep1, actualWeight);
			(theHistograms["philep1"])->Fill(philep1, actualWeight);
			(theHistograms["ptlep2"])->Fill(ptlep2, actualWeight);
			(theHistograms["etalep2"])->Fill(etalep2, actualWeight);
			(theHistograms["philep2"])->Fill(philep2, actualWeight);
			(theHistograms["jet1pt"])->Fill(jet1pt, actualWeight);
			(theHistograms["jet1eta"])->Fill(jet1eta, actualWeight);
			(theHistograms["jet2pt"])->Fill(jet2pt, actualWeight);
			(theHistograms["jet2eta"])->Fill(jet2eta, actualWeight);
			if(Mjj<400)(theHistograms["Mjj"])->Fill(Mjj, actualWeight);
			(theHistograms["ZGmass"])->Fill(ZGmass, actualWeight);
			(theHistograms["nVtx"])->Fill(nVtx, actualWeight);
			(theHistograms["zepp"])->Fill(zepp, actualWeight);
			(theHistograms["delta_phi"])->Fill(delta_phi, actualWeight);
			(theHistograms["detajj"])->Fill(detajj, actualWeight);

		}
	}     //end loop over entries
	cout << "after cut: " << numbe_out << "*actualweight" << actualWeight
		<< " result " << numbe_out * actualWeight << endl;
	this->saveAllHistos(outFileName);
}

void EDBRHistoMaker::Loop_SFs_mc(std::string outFileName){

	if (fChain == 0)
		return;
	int numbe_out = 0;
	Long64_t nentries = fChain->GetEntriesFast();
	std::cout << "nentries" << nentries << std::endl;
	Long64_t npp = fChain->GetEntries("theWeight>0.");
	Long64_t nmm = fChain->GetEntries("theWeight<0.");
	Double_t nn;
	std::cout << "numberofnp:" << npp << "  numberofnm:" << nmm << std::endl;
	Long64_t nbytes = 0, nb = 0;

	TLorentzVector Zp4, photonp4, jet1p4, jet2p4, lep1p4, lep2p4;
	for (Long64_t jentry = 0; jentry < nentries; jentry++) {
	double r1=gRandom->Rndm(jentry);
	double r2=gRandom->Rndm(jentry*2);
		drll=-1e2;
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0)
			break;

		nb = fChain->GetEntry(jentry);
		nbytes += nb;

		//rochester correction
		/*muon1_rochester=get_rochester_scale(false, lep1_sign, ptlep1,etalep1, philep1, muon1_trackerLayers, matchedgenMu1_pt,r1, r2);
		muon2_rochester=get_rochester_scale(false, lep2_sign, ptlep2,etalep2, philep2, muon2_trackerLayers, matchedgenMu2_pt,r1, r2);
		ptlep1*=muon1_rochester;
		ptlep2*=muon2_rochester;*/
		//cout<<"OK2"<<endl;

		lep1p4.SetPtEtaPhiM(ptlep1, etalep1, philep1, 0.105666);
		lep2p4.SetPtEtaPhiM(ptlep2, etalep2, philep2, 0.105666);
		massVlep=(lep1p4+lep2p4).M();
		yVlep=(lep1p4+lep2p4).Eta();
		phiVlep=(lep1p4+lep2p4).Phi();
		ptVlep=(lep1p4+lep2p4).Pt();
		//rochester correction
		if (jentry % 100000 == 0)
			std::cout << "Entry num " << jentry << std::endl;

		if (theWeight > 0)
			nn = 1;
		else
			nn = -1;
//	        if(outFileName.find("ZJets") != std::string::npos){
//                      scalef=0.07487*fabs(theWeight)/theWeight;
//                }
		actualWeight = lumiWeight * pileupWeight * scalef;
		detajj = fabs(jet1eta - jet2eta);
		if (fabs(jet1phi-jet2phi)>Pi) drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*Pi-fabs(jet1phi-jet2phi))*(2*Pi-fabs(jet1phi-jet2phi)));
                else drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)));

		if (fabs(philep1-philep2)>Pi) drll = sqrt((etalep1-etalep2)*(etalep1-etalep2)+(2*Pi-fabs(philep1-philep2))*(2*Pi-fabs(philep1-philep2)));
                else drll = sqrt((etalep1-etalep2)*(etalep1-etalep2)+(fabs(philep1-philep2))*(fabs(philep1-philep2)));

		jet1p4.SetPtEtaPhiE(jet1pt, jet1eta, jet1phi, jet1e);
		jet2p4.SetPtEtaPhiE(jet2pt, jet2eta, jet2phi, jet2e);
		Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, massVlep);
		photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
		delta_phi=fabs((Zp4+photonp4).Phi()-(jet1p4+jet2p4).Phi());
		ZGmass=(Zp4+photonp4).M();
		if (delta_phi>Pi) delta_phi=2*Pi-delta_phi;

		if (setUnitaryWeights_) {
			if (jentry == 0)
				printf("Unitary weights set!\n");
			actualWeight = 1;
		}
		int iswjets = 0;
                int isnotwets = 0;
                int iszjets = 0;
                int isttjets = 0;

                TString filename = fileTMP_->GetName();
                if (filename.Contains("WJets") && isprompt != 1) {
                        iswjets = 1;
                }
                if (filename.Contains("ZJets") && isprompt != 1) {
                        iszjets = 1;
                }
                if (filename.Contains("TTJets") && isprompt != 1) {
                        isttjets = 1;
                }
                if (!(filename.Contains("WJets")) && !(filename.Contains("ZJets"))
                                && !(filename.Contains("TTJets"))) {
                        isnotwets = 1;
                }
                //cout<<"drll = "<<drll<<endl;
		if (drll>0.3 && lep == 13 && (HLT_Mu1>0 || HLT_Mu2 > 0) && ptlep1 > 20. && ptlep2 > 20. && fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep > 70. && massVlep < 110. && photonet > 20. && fabs(photoneta) < 1.4442 /* && jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7 && Mjj > 150*/) {
			numbe_out++;
			treename->Fill();
		}
		else
			continue;

		actualWeight = actualWeight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon1_track_scale*muon2_track_scale*muon_hlt_scale;
                if(filename.Contains("JEC")){  cout<<"actualWeight"<<actualWeight<<endl;cout<<"lumiWeight:"<<lumiWeight<<"; pileupWeight:"<<pileupWeight<<"; scalef = "<<scalef<<"; muon1_id_scale = "<<muon1_id_scale<<"; muon2_id_scale = "<<muon2_id_scale<<"; muon1_track_scale = "<<muon1_track_scale<<"; muon_hlt_scale = "<<muon_hlt_scale<<endl;}
                if(filename.Contains("plj")) {
                     actualWeight = scalef;
                     if(jentry%1000==0) cout<<"photonet = "<<photonet<<"; actualWeight = "<<actualWeight<<endl;
                }

		if (isnotwets > 0 || iswjets > 0 || iszjets > 0 || isttjets > 0) {
			(theHistograms["ptVlep"])->Fill(ptVlep, actualWeight);
			(theHistograms["etaVlep"])->Fill(yVlep, actualWeight);
			(theHistograms["phiVlep"])->Fill(phiVlep, actualWeight);
			(theHistograms["massVlep"])->Fill(massVlep, actualWeight);
			(theHistograms["photonet"])->Fill(photonet, actualWeight);
			(theHistograms["photoneta"])->Fill(photoneta, actualWeight);
			(theHistograms["photonphi"])->Fill(photonphi, actualWeight);
			(theHistograms["photonsieie"])->Fill(photonsieie, actualWeight);
			(theHistograms["photonphoiso"])->Fill(photonphoiso, actualWeight);
			(theHistograms["photonchiso"])->Fill(photonchiso, actualWeight);
			(theHistograms["photonnhiso"])->Fill(photonnhiso, actualWeight);
			(theHistograms["ptlep1"])->Fill(ptlep1, actualWeight);
			(theHistograms["etalep1"])->Fill(etalep1, actualWeight);
			(theHistograms["philep1"])->Fill(philep1, actualWeight);
			(theHistograms["ptlep2"])->Fill(ptlep2, actualWeight);
			(theHistograms["etalep2"])->Fill(etalep2, actualWeight);
			(theHistograms["philep2"])->Fill(philep2, actualWeight);
			(theHistograms["jet1pt"])->Fill(jet1pt, actualWeight);
			(theHistograms["jet1eta"])->Fill(jet1eta, actualWeight);
			(theHistograms["jet2pt"])->Fill(jet2pt, actualWeight);
			(theHistograms["jet2eta"])->Fill(jet2eta, actualWeight);
			if(Mjj<400)(theHistograms["Mjj"])->Fill(Mjj, actualWeight);
			(theHistograms["ZGmass"])->Fill(ZGmass, actualWeight);
			(theHistograms["nVtx"])->Fill(nVtx, actualWeight);
			(theHistograms["zepp"])->Fill(zepp, actualWeight);
			(theHistograms["delta_phi"])->Fill(delta_phi, actualWeight);
			(theHistograms["detajj"])->Fill(detajj, actualWeight);

		}
	}
	cout << "after cut: " << numbe_out << "*actualweight" << actualWeight
		<< " result " << numbe_out * actualWeight << endl;
	this->saveAllHistos(outFileName);
}
