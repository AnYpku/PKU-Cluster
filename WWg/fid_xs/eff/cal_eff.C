int count(TString cut,TString year){
        TFile*file=new TFile("/home/pku/anying/cms/rootfiles/WWg/20"+year+"/Genlep1-outWWG_emu"+year+".root");
        TTree*tree=(TTree*)file->Get("Events");
	int n=tree->GetEntries(cut);
	return n;
}
int cal_eff(){
        TString LEP = "( ((HLT_emu1)||(HLT_emu2)||(HLT_emu3)||(HLT_emu4)) && channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && lep1pt>20 && lep2pt>25 && fabs(lep1eta) < 2.4 && fabs(lep1eta) < 2.5 && n_loose_ele==1 && n_loose_mu==1 && ptll>30 && mll>20 && lep1_charge*lep2_charge<0 && drll>0.5 && lep1_is_tight==1 && lep2_is_tight==1 && lep1_isprompt==1 && lep2_isprompt==1)";
//	TString LEP = "( ( (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ) || (HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL) ) && channel==1 && fabs(lep1_pid)==13 && fabs(lep2_pid)==11 && lep1pt>20 && lep2pt>25 && fabs(lep1eta) < 2.4 && fabs(lep1eta) < 2.5 && n_loose_ele==1 && n_loose_mu==1 && ptll>30 && mll>20 && lep1_charge*lep2_charge<0 && drll>0.5 && lep1_is_tight==1 && lep2_is_tight==1 && lep1_isprompt==1 && lep2_isprompt==1)";
        TString PHOTON = "(n_photon>0  && photonet > 20. && ( (fabs(photoneta) < 1.4442) ||  (fabs(photoneta) < 2.5 && fabs(photoneta)>1.566) ) && drl1a>0.5 && drl2a>0.5 && photon_selection==1 && photon_isprompt==1)";
	TString MET = "( PuppiMET_T1Smear_pt > 20 && mT>50 && mT2>20 )";
	TString JET = "( n_bjets_nom==0 && njets30<=1 )";
        TString GenLEP = "( gen_channel==1 && fabs(genlep1)==13 && fabs(genlep2)==11 && genlep1pt>20 && genlep2pt>25 && fabs(genlep1eta) < 2.4 && fabs(genlep1eta) < 2.5 && genptll>30 && genmll>20 )";
        TString GenPHOTON = "( genphotonet>20 && ( fabs(genphotoneta)<1.4442 || (fabs(genphotoneta)<2.5 && fabs(genphotoneta)>1.566 )) && gendrl1a>0.5 && gendrl2a>0.5 )";
        TString GenMET = "(GenMET_pt>20 && genmT>50 && genmT2>20)";
	TString GenJET = "(n_genbjets==0 && n_genjets30<=1)";
	TString y="18"; 
        cout<<"LEP && PHOTON && MET && JET "<<count(LEP+"&&"+PHOTON+"&&"+MET+"&&"+JET,y)<<endl;
        cout<<"LEP && PHOTON && MET && JET && GenLEP && GenJET "<<count(LEP+"&&"+PHOTON+"&&"+MET+"&&"+JET+"&&"+GenLEP+"&&"+GenJET+"&&"+GenMET,y)<<endl;

	return 0;
}
