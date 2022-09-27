void get_interf(TString tag){
	ofstream f1("./interf_uncer"+tag+".txt");
	TFile* file1 = new TFile("./hist-EWK_"+tag+".root");
	TFile* file2 = new TFile("./hist_interf_"+tag+".root");
	TH1D* h1 = (TH1D*)file1->Get("hist-EWK");
	TH1D* h2 = (TH1D*)file2->Get("hist_interf");
        const int num=h1->GetNbinsX()-2;
        const int kk=h1->GetNbinsX(); 
        h1->SetBinContent(kk-2,h1->GetBinContent(kk-2)+h1->GetBinContent(kk-1)+h1->GetBinContent(kk));
        h2->SetBinContent(kk-2,h2->GetBinContent(kk-2)+h2->GetBinContent(kk-1)+h2->GetBinContent(kk));
	Double_t bincontent1[num],bincontent2[num];
	Double_t uncer[num];
        f1<<"interf"<<tag<<"=[";
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
	vector<TString> tag={"16","17","18"};
	for(int i=0;i<tag.size();i++){
		get_interf(tag[i]);
	}
	return 0;
}
