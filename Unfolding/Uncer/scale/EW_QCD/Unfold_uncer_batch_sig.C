#define num 9
void run( TFile*file,TString vec_branchname,TString reco,vector<double> bins,TString cut1,TString tag,int kk){
	TTree*tree=(TTree*)file->Get("ZPKUCandidates");     
	//     tree->SetBranchStatus("*",0);
	map<TString, double> variables;
	double Mjj,deltaetajj,gendetajj;
	Double_t scalef,pileupWeight,pweight[703],prefWeight;
	double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale,ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale,muon_hlt_scale,ele_hlt_scale,puIdweight_T;
	int lep;
	tree->SetBranchAddress("lep",&lep);
	tree->SetBranchAddress("scalef",&scalef);
	tree->SetBranchAddress("pileupWeight",&pileupWeight);
	tree->SetBranchAddress("prefWeight",&prefWeight);
	tree->SetBranchAddress("puIdweight_T", &puIdweight_T);
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
	tree->SetBranchAddress("puIdweight_T", &puIdweight_T);
	tree->SetBranchAddress(vec_branchname, &variables[vec_branchname]);
	tree->SetBranchAddress(reco, &variables[reco]);
	TTreeFormula *tformula=new TTreeFormula("formula", cut1, tree);
	double actualWeight[num],weight;
	TH1D*th1[num][kk];
	TH2D*th2[num][kk];
	TString th1name[num][kk];
	Double_t mjj_bins[4]={500, 800, 1200, 2000};
	Double_t detajj_bins[4]={2.5, 4.5,  6, 6.5};
	for(Int_t j=0;j<kk;j++){//Loop the binning cuts
		for(Int_t i=0;i<num;i++){
			th1name[i][j]=vec_branchname+Form("_scale%d_",i)+Form("recobin%d",j+1);
			if(vec_branchname.Contains("Mjj")==0)th1[i][j] = new TH1D(th1name[i][j],th1name[i][j],bins.size()-1,&bins[0]);
			else th2[i][j] = new TH2D(th1name[i][j],th1name[i][j],3,mjj_bins,3,detajj_bins);
		}      
	}
	for(int k=0;k<tree->GetEntries();k++){
		tree->GetEntry(k);
		if(tag.Contains("18")) prefWeight=1;
		if(tag.Contains("17")==0) puIdweight_T=1;
		weight=scalef*pileupWeight*prefWeight*photon_id_scale*photon_veto_scale*puIdweight_T;
		if(lep==11)
			weight=weight*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*ele_hlt_scale;
		if(lep==13)
			weight=weight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon_hlt_scale;
		if ( ! tformula->EvalInstance() ) continue;
		int p=0;
		int first;
		if(tag.Contains("16"))first=104;//16 qcd sample
		else if(tag.Contains("16")==0)first=0;//17 or 18 qcd sample
		for(Int_t i=first;i<(num+first);i++){//Loop scale variation
			int k;k=i;
			actualWeight[p]=weight*pweight[k];
			if(vec_branchname.Contains("Mjj")==0){
				for(Int_t j=0;j<kk;j++){
					if(j<kk-1 && variables[reco]>bins[j]&&variables[reco]<bins[j+1]){
						th1[p][j]->Fill(variables[vec_branchname],actualWeight[p]);
					}
					else if(j==kk-1 && variables[reco]>bins[j]){
						th1[p][j]->Fill(variables[vec_branchname],actualWeight[p]);
					}
				}
			}
			else{
				for(int iy=0;iy<3;iy++){
					for(int ix=0;ix<3;ix++){
						if(variables[vec_branchname]>2000) variables[vec_branchname]=1999;
						if(gendetajj>6.5) gendetajj=6.1;
						if(ix<2&&iy<2&&variables[reco]>mjj_bins[ix]&&variables[reco]<mjj_bins[ix+1]&&deltaetajj>detajj_bins[iy]&&deltaetajj<detajj_bins[iy+1])
							th2[p][ix+(iy)*3]->Fill(variables[vec_branchname],gendetajj,actualWeight[p]);
						if(ix==2&&iy<2&&variables[reco]>mjj_bins[ix]&&deltaetajj>detajj_bins[iy]&&deltaetajj<detajj_bins[iy+1])
							th2[p][ix+(iy)*3]->Fill(variables[vec_branchname],gendetajj,actualWeight[p]);
						if(ix<2&&iy==2&&variables[reco]>mjj_bins[ix]&& variables[reco]<mjj_bins[ix+1] &&deltaetajj>detajj_bins[iy])
							th2[p][ix+(iy)*3]->Fill(variables[vec_branchname],gendetajj,actualWeight[p]);
						if(ix==2&&iy==2 && variables[reco]>mjj_bins[ix] && deltaetajj>detajj_bins[iy])
							th2[p][ix+(iy)*3]->Fill(variables[vec_branchname],gendetajj,actualWeight[p]);
					}
				}

			}
			p++;
		}
	}

	TFile*fout[kk];
	for(int j=0;j<kk;j++){
		if(vec_branchname.Contains("Mjj")==0) fout[j]= new TFile("unfold_"+vec_branchname+Form("_recobin%d",j+1)+"_qcd_scale"+tag+".root","recreate");
		else fout[j]= new TFile("unfold_2d"+vec_branchname+Form("_recobin%d",j+1)+"_qcd_scale"+tag+".root","recreate");
	}
	for(int j=0;j<kk;j++){
		fout[j]->cd();
		for(Int_t i=0;i<num;i++){
			if(vec_branchname.Contains("Mjj")==0)
				th1[i][j]->Write();
			else th2[i][j]->Write();
		}
		fout[j]->Close();
	}
	for(int i=0;i<num;i++){
		for(int j=0;j<kk;j++){
			if(vec_branchname.Contains("Mjj")==0)
				delete th1[i][j];
			else delete th2[i][j];
		}
	}
}
int Unfold_uncer_batch_sig(){
	TString GenLEPmu  = "(genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4&& genmassVlep>70 && genmassVlep<110)";
	TString GenLEPele = "(genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5&& genmassVlep>70 && genmassVlep<110)";
	TString GenPhoton = "(genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) ) )";
	TString GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
	TString GenDr = "(gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5)";
	TString GenSignalRegion = "(genMjj >500 && gendetajj>2.5)";
	TString Gen= "(" + GenLEPmu +"||"+GenLEPele+")"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenSignalRegion;

	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ) )";
	TString jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
	TString dr = "(drjj>0.5 && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
	TString SignalRegion = "(Mjj>500 && deltaetajj>2.5 && Mva>100)";
	vector<vector<double>> bins;
	vector<double> ptlepBins={20,80,120,200,400};
	vector<double> photonEtBins={20,80,120,200,400};
	vector<double> jetptBins={30,150,250,350,800};
	vector<double> MvaBins={100,150,1000};
	vector<double> MjjBins={500,1000,1500,2000};
	bins.push_back(ptlepBins);
	bins.push_back(photonEtBins);
	bins.push_back(jetptBins);
	bins.push_back(MjjBins);

	vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt","genMjj"};
	vector<TString> recovars={"ptlep1","photonet","jet1pt","Mjj"};
	//	vector<TString> genvars={"genMjj"};
	//	vector<TString> recovars={"Mjj"};
	TString dir[3];
	TFile*file[3];
	vector<TString> tag={"16","17","18"};
	//	vector<TString> tag={"17"};
	for(int i=0;i<tag.size();i++){
		if(tag[i].Contains("17")){
			jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdTight==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdTight==1)) )";
		}
		else{
			jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
		}
		TString Reco= "("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
		TString cut1 ="(("+Reco+")&&("+Gen+"))";
		TString cut2 ="(("+Reco+")&& !("+Gen+"))";
		dir[i]="/home/pku/anying/cms/rootfiles/20"+tag[i]+"/";
		file[i]=new TFile(dir[i]+"unfold_GenCutla-ZA"+tag[i]+".root");
		if(tag[i].Contains("17")==0) continue;
		for(int j=0;j<genvars.size();j++){
			cout<<tag[i]<<" "<<genvars[j]<<endl;
			if(genvars[j].Contains("Mjj")==0) run(file[i],genvars[j], recovars[j], bins[j],cut1,tag[i],bins[j].size()-1);
			else run(file[i],genvars[j], recovars[j], bins[j],cut1,tag[i],9);
		}
	}
	return 1;
}
