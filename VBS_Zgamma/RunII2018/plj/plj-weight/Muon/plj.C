#define plj_cxx
#include "plj.h"
#include <TH2.h>
#include <TStyle.h>
#include <iostream>
#include <TCanvas.h>
#include <fstream>
using namespace std;
void plj::Loop(TString flag)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   ifstream f1,f2,f3,f4;
   f1.open("/home/pku/anying/cms/PKU-Cluster/FakePhoton/txt/pljweight"+flag+"_mubarrel18.txt");
   f2.open("/home/pku/anying/cms/PKU-Cluster/FakePhoton/txt/pljweight"+flag+"_muendcap18.txt");
   f3.open("/home/pku/anying/cms/PKU-Cluster/FakePhoton/txt/pljweight"+flag+"_elebarrel18.txt");
   f4.open("/home/pku/anying/cms/PKU-Cluster/FakePhoton/txt/pljweight"+flag+"_eleendcap18.txt");
   Double_t scalef_f1[8];
   Double_t scalef_f2[8];
   Double_t scalef_f3[8];
   Double_t scalef_f4[8];
   for(Int_t i=0;i<8;i++){
      f1>>scalef_f1[i];
      f2>>scalef_f2[i];
//    f3>>scalef_f3[i];
//    f4>>scalef_f4[i];
      scalef_f3[i]=0;
      scalef_f4[i]=0;
      cout<<"scalef_f1["<<i<<"] = "<<scalef_f1[i]<<endl;
      cout<<"scalef_f2["<<i<<"] = "<<scalef_f2[i]<<endl;
      cout<<"scalef_f3["<<i<<"] = "<<scalef_f3[i]<<endl;
      cout<<"scalef_f4["<<i<<"] = "<<scalef_f4[i]<<endl;
   }
   f1.close();
   f2.close(); 
   f3.close();
   f4.close(); 
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%1000000==0) cout<<jentry<<", "<<nentries<<endl;
     
      if(lep==13 && fabs(photoneta)<1.4442){
	      if(photonet>20 &&  photonet<25)      {int i=0;scalef_tmp = scalef_f1[i];}
	      if(photonet>25 &&  photonet<30)      {int i=1;scalef_tmp = scalef_f1[i];}
	      if(photonet>30 &&  photonet<35)      {int i=2;scalef_tmp = scalef_f1[i];}
	      if(photonet>35 &&  photonet<40)      {int i=3;scalef_tmp = scalef_f1[i];}
	      if(photonet>40 &&  photonet<50)      {int i=4;scalef_tmp = scalef_f1[i];}
	      if(photonet>50 &&  photonet<60)      {int i=5;scalef_tmp = scalef_f1[i];}
	      if(photonet>60 &&  photonet<100)     {int i=6;scalef_tmp = scalef_f1[i];}
	      if(photonet>100)                     {int i=7;scalef_tmp = scalef_f1[i];}
      }

      if(lep==13 && fabs(photoneta)>1.566 && fabs(photoneta)<2.5){
	      if(photonet>20 &&  photonet<25)      {int i=0;scalef_tmp = scalef_f2[i];}
	      if(photonet>25 &&  photonet<30)      {int i=1;scalef_tmp = scalef_f2[i];}
	      if(photonet>30 &&  photonet<40)      {int i=2;scalef_tmp = scalef_f2[i];}
	      if(photonet>40 &&  photonet<50)      {int i=3;scalef_tmp = scalef_f2[i];}
	      if(photonet>50 &&  photonet<60)      {int i=4;scalef_tmp = scalef_f2[i];}
	      if(photonet>60/*&&  photonet<400*/)  {int i=5;scalef_tmp = scalef_f2[i];}
      }
      
      if(lep==11 && fabs(photoneta)<1.4442){
	      if(photonet>20 &&  photonet<25)      {int i=0;scalef_tmp = scalef_f3[i];}
	      if(photonet>25 &&  photonet<30)      {int i=1;scalef_tmp = scalef_f3[i];}
	      if(photonet>30 &&  photonet<35)      {int i=2;scalef_tmp = scalef_f3[i];}
	      if(photonet>35 &&  photonet<40)      {int i=3;scalef_tmp = scalef_f3[i];}
	      if(photonet>40 &&  photonet<50)      {int i=4;scalef_tmp = scalef_f3[i];}
	      if(photonet>50 &&  photonet<60)      {int i=5;scalef_tmp = scalef_f3[i];}
	      if(photonet>60 &&  photonet<100)     {int i=6;scalef_tmp = scalef_f3[i];}
	      if(photonet>100)                     {int i=7;scalef_tmp = scalef_f3[i];}
      }

      if(lep==11 && fabs(photoneta)>1.566 && fabs(photoneta)<2.5){
	      if(photonet>20 &&  photonet<25)      {int i=0;scalef_tmp = scalef_f4[i];}
	      if(photonet>25 &&  photonet<30)      {int i=1;scalef_tmp = scalef_f4[i];}
	      if(photonet>30 &&  photonet<40)      {int i=2;scalef_tmp = scalef_f4[i];}
	      if(photonet>40 &&  photonet<50)      {int i=3;scalef_tmp = scalef_f4[i];}
	      if(photonet>50 &&  photonet<60)      {int i=4;scalef_tmp = scalef_f4[i];}
	      if(photonet>60/*&&  photonet<400*/)  {int i=5;scalef_tmp = scalef_f4[i];}
      }

      pileupWeight_tmp=1;

      ExTree->Fill();
   }
}
