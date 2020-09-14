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
   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();
   TH1D* h1[373];
   char name[373];
   for(Int_t i=0;i<373;i++){
	   sprintf(name,"h1_%d",i);
	   h1[i] = new TH1D(name,name,100,60,200);
   }
   Long64_t nbytes = 0, nb = 0;
   int cutl0=0,cutp0=0,cutr0=0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      
   for(Int_t i=0;i<373;i++){
          h1[i]->Fill(photonet,pweight[i+104]);
     }
   }
   TCanvas* c1 = new TCanvas("c1","c1",900,600);  
   for(Int_t i=0;i<373;i++){
           h1[i]->SetLineColor(i);
	   h1[i]->Draw("same pe");
   }
   c1->Print("./fig.pdf");
   c1->Print("./fig.C");
}
