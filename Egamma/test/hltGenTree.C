#define hltGenTree_cxx
#include "hltGenTree.h"
#include "TEfficiency.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include "unroll.C"
void hltGenTree::Loop(TString name)
{
   TFile* file = new TFile("test1.root","recreate");
   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();
   TH1D* hetN = new TH1D("hetN","eleTruthEt",15,0,200);
   TH1D* hetD = new TH1D("hetD","eleTruthEt",15,0,200);
   TH1D* hetaN = new TH1D("hetaN","eleTruthEta",10,0,2.5);
   TH1D* hetaD = new TH1D("hetaD","eleTruthEta",10,0,2.5);
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if( !( (fabs(eleTruthEta)<1.4442) ) ) continue;
      if(egHLT_nrgy>0) {hetN->Fill(eleTruthEt);hetaN->Fill(eleTruthEta);}
      hetD->Fill(eleTruthEt); 
      hetaD->Fill(eleTruthEta); 
    
   }
   TEfficiency* het;
   TEfficiency* heta;
   if(TEfficiency::CheckConsistency(*hetN,*hetD))
	   het =new TEfficiency(*hetN,*hetD); 
   if(TEfficiency::CheckConsistency(*hetaN,*hetaD))
	   heta =new TEfficiency(*hetaN,*hetaD); 
   het->Write();
   hetN->Write();
   hetD->Write();
   heta->Write();
   hetaN->Write();
   hetaD->Write();
   file->Close();
}
