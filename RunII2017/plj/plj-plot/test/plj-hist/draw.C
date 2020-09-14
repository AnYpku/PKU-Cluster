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
   int ijet,cut0=0,cut1=0;
   TString hname="h_"+name;
   Bool_t PHOTON_barrel,PHOTON_endcap,LEPmu,LEPele,SignalRegion,JETS,JET[6];
//   Double_t pt[11]={20,25,30,35,40,45,50,60,80,120,400};
   Double_t pt[8] = {20,25,30,35,50,60,100,400};
   h1 = new TH1F(hname,hname,7,pt);
//   nentries=100;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%100000==0) cout<<jentry<<"; "<<nentries<<endl;
  // if (Cut(ientry) < 0) continue;
      lep1_phi_station2_tmp = lep1_phi_station2;
      lep2_phi_station2_tmp = lep2_phi_station2;
      if(lep1_phi_station2<0) lep1_phi_station2_tmp = lep1_phi_station2+6.28319;
      if(lep2_phi_station2<0) lep2_phi_station2_tmp = lep2_phi_station2+6.28319;
      l1_weight = L1_weight(lep1_phi_station2_tmp, lep2_phi_station2_tmp, lep1_eta_station2, lep2_eta_station2);
      LEPele = lep==11 &&(HLT_Ele1>0 ||  HLT_Ele2>0) && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep < 110; 
      LEPmu =  lep == 13 && /*(HLT_Mu1>0|| HLT_Mu2>0)  && */ptlep1 > 20. && ptlep2 > 20. && fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4  && nlooseeles == 0 && nloosemus < 3 && massVlep > 70. && massVlep < 110.;
      PHOTON_barrel= /*photonet<400&&*/photonet>20 &&(/*(fabs(photoneta)<2.5&&fabs(photoneta)>1.566) ||*/ (fabs(photoneta)<1.4442) ) ;
      PHOTON_endcap= /*photonet<400&&*/photonet>20 &&(fabs(photoneta)<2.5&&fabs(photoneta)>1.566);
      JETS=jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7;
      if(name.Contains("ZA"))scalef = scalef*muon1_id_scale*muon2_id_scale*muon2_iso_scale*muon1_iso_scale*muon1_track_scale*muon2_track_scale*photon_id_scale*prefWeight;
      ijet=0;
      for(Int_t j=0;j<6;j++)
      {
       JET[j]=ak4jet_pt[j]>30 && fabs(ak4jet_eta[j])<4.7;
       if(JET[j])        ijet++;
      }
      SignalRegion= Mjj>500 && deltaetajj>2.5 && zepp<2.4;
      if(SignalRegion) continue;
      //if(LEPmu&&PHOTON_barrel&&(ijet>1)&&!SignalRegion )
      //if(LEPmu&&PHOTON_barrel)
      if(LEPmu&&PHOTON_endcap==true)
      //if(LEPele&&PHOTON_barrel==true)
      //if(LEPele&&PHOTON_endcap==true)
       {  h1->Fill(photonet,scalef);   cut1++;} 
   }
   cout<<"LEPmu && PHOTON_endcap "<<cut1<<endl;
}
