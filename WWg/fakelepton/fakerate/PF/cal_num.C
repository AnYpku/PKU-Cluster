TH2D* run(TString filename,TString cut,TString particle,TString year,TString type){
	vector<double> ptbins={20,25,30,35,40,60};
	vector<double> etabins={0,0.5,1,1.5,2,2.5};
	TFile*f1=new TFile("/home/pku/anying/cms/rootfiles/WWg/"+filename+year+"_fakerate.root");
	TTree*tree=(TTree*)f1->Get("Events");
	double scalef;
	if(filename.Contains("WJets")){scalef=0.45378848;}
	else if(filename.Contains("DY")){scalef=0.0925280;}
	else scalef=1;
	if(particle.Contains("mu")){
		if(filename.Contains("Muon")==0){
			scalef=scalef*0.04578;
			cut="("+cut+"&&(HLT_Mu17_TrkIsoVVL)&&lepton_isprompt==1"+"&&"+type+")";
		}
		else
			cut="("+cut+"&&(HLT_Mu17_TrkIsoVVL)"+"&&"+type+")";
	}

	else if(particle.Contains("ele")){
		if(filename.Contains("Ele")==0){
			cut="("+cut+"&&(HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30)&&lepton_isprompt==1"+"&&"+type+")";
			scalef=scalef*0.03891;
		}
		else
			cut="("+cut+"&&(HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30)"+"&&"+type+")";
                       
	}
        cout<<filename<<" "<<particle<<" "<<scalef<<" "<<cut<<" "<<tree->GetEntries(cut)<<" "<<tree->GetEntries()<<endl;
        TString t; if(type.Contains("1"))t="tight";else t="loose_not_tight";
	TString histname="hist_"+particle+"_"+filename+year+"_"+t;
	TH2D*h1=new TH2D(histname,"",etabins.size()-1,&etabins[0],ptbins.size()-1,&ptbins[0]);
        TString weight=Form("*%f*fabs(gen_weight)/gen_weight",scalef);
	cout<<weight<<endl;
	if(filename.Contains("Muon")||filename.Contains("Ele"))
		tree->Draw("lepton_pt:lepton_eta>>"+histname,cut+"*1","goff");
	else
		tree->Draw("lepton_pt:fabs(lepton_eta)>>"+histname,cut+weight,"goff");
        cout<<h1->GetEntries()<<endl;
        return h1;
}
int cal_num(){
	TString cut="(fabs(lepton_pid)==13 && lepton_pt>20 && fabs(lepton_eta)<2.4 && met<30 && mt<20)";
        TH2D*h_mu_T=run("DMuon",cut,"mu","18","is_lepton_tight==1");
        TH2D*h_mu_L=run("DMuon",cut,"mu","18","is_lepton_tight==0");
        TH2D*h_WJets_T=run("WJets",cut,"mu","18","is_lepton_tight==1");
        TH2D*h_WJets_L=run("WJets",cut,"mu","18","is_lepton_tight==0");
        TH2D*h_DY_T=run("DY",cut,"mu","18","is_lepton_tight==1");
        TH2D*h_DY_L=run("DY",cut,"mu","18","is_lepton_tight==0");
	TFile*file=new TFile("hist_num.root","recreate");
        h_mu_L->Write();     
        h_mu_T->Write();     
        h_WJets_L->Write();     
        h_WJets_T->Write();     
        h_DY_L->Write();     
        h_DY_T->Write();     
	file->Close();
	return 0;
}
