void get_interf(){
	ofstream f1("./interf_uncer.txt");
	TFile* file11 = new TFile("./hist_EWK_16.root");
	TFile* file12 = new TFile("./hist_EWK_17.root");
	TFile* file13 = new TFile("./hist_EWK_18.root");
	TFile* file21 = new TFile("./hist_interference_16.root");
	TFile* file22 = new TFile("./hist_interference_17.root");
	TFile* file23 = new TFile("./hist_interference_18.root");
	TH1D* h1 = (TH1D*)file11->Get("histEWK");
	TH1D* h12 = (TH1D*)file12->Get("histEWK");
	TH1D* h13 = (TH1D*)file13->Get("histEWK");
	TH1D* h2 = (TH1D*)file21->Get("histinterference");
	TH1D* h22 = (TH1D*)file22->Get("histinterference");
	TH1D* h23 = (TH1D*)file23->Get("histinterference");
        h1->Add(h12,1);
        h1->Add(h13,1);
        h2->Add(h22,1);
        h2->Add(h23,1);
        const int num=h1->GetNbinsX();
	Double_t bincontent1[num],bincontent2[num];
	Double_t uncer[num];
        f1<<"interf"<<"=[";
	for(Int_t i=0;i<num;i++){
		bincontent1[i] = h1->GetBinContent(i+1);
		bincontent2[i] = h2->GetBinContent(i+1);
		uncer[i] = bincontent2[i]/bincontent1[i];
		cout<<fixed<<setprecision(3)<<1+uncer[i]<<",";
		if(i<num-1) f1<<fixed<<setprecision(3)<<1+uncer[i]<<",";
                if(i==num-1)f1<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
	}
	cout<<endl;
}
int uncer_interf(){
		get_interf();
	return 0;
}
