#include "TGraphAsymmErrors.h"

double get_muon_ID(double etalep, double ptlep, TH2F* ID_BF){
	double ptlep_tmp=ptlep;
	if(ptlep>110) ptlep_tmp=110.;
	double lep_ID_scale=-1;
	lep_ID_scale=ID_BF->GetBinContent(ID_BF->FindBin(fabs(etalep),fabs(ptlep_tmp)));
	
	return lep_ID_scale;
}

double get_muon_iso(double etalep, double ptlep, TH2F* iso_BF){
	double ptlep_tmp=ptlep;
        if(ptlep>110) ptlep_tmp=110.;
        double lep_iso_scale=-1;
	lep_iso_scale=iso_BF->GetBinContent(iso_BF->FindBin(fabs(etalep),ptlep_tmp));
	
        return lep_iso_scale;
}

double get_muon_ID_up(double etalep, double ptlep, TH2F* ID_BF){
	double ptlep_tmp=ptlep;
	if(ptlep>110) ptlep_tmp=110.;
	double lep_ID_scale=-1;
	lep_ID_scale=ID_BF->GetBinContent(ID_BF->FindBin(fabs(etalep),fabs(ptlep_tmp)))+ID_BF->GetBinError(ID_BF->FindBin(fabs(etalep),fabs(ptlep_tmp)));
	return lep_ID_scale;
}

double get_muon_ID_down(double etalep, double ptlep, TH2F* ID_BF){
	double ptlep_tmp=ptlep;
	if(ptlep>110) ptlep_tmp=110.;
	double lep_ID_scale=-1;
	lep_ID_scale=ID_BF->GetBinContent(ID_BF->FindBin(fabs(etalep),fabs(ptlep_tmp)))-ID_BF->GetBinError(ID_BF->FindBin(fabs(etalep),fabs(ptlep_tmp)));
	return lep_ID_scale;
}

double get_muon_iso_up(double etalep, double ptlep, TH2F* iso_BF){
	double ptlep_tmp=ptlep;
        if(ptlep>110) ptlep_tmp=110.;
        double lep_iso_scale=-1;
	lep_iso_scale=iso_BF->GetBinContent(iso_BF->FindBin(fabs(etalep),ptlep_tmp))+iso_BF->GetBinError(iso_BF->FindBin(fabs(etalep),ptlep_tmp));
	
        return lep_iso_scale;
}

double get_muon_iso_down(double etalep, double ptlep, TH2F* iso_BF){
	double ptlep_tmp=ptlep;
        if(ptlep>110) ptlep_tmp=110.;
        double lep_iso_scale=-1;
	lep_iso_scale=iso_BF->GetBinContent(iso_BF->FindBin(fabs(etalep),ptlep_tmp))-iso_BF->GetBinError(iso_BF->FindBin(fabs(etalep),ptlep_tmp));
	
        return lep_iso_scale;
}
