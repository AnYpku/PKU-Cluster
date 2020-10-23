#include "TGraphAsymmErrors.h"

double get_muon_ID_sys16(double etalep, double ptlep, TH2D* ID_BF, TH2D* ID_GH ){
	double ptlep_tmp=ptlep;
	if(ptlep>110) ptlep_tmp=110.;
	double lep_ID_scale=-1;
	lep_ID_scale=0.55*ID_BF->GetBinError(ID_BF->FindBin(fabs(etalep),ptlep_tmp))+0.45*ID_GH->GetBinError(ID_GH->FindBin(fabs(etalep),ptlep_tmp));
	
	return lep_ID_scale;
}
double get_muon_ID_stat16(double etalep, double ptlep, TH2D* ID_BF,TH2D*ID_GH){
        double ptlep_tmp=ptlep;
        if(ptlep>110) ptlep_tmp=110.;
        double lep_ID_scale=-1;
        lep_ID_scale=0.55*ID_BF->GetBinError(ID_BF->FindBin(fabs(etalep),ptlep_tmp))+0.45*ID_GH->GetBinError(ID_GH->FindBin(fabs(etalep),ptlep_tmp));;

        return lep_ID_scale;
}

double get_muon_iso_stat16(double etalep, double ptlep, TH2D* iso_BF, TH2D* iso_GH){
	double ptlep_tmp=ptlep;
        if(ptlep>110) ptlep_tmp=110.;
        double lep_iso_scale=-1;
	lep_iso_scale=0.55*iso_BF->GetBinError(iso_BF->FindBin(fabs(etalep),ptlep_tmp))+0.45*iso_GH->GetBinError(iso_GH->FindBin(fabs(etalep),ptlep_tmp));
	
        return lep_iso_scale;
}
double get_muon_iso_sys16(double etalep, double ptlep, TH2D* iso_BF,TH2D*iso_GH){
        double ptlep_tmp=ptlep;
        if(ptlep>110) ptlep_tmp=110.;
        double lep_iso_scale=-1;
        lep_iso_scale=0.55*iso_BF->GetBinError(iso_BF->FindBin(fabs(etalep),ptlep_tmp))+0.45*iso_GH->GetBinError(iso_GH->FindBin(fabs(etalep),ptlep_tmp));

        return lep_iso_scale;
}


