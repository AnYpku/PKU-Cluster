#define WWg_cxx
#include "WWg.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include "ele_channel_scale.C"
#include "muon_channel_scale.C"
using namespace std;
void WWg::Loop(TString name,TString year)
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   

   Long64_t nbytes = 0, nb = 0;
   int tot=0;
   TFile*fbtag=new TFile("eff_b_jet"+year+".root");
   TH1D*hbeff=(TH1D*)fbtag->Get("b_jet_eff"+year);
   TFile*fctag=new TFile("eff_c_jet"+year+".root");
   TH1D*hceff=(TH1D*)fctag->Get("c_jet_eff"+year);
   TFile*fltag=new TFile("eff_l_jet"+year+".root");
   TH1D*hleff=(TH1D*)fltag->Get("l_jet_eff"+year);
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%10000==0) cout<<jentry<<" "<<nentries<<" "<<scalef<<endl;
      double MCweight=1,Dataweight=1;
      double MCweight_up=1,Dataweight_up=1;
      double MCweight_down=1,Dataweight_down=1;
      btag_weight=1;btag_weight_up=1;btag_weight_down=1;
//      cout<<hbeff->GetBinContent(1)<<endl;
//      cout<<hceff->GetBinContent(1)<<endl;
//      cout<<hleff->GetBinContent(1)<<endl;
      for(int i=0;i<nJet;i++){
	      if(fabs(Jet_partonFlavour[i])==5){
                      if(Jet_btagDeepB[i]>0.4168){
			      MCweight=MCweight*hbeff->GetBinContent(hbeff->FindBin(Jet_pt_nom[i]));
			      Dataweight=Dataweight*hbeff->GetBinContent(hbeff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M[i];
			      Dataweight_up=Dataweight*hbeff->GetBinContent(hbeff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_up[i];
			      Dataweight_down=Dataweight*hbeff->GetBinContent(hbeff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_down[i];
		      }
		      else{
			      MCweight=MCweight*(1-hbeff->GetBinContent(hbeff->FindBin(Jet_pt_nom[i])));
			      Dataweight=Dataweight*(1-hbeff->GetBinContent(hbeff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M[i]);
			      Dataweight_up=Dataweight*(1-hbeff->GetBinContent(hbeff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_up[i]);
			      Dataweight_down=Dataweight*(1-hbeff->GetBinContent(hbeff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_down[i]);
		      }
	      }
	      else if(fabs(Jet_partonFlavour[i])==4){
		      if(Jet_btagDeepB[i]>0.4168){
			      MCweight=MCweight*hceff->GetBinContent(hceff->FindBin(Jet_pt_nom[i]));
			      Dataweight=Dataweight*hceff->GetBinContent(hceff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M[i];
			      Dataweight_up=Dataweight*hceff->GetBinContent(hceff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_up[i];
			      Dataweight_down=Dataweight*hceff->GetBinContent(hceff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_down[i];
		      }
		      else{
			      MCweight=MCweight*(1-hceff->GetBinContent(hceff->FindBin(Jet_pt_nom[i])));
			      Dataweight=Dataweight*(1-hceff->GetBinContent(hceff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M[i]);
			      Dataweight_up=Dataweight*(1-hceff->GetBinContent(hceff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_up[i]);
			      Dataweight_down=Dataweight*(1-hceff->GetBinContent(hceff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_down[i]);
		      }
	      }
	      else{
		      if(Jet_btagDeepB[i]>0.4168){
			      MCweight=MCweight*hleff->GetBinContent(hleff->FindBin(Jet_pt_nom[i]));
			      Dataweight=Dataweight*hleff->GetBinContent(hleff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M[i];
			      Dataweight_up=Dataweight*hleff->GetBinContent(hleff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_up[i];
			      Dataweight_down=Dataweight*hleff->GetBinContent(hleff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_down[i];
		      }
		      else{
			      MCweight=MCweight*(1-hleff->GetBinContent(hleff->FindBin(Jet_pt_nom[i])));
			      Dataweight=Dataweight*(1-hleff->GetBinContent(hleff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M[i]);
			      Dataweight_up=Dataweight*(1-hleff->GetBinContent(hleff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_up[i]);
			      Dataweight_down=Dataweight*(1-hleff->GetBinContent(hleff->FindBin(Jet_pt_nom[i]))*Jet_btagSF_deepcsv_M_down[i]);
		      }
	      }

//	      cout<<i<<" "<<nJet<<" "<<fabs(Jet_partonFlavour[i])<<" "<<Jet_pt_nom[i]<<" "<<hbeff->GetBinContent(hbeff->FindBin(Jet_pt_nom[i]))<<" "<<Jet_btagSF_deepcsv_M[i]<<" "<<Dataweight<<" "<<MCweight<<" "<<endl;
      }
      if(MCweight>0){
	      btag_weight=Dataweight/MCweight;
	      btag_weight_up=Dataweight_up/MCweight;
	      btag_weight_down=Dataweight_down/MCweight;
      }
      cout<<Dataweight<<" "<<MCweight<<" "<< btag_weight<<" "<<btag_weight_up<<" "<<btag_weight_down<<endl;
      ExTree->Fill();
      tot++;
   }
   fbtag->Close();
   fctag->Close();
   fltag->Close();
   cout<<nentries<<" "<<tot<<endl;
}
