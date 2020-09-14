#define EGMregression_cxx
#include "EGMregression.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void EGMregression::Loop(bool isData)
{

  string suffix = "mc";
  
  if(isData)  suffix = "data";
  
  TFile *fout = new TFile( Form("histo_%s.root",suffix.c_str()),"RECREATE");
  int nbins = 100;
  double xmin = 50;
  double xmax = 150;
  
  TH1F *hrawM = new TH1F("hrawM","Raw", nbins,xmin,xmax);
  TH1F *hegmRM = new TH1F("hegmRM","EGM Reg", nbins,xmin,xmax);
  TH1F *hcalibM = new TH1F("hcalibM","Calib", nbins,xmin,xmax);

  nbins = 100;
  xmin = 0;
  xmax = 400;
  TH1F *hrawE = new TH1F("hrawE","raw E", nbins,xmin,xmax);
  TH1F *hcorrE = new TH1F("hcorrE","corr E", nbins,xmin,xmax);

  TFile *f = TFile::Open( Form("test3_%s.root",suffix.c_str()));
  TTree *tree = (TTree*)f->Get("ggNtuplizer/EventTree");;
  Init(tree);

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      /*
      for(int iele=0; iele<nEle; iele++){
	
	///apply loose ID
	if ((eleIDbit[iele] >> 2 & 1 ) ==0) return 0
	TLorentzVector ;
      }//for(int iele=0; iele<nEle; iele++)
      */

      if(nEle < 2) continue;

      //cout<<"EleId bit 0 : 1 "<<(eleIDbit->at(0) >> 1 & 1 )<<" "<<(eleIDbit->at(1) >> 1 & 1 )<<endl;

      if ( !(eleIDbit->at(0) >> 0 & 1 )) continue;
      if ( !(eleIDbit->at(1) >> 0 & 1 )) continue;
      
      ///ele1
      double el1rawpT      = eleSCRawEn->at(0)/TMath::CosH(eleEta->at(0));  ///no EGM regression, no SS
      TLorentzVector *el1raw  = new TLorentzVector();
      el1raw->SetPtEtaPhiM(el1rawpT,eleEta->at(0),elePhi->at(0),0);

      double el1pT         = eleSCEn->at(0)/TMath::CosH(eleEta->at(0));   ///EGM regression is there, but no SS
      TLorentzVector *el1  = new TLorentzVector();
      el1->SetPtEtaPhiM(el1pT,eleEta->at(0),elePhi->at(0),0);

      double el1CalibpT    = eleCalibEn->at(0)/TMath::CosH(eleEta->at(0));   ///EGM regression is there, but no SS
      TLorentzVector *el1calib  = new TLorentzVector();
      el1calib->SetPtEtaPhiM(el1CalibpT,eleEta->at(0),elePhi->at(0),0);


      ///ele2
      double el2rawpT      = eleSCRawEn->at(1)/TMath::CosH(eleEta->at(1));  ///no EGM regression, no SS
      TLorentzVector *el2raw  = new TLorentzVector();
      el2raw->SetPtEtaPhiM(el2rawpT,eleEta->at(1),elePhi->at(1),0);

      double el2pT         = eleSCEn->at(1)/TMath::CosH(eleEta->at(1));   ///EGM regression is there, but no SS
      TLorentzVector *el2  = new TLorentzVector();
      el2->SetPtEtaPhiM(el2pT,eleEta->at(1),elePhi->at(1),0);

      double el2CalibpT    = eleCalibEn->at(1)/TMath::CosH(eleEta->at(1));   ///EGM regression is there, but no SS
      TLorentzVector *el2calib  = new TLorentzVector();
      el2calib->SetPtEtaPhiM(el2CalibpT,eleEta->at(1),elePhi->at(1),0);


      double mass_raw = (*el1raw + *el2raw).M();
      double mass_egmR = (*el1 + *el2).M();
      double mass_calib = (*el1calib + *el2calib).M();

      hrawM->Fill(mass_raw);
      hegmRM->Fill(mass_egmR);
      hcalibM->Fill(mass_calib);

      hrawE->Fill(eleSCRawEn->at(0));
      hcorrE->Fill(eleSCEn->at(0));
   }//for (Long64_t jentry=0; jentry<nentries;jentry++)

   cout<<"Writing the root file "<<endl;

   fout->cd();
   hrawM->Write();
   hegmRM->Write();
   hcalibM->Write();
   hrawE->Write();
   hcorrE->Write();
   fout->Write();
   fout->Close();
}
