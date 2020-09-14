//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Apr 30 22:58:33 2019 by ROOT version 6.06/01
// from TTree hltGenTree/
// found on file: zToEE_M_50_120_102X_TrigNtup.root
//////////////////////////////////////////////////////////

#ifndef test_h
#define test_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class test {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           evt_runnr;
   Int_t           evt_lumiSec;
   Int_t           evt_eventnr;
   Int_t           evt_bx;
   Int_t           evt_datasetCode;
   Int_t           genPU_nrTruePUInt;
   Int_t           genPU_nrPUInt;
   Int_t           genPU_nrPUIntPos;
   Int_t           genPU_nrPUIntNeg;
   Float_t         weight;
   Float_t         genWeight;
   Float_t         puWeight;
   Float_t         truthDR;
 //EleStructs::EleStruct *ele;
   Float_t         nrgy;
   Float_t         clusNrgy;
   Float_t         gsfNrgy;
   Float_t         preShowerNrgy;
   Float_t         et;
   Float_t         clusEt;
   Float_t         eta;
   Float_t         phi;
   Float_t         detEta;
   Float_t         detPhi;
   Float_t         z0;
   Char_t          region;
   Char_t          q;
   Float_t         trkPt;
   Float_t         epIn;
   Float_t         epOut;
   Float_t         invEinvP;
   Float_t         bremFrac;
   Float_t         trkPInn;
   Float_t         trkEtaInn;
   Float_t         trkPhiInn;
   Float_t         dEtaIn;
   Float_t         dEtaInSeed;
   Float_t         dPhiIn;
   Float_t         hadem;
   Float_t         sigmaIEtaIEta;
   Float_t         e1x5Over5x5;
   Float_t         e2x5Over5x5;
   Float_t         e5x5;
   Float_t         isolEm;
   Float_t         isolHadDepth1;
   Float_t         isolHadDepth2;
   Float_t         isolPtTrks;
   Float_t         dxy;
   Float_t         nrMissHits;
   Float_t         r9;
   Float_t         rhoCorr;
   Float_t         isolCharged;
   Float_t         isolNeutral;
   Float_t         isolPhoton;
   Float_t         isolEcalClus;
   Float_t         isolHcalClus;
   Float_t         hademDepth1BC;
   Float_t         hademDepth2BC;
   Char_t          nrSatIn5x5;
   Bool_t          passCutPreSel;
   Bool_t          passPFPreSel;
   Bool_t          hasTrk;
   Bool_t          isEcalDriven;
   Bool_t          isTrackerDriven;
   Int_t           cutCode;
   Int_t           vidIds;
   Float_t         rawNrgy;
   Float_t         seedClusEt;
   Float_t         seedClusEta;
   Float_t         seedClusPhi;
   Short_t         nrClus;
   Short_t         nrCrys;
   Float_t         eMax;
   Float_t         e3x3;
   Short_t         eMaxPhi;
   Short_t         eMaxEta;
   Short_t         eMaxTowerPhi;
   Short_t         eMaxTowerEta;
   Short_t         e2ndPhi;
   Short_t         e2ndEta;
   Short_t         e2ndTowerPhi;
   Short_t         e2ndTowerEta;
   Char_t          seedRegion;
   Char_t          nrGain6In5x5;
   Char_t          nrGain1In5x5;
   Float_t         towerHadEt;
   Float_t         towerEmEt;
   Float_t         towerHadD1Nrgy;
   Float_t         towerHadD2Nrgy;
   Float_t         nrgyAlt;
   Float_t         gsfNrgyAlt;
   Float_t         phoNrgy;
   Float_t         phoNrgyAlt;
   Int_t           gain6Map;
   Int_t           gain1Map;
   Float_t         isolPtTrksAlt;
   Float_t         mvaIsol;
   Float_t         mvaNonIsol;
   Float_t         eleTruthNrgy;
   Float_t         eleTruthPhi;
   Float_t         eleTruthEta;
   Float_t         eleTruthDetEta;
   Float_t         eleTruthRegion;
   Float_t         eleTruthEt;
   Float_t         eleTruthZ;
   Float_t         eleTruthY;
   Float_t         eleTruthX;
   Int_t           pid;
   Int_t           eleTrigs[4];
   Int_t           evtTrigs;
   Float_t         hlt_nrgy;
   Float_t         hlt_et;
   Float_t         hlt_eta;
   Float_t         hlt_phi;
   Float_t         hlt_pt;
   Float_t         egHLT_et;
   Float_t         egHLT_nrgy;
   Float_t         egHLT_eta;
   Float_t         egHLT_phi;
   Float_t         egHLT_hadem;
   Float_t         egHLT_sigmaIEtaIEta;
   Float_t         egHLT_dEtaIn;
   Float_t         egHLT_dPhiIn;
   Float_t         egHLT_nrMissHits;
   Float_t         egHLT_nrClus;
   Float_t         egHLT_seedClusEFrac;
   Float_t         egHLT_pmDPhi1;
   Float_t         egHLT_pmDPhi2;
   Float_t         egHLT_pmDPhi3;
   Float_t         egHLT_pmDPhi4;
   Float_t         egHLT_pmDPhi1Info;
   Float_t         egHLT_pmDPhi2Info;
   Float_t         egHLT_pmDPhi3Info;
   Float_t         egHLT_pmDPhi4Info;
   Float_t         egHLT_pmDRZ1;
   Float_t         egHLT_pmDRZ2;
   Float_t         egHLT_pmDRZ3;
   Float_t         egHLT_pmDRZ4;
   Float_t         egHLT_pmDRZ1Info;
   Float_t         egHLT_pmDRZ2Info;
   Float_t         egHLT_pmDRZ3Info;
   Float_t         egHLT_pmDRZ4Info;
   Float_t         egHLT_phiWidth;
   Float_t         egHLT_etaWidth;
   Float_t         egHLT_s2;
   Float_t         egHLT_dPhi1BestS2;
   Float_t         egHLT_dPhi2BestS2;
   Float_t         egHLT_dPhi3BestS2;
   Float_t         egHLT_dRZ2BestS2;
   Float_t         egHLT_dRZ3BestS2;
   Float_t         egHLT_ecalIso;
   Float_t         egHLT_hcalIso;
   Float_t         egHLT_trkIso;
   Float_t         egHLT_trkChi2;
   Float_t         egHLT_invEOInvP;
   Float_t         egHLTUS_et;
   Float_t         egHLTUS_nrgy;
   Float_t         egHLTUS_eta;
   Float_t         egHLTUS_phi;
   Float_t         egHLTUS_hadem;
   Float_t         egHLTUS_sigmaIEtaIEta;
   Float_t         egHLTUS_dEtaIn;
   Float_t         egHLTUS_dPhiIn;
   Float_t         egHLTUS_nrMissHits;
   Float_t         egHLTUS_nrClus;
   Float_t         egHLTUS_seedClusEFrac;
   Float_t         egHLTUS_pmDPhi1;
   Float_t         egHLTUS_pmDPhi2;
   Float_t         egHLTUS_pmDPhi3;
   Float_t         egHLTUS_pmDPhi4;
   Float_t         egHLTUS_pmDPhi1Info;
   Float_t         egHLTUS_pmDPhi2Info;
   Float_t         egHLTUS_pmDPhi3Info;
   Float_t         egHLTUS_pmDPhi4Info;
   Float_t         egHLTUS_pmDRZ1;
   Float_t         egHLTUS_pmDRZ2;
   Float_t         egHLTUS_pmDRZ3;
   Float_t         egHLTUS_pmDRZ4;
   Float_t         egHLTUS_pmDRZ1Info;
   Float_t         egHLTUS_pmDRZ2Info;
   Float_t         egHLTUS_pmDRZ3Info;
   Float_t         egHLTUS_pmDRZ4Info;
   Float_t         egHLTUS_phiWidth;
   Float_t         egHLTUS_etaWidth;
   Float_t         egHLTUS_s2;
   Float_t         egHLTUS_dPhi1BestS2;
   Float_t         egHLTUS_dPhi2BestS2;
   Float_t         egHLTUS_dPhi3BestS2;
   Float_t         egHLTUS_dRZ2BestS2;
   Float_t         egHLTUS_dRZ3BestS2;
   Float_t         egHLTUS_ecalIso;
   Float_t         egHLTUS_hcalIso;
   Float_t         egHLTUS_trkIso;
   Float_t         egHLTUS_trkChi2;
   Float_t         egHLTUS_invEOInvP;
   Float_t         rho;
   Float_t         rhoAlt;

   // List of branches
   TBranch        *b_evt;   //!
   TBranch        *b_genPU;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_genWeight;   //!
   TBranch        *b_puWeight;   //!
   TBranch        *b_truthDR;   //!
   TBranch        *b_ele_nrgy;   //!
   TBranch        *b_ele_clusNrgy;   //!
   TBranch        *b_ele_gsfNrgy;   //!
   TBranch        *b_ele_preShowerNrgy;   //!
   TBranch        *b_ele_et;   //!
   TBranch        *b_ele_clusEt;   //!
   TBranch        *b_ele_eta;   //!
   TBranch        *b_ele_phi;   //!
   TBranch        *b_ele_detEta;   //!
   TBranch        *b_ele_detPhi;   //!
   TBranch        *b_ele_z0;   //!
   TBranch        *b_ele_region;   //!
   TBranch        *b_ele_q;   //!
   TBranch        *b_ele_trkPt;   //!
   TBranch        *b_ele_epIn;   //!
   TBranch        *b_ele_epOut;   //!
   TBranch        *b_ele_invEinvP;   //!
   TBranch        *b_ele_bremFrac;   //!
   TBranch        *b_ele_trkPInn;   //!
   TBranch        *b_ele_trkEtaInn;   //!
   TBranch        *b_ele_trkPhiInn;   //!
   TBranch        *b_ele_dEtaIn;   //!
   TBranch        *b_ele_dEtaInSeed;   //!
   TBranch        *b_ele_dPhiIn;   //!
   TBranch        *b_ele_hadem;   //!
   TBranch        *b_ele_sigmaIEtaIEta;   //!
   TBranch        *b_ele_e1x5Over5x5;   //!
   TBranch        *b_ele_e2x5Over5x5;   //!
   TBranch        *b_ele_e5x5;   //!
   TBranch        *b_ele_isolEm;   //!
   TBranch        *b_ele_isolHadDepth1;   //!
   TBranch        *b_ele_isolHadDepth2;   //!
   TBranch        *b_ele_isolPtTrks;   //!
   TBranch        *b_ele_dxy;   //!
   TBranch        *b_ele_nrMissHits;   //!
   TBranch        *b_ele_r9;   //!
   TBranch        *b_ele_rhoCorr;   //!
   TBranch        *b_ele_isolCharged;   //!
   TBranch        *b_ele_isolNeutral;   //!
   TBranch        *b_ele_isolPhoton;   //!
   TBranch        *b_ele_isolEcalClus;   //!
   TBranch        *b_ele_isolHcalClus;   //!
   TBranch        *b_ele_hademDepth1BC;   //!
   TBranch        *b_ele_hademDepth2BC;   //!
   TBranch        *b_ele_nrSatIn5x5;   //!
   TBranch        *b_ele_passCutPreSel;   //!
   TBranch        *b_ele_passPFPreSel;   //!
   TBranch        *b_ele_hasTrk;   //!
   TBranch        *b_ele_isEcalDriven;   //!
   TBranch        *b_ele_isTrackerDriven;   //!
   TBranch        *b_ele_cutCode;   //!
   TBranch        *b_ele_vidIds;   //!
   TBranch        *b_ele_rawNrgy;   //!
   TBranch        *b_ele_seedClusEt;   //!
   TBranch        *b_ele_seedClusEta;   //!
   TBranch        *b_ele_seedClusPhi;   //!
   TBranch        *b_ele_nrClus;   //!
   TBranch        *b_ele_nrCrys;   //!
   TBranch        *b_ele_eMax;   //!
   TBranch        *b_ele_e3x3;   //!
   TBranch        *b_ele_eMaxPhi;   //!
   TBranch        *b_ele_eMaxEta;   //!
   TBranch        *b_ele_eMaxTowerPhi;   //!
   TBranch        *b_ele_eMaxTowerEta;   //!
   TBranch        *b_ele_e2ndPhi;   //!
   TBranch        *b_ele_e2ndEta;   //!
   TBranch        *b_ele_e2ndTowerPhi;   //!
   TBranch        *b_ele_e2ndTowerEta;   //!
   TBranch        *b_ele_seedRegion;   //!
   TBranch        *b_ele_nrGain6In5x5;   //!
   TBranch        *b_ele_nrGain1In5x5;   //!
   TBranch        *b_ele_towerHadEt;   //!
   TBranch        *b_ele_towerEmEt;   //!
   TBranch        *b_ele_towerHadD1Nrgy;   //!
   TBranch        *b_ele_towerHadD2Nrgy;   //!
   TBranch        *b_ele_nrgyAlt;   //!
   TBranch        *b_ele_gsfNrgyAlt;   //!
   TBranch        *b_ele_phoNrgy;   //!
   TBranch        *b_ele_phoNrgyAlt;   //!
   TBranch        *b_ele_gain6Map;   //!
   TBranch        *b_ele_gain1Map;   //!
   TBranch        *b_ele_isolPtTrksAlt;   //!
   TBranch        *b_ele_mvaIsol;   //!
   TBranch        *b_ele_mvaNonIsol;   //!
   TBranch        *b_eleTruthNrgy;   //!
   TBranch        *b_eleTruthPhi;   //!
   TBranch        *b_eleTruthEta;   //!
   TBranch        *b_eleTruthDetEta;   //!
   TBranch        *b_eleTruthRegion;   //!
   TBranch        *b_eleTruthEt;   //!
   TBranch        *b_eleTruthZ;   //!
   TBranch        *b_eleTruthY;   //!
   TBranch        *b_eleTruthX;   //!
   TBranch        *b_pid;   //!
   TBranch        *b_eleTrigs;   //!
   TBranch        *b_evtTrigs;   //!
   TBranch        *b_hlt;   //!
   TBranch        *b_egHLT;   //!
   TBranch        *b_egHLTUS;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_rhoAlt;   //!

   test(TTree *tree=0);
   virtual ~test();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef test_cxx
test::test(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("zToEE_M_50_120_102X_TrigNtup.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("zToEE_M_50_120_102X_TrigNtup.root");
      }
      f->GetObject("hltGenTree",tree);

   }
   Init(tree);
}

test::~test()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t test::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t test::LoadTree(Long64_t entry)
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

void test::Init(TTree *tree)
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

   fChain->SetBranchAddress("evt", &evt_runnr, &b_evt);
   fChain->SetBranchAddress("genPU", &genPU_nrTruePUInt, &b_genPU);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
   fChain->SetBranchAddress("puWeight", &puWeight, &b_puWeight);
   fChain->SetBranchAddress("truthDR", &truthDR, &b_truthDR);
   fChain->SetBranchAddress("nrgy", &nrgy, &b_ele_nrgy);
   fChain->SetBranchAddress("clusNrgy", &clusNrgy, &b_ele_clusNrgy);
   fChain->SetBranchAddress("gsfNrgy", &gsfNrgy, &b_ele_gsfNrgy);
   fChain->SetBranchAddress("preShowerNrgy", &preShowerNrgy, &b_ele_preShowerNrgy);
   fChain->SetBranchAddress("et", &et, &b_ele_et);
   fChain->SetBranchAddress("clusEt", &clusEt, &b_ele_clusEt);
   fChain->SetBranchAddress("eta", &eta, &b_ele_eta);
   fChain->SetBranchAddress("phi", &phi, &b_ele_phi);
   fChain->SetBranchAddress("detEta", &detEta, &b_ele_detEta);
   fChain->SetBranchAddress("detPhi", &detPhi, &b_ele_detPhi);
   fChain->SetBranchAddress("z0", &z0, &b_ele_z0);
   fChain->SetBranchAddress("region", &region, &b_ele_region);
   fChain->SetBranchAddress("q", &q, &b_ele_q);
   fChain->SetBranchAddress("trkPt", &trkPt, &b_ele_trkPt);
   fChain->SetBranchAddress("epIn", &epIn, &b_ele_epIn);
   fChain->SetBranchAddress("epOut", &epOut, &b_ele_epOut);
   fChain->SetBranchAddress("invEinvP", &invEinvP, &b_ele_invEinvP);
   fChain->SetBranchAddress("bremFrac", &bremFrac, &b_ele_bremFrac);
   fChain->SetBranchAddress("trkPInn", &trkPInn, &b_ele_trkPInn);
   fChain->SetBranchAddress("trkEtaInn", &trkEtaInn, &b_ele_trkEtaInn);
   fChain->SetBranchAddress("trkPhiInn", &trkPhiInn, &b_ele_trkPhiInn);
   fChain->SetBranchAddress("dEtaIn", &dEtaIn, &b_ele_dEtaIn);
   fChain->SetBranchAddress("dEtaInSeed", &dEtaInSeed, &b_ele_dEtaInSeed);
   fChain->SetBranchAddress("dPhiIn", &dPhiIn, &b_ele_dPhiIn);
   fChain->SetBranchAddress("hadem", &hadem, &b_ele_hadem);
   fChain->SetBranchAddress("sigmaIEtaIEta", &sigmaIEtaIEta, &b_ele_sigmaIEtaIEta);
   fChain->SetBranchAddress("e1x5Over5x5", &e1x5Over5x5, &b_ele_e1x5Over5x5);
   fChain->SetBranchAddress("e2x5Over5x5", &e2x5Over5x5, &b_ele_e2x5Over5x5);
   fChain->SetBranchAddress("e5x5", &e5x5, &b_ele_e5x5);
   fChain->SetBranchAddress("isolEm", &isolEm, &b_ele_isolEm);
   fChain->SetBranchAddress("isolHadDepth1", &isolHadDepth1, &b_ele_isolHadDepth1);
   fChain->SetBranchAddress("isolHadDepth2", &isolHadDepth2, &b_ele_isolHadDepth2);
   fChain->SetBranchAddress("isolPtTrks", &isolPtTrks, &b_ele_isolPtTrks);
   fChain->SetBranchAddress("dxy", &dxy, &b_ele_dxy);
   fChain->SetBranchAddress("nrMissHits", &nrMissHits, &b_ele_nrMissHits);
   fChain->SetBranchAddress("r9", &r9, &b_ele_r9);
   fChain->SetBranchAddress("rhoCorr", &rhoCorr, &b_ele_rhoCorr);
   fChain->SetBranchAddress("isolCharged", &isolCharged, &b_ele_isolCharged);
   fChain->SetBranchAddress("isolNeutral", &isolNeutral, &b_ele_isolNeutral);
   fChain->SetBranchAddress("isolPhoton", &isolPhoton, &b_ele_isolPhoton);
   fChain->SetBranchAddress("isolEcalClus", &isolEcalClus, &b_ele_isolEcalClus);
   fChain->SetBranchAddress("isolHcalClus", &isolHcalClus, &b_ele_isolHcalClus);
   fChain->SetBranchAddress("hademDepth1BC", &hademDepth1BC, &b_ele_hademDepth1BC);
   fChain->SetBranchAddress("hademDepth2BC", &hademDepth2BC, &b_ele_hademDepth2BC);
   fChain->SetBranchAddress("nrSatIn5x5", &nrSatIn5x5, &b_ele_nrSatIn5x5);
   fChain->SetBranchAddress("passCutPreSel", &passCutPreSel, &b_ele_passCutPreSel);
   fChain->SetBranchAddress("passPFPreSel", &passPFPreSel, &b_ele_passPFPreSel);
   fChain->SetBranchAddress("hasTrk", &hasTrk, &b_ele_hasTrk);
   fChain->SetBranchAddress("isEcalDriven", &isEcalDriven, &b_ele_isEcalDriven);
   fChain->SetBranchAddress("isTrackerDriven", &isTrackerDriven, &b_ele_isTrackerDriven);
   fChain->SetBranchAddress("cutCode", &cutCode, &b_ele_cutCode);
   fChain->SetBranchAddress("vidIds", &vidIds, &b_ele_vidIds);
   fChain->SetBranchAddress("rawNrgy", &rawNrgy, &b_ele_rawNrgy);
   fChain->SetBranchAddress("seedClusEt", &seedClusEt, &b_ele_seedClusEt);
   fChain->SetBranchAddress("seedClusEta", &seedClusEta, &b_ele_seedClusEta);
   fChain->SetBranchAddress("seedClusPhi", &seedClusPhi, &b_ele_seedClusPhi);
   fChain->SetBranchAddress("nrClus", &nrClus, &b_ele_nrClus);
   fChain->SetBranchAddress("nrCrys", &nrCrys, &b_ele_nrCrys);
   fChain->SetBranchAddress("eMax", &eMax, &b_ele_eMax);
   fChain->SetBranchAddress("e3x3", &e3x3, &b_ele_e3x3);
   fChain->SetBranchAddress("eMaxPhi", &eMaxPhi, &b_ele_eMaxPhi);
   fChain->SetBranchAddress("eMaxEta", &eMaxEta, &b_ele_eMaxEta);
   fChain->SetBranchAddress("eMaxTowerPhi", &eMaxTowerPhi, &b_ele_eMaxTowerPhi);
   fChain->SetBranchAddress("eMaxTowerEta", &eMaxTowerEta, &b_ele_eMaxTowerEta);
   fChain->SetBranchAddress("e2ndPhi", &e2ndPhi, &b_ele_e2ndPhi);
   fChain->SetBranchAddress("e2ndEta", &e2ndEta, &b_ele_e2ndEta);
   fChain->SetBranchAddress("e2ndTowerPhi", &e2ndTowerPhi, &b_ele_e2ndTowerPhi);
   fChain->SetBranchAddress("e2ndTowerEta", &e2ndTowerEta, &b_ele_e2ndTowerEta);
   fChain->SetBranchAddress("seedRegion", &seedRegion, &b_ele_seedRegion);
   fChain->SetBranchAddress("nrGain6In5x5", &nrGain6In5x5, &b_ele_nrGain6In5x5);
   fChain->SetBranchAddress("nrGain1In5x5", &nrGain1In5x5, &b_ele_nrGain1In5x5);
   fChain->SetBranchAddress("towerHadEt", &towerHadEt, &b_ele_towerHadEt);
   fChain->SetBranchAddress("towerEmEt", &towerEmEt, &b_ele_towerEmEt);
   fChain->SetBranchAddress("towerHadD1Nrgy", &towerHadD1Nrgy, &b_ele_towerHadD1Nrgy);
   fChain->SetBranchAddress("towerHadD2Nrgy", &towerHadD2Nrgy, &b_ele_towerHadD2Nrgy);
   fChain->SetBranchAddress("nrgyAlt", &nrgyAlt, &b_ele_nrgyAlt);
   fChain->SetBranchAddress("gsfNrgyAlt", &gsfNrgyAlt, &b_ele_gsfNrgyAlt);
   fChain->SetBranchAddress("phoNrgy", &phoNrgy, &b_ele_phoNrgy);
   fChain->SetBranchAddress("phoNrgyAlt", &phoNrgyAlt, &b_ele_phoNrgyAlt);
   fChain->SetBranchAddress("gain6Map", &gain6Map, &b_ele_gain6Map);
   fChain->SetBranchAddress("gain1Map", &gain1Map, &b_ele_gain1Map);
   fChain->SetBranchAddress("isolPtTrksAlt", &isolPtTrksAlt, &b_ele_isolPtTrksAlt);
   fChain->SetBranchAddress("mvaIsol", &mvaIsol, &b_ele_mvaIsol);
   fChain->SetBranchAddress("mvaNonIsol", &mvaNonIsol, &b_ele_mvaNonIsol);
   fChain->SetBranchAddress("eleTruthNrgy", &eleTruthNrgy, &b_eleTruthNrgy);
   fChain->SetBranchAddress("eleTruthPhi", &eleTruthPhi, &b_eleTruthPhi);
   fChain->SetBranchAddress("eleTruthEta", &eleTruthEta, &b_eleTruthEta);
   fChain->SetBranchAddress("eleTruthDetEta", &eleTruthDetEta, &b_eleTruthDetEta);
   fChain->SetBranchAddress("eleTruthRegion", &eleTruthRegion, &b_eleTruthRegion);
   fChain->SetBranchAddress("eleTruthEt", &eleTruthEt, &b_eleTruthEt);
   fChain->SetBranchAddress("eleTruthZ", &eleTruthZ, &b_eleTruthZ);
   fChain->SetBranchAddress("eleTruthY", &eleTruthY, &b_eleTruthY);
   fChain->SetBranchAddress("eleTruthX", &eleTruthX, &b_eleTruthX);
   fChain->SetBranchAddress("pid", &pid, &b_pid);
   fChain->SetBranchAddress("eleTrigs", eleTrigs, &b_eleTrigs);
   fChain->SetBranchAddress("evtTrigs", &evtTrigs, &b_evtTrigs);
   fChain->SetBranchAddress("hlt", &hlt_nrgy, &b_hlt);
   fChain->SetBranchAddress("egHLT", &egHLT_et, &b_egHLT);
   fChain->SetBranchAddress("egHLTUS", &egHLTUS_et, &b_egHLTUS);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("rhoAlt", &rhoAlt, &b_rhoAlt);
   Notify();
}

Bool_t test::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void test::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t test::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef test_cxx
