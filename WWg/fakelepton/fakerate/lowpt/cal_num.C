TH2D* run(TString filename,TString cut,TString particle,TString year,TString type){
	vector<double> ptbins={15,20,25,30,35,40,60};
	vector<double> etabins={0,0.5,1,1.5,2,2.5};
        TChain*tree=new TChain("Events","");
	if(year.Contains("16")){
		ptbins={15,20,30,40,60};
		etabins={0,0.5,1,1.5,2,2.5};
	}
	if(year.Contains("17")&&particle.Contains("mu")){
		ptbins={15,20};
		etabins={0,2.5};
	}
        TString dir;
	if(year.Contains("16pre")){dir="../../chain_combine/rootfiles/pre/";year="16";}
	else dir="../../chain_combine/rootfiles/";
        if(filename.Contains("Ele")||filename.Contains("EGamma")||filename.Contains("Muon")) 
		tree->Add(dir+"out"+filename+"*_fakerate"+year+".root");
	else{
                if(dir.Contains("pre"))   tree->Add(dir+"out"+filename+"_fakerate16pre.root");
		else      tree->Add(dir+"out"+filename+"_fakerate"+year+".root");
	}
        TString HLT_Ele1,HLT_Ele2,HLT_Mu1,HLT_Mu2;
	HLT_Mu1="HLT_Mu8_TrkIsoVVL";
	HLT_Mu2="HLT_Mu17_TrkIsoVVL";
	HLT_Ele2="HLT_Ele23_CaloIdL_TrackIdL_IsoVL_PFJet30";
        if(year.Contains("16")) HLT_Ele1="HLT_Ele12_CaloIdL_TrackIdL_IsoVL_PFJet30";
	
	else  HLT_Ele1="HLT_Ele8_CaloIdL_TrackIdL_IsoVL_PFJet30";
	if(particle.Contains("mu")){
		if(filename.Contains("Muon")==0){
			cut="("+cut+" && ( (lepton_pt>25 &&"+ HLT_Mu2 +")||(lepton_pt<25 &&"+ HLT_Mu1 + ") ) && lepton_isprompt==1"+"&&"+type+")";
		}
		else
			cut="("+cut+"&&( (lepton_pt>25 &&" + HLT_Mu2 +") || (lepton_pt<25 && "+ HLT_Mu1 + ") )"+"&&"+type+")";
	}

	else if(particle.Contains("ele")){
		if(filename.Contains("Ele")==0 && filename.Contains("EGamma")==0){
			cut="("+cut+" && ( ( lepton_pt<25 &&"+ HLT_Ele1 +") || ( lepton_pt>25 &&"+ HLT_Ele2  +") ) && lepton_isprompt==1"+"&&"+type+")";
		}
		else
			cut="("+cut+"&&( ( lepton_pt<25 && "+ HLT_Ele1 +") || (  lepton_pt>25 &&"+ HLT_Ele2  +" ) )"+"&&"+type+")";
                       
	}
        cout<<filename<<" "<<particle<<" "<<" "<<cut<<"; after this cut "<<tree->GetEntries(cut)<<"; total entries "<<tree->GetEntries()<<endl;
        TString t; if(type.Contains("1"))t="tight";else t="loose_not_tight";
	TString histname="hist_"+particle+"_"+filename+year+"_"+t;
	TH2D*h1=new TH2D(histname,"",etabins.size()-1,&etabins[0],ptbins.size()-1,&ptbins[0]);
	if(filename.Contains("Muon")||filename.Contains("Ele"))
		tree->Draw("lepton_pt:fabs(lepton_eta)>>"+histname,cut+"*1","goff");
	else{
		if(year.Contains("16")&&dir.Contains("pre")==0)
			tree->Draw("lepton_pt:fabs(lepton_eta)>>"+histname,cut+"*scalef*0.4627","goff");
		else if(year.Contains("16")&&dir.Contains("pre"))
			tree->Draw("lepton_pt:fabs(lepton_eta)>>"+histname,cut+"*scalef*0.537","goff");
		else tree->Draw("lepton_pt:fabs(lepton_eta)>>"+histname,cut+"*scalef","goff");
	}
        cout<<h1->GetEntries()<<endl;
        return h1;
}
TFile* run_cal_num(TString channel,TString year){
 
	TString cut,cut_mc,file;
	if(channel=="mu"){
		file="Muon";
		cut="( fabs(lepton_pid)==13 && lepton_pt>10 && fabs(lepton_eta)<2.4 && MET_T1_pt<30 && sqrt(2*(lepton_pt*MET_T1_pt*(1-cos(lepton_phi-MET_T1_phi) ) ) )<20 )";
		cut_mc="( fabs(lepton_pid)==13 && lepton_pt>10 && fabs(lepton_eta)<2.4 && MET_T1Smear_pt<30 && sqrt(2*(lepton_pt*MET_T1Smear_pt*(1-cos(lepton_phi-MET_T1Smear_phi) ) ) )<20 )";
	}
	else{
		cut="( fabs(lepton_pid)==11 && lepton_pt>10 && fabs(lepton_eta)<2.5 && MET_T1_pt<30 && sqrt(2*(lepton_pt*MET_T1_pt*(1-cos(lepton_phi-MET_T1_phi) ) ) )<20 )";
		cut_mc="( fabs(lepton_pid)==11 && lepton_pt>10 && fabs(lepton_eta)<2.5 && MET_T1Smear_pt<30 && sqrt(2*(lepton_pt*MET_T1Smear_pt*(1-cos(lepton_phi-MET_T1Smear_phi) ) ) )<20 )";
		file="Ele";
	}
        TH2D*h_mu_T=run(file,cut,channel,year,"is_lepton_tight==1");
        TH2D*h_mu_L=run(file,cut,channel,year,"is_lepton_tight==0");
        TH2D*h_WJets_T=run("WJets",cut_mc,channel,year,"is_lepton_tight==1");
        TH2D*h_WJets_L=run("WJets",cut_mc,channel,year,"is_lepton_tight==0");
        TH2D*h_DY_T=run("DYJets",cut_mc,channel,year,"is_lepton_tight==1");
        TH2D*h_DY_L=run("DYJets",cut_mc,channel,year,"is_lepton_tight==0");
	TFile*fout=new TFile("hist_num"+channel+year+".root","recreate");
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
//	TFile*fmu=run_cal_num("mu","16pre");
//	TFile*fele=run_cal_num("ele","16pre");
//	TFile*fmu1=run_cal_num("mu","16");
//	TFile*fele1=run_cal_num("ele","16");
//	TFile*fmu=run_cal_num("mu","18");
//	TFile*fele=run_cal_num("ele","18");
	TFile*fmu=run_cal_num("mu","17");
//	TFile*fele=run_cal_num("ele","17");
return 0;
}
