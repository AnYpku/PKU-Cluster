void run(TString sample,TString tag){
        fstream ftxt("./jes_uncer"+tag+".txt", ios::app );
	ifstream f1("./"+sample+"_jes_uncer"+tag+".txt");
	TFile*file1;TFile*file2;TFile*file3;
	if(sample.Contains("WA")==0){
		if(sample.Contains("EWK")){
			file1 = new TFile("./root/hist_16outJEC_"+sample+"_jes16.root");
			file2 = new TFile("./root/hist_17outJEC_"+sample+"_jes17.root");
			file3 = new TFile("./root/hist_18outJEC_"+sample+"_jes18.root");
		}
		else{
			file1=new TFile("./root/hist_"+sample+"_jes16.root");
			file2=new TFile("./root/hist_"+sample+"_jes17.root");
			file3=new TFile("./root/hist_"+sample+"_jes18.root");
		}
	}
	TH1D* h11 = (TH1D*)file1->Get("hist_0");TH1D* h12 = (TH1D*)file2->Get("hist_0");TH1D* h13 = (TH1D*)file3->Get("hist_0");
	TH1D* h21 = (TH1D*)file1->Get("hist_1");TH1D* h22 = (TH1D*)file2->Get("hist_1");TH1D* h23 = (TH1D*)file3->Get("hist_1");
	TH1D* h31 = (TH1D*)file1->Get("hist_2");TH1D* h32 = (TH1D*)file2->Get("hist_2");TH1D* h33 = (TH1D*)file3->Get("hist_2");
	TH1D*h1=(TH1D*)h11->Clone();TH1D*h2=(TH1D*)h21->Clone();TH1D*h3=(TH1D*)h31->Clone();
	h1->Add(h12,1);h1->Add(h13,1);
	h2->Add(h22,1);h2->Add(h23,1);
	h3->Add(h32,1);h3->Add(h33,1);
	const int num=h1->GetNbinsX();
	Double_t uncer[num],factor[num];
	for(int i=0;i<num;i++){
		f1>>uncer[i];
		cout<<sample<<" uncertainty "<<uncer[i]<<endl;
	}
	ftxt<<"jes"<<tag<<"_"<<sample<<"=[";
	for(Int_t i=0;i<num;i++){
		if(sample.Contains("WA")==0){
			if(sample.Contains("ZA")){
				if(tag.Contains("16")){
					factor[i]=h11->GetBinContent(i+1)/h1->GetBinContent(i+1);
				}
				if(tag.Contains("17")){
					factor[i]=h12->GetBinContent(i+1)/h1->GetBinContent(i+1);
				}
				if(tag.Contains("18")){
					factor[i]=h13->GetBinContent(i+1)/h1->GetBinContent(i+1);
				}
			}
			else{
				if(tag.Contains("16")) factor[i]=h11->GetSum()/h1->GetSum();
				if(tag.Contains("17")) factor[i]=h12->GetSum()/h1->GetSum();
				if(tag.Contains("18")) factor[i]=h13->GetSum()/h1->GetSum();
			}
		}
		else factor[i]=0;
		cout<<sample<<tag<<" "<<uncer[i]<<" "<<factor[i]<<endl;
		uncer[i]=uncer[i]*factor[i];
		if(i<num-1)ftxt<<fixed<<setprecision(3)<<1+uncer[i]<<",";
		else ftxt<<fixed<<setprecision(3)<<1+uncer[i]<<"]"<<endl;
	}
	cout<<endl;
	ftxt.close();
}
int generate_frac(){
	vector<TString> sample={"ZA","ZA-EWK","TTA","VV","ST","WA"};
	vector<TString> genvars={"ptlep1","photonet","jet1pt","Mva","Mjj"};
	for(int j=0;j<sample.size();j++){
		run(sample[j],"16");
		run(sample[j],"17");
		run(sample[j],"18");
	}
	return 1;
}
