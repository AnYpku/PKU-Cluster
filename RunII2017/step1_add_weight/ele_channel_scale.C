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
double get_eleHLT_SF(double etalep1, double ptlep1,double etalep2,double ptlep2, TH2F* MC1,TH2F*SF1,TH2F*MC2,TH2F*SF2){
        if(ptlep1>500) ptlep1=499.;
        if(ptlep2>500) ptlep2=499.;

        double lep_HLT_scale=-1;
        double lep_HLT_scale_MC=MC1->GetBinContent(MC1->FindBin(etalep1,ptlep1))*MC2->GetBinContent(MC2->FindBin(etalep2,ptlep2))+MC1->GetBinContent(MC1->FindBin(etalep2,ptlep2))*MC2->GetBinContent(MC2->FindBin(etalep1,ptlep1))-MC1->GetBinContent(MC1->FindBin(etalep1,ptlep1))*MC1->GetBinContent(MC1->FindBin(etalep2,ptlep2));

	double lep_HLT_scale_Data=MC1->GetBinContent(MC1->FindBin(etalep1,ptlep1))*SF1->GetBinContent(SF1->FindBin(etalep1,ptlep1))*MC2->GetBinContent(MC2->FindBin(etalep2,ptlep2))*SF2->GetBinContent(SF2->FindBin(etalep2,ptlep2))+MC1->GetBinContent(MC1->FindBin(etalep2,ptlep2))*SF1->GetBinContent(SF1->FindBin(etalep2,ptlep2))*MC2->GetBinContent(MC2->FindBin(etalep1,ptlep1))*SF2->GetBinContent(SF2->FindBin(etalep1,ptlep1))-MC1->GetBinContent(MC1->FindBin(etalep1,ptlep1))*SF1->GetBinContent(SF1->FindBin(etalep1,ptlep1))*MC1->GetBinContent(MC1->FindBin(etalep2,ptlep2))*SF1->GetBinContent(SF1->FindBin(etalep2,ptlep2));

	lep_HLT_scale=lep_HLT_scale_Data/lep_HLT_scale_MC;

	return lep_HLT_scale;
}
double get_PUID_SF(double jet1eta,double jet1pt,double jet2eta,double jet2pt,TH2F*eff,TH2F*SFeff,TH2F*mis,TH2F*SFmis,int flag1,int flag2,double puId1,double puId2){
	double PUweight;
	int bin1=eff->FindBin(jet1pt,jet1eta);
	int bin2=eff->FindBin(jet2pt,jet2eta);
	if(jet1pt<50 && jet2pt<50 ){
		double PMC;
		double PData;
		if(flag1==1&&flag2==1){
			if(puId1==1&&puId2==1){
				PMC=eff->GetBinContent(bin1)*eff->GetBinContent(bin2);
				PData=SFeff->GetBinContent(bin1)*eff->GetBinContent(bin1)*SFeff->GetBinContent(bin2)*eff->GetBinContent(bin2);
			}
			else if(puId1==1&&puId2==0){
				PMC=eff->GetBinContent(bin1)*(1-eff->GetBinContent(bin2));
				PData=SFeff->GetBinContent(bin1)*eff->GetBinContent(bin1)*(1-SFeff->GetBinContent(bin2)*eff->GetBinContent(bin2));
			}
			else if(puId1==0&&puId2==1){
				PMC=eff->GetBinContent(bin2)*(1-eff->GetBinContent(bin1));
				PData=SFeff->GetBinContent(bin2)*eff->GetBinContent(bin2)*(1-SFeff->GetBinContent(bin1)*eff->GetBinContent(bin1));
			}
			else{
				PMC=(1-eff->GetBinContent(bin2))*(1-eff->GetBinContent(bin1));
				PData=(1-SFeff->GetBinContent(bin2)*eff->GetBinContent(bin2))*(1-SFeff->GetBinContent(bin1)*eff->GetBinContent(bin1));
			}
		}
		if(flag1==1&&flag2==0){
			if(puId1==1&&puId2==1){
				PMC=eff->GetBinContent(bin1)*mis->GetBinContent(bin2);
				PData=SFeff->GetBinContent(bin1)*eff->GetBinContent(bin1)*SFmis->GetBinContent(bin2)*mis->GetBinContent(bin2);
			}
			else if(puId1==1&&puId2==0){
				PMC=eff->GetBinContent(bin1)*(1-mis->GetBinContent(bin2));
				PData=SFeff->GetBinContent(bin1)*eff->GetBinContent(bin1)*(1-SFmis->GetBinContent(bin2)*mis->GetBinContent(bin2));
			}
			else if(puId1==0&&puId2==1){
				PMC=mis->GetBinContent(bin2)*(1-eff->GetBinContent(bin1));
				PData=SFmis->GetBinContent(bin2)*mis->GetBinContent(bin2)*(1-SFeff->GetBinContent(bin1)*eff->GetBinContent(bin1));
			}
			else{
				PMC=(1-mis->GetBinContent(bin2))*(1-eff->GetBinContent(bin1));
				PData=(1-SFmis->GetBinContent(bin2)*mis->GetBinContent(bin2))*(1-SFeff->GetBinContent(bin1)*eff->GetBinContent(bin1));
			}
		}
		if(flag1==0&&flag2==1){
			if(puId1==1&&puId2==1){
				PMC=eff->GetBinContent(bin2)*mis->GetBinContent(bin1);
				PData=SFeff->GetBinContent(bin2)*eff->GetBinContent(bin2)*SFmis->GetBinContent(bin1)*mis->GetBinContent(bin1);
			}
			else if(puId1==1&&puId2==0){
				PMC=mis->GetBinContent(bin1)*(1-eff->GetBinContent(bin2));
				PData=(1-SFeff->GetBinContent(bin2)*eff->GetBinContent(bin2))*SFmis->GetBinContent(bin1)*mis->GetBinContent(bin1);
			}
			else if(puId1==0&&puId2==1){
				PMC=(1-mis->GetBinContent(bin1))*eff->GetBinContent(bin2);
				PData=(1-SFmis->GetBinContent(bin1)*mis->GetBinContent(bin1))*SFeff->GetBinContent(bin2)*eff->GetBinContent(bin2);
			}
			else{
				PMC=(1-mis->GetBinContent(bin1))*(1-eff->GetBinContent(bin2));
				PData=(1-SFmis->GetBinContent(bin1)*mis->GetBinContent(bin1))*(1-SFeff->GetBinContent(bin2)*eff->GetBinContent(bin2));
			}
		}
		if(flag1==0&&flag2==0){
			if(puId1==1&&puId2==1){
				PMC=mis->GetBinContent(bin1)*mis->GetBinContent(bin2);
				PData=SFmis->GetBinContent(bin1)*mis->GetBinContent(bin1)*SFmis->GetBinContent(bin2)*mis->GetBinContent(bin2);
			}
			else if(puId1==1&&puId2==0){
				PMC=mis->GetBinContent(bin1)*(1-mis->GetBinContent(bin2));
				PData=SFmis->GetBinContent(bin1)*mis->GetBinContent(bin1)*(1-SFmis->GetBinContent(bin2)*mis->GetBinContent(bin2));
			}
			else if(puId1==0&&puId2==1){
				PMC=mis->GetBinContent(bin2)*(1-mis->GetBinContent(bin1));
				PData=SFmis->GetBinContent(bin2)*mis->GetBinContent(bin2)*(1-SFmis->GetBinContent(bin1)*mis->GetBinContent(bin1));
			}
			else{
				PMC=(1-mis->GetBinContent(bin2))*(1-mis->GetBinContent(bin1));
				PData=(1-SFmis->GetBinContent(bin2)*mis->GetBinContent(bin2))*(1-SFmis->GetBinContent(bin1)*mis->GetBinContent(bin1));
			}
		}
		if(PMC!=0)  PUweight=PData/PMC;
		else PUweight=1;
	}
	else if(jet2pt<50 && jet1pt>50 ){
		double PMC;
		double PData;
                if(flag2==1){
			if(puId2==1){
                           PMC=eff->GetBinContent(bin2);
			   PData=SFeff->GetBinContent(bin2)*eff->GetBinContent(bin2);
			}
			else{
                           PMC=1-eff->GetBinContent(bin2);
			   PData=1-SFeff->GetBinContent(bin2)*eff->GetBinContent(bin2);
			}
		}
		else{
			if(puId2==1){
                           PMC=mis->GetBinContent(bin2);
			   PData=SFmis->GetBinContent(bin2)*mis->GetBinContent(bin2);
			}
			else{
                           PMC=1-mis->GetBinContent(bin2);
			   PData=1-SFmis->GetBinContent(bin2)*mis->GetBinContent(bin2);
			}
		}
		if(PMC!=0)  PUweight=PData/PMC;
		else PUweight=1;
	}
	else PUweight=1;
	return PUweight;
}
