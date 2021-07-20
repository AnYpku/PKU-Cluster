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

   Long64_t nentries = fChain->GetEntries();

   Long64_t nbytes = 0, nb = 0;
   Long64_t npp = fChain->GetEntries("gen_weight>0.");
   Long64_t nmm = fChain->GetEntries("gen_weight<0.");
   Bool_t HLT_mm=0,HLT_ee=0,HLT_emu=0;
   Bool_t BSL=0,LEP=0,PHOTON=0;
   TFile*fele=new TFile("/home/pku/anying/cms/PKU-Cluster/WWg/fakelepton/fakerate/mu18_fakerate.root");
   TH2D*hele=(TH2D*)fele->Get("TtoL");
   TFile*fmu=new TFile("/home/pku/anying/cms/PKU-Cluster/WWg/fakelepton/fakerate/ele18_fakerate.root");
   TH2D*hmu=(TH2D*)fmu->Get("TtoL");
   double lumi=59.7;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      scalef=scalef*ele_id_scale*ele_reco_scale*muon_id_scale*muon_iso_scale*puWeight;
      if(jentry%1000==0) cout<<jentry<<" "<<nentries<<" "<<scalef<<endl;
      if(name.Contains("Ele")||name.Contains("Muon")){ scalef=1;photon_isprompt=1;lep1_isprompt=1;lep2_isprompt=1;}
      LEP = pass_selection>0 && channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && lep1_charge*lep2_charge<0 && drll>0.5 && lep1pt>20 && lep2pt>25 && fabs(lep1eta) < 2.4 && fabs(lep1eta) < 2.5 && n_loose_ele==1 && n_loose_mu==1 && ptll>30 && mll>20 && !(lep1_is_tight==1 && lep2_is_tight==1 ) && lep1_isprompt==1 && lep2_isprompt==1; 
      PHOTON = n_photon>0  && photonet > 20. && ( (fabs(photoneta) < 1.4442) || ( fabs(photoneta) < 2.5 && fabs(photoneta)>1.566 )) && drl1a>0.5 && drl2a>0.5 && photon_selection==1 /*&& photon_isprompt==1*/;
      if( !( LEP ) )
	      continue;
      if(PHOTON && name.Contains("Muon")==0) scalef=scalef*photon_id_scale*photon_veto_scale;
      double lep1pt_tmp,lep2pt_tmp;
      if(lep1pt>60) lep1pt_tmp=59; else lep1pt_tmp=lep1pt;
      if(lep2pt>60) lep2pt_tmp=59; else lep2pt_tmp=lep2pt;
      if(lep1_is_tight!=1 && lep2_is_tight!=1){
              if(name.Contains("Muon"))
		      scalef=hmu->GetBinContent(hmu->FindBin(fabs(lep1eta),lep1pt_tmp))/(1-hmu->GetBinContent(hmu->FindBin(fabs(lep1eta),lep1pt_tmp))) * hele->GetBinContent(hele->FindBin(fabs(lep2eta),lep2pt_tmp))/(1-hele->GetBinContent(hele->FindBin(fabs(lep2eta),lep2pt_tmp))) * (-1);
	      else{
		      scalef=scalef * lumi * hmu->GetBinContent(hmu->FindBin(fabs(lep1eta),lep1pt_tmp))/(1-hmu->GetBinContent(hmu->FindBin(fabs(lep1eta),lep1pt_tmp))) * hele->GetBinContent(hele->FindBin(fabs(lep2eta),lep2pt_tmp))/(1-hele->GetBinContent(hele->FindBin(fabs(lep2eta),lep2pt_tmp))) ;//MC loose+loose
//		      cout<<scalef<<endl;
	      }
      }
      else if(lep1_is_tight!=1 && lep2_is_tight==1){
              if(name.Contains("Muon"))
		      scalef=hmu->GetBinContent(hmu->FindBin(fabs(lep1eta),lep1pt_tmp))/(1-hmu->GetBinContent(hmu->FindBin(fabs(lep1eta),lep1pt_tmp)));
	      else{
		      scalef = scalef * lumi * hmu->GetBinContent(hmu->FindBin(fabs(lep1eta),lep1pt_tmp))/(1-hmu->GetBinContent(hmu->FindBin(fabs(lep1eta),lep1pt_tmp))) * (-1);//MC tight+loose
//		      cout<<scalef<<endl;
	      }
      }
      else if(lep1_is_tight==1 && lep2_is_tight!=1){
              if(name.Contains("Muon"))
		      scalef=hele->GetBinContent(hele->FindBin(fabs(lep2eta),lep2pt_tmp))/(1-hele->GetBinContent(hele->FindBin(fabs(lep2eta),lep2pt_tmp)));
	      else{
		      scalef=scalef * lumi * hele->GetBinContent(hele->FindBin(fabs(lep2eta),lep2pt_tmp))/(1-hele->GetBinContent(hele->FindBin(fabs(lep2eta),lep2pt_tmp))) * (-1); //MC tight+loose
//		      cout<<scalef<<endl;
	      }
      }
      else scalef=0;
      if(jentry%1000==0) cout<<jentry<<" "<<nentries<<" "<<scalef<<" "<<lep1pt_tmp<<" "<<lep2pt_tmp<<endl;

      ExTree->Fill();
      // if (Cut(ientry) < 0) continue;
   }
}
