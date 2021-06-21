#define WWg_cxx
#include "WWg.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <fstream>
using namespace std;
void WWg::Loop(TString name)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   Long64_t npp = fChain->GetEntries("gen_weight>0.");
   Long64_t nmm = fChain->GetEntries("gen_weight<0.");
   Bool_t HLT_mm=0,HLT_ee=0,HLT_emu=0;
   Bool_t BSL=0,LEP=0,PHOTON=0;
   vector<double> ptbins_b={20,25,30,35,40,50,60,100,400};
   vector<double> ptbins_e={20,25,30,40,50,60,400};
   const int num_b=ptbins_b.size()-1;
   const int num_e=ptbins_e.size()-1;
   double scalef_fb[num_b];
   double scalef_fe[num_e];
   ifstream f1,f2;
   f1.open("../cal_weight/pljweight_mm_barrel18.txt");
   f2.open("../cal_weight/pljweight_mm_endcap18.txt");
   for(int i=0;i<num_b;i++){
       f1>>scalef_fb[i];
       cout<<scalef_fb[i]<<endl;
   }
   for(int i=0;i<num_e;i++){
       f2>>scalef_fe[i];
       cout<<scalef_fe[i]<<endl;
   }
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(name.Contains("Ele")||name.Contains("Muon")) scalef=1;
      LEP = lep1pt > 20. && lep2pt > 20. && fabs(lep1eta) < 2.5 && fabs(lep2eta) < 2.5 && (n_loose_ele+n_loose_mu)==2 ; 
      PHOTON = n_photon>0 && photonet > 20. && ( (fabs(photoneta) < 1.4442) || ( fabs(photoneta)<2.5&&fabs(photoneta)>1.566 ) ) && pass_selection1 && (photon_selection==2 || photon_selection==3 || photon_selection==4 || photon_selection ==5 ) ;
      if( !( LEP && PHOTON ) )
	      continue;
      if(photonet>400) photonet=399;
      if(fabs(photoneta)<1.4442){
	      if(photonet>20 &&  photonet<25)  {int i=0;scalef_tmp=scalef_fb[i];} 
	      if(photonet>25 &&  photonet<30)  {int i=1;scalef_tmp=scalef_fb[i];}
	      if(photonet>30 &&  photonet<35)  {int i=2;scalef_tmp=scalef_fb[i];}
	      if(photonet>35 &&  photonet<40)  {int i=3;scalef_tmp=scalef_fb[i];}
	      if(photonet>40 &&  photonet<50)  {int i=4;scalef_tmp=scalef_fb[i];}
	      if(photonet>50 &&  photonet<60)  {int i=5;scalef_tmp=scalef_fb[i];}
	      if(photonet>60 &&  photonet<100) {int i=6;scalef_tmp=scalef_fb[i];}
	      if(photonet>100)                 {int i=7;scalef_tmp=scalef_fb[i];}

      }
      else if( (fabs(photoneta)<2.5 && fabs(photoneta)>1.566) ){
	      if(photonet>20 &&  photonet<25)  {int i=0;scalef_tmp=scalef_fe[i];} 
	      if(photonet>25 &&  photonet<30)  {int i=1;scalef_tmp=scalef_fe[i];}
	      if(photonet>30 &&  photonet<40)  {int i=2;scalef_tmp=scalef_fe[i];}
	      if(photonet>40 &&  photonet<50)  {int i=3;scalef_tmp=scalef_fe[i];}
	      if(photonet>50 &&  photonet<60)  {int i=4;scalef_tmp=scalef_fe[i];}
	      if(photonet>60)                  {int i=5;scalef_tmp=scalef_fe[i];}

      }
      else scalef_tmp=0;
      if(jentry%10000==0) cout<<jentry<<" "<<nentries<<" "<<scalef_tmp<<endl;

      ExTree->Fill();
      // if (Cut(ientry) < 0) continue;
   }
}
