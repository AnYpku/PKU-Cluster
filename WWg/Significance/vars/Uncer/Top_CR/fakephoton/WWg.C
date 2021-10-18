#define WWg_cxx
#include "WWg.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <fstream>
using namespace std;
void WWg::Loop(TString name,TString year)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntries();
   vector<double> ptbins_b,ptbins_e;
   ptbins_b={20,25,30,35,40,50,60,100,400};
   ptbins_e={20,25,30,40,50,60,400};
   TFile*fb=new TFile("./weight_barrel_uncer"+year+".root");
   TFile*fe=new TFile("./weight_endcap_uncer"+year+".root");
   TFile*fin=new TFile("../../../../fakephoton/cal_weight/weight_"+year+".root");
   TH2D*weight_b=(TH2D*)fin->Get("weight_barrel");
   TH2D*weight_e=(TH2D*)fin->Get("weight_endcap");
   TH1D*weight_b_up=(TH1D*)fb->Get("weight_up");
   TH1D*weight_e_up=(TH1D*)fe->Get("weight_up");
   TH1D*weight_b_down=(TH1D*)fb->Get("weight_down");
   TH1D*weight_e_down=(TH1D*)fe->Get("weight_down");
   Long64_t nbytes = 0, nb = 0;
   double lumi;
   if(name.Contains("18")); lumi=59.7;
   if(name.Contains("17")); lumi=41.52;
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
      double tmp;
      if(cut){
              if(fabs(photoneta)<1.4442){
		      double weight=weight_b->GetBinContent(weight_b->FindBin(0.5,photonet));
                      double weight_up=weight_b_up->GetBinContent(weight_b_up->FindBin(photonet));
                      double weight_down=weight_b_down->GetBinContent(weight_b_down->FindBin(photonet));
                      if(name.Contains("Muon")==0) tmp=scalef/weight;
		      else tmp=1;
		      scalef=tmp*weight;
                      scalef_up=tmp*weight_up;
                      scalef_down=tmp*weight_down;
	      }
	      else if( (fabs(photoneta)<2.5 && fabs(photoneta)>1.566) ){
		      double weight=weight_e->GetBinContent(weight_e->FindBin(0.5,photonet));
                      double weight_up=weight_e_up->GetBinContent(weight_e_up->FindBin(photonet));
                      double weight_down=weight_e_down->GetBinContent(weight_e_down->FindBin(photonet));
                      if(name.Contains("Muon")==0) tmp=scalef/weight;
		      else tmp=1;
		      scalef=tmp*weight;
                      scalef_up=tmp*weight_up;
                      scalef_down=tmp*weight_down;
	      }
      }
      else continue;
      if(name.Contains("Muon")==0){
          PuppiMET_T1_pt=PuppiMET_T1Smear_pt;
          PuppiMET_T1_phi=PuppiMET_T1Smear_phi;
      }
      ExTree->Fill();
   }
   fin->Close();
   fb->Close();
   fe->Close();
}
