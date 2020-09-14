#define plj_cxx
#include "plj.h"
#include <TH2.h>
#include <TStyle.h>
#include <iostream>
#include <TCanvas.h>
#include "L1_weight.C"
#include <fstream>
using namespace std;
void plj::Loop(TString name)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   double lep1_phi_station2_tmp = 0;
   double lep2_phi_station2_tmp = 0;

   ifstream f1,f2;
   f1.open("/afs/cern.ch/user/y/yian/work/PKU-Cluster/Uncer/2016legacy/fakephoton/elebarrel/step1/pljweight"+name+".txt");
   f2.open("/afs/cern.ch/user/y/yian/work/PKU-Cluster/Uncer/2016legacy/fakephoton/eleendcap/step1/pljweight"+name+".txt");
   Double_t scalef_f1[8];
   Double_t scalef_f2[8];
   for(Int_t i=0;i<8;i++){
      f1>>scalef_f1[i];
      f2>>scalef_f2[i];
      cout<<"scalef_f1["<<i<<"] = "<<scalef_f1[i]<<endl;
      cout<<"scalef_f2["<<i<<"] = "<<scalef_f2[i]<<endl;
   }
   f1.close();
   f2.close(); 
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%1000000==0) cout<<jentry<<", "<<nentries<<endl;
     
      if(lep==11 && fabs(photoneta)<1.4442){
	      if(photonet>20 &&  photonet<25)      {int i=0;scalef_tmp = scalef_f1[i];}
	      if(photonet>25 &&  photonet<30)      {int i=1;scalef_tmp = scalef_f1[i];}
	      if(photonet>30 &&  photonet<35)      {int i=2;scalef_tmp = scalef_f1[i];}
	      if(photonet>35 &&  photonet<40)      {int i=3;scalef_tmp = scalef_f1[i];}
	      if(photonet>40 &&  photonet<50)      {int i=4;scalef_tmp = scalef_f1[i];}
	      if(photonet>50 &&  photonet<60)      {int i=5;scalef_tmp = scalef_f1[i];}
	      if(photonet>60 &&  photonet<100)     {int i=6;scalef_tmp = scalef_f1[i];}
	      if(photonet>100)                     {int i=7;scalef_tmp = scalef_f1[i];}
      }

      if(lep==11 && fabs(photoneta)>1.566 && fabs(photoneta)<2.5){
	      if(photonet>20 &&  photonet<25)      {int i=0;scalef_tmp = scalef_f2[i];}
	      if(photonet>25 &&  photonet<30)      {int i=1;scalef_tmp = scalef_f2[i];}
	      if(photonet>30 &&  photonet<40)      {int i=2;scalef_tmp = scalef_f2[i];}
	      if(photonet>40 &&  photonet<50)      {int i=3;scalef_tmp = scalef_f2[i];}
	      if(photonet>50 &&  photonet<60)      {int i=4;scalef_tmp = scalef_f2[i];}
	      if(photonet>60/*&&  photonet<400*/)  {int i=5;scalef_tmp = scalef_f2[i];}
      }
      
      pileupWeight_tmp=1;

      lep1_phi_station2_tmp = lep1_phi_station2;
      lep2_phi_station2_tmp = lep2_phi_station2;      
      
      if(lep1_phi_station2<0) lep1_phi_station2_tmp = lep1_phi_station2+6.28319;
      if(lep2_phi_station2<0) lep2_phi_station2_tmp = lep2_phi_station2+6.28319;
      
//      l1_weight = L1_weight(lep1_phi_station2_tmp, lep2_phi_station2_tmp, lep1_eta_station2, lep2_eta_station2);      
      

      ExTree->Fill();
   }
}
