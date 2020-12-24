#define num 103
#define pi 3.1415926
void run( TFile*file,TString cut1,TString tag,bool turn){
	TString name=file->GetName();
	TTree*tree=(TTree*)file->Get("ZPKUCandidates");     
	Double_t scalef,pileupWeight,prefWeight,pweight[703],Mjj,jet1eta,jet2eta;
	double muon1_id_scale,muon2_id_scale,muon1_iso_scale,muon2_iso_scale,ele1_id_scale,ele2_id_scale,ele1_reco_scale,ele2_reco_scale,photon_id_scale,photon_veto_scale,muon_hlt_scale,ele_hlt_scale,puIdweight_M;
	int lep;
	tree->SetBranchAddress("lep",&lep);
	tree->SetBranchAddress("scalef",&scalef);
	tree->SetBranchAddress("pileupWeight",&pileupWeight);
	tree->SetBranchAddress("prefWeight",&prefWeight);
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
	tree->SetBranchAddress("Mjj",&Mjj);
	tree->SetBranchAddress("jet1eta",&jet1eta);
	tree->SetBranchAddress("jet2eta",&jet2eta);
	TTreeFormula *tformula=new TTreeFormula("formula", cut1, tree);
	double actualWeight[num],weight;
	TH1D*th1[num];
	TString th1name[num];
	for(Int_t i=0;i<num;i++){
		th1name[i]=Form("hist_%d",i);
		th1[i] = new TH1D(th1name[i],th1name[i],9,0,9);
		th1[i]->Sumw2(); 
	}
	cout<<tag<<" "<<name<<endl;
	for(int k=0;k<tree->GetEntries();k++){
		tree->GetEntry(k);
		double detajj=fabs(jet1eta-jet2eta);
		int p=0;
		int init;
		if(tag.Contains("16")&&name.Contains("EWK"))
			init=9;//16 ewk
		else if(tag.Contains("16")&&name.Contains("EWK")==0)
			init=0;//16 qcd
		else if(( tag.Contains("17")||tag.Contains("18"))&&name.Contains("EWK"))
			init=45;//17 ewk,18 ewk
                if(tag.Contains("18")) prefWeight=1;
                if(tag.Contains("17")==0) puIdweight_M=1;
		weight=scalef*pileupWeight*photon_id_scale*photon_veto_scale*puIdweight_M;
		if(lep==11)
			weight=weight*ele1_id_scale*ele2_id_scale*ele1_reco_scale*ele2_reco_scale*ele_hlt_scale;
		if(lep==13)
			weight=weight*muon1_id_scale*muon2_id_scale*muon1_iso_scale*muon2_iso_scale*muon_hlt_scale;
		if (  tformula->EvalInstance() ){
			for(Int_t i=init;i<(num+init);i++){
				actualWeight[p]=weight*pweight[i];
				if(Mjj>=500&&Mjj<800&&detajj>=2.5&&detajj<4.5)th1[p]->Fill(0.5,actualWeight[p]);//0~1, 2.5~4.5 and 500~800
				if(Mjj>=800&&Mjj<1200&&detajj>=2.5&&detajj<4.5)th1[p]->Fill(1.5,actualWeight[p]);//1~2 2.5~4.5 and 800~1200
				if(Mjj>=1200&&detajj>=2.5&&detajj<4.5)th1[p]->Fill(2.5,actualWeight[p]);//2~3 2.5~4.5 1200~2000
				if(Mjj>=500&&Mjj<800&&detajj>=4.5&&detajj<6)th1[p]->Fill(3.5,actualWeight[p]);//3~4 4.5~6 500~800 
				if(Mjj>=800&&Mjj<1200&&detajj>=4.5&&detajj<6)th1[p]->Fill(4.5,actualWeight[p]);//4~5 4.5~6 800~1200
				if(Mjj>=1200&&detajj>=4.5&&detajj<6)th1[p]->Fill(5.5,actualWeight[p]);//5~6 6~infi 500~800
				if(Mjj>=500&&Mjj<800&&detajj>=6)th1[p]->Fill(6.5,actualWeight[p]);//6~7 6~infi 800~1200
				if(Mjj>=800&&Mjj<1200&&detajj>=6)th1[p]->Fill(7.5,actualWeight[p]);//7~8 6~infi800~1200
				if(Mjj>=1200&&detajj>=6)th1[p]->Fill(8.5,actualWeight[p]);//8~9 6~infi 800~1200
				p++;
			}
		}
	}
	TFile*fout;
	if(name.Contains("EWK")==0)
		fout= new TFile("hist_qcd_pdf"+tag+".root","recreate");
	else{
		if(turn==1)	fout= new TFile("hist_Sigout_pdf"+tag+".root","recreate");
		else  fout= new TFile("hist_ewk_pdf"+tag+".root","recreate");
	}
	fout->cd();
	for(Int_t i=0;i<num;i++){
		th1[i]->Write();
	}
	fout->Close();
	for(Int_t i=0;i<num;i++){
		delete  th1[i];
	}
}
int Uncer_batch_bkg(){
	TString GenLEPmu  = "(genlep==13 && genlep1pt>20 && genlep2pt>20 && fabs(genlep1eta)<2.4 && fabs(genlep2eta)<2.4&& genmassVlep>70 && genmassVlep<110)";
	TString GenLEPele = "(genlep==11 && genlep1pt>25 && genlep2pt>25 && fabs(genlep1eta)<2.5 && fabs(genlep2eta)<2.5&& genmassVlep>70 && genmassVlep<110)";
	TString GenPhoton = "(genphotonet>20 && ( (fabs(genphotoneta)<2.5&&fabs(genphotoneta)>1.566) || (fabs(genphotoneta)<1.4442) ))";
	TString GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
	TString GenDr = "(gendrjj>0.5 && gendrla1>0.7 && gendrla2>0.7 && gendrj1a>0.5 && gendrj2a>0.5 && gendrj1l>0.5 && gendrj2l>0.5 && gendrj1l2>0.5 && gendrj2l2>0.5)";
	TString GenSignalRegion = "(genMjj >500 && gendetajj>2.5)";

	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>20 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) ))";
	TString jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
	TString Pi=Form("%f",pi);
	TString dr = "(( sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(2*"+Pi+"-fabs(jet1phi-jet2phi))*(2*"+Pi+"-fabs(jet1phi-jet2phi)))>0.5 ||sqrt((jet1eta-jet2eta)*(jet1eta-jet2eta)+(fabs(jet1phi-jet2phi))*(fabs(jet1phi-jet2phi)))>0.5) && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
	TString SignalRegion = "(Mjj>500 && fabs(jet1eta-jet2eta)>2.5 && Mva>100)";
	vector<TString> tag={"16","17","18"};

	TFile*file1[3];
	TString dir1="/home/pku/anying/cms/rootfiles/2016/";     
	TString dir2="/home/pku/anying/cms/rootfiles/2017/";     
	TString dir3="/home/pku/anying/cms/rootfiles/2018/";     
	file1[0]=new TFile(dir1+"cutla-outZA16.root");
	file1[1]=new TFile(dir2+"cutla-outZA17.root");
	file1[2]=new TFile(dir3+"cutla-outZA18.root");

	TFile*file2[3];
	file2[0]=new TFile(dir1+"unfold_GenCutla-ZA-EWK16.root");
	file2[1]=new TFile(dir2+"unfold_GenCutla-ZA-EWK17.root");
	file2[2]=new TFile(dir3+"unfold_GenCutla-ZA-EWK18.root");

	for(int i=0;i<tag.size();i++){
		if(tag[i].Contains("17")){
			GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
			jet="( ((jet1pt>50&&fabs(jet1eta)<4.7)||(jet1pt>30&&jet1pt<50&&fabs(jet1eta)<4.7&&jet1puIdMedium==1)) && ((jet2pt>50&&fabs(jet2eta)<4.7)||(jet2pt>30&&jet2pt<50&&fabs(jet2eta)<4.7&&jet2puIdMedium==1)) )";
		}
		else{
			GenJet = "(genjet1pt>30 && genjet2pt>30 && fabs(genjet1eta)<4.7 && fabs(genjet2eta)<4.7)";
			jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
		}
		TString Gen= "(" + GenLEPmu +"||"+GenLEPele+")"+"&&"+GenPhoton+"&&"+GenJet+"&&"+GenDr+"&&"+GenSignalRegion;
		TString Reco= "(("+LEPmu+")||("+LEPele+"))"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion;
		TString cut1 ="("+Reco+")&&("+Gen+")";
		TString cut2 ="(("+Reco+")&& !("+Gen+"))";
		cout<<tag[i]<<" "<<jet<<endl;
		cout<<tag[i]<<" "<<GenJet<<endl;
		if(tag[i].Contains("16"))	
			run(file1[i],Reco,tag[i],0);
		run(file2[i],cut1,tag[i],0);
		run(file2[i],cut2,tag[i],1);
	}
	return 1;
}
