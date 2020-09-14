#define tree_cxx
#include <iostream>
#include "tree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
using namespace std;
TH2D* tree::Loop(TString filename,Int_t i)
{
   Long64_t nentries = fChain->GetEntriesFast();
   Double_t detajj_bins[2]={0, 6.5};
   Double_t mjj_bins[2]={150,500};
//   TH2D* th2 = new TH2D(filename,"th2",3, mjj_bins, 3, detajj_bins);
   TH2D* th2 = new TH2D(Form("th2_%i",i),"th2",1, mjj_bins, 1, detajj_bins);
   th2->Sumw2();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      detajj=fabs(jet1eta-jet2eta);
      if(lep==13 && fabs(photoneta)>1.566 && fabs(photoneta)<2.5 && Mjj >150 && Mjj<500 && ZGmass>100){
	      if(i==0) actualWeight = actualWeight;
	      if(i==1) actualWeight = actualWeight/prefWeight*prefWeightUp;
	      if(i==2) actualWeight = actualWeight/prefWeight*prefWeightDown;
	      if(Mjj<500 && detajj<6.5) th2->Fill(Mjj, detajj, actualWeight);
	      if(Mjj<500 && detajj>=6.5) th2->Fill(Mjj, 6.1, actualWeight);
      }
   }
   return th2;
}
void tree::run(TString filename){
	if (fChain == 0) return;
        TFile* f1=new TFile(filename+".root","RECREATE");
        cout<<"create file"<<endl;
	TH2D* h0= Loop(filename,0);
	TH2D* h1= Loop(filename,1);
	TH2D* h2= Loop(filename,2);
        cout<<"create histogram"<<endl;
        f1->cd();
        h0->Write();
        h1->Write();
        h2->Write();
        f1->Close();
}

