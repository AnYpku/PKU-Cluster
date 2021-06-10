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
#include "RoccoR.cc"
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
                Bool_t          photon_flag;
                Bool_t          lepton1_flag;
                Bool_t          lepton2_flag;
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
		Int_t           lepton1_isprompt;
		Int_t           lepton2_isprompt;
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
		Float_t         ptll;
		Float_t         mt;
		Float_t         met;
		Float_t         metup;
		Float_t         puppimet;
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
		Int_t           n_bjets;
		Int_t           njets;
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
		Double_t        scalef;
		Float_t        actualWeight;
                Float_t        drll;
                Float_t        yVlep;
                Float_t        phiVlep;
                Float_t        ptVlep;
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
		TBranch        *b_lepton1_isprompt;   //!
		TBranch        *b_lepton2_isprompt;   //!
		TBranch        *b_n_loose_mu;   //!
		TBranch        *b_n_loose_ele;   //!
		TBranch        *b_n_photon;   //!
		TBranch        *b_photonet;   //!
		TBranch        *b_photoneta;   //!
		TBranch        *b_photonphi;   //!
		TBranch        *b_photon_isprompt;   //!
		TBranch        *b_photon_gen_matching;   //!
		TBranch        *b_mll;   //!
		TBranch        *b_mllg;   //!
		TBranch        *b_ptll;   //!
		TBranch        *b_mt;   //!
		TBranch        *b_met;   //!
		TBranch        *b_metup;   //!
		TBranch        *b_puppimet;   //!
		TBranch        *b_puppimetphi;   //!
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
		TBranch        *b_njets;   //!
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
		TBranch        *b_scalef;   //!

		// Basic functions directly from MakeClass
		Int_t GetEntry(Long64_t entry);
		Long64_t LoadTree(Long64_t entry);
		void Init(TTree *tree);
		void Loop(std::string outFileName,double lumi);
		void Loop_SFs_mc(std::string outFileNamei,double lumi);
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
		double get_rochester_scale(bool isdata, double charge_temp, double pt, double eta, double phi, int nl, double genPt, double r1);


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
	treename->Branch("lep1_pid", &lep1_pid, "lep1_pid/I");
	treename->Branch("lep2_pid", &lep2_pid, "lep1_pid/I");
	treename->Branch("lep1pt", &lep1pt,     "lep1pt/F");
	treename->Branch("lep2pt", &lep2pt,     "lep2pt/F");
	treename->Branch("lep1eta", &lep1eta,   "lep1eta/F");
	treename->Branch("lep2eta", &lep2eta,   "lep2eta/F");
	treename->Branch("lep1phi", &lep1phi,   "lep1phi/I");
	treename->Branch("lep2phi", &lep2phi,   "lep1phi/I");
	treename->Branch("lepton1_isprompt", &lepton1_isprompt, "lepton1_isprompt/I");
	treename->Branch("lepton2_isprompt", &lepton2_isprompt, "lepton1_isprompt/I");
	treename->Branch("n_loose_mu", &n_loose_mu,   "n_loose_mu/I");
	treename->Branch("n_loose_ele", &n_loose_ele, "n_loose_ele/I");
	treename->Branch("n_photon", &n_photon, "n_photon/I");
	treename->Branch("photonet", &photonet,   "photonet/F");
	treename->Branch("photoneta", &photoneta, "photoneta/F");
	treename->Branch("photonphi", &photonphi, "photonphi/F");
	treename->Branch("photon_isprompt", &photon_isprompt, "photon_isprompt/I");
	treename->Branch("photon_gen_matching", &photon_gen_matching, "photon_gen_matching/I");
	treename->Branch("mll", &mll, "mll/F");
	treename->Branch("mllg", &mllg, "mllg/F");
	treename->Branch("ptll", &ptll, "ptll/F");
	treename->Branch("mt", &mt, "mt/F");
	treename->Branch("met", &met, "met/F");
	treename->Branch("metup", &metup, "metup/F");
	treename->Branch("puppimet", &puppimet, "puppimet/F");
	treename->Branch("puppimetphi", &puppimetphi, "puppimetphi/F");
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
	treename->Branch("n_bjets", &n_bjets, "n_bjets/I");
	treename->Branch("njets", &njets, "njets/I");
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
	treename->Branch("scalef", &scalef, "scalef/D");
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
	fChain->SetBranchAddress("lepton1_isprompt", &lepton1_isprompt, &b_lepton1_isprompt);
	fChain->SetBranchAddress("lepton2_isprompt", &lepton2_isprompt, &b_lepton2_isprompt);
	fChain->SetBranchAddress("n_loose_mu", &n_loose_mu, &b_n_loose_mu);
	fChain->SetBranchAddress("n_loose_ele", &n_loose_ele, &b_n_loose_ele);
	fChain->SetBranchAddress("n_photon", &n_photon, &b_n_photon);
	fChain->SetBranchAddress("photonet", &photonet, &b_photonet);
	fChain->SetBranchAddress("photoneta", &photoneta, &b_photoneta);
	fChain->SetBranchAddress("photonphi", &photonphi, &b_photonphi);
	fChain->SetBranchAddress("photon_isprompt", &photon_isprompt, &b_photon_isprompt);
	fChain->SetBranchAddress("photon_gen_matching", &photon_gen_matching, &b_photon_gen_matching);
	fChain->SetBranchAddress("mll", &mll, &b_mll);
	fChain->SetBranchAddress("mllg", &mllg, &b_mllg);
	fChain->SetBranchAddress("ptll", &ptll, &b_ptll);
	fChain->SetBranchAddress("mt", &mt, &b_mt);
	fChain->SetBranchAddress("met", &met, &b_met);
	fChain->SetBranchAddress("metup", &metup, &b_metup);
	fChain->SetBranchAddress("puppimet", &puppimet, &b_puppimet);
	fChain->SetBranchAddress("puppimetphi", &puppimetphi, &b_puppimetphi);
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
	fChain->SetBranchAddress("n_bjets", &n_bjets, &b_n_bjets);
	fChain->SetBranchAddress("njets", &njets, &b_njets);
	fChain->SetBranchAddress("njets50", &njets50, &b_njets50);
	fChain->SetBranchAddress("njets40", &njets40, &b_njets40);
	fChain->SetBranchAddress("njets30", &njets30, &b_njets30);
	fChain->SetBranchAddress("njets20", &njets20, &b_njets20);
	fChain->SetBranchAddress("njets15", &njets15, &b_njets15);
	fChain->SetBranchAddress("puWeight", &puWeight, &b_puWeight);
	fChain->SetBranchAddress("puWeightUp", &puWeightUp, &b_puWeightUp);
	fChain->SetBranchAddress("puWeightDown", &puWeightDown, &b_puWeightDown);
	fChain->SetBranchAddress("scalef", &scalef, &b_scalef);
	fChain->SetBranchAddress("HLT_IsoMu24", &HLT_IsoMu24, &b_HLT_IsoMu24);
	fChain->SetBranchAddress("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8, &b_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8);
	fChain->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ, &b_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
	fChain->SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL, &b_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL);
	fChain->SetBranchAddress("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL", &HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL, &b_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
	fChain->SetBranchAddress("HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ, &b_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);
	fChain->SetBranchAddress("HLT_Ele32_WPTight_Gsf", &HLT_Ele32_WPTight_Gsf, &b_HLT_Ele32_WPTight_Gsf);
	fChain->SetBranchAddress("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL, &b_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL);

}

EDBRHistoMaker::EDBRHistoMaker(TTree* tree, TFile* fileTMP, TH1F* hR1, std::string out_name_, RoccoR* rc_in) {
	fChain = 0;

	// Which category do we want to analyze?
	fileTMP_ = fileTMP;
	hR1_ = hR1;
	out_name = out_name_;
	rc = *rc_in;
	debug_ = true;
	Init(tree);
	createAllHistos();
	printAllHistos();
}

double EDBRHistoMaker::get_rochester_scale(bool isdata, double charge_temp, double pt, double eta, double phi, int nl, double genPt, double r1){
	int charge = int(charge_temp/fabs(charge_temp));
	// data correction
	if(isdata) return rc.kScaleDT(charge, pt, eta, phi, 0, 0);

	// MC with genPt avalible
	if((!isdata) && genPt>0&&fabs(genPt-pt)/pt<0.1)
		return rc.kSpreadMC(charge, pt, eta, phi, genPt, 0, 0);

	// MC without genPT avalible
	if((!isdata) && !(genPt>0&&fabs(genPt-pt)/pt<0.1))
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

void EDBRHistoMaker::createAllHistos() {

	/// This part substitutes the big arrays that used to be 
	/// in the beginning of this file.
	/// Much simpler to create histos now: just add them to
	/// hs with hs.setHisto(name,nbins,min,max);
	hs.setHisto("mll", 18, 40, 200);
	hs.setHisto("photonet", 8, 20, 105);
	hs.setHisto("photoneta", 12, -1.5, 1.5);
	hs.setHisto("photonphi", 16, -3.14, 3.14);
	hs.setHisto("lep1pt", 10, 20, 300);
	hs.setHisto("lep1eta", 12, -2.4, 2.4);
	hs.setHisto("lep1phi", 16, -3.14, 3.14);
	hs.setHisto("lep2pt", 10, 20, 300);
	hs.setHisto("lep2eta", 12, -2.4, 2.4);
	hs.setHisto("lep2phi", 16, -3.14, 3.14);
	hs.setHisto("mllg", 8, 70, 500);
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
void EDBRHistoMaker::Loop(std::string outFileName,double lumi) {

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
	double sum=0;
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
		/*if(lep==13){
		  muon1_rochester=get_rochester_scale(true, lep1_sign, lep1pt,lep1eta, lep1phi, muon1_trackerLayers, matchedgenMu1_pt,r1);
		  muon2_rochester=get_rochester_scale(true, lep2_sign, lep2pt,lep2eta, lep2phi, muon2_trackerLayers, matchedgenMu2_pt,r1);
		  lep1pt*=muon1_rochester;
		  lep2pt*=muon2_rochester;
		  }*/
		//rochester correction

//		lep1p4.SetPtEtaPhiM(lep1pt, lep1eta, lep1phi, 0.105666);
//		lep2p4.SetPtEtaPhiM(lep2pt, lep2eta, lep2phi, 0.105666);
//		mll=(lep1p4+lep2p4).M();
		yVlep=(lep1p4+lep2p4).Eta();
		phiVlep=(lep1p4+lep2p4).Phi();
		ptVlep=(lep1p4+lep2p4).Pt();

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
                
	        if( (HLT_emu1 ||HLT_emu2 || HLT_emu3 || HLT_emu4 ) && lep1pt > 20. && lep2pt > 20. && fabs(lep1eta) < 2.4 && fabs(lep2eta) < 2.4 && n_loose_ele == 1 && n_loose_mu == 1 && n_photon>0  && photonet > 20. &&( (fabs(photoneta) < 1.4442) ) && ptll > 30 && mll >50 && met > 20 && n_bjets >=1 ){
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

	}     //end loop over entries
	cout << "after cut: " << numbe_out << "*actualweight " << actualWeight
		<< " result " << sum <<"; yields "<<sum<< endl;
	this->saveAllHistos(outFileName);
}

void EDBRHistoMaker::Loop_SFs_mc(std::string outFileName,double lumi){
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
	double sum=0;

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
		TString name=fileTMP_->GetName();
		/*if(lep==13 ){
		  muon1_rochester=get_rochester_scale(false, lep1_sign, lep1pt,lep1eta, lep1phi, muon1_trackerLayers, matchedgenMu1_pt,r1);
		  muon2_rochester=get_rochester_scale(false, lep2_sign, lep2pt,lep2eta, lep2phi, muon2_trackerLayers, matchedgenMu2_pt,r1);

		  lep1pt*=muon1_rochester;
		  lep2pt*=muon2_rochester;
		  }*/
		//rochester correction

//		lep1p4.SetPtEtaPhiM(lep1pt, lep1eta, lep1phi, 0.105666);
//		lep2p4.SetPtEtaPhiM(lep2pt, lep2eta, lep2phi, 0.105666);
//		mll=(lep1p4+lep2p4).M();
		yVlep=(lep1p4+lep2p4).Eta();
		phiVlep=(lep1p4+lep2p4).Phi();
		ptVlep=(lep1p4+lep2p4).Pt();
		if (jentry % 100000 == 0)
			std::cout << "Entry num " << jentry << std::endl;

		if (gen_weight > 0)
			nn = 1;
		else
			nn = -1;
		actualWeight = scalef;//mc

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
		actualWeight = scalef;
		if(filename.Contains("plj")){
			actualWeight = scalef;
			lumi=1;
		}
		// mc
                photon_flag=false;
		if(filename.Contains("DY")||filename.Contains("TTJets")||filename.Contains("TTWJets")||filename.Contains("WJets")){
                     if(photon_isprompt<1) photon_flag=1;
		}
                else if(filename.Contains("plj"))
                       photon_flag=1;
		else{
                     if(photon_isprompt==1) photon_flag=1;
		}
		if( (HLT_emu1 > 0||HLT_emu2>0 || HLT_emu3>0 || HLT_emu4>0) && lep1pt > 20. && lep2pt > 20. && fabs(lep1eta) < 2.4 && fabs(lep2eta) < 2.4 && n_loose_ele == 1 && n_loose_mu == 1 && n_photon>0  && photonet > 20. &&( (fabs(photoneta) < 1.4442) ) && photon_flag==1 && ptll > 30 && mll >50 && met > 20 && n_bjets >=1 ){
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
	}
	cout << "after cut: " << numbe_out << "; actualweight" << actualWeight<<endl;
	cout<< " total events: " << sum <<"; yields "<<sum*lumi<<endl;
	this->saveAllHistos(outFileName);
}
