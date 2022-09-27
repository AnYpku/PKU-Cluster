void run(TString tag,TString sample){
	ofstream f1("./txt/pu_uncer_"+sample+"_"+tag+"CR.txt");
	ofstream ftxt("./pu_uncer_"+tag+"CR.txt",ios::app);
	TFile* file = new TFile("./root/hist_"+sample+"_pileup_"+tag+".root");
	TH1D* h1 = (TH1D*)file->Get("hist_0");
	TH1D* h2 = (TH1D*)file->Get("hist_1");
	TH1D* h3 = (TH1D*)file->Get("hist_2");
        if(sample.Contains("ZA")&&sample.Contains("EWK")==0){
                TFile* f2 = new TFile("./root/hist_ZA_interf_pileup_"+tag+".root");
                TH1D* hh1 = (TH1D*)f2->Get("hist_0");
                TH1D* hh2 = (TH1D*)f2->Get("hist_1");
                TH1D* hh3 = (TH1D*)f2->Get("hist_2");
                h1->Add(hh1);h2->Add(hh2);h3->Add(hh3);
        }

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
	vector<TString> channels={"mubarrel","muendcap","elebarrel","eleendcap"};
	vector<TString> tag={"16","17","18"};
	vector<TString> sample={"ZA","ZA-EWK","TTA","VV","ST"};
	for(int j=0;j<tag.size();j++){
		for(int k=0;k<sample.size();k++){
			run(tag[j],sample[k]);
		}
	}
	return 1;
}
