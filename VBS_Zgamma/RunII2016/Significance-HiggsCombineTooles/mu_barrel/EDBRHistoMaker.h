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
#define Pi 3.1415926
//#include "RoccoR.C"
/// The large arrays that were here are now GONE.
/// Instead, we have this helper that holds the
/// information of all our histograms.
using namespace std;
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
		EDBRHistoMaker(TTree *tree = 0, TFile *fileTMP = 0, TH1F* hR1 = 0, std::string out_name_="");
		virtual ~EDBRHistoMaker();

		/// This is the tree structure. This comes directly from MakeClass
		TTree* fChain;   //!pointer to the analyzed TTree or TChain
		TFile* fileTMP_;
		TH1F* hR1_;
		Int_t fCurrent; //!current Tree number in a TChain
		bool setUnitaryWeights_;

		// Declaration of leaf types
		Double_t scalef;
		Int_t nVtx;
		Double_t theWeight;
		Double_t lumiWeight;
		Double_t pileupWeight;
		Int_t HLT_Ele2;
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
		Double_t drj2a;
		Double_t drj1l;
		Double_t drj1l2;
		Double_t drj2l;
		Double_t drj2l2;
		Int_t nlooseeles;
		Int_t nloosemus;
		Double_t MET_et;
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
		Double_t jet1eta;
		Double_t jet1e;
		Double_t jet2e;
		Double_t jet2pt;
		Double_t jet2eta;
		Double_t jet1phi;
		Double_t jet2phi;
		Double_t Mjj;
		Double_t zepp;
		Double_t deltaeta;
		Double_t actualWeight;
		Double_t detajj;
		Double_t ZGmass;
		Double_t delta_phi;
		Double_t drjj;
		Double_t l1_weight;
		Double_t ele1_id_scale;
		Double_t ele2_id_scale;
		Double_t ele1_reco_scale;
		Double_t ele2_reco_scale;
		Double_t photon_id_scale;
		// for rochester correction
		Int_t lep1_sign;
		Int_t lep2_sign;
		Int_t muon1_trackerLayers;
		Int_t muon2_trackerLayers;
		Double_t matchedgenMu1_pt;
		Double_t matchedgenMu2_pt;
		Double_t muon1_rochester;
		Double_t muon2_rochester;
		
		Double_t muon1_id_scale;
		Double_t muon2_id_scale;
		Double_t muon1_iso_scale;
		Double_t muon2_iso_scale;
		Double_t muon1_track_scale;
		Double_t muon2_track_scale;
		Double_t muon_hlt_scale;
		Double_t drll;
		// List of branches
		TBranch *b_drll;   //!
		TBranch *b_ele1_id_scale;   //!
		TBranch *b_ele2_id_scale;   //!
		TBranch *b_ele1_reco_scale;   //!
		TBranch *b_ele2_reco_scale;   //!
		TBranch *b_photon_id_scale;   //!
		TBranch *b_lep1_sign;   //!
		TBranch *b_lep2_sign;   //!
		TBranch *b_muon1_trackerLayers;   //!
		TBranch *b_muon2_trackerLayers;   //!
		TBranch *b_muon1_rochester;   //!
		TBranch *b_muon2_rochester;   //!
		TBranch *b_matchedgenMu1_pt;   //!
		TBranch *b_matchedgenMu2_pt;   //!
		TBranch *b_muon1_id_scale;   //!
		TBranch *b_muon2_id_scale;   //!
		TBranch *b_muon1_iso_scale;   //!
		TBranch *b_muon2_iso_scale;   //!
		TBranch *b_muon1_track_scale;   //!
		TBranch *b_muon2_track_scale;   //!
		TBranch *b_muon_hlt_scale;   //!
		TBranch *b_scalef;   //!
		TBranch *b_nVtx;   //!
		TBranch *b_theWeight;   //!
		TBranch *b_lumiWeight;   //!
		TBranch *b_pileupWeight;   //!
		TBranch *b_HLT_Ele2;   //!
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
		TBranch *b_drj2a;
		TBranch *b_drj1l;
		TBranch *b_drj1l2;
		TBranch *b_drj2l;
		TBranch *b_drj2l2;
		TBranch *b_nlooseeles;   //!
		TBranch *b_nloosemus;   //!
		TBranch *b_MET_et;   //!
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
		TBranch *b_jet1eta;   //!
		TBranch *b_jet2pt;   //!
		TBranch *b_jet2eta;   //!
		TBranch *b_jet1phi;
		TBranch *b_jet2phi;
		TBranch *b_jet1e;
		TBranch *b_jet2e;
		TBranch *b_Mjj;    //!
		TBranch *b_zepp;
		TBranch *b_deltaeta;
		TBranch *b_l1_weight;

		// Basic functions directly from MakeClass
		Int_t GetEntry(Long64_t entry);
		Long64_t LoadTree(Long64_t entry);
		void Init(TTree *tree);
		void Loop(std::string outFileName);
		void Loop_plj(std::string outFileName);
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
//		RoccoR rc;
//		double get_rochester_scale(bool isdata, double charge_temp, double pt, double eta, double phi, int nl, double genPt, double r1, double r2);


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
	treename->Branch("scalef", &scalef, "scalef/D");
	treename->Branch("nVtx", &nVtx, "nVtx/I");
	treename->Branch("theWeight", &theWeight, "theWeight/D");
	treename->Branch("lumiWeight", &lumiWeight, "lumiWeight/D");
	treename->Branch("pileupWeight", &pileupWeight, "pileupWeight/D");
	treename->Branch("HLT_Ele2", &HLT_Ele2, "HLT_Ele2/I");
	treename->Branch("HLT_Mu2", &HLT_Mu2, "HLT_Mu2/I");
	treename->Branch("HLT_Mu5", &HLT_Mu5, "HLT_Mu5/I");
	treename->Branch("nump", &nump, "nump/D");
	treename->Branch("numm", &numm, "numm/D");
	treename->Branch("npT", &npT, "npT/D");
	treename->Branch("lep", &lep, "lep/I");
	treename->Branch("run_period", &run_period, "run_period/I");
	treename->Branch("ptVlep", &ptVlep, "ptVlep/D");
	treename->Branch("yVlep", &yVlep, "yVlep/D");
	treename->Branch("phiVlep", &phiVlep, "phiVlep/D");
	treename->Branch("massVlep", &massVlep, "massVlep/D");
	treename->Branch("ptlep1", &ptlep1, "ptlep1/D");
	treename->Branch("etalep1", &etalep1, "etalep1/D");
	treename->Branch("philep1", &philep1, "philep1/D");
	treename->Branch("ptlep2", &ptlep2, "ptlep2/D");
	treename->Branch("etalep2", &etalep2, "etalep2/D");
	treename->Branch("philep2", &philep2, "philep2/D");
	treename->Branch("drla", &drla, "drla/D");
	treename->Branch("drla2", &drla2, "drla2/D");
	treename->Branch("drj1a", &drj1a, "drj1a/D");
	treename->Branch("drj2a", &drj2a, "drj2a/D");
	treename->Branch("drj1l", &drj1l, "drj1l/D");
	treename->Branch("drj2l", &drj2l, "drj2l/D");
	treename->Branch("drj1l2", &drj1l2, "drj1l2/D");
	treename->Branch("drj2l2", &drj2l2, "drj2l2/D");
	treename->Branch("nlooseeles", &nlooseeles, "nlooseeles/I");
	treename->Branch("nloosemus", &nloosemus, "nloosemus/I");
	treename->Branch("MET_et", &MET_et, "MET_et/D");
	treename->Branch("photonet", &photonet, "photonet/D");
	treename->Branch("photoneta", &photoneta, "photoneta/D");
	treename->Branch("photonphi", &photonphi, "photonphi/D");
	treename->Branch("photone", &photone, "photone/D");
	treename->Branch("photonsieie", &photonsieie, "photonsieie/D");
	treename->Branch("photonphoiso", &photonphoiso, "photonphoiso/D");
	treename->Branch("photonchiso", &photonchiso, "photonchiso/D");
	treename->Branch("photonnhiso", &photonnhiso, "photonnhiso/D");
	treename->Branch("isprompt", &isprompt, "isprompt/I");
	treename->Branch("jet1pt", &jet1pt, "jet1pt/D");
	treename->Branch("jet1eta", &jet1eta, "jet1eta/D");
	treename->Branch("jet1phi", &jet1phi, "jet1phi/D");
	treename->Branch("jet1e", &jet1e, "jet1e/D");
	treename->Branch("jet2pt", &jet2pt, "jet2pt/D");
	treename->Branch("jet2eta", &jet2eta, "jet2eta/D");
	treename->Branch("jet2phi", &jet2phi, "jet2phi/D");
	treename->Branch("jet2e", &jet2e, "jet2e/D");
	treename->Branch("Mjj", &Mjj, "Mjj/D");
	treename->Branch("ZGmass", &ZGmass, "ZGmass/D");
	treename->Branch("actualWeight", &actualWeight, "actualWeight/D");
	treename->Branch("zepp", &zepp, "zepp/D");
	treename->Branch("deltaeta", &deltaeta, "deltaeta/D");
	treename->Branch("delta_phi", &delta_phi, "delta_phi/D");
	treename->Branch("detajj", &detajj, "detajj/D");
	treename->Branch("drjj", &drjj, "drjj/D");
	treename->Branch("l1_weight", &l1_weight, "l1_weight/D");
	treename->Branch("ele1_id_scale", &ele1_id_scale, "ele1_id_scale/D");
	treename->Branch("ele2_id_scale", &ele2_id_scale, "ele2_id_scale/D");
	treename->Branch("ele1_reco_scale", &ele1_reco_scale, "ele1_reco_scale/D");
	treename->Branch("ele2_reco_scale", &ele2_reco_scale, "ele2_reco_scale/D");
	treename->Branch("photon_id_scale", &photon_id_scale, "photon_id_scale/D");
	treename->Branch("lep1_sign", &lep1_sign, "lep1_sign/I");
	treename->Branch("lep2_sign", &lep2_sign, "lep2_sign/I");
	treename->Branch("muon1_trackerLayers", &muon1_trackerLayers, "muon1_trackerLayers/I");
	treename->Branch("muon2_trackerLayers", &muon2_trackerLayers, "muon2_trackerLayers/I");
	treename->Branch("matchedgenMu1_pt", &matchedgenMu1_pt, "matchedgenMu1_pt/D");
	treename->Branch("matchedgenMu2_pt", &matchedgenMu2_pt, "matchedgenMu2_pt/D");
	treename->Branch("muon1_id_scale", &muon1_id_scale, "muon1_id_scale/D");
	treename->Branch("muon2_id_scale", &muon2_id_scale, "muon2_id_scale/D");
	treename->Branch("muon1_iso_scale", &muon1_iso_scale, "muon1_iso_scale/D");
	treename->Branch("muon2_iso_scale", &muon2_iso_scale, "muon2_iso_scale/D");
	treename->Branch("muon1_track_scale", &muon1_track_scale, "muon1_track_scale/D");
	treename->Branch("muon2_track_scale", &muon2_track_scale, "muon2_track_scale/D");
	treename->Branch("muon_hlt_scale", &muon_hlt_scale, "muon_hlt_scale/D");
	treename->Branch("muon1_rochester", &muon1_rochester, "muon1_rochester/D");
	treename->Branch("muon2_rochester", &muon2_rochester, "muon2_rochester/D");
	treename->Branch("drll", &drll, "drll/D");
	cout<<"make outfile tree end"<<endl;

	fChain->SetBranchAddress("drll", &drll, &b_drll);
	fChain->SetBranchAddress("ele1_id_scale", &ele1_id_scale, &b_ele1_id_scale);
        fChain->SetBranchAddress("ele2_id_scale", &ele2_id_scale, &b_ele2_id_scale);
        fChain->SetBranchAddress("ele1_reco_scale", &ele1_reco_scale, &b_ele1_reco_scale);
        fChain->SetBranchAddress("ele2_reco_scale", &ele2_reco_scale, &b_ele2_reco_scale);
        fChain->SetBranchAddress("photon_id_scale", &photon_id_scale, &b_photon_id_scale);
        fChain->SetBranchAddress("lep1_sign", &lep1_sign, &b_lep1_sign);
        fChain->SetBranchAddress("lep2_sign", &lep2_sign, &b_lep2_sign);
        fChain->SetBranchAddress("muon1_trackerLayers", &muon1_trackerLayers, &b_muon1_trackerLayers);
        fChain->SetBranchAddress("muon2_trackerLayers", &muon2_trackerLayers, &b_muon2_trackerLayers);
        fChain->SetBranchAddress("muon1_rochester", &muon1_rochester, &b_muon1_rochester);
        fChain->SetBranchAddress("muon2_rochester", &muon2_rochester, &b_muon2_rochester);
        fChain->SetBranchAddress("matchedgenMu1_pt", &matchedgenMu1_pt, &b_matchedgenMu1_pt);
        fChain->SetBranchAddress("matchedgenMu2_pt", &matchedgenMu2_pt, &b_matchedgenMu2_pt);
        fChain->SetBranchAddress("muon1_id_scale", &muon1_id_scale, &b_muon1_id_scale);
        fChain->SetBranchAddress("muon2_id_scale", &muon2_id_scale, &b_muon2_id_scale);
        fChain->SetBranchAddress("muon1_iso_scale", &muon1_iso_scale, &b_muon1_iso_scale);
        fChain->SetBranchAddress("muon2_iso_scale", &muon2_iso_scale, &b_muon2_iso_scale);
        fChain->SetBranchAddress("muon1_track_scale", &muon1_track_scale, &b_muon1_track_scale);
        fChain->SetBranchAddress("muon2_track_scale", &muon2_track_scale, &b_muon2_track_scale);
        fChain->SetBranchAddress("muon_hlt_scale", &muon_hlt_scale, &b_muon_hlt_scale);
	fChain->SetBranchAddress("scalef", &scalef, &b_scalef);
	fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
	fChain->SetBranchAddress("theWeight", &theWeight, &b_theWeight);
	fChain->SetBranchAddress("lumiWeight", &lumiWeight, &b_lumiWeight);
	fChain->SetBranchAddress("pileupWeight", &pileupWeight, &b_pileupWeight);
	fChain->SetBranchAddress("HLT_Ele2", &HLT_Ele2, &b_HLT_Ele2);
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
	fChain->SetBranchAddress("drj2a", &drj2a, &b_drj2a);
	fChain->SetBranchAddress("drj1l", &drj1l, &b_drj1l);
	fChain->SetBranchAddress("drj2l", &drj2l, &b_drj2l);
	fChain->SetBranchAddress("drj1l2", &drj1l2, &b_drj1l2);
	fChain->SetBranchAddress("drj2l2", &drj2l2, &b_drj2l2);
	fChain->SetBranchAddress("nlooseeles", &nlooseeles, &b_nlooseeles);
	fChain->SetBranchAddress("nloosemus", &nloosemus, &b_nloosemus);
	fChain->SetBranchAddress("MET_et", &MET_et, &b_MET_et);
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
	fChain->SetBranchAddress("jet1eta", &jet1eta, &b_jet1eta);
	fChain->SetBranchAddress("jet2pt", &jet2pt, &b_jet2pt);
	fChain->SetBranchAddress("jet2eta", &jet2eta, &b_jet2eta);
	fChain->SetBranchAddress("jet1phi", &jet1phi, &b_jet1phi);
	fChain->SetBranchAddress("jet2phi", &jet2phi, &b_jet2phi);
	fChain->SetBranchAddress("jet1e", &jet1e, &b_jet1e);
	fChain->SetBranchAddress("jet2e", &jet2e, &b_jet2e);
	fChain->SetBranchAddress("Mjj", &Mjj, &b_Mjj);
	fChain->SetBranchAddress("zepp", &zepp, &b_zepp);
	fChain->SetBranchAddress("deltaeta", &deltaeta, &b_deltaeta);
	fChain->SetBranchAddress("l1_weight", &l1_weight, &b_l1_weight);
}

EDBRHistoMaker::EDBRHistoMaker(TTree* tree, TFile* fileTMP, TH1F* hR1, std::string out_name_/*, RoccoR* rc_in*/) {
	fChain = 0;

	// Which category do we want to analyze?
	fileTMP_ = fileTMP;
	hR1_ = hR1;
	out_name = out_name_;
//	rc = *rc_in;
	debug_ = true;
	Init(tree);
	createAllHistos();
	printAllHistos();
}
/*
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
*/
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
	hs.setHisto("ptVlep", 15, 0, 450);//for ZG
//	hs.setHisto("ptVlep", 30, 0, 450);//for only Z
	hs.setHisto("etaVlep", 12, -1.5, 1.5);
	hs.setHisto("phiVlep", 16, -3.14, 3.14);
	hs.setHisto("massVlep", 10, 70, 110);//for only ZG
//	hs.setHisto("massVlep", 40, 70, 110);//for only Z
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
	hs.setHisto("Mjj_control1", 15, 150, 1500);
	hs.setHisto("Mjj_control2", 15, 150, 1500);
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
	TLorentzVector Zp4, photonp4, jet1p4, jet2p4;
	for (Long64_t jentry = 0; jentry < nentries; jentry++) {
//	double r1=gRandom->Rndm(jentry);
//	double r2=gRandom->Rndm(jentry*2);
//		drll=-1e2;
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0)
			break;

		nb = fChain->GetEntry(jentry);
		nbytes += nb;

		if (jentry % 1000000== 0)
			std::cout << "Entry num " << jentry << std::endl;

		if (theWeight > 0)
			nn = 1;
		else
			nn = -1;

		actualWeight = lumiWeight * pileupWeight * scalef;
		detajj = fabs(jet1eta - jet2eta);
		if (fabs(jet1phi-jet2phi)>Pi) drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*Pi-fabs(jet1phi-jet2phi))*(2*Pi-fabs(jet1phi-jet2phi)));
                else drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)));

//		if (fabs(philep1-philep2)>Pi) drll = sqrt((etalep1-etalep2)*(etalep1-etalep2)+(2*Pi-fabs(philep1-philep2))*(2*Pi-fabs(philep1-philep2)));
//		else drll = sqrt((etalep1-etalep2)*(etalep1-etalep2)+(fabs(philep1-philep2))*(fabs(philep1-philep2)));

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
		if (drll>0.3 && (isnotwets > 0 || iswjets > 0 || iszjets > 0 || isttjets > 0)&&l1_weight==1&&lep == 13 && ((run_period<7 && HLT_Mu5 > 0)|| (run_period==7 && HLT_Mu2 > 0)) && ptlep1 > 20. && ptlep2 > 20. && fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep > 70. && massVlep < 110. && photonet > 25. && fabs(photoneta) < 1.4442&& jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7 && drjj > 0.5&& drj1l > 0.5 && drj1l2 > 0.5 && drj2l > 0.5 && drj2l2 > 0.5&& zepp<1.8 &&ZGmass>100/* && detajj>2.5 && Mjj > 400&&*/) {

		if ((isnotwets > 0 || iswjets > 0 || iszjets > 0 || isttjets > 0)&& Mjj>400&&detajj>2.5) {
			numbe_out++;
			treename->Fill();
			(theHistograms["ptVlep"])->Fill(ptVlep, actualWeight);
			(theHistograms["etaVlep"])->Fill(yVlep, actualWeight);
			(theHistograms["phiVlep"])->Fill(phiVlep, actualWeight);
			(theHistograms["massVlep"])->Fill(massVlep, actualWeight);
			if(photonet<65)(theHistograms["photonet"])->Fill(photonet, actualWeight);
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
			(theHistograms["ZGmass"])->Fill(ZGmass, actualWeight);
			(theHistograms["nVtx"])->Fill(nVtx, actualWeight);
			(theHistograms["zepp"])->Fill(zepp, actualWeight);
			(theHistograms["delta_phi"])->Fill(delta_phi, actualWeight);
			(theHistograms["detajj"])->Fill(detajj, actualWeight);
		  }
		if((isnotwets > 0 || iswjets > 0 || iszjets > 0 || isttjets > 0)&&Mjj<400)(theHistograms["Mjj"])->Fill(Mjj, actualWeight);
		if((isnotwets > 0 || iswjets > 0 || iszjets > 0 || isttjets > 0)&&(Mjj<400 && detajj>2.5)||(Mjj>=400 && Mjj<1500 && detajj<=2.5))(theHistograms["Mjj_control1"])->Fill(Mjj, actualWeight);
		if((isnotwets > 0 || iswjets > 0 || iszjets > 0 || isttjets > 0)&&(Mjj>=1500 && detajj<=2.5))(theHistograms["Mjj_control1"])->Fill(1499, actualWeight);
		if((isnotwets > 0 || iswjets > 0 || iszjets > 0 || isttjets > 0)&&(detajj<2.5&&Mjj<1500))(theHistograms["Mjj_control2"])->Fill(Mjj, actualWeight);
		if((isnotwets > 0 || iswjets > 0 || iszjets > 0 || isttjets > 0)&&(Mjj>=1500 && detajj<2.5))(theHistograms["Mjj_control2"])->Fill(1499, actualWeight);
		}//end if
		else
			continue;

	}     //end loop over entries
	cout << "after cut: " << numbe_out << "*actualweight" << actualWeight
		<< " result " << numbe_out * actualWeight << endl;
	this->saveAllHistos(outFileName);
}

void EDBRHistoMaker::Loop_plj(std::string outFileName) {
	double scale_plj[9] = {0.401971,0.421061,0.332199,0.330386,0.251761,0.243142,0.215889,0.171153,0.168255};//central
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
	TLorentzVector Zp4, photonp4, jet1p4, jet2p4;
	for (Long64_t jentry = 0; jentry < nentries; jentry++) {
//	double r1=gRandom->Rndm(jentry);
//	double r2=gRandom->Rndm(jentry*2);
//		drll=-1e2;
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0)
			break;

		nb = fChain->GetEntry(jentry);
		nbytes += nb;

		if (jentry % 1000000== 0)
			std::cout << "Entry num " << jentry << std::endl;

		if (theWeight > 0)
			nn = 1;
		else
			nn = -1;

		actualWeight = lumiWeight * pileupWeight * scalef;
		detajj = fabs(jet1eta - jet2eta);
		if (fabs(jet1phi-jet2phi)>Pi) drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*Pi-fabs(jet1phi-jet2phi))*(2*Pi-fabs(jet1phi-jet2phi)));
                else drjj = sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)));

//		if (fabs(philep1-philep2)>Pi) drll = sqrt((etalep1-etalep2)*(etalep1-etalep2)+(2*Pi-fabs(philep1-philep2))*(2*Pi-fabs(philep1-philep2)));
//		else drll = sqrt((etalep1-etalep2)*(etalep1-etalep2)+(fabs(philep1-philep2))*(fabs(philep1-philep2)));

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
		if(photonet>120.) actualWeight = scale_plj[8];
                if(photonet>80.&& photonet<120.) actualWeight = scale_plj[7];
                if(photonet>60.&& photonet<80.) actualWeight = scale_plj[6];
                if(photonet>50.&& photonet<60.) actualWeight = scale_plj[5];
                if(photonet>45.&& photonet<50.) actualWeight = scale_plj[4];
                if(photonet>40.&& photonet<45.) actualWeight = scale_plj[3];
                if(photonet>35.&& photonet<40.) actualWeight = scale_plj[2];
                if(photonet>30.&& photonet<35.) actualWeight = scale_plj[1];
                if(photonet>25.&& photonet<30.) actualWeight = scale_plj[0];
		if (drll>0.3 && (isnotwets > 0 || iswjets > 0 || iszjets > 0 || isttjets > 0)&&l1_weight==1&&lep == 13 && ((run_period<7 && HLT_Mu5 > 0)|| (run_period==7 && HLT_Mu2 > 0)) && ptlep1 > 20. && ptlep2 > 20. && fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4	&& nlooseeles == 0 && nloosemus < 3 && massVlep > 70. && massVlep < 110. && photonet > 25. && fabs(photoneta) < 1.4442 && jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7 &&/* Mjj > 400&&*/drjj > 0.5&& drj1l > 0.5 && drj1l2 > 0.5 && drj2l > 0.5 && drj2l2 > 0.5&&/*detajj>2.5&&*/zepp<1.8&&ZGmass>100/*&&drjj > 0.5&& drj1l > 0.5 && drj1l2 > 0.5 && drj2l > 0.5 && drj2l2 > 0.5&&detajj>1.9 &&delta_phi>2.26&&zepp<1.18&& photonet>200. && Mjj>400*/ /*&& lep == 13 &&((run_period<7 && HLT_Mu5 > 0)|| (run_period==7 && HLT_Mu2 > 0) ||(run_period==8 && (HLT_Mu2 > 0) ))  && ptlep1 > 20. && ptlep2 > 20. &&fabs(etalep1) < 2.4 &&fabs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep >70. && massVlep < 110*/) {

		if ((isnotwets > 0 || iswjets > 0 || iszjets > 0 || isttjets > 0)&& Mjj>400&&detajj>2.5) {
			numbe_out++;
			treename->Fill();
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
			(theHistograms["ZGmass"])->Fill(ZGmass, actualWeight);
			(theHistograms["nVtx"])->Fill(nVtx, actualWeight);
			(theHistograms["zepp"])->Fill(zepp, actualWeight);
			(theHistograms["delta_phi"])->Fill(delta_phi, actualWeight);
			(theHistograms["detajj"])->Fill(detajj, actualWeight);
		}
			if((isnotwets > 0 || iswjets > 0 || iszjets > 0 || isttjets > 0)&&Mjj<400)(theHistograms["Mjj"])->Fill(Mjj, actualWeight);
			if((isnotwets > 0 || iswjets > 0 || iszjets > 0 || isttjets > 0)&&((Mjj<500 && detajj>2.5)||(Mjj>=500 && Mjj<1500 && detajj<=2.5)))(theHistograms["Mjj_control1"])->Fill(Mjj, actualWeight);
			if((isnotwets > 0 || iswjets > 0 || iszjets > 0 || isttjets > 0)&&Mjj>=1500 && detajj<=2.5)(theHistograms["Mjj_control1"])->Fill(1499, actualWeight);
			if((isnotwets > 0 || iswjets > 0 || iszjets > 0 || isttjets > 0)&&detajj<2.5&&Mjj<1500)(theHistograms["Mjj_control2"])->Fill(Mjj, actualWeight);
			if((isnotwets > 0 || iswjets > 0 || iszjets > 0 || isttjets > 0)&&Mjj>=1500 && detajj<2.5)(theHistograms["Mjj_control2"])->Fill(1499, actualWeight);

		}//end if
		else
			continue;
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

	TLorentzVector Zp4, photonp4, jet1p4, jet2p4;

	for (Long64_t jentry = 0; jentry < nentries; jentry++) {
//	double r1=gRandom->Rndm(jentry);
//	double r2=gRandom->Rndm(jentry*2);
//		drll=-1e2;
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0)
			break;

		nb = fChain->GetEntry(jentry);
		nbytes += nb;

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

//		if (fabs(philep1-philep2)>Pi) drll = sqrt((etalep1-etalep2)*(etalep1-etalep2)+(2*Pi-fabs(philep1-philep2))*(2*Pi-fabs(philep1-philep2)));
//                else drll = sqrt((etalep1-etalep2)*(etalep1-etalep2)+(fabs(philep1-philep2))*(fabs(philep1-philep2)));

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
		Double_t photon_veto_scale=0.9938;//barrel
		actualWeight = actualWeight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon1_track_scale*muon2_track_scale*muon_hlt_scale*photon_id_scale*photon_veto_scale;
		if (drll>0.3 && (isnotwets > 0 || iswjets > 0 || iszjets > 0 || isttjets > 0)&&l1_weight==1&&lep == 13 && HLT_Mu2 > 0 && ptlep1 > 20. && ptlep2 > 20. && fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep > 70. && massVlep < 110. && photonet > 25. && fabs(photoneta) < 1.4442 && jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7 && /*Mjj > 400&&*/drjj > 0.5&& drj1l > 0.5 && drj1l2 > 0.5 && drj2l > 0.5 && drj2l2 > 0.5&& /*detajj>2.5&&*/zepp<1.8&&ZGmass>100/*&&drjj > 0.5&& drj1l > 0.5 && drj1l2 > 0.5 && drj2l > 0.5 && drj2l2 > 0.5&&detajj>1.9 &&delta_phi>2.26&&zepp<1.18*/ /* && photonet>200. && Mjj>400 *//*&& lep == 13 &&((run_period<7 && HLT_Mu5 > 0)|| (run_period==7 && HLT_Mu2 > 0) ||(run_period==8 && (HLT_Mu2 > 0) ))  && ptlep1 > 20. && ptlep2 > 20. &&fabs(etalep1) < 2.4 &&fabs(etalep2) < 2.4 && nlooseeles == 0 && nloosemus < 3 && massVlep >70. && massVlep < 110*/) {

		if ((isnotwets > 0 || iswjets > 0 || iszjets > 0 || isttjets > 0)&& Mjj > 400&& detajj>2.5) {
			numbe_out++;
			treename->Fill();
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
			(theHistograms["ZGmass"])->Fill(ZGmass, actualWeight);
			(theHistograms["nVtx"])->Fill(nVtx, actualWeight);
			(theHistograms["zepp"])->Fill(zepp, actualWeight);
			(theHistograms["delta_phi"])->Fill(delta_phi, actualWeight);
			(theHistograms["detajj"])->Fill(detajj, actualWeight);
		  }
		if((isnotwets > 0|| iswjets > 0 || iszjets > 0 || isttjets > 0)&& Mjj<400)
			(theHistograms["Mjj"])->Fill(Mjj, actualWeight);
		if((isnotwets > 0|| iswjets > 0 || iszjets > 0 || isttjets > 0)&&(Mjj<500 && detajj>2.5)||(Mjj>=500 && Mjj<1500 && detajj<=2.5))
			(theHistograms["Mjj_control1"])->Fill(Mjj, actualWeight);
		if((isnotwets > 0 || iswjets > 0 || iszjets > 0 || isttjets > 0)&&Mjj>=1500 && detajj<=2.5)
			(theHistograms["Mjj_control1"])->Fill(1499, actualWeight);
		if((isnotwets > 0 || iswjets > 0 || iszjets > 0 || isttjets > 0)&&detajj<2.5&&Mjj<1500)
			(theHistograms["Mjj_control2"])->Fill(Mjj, actualWeight);
		if((isnotwets > 0 || iswjets > 0 || iszjets > 0 || isttjets > 0)&&Mjj>=1500 && detajj<2.5)
			(theHistograms["Mjj_control2"])->Fill(1499, actualWeight);

		}//end if
		else
			continue;
	}//end loop
	cout << "after cut: " << numbe_out << "*actualweight" << actualWeight
		<< " result " << numbe_out * actualWeight << endl;
	this->saveAllHistos(outFileName);
}
