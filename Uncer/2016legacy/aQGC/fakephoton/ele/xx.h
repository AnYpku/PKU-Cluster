//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jan  8 13:32:56 2020 by ROOT version 5.34/38
// from TTree outtree/outtree
// found on file: optimal_2016aqgc_ZA-EWK.root
//////////////////////////////////////////////////////////

#ifndef xx_h
#define xx_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
using namespace std;
// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class xx {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Double_t        scalef;
   Double_t        actualWeight;
   Int_t           nVtx;
   Double_t        theWeight;
   Double_t        lumiWeight;
   Double_t        pileupWeight;
   Int_t           HLT_Ele1;
   Int_t           HLT_Ele2;
   Int_t           HLT_Ele3;
   Int_t           HLT_Ele4;
   Int_t           HLT_Ele5;
   Int_t           HLT_Mu1;
   Int_t           HLT_Mu2;
   Int_t           HLT_Mu3;
   Int_t           HLT_Mu4;
   Int_t           HLT_Mu5;
   Double_t        nump;
   Double_t        numm;
   Double_t        npT;
   Int_t           lep;
   Int_t           run_period;
   Double_t        ptVlep;
   Double_t        yVlep;
   Double_t        phiVlep;
   Double_t        massVlep;
   Double_t        Mva;
   Double_t        ptlep1;
   Double_t        etalep1;
   Double_t        philep1;
   Double_t        ptlep2;
   Double_t        etalep2;
   Double_t        philep2;
   Double_t        drla;
   Double_t        drla2;
   Double_t        drj1a;
   Double_t        drj2a;
   Double_t        drj1l;
   Double_t        drj2l;
   Double_t        drj1l2;
   Double_t        drj2l2;
   Int_t           nlooseeles;
   Int_t           nloosemus;
   Double_t        MET_et;
   Double_t        photonet;
   Double_t        photoneta;
   Double_t        photonphi;
   Double_t        photone;
   Double_t        photonsieie;
   Double_t        photonphoiso;
   Double_t        photonchiso;
   Double_t        photonnhiso;
   Int_t           isprompt;
   Double_t        jet1pt;
   Double_t        jet1eta;
   Double_t        jet1phi;
   Double_t        jet1e;
   Double_t        jet2pt;
   Double_t        jet2eta;
   Double_t        jet2phi;
   Double_t        jet2e;
   Double_t        Mjj;
   Double_t        zepp;
   Double_t        deltaetajj;
   Double_t        delta_phi;
   Double_t        drjj;
   Double_t        ele1_id_scale;
   Double_t        ele2_id_scale;
   Double_t        ele1_reco_scale;
   Double_t        ele2_reco_scale;
   Double_t        photon_id_scale;
   Int_t           lep1_sign;
   Int_t           lep2_sign;
   Int_t           muon1_trackerLayers;
   Int_t           muon2_trackerLayers;
   Double_t        matchedgenMu1_pt;
   Double_t        matchedgenMu2_pt;
   Double_t        muon1_id_scale;
   Double_t        muon2_id_scale;
   Double_t        muon1_iso_scale;
   Double_t        muon2_iso_scale;
   Double_t        muon1_track_scale;
   Double_t        muon2_track_scale;
   Double_t        muon_hlt_scale;
   Double_t        ele_hlt_scale;
   Double_t        muon1_rochester;
   Double_t        muon2_rochester;
   Double_t        drll;

   // List of branches
   TBranch        *b_scalef;   //!
   TBranch        *b_actualWeight;   //!
   TBranch        *b_nVtx;   //!
   TBranch        *b_theWeight;   //!
   TBranch        *b_lumiWeight;   //!
   TBranch        *b_pileupWeight;   //!
   TBranch        *b_HLT_Ele1;   //!
   TBranch        *b_HLT_Ele2;   //!
   TBranch        *b_HLT_Ele3;   //!
   TBranch        *b_HLT_Ele4;   //!
   TBranch        *b_HLT_Ele5;   //!
   TBranch        *b_HLT_Mu1;   //!
   TBranch        *b_HLT_Mu2;   //!
   TBranch        *b_HLT_Mu3;   //!
   TBranch        *b_HLT_Mu4;   //!
   TBranch        *b_HLT_Mu5;   //!
   TBranch        *b_nump;   //!
   TBranch        *b_numm;   //!
   TBranch        *b_npT;   //!
   TBranch        *b_lep;   //!
   TBranch        *b_run_period;   //!
   TBranch        *b_ptVlep;   //!
   TBranch        *b_yVlep;   //!
   TBranch        *b_phiVlep;   //!
   TBranch        *b_massVlep;   //!
   TBranch        *b_Mva;   //!
   TBranch        *b_ptlep1;   //!
   TBranch        *b_etalep1;   //!
   TBranch        *b_philep1;   //!
   TBranch        *b_ptlep2;   //!
   TBranch        *b_etalep2;   //!
   TBranch        *b_philep2;   //!
   TBranch        *b_drla;   //!
   TBranch        *b_drla2;   //!
   TBranch        *b_drj1a;   //!
   TBranch        *b_drj2a;   //!
   TBranch        *b_drj1l;   //!
   TBranch        *b_drj2l;   //!
   TBranch        *b_drj1l2;   //!
   TBranch        *b_drj2l2;   //!
   TBranch        *b_nlooseeles;   //!
   TBranch        *b_nloosemus;   //!
   TBranch        *b_MET_et;   //!
   TBranch        *b_photonet;   //!
   TBranch        *b_photoneta;   //!
   TBranch        *b_photonphi;   //!
   TBranch        *b_photone;   //!
   TBranch        *b_photonsieie;   //!
   TBranch        *b_photonphoiso;   //!
   TBranch        *b_photonchiso;   //!
   TBranch        *b_photonnhiso;   //!
   TBranch        *b_isprompt;   //!
   TBranch        *b_jet1pt;   //!
   TBranch        *b_jet1eta;   //!
   TBranch        *b_jet1phi;   //!
   TBranch        *b_jet1e;   //!
   TBranch        *b_jet2pt;   //!
   TBranch        *b_jet2eta;   //!
   TBranch        *b_jet2phi;   //!
   TBranch        *b_jet2e;   //!
   TBranch        *b_Mjj;   //!
   TBranch        *b_zepp;   //!
   TBranch        *b_deltaetajj;   //!
   TBranch        *b_delta_phi;   //!
   TBranch        *b_drjj;   //!
   TBranch        *b_ele1_id_scale;   //!
   TBranch        *b_ele2_id_scale;   //!
   TBranch        *b_ele1_reco_scale;   //!
   TBranch        *b_ele2_reco_scale;   //!
   TBranch        *b_photon_id_scale;   //!
   TBranch        *b_lep1_sign;   //!
   TBranch        *b_lep2_sign;   //!
   TBranch        *b_muon1_trackerLayers;   //!
   TBranch        *b_muon2_trackerLayers;   //!
   TBranch        *b_matchedgenMu1_pt;   //!
   TBranch        *b_matchedgenMu2_pt;   //!
   TBranch        *b_muon1_id_scale;   //!
   TBranch        *b_muon2_id_scale;   //!
   TBranch        *b_muon1_iso_scale;   //!
   TBranch        *b_muon2_iso_scale;   //!
   TBranch        *b_muon1_track_scale;   //!
   TBranch        *b_muon2_track_scale;   //!
   TBranch        *b_muon_hlt_scale;   //!
   TBranch        *b_ele_hlt_scale;   //!
   TBranch        *b_muon1_rochester;   //!
   TBranch        *b_muon2_rochester;   //!
   TBranch        *b_drll;   //!

   xx(TTree *tree=0);
   virtual ~xx();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(TString name);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef xx_cxx
xx::xx(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("optimal_2016aqgc_ZA-EWK.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("optimal_2016aqgc_ZA-EWK.root");
      }
      f->GetObject("outtree",tree);

   }
   Init(tree);
}

xx::~xx()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t xx::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t xx::LoadTree(Long64_t entry)
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

void xx::Init(TTree *tree)
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

   fChain->SetBranchAddress("scalef", &scalef, &b_scalef);
//   fChain->SetBranchAddress("actualWeight", &actualWeight, &b_actualWeight);
   fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
   fChain->SetBranchAddress("theWeight", &theWeight, &b_theWeight);
   fChain->SetBranchAddress("lumiWeight", &lumiWeight, &b_lumiWeight);
   fChain->SetBranchAddress("pileupWeight", &pileupWeight, &b_pileupWeight);
   fChain->SetBranchAddress("HLT_Ele1", &HLT_Ele1, &b_HLT_Ele1);
   fChain->SetBranchAddress("HLT_Ele2", &HLT_Ele2, &b_HLT_Ele2);
   fChain->SetBranchAddress("HLT_Ele3", &HLT_Ele3, &b_HLT_Ele3);
   fChain->SetBranchAddress("HLT_Ele4", &HLT_Ele4, &b_HLT_Ele4);
   fChain->SetBranchAddress("HLT_Ele5", &HLT_Ele5, &b_HLT_Ele5);
   fChain->SetBranchAddress("HLT_Mu1", &HLT_Mu1, &b_HLT_Mu1);
   fChain->SetBranchAddress("HLT_Mu2", &HLT_Mu2, &b_HLT_Mu2);
   fChain->SetBranchAddress("HLT_Mu3", &HLT_Mu3, &b_HLT_Mu3);
   fChain->SetBranchAddress("HLT_Mu4", &HLT_Mu4, &b_HLT_Mu4);
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
   fChain->SetBranchAddress("Mva", &Mva, &b_Mva);
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
   fChain->SetBranchAddress("jet1phi", &jet1phi, &b_jet1phi);
   fChain->SetBranchAddress("jet1e", &jet1e, &b_jet1e);
   fChain->SetBranchAddress("jet2pt", &jet2pt, &b_jet2pt);
   fChain->SetBranchAddress("jet2eta", &jet2eta, &b_jet2eta);
   fChain->SetBranchAddress("jet2phi", &jet2phi, &b_jet2phi);
   fChain->SetBranchAddress("jet2e", &jet2e, &b_jet2e);
   fChain->SetBranchAddress("Mjj", &Mjj, &b_Mjj);
   fChain->SetBranchAddress("zepp", &zepp, &b_zepp);
   fChain->SetBranchAddress("deltaetajj", &deltaetajj, &b_deltaetajj);
   fChain->SetBranchAddress("delta_phi", &delta_phi, &b_delta_phi);
   fChain->SetBranchAddress("drjj", &drjj, &b_drjj);
   fChain->SetBranchAddress("ele1_id_scale", &ele1_id_scale, &b_ele1_id_scale);
   fChain->SetBranchAddress("ele2_id_scale", &ele2_id_scale, &b_ele2_id_scale);
   fChain->SetBranchAddress("ele1_reco_scale", &ele1_reco_scale, &b_ele1_reco_scale);
   fChain->SetBranchAddress("ele2_reco_scale", &ele2_reco_scale, &b_ele2_reco_scale);
   fChain->SetBranchAddress("photon_id_scale", &photon_id_scale, &b_photon_id_scale);
   fChain->SetBranchAddress("lep1_sign", &lep1_sign, &b_lep1_sign);
   fChain->SetBranchAddress("lep2_sign", &lep2_sign, &b_lep2_sign);
   fChain->SetBranchAddress("muon1_trackerLayers", &muon1_trackerLayers, &b_muon1_trackerLayers);
   fChain->SetBranchAddress("muon2_trackerLayers", &muon2_trackerLayers, &b_muon2_trackerLayers);
   fChain->SetBranchAddress("matchedgenMu1_pt", &matchedgenMu1_pt, &b_matchedgenMu1_pt);
   fChain->SetBranchAddress("matchedgenMu2_pt", &matchedgenMu2_pt, &b_matchedgenMu2_pt);
   fChain->SetBranchAddress("muon1_id_scale", &muon1_id_scale, &b_muon1_id_scale);
   fChain->SetBranchAddress("muon2_id_scale", &muon2_id_scale, &b_muon2_id_scale);
   fChain->SetBranchAddress("muon1_iso_scale", &muon1_iso_scale, &b_muon1_iso_scale);
   fChain->SetBranchAddress("muon2_iso_scale", &muon2_iso_scale, &b_muon2_iso_scale);
   fChain->SetBranchAddress("muon1_track_scale", &muon1_track_scale, &b_muon1_track_scale);
   fChain->SetBranchAddress("muon2_track_scale", &muon2_track_scale, &b_muon2_track_scale);
   fChain->SetBranchAddress("muon_hlt_scale", &muon_hlt_scale, &b_muon_hlt_scale);
   fChain->SetBranchAddress("ele_hlt_scale", &ele_hlt_scale, &b_ele_hlt_scale);
   fChain->SetBranchAddress("muon1_rochester", &muon1_rochester, &b_muon1_rochester);
   fChain->SetBranchAddress("muon2_rochester", &muon2_rochester, &b_muon2_rochester);
   fChain->SetBranchAddress("drll", &drll, &b_drll);
   Notify();
}

Bool_t xx::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void xx::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t xx::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef xx_cxx
