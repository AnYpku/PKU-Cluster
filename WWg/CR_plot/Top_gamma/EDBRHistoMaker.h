#include "TGraphAsymmErrors.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTree.h"
#include "TChain.h"
#include "math.h"
#include "TLorentzVector.h"
#include "roccor/RoccoR.cc"
#include "TRandom.h"
//#include "get_rochester_scale.C"
#define Pi 3.1415926
using namespace std;
/// The large arrays that were here are now GONE.
/// Instead, we have this helper that holds the
/// information of all our histograms.

class HistoFactory {
	public:
		std::vector<std::string> vars;
		std::vector<int> nBins;
		std::vector<float> minBin;
		std::vector<float> maxBin;
		void setHisto(std::string s, int n, float min, float max) {
			vars.push_back(s);
			nBins.push_back(n);
			minBin.push_back(min);
			maxBin.push_back(max);
		}
};

class EDBRHistoMaker {
	public:
		EDBRHistoMaker(TTree *tree = 0, TFile *fileTMP = 0, TH1F* hR1 = 0, std::string out_name_="", RoccoR* rc_in=0,TString isChannel="");
		virtual ~EDBRHistoMaker();
		/// This is the tree structure. This comes directly from MakeClass
		TTree* fChain;   //!pointer to the analyzed TTree or TChain
		TFile* fileTMP_;
		TH1F* hR1_;
		Int_t fCurrent; //!current Tree number in a TChain
		bool setUnitaryWeights_;
		// Declaration of leaf types
                float mT;
                float mT1;
                float mT2;
		float muon1_rochester;
                Bool_t          photon_flag;
                Bool_t          lepton_flag;
		UInt_t          lumi;
		Int_t           channel;
		Int_t           lep1_pid;
		Int_t           lep2_pid;
		Float_t         lep1pt;
		Float_t         lep2pt;
		Float_t         lep1eta;
		Float_t         lep2eta;
		Float_t         lep1phi;
		Float_t         lep2phi;
		Int_t           lep1_isprompt;
		Int_t           lep2_isprompt;
		Int_t           lep1_is_tight;
		Int_t           lep2_is_tight;
		Int_t           lep1_charge;
		Int_t           lep2_charge;
		Int_t           Muon_nTrackerLayers;
		Int_t           photon_selection;
		Int_t           n_loose_mu;
		Int_t           n_loose_ele;
		Int_t           n_photon;
		Float_t         photonet;
		Float_t         photoneta;
		Float_t         photonphi;
		Int_t           photon_isprompt;
		Int_t           photon_gen_matching;
		Float_t         mll;
		Float_t         mllg;
                Float_t         ml1g;
                Float_t         ml2g;
		Float_t         ptll;
		Float_t         mt;
		Float_t         met;
		Float_t         metup;
		Float_t         puppimet;
		Float_t         PuppiMET_T1_pt;
		Float_t         PuppiMET_T1Smear_pt;
		Float_t         PuppiMET_T1_phi;
		Float_t         PuppiMET_T1Smear_phi;
		Float_t         puppimetphi;
		Float_t         rawmet;
		Float_t         rawmetphi;
		Float_t         metphi;
		Float_t         gen_weight;
		Int_t           npu;
		Float_t         ntruepu;
		Int_t           n_pos;
		Int_t           n_minus;
		Int_t           n_num;
		Int_t           MET_pass;
		Int_t           npvs;
		Int_t           n_bjets_nom;
		Int_t           njets20_nom;
		Int_t           njets25_nom;
		Int_t           njets30_nom;
		Int_t           njets35_nom;
		Int_t           njets40_nom;
		Int_t           njets50_nom;
		Int_t           n_bjets;
		Int_t           njets;
		Int_t           njets_fake;
		Int_t           njets50;
		Int_t           njets40;
		Int_t           njets30;
		Int_t           njets20;
		Int_t           njets15;
		Float_t         puWeight;
		Float_t         puWeightUp;
		Float_t         puWeightDown;
		Bool_t          HLT_IsoMu24;
		Bool_t          HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8;
		Bool_t          HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
		Bool_t          HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL;
		Bool_t          HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
		Bool_t          HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
		Bool_t          HLT_Ele32_WPTight_Gsf;
		Bool_t          HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL;
                Float_t         LHEScaleWeight[9];
                Float_t         LHEPdfWeight[103];
		Float_t         PrefireWeight;
		Float_t         PrefireWeight_Up;
		Float_t         PrefireWeight_Down;
		Float_t         scalef;
                Float_t         btag_weight;
                Float_t         btag_weight_up;
                Float_t         btag_weight_down;
                Float_t        ele_id_scale;
                Float_t        ele_id_scale_Up;
                Float_t        ele_id_scale_Down;
                Float_t        ele_reco_scale;
                Float_t        ele_reco_scale_Up;
                Float_t        ele_reco_scale_Down;
                Float_t        muon_id_scale;
                Float_t        muon_id_scale_Up;
                Float_t        muon_id_scale_Down;
                Float_t        muon_iso_scale;
                Float_t        muon_iso_scale_Up;
                Float_t        muon_iso_scale_Down;
                Float_t        photon_id_scale;
                Float_t        photon_id_scale_Up;
                Float_t        photon_id_scale_Down;
                Float_t        photon_veto_scale;
                Float_t        photon_veto_scale_Up;
                Float_t        photon_veto_scale_Down;
		Float_t         actualWeight;
                Float_t         drll;
                Float_t         drl1a;
                Float_t         drl2a;
                Float_t         yVlep;
                Float_t         phiVlep;
                Float_t         ptVlep;
                Bool_t          HLT_Mu1;
                Bool_t          HLT_Mu2;
                Bool_t          HLT_emu1;
                Bool_t          HLT_emu2;
                Bool_t          HLT_emu3;
                Bool_t          HLT_emu4;
                Bool_t          HLT_Ele1;
                Bool_t          HLT_Ele2;

		// List of branches
		TBranch        *b_lumi;   //!
		TBranch        *b_channel;   //!
		TBranch        *b_lep1_pid;   //!
		TBranch        *b_lep2_pid;   //!
		TBranch        *b_lep1pt;   //!
		TBranch        *b_lep2pt;   //!
		TBranch        *b_lep1eta;   //!
		TBranch        *b_lep2eta;   //!
		TBranch        *b_lep1phi;   //!
		TBranch        *b_lep2phi;   //!
		TBranch        *b_lep1_isprompt;   //!
		TBranch        *b_lep2_isprompt;   //!
		TBranch        *b_lep1_is_tight;   //!
		TBranch        *b_lep2_is_tight;   //!
		TBranch        *b_lep1_charge;   //!
		TBranch        *b_lep2_charge;   //!
		TBranch        *b_Muon_nTrackerLayers;   //!
		TBranch        *b_photon_selection;   //!
		TBranch        *b_n_loose_mu;   //!
		TBranch        *b_n_loose_ele;   //!
		TBranch        *b_n_photon;   //!
		TBranch        *b_photonet;   //!
		TBranch        *b_photoneta;   //!
		TBranch        *b_photonphi;   //!
		TBranch        *b_photon_isprompt;   //!
		TBranch        *b_photon_gen_matching;   //!
		TBranch        *b_drll;   //!
		TBranch        *b_drl1a;   //!
		TBranch        *b_drl2a;   //!
		TBranch        *b_mllg;   //!
                TBranch        *b_ml1g;   //!
                TBranch        *b_ml2g;   //!
		TBranch        *b_mll;   //!
		TBranch        *b_ptll;   //!
		TBranch        *b_mt;   //!
		TBranch        *b_met;   //!
		TBranch        *b_metup;   //!
		TBranch        *b_puppimet;   //!
		TBranch        *b_puppimetphi;   //!
		TBranch        *b_PuppiMET_T1_pt;   //!
		TBranch        *b_PuppiMET_T1Smear_pt;   //!
		TBranch        *b_PuppiMET_T1_phi;   //!
		TBranch        *b_PuppiMET_T1Smear_phi;   //!
		TBranch        *b_rawmet;   //!
		TBranch        *b_rawmetphi;   //!
		TBranch        *b_metphi;   //!
		TBranch        *b_gen_weight;   //!
		TBranch        *b_npu;   //!
		TBranch        *b_ntruepu;   //!
		TBranch        *b_n_pos;   //!
		TBranch        *b_n_minus;   //!
		TBranch        *b_n_num;   //!
		TBranch        *b_MET_pass;   //!
		TBranch        *b_npvs;   //!
		TBranch        *b_n_bjets;   //!
		TBranch        *b_n_bjets_nom;   //!
		TBranch        *b_njets20_nom;   //!
		TBranch        *b_njets25_nom;   //!
		TBranch        *b_njets30_nom;   //!
		TBranch        *b_njets35_nom;   //!
		TBranch        *b_njets40_nom;   //!
		TBranch        *b_njets50_nom;   //!
		TBranch        *b_njets;   //!
		TBranch        *b_njets_fake;   //!
		TBranch        *b_njets50;   //!
		TBranch        *b_njets40;   //!
		TBranch        *b_njets30;   //!
		TBranch        *b_njets20;   //!
		TBranch        *b_njets15;   //!
		TBranch        *b_puWeight;   //!
		TBranch        *b_puWeightUp;   //!
		TBranch        *b_puWeightDown;   //!
		TBranch        *b_HLT_IsoMu24;
		TBranch        *b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8;
		TBranch        *b_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
		TBranch        *b_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL;
		TBranch        *b_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
		TBranch        *b_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
		TBranch        *b_HLT_Ele32_WPTight_Gsf;
		TBranch        *b_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL;
                TBranch        *b_LHEScaleWeight;
                TBranch        *b_LHEPdfWeight;
		TBranch        *b_scalef;   //!
		TBranch        *b_PrefireWeight;   //!
		TBranch        *b_PrefireWeight_Up;   //!
		TBranch        *b_PrefireWeight_Down;   //!
		TBranch        *b_btag_weight;   //!
		TBranch        *b_btag_weight_up;   //!
		TBranch        *b_btag_weight_down;   //!
                TBranch        *b_ele_id_scale;   //!
                TBranch        *b_ele_id_scale_Up;   //!
                TBranch        *b_ele_id_scale_Down;   //!
                TBranch        *b_ele_reco_scale;   //!
                TBranch        *b_ele_reco_scale_Up;   //!
                TBranch        *b_ele_reco_scale_Down;   //!
                TBranch        *b_muon_id_scale;   //!
                TBranch        *b_muon_id_scale_Up;   //!
                TBranch        *b_muon_id_scale_Down;   //!
                TBranch        *b_muon_iso_scale;   //!
                TBranch        *b_muon_iso_scale_Up;   //!
                TBranch        *b_muon_iso_scale_Down;   //!
                TBranch        *b_photon_id_scale;   //!
                TBranch        *b_photon_id_scale_Up;   //!
                TBranch        *b_photon_id_scale_Down;   //!
                TBranch        *b_photon_veto_scale;   //!
                TBranch        *b_photon_veto_scale_Up;   //!
                TBranch        *b_photon_veto_scale_Down;   //!

		// Basic functions directly from MakeClass
		Int_t GetEntry(Long64_t entry);
		Long64_t LoadTree(Long64_t entry);
		void Init(TTree *tree);
		void Loop(std::string outFileName,float luminosity,int isBarrel,TString isChannel);
		void Loop_SFs_mc(std::string outFileNamei,float luminosity,int isBarrel,TString isChannel);
		// Our added functions
		void createAllHistos(TString isChannel);
		void printAllHistos();
		void saveAllHistos(std::string outFileName);
		void setUnitaryWeights(bool setuniw = false) {
			setUnitaryWeights_ = setuniw;
		}

		int check(float pt, std::vector<float> * ptZ) {
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
		float get_rochester_scale(bool isdata, float charge_temp, float pt, float eta, float phi, int nl, float r1);


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
	treename = new TTree("outtree","outtree");
	cout<<"begin make outfile tree"<<endl;
	treename->Branch("channel", &channel,   "channel/I");
	treename->Branch("ptVlep", &ptVlep,   "ptVlep/F");
	treename->Branch("phiVlep", &phiVlep,   "phiVlep/F");
	treename->Branch("yVlep", &yVlep,   "yVlep/F");
	treename->Branch("lep1_pid", &lep1_pid, "lep1_pid/I");
	treename->Branch("lep2_pid", &lep2_pid, "lep1_pid/I");
	treename->Branch("lep1pt", &lep1pt,     "lep1pt/F");
	treename->Branch("lep2pt", &lep2pt,     "lep2pt/F");
	treename->Branch("lep1eta", &lep1eta,   "lep1eta/F");
	treename->Branch("lep2eta", &lep2eta,   "lep2eta/F");
	treename->Branch("lep1phi", &lep1phi,   "lep1phi/F");
	treename->Branch("lep2phi", &lep2phi,   "lep1phi/F");
	treename->Branch("lep1_isprompt", &lep1_isprompt, "lep1_isprompt/I");
	treename->Branch("lep2_isprompt", &lep2_isprompt, "lep2_isprompt/I");
	treename->Branch("lep1_is_tight", &lep1_is_tight, "lep1_is_tight/I");
	treename->Branch("lep2_is_tight", &lep2_is_tight, "lep2_is_tight/I");
	treename->Branch("lep1_charge", &lep1_charge, "lep1_charge/I");
	treename->Branch("lep2_charge", &lep2_charge, "lep2_charge/I");
	treename->Branch("Muon_nTrackerLayers", &Muon_nTrackerLayers, "Muon_nTrackerLayers/I");
	treename->Branch("photon_selection", &photon_selection, "photon_selection/I");
	treename->Branch("n_loose_mu", &n_loose_mu,   "n_loose_mu/I");
	treename->Branch("n_loose_ele", &n_loose_ele, "n_loose_ele/I");
	treename->Branch("n_photon", &n_photon, "n_photon/I");
	treename->Branch("photonet", &photonet,   "photonet/F");
	treename->Branch("photoneta", &photoneta, "photoneta/F");
	treename->Branch("photonphi", &photonphi, "photonphi/F");
	treename->Branch("photon_isprompt", &photon_isprompt, "photon_isprompt/I");
	treename->Branch("photon_gen_matching", &photon_gen_matching, "photon_gen_matching/I");
	treename->Branch("drll", &drll, "drll/F");
	treename->Branch("drl1a", &drl1a, "drl1a/F");
	treename->Branch("drl2a", &drl2a, "drl2a/F");
	treename->Branch("mll", &mll, "mll/F");
	treename->Branch("mllg", &mllg, "mllg/F");
        treename->Branch("ml1g", &ml1g, "ml1g/F");
        treename->Branch("ml2g", &ml2g, "ml2g/F");
	treename->Branch("ptll", &ptll, "ptll/F");
	treename->Branch("mt", &mt, "mt/F");
	treename->Branch("mT", &mT, "mT/F");
	treename->Branch("mT1", &mT1, "mT1/F");
	treename->Branch("mT2", &mT2, "mT2/F");
	treename->Branch("met", &met, "met/F");
	treename->Branch("metup", &metup, "metup/F");
	treename->Branch("puppimet", &puppimet, "puppimet/F");
	treename->Branch("puppimetphi", &puppimetphi, "puppimetphi/F");
	treename->Branch("PuppiMET_T1_pt", &PuppiMET_T1_pt, "PuppiMET_T1_pt/F");
	treename->Branch("PuppiMET_T1Smear_pt", &PuppiMET_T1Smear_pt, "PuppiMET_T1Smear_pt/F");
	treename->Branch("PuppiMET_T1_phi", &PuppiMET_T1_phi, "PuppiMET_T1_phi/F");
	treename->Branch("PuppiMET_T1Smear_phi", &PuppiMET_T1Smear_phi, "PuppiMET_T1Smear_phi/F");
	treename->Branch("rawmet", &rawmet, "rawmet/F");
	treename->Branch("rawmetphi", &rawmetphi, "rawmetphi/F");
	treename->Branch("metphi", &metphi, "metphi/F");
	treename->Branch("gen_weight", &gen_weight, "gen_weight/F");
	treename->Branch("npu", &npu, "npu/I");
	treename->Branch("ntruepu", &ntruepu, "ntruepu/F");
	treename->Branch("n_pos", &n_pos, "n_pos/I");
	treename->Branch("n_minus", &n_minus, "n_minus/I");
	treename->Branch("n_num", &n_num, "n_num/I");
	treename->Branch("MET_pass", &MET_pass, "MET_pass/I");
	treename->Branch("npvs", &npvs, "npvs/I");
        treename->Branch("n_bjets_nom", &n_bjets_nom, "n_bjets_nom/I");
        treename->Branch("njets50_nom", &njets50_nom, "njets50_nom/I");
        treename->Branch("njets40_nom", &njets40_nom, "njets40_nom/I");
        treename->Branch("njets35_nom", &njets35_nom, "njets35_nom/I");
        treename->Branch("njets30_nom", &njets30_nom, "njets30_nom/I");
        treename->Branch("njets25_nom", &njets25_nom, "njets25_nom/I");
        treename->Branch("njets20_nom", &njets20_nom, "njets20_nom/I");
	treename->Branch("n_bjets", &n_bjets, "n_bjets/I");
	treename->Branch("njets", &njets, "njets/I");
	treename->Branch("njets_fake", &njets_fake, "njets_fake/I");
	treename->Branch("njets50", &njets50, "njets50/I");
	treename->Branch("njets40", &njets40, "njets40/I");
	treename->Branch("njets30", &njets30, "njets30/I");
	treename->Branch("njets20", &njets20, "njets30/I");
	treename->Branch("njets15", &njets15, "njets15/I");
	treename->Branch("puWeight", &puWeight, "puWeight/F");
	treename->Branch("puWeightUp", &puWeightUp, "puWeightUp/F");
	treename->Branch("puWeightDown", &puWeightDown, "puWeightDown/F");
	treename->Branch("HLT_Mu1", &HLT_IsoMu24, "HLT_Mu1/B");
	treename->Branch("HLT_Mu2", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8, "HLT_Mu2/B");
	treename->Branch("HLT_emu1", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ, "HLT_emu1/B");
	treename->Branch("HLT_emu2", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL, "HLT_emu2/B");
	treename->Branch("HLT_emu3", &HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL, "HLT_emu3/B");
	treename->Branch("HLT_emu4", &HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ, "HLT_emu4/B");
	treename->Branch("HLT_Ele1", &HLT_Ele32_WPTight_Gsf, "HLT_Ele1/B");
	treename->Branch("HLT_Ele2", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL, "HLT_Ele2/B");
	treename->Branch("scalef", &scalef, "scalef/F");
	treename->Branch("PrefireWeight", &PrefireWeight, "PrefireWeight/F");
	treename->Branch("PrefireWeight_Up", &PrefireWeight_Up, "PrefireWeight_Up/F");
	treename->Branch("PrefireWeight_Down", &PrefireWeight_Down, "PrefireWeight_Down/F");
        treename->Branch("LHEScaleWeight", LHEScaleWeight, "LHEScaleWeight[9]/F");
        treename->Branch("LHEPdfWeight", LHEPdfWeight, "LHEPdfWeight[103]/F");
	treename->Branch("btag_weight", &btag_weight, "btag_weight/F");
	treename->Branch("btag_weight_up", &btag_weight_up, "btag_weight_up/F");
	treename->Branch("btag_weight_down", &btag_weight_down, "btag_weight_down/F");
	treename->Branch("actualWeight", &actualWeight, "actualWeight/F");
        treename->Branch("ele_id_scale",&ele_id_scale,"ele_id_scale/F");
        treename->Branch("ele_id_scale_Up",&ele_id_scale_Up,"ele_id_scale_Up/F");
        treename->Branch("ele_id_scale_Down",&ele_id_scale_Down,"ele_id_scale_Down/F");
        treename->Branch("ele_reco_scale",&ele_reco_scale,"ele_reco_scale/F");
        treename->Branch("ele_reco_scale_Up",&ele_reco_scale_Up,"ele_reco_scale_Up/F");
        treename->Branch("ele_reco_scale_Down",&ele_reco_scale_Down,"ele_reco_scale_Down/F");
        treename->Branch("muon_id_scale",&muon_id_scale,"muon_id_scale/F");
        treename->Branch("muon_id_scale_Up",&muon_id_scale_Up,"muon_id_scale_Up/F");
        treename->Branch("muon_id_scale_Down",&muon_id_scale_Down,"muon_id_scale_Down/F");
        treename->Branch("muon_iso_scale",&muon_iso_scale,"muon_iso_scale/F");
        treename->Branch("muon_iso_scale_Up",&muon_iso_scale_Up,"muon_iso_scale_Up/F");
        treename->Branch("muon_iso_scale_Down",&muon_iso_scale_Down,"muon_iso_scale_Down/F");
        treename->Branch("photon_id_scale",&photon_id_scale,"photon_id_scale/F");
        treename->Branch("photon_id_scale_Up",&photon_id_scale_Up,"photon_id_scale_Up/F");
        treename->Branch("photon_id_scale_Down",&photon_id_scale_Down,"photon_id_scale_Down/F");
        treename->Branch("photon_veto_scale",&photon_veto_scale,"photon_veto_scale/F");
        treename->Branch("photon_veto_scale_Up",&photon_veto_scale_Up,"photon_veto_scale_Up/F");
        treename->Branch("photon_veto_scale_Down",&photon_veto_scale_Down,"photon_veto_scale_Down/F");
	cout<<"make outfile tree end"<<endl;

	fChain->SetBranchAddress("channel", &channel, &b_channel);
	fChain->SetBranchAddress("lep1_pid", &lep1_pid, &b_lep1_pid);
	fChain->SetBranchAddress("lep2_pid", &lep2_pid, &b_lep2_pid);
	fChain->SetBranchAddress("lep1pt", &lep1pt, &b_lep1pt);
	fChain->SetBranchAddress("lep2pt", &lep2pt, &b_lep2pt);
	fChain->SetBranchAddress("lep1eta", &lep1eta, &b_lep1eta);
	fChain->SetBranchAddress("lep2eta", &lep2eta, &b_lep2eta);
	fChain->SetBranchAddress("lep1phi", &lep1phi, &b_lep1phi);
	fChain->SetBranchAddress("lep2phi", &lep2phi, &b_lep2phi);
	fChain->SetBranchAddress("lep1_isprompt", &lep1_isprompt, &b_lep1_isprompt);
	fChain->SetBranchAddress("lep2_isprompt", &lep2_isprompt, &b_lep2_isprompt);
	fChain->SetBranchAddress("lep1_is_tight", &lep1_is_tight, &b_lep1_is_tight);
	fChain->SetBranchAddress("lep2_is_tight", &lep2_is_tight, &b_lep2_is_tight);
	fChain->SetBranchAddress("lep1_charge", &lep1_charge, &b_lep1_charge);
	fChain->SetBranchAddress("lep2_charge", &lep2_charge, &b_lep2_charge);
	fChain->SetBranchAddress("Muon_nTrackerLayers", &Muon_nTrackerLayers, &b_Muon_nTrackerLayers);
	fChain->SetBranchAddress("photon_selection", &photon_selection, &b_photon_selection);
	fChain->SetBranchAddress("n_loose_mu", &n_loose_mu, &b_n_loose_mu);
	fChain->SetBranchAddress("n_loose_ele", &n_loose_ele, &b_n_loose_ele);
	fChain->SetBranchAddress("n_photon", &n_photon, &b_n_photon);
	fChain->SetBranchAddress("photonet", &photonet, &b_photonet);
	fChain->SetBranchAddress("photoneta", &photoneta, &b_photoneta);
	fChain->SetBranchAddress("photonphi", &photonphi, &b_photonphi);
	fChain->SetBranchAddress("photon_isprompt", &photon_isprompt, &b_photon_isprompt);
	fChain->SetBranchAddress("photon_gen_matching", &photon_gen_matching, &b_photon_gen_matching);
	fChain->SetBranchAddress("drll", &drll, &b_drll);
	fChain->SetBranchAddress("drl1a", &drl1a, &b_drl1a);
	fChain->SetBranchAddress("drl2a", &drl2a, &b_drl2a);
	fChain->SetBranchAddress("mll", &mll, &b_mll);
	fChain->SetBranchAddress("mllg", &mllg, &b_mllg);
	fChain->SetBranchAddress("ptll", &ptll, &b_ptll);
	fChain->SetBranchAddress("mt", &mt, &b_mt);
	fChain->SetBranchAddress("met", &met, &b_met);
	fChain->SetBranchAddress("metup", &metup, &b_metup);
	fChain->SetBranchAddress("puppimet", &puppimet, &b_puppimet);
	fChain->SetBranchAddress("puppimetphi", &puppimetphi, &b_puppimetphi);
	fChain->SetBranchAddress("PuppiMET_T1_pt", &PuppiMET_T1_pt, &b_PuppiMET_T1_pt);
	fChain->SetBranchAddress("PuppiMET_T1Smear_pt", &PuppiMET_T1Smear_pt, &b_PuppiMET_T1Smear_pt);
	fChain->SetBranchAddress("PuppiMET_T1_phi", &PuppiMET_T1_phi, &b_PuppiMET_T1_phi);
	fChain->SetBranchAddress("PuppiMET_T1Smear_phi", &PuppiMET_T1Smear_phi, &b_PuppiMET_T1Smear_phi);
	fChain->SetBranchAddress("rawmet", &rawmet, &b_rawmet);
	fChain->SetBranchAddress("rawmetphi", &rawmetphi, &b_rawmetphi);
	fChain->SetBranchAddress("metphi", &metphi, &b_metphi);
	fChain->SetBranchAddress("gen_weight", &gen_weight, &b_gen_weight);
	fChain->SetBranchAddress("npu", &npu, &b_npu);
	fChain->SetBranchAddress("ntruepu", &ntruepu, &b_ntruepu);
	fChain->SetBranchAddress("n_pos", &n_pos, &b_n_pos);
	fChain->SetBranchAddress("n_minus", &n_minus, &b_n_minus);
	fChain->SetBranchAddress("n_num", &n_num, &b_n_num);
	fChain->SetBranchAddress("MET_pass", &MET_pass, &b_MET_pass);
	fChain->SetBranchAddress("npvs", &npvs, &b_npvs);
	fChain->SetBranchAddress("n_bjets_nom", &n_bjets_nom, &b_n_bjets_nom);
	fChain->SetBranchAddress("njets20_nom", &njets20_nom, &b_njets20_nom);
	fChain->SetBranchAddress("njets25_nom", &njets25_nom, &b_njets25_nom);
	fChain->SetBranchAddress("njets30_nom", &njets30_nom, &b_njets30_nom);
	fChain->SetBranchAddress("njets35_nom", &njets35_nom, &b_njets35_nom);
	fChain->SetBranchAddress("njets40_nom", &njets40_nom, &b_njets40_nom);
	fChain->SetBranchAddress("njets50_nom", &njets50_nom, &b_njets50_nom);
	fChain->SetBranchAddress("n_bjets", &n_bjets, &b_n_bjets);
	fChain->SetBranchAddress("njets", &njets, &b_njets);
	fChain->SetBranchAddress("njets_fake", &njets_fake, &b_njets_fake);
	fChain->SetBranchAddress("njets50", &njets50, &b_njets50);
	fChain->SetBranchAddress("njets40", &njets40, &b_njets40);
	fChain->SetBranchAddress("njets30", &njets30, &b_njets30);
	fChain->SetBranchAddress("njets20", &njets20, &b_njets20);
	fChain->SetBranchAddress("njets15", &njets15, &b_njets15);
	fChain->SetBranchAddress("puWeight", &puWeight, &b_puWeight);
	fChain->SetBranchAddress("puWeightUp", &puWeightUp, &b_puWeightUp);
	fChain->SetBranchAddress("puWeightDown", &puWeightDown, &b_puWeightDown);
	fChain->SetBranchAddress("scalef", &scalef, &b_scalef);
	fChain->SetBranchAddress("PrefireWeight", &PrefireWeight, &b_PrefireWeight);
	fChain->SetBranchAddress("PrefireWeight_Up", &PrefireWeight_Up, &b_PrefireWeight_Up);
	fChain->SetBranchAddress("PrefireWeight_Down", &PrefireWeight_Down, &b_PrefireWeight_Down);
        fChain->SetBranchAddress("LHEScaleWeight", LHEScaleWeight, &b_LHEScaleWeight);
        fChain->SetBranchAddress("LHEPdfWeight", LHEPdfWeight, &b_LHEPdfWeight);
	fChain->SetBranchAddress("btag_weight", &btag_weight, &b_btag_weight);
	fChain->SetBranchAddress("btag_weight_up", &btag_weight_up, &b_btag_weight_up);
	fChain->SetBranchAddress("btag_weight_down", &btag_weight_down, &b_btag_weight_down);
        fChain->SetBranchAddress("ele_id_scale", &ele_id_scale, &b_ele_id_scale);
        fChain->SetBranchAddress("ele_id_scale_Up", &ele_id_scale_Up, &b_ele_id_scale_Up);
        fChain->SetBranchAddress("ele_id_scale_Down", &ele_id_scale_Down, &b_ele_id_scale_Down);
        fChain->SetBranchAddress("ele_reco_scale", &ele_reco_scale, &b_ele_reco_scale);
        fChain->SetBranchAddress("ele_reco_scale_Up", &ele_reco_scale_Up, &b_ele_reco_scale_Up);
        fChain->SetBranchAddress("ele_reco_scale_Down", &ele_reco_scale_Down, &b_ele_reco_scale_Down);
        fChain->SetBranchAddress("muon_id_scale", &muon_id_scale, &b_muon_id_scale);
        fChain->SetBranchAddress("muon_id_scale_Up", &muon_id_scale_Up, &b_muon_id_scale_Up);
        fChain->SetBranchAddress("muon_id_scale_Down", &muon_id_scale_Down, &b_muon_id_scale_Down);
        fChain->SetBranchAddress("muon_iso_scale", &muon_iso_scale, &b_muon_iso_scale);
        fChain->SetBranchAddress("muon_iso_scale_Up", &muon_iso_scale_Up, &b_muon_iso_scale_Up);
        fChain->SetBranchAddress("muon_iso_scale_Down", &muon_iso_scale_Down, &b_muon_iso_scale_Down);
        fChain->SetBranchAddress("photon_id_scale", &photon_id_scale, &b_photon_id_scale);
        fChain->SetBranchAddress("photon_id_scale_Up", &photon_id_scale_Up, &b_photon_id_scale_Up);
        fChain->SetBranchAddress("photon_id_scale_Down", &photon_id_scale_Down, &b_photon_id_scale_Down);
        fChain->SetBranchAddress("photon_veto_scale", &photon_veto_scale, &b_photon_veto_scale);
        fChain->SetBranchAddress("photon_veto_scale_Up", &photon_veto_scale_Up, &b_photon_veto_scale_Up);
        fChain->SetBranchAddress("photon_veto_scale_Down", &photon_veto_scale_Down, &b_photon_veto_scale_Down);
	fChain->SetBranchAddress("HLT_IsoMu24", &HLT_IsoMu24, &b_HLT_IsoMu24);
	fChain->SetBranchAddress("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8, &b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8);
	fChain->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ, &b_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
	fChain->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL, &b_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL);
	fChain->SetBranchAddress("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL", &HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL, &b_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
	fChain->SetBranchAddress("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ, &b_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);
	fChain->SetBranchAddress("HLT_Ele32_WPTight_Gsf", &HLT_Ele32_WPTight_Gsf, &b_HLT_Ele32_WPTight_Gsf);
	fChain->SetBranchAddress("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL, &b_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL);

}

EDBRHistoMaker::EDBRHistoMaker(TTree* tree, TFile* fileTMP, TH1F* hR1, std::string out_name_, RoccoR* rc_in,TString isChannel) {
	fChain = 0;

	// Which category do we want to analyze?
	fileTMP_ = fileTMP;
	hR1_ = hR1;
	out_name = out_name_;
	rc = *rc_in;
	debug_ = true;
	Init(tree);
	createAllHistos(isChannel);
	printAllHistos();
}

float EDBRHistoMaker::get_rochester_scale(bool isdata, float charge_temp, float pt, float eta, float phi, int nl, float r1){
	int charge = int(charge_temp/fabs(charge_temp));
	// data correction
	if(isdata) return rc.kScaleDT(charge, pt, eta, phi, 0, 0);

	// MC without genPT avalible
	if((!isdata))
		return rc.kSmearMC(charge, pt, eta, phi, nl, r1, 0, 0);
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

void EDBRHistoMaker::createAllHistos(TString isChannel) {

	/// This part substitutes the big arrays that used to be 
	/// in the beginning of this file.
	/// Much simpler to create histos now: just add them to
	/// hs with hs.setHisto(name,nbins,min,max);
	hs.setHisto("mll", 10, 50, 300);
	hs.setHisto("photonet", 8, 20, 105);
	hs.setHisto("photoneta", 12, -1.5, 1.5);
	hs.setHisto("photonphi", 16, -3.14, 3.14);
	hs.setHisto("lep1pt", 15, 20, 180);
	hs.setHisto("lep1eta", 12, -2.4, 2.4);
	hs.setHisto("lep1phi", 16, -3.14, 3.14);
	hs.setHisto("lep2pt", 15, 20, 180);
	hs.setHisto("lep2eta", 12, -2.4, 2.4);
	hs.setHisto("lep2phi", 16, -3.14, 3.14);
        hs.setHisto("mllg", 12, 40, 500);
        hs.setHisto("ml1g", 10, 5, 200);
        hs.setHisto("ml2g", 10, 5, 300);
	hs.setHisto("ptll", 12, 30, 250);
	hs.setHisto("phiVlep", 16, -4, 4);
	hs.setHisto("yVlep", 20, -5, 5);
	hs.setHisto("puppimet", 12,20, 260);
	hs.setHisto("puppimetphi", 12,-3.2,3.2);
	hs.setHisto("npvs", 15, 5, 65);
	hs.setHisto("n_bjets", 6, 1, 7);
	hs.setHisto("mT", 10, 0, 250);
	hs.setHisto("mT2", 8, 30, 200);
	hs.setHisto("PuppiMET_T1_pt", 12,20, 260);
	hs.setHisto("PuppiMET_T1_phi", 12,-3.2, 3.2);
        hs.setHisto("njets", 14,0, 14);
        hs.setHisto("njets15", 14,0, 14);
        hs.setHisto("njets20", 14,0, 14);
        hs.setHisto("njets30", 14,0, 14);
        hs.setHisto("njets40", 14,0, 14);
        hs.setHisto("njets50", 14,0, 14);
	char buffer[256];
	char buffer2[256];

	nVars = hs.vars.size();

	for (int i = 0; i != nVars; ++i) {
		sprintf(buffer, "%s_"+isChannel, hs.vars[i].c_str());
		sprintf(buffer2, "%s;%s;Number of events;", hs.vars[i].c_str(),hs.vars[i].c_str());
		TH1D* histogram = new TH1D(buffer, buffer2, hs.nBins[i], hs.minBin[i],hs.maxBin[i]);
		histogram->SetStats(kFALSE);
		histogram->SetDirectory(0);
		histogram->Sumw2();
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
void EDBRHistoMaker::Loop(std::string outFileName,float luminosity,int isBarrel,TString isChannel) {

	if (fChain == 0)
		return;
	int numbe_out = 0;
	Long64_t nentries = fChain->GetEntries();
//        nentries=100;
	std::cout << "nentries" << nentries << std::endl;
	Float_t nn;
	Long64_t npp =0;
	Long64_t nmm =0;
	//	std::cout << "numberofnp:" << npp << "  numberofnm:" << nmm << std::endl;
	Long64_t nbytes = 0, nb = 0;
	TLorentzVector Zp4, photonp4, jet1p4, jet2p4,lep1p4,lep2p4;
	float sum=0;
	for (Long64_t jentry = 0; jentry < nentries; jentry++) {
		float r1=gRandom->Rndm(jentry);
		float r2=gRandom->Rndm(jentry*2);
		drll=-1e2;
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0)
			break;

		nb = fChain->GetEntry(jentry);
		nbytes += nb;
		//rochester correction
		if(fabs(lep1_pid)==13){
			muon1_rochester=get_rochester_scale(true, lep1_charge, lep1pt,lep1eta, lep1phi, Muon_nTrackerLayers , r1);
			lep1pt*=muon1_rochester;
		}
		//rochester correction

		lep1p4.SetPtEtaPhiM(lep1pt, lep1eta, lep1phi, 0.105666);
		lep2p4.SetPtEtaPhiM(lep2pt, lep2eta, lep2phi, 0.000511);
		mll=(lep1p4+lep2p4).M();
		yVlep=(lep1p4+lep2p4).Eta();
		phiVlep=(lep1p4+lep2p4).Phi();
		ptVlep=(lep1p4+lep2p4).Pt();

		Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, mll);
                photonp4.SetPtEtaPhiM(photonet, photoneta, photonphi,0);               
                mllg=(Zp4+photonp4).M();

                if(lep1pt>lep2pt){
                        ml1g=(lep1p4+photonp4).M();
                        ml2g=(lep2p4+photonp4).M();
                }
                else{
                        ml1g=(lep2p4+photonp4).M();
                        ml2g=(lep1p4+photonp4).M();
                }

                mT=sqrt(2*(ptll*PuppiMET_T1_pt*(1-cos(phiVlep-PuppiMET_T1_phi) ) ) );
		if(lep1pt>lep2pt){
			mT2=sqrt(2*(lep2pt*PuppiMET_T1_pt*(1-cos(lep2phi-PuppiMET_T1_phi) ) ) );
		}
		else{
			mT2=sqrt(2*(lep1pt*PuppiMET_T1_pt*(1-cos(lep1phi-PuppiMET_T1_phi) ) ) );
		}

		if (gen_weight > 0)
			nn = 1;
		else
			nn = -1;

		actualWeight = 1;//data
		if (fabs(lep1phi-lep2phi)>Pi) drll = sqrt((lep1eta-lep2eta)*(lep1eta-lep2eta)+(2*Pi-fabs(lep1phi-lep2phi))*(2*Pi-fabs(lep1phi-lep2phi)));
		else drll = sqrt((lep1eta-lep2eta)*(lep1eta-lep2eta)+(fabs(lep1phi-lep2phi))*(fabs(lep1phi-lep2phi)));

		if (setUnitaryWeights_) {
			if (jentry == 0)
				printf("Unitary weights set!\n");
			actualWeight = 1;
		}

		TString filename = fileTMP_->GetName();
                HLT_Mu1=HLT_IsoMu24;HLT_Mu2=HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8;
                HLT_emu1=HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL;
                HLT_emu2=HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
                HLT_emu3=HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
                HLT_emu4=HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
                HLT_Ele1=HLT_Ele32_WPTight_Gsf;HLT_Ele2=HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL;
		//data
		actualWeight=1;
                bool photon_channel=false,lepton_channel=false;
                if(isChannel=="emu") 
			lepton_channel= ((HLT_emu1||HLT_emu2||HLT_emu3||HLT_emu4) && channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && lep1pt>20 && lep2pt>25 && fabs(lep1eta) < 2.4 && fabs(lep1eta) < 2.5) && lep1_charge*lep2_charge<0 && drll>0.5;
                if(isBarrel==1)  photon_channel=( (fabs(photoneta) < 1.4442) );
                else if(isBarrel==0) photon_channel= ( fabs(photoneta) < 2.5 && fabs(photoneta)>1.566 );
                else photon_channel=( (fabs(photoneta) < 1.4442) || ( fabs(photoneta) < 2.5 && fabs(photoneta)>1.566 ));
	        if( lepton_channel && n_loose_ele==1 && n_loose_mu==1 && lep1_is_tight==1 && lep2_is_tight==1 && mll >50 && ptll > 30 && n_photon>0  && photonet > 20. && drl1a>0.5 && drl2a>0.5 && photon_channel && photon_selection==1 && PuppiMET_T1_pt > 20 && mT2 > 30 && n_bjets_nom >=1  ){
			sum = sum + actualWeight;
			numbe_out++;
			treename->Fill();
		}
		else
			continue;

		(theHistograms["mll"])->Fill(mll, actualWeight);
		(theHistograms["photonet"])->Fill(photonet, actualWeight);
		(theHistograms["photoneta"])->Fill(photoneta, actualWeight);
		(theHistograms["photonphi"])->Fill(photonphi, actualWeight);
		(theHistograms["lep1pt"])->Fill(lep1pt, actualWeight);
		(theHistograms["lep1eta"])->Fill(lep1eta, actualWeight);
		(theHistograms["lep1phi"])->Fill(lep1phi, actualWeight);
		(theHistograms["lep2pt"])->Fill(lep2pt, actualWeight);
		(theHistograms["lep2eta"])->Fill(lep2eta, actualWeight);
		(theHistograms["lep2phi"])->Fill(lep2phi, actualWeight);
		(theHistograms["mllg"])->Fill(mllg, actualWeight);
                (theHistograms["ml1g"])->Fill(ml1g, actualWeight);
                (theHistograms["ml2g"])->Fill(ml2g, actualWeight);
		(theHistograms["ptll"])->Fill(ptll, actualWeight);
		(theHistograms["phiVlep"])->Fill(phiVlep, actualWeight);
		(theHistograms["yVlep"])->Fill(yVlep, actualWeight);
		(theHistograms["puppimet"])->Fill(puppimet, actualWeight);
		(theHistograms["puppimetphi"])->Fill(puppimetphi, actualWeight);
		(theHistograms["npvs"])->Fill(npvs, actualWeight);
		(theHistograms["n_bjets"])->Fill(n_bjets_nom, actualWeight);
                (theHistograms["mT"])->Fill(mT, actualWeight);
                (theHistograms["mT2"])->Fill(mT2, actualWeight);
		(theHistograms["PuppiMET_T1_pt"])->Fill(PuppiMET_T1_pt, actualWeight);
		(theHistograms["PuppiMET_T1_phi"])->Fill(PuppiMET_T1_phi, actualWeight);
		(theHistograms["njets"])->Fill(njets, actualWeight);
                (theHistograms["njets15"])->Fill(njets15, actualWeight);
                (theHistograms["njets20"])->Fill(njets20, actualWeight);
                (theHistograms["njets30"])->Fill(njets30, actualWeight);
                (theHistograms["njets40"])->Fill(njets40, actualWeight);
                (theHistograms["njets50"])->Fill(njets50, actualWeight);
	}     //end loop over entries
	cout << "after cut: " << numbe_out << "*actualweight " << actualWeight
		<< " result " << sum <<"; yields "<<sum<< endl;
	this->saveAllHistos(outFileName);
}

void EDBRHistoMaker::Loop_SFs_mc(std::string outFileName,float luminosity,int isBarrel,TString isChannel){
	if (fChain == 0)
		return;
	int numbe_out = 0;
	Long64_t nentries = fChain->GetEntriesFast();
//	nentries=100;
	std::cout << "nentries " << nentries << std::endl;
	Long64_t npp=0;
	Long64_t nmm=0;
	Float_t nn;
	Long64_t nbytes = 0, nb = 0;

	TLorentzVector Zp4, photonp4, jet1p4, jet2p4, lep1p4, lep2p4;
	float sum=0;

	for (Long64_t jentry = 0; jentry < nentries; jentry++) {
		float r1=gRandom->Rndm(jentry);
		float r2=gRandom->Rndm(jentry*2);
		drll=-1e2;
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0)
			break;

		nb = fChain->GetEntry(jentry);
		nbytes += nb;

		//rochester correction
		TString filename = fileTMP_->GetName();
		if(fabs(lep1_pid)==13 ){
			muon1_rochester=get_rochester_scale(false, lep1_charge, lep1pt,lep1eta, lep1phi, Muon_nTrackerLayers ,r1);

			lep1pt*=muon1_rochester;
		}
		//rochester correction

                lep1p4.SetPtEtaPhiM(lep1pt, lep1eta, lep1phi, 0.105666);
                lep2p4.SetPtEtaPhiM(lep2pt, lep2eta, lep2phi, 0.000511);
                mll=(lep1p4+lep2p4).M();
                yVlep=(lep1p4+lep2p4).Eta();
                phiVlep=(lep1p4+lep2p4).Phi();
                ptVlep=(lep1p4+lep2p4).Pt();

                Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, mll);
                photonp4.SetPtEtaPhiM(photonet, photoneta, photonphi,0);        
                mllg=(Zp4+photonp4).M();

                if(lep1pt>lep2pt){
                        ml1g=(lep1p4+photonp4).M();
                        ml2g=(lep2p4+photonp4).M();
                }
                else{
                        ml1g=(lep2p4+photonp4).M();
                        ml2g=(lep1p4+photonp4).M();
                }

		if(filename.Contains("plj") || filename.Contains("fake")){
                        PuppiMET_T1Smear_pt=PuppiMET_T1_pt; 
                        PuppiMET_T1Smear_phi=PuppiMET_T1_phi; 
		}

                mT=sqrt(2*(ptll*PuppiMET_T1Smear_pt*(1-cos(phiVlep-PuppiMET_T1Smear_phi) ) ) );
		if(lep1pt>lep2pt){
			mT2=sqrt(2*(lep2pt*PuppiMET_T1Smear_pt*(1-cos(lep2phi-PuppiMET_T1Smear_phi) ) ) );
                }
                else{
			mT2=sqrt(2*(lep1pt*PuppiMET_T1Smear_pt*(1-cos(lep1phi-PuppiMET_T1Smear_phi) ) ) );
                }

		if (jentry % 100000 == 0)
			std::cout << "Entry num " << jentry << std::endl;

		if (gen_weight > 0)
			nn = 1;
		else
			nn = -1;

		if (fabs(lep1phi-lep2phi)>Pi) drll = sqrt((lep1eta-lep2eta)*(lep1eta-lep2eta)+(2*Pi-fabs(lep1phi-lep2phi))*(2*Pi-fabs(lep1phi-lep2phi)));
		else drll = sqrt((lep1eta-lep2eta)*(lep1eta-lep2eta)+(fabs(lep1phi-lep2phi))*(fabs(lep1phi-lep2phi)));

		if (setUnitaryWeights_) {
			if (jentry == 0)
				printf("Unitary weights set!\n");
			actualWeight = 1;
		}

                HLT_Mu1=HLT_IsoMu24;HLT_Mu2=HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8;
                HLT_emu1=HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL;
                HLT_emu2=HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
                HLT_emu3=HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
                HLT_emu4=HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
                HLT_Ele1=HLT_Ele32_WPTight_Gsf;HLT_Ele2=HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL;

                photon_flag=false;lepton_flag=false;
		if(filename.Contains("DY")||filename.Contains("TTJets")||filename.Contains("TTWJets")||filename.Contains("WJets")){
                     if(photon_selection==1 && photon_isprompt<1) photon_flag=1;
                     if(lep1_is_tight==1 && lep2_is_tight==1 && !(lep1_isprompt==1 && lep2_isprompt==1) ) 
			     lepton_flag=1;
		}
                else if(filename.Contains("plj")){//fake photon
                       if(photon_selection==2 || photon_selection==3 || photon_selection==4 || photon_selection==5)
			       photon_flag=1;
                       if(lep1_is_tight==1 && lep2_is_tight==1)
			       lepton_flag=1;
		}
		else if(filename.Contains("fake")){//fake lepton
                        if(photon_selection==1)
				photon_flag=1;
			if( ! (lep1_is_tight==1 && lep2_is_tight==1) )
			      lepton_flag=1;
		}
		else{//MC
                     if(photon_selection==1 && photon_isprompt==1) 
			     photon_flag=1;
                     if(lep1_is_tight==1 && lep2_is_tight==1 && lep1_isprompt==1 && lep2_isprompt==1) 
			     lepton_flag=1;
		}

                if(filename.Contains("18")) PrefireWeight=1;
		actualWeight = scalef*ele_id_scale*ele_reco_scale*muon_id_scale*muon_iso_scale*photon_id_scale*photon_veto_scale*puWeight*btag_weight*PrefireWeight;//mc
		if(filename.Contains("plj") || filename.Contains("fake")){
			actualWeight = scalef;luminosity=1;
		}// mc

		bool photon_channel=false,lepton_channel=false;
                if(isChannel=="emu") 
			lepton_channel= ((HLT_emu1||HLT_emu2||HLT_emu3||HLT_emu4) && channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && lep1pt>20 && lep2pt>25 && fabs(lep1eta) < 2.4 && fabs(lep1eta) < 2.5) && lep1_charge*lep2_charge<0 && drll>0.5;
                if(isBarrel==1)  photon_channel=( (fabs(photoneta) < 1.4442) );
                else if(isBarrel==0) photon_channel= ( fabs(photoneta) < 2.5 && fabs(photoneta)>1.566 );
                else photon_channel=( (fabs(photoneta) < 1.4442) || ( fabs(photoneta) < 2.5 && fabs(photoneta)>1.566 ));
		if( lepton_channel && n_loose_ele==1 && n_loose_mu==1 && mll >50 && ptll > 30 && lepton_flag && n_photon>0  && photonet > 20. && drl1a>0.5 && drl2a>0.5 && photon_channel && photon_flag==1 && PuppiMET_T1Smear_pt > 20 && mT2>30&& n_bjets_nom>=1 ){
			if(gen_weight>0) npp++;
			if(gen_weight<0) nmm++;
			numbe_out++;
			treename->Fill();
		}
		else
			continue;

		sum = (sum + actualWeight);

		(theHistograms["mll"])->Fill(mll, actualWeight);
		(theHistograms["photonet"])->Fill(photonet, actualWeight);
		(theHistograms["photoneta"])->Fill(photoneta, actualWeight);
		(theHistograms["photonphi"])->Fill(photonphi, actualWeight);
		(theHistograms["lep1pt"])->Fill(lep1pt, actualWeight);
		(theHistograms["lep1eta"])->Fill(lep1eta, actualWeight);
		(theHistograms["lep1phi"])->Fill(lep1phi, actualWeight);
		(theHistograms["lep2pt"])->Fill(lep2pt, actualWeight);
		(theHistograms["lep2eta"])->Fill(lep2eta, actualWeight);
		(theHistograms["lep2phi"])->Fill(lep2phi, actualWeight);
		(theHistograms["mllg"])->Fill(mllg, actualWeight);
                (theHistograms["ml1g"])->Fill(ml1g, actualWeight);
                (theHistograms["ml2g"])->Fill(ml2g, actualWeight);
                (theHistograms["ptll"])->Fill(ptll, actualWeight);
                (theHistograms["phiVlep"])->Fill(phiVlep, actualWeight);
                (theHistograms["yVlep"])->Fill(yVlep, actualWeight);
		(theHistograms["puppimet"])->Fill(puppimet, actualWeight);
		(theHistograms["puppimetphi"])->Fill(puppimetphi, actualWeight);
                (theHistograms["npvs"])->Fill(npvs, actualWeight);
                (theHistograms["n_bjets"])->Fill(n_bjets_nom, actualWeight);
                (theHistograms["mT"])->Fill(mT, actualWeight);
                (theHistograms["mT2"])->Fill(mT2, actualWeight);
		(theHistograms["PuppiMET_T1_pt"])->Fill(PuppiMET_T1Smear_pt, actualWeight);
		(theHistograms["PuppiMET_T1_phi"])->Fill(PuppiMET_T1Smear_phi, actualWeight);
		(theHistograms["njets"])->Fill(njets, actualWeight);
		(theHistograms["njets15"])->Fill(njets15, actualWeight);
		(theHistograms["njets20"])->Fill(njets20, actualWeight);
                (theHistograms["njets30"])->Fill(njets30, actualWeight);
                (theHistograms["njets40"])->Fill(njets40, actualWeight);
                (theHistograms["njets50"])->Fill(njets50, actualWeight);
	}
	cout << "after cut: " << numbe_out << "; actualweight" << actualWeight<<endl;
	cout<< " total events: " << sum <<"; yields "<<sum*luminosity<<endl;
	this->saveAllHistos(outFileName);
}
