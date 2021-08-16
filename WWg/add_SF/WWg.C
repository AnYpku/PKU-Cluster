#define WWg_cxx
#include "WWg.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include "ele_channel_scale.C"
#include "muon_channel_scale.C"
using namespace std;
void WWg::Loop(TString name)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   

   Long64_t nbytes = 0, nb = 0;
   int tot=0;
   TFile*fbtag=new TFile("eff_btag18.root");
   TH1D*heff=(TH1D*)fbtag->Get("btag_eff18");
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%10000==0) cout<<jentry<<" "<<nentries<<" "<<scalef<<endl;
      double MCweight=1,Dataweight=1;
      double MCweight_up=1,Dataweight_up=1;
      double MCweight_down=1,Dataweight_down=1;
      btag_weight=1;btag_weight_up=1;btag_weight_down=1;
      for(int i=0;i<nJet;i++){
	      if(fabs(Jet_partonFlavour[i])==5){
		      MCweight=MCweight*heff->GetBinContent(heff->FindBin(Jet_pt_nom[i]));
                      Dataweight=Dataweight*heff->GetBinContent(heff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M[i];
                      Dataweight_up=Dataweight*heff->GetBinContent(heff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_up[i];
                      Dataweight_down=Dataweight*heff->GetBinContent(heff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_down[i];
	      }
	      else{
                     MCweight=MCweight*(1-heff->GetBinContent(heff->FindBin(Jet_pt_nom[i])));
                     Dataweight=Dataweight*(1-heff->GetBinContent(heff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M[i]);
                     Dataweight_up=Dataweight*(1-heff->GetBinContent(heff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_up[i]);
                     Dataweight_down=Dataweight*(1-heff->GetBinContent(heff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_down[i]);
	      }
	      cout<<i<<" "<<nJet<<" "<<fabs(Jet_partonFlavour[i])<<" "<<Jet_pt_nom[i]<<" "<<heff->GetBinContent(heff->FindBin(Jet_pt_nom[i]))<<" "<<Jet_btagSF_deepcsv_M[i]<<" "<<Dataweight<<" "<<MCweight<<" "<<endl;
      }
      cout<<Dataweight<<" "<<MCweight<<" "<< btag_weight<<endl;
      btag_weight=Dataweight/MCweight;
      btag_weight_up=Dataweight_up/MCweight;
      btag_weight_down=Dataweight_down/MCweight;
      ExTree->Fill();
      tot++;
   }
   cout<<nentries<<" "<<tot<<endl;
}
