void run_year(TString channel,TString tag);
void run(TString channel){
	ofstream f1("./interf_uncer_"+channel+".txt");
	TFile* file1 = new TFile("./hist_interf_"+channel+"_16.root");
	TFile* file2 = new TFile("./hist_interf_"+channel+"_17.root");
	TFile* file3 = new TFile("./hist_interf_"+channel+"_18.root");
	TH1D* h1 = (TH1D*)file1->Get("hist_EWK");
	TH1D* h2 = (TH1D*)file1->Get("hist_EWK_interf");
	TH1D* hh1 = (TH1D*)file2->Get("hist_EWK");
	TH1D* hh2 = (TH1D*)file2->Get("hist_EWK_interf");
	TH1D* hhh1 = (TH1D*)file3->Get("hist_EWK");
	TH1D* hhh2 = (TH1D*)file3->Get("hist_EWK_interf");
        h1->Add(hh1,1);
        h1->Add(hhh1,1);
        h2->Add(hh2,1);
        h2->Add(hhh2,1);

	const int num =h1->GetNbinsX();
	Double_t bincontent_new[num],bincontent_interf[num];
	Double_t uncer[num];
	f1<<"interf=[";
	cout<<channel<<" combined uncertainty ";
		 for(Int_t i=0;i<num;i++){
			 bincontent_new[i] = h1->GetBinContent(i+1);
			 bincontent_interf[i] = h2->GetBinContent(i+1);
                         if(bincontent_new[i]<=0||bincontent_interf[i]<=0) uncer[i] =0;
			 else
				 uncer[i] = bincontent_interf[i]/bincontent_new[i];
			 cout<<fixed<<setprecision(2)<<1+uncer[i]<<",";
			 if(i<num-1)f1<<fixed<<setprecision(3)<<uncer[i]+1<<",";
			 if(i==num-1) f1<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
		 }
		 cout<<endl;
}
int uncer_interf(){
     vector<TString> channels={"mu","ele",""};//,"Mva","Mjj";
     vector<TString> tag={"16","17","18"};
     for(int i=0;i<channels.size();i++){
	     run(channels[i]);
	     for(int j=0;j<tag.size();j++){
		     run_year(channels[i],tag[j]);
	     }
     }
     return 1;
}
void run_year(TString channel,TString tag){
	ofstream f1("./interf_uncer"+tag+"_"+channel+".txt");
	TFile* file1 = new TFile("./hist_interf_"+channel+"_"+tag+".root");
	TH1D* h1 = (TH1D*)file1->Get("hist_EWK");
	TH1D* h2 = (TH1D*)file1->Get("hist_EWK_interf");

	const int num =h1->GetNbinsX();
	Double_t bincontent_new[num],bincontent_interf[num];
	Double_t uncer[num];
	f1<<"interf=[";
	cout<<channel<<" 20"<<tag<<" uncertainty ";
	for(Int_t i=0;i<num;i++){
		bincontent_new[i] = h1->GetBinContent(i+1);
		bincontent_interf[i] = h2->GetBinContent(i+1);
		if(bincontent_new[i]<=0||bincontent_interf[i]<=0) uncer[i] =0;
		else
			uncer[i] = bincontent_interf[i]/bincontent_new[i];
		cout<<fixed<<setprecision(2)<<1+uncer[i]<<",";
		if(i<num-1)f1<<fixed<<setprecision(3)<<uncer[i]+1<<",";
		if(i==num-1) f1<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
	}
	cout<<endl;
}
