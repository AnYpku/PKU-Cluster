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
   vector<double> ptbins={20,30,40,50,80,400};
   const int num=ptbins.size()-1;
   double scalef_f[num];
   ifstream f1;
   f1.open("../cal_weight/pljweight_em_barrel.txt");
   for(int i=0;i<num;i++){
       f1>>scalef_f[i];
       cout<<scalef_f[i]<<endl;
   }
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(name.Contains("Ele")||name.Contains("Muon")) scalef=1;
      if(jentry%10000==0) cout<<jentry<<" "<<nentries<<" "<<scalef<<endl;
      LEP = lep1pt > 20. && lep2pt > 20. && fabs(lep1eta) < 2.5 && fabs(lep2eta) < 2.5 && (n_loose_ele+n_loose_mu)==2 ; 
      PHOTON = n_photon>0 && photonet > 20. && ( (fabs(photoneta) < 1.4442) || ( fabs(photoneta)<2.5&&fabs(photoneta)>1.566 ) ) && pass_selection1 && (photon_selection==2 || photon_selection==3 || photon_selection==4 || photon_selection ==5 ) ;
      if( !( LEP && PHOTON ) )
	      continue;
      if(photonet>400) photonet=399;
      if(fabs(photoneta)<1.4442){
	      if(photonet>20 &&  photonet<30)  {int i=0;scalef_tmp=scalef_f[i];} 
	      if(photonet>30 &&  photonet<40)  {int i=1;scalef_tmp=scalef_f[i];}
	      if(photonet>40 &&  photonet<50)  {int i=2;scalef_tmp=scalef_f[i];}
	      if(photonet>50 &&  photonet<80)  {int i=3;scalef_tmp=scalef_f[i];}
	      if(photonet>80)                  {int i=4;scalef_tmp=scalef_f[i];}
		      
      }
      else scalef_tmp=0;
      
      ExTree->Fill();
      // if (Cut(ientry) < 0) continue;
   }
}
