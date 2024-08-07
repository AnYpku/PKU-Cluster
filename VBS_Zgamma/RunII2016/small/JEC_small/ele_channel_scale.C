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
	photon_ID_scale=ID_photon->GetBinContent(ID_photon->FindBin(photoneta,photonet));

	return photon_ID_scale;
}
double get_eleHLT_SF(double etalep1, double ptlep1,double etalep2,double ptlep2, TH2F* MC1,TH2F*SF1,TH2F*MC2,TH2F*SF2){
        if(ptlep1>500) ptlep1=499.;
        if(ptlep2>500) ptlep2=499.;

        double lep_HLT_scale=-1;
        double lep_HLT_scale_MC=MC1->GetBinContent(MC1->FindBin(etalep1,ptlep1))*MC2->GetBinContent(MC2->FindBin(etalep2,ptlep2))+MC1->GetBinContent(MC1->FindBin(etalep2,ptlep2))*MC2->GetBinContent(MC2->FindBin(etalep1,ptlep1))-MC1->GetBinContent(MC1->FindBin(etalep1,ptlep1))*MC1->GetBinContent(MC1->FindBin(etalep2,ptlep2));

	double lep_HLT_scale_Data=MC1->GetBinContent(MC1->FindBin(etalep1,ptlep1))*SF1->GetBinContent(SF1->FindBin(etalep1,ptlep1))*MC2->GetBinContent(MC2->FindBin(etalep2,ptlep2))*SF2->GetBinContent(SF2->FindBin(etalep2,ptlep2))+MC1->GetBinContent(MC1->FindBin(etalep2,ptlep2))*SF1->GetBinContent(SF1->FindBin(etalep2,ptlep2))*MC2->GetBinContent(MC2->FindBin(etalep1,ptlep1))*SF2->GetBinContent(SF2->FindBin(etalep1,ptlep1))-MC1->GetBinContent(MC1->FindBin(etalep1,ptlep1))*SF1->GetBinContent(SF1->FindBin(etalep1,ptlep1))*MC1->GetBinContent(MC1->FindBin(etalep2,ptlep2))*SF1->GetBinContent(SF1->FindBin(etalep2,ptlep2));

        lep_HLT_scale=lep_HLT_scale_Data/lep_HLT_scale_MC;

        return lep_HLT_scale;
}
double get_PUID_SF(double jeteta,double jetpt,TH2F*eff,TH2F*misrate,TH2F*effSF,TH2F*misrateSF){
       double PUweight=1;
       if(jetpt<50){
               double PMC=eff->GetBinContent(eff->FindBin(jetpt,jeteta))*(1-misrate->GetBinContent(misrate->FindBin(jetpt,jeteta))); 
	       double PData= effSF->GetBinContent(effSF->FindBin(jetpt,jeteta))*eff->GetBinContent(eff->FindBin(jetpt,jeteta))*(1-misrateSF->GetBinContent(misrateSF->FindBin(jetpt,jeteta))*misrate->GetBinContent(misrate->FindBin(jetpt,jeteta)) );
	       PUweight=PData/PMC;
       }
       else PUweight=1;
       return PUweight;
}
