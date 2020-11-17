void run(TString channel, TString tag, TString sample,TString cut,vector<double>ZGbin){
	TFile*file;
	if(sample.Contains("plj")==0)file=new TFile("./rootfiles/optimal_"+sample+tag+".root");
	else file=new TFile("./rootfiles/optimal_"+sample+tag+"_weight.root");
	TTree*tree=(TTree*)file->Get("outtree");
	TString cut2;
	if(channel.Contains("ele")) cut2="(lep==11)";
        else if(channel.Contains("mu")) cut2="(lep==13)"; 
        cut="("+cut+"&&("+cut2+"))";
	TTreeFormula *tformula1=new TTreeFormula("formula1", cut, tree);
        TString hname="hist";
        TH1D*h1=new TH1D(hname,hname,ZGbin.size()-1,&ZGbin[0]);
	TString lumi;
	if(tag.Contains("16"))lumi=Form("%f",35.86);
	if(tag.Contains("17"))lumi=Form("%f",41.52);
	if(tag.Contains("18"))lumi=Form("%f",58.7);
        if(sample.Contains("plj")) lumi=Form("%f",1.0);
	cout<<sample<<" "<<channel<<" "<<tag<<" "<< lumi<<endl;
	tree->Draw("ZGmass>>"+hname,cut+"*actualWeight*"+lumi,"goff");
        TFile*fout=new TFile("./root/hist_"+sample+tag+channel+".root","recreate");
	fout->cd();
	h1->Write();
	fout->Close();
	file->Close();
}
int Build_histo_aQGC(){
	TString LEPmu = "(lep==13 &&  ptlep1 > 20. && ptlep2 > 20.&& fabs(etalep1) < 2.4 &&abs(etalep2) < 2.4 && nlooseeles==0 && nloosemus <3  && massVlep >70. && massVlep<110)";
	TString LEPele = "(lep==11  && ptlep1 > 25. && ptlep2 > 25.&& fabs(etalep1) < 2.5 &&abs(etalep2) < 2.5 && nlooseeles < 3 && nloosemus == 0  && massVlep >70. && massVlep<110)";
	TString photon = "(photonet>100 &&( (fabs(photoneta)<2.5&&fabs(photoneta)>1.566) || (fabs(photoneta)<1.4442) )  )";
	TString jet;
	TString dr = "(drjj>0.5 && drla>0.7 && drla2>0.7 && drj1a>0.5 && drj2a>0.5 && drj1l>0.5&&drj2l>0.5&&drj1l2>0.5&&drj2l2>0.5)";
	TString SignalRegion = "(Mjj>500 && fabs(jet1eta-jet2eta)>2.5)";
	vector<TString> tag={"16","17","18"};
	vector<TString> channel={"ele","mu"};
	vector<TString> sample={"ST","plj","TTA","VV","ZA","ZA-EWK"};
	vector<double> ZGbin={150,400,600,800,1000,2e4};
	TString Reco;
	for(int k=0;k<tag.size();k++){
		if(tag[k].Contains("17")==1){
			jet="(  ( (fabs(jet1eta)<3.14&&fabs(jet1eta)>2.65&&jet1pt>30&&jet1pt<50&&jet1puIdTight==1) || (!(fabs(jet1eta)<3.14&&fabs(jet1eta)>2.65) && fabs(jet1eta)<4.7 && jet1pt>30 && jet1pt<50)||(fabs(jet1eta)<4.7&& jet1pt>50) ) && ( (fabs(jet2eta)<3.14&&fabs(jet2eta)>2.65&&jet2pt>30&&jet2pt<50&&jet2puIdTight==1)||(!(fabs(jet2eta)<3.14&&fabs(jet2eta)>2.65)&&fabs(jet2eta)<4.7&&jet2pt>30&&jet2pt<50) ||(fabs(jet2eta)<4.7 && jet2pt>50) ) )";
		}
		else{
			jet = "(jet1pt> 30 && jet2pt > 30 && fabs(jet1eta)< 4.7 && fabs(jet2eta)<4.7)";
		}
		Reco= "(("+LEPmu+"||"+LEPele+")"+"&&"+photon+"&&"+dr+"&&"+jet+"&&"+SignalRegion+")";
		for(int i=0;i<sample.size();i++){
			for(int j=0;j<channel.size();j++){
				run(channel[j], tag[k], sample[i],Reco,ZGbin);
			}
		}
	}

	return 0;
} 
