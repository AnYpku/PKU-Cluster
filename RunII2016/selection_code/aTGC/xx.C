#define xx_cxx
#include "L1_weight.C"
#include "xx.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>

using namespace std;
void xx::Loop()
{
//   In a ROOT session, you can do:
//      root> .L xx.C
//      root> xx t
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


   double lep1_phi_station2_tmp = 0;
   double lep2_phi_station2_tmp = 0;

   TH1D* h1 = new TH1D("h1","h1",100,60,200);
   cut0=0,cut1=0;
   bool LEP,JET,PHOTON,SignalRegion,DR;
//  nentries=1000;
   Long64_t nbytes = 0, nb = 0;
   int cutl0=0,cutp0=0,cutr0=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      lep1_phi_station2_tmp = lep1_phi_station2;
      lep2_phi_station2_tmp = lep2_phi_station2;      
     
      cut0++;//total events, cut0=t1->GetEntries()
      

      if(lep1_phi_station2<0) lep1_phi_station2_tmp = lep1_phi_station2+6.28319;
      if(lep2_phi_station2<0) lep2_phi_station2_tmp = lep2_phi_station2+6.28319;

      l1_weight = L1_weight(lep1_phi_station2_tmp, lep2_phi_station2_tmp, lep1_eta_station2, lep2_eta_station2);      
      if(drla==10) drla=0;
      if(drla2==10) drla2=0; 
      if(drj1a==10) drj1a=-1;
      if(drj2a==10) drj2a=-1;

      LEP = lep == 13 && (ptlep1 > 20. && fabs(etalep1) < 2.4) || (ptlep2 > 20.  && fabs(etalep2) < 2.4) && nlooseeles == 0 && nloosemus < 3;// && massVlep > 20. && massVlep < 200.;
//      SignalRegion= Mjj>500 && deltaetajj>2.5 && zepp<1.8;
      PHOTON= photonet>25 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) );
//      JET=jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7;
      DR =drla>0.7 && drla2>0.7; //&& drj1a>0.5 && drj2a>0.5;
      if(LEP)    cutl0++;
      if(PHOTON) cutp0++;
      if(DR)     cutr0++;
      if((LEP)==true)
         {
             cut1++;//how many events passing the selection 
             h1->Fill(photonet,pweight[476]);
             newtree->Fill(); //fill the brach when this entry pass the both selection
//                 cout<<"jentry = "<<jentry<<"; cut1 = "<<cut1<<endl;
         }

    }
     h1->Draw();
     cout<<"lep cut "<<cutl0<<endl;
     cout<<"photon cut "<<cutp0<<endl;
     cout<<"dr cut "<<cutr0<<endl;
}
