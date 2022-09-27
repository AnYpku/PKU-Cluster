#include "TGraphAsymmErrors.h"

double get_muon_ID(double etalep, double ptlep, TH2D* ID_BF){
	double ptlep_tmp=ptlep;
	if(ptlep>110) ptlep_tmp=110.;
	double lep_ID_scale=-1;
	lep_ID_scale=ID_BF->GetBinContent(ID_BF->FindBin(fabs(ptlep_tmp),fabs(etalep)));
	
	return lep_ID_scale;
}

double get_muon_iso(double etalep, double ptlep, TH2D* iso_BF){
	double ptlep_tmp=ptlep;
        if(ptlep>110) ptlep_tmp=110.;
        double lep_iso_scale=-1;
	lep_iso_scale=iso_BF->GetBinContent(iso_BF->FindBin(ptlep_tmp,fabs(etalep)));
	
        return lep_iso_scale;
}

double get_muon_track_scale(double etalep, TH1F* track_SF){
	double track_scale=-1;
	track_scale=track_SF->GetBinContent(track_SF->FindBin(etalep));

	return track_scale;
}

double muon_HLT_scale(double ptlep1, double ptlep2, TH2D* di_lep_trigger){
	double hlt_scale=-1;
       if(ptlep1 > ptlep2){
               if(ptlep1>200) ptlep1=199;
               if(ptlep2>200) ptlep1=198;
	       hlt_scale=di_lep_trigger->GetBinContent(di_lep_trigger->FindBin(fabs(ptlep1),fabs(ptlep2)));
       }
       if(ptlep2 > ptlep1){
               if(ptlep1>200) ptlep1=198;
               if(ptlep2>200) ptlep1=199;
	       hlt_scale=di_lep_trigger->GetBinContent(di_lep_trigger->FindBin(fabs(ptlep2),fabs(ptlep1)));
       }

	return hlt_scale;
}
