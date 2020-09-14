#define hsito_cxx
#include "hsito.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#define ptnumber 7

void hsito::Loop()
{
   if (fChain == 0) return;
   Double_t lowpt[ptnumber] ={20,25,30,40,50,65,0};
   Double_t highpt[ptnumber]={25,30,40,50,65,400,400};
   Bool_t LEP;
   TH1D* h1[ptnumber]; 
   TCanvas*c1[ptnumber];
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   for(int i =0;i<ptnumber;i++){
   h1[i] = new TH1D(Form("h1_%i",i+1),Form("pt%0.f_%0.f",lowpt[i],highpt[i]),100,lowpt[i],highpt[i]);
   c1[i] = new TCanvas(Form("c1_%i",i),Form("pt%0.f_%0.f",lowpt[i],highpt[i]),900,600);
   h1[i]->Sumw2();
   }
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      LEP = lep==11 /*&& (HLT_Ele1>0 || HLT_Ele2>0)*/ && ptlep1 > 25. && ptlep2 > 25.&& abs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0 && massVlep >70. && massVlep < 110;
      if(LEP==false)  continue;
      for(Int_t i=0;i<ptnumber;i++){    
        if(photon_pt[position]>lowpt[i]&&photon_pt[position]<highpt[i])
		h1[i]->Fill(photon_pt[position],scalef);
      }
      
  }
   TFile* hfake = new TFile("hfake.root","recreate");
   hfake->cd();
   for(Int_t i=0;i<ptnumber;i++){
	   c1[i]->cd();
	   h1[i]->Write();
	   h1[i]->Draw("hist");
	   c1[i]->Print(Form("./pt%0.f_%0.f.pdf",lowpt[i],highpt[i]));
   }
   hfake->Close();
}
