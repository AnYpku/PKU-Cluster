#include "WWg.h"
float WWg::get_btag_scale(TH1D*hbeff,TH1D*hceff,TH1D*hleff,double value,int nJet, float Jet_btagDeepB[30],int Jet_partonFlavour[30], float Jet_btagSF_deepcsv[30],float Jet_btagSF_deepcsv_up[30],float Jet_btagSF_deepcsv_down[30],float Jet_pt[30], TString type){
	float MCweight=1,Dataweight=1;
	float MCweight_up=1,Dataweight_up=1;
	float MCweight_down=1,Dataweight_down=1;
	float btag_weight_nominal=1,btag_weight_up=1,btag_weight_down=1;
	for(int i=0;i<nJet;i++){
		if(fabs(Jet_partonFlavour[i])==5){
			if(Jet_btagDeepB[i]>value){
				MCweight=MCweight*hbeff->GetBinContent(hbeff->FindBin(Jet_pt[i]));
				Dataweight=Dataweight*hbeff->GetBinContent(hbeff->FindBin(Jet_pt[i]))*Jet_btagSF_deepcsv[i];
				Dataweight_up=Dataweight*hbeff->GetBinContent(hbeff->FindBin(Jet_pt[i]))*Jet_btagSF_deepcsv_up[i];
				Dataweight_down=Dataweight*hbeff->GetBinContent(hbeff->FindBin(Jet_pt[i]))*Jet_btagSF_deepcsv_down[i];
			}
			else{
				MCweight=MCweight*(1-hbeff->GetBinContent(hbeff->FindBin(Jet_pt[i])));
				Dataweight=Dataweight*(1-hbeff->GetBinContent(hbeff->FindBin(Jet_pt[i]))*Jet_btagSF_deepcsv[i]);
				Dataweight_up=Dataweight*(1-hbeff->GetBinContent(hbeff->FindBin(Jet_pt[i]))*Jet_btagSF_deepcsv_up[i]);
				Dataweight_down=Dataweight*(1-hbeff->GetBinContent(hbeff->FindBin(Jet_pt[i]))*Jet_btagSF_deepcsv_down[i]);
			}
		}
		else if(fabs(Jet_partonFlavour[i])==4){
			if(Jet_btagDeepB[i]>value){
				MCweight=MCweight*hceff->GetBinContent(hceff->FindBin(Jet_pt[i]));
				Dataweight=Dataweight*hceff->GetBinContent(hceff->FindBin(Jet_pt[i]))*Jet_btagSF_deepcsv[i];
				Dataweight_up=Dataweight*hceff->GetBinContent(hceff->FindBin(Jet_pt[i]))*Jet_btagSF_deepcsv_up[i];
				Dataweight_down=Dataweight*hceff->GetBinContent(hceff->FindBin(Jet_pt[i]))*Jet_btagSF_deepcsv_down[i];
			}
			else{
				MCweight=MCweight*(1-hceff->GetBinContent(hceff->FindBin(Jet_pt[i])));
				Dataweight=Dataweight*(1-hceff->GetBinContent(hceff->FindBin(Jet_pt[i]))*Jet_btagSF_deepcsv[i]);
				Dataweight_up=Dataweight*(1-hceff->GetBinContent(hceff->FindBin(Jet_pt[i]))*Jet_btagSF_deepcsv_up[i]);
				Dataweight_down=Dataweight*(1-hceff->GetBinContent(hceff->FindBin(Jet_pt[i]))*Jet_btagSF_deepcsv_down[i]);
			}
		}
		else{
			if(Jet_btagDeepB[i]>value){
				MCweight=MCweight*hleff->GetBinContent(hleff->FindBin(Jet_pt[i]));
				Dataweight=Dataweight*hleff->GetBinContent(hleff->FindBin(Jet_pt[i]))*Jet_btagSF_deepcsv[i];
				Dataweight_up=Dataweight*hleff->GetBinContent(hleff->FindBin(Jet_pt[i]))*Jet_btagSF_deepcsv_up[i];
				Dataweight_down=Dataweight*hleff->GetBinContent(hleff->FindBin(Jet_pt[i]))*Jet_btagSF_deepcsv_down[i];
			}
			else{
				MCweight=MCweight*(1-hleff->GetBinContent(hleff->FindBin(Jet_pt[i])));
				Dataweight=Dataweight*(1-hleff->GetBinContent(hleff->FindBin(Jet_pt[i]))*Jet_btagSF_deepcsv[i]);
				Dataweight_up=Dataweight*(1-hleff->GetBinContent(hleff->FindBin(Jet_pt[i]))*Jet_btagSF_deepcsv_up[i]);
				Dataweight_down=Dataweight*(1-hleff->GetBinContent(hleff->FindBin(Jet_pt[i]))*Jet_btagSF_deepcsv_down[i]);
			}
		}
	}
	if(MCweight>0){
		btag_weight_nominal=Dataweight/MCweight;
		btag_weight_up=Dataweight_up/MCweight;
		btag_weight_down=Dataweight_down/MCweight;
	}
	if(type.Contains("up"))
		return btag_weight_up;
	else if(type.Contains("down"))
		return btag_weight_down;
	else
		return btag_weight_nominal;
}

