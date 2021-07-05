TH2D* run(TString filename,TString cut,TString particle,TString year,TString type){
	vector<double> ptbins={10,15,20,25,30,35,40,60,200};
	vector<double> etabins={0,0.5,1,1.5,2,2.5};
        TChain*tree=new TChain("Events","");
        if(filename.Contains("Ele")) 
		tree->Add("../out"+filename+"*"+year+"_fakerate.root");
	else
		tree->Add("../out"+filename+year+"_fakerate.root");
//	TFile*f1=new TFile("../out"+filename+year+"_fakerate.root");
//      cout<<f1->GetName()<<endl;
//	TTree*tree=(TTree*)f1->Get("Events");
	if(particle.Contains("mu")){
		if(filename.Contains("Muon")==0){
			cut="("+cut+" && ( (lepton_pt>25 && HLT_Mu17_TrkIsoVVL)||(lepton_pt<25 && HLT_Mu8_TrkIsoVVL) ) && lepton_isprompt==1"+"&&"+type+")";
		}
		else
			cut="("+cut+"&&( (lepton_pt>25 && HLT_Mu17_TrkIsoVVL) || (lepton_pt<25 && HLT_Mu8_TrkIsoVVL) )"+"&&"+type+")";
	}

	else if(particle.Contains("ele")){
		if(filename.Contains("Ele")==0){
			cut="("+cut+" && ( ( lepton_pt<25 && HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30) || ( lepton_pt>25 && HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30) ) && lepton_isprompt==1"+"&&"+type+")";
		}
		else
			cut="("+cut+"&&( ( lepton_pt<25 && HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30) || (  lepton_pt>25 && HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30) )"+"&&"+type+")";
                       
	}
        cout<<filename<<" "<<particle<<" "<<" "<<cut<<" "<<tree->GetEntries(cut)<<" "<<tree->GetEntries()<<endl;
        TString t; if(type.Contains("1"))t="tight";else t="loose_not_tight";
	TString histname="hist_"+particle+"_"+filename+year+"_"+t;
	TH2D*h1=new TH2D(histname,"",etabins.size()-1,&etabins[0],ptbins.size()-1,&ptbins[0]);
	if(filename.Contains("Muon")||filename.Contains("Ele"))
		tree->Draw("lepton_pt:fabs(lepton_eta)>>"+histname,cut+"*1","goff");
	else
		tree->Draw("lepton_pt:fabs(lepton_eta)>>"+histname,cut+"*scalef","goff");
        cout<<h1->GetEntries()<<endl;
        return h1;
}
TFile* run_cal_num(TString channel){
 
	TString cut,file;
	if(channel=="mu"){
		cut="( fabs(lepton_pid)==13 && lepton_pt>10 && fabs(lepton_eta)<2.4 && puppimet<30 && puppimt<20)";
		file="DMuon";
	}
	else{
		cut="( fabs(lepton_pid)==11 && lepton_pt>10 && fabs(lepton_eta)<2.4 && puppimet<30 && puppimt<20)";
		file="DEle";
	}
        TH2D*h_mu_T=run(file,cut,channel,"18","is_lepton_tight==1");
        TH2D*h_mu_L=run(file,cut,channel,"18","is_lepton_tight==0");
        TH2D*h_WJets_T=run("WJets",cut,channel,"18","is_lepton_tight==1");
        TH2D*h_WJets_L=run("WJets",cut,channel,"18","is_lepton_tight==0");
        TH2D*h_DY_T=run("DY",cut,channel,"18","is_lepton_tight==1");
        TH2D*h_DY_L=run("DY",cut,channel,"18","is_lepton_tight==0");
	TFile*fout=new TFile("hist_num"+channel+".root","recreate");
        h_mu_L->Write();     
        h_mu_T->Write();     
        h_WJets_L->Write();     
        h_WJets_T->Write();     
        h_DY_L->Write();     
        h_DY_T->Write();     
	fout->Close();
	return fout;
}
int cal_num(){
	TFile*fmu=run_cal_num("mu");
	TFile*fele=run_cal_num("ele");
return 0;
}
