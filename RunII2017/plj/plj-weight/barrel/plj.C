#define plj_cxx
#include "plj.h"
#include <TH2.h>
#include <TStyle.h>
#include <iostream>
#include <TCanvas.h>
#include "L1_weight.C"
#include <fstream>
using namespace std;
void plj::Loop()
{
//   In a ROOT session, you can do:
//      root> .L plj.C
//      root> plj t
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

   ifstream f1;
//   f1.open("/home/pku/anying/cms/Uncer/2017/fakephoton/barrel/step1/pljweight_down.txt");
//   f1.open("/home/pku/anying/cms/Uncer/2017/fakephoton/barrel/step1/pljweight_up.txt");
   f1.open("/afs/cern.ch/user/y/yian/work/PKU-Cluster/RunII2017/plj/plj-plot/barrel/pljweight.txt");
   Double_t scalef_f[8];
   for(Int_t i=0;i<8;i++){
      f1>>scalef_f[i];
      cout<<"scalef_f["<<"i"<<"] = "<<scalef_f[i]<<endl;
   }
  
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
     if(jentry%1000000==0) cout<<jentry<<", "<<nentries<<endl;
     if(photonet<20)                      {scalef_tmp==0;} 
     if(photonet<25&&photonet>20)         {int i=0;scalef_tmp =scalef_f[i];}
     if(photonet>25 &&  photonet<30)      {int i=1;scalef_tmp =scalef_f[i];}
     if(photonet>30 &&  photonet<35)      {int i=2;scalef_tmp =scalef_f[i];}
     if(photonet>35 &&  photonet<40)      {int i=3;scalef_tmp =scalef_f[i];}
     if(photonet>40 &&  photonet<50)      {int i=4;scalef_tmp =scalef_f[i];}
     if(photonet>50 &&  photonet<60)      {int i=5;scalef_tmp =scalef_f[i];}
     if(photonet>60 &&  photonet<100)     {int i=6;scalef_tmp =scalef_f[i];}
     if(photonet>100/*&&  photonet<400*/) {int i=7;scalef_tmp =scalef_f[i];} 
      
      pileupWeight_tmp=1;

      lep1_phi_station2_tmp = lep1_phi_station2;
      lep2_phi_station2_tmp = lep2_phi_station2;      
      
      if(lep1_phi_station2<0) lep1_phi_station2_tmp = lep1_phi_station2+6.28319;
      if(lep2_phi_station2<0) lep2_phi_station2_tmp = lep2_phi_station2+6.28319;
      
      l1_weight = L1_weight(lep1_phi_station2_tmp, lep2_phi_station2_tmp, lep1_eta_station2, lep2_eta_station2);      
      

      ExTree->Fill();
   }
}
