#define small_cxx
#include "small.h"
#include <iostream>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
using namespace std;
void small::Loop(TString name)
{
//   In a ROOT session, you can do:
//      Root > .L small.C
//      Root > small t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   TH2D* h_up[30];
   TH2D* h_down[30];
   Double_t mjj_bins[4]={500, 800, 1200,2000};
   Double_t detajj_bins[4]={2.5,4.5,6,6.5};
   TH2D*h=new TH2D("h","hist",3,mjj_bins,3,detajj_bins);
   for(int i=0;i<30;i++){
      h_up[i]=new TH2D(Form("hist_up_%i",i),"hist",3,mjj_bins,3,detajj_bins);
      h_down[i]=new TH2D(Form("hist_down_%i",i),"hist",3,mjj_bins,3,detajj_bins);
   }
   Bool_t JET_up;
   Bool_t JET_down;
   Bool_t JET;
   TFile*file=new TFile("hist1_"+name,"RECREATE");
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
//   for (Long64_t jentry=0; jentry<1000;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      scalef = 1000.*47.46/(np-nm)*theWeight/fabs(theWeight);
      if(jentry%10000==0) cout<<"scalef "<<scalef<<endl;
      JET=jet1pt_new>30 && jet2pt_new>30 && fabs(jet1eta_new)<4.7 && fabs(jet2eta)<4.7&&Mjj_new>500&&deltaeta_new>2.5 && drj1a_new>0.5 && drj1l_new>0.5 && drj2l_new>0.5 && drj1l2_new>0.5 && drj2l2_new>0.5;
      for(int i=0;i<jet1pt_unc_up->size();i++){
          JET_up=jet1pt_unc_up->at(i)>30 && jet2pt_unc_up->at(i)>30 && fabs(jet1eta_unc_up->at(i))<4.7 && fabs(jet2eta_unc_up->at(i))<4.7 && drj1a_up->at(i)>0.5 && drj1l1_up->at(i)>0.5 && drj1l2_up->at(i)>0 && drj2l1_up->at(i)>0 && drj2l2_up->at(i)>0.5 && drjj_up->at(i)>0.5 && detajj_up->at(i)>2.5 && Mjj_up->at(i)>500;
          JET_down=jet1pt_unc_down->at(i)>30 && jet2pt_unc_down->at(i)>30 && fabs(jet1eta_unc_down->at(i))<4.7 && fabs(jet2eta_unc_down->at(i))<4.7 && drj1a_down->at(i)>0.5 && drj1l1_down->at(i)>0.5 && drj1l2_down->at(i)>0 && drj2l1_down->at(i)>0 && drj2l2_down->at(i)>0.5 && drjj_down->at(i)>0.5 && detajj_down->at(i)>2.5 && Mjj_down->at(i)>500;      
          if(Mjj_up->at(i)>2000) Mjj_up->at(i)=1999;   if(Mjj_down->at(i)>2000) Mjj_down->at(i)=1999;
          if(detajj_up->at(i)>6.5) detajj_up->at(i)=6.1;   if(detajj_down->at(i)>6.5) detajj_down->at(i)=6.1;
//          if(jentry%100==0)cout<<"Fill histograms"<<endl;
          if(JET_up){
               h_up[i]->Fill(Mjj_up->at(i),detajj_up->at(i),scalef);
	  }
          if(JET_down){
               h_down[i]->Fill(Mjj_down->at(i),detajj_down->at(i),scalef);
	  }
      }   
      if(Mjj_new>2000) Mjj_new=1999;
      if(deltaeta_new>6.5) deltaeta_new=6.1;
      if(JET) {h->Fill(Mjj_new,deltaeta_new,scalef);}
      if(jentry%10000==0)cout<<"finish the vector loop"<<endl;
   }
  cout<<"end the big loop"<<endl; 
  file->cd();
  for(int i=0;i<30;i++){
	  h_up[i]->Write();
  }
  for(int i=0;i<30;i++){
	  h_down[i]->Write();
  }
  h->Write();
  file->Close();
}
