void run(TString sample,TString tag){
        fstream ftxt("./jes_uncer"+tag+".txt", ios::app );
	ofstream f1("./"+sample+"_jes_uncer"+tag+".txt");
	TFile*file;TFile*file1;TFile*file2;
	if(sample.Contains("ZA")&&sample.Contains("out")==0){
		file = new TFile("./hist_ZA_jes"+tag+".root");
		file1 = new TFile("../hist_ZA-EWK_jes"+tag+".root");
		file2 = new TFile("./hist_ZA_interf_jes"+tag+".root");
	}
	else if(sample.Contains("ZA")&&sample.Contains("out")){
		file = new TFile("./hist_ZAout_jes"+tag+".root");
		file1 = new TFile("../hist_ZA-EWKout_jes"+tag+".root");
		file2 = new TFile("./hist_ZA_interfout_jes"+tag+".root");
	}
        else file=new TFile("../hist_"+sample+"_jes"+tag+".root");
	TH1D* h1 = (TH1D*)file->Get("hist_0");
	TH1D* h2 = (TH1D*)file->Get("hist_1");
	TH1D* h3 = (TH1D*)file->Get("hist_2");
	if(sample.Contains("ZA")){
		TH1D* hh1 = (TH1D*)file1->Get("hist_0");
		TH1D* hh2 = (TH1D*)file1->Get("hist_1");
		TH1D* hh3 = (TH1D*)file1->Get("hist_2");
		TH1D* hhh1 = (TH1D*)file2->Get("hist_0");
		TH1D* hhh2 = (TH1D*)file2->Get("hist_1");
		TH1D* hhh3 = (TH1D*)file2->Get("hist_2");
		h1->Add(hh1);h2->Add(hh2);h3->Add(hh3);
		h1->Add(hhh1);h2->Add(hhh2);h3->Add(hhh3);
	}
	const int kk =h1->GetNbinsX();
	const int num = kk-2;
	h1->SetBinContent(kk-2,h1->GetBinContent(kk-2)+h1->GetBinContent(kk-1)+h1->GetBinContent(kk));
	h2->SetBinContent(kk-2,h2->GetBinContent(kk-2)+h2->GetBinContent(kk-1)+h2->GetBinContent(kk));
	h3->SetBinContent(kk-2,h3->GetBinContent(kk-2)+h3->GetBinContent(kk-1)+h3->GetBinContent(kk));
	Double_t bincontent_new[num],bincontent_up[num],bincontent_down[num];
	Double_t uncer[num];
	cout<<sample<<" "<<tag<<" uncertainty ";
	f1<<"jes_"<<sample<<"=[";
	ftxt<<"jes"<<tag<<"_"<<sample<<"=[";
	for(Int_t i=0;i<num;i++){
		bincontent_new[i] = h1->GetBinContent(i+1);
		bincontent_up[i] = h2->GetBinContent(i+1);
		bincontent_down[i] = h3->GetBinContent(i+1);
		double max;
		if(fabs(bincontent_up[i]-bincontent_new[i])>fabs(bincontent_down[i]-bincontent_new[i]))
			max=fabs(bincontent_up[i]-bincontent_new[i]);
		else
			max=fabs(bincontent_down[i]-bincontent_new[i]);
		if(bincontent_new[i]<=0||h1->GetSum()==0) uncer[i] =0;
		else{
			if(sample.Contains("ZA")){
				uncer[i] = max/bincontent_new[i];
			}
			else uncer[i]=std::max( fabs(h2->GetSum()-h1->GetSum()),fabs(h3->GetSum()-h1->GetSum()) )/h1->GetSum();
		}
		cout<<fixed<<setprecision(2)<<1+uncer[i]<<",";
		f1<<fixed<<setprecision(2)<<uncer[i]+1<<",";
		if(i<num-1)ftxt<<fixed<<setprecision(2)<<uncer[i]+1<<",";
		if(i==num-1) {
			f1<<uncer[i]+1<<"]"<<endl;
			ftxt<<fixed<<setprecision(2)<<uncer[i]+1<<"]"<<endl;
		}
	}
	cout<<endl;
	ftxt.close();
}
int uncer_jesr(){
	vector<TString> sample={"ZA","TTA","VV","ST","ZAout"};
	vector<TString> genvars={"ptlep1","photonet","jet1pt","Mva","Mjj"};
	for(int j=0;j<sample.size();j++){
		run(sample[j],"16");
		run(sample[j],"17");
		run(sample[j],"18");
	}
	return 1;
}
