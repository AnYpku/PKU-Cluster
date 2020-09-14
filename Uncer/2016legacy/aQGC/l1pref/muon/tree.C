#define tree_cxx
#include <iostream>
#include "tree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
using namespace std;
TH1D* tree::Loop(TString filename,Int_t i)
{
   Long64_t nentries = fChain->GetEntriesFast();
   double ZGammabins[7]={150,300,450,600,750,1000,2e4};
   TH1D* th2 = new TH1D(Form("th2_%i",i),"th2",6,ZGammabins);
   th2->Sumw2();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      detajj=fabs(jet1eta-jet2eta);
      if(lep==13 && photonet>100 && Mjj >500 && detajj>2.5){
	      if(i==0) actualWeight = actualWeight;
	      if(i==1) actualWeight = actualWeight/prefWeight*prefWeightUp;
	      if(i==2) actualWeight = actualWeight/prefWeight*prefWeightDown;
	      if(ZGmass>2000) ZGmass=1999;
	      th2->Fill(ZGmass, actualWeight);
      }
   }
   return th2;
}
void tree::run(TString filename){
	if (fChain == 0) return;
        TFile* f1=new TFile(filename+".root","RECREATE");
        cout<<"create file"<<endl;
	TH1D* h0= Loop(filename,0);
	TH1D* h1= Loop(filename,1);
	TH1D* h2= Loop(filename,2);
        cout<<"create histogram"<<endl;
        f1->cd();
        h0->Write();
        h1->Write();
        h2->Write();
        f1->Close();
}

