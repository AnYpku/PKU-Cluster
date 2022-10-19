TH1D* run(TString year,TString filename,TString particle,TString cut,int nbins,double low,double high){
	TChain* tree = new TChain("Events","");
	tree->Add("/home/pku/guanz/compare/PF_WWg/fakelepton/rootfiles/"+filename+"*"+year+".root");
	cout<<"add"<<" /home/pku/guanz/compare/PF_WWg/fakelepton/rootfiles/"+filename+"*"+year+".root"<<endl;
	TString HLT_Ele1,HLT_Ele2,HLT_Mu1,HLT_Mu2;
	HLT_Mu1="HLT_Mu8_TrkIsoVVL";
	HLT_Mu2="HLT_Mu17_TrkIsoVVL";
	HLT_Ele2="HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30";
	if(year.Contains("16")) HLT_Ele1="HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30";
	else  HLT_Ele1="HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30";

	if(particle.Contains("mu")){
			cut="("+cut+"&&( (lepton_pt>25 &&" + HLT_Mu2 +") || (lepton_pt<25 && "+ HLT_Mu1 + ") ))";
	}

	else if(particle.Contains("ele")){
			cut="("+cut+"&&( ( lepton_pt<25 && "+ HLT_Ele1 +") || (  lepton_pt>25 &&"+ HLT_Ele2  +" ) ))";

	}

	TString histname="hist_"+particle+"_"+filename+year+"_"+Form("%0.f_%0.f",low,high);
        TH1D*h1=new TH1D(histname,"",nbins,low,high);
	tree->Draw("lepton_pt>>"+histname,cut+"*scalef","goff");

        cout<<h1->GetEntries()<<endl;
        return h1;
}
int closure(){

	TFile*fout=new TFile("hist18.root","recreate");
	fout->cd();
	vector<double> ptbins={25,40,60};
	TString cut_mu="( fabs(lepton_pid)==13 && lepton_pt>15 && fabs(lepton_eta)<2.4  && MET_T1_pt<30 && sqrt(2*(lepton_pt*MET_T1_pt*(1-cos(lepton_phi-MET_T1_phi) ) ) )< 20 )";
	TString cut_ele="( fabs(lepton_pid)==11 && lepton_pt>15 && fabs(lepton_eta)<2.5 && MET_T1_pt<30 && sqrt(2*(lepton_pt*MET_T1_pt*(1-cos(lepton_phi-MET_T1_phi) ) ) )< 20 )";
	TH1D*h1=run("18","outWJets","ele","(("+cut_ele+")&& is_lepton_tight==1)",5,ptbins[0],ptbins[2]);
	TH1D*h2=run("18","outWJets","ele","(("+cut_ele+")&& is_lepton_tight==0)",5,ptbins[0],ptbins[2]);
	TH1D*h3=run("18","outWJets","elemc","(("+cut_ele+")&& lepton_isprompt==1)",5,ptbins[0],ptbins[2]);
	TH1D*h4=run("18","outWJets","elemc","(("+cut_ele+")&& lepton_isprompt!=1)",5,ptbins[0],ptbins[2]);
        h1->Write("mc_rate_tight");
        h2->Write("mc_rate_fake");
        h3->Write("mc_truth_tight");
        h4->Write("mc_truth_fake");
	for(int i=0;i<ptbins.size()-1;i++){
		TH1D*h1=run("18","outWJets","ele","(("+cut_ele+")&& is_lepton_tight==1)",5,ptbins[i],ptbins[i+1]);
		h1->Write(Form("mc_rate_tight_%0.f_%0.f",ptbins[i],ptbins[i+1]));
		TH1D*h2=run("18","outWJets","ele","(("+cut_ele+")&& is_lepton_tight==0)",5,ptbins[i],ptbins[i+1]);
		h2->Write(Form("mc_rate_fake_%0.f_%0.f",ptbins[i],ptbins[i+1]));
		TH1D*h3=run("18","outWJets","elemc","(("+cut_ele+")&& lepton_isprompt==1)",5,ptbins[i],ptbins[i+1]);
		h3->Write(Form("mc_truth_tight_%0.f_%0.f",ptbins[i],ptbins[i+1]));
		TH1D*h4=run("18","outWJets","elemc","(("+cut_ele+")&& lepton_isprompt!=1)",5,ptbins[i],ptbins[i+1]);
		h4->Write(Form("mc_truth_fake_%0.f_%0.f",ptbins[i],ptbins[i+1]));
	}
	fout->Close();
	return 0;
}
