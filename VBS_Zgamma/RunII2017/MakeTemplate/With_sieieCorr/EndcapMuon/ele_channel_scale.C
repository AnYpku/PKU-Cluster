double get_ele_ID(double etalep, double ptlep, TH2F* ID){
	double ptlep_tmp = ptlep;
	if(ptlep>500) ptlep_tmp=499.;
	double lep_ID_scale=-1;
	lep_ID_scale=ID->GetBinContent(ID->FindBin(etalep,ptlep_tmp));

	return lep_ID_scale;
}

double get_ele_Reco(double etalep, double ptlep, TH2F* Reco){
	double ptlep_tmp = ptlep;
	if(ptlep>500) ptlep_tmp=499.;
	double lep_Reco_scale=-1;
	lep_Reco_scale=Reco->GetBinContent(Reco->FindBin(etalep,ptlep_tmp));

	return lep_Reco_scale;
}

double get_photon_ID(double photoneta, double photonet, TH2F* ID_photon){
	double photon_ID_scale=-1;
        if(photonet>500) photonet=499;
	photon_ID_scale=ID_photon->GetBinContent(ID_photon->FindBin(photoneta,photonet));

	return photon_ID_scale;
}
