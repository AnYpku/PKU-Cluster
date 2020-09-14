#define xx_cxx
#include "xx.h"
#include <TH2.h>
#include "ele_channel_scale.C"
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

using namespace std;
void xx::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   bool LEPmu,LEPele,JET,PHOTON,SignalRegion,DR;
//  nentries=1000;
   Long64_t nbytes = 0, nb = 0;
   TFile* Reco_egamma= TFile::Open("./ele_SFs/EGM2D_BtoH_GT20GeV_RecoSF_Legacy2016.root");
   TH2F* Reco=0;
   Reco_egamma->GetObject("EGamma_SF2D", Reco);
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
     
      cut0++;//total events, cut0=t1->GetEntries()
      if(drla==10) drla=0;
      if(drla2==10) drla2=0; 
      if(drj1a==10) drj1a=-1;
      if(drj2a==10) drj2a=-1;
      if(jentry%1000000==0)   cout<<jentry<<"; "<<nentries<<endl;
      if(lep==11){
	      ele1_reco_scale=get_ele_Reco(etalep1, ptlep1,Reco);
	      ele2_reco_scale=get_ele_Reco(etalep2, ptlep2,Reco);
      }

      newtree->Fill();
   }
   Reco_egamma->Close();
}
