#define draw_cxx
#include "draw.h"
#include "TLorentzVector.h"
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
   Double_t pt[7] = {20,25,30,40,50,60,400};
   h1 = new TH1F(hname,hname,6,pt);
//   nentries=100;
   double delta_phi,ZGmass,detajj;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%100000==0) cout<<jentry<<"; "<<nentries<<endl;
      TLorentzVector Zp4, photonp4, jet1p4, jet2p4;
      Zp4.SetPtEtaPhiM(ptVlep, yVlep, phiVlep, massVlep);
      photonp4.SetPtEtaPhiE(photonet, photoneta, photonphi, photone);
      jet1p4.SetPtEtaPhiE(jet1pt, jet1eta, jet1phi, jet1e);
      jet2p4.SetPtEtaPhiE(jet2pt, jet2eta, jet2phi, jet2e);
      delta_phi=fabs((Zp4+photonp4).Phi()-(jet1p4+jet2p4).Phi());
      ZGmass=(Zp4+photonp4).M();
      detajj=fabs(jet1eta - jet2eta);
      LEPele = lep==11 &&(HLT_Ele1>0 ||  HLT_Ele2>0) && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep < 110; 
      LEPmu =  lep == 13 && /*(HLT_Mu1>0|| HLT_Mu2>0)  && */ptlep1 > 20. && ptlep2 > 20. && fabs(etalep1) < 2.4 && fabs(etalep2) < 2.4  && nlooseeles == 0 && nloosemus < 3 && massVlep > 70. && massVlep < 110.;
      PHOTON_barrel= /*photonet<400&&*/photonet>20 &&(/*(fabs(photoneta)<2.5&&fabs(photoneta)>1.566) ||*/ (fabs(photoneta)<1.4442) ) ;
      PHOTON_endcap= /*photonet<400&&*/photonet>20 &&(fabs(photoneta)<2.5&&fabs(photoneta)>1.566);
      JETS=( ( jet1pt<50 && jet1pt>30 && fabs(jet1eta)<4.7 && !(fabs(jet1eta)<3.14 && fabs(jet1eta)>2.65) ) || (jet1pt>50 && fabs(jet1eta)< 4.7 ) ) && ( (!(fabs(jet2eta)<3.14 && fabs(jet2eta)>2.65) && jet2pt<50 && jet2pt>30 && fabs(jet2eta)< 4.7 )|| ( jet2pt>50 && fabs(jet2eta)<4.7 ) );
      SignalRegion= ZGmass>100 && Mjj>500 && detajj>2.5 && zepp<2.4 && delta_phi>1.9;
      if(name.Contains("ZA"))scalef = scalef*photon_id_scale*prefWeight*pileupWeight;
      if(LEPmu&&PHOTON_endcap&&JETS&&SignalRegion){
	      cut0++;
	      continue;
      }
      if( (LEPmu&&PHOTON_endcap) )
       {  h1->Fill(photonet,scalef);   cut1++;} 
//      if(SignalRegion) continue;
   }
   cout<<"exclude signal events "<<cut0<<endl;
   cout<<"LEPmu && PHOTON_endcap "<<cut1<<endl;
}
