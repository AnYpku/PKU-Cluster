void count(){
	Double_t fakerate[8];
	Double_t lowpt[8]= {20,25,30,35,40,50,60,100};
	Double_t highpt[8]={25,30,35,40,50,60,100,400};
	Double_t bin_data[8],bin_plj[8],bin_za[8],bin_ew[8];
	Double_t weight[8];
	TFile* f1 = new TFile("./cutla-outplj_h.root");
	TFile* f2 = new TFile("./cutla-outDMuon_h.root");
	TFile* f3 = new TFile("./cutla-outZA_plj_h.root");
	TFile* f4 = new TFile("./cutla-outZA-EWK_plj_h.root");

	TH1F* h1 = (TH1F*)f1->Get("h_outplj");
	TH1F* h2 = (TH1F*)f2->Get("h_outDMuon");
	TH1D* h3 = (TH1D*)f3->Get("h_outZA_plj");
	TH1D* h4 = (TH1D*)f4->Get("h_outZA-EWK_plj");
	for(Int_t i=0;i<8;i++){
		bin_data[i]=h2->GetBinContent(i+1);
		bin_plj[i] =h1->GetBinContent(i+1);
		bin_za[i] = 35.86*h3->GetBinContent(i+1);
		bin_ew[i] = 35.86*h4->GetBinContent(i+1);
	}
	for(Int_t i=0;i<8;i++){
		const char *name[8]={"20~25","25~30","30~35","35~40","40~50","50~60","60~100","100~400"};
		cout<<"bin "<<name[i]<<" ;"<<fixed<<setprecision(0)<<"data : "<<bin_data[i]<<"; plj : "<<bin_plj[i]<<fixed<<setprecision(2)<<"; za contamination "<<bin_za[i]<<"; EW contamination : "<<bin_ew[i]<<endl;
	}
}

