#define chain_WWg_cxx
#include "chain_WWg.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
using namespace std;
void chain_WWg::Loop(TString name)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();

   Long64_t nbytes = 0, nb = 0;
   Long64_t npp = fChain->GetEntries("gen_weight>0.");
   Long64_t nmm = fChain->GetEntries("gen_weight<0.");
   Bool_t HLT_mm=0,HLT_ee=0,HLT_emu=0;
   Bool_t BSL=0,LEP=0,PHOTON=0,missET=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(name.Contains("Mu")) { scalef=1.0;}
      if(name.Contains("Ele")){ scalef=1.0;}
   
      HLT_mm = (HLT_IsoMu24) || (HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
      HLT_ee = (HLT_Ele32_WPTight_Gsf) || (HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
      HLT_emu = (HLT_Ele32_WPTight_Gsf) || (HLT_IsoMu24) || (HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL); 
      if(jentry%10000==0) cout<<jentry<<" "<<nentries<<" "<<scalef<<endl;
      BSL = (n_loose_ele+n_loose_mu)==2 && (HLT_mm || HLT_ee || HLT_emu);
      LEP = /*pass_selection>0 &&*/ lep1pt > 20. && lep2pt > 25. && fabs(lep1eta) < 2.4 && fabs(lep2eta) < 2.5 && (n_loose_ele+n_loose_mu)==2 && mll>20 && ptll>30;
      PHOTON = n_photon>0 && photonet > 20. &&( (fabs(photoneta) < 1.4442) || ( fabs(photoneta)<2.5&&fabs(photoneta)>1.566 ) );
      missET = (met>20 || puppimet>20);
      if( !(  LEP /*&& PHOTON*/ && missET ) )
	      continue;
      ExTree->Fill();
      // if (Cut(ientry) < 0) continue;
   }
}
