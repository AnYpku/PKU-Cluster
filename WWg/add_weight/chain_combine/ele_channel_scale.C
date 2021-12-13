double get_ele_ID(double etalep, double ptlep, TH2F* ID){
	double ptlep_tmp = ptlep;
	if(ptlep>500) ptlep_tmp=499.;
	double lep_ID_scale=-1;
	lep_ID_scale=ID->GetBinContent(ID->FindBin(etalep,ptlep_tmp));

	return lep_ID_scale;
}

double get_ele_Reco(double etalep, double ptlep, TH2F* Reco, TH2F*Reco1){
	double ptlep_tmp = ptlep;
	if(ptlep>500) ptlep_tmp=499.;
	double lep_Reco_scale=-1;
	if(ptlep>20)
		lep_Reco_scale=Reco->GetBinContent(Reco->FindBin(etalep,ptlep_tmp));
	else
		lep_Reco_scale=Reco1->GetBinContent(Reco1->FindBin(etalep,ptlep_tmp));

	return lep_Reco_scale;
}

double get_photon_ID(double photoneta, double photonet, TH2F* ID_photon){
	double photon_ID_scale=-1;
        if(photonet>500) photonet=499;
	photon_ID_scale=ID_photon->GetBinContent(ID_photon->FindBin(photoneta,photonet));

	return photon_ID_scale;
}

double get_ele_ID_up(double etalep, double ptlep, TH2F* ID){
	double ptlep_tmp = ptlep;
	if(ptlep>500) ptlep_tmp=499.;
	double lep_ID_scale=-1;
	lep_ID_scale=ID->GetBinContent(ID->FindBin(etalep,ptlep_tmp))+ID->GetBinError(ID->FindBin(etalep,ptlep_tmp));
	return lep_ID_scale;
}

double get_ele_ID_down(double etalep, double ptlep, TH2F* ID){
	double ptlep_tmp = ptlep;
	if(ptlep>500) ptlep_tmp=499.;
	double lep_ID_scale=-1;
	lep_ID_scale=ID->GetBinContent(ID->FindBin(etalep,ptlep_tmp))-ID->GetBinError(ID->FindBin(etalep,ptlep_tmp));
	return lep_ID_scale;
}

double get_ele_Reco_up(double etalep, double ptlep, TH2F* Reco, TH2F*Reco1){
	double ptlep_tmp = ptlep;
	if(ptlep>500) ptlep_tmp=499.;
	double lep_Reco_scale=-1;
	if(ptlep>20)
		lep_Reco_scale=Reco->GetBinContent(Reco->FindBin(etalep,ptlep_tmp))+Reco->GetBinError(Reco->FindBin(etalep,ptlep_tmp));
	else
		lep_Reco_scale=Reco1->GetBinContent(Reco1->FindBin(etalep,ptlep_tmp))+Reco->GetBinError(Reco->FindBin(etalep,ptlep_tmp));
	return lep_Reco_scale;
}

double get_ele_Reco_down(double etalep, double ptlep, TH2F* Reco,TH2F*Reco1){
	double ptlep_tmp = ptlep;
	if(ptlep>500) ptlep_tmp=499.;
	double lep_Reco_scale=-1;
	if(ptlep>20)
		lep_Reco_scale=Reco->GetBinContent(Reco->FindBin(etalep,ptlep_tmp))-Reco->GetBinError(Reco->FindBin(etalep,ptlep_tmp));
	else
		lep_Reco_scale=Reco1->GetBinContent(Reco1->FindBin(etalep,ptlep_tmp))-Reco->GetBinError(Reco->FindBin(etalep,ptlep_tmp));
	return lep_Reco_scale;
}

double get_photon_ID_up(double photoneta, double photonet, TH2F* ID_photon){
	double photon_ID_scale=-1;
        if(photonet>500) photonet=499;
	photon_ID_scale=ID_photon->GetBinContent(ID_photon->FindBin(photoneta,photonet))+ID_photon->GetBinError(ID_photon->FindBin(photoneta,photonet));
	return photon_ID_scale;
}

double get_photon_ID_down(double photoneta, double photonet, TH2F* ID_photon){
	double photon_ID_scale=-1;
        if(photonet>500) photonet=499;
	photon_ID_scale=ID_photon->GetBinContent(ID_photon->FindBin(photoneta,photonet))-ID_photon->GetBinError(ID_photon->FindBin(photoneta,photonet));
	return photon_ID_scale;
}

double get_photon_veto_up(double photoneta,TH1F*SF,TH1F*Stat,TH1F*PU,TH1F*Model,TString year){
       double photon_veto_scale=1;
       double unc_model;
       if(year.Contains("16")==0) unc_model=pow(Model->GetBinContent(1),2);
       else unc_model=0;
       if(fabs(photoneta)<1.4442)
	       photon_veto_scale=SF->GetBinContent(1)+sqrt(pow(Stat->GetBinContent(1),2)+pow(PU->GetBinContent(1),2)+unc_model);
       if(fabs(photoneta)<2.5 && fabs(photoneta)>1.566)
	       photon_veto_scale=SF->GetBinContent(4)+sqrt(pow(Stat->GetBinContent(4),2)+pow(PU->GetBinContent(4),2)+unc_model);
       return photon_veto_scale;
}

double get_photon_veto_down(double photoneta,TH1F*SF,TH1F*Stat,TH1F*PU,TH1F*Model,TString year){
       double photon_veto_scale=1;
       double unc_model;
       if(year.Contains("16")==0) unc_model=pow(Model->GetBinContent(1),2);
       else unc_model=0;
       if(fabs(photoneta)<1.4442)
	       photon_veto_scale=SF->GetBinContent(1)-sqrt(pow(Stat->GetBinContent(1),2)+pow(PU->GetBinContent(1),2)+unc_model);
       if(fabs(photoneta)<2.5 && fabs(photoneta)>1.566)
	       photon_veto_scale=SF->GetBinContent(4)-sqrt(pow(Stat->GetBinContent(4),2)+pow(PU->GetBinContent(4),2)+unc_model);
       return photon_veto_scale;
}
