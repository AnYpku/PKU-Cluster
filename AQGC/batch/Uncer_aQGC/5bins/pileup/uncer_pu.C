void run_combine(TString sample);
void run(TString tag,TString sample){
	ofstream f1("./txt/pu_uncer_"+sample+"_"+tag+".txt");
	ofstream ftxt("./pu_uncer"+tag+".txt",ios::app);
	TFile* file = new TFile("./root/hist_"+sample+"_pileup_"+tag+".root");
	TH1D* h1 = (TH1D*)file->Get("hist_0");
	TH1D* h2 = (TH1D*)file->Get("hist_1");
	TH1D* h3 = (TH1D*)file->Get("hist_2");

	const int num =h1->GetNbinsX();
        const int kk =h1->GetNbinsX();
	Double_t bincontent_new[num],bincontent_up[num],bincontent_down[num];
	Double_t uncer[num];
        if(tag.Contains("16")){
		f1<<"pu16=[";
		ftxt<<"pu_"<<sample<<"=[";
	}
        if(tag.Contains("17")){
		f1<<"pu17=[";
		ftxt<<"pu_"<<sample<<"=[";
	}
        if(tag.Contains("18")){
		f1<<"pu18=[";
		ftxt<<"pu_"<<sample<<"=[";
	}
	cout<<tag<<" "<<" "<<sample<<" uncertainty ";
		 for(Int_t i=0;i<num;i++){
			 bincontent_new[i] = h1->GetBinContent(i+1);
			 bincontent_up[i] = h2->GetBinContent(i+1);
			 bincontent_down[i] = h3->GetBinContent(i+1);
			 if(bincontent_new[i]<=0) uncer[i] =0;
			 else
				 uncer[i] = fabs(bincontent_up[i]-bincontent_down[i])/2/bincontent_new[i];
			 cout<<fixed<<setprecision(3)<<1+uncer[i]<<",";
			 if(i<num-1){
				 f1<<fixed<<setprecision(3)<<uncer[i]+1<<",";
				 ftxt<<fixed<<setprecision(3)<<uncer[i]+1<<",";
			 }
			 if(i==num-1){
				 f1<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
				 ftxt<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
			 }
		 }
		 cout<<endl;
}
int uncer_pu(){
	vector<TString> tag={"16","17","18"};
	vector<TString> sample={"ZA","ZA-EWK","others"};
	for(int k=0;k<sample.size();k++){
		run_combine(sample[k]);
		for(int j=0;j<tag.size();j++){
			run(tag[j],sample[k]);
		}
	}
	return 1;
}
void run_combine(TString sample) {
	ofstream f1("./txt/pu_uncer_"+sample+".txt");
	ofstream ftxt("./pu_uncer.txt",ios::app);
	TFile* file = new TFile("./root/hist_"+sample+"_pileup_16.root");
	TFile* file1 = new TFile("./root/hist_"+sample+"_pileup_17.root");
	TFile* file2 = new TFile("./root/hist_"+sample+"_pileup_18.root");
	TH1D* h1 = (TH1D*)file->Get("hist_0");
	TH1D* h2 = (TH1D*)file->Get("hist_1");
	TH1D* h3 = (TH1D*)file->Get("hist_2");
	TH1D* h11 = (TH1D*)file1->Get("hist_0");
	TH1D* h12 = (TH1D*)file1->Get("hist_1");
	TH1D* h13 = (TH1D*)file1->Get("hist_2");
	TH1D* h21 = (TH1D*)file2->Get("hist_0");
	TH1D* h22 = (TH1D*)file2->Get("hist_1");
	TH1D* h23 = (TH1D*)file2->Get("hist_2");
	h1->Add(h11,1);h1->Add(h21,1);
	h2->Add(h12,1);h2->Add(h22,1);
	h3->Add(h13,1);h3->Add(h23,1);
	const int num =h1->GetNbinsX();
	const int kk =h1->GetNbinsX();
	Double_t bincontent_new[num],bincontent_up[num],bincontent_down[num];
	Double_t uncer[num];
	f1<<"pu=[";
	ftxt<<"pu_"<<sample<<"=[";
	cout<<" "<<" "<<sample<<" uncertainty ";
	for(Int_t i=0;i<num;i++){
		bincontent_new[i] = h1->GetBinContent(i+1);
		bincontent_up[i] = h2->GetBinContent(i+1);
		bincontent_down[i] = h3->GetBinContent(i+1);
		if(bincontent_new[i]<=0) uncer[i] =0;
		else
			uncer[i] = fabs(bincontent_up[i]-bincontent_down[i])/2/bincontent_new[i];
		cout<<fixed<<setprecision(3)<<1+uncer[i]<<",";
		if(i<num-1){
			f1<<fixed<<setprecision(3)<<uncer[i]+1<<",";
			ftxt<<fixed<<setprecision(3)<<uncer[i]+1<<",";
		}
		if(i==num-1){
			f1<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
			ftxt<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
		}
	}
	cout<<endl;
}
