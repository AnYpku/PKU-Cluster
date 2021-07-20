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
   vector<double> ptbins_b,ptbins_e;
   ptbins_b={20,25,30,35,40,50,60,100,400};
   ptbins_e={20,25,30,40,50,60,400};
   TFile*fout=new TFile("hist_MCprompt_"+name,"recreate");
   TH1D*hb=new TH1D("hist_barrel_"+name,"",ptbins_b.size()-1,&ptbins_b[0]);
   TH1D*he=new TH1D("hist_endcap_"+name,"",ptbins_e.size()-1,&ptbins_e[0]);
   TFile*fin=new TFile("../cal_weight/weight_18.root");
   TH2D*weight_b=(TH2D*)fin->Get("weight_barrel");
   TH2D*weight_e=(TH2D*)fin->Get("weight_endcap");
   Long64_t nbytes = 0, nb = 0;
   double lumi;
   if(name.Contains("18")); lumi=59.7;
   cout<<lumi<<endl;
   Bool_t cut,cut1;
   double actualWeight;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if(jentry%10000==0)cout<<jentry<<" "<<nentries<<endl;
      if(photonet>=400) photonet=399;
      if(name.Contains("Muon")){scalef=1;photon_isprompt=1;lep1_isprompt=1;lep2_isprompt=1;}
      cut=(channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11&&lep1_is_tight==1&&lep2_is_tight==1&&lep1_charge*lep2_charge<0&&drll>0.5&& lep1pt>20 && lep2pt>25 && fabs(lep1eta) < 2.4 && fabs(lep1eta) < 2.5&&n_loose_ele==1&&n_loose_mu==1&&ptll>30 && mll>20) && ( n_photon>0 && photonet > 20. && ( (fabs(photoneta)<1.4442) || (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) ) && drl1a>0.5 && drl2a>0.5 && (photon_selection==2 || photon_selection==3 || photon_selection==4 || photon_selection ==5 ) && photon_isprompt==1 /*&& lep1_isprompt==1 && lep2_isprompt==1*/ ) && ((HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL)) ;//selection of fake photon enriched sample 
      actualWeight=scalef*ele_id_scale*ele_reco_scale*muon_id_scale*muon_iso_scale*photon_id_scale*photon_veto_scale*puWeight*lumi;
      if(name.Contains("Muon")) actualWeight=1;
      if(cut){
              if(fabs(photoneta)<1.4442){
                      double weight=weight_b->GetBinContent(weight_b->FindBin(0.5,photonet));
		      hb->Fill(photonet,actualWeight*weight);          
                      scalef=scalef*weight;
	      }
	      else if( (fabs(photoneta)<2.5 && fabs(photoneta)>1.566) ){
                      double weight=weight_e->GetBinContent(weight_e->FindBin(0.5,photonet));
		      he->Fill(photonet,actualWeight*weight);          
                      scalef=scalef*weight;
	      }
      }
      else continue;
      if(name.Contains("Muon")==0) scalef=scalef*(-1)*lumi;
      ExTree->Fill();
   }
   fin->Close();
   fout->cd();
   cout<<hb->GetEntries()<<" "<<he->GetEntries()<<endl;
   hb->Write("barrel");
   he->Write("endcap");
   fout->Close();
}
