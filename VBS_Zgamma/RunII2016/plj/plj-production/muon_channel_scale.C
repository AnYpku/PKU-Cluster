#include "TGraphAsymmErrors.h"

double get_muon_ID(double etalep, double ptlep, TH2F* ID_BF, TH2F* ID_GH ){
	double ptlep_tmp=ptlep;
	if(ptlep>110) ptlep_tmp=110.;
	double lep_ID_scale=-1;
	lep_ID_scale=0.55*ID_BF->GetBinContent(ID_BF->FindBin(fabs(etalep),ptlep_tmp))+0.45*ID_GH->GetBinContent(ID_GH->FindBin(fabs(etalep),ptlep_tmp));
	
	return lep_ID_scale;
}

double get_muon_iso(double etalep, double ptlep, TH2F* iso_BF, TH2F* iso_GH){
	double ptlep_tmp=ptlep;
        if(ptlep>110) ptlep_tmp=110.;
        double lep_iso_scale=-1;
	lep_iso_scale=0.55*iso_BF->GetBinContent(iso_BF->FindBin(fabs(etalep),ptlep_tmp))+0.45*iso_GH->GetBinContent(iso_GH->FindBin(fabs(etalep),ptlep_tmp));
	
        return lep_iso_scale;
}

double get_muon_track_scale(double etalep, TGraphAsymmErrors* track_SF){
	double track_scale=-1;
	track_scale=track_SF->Eval(0.1+0.2*int(fabs(etalep)/0.2));

	return track_scale;
}

double muon_HLT_scale(double etalep1, double etalep2, TH2D* di_lep_trigger){
	double hlt_scale=-1;
	hlt_scale=di_lep_trigger->GetBinContent(di_lep_trigger->FindBin(fabs(etalep1),fabs(etalep2)));

	return hlt_scale;
}
