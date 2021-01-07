#define num 3
void run( TFile*file,TString vec_branchname,TString reco,vector<double> bins,TString cut1,TString tag,int kk){
	TTree*tree=(TTree*)file->Get("ZPKUCandidates");     
	//     tree->SetBranchStatus("*",0);
	map<TString, double> variables;
	double Mjj,deltaetajj,gendetajj;
	Double_t scalef,pileupWeight,pweight[703],prefWeight;
	double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale,ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale,muon_hlt_scale,ele_hlt_scale,puIdweight_M;
	int lep;
	tree->SetBranchAddress("lep",&lep);
	tree->SetBranchAddress("scalef",&scalef);
	tree->SetBranchAddress("pileupWeight",&pileupWeight);
	tree->SetBranchAddress("prefWeight",&prefWeight);
	tree->SetBranchAddress("puIdweight_M", &puIdweight_M);
	tree->SetBranchAddress("deltaetajj",&deltaetajj);
	tree->SetBranchAddress("gendetajj",&gendetajj);
	tree->SetBranchAddress("pweight",pweight);
	tree->SetBranchAddress("photon_id_scale", &photon_id_scale);
	tree->SetBranchAddress("photon_veto_scale", &photon_veto_scale);
	tree->SetBranchAddress("ele1_id_scale",   &ele1_id_scale);
	tree->SetBranchAddress("ele2_id_scale",   &ele2_id_scale);
	tree->SetBranchAddress("ele1_reco_scale", &ele1_reco_scale);
	tree->SetBranchAddress("ele2_reco_scale", &ele2_reco_scale);
	tree->SetBranchAddress("muon1_id_scale",   &muon1_id_scale);
	tree->SetBranchAddress("muon2_id_scale",   &muon2_id_scale);
	tree->SetBranchAddress("muon1_iso_scale", &muon1_iso_scale);
	tree->SetBranchAddress("muon2_iso_scale", &muon2_iso_scale);
	tree->SetBranchAddress("muon_hlt_scale", &muon_hlt_scale);
	tree->SetBranchAddress("ele_hlt_scale", &ele_hlt_scale);
	tree->SetBranchAddress("puIdweight_M", &puIdweight_M);
	tree->SetBranchAddress(vec_branchname, &variables[vec_branchname]);
	tree->SetBranchAddress(reco, &variables[reco]);
	TTreeFormula *tformula=new TTreeFormula("formula", cut1, tree);
	double actualWeight[num],weight;
	TH1D*th1[num][kk];
	TH2D*th2[num][kk];
	TString th1name[num][kk];
	for(Int_t j=0;j<kk;j++){//Loop the binning cuts
		for(Int_t i=0;i<num;i++){
			th1name[i][j]=vec_branchname+Form("_scale%d_",i)+Form("recobin%d",j+1);
			th1[i][j] = new TH1D(th1name[i][j],th1name[i][j],bins.size()-1,&bins[0]);
		}      
	}
	for(int k=0;k<tree->GetEntries();k++){
		tree->GetEntry(k);
		if(tag.Contains("18")) prefWeight=1;
		if(tag.Contains("17")==0) puIdweight_M=1;
		weight=scalef*pileupWeight*prefWeight*photon_id_scale*photon_veto_scale*puIdweight_M;
		if(lep==11)
			weight=weight*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*ele_hlt_scale;
		if(lep==13)
			weight=weight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon_hlt_scale;
		if ( ! tformula->EvalInstance() ) continue;
		int p=0;
		for(Int_t i=0;i<(num);i++){//Loop scale variation
			int k;
			if(tag.Contains("16")==0)
				k=15*i;
			else    k=i;
			actualWeight[p]=weight*pweight[k];
			for(Int_t j=0;j<kk;j++){
				if(j<kk-1 && variables[reco]>bins[j]&&variables[reco]<bins[j+1]){
					th1[p][j]->Fill(variables[vec_branchname],actualWeight[p]);
				}
				else if(j==kk-1 && variables[reco]>bins[j]){
					th1[p][j]->Fill(variables[vec_branchname],actualWeight[p]);
				}
			}
			p++;
		}
	}

	TFile*fout[kk];
	for(int j=0;j<kk;j++){
		fout[j]= new TFile("unfold_"+vec_branchname+Form("_recobin%d",j+1)+"_ewk_scale"+tag+".root","recreate");
	}
	for(int j=0;j<kk;j++){
		fout[j]->cd();
		for(Int_t i=0;i<num;i++){
			th1[i][j]->Write();
		}
		fout[j]->Close();
	}
	for(int i=0;i<num;i++){
		for(int j=0;j<kk;j++){
			delete th1[i][j];
		}
	}
}
int Unfold_uncer_batch_sig(){
	TString GenLEPmu  = "(genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4&& genmassVlep>70 && genmassVlep<110)";
	TString GenLEPele = "(genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5&& genmassVlep>70 && genmassVlep<110)";
	TString GenPhoton = "(genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) ) )";
	TString GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
	TString GenDr = "(gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5)";
	TString GenSignalRegion = "(genMjj >150 && genMjj<500 && genZGmass>100)";
	TString Gen= "(" + GenLEPmu +"||"+GenLEPele+")"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenSignalRegion;

	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ) )";
	TString jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
	TString dr = "(drjj>0.5 && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
	TString SignalRegion = "(Mjj>150 && Mjj<500 && Mva>100)";
	vector<vector<double>> bins;
	vector<double> ptlepBins={20,80,120,200,400};
	vector<double> photonEtBins={20,80,120,200,400};
	vector<double> jetptBins={30,150,250,350,800};
	vector<double> MvaBins={100,150,1000};
	vector<double> MjjBins={150,300,400,500};
	bins.push_back(ptlepBins);
	bins.push_back(photonEtBins);
	bins.push_back(jetptBins);
	bins.push_back(MjjBins);

	vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt","genMjj"};
	vector<TString> recovars={"ptlep1","photonet","jet1pt","Mjj"};
	//vector<TString> genvars={"genMjj"};
	//vector<TString> recovars={"Mjj"};
	TString dir[3];
	TFile*file[3];
	vector<TString> tag={"16","17","18"};
	//vector<TString> tag={"17"};
	for(int i=0;i<tag.size();i++){
		if(tag[i].Contains("17")){
			jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";
		}
		else{
			jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
		}
		TString Reco= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
		TString cut1 ="(("+Reco+")&&("+Gen+"))";
		TString cut2 ="(("+Reco+")&& !("+Gen+"))";
		dir[i]="/home/pku/anying/cms/rootfiles/20"+tag[i]+"/";
		file[i]=new TFile(dir[i]+"unfold_GenCutla-ZA-EWK"+tag[i]+".root");
		for(int j=0;j<genvars.size();j++){
			cout<<tag[i]<<" "<<genvars[j]<<endl;
			run(file[i],genvars[j], recovars[j], bins[j],cut1,tag[i],bins[j].size()-1);
		}
	}
	return 1;
}
