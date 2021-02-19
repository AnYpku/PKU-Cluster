void run(TString particle,TString sample,TString type,TString tag){
//	ofstream f1("./"+var+"_"+particle+"_"+type+"_"+tag+".txt");
	ofstream f2("./"+particle+"_"+type+"_"+tag+"CR.txt",ios::app);
        TFile* file;TH1D* h1;TH1D* h2;TH1D* h3;
	file = new TFile("./root/"+particle+"_"+sample+"_"+type+tag+"CR.root");
//	cout<<particle+"_"+type+tag+".root"<<endl;
	h1 = (TH1D*)file->Get("hist_0");
	h2 = (TH1D*)file->Get("hist_1");
	h3 = (TH1D*)file->Get("hist_2");

	if(tag.Contains("16"))
		f2<<particle<<"_"<<sample<<"_"<<type<<"=[";
	if(tag.Contains("17"))
		f2<<particle<<"_"<<sample<<"_"<<type<<"=[";
	if(tag.Contains("18"))
		f2<<particle<<"_"<<sample<<"_"<<type<<"=[";
        const int num =h1->GetNbinsX();
        const int kk =h1->GetNbinsX();
        Double_t bincontent_new[num],bincontent_up[num],bincontent_down[num];
        Double_t uncer[num];
	cout<<sample<<" "<<particle<<" "<<type<<" "<<tag<<" uncertainty ";
	for(Int_t i=0;i<num;i++){
		bincontent_new[i] = h1->GetBinContent(i+1);
		bincontent_up[i] = h2->GetBinContent(i+1);
		bincontent_down[i] = h3->GetBinContent(i+1);
		if(bincontent_new[i]<=0) uncer[i] =0;
		else{
			if(sample.Contains("ZA"))
				uncer[i] = fabs(bincontent_up[i]-bincontent_down[i])/2/bincontent_new[i];
			else  uncer[i]=fabs(h2->GetSum()-h3->GetSum())/2/h1->GetSum();
		}
		if(i<num-1){
			f2<<fixed<<setprecision(3)<<1+uncer[i]<<",";
			cout<<uncer[i]<<",";
		}
		else{
			f2<<fixed<<setprecision(3)<<1+uncer[i]<<"]"<<endl;
			cout<<uncer[i]<<endl;
		}
	}
}
int uncer_lepton(){
	vector<TString> par={"ele","muon","photon"};
	vector<TString> tag={"16","17","18"};
	vector<TString> recovars={"ptlep1","photonet","jet1pt"};
	vector<TString> sample={"ZA","ZA-EWK","TTA","VV","ST"};
	for(int i=0;i<par.size();i++){
		for(int k=0;k<sample.size();k++){
			for(int j=0;j<tag.size();j++){
				if(par[i].Contains("muon")){
					run(par[i],sample[k],"all",tag[j]);
					run(par[i],sample[k],"trigger",tag[j]);
				}
				if(par[i].Contains("photon")){
					run(par[i],sample[k],"ID",tag[j]);
				}
				if(par[i].Contains("ele")){
					run(par[i],sample[k],"ID",tag[j]);
					run(par[i],sample[k],"reco",tag[j]);
				}
			}
		}
	}    
	return 1;
}
