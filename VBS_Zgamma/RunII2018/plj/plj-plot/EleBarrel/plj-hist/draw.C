#define draw_cxx
#include "draw.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <TH1.h>
#include "L1_weight.C"

using namespace std;
void draw::Loop(TString name)
{
//   In a ROOT session, you can do:
//      root> .L draw.C
//      root> draw t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   double lep1_phi_station2_tmp = 0;
   double lep2_phi_station2_tmp = 0;
   double actualWeight=1;
   int cut0=0,cut1=0;
   TString hname="h_"+name;
   Bool_t PHOTON_barrel,PHOTON_endcap,LEPmu,LEPele,SignalRegion;
   Double_t pt[9] = {20,25,30,35,40,50,60,100,400};
   h1 = new TH1F(hname,hname,8,pt);
//   nentries=100;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      cut0++;
      if(jentry%100000==0) cout<<jentry<<"; "<<nentries<<endl;
  // if (Cut(ientry) < 0) continue;
      lep1_phi_station2_tmp = lep1_phi_station2;
      lep2_phi_station2_tmp = lep2_phi_station2;
      if(lep1_phi_station2<0) lep1_phi_station2_tmp = lep1_phi_station2+6.28319;
      if(lep2_phi_station2<0) lep2_phi_station2_tmp = lep2_phi_station2+6.28319;
      l1_weight = L1_weight(lep1_phi_station2_tmp, lep2_phi_station2_tmp, lep1_eta_station2, lep2_eta_station2);
      if(name.Contains("Ele")==1) actualWeight =1;
      else actualWeight = scalef*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*photon_id_scale;
      LEPele = lep==11 && (HLT_Ele1>0||HLT_Ele2>0) && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep < 110; 
      LEPmu =  lep == 13 && ptlep1 > 20. && ptlep2 > 20. && fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4  && nlooseeles == 0 && nloosemus < 3 && massVlep > 70. && massVlep < 110.;
      PHOTON_barrel= /*photonet<400&&*/photonet>20 &&(/*(fabs(photoneta)<2.5&&fabs(photoneta)>1.566) ||*/ (fabs(photoneta)<1.4442) ) ;
      PHOTON_endcap= /*photonet<400&&*/photonet>20 &&(fabs(photoneta)<2.5&&fabs(photoneta)>1.566);
      SignalRegion= Mjj>500 && deltaetajj>2.5 && zepp<2.4;
//      if(SignalRegion) continue;

      if( (LEPele&&PHOTON_barrel&& !SignalRegion) )
	{h1->Fill(photonet,actualWeight);   cut1++;} 
   }
   cout<<cut0<<"; "<<cut1<<endl;
}
