void run_year(TString sample,TString tag){
	ofstream f1("./"+sample+"_jes_uncer"+tag+".txt");
        fstream ftxt("./jes_uncer"+tag+".txt", ios::app );
	TFile*file;
	file = new TFile("./root/hist_"+sample+"_jes"+tag+".root");
	TH1D* h1 = (TH1D*)file->Get("hist_0");
	TH1D* h2 = (TH1D*)file->Get("hist_1");
	TH1D* h3 = (TH1D*)file->Get("hist_2");
	const int num = h1->GetNbinsX();
	Double_t bincontent_new[num],bincontent_up[num],bincontent_down[num];
	Double_t uncer[num];
	cout<<sample<<" 20"<<tag<<" uncertainty ";
	f1<<"jes_"<<sample<<tag<<"=[";
        ftxt<<"jes"<<tag<<"_"<<sample<<"=[";
//	ftxt<<"jes"<<tag<<"_"<<sample<<"=[";
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
		cout<<fixed<<setprecision(2)<<uncer[i]<<",";
		if(i<num-1){
			f1<<fixed<<setprecision(3)<<1+uncer[i]<<",";
			ftxt<<fixed<<setprecision(3)<<1+uncer[i]<<",";
		}
		if(i==num-1){
			f1<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
			ftxt<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
		}
	}
	cout<<endl;
}
void run(TString sample){
	ofstream f1("./"+sample+"_jes_uncer.txt");
	fstream ftxt("./jes_uncer.txt", ios::app );
	TFile*file1 = new TFile("./root/hist_"+sample+"_jes16.root");
	TFile*file2 = new TFile("./root/hist_"+sample+"_jes17.root");
	TFile*file3 = new TFile("./root/hist_"+sample+"_jes18.root");
	TH1D* h1[3];TH1D*h2[3];TH1D*h3[3];
        TH1D*hist1;TH1D*hist2;TH1D*hist3;
	for(int i=0;i<3;i++){
		h1[i]= (TH1D*)file1->Get(Form("hist_%d",i));
		h2[i]= (TH1D*)file2->Get(Form("hist_%d",i));
		h3[i]= (TH1D*)file3->Get(Form("hist_%d",i));
	}
	hist1=(TH1D*)h1[0]->Clone();hist1->Add(h2[0]);hist1->Add(h3[0]);//central
	hist2=(TH1D*)h1[1]->Clone();hist2->Add(h2[1]);hist2->Add(h3[1]);//up
	hist3=(TH1D*)h1[2]->Clone();hist3->Add(h2[2]);hist3->Add(h3[2]);//down
        const int num = hist1->GetNbinsX();
        Double_t bincontent_new[num],bincontent_up[num],bincontent_down[num];
        Double_t uncer[num];
        f1<<"jes_"<<sample<<"=[";
        ftxt<<"jes_"<<sample<<"=[";
        cout<<sample<<" combined uncertainty ";
	for(int i=0;i<num;i++){
		bincontent_new[i] = hist1->GetBinContent(i+1);
		bincontent_up[i] = hist2->GetBinContent(i+1);
		bincontent_down[i] = hist3->GetBinContent(i+1);
		double max;
		if(fabs(bincontent_up[i]-bincontent_new[i])>fabs(bincontent_down[i]-bincontent_new[i]))
			max=fabs(bincontent_up[i]-bincontent_new[i]);
		else
			max=fabs(bincontent_down[i]-bincontent_new[i]);
		if(bincontent_new[i]<=0||hist1->GetSum()==0) uncer[i] =0;
		else{
			if(sample.Contains("ZA")){
				uncer[i] = max/bincontent_new[i];
			}
			else uncer[i]=std::max( fabs(hist2->GetSum()-hist1->GetSum()),fabs(hist3->GetSum()-hist1->GetSum()) )/hist1->GetSum();
		}
		cout<<fixed<<setprecision(2)<<uncer[i]<<",";
                if(i<num-1){
			f1<<fixed<<setprecision(3)<<1+uncer[i]<<",";
			ftxt<<fixed<<setprecision(3)<<1+uncer[i]<<",";
		}
                if(i==num-1){
			f1<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
			ftxt<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
		}
	}




}
int uncer_jesr(){
	vector<TString> sample={"ZA","ZA-EWK","TTA","VV","ST"};
	vector<TString> tag={"16","17","18"};
	for(int j=0;j<sample.size();j++){
		run(sample[j]);
		cout<<endl;
		for(int i=0;i<tag.size();i++){
			run_year(sample[j],tag[i]);
		}
	}
	return 1;
}
