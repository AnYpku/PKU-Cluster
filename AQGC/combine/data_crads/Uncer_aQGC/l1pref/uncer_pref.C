void run(TString channel ){
	ofstream f1("./l1pref_uncer_"+channel+".txt");
	TFile* file1 = new TFile("./hist_ewk_pref_16"+channel+".root");
	TFile* file2 = new TFile("./hist_ewk_pref_17"+channel+".root");
	TFile* file3 = new TFile("./hist_ewk_pref_18"+channel+".root");
	TH1D* h11 = (TH1D*)file1->Get("hist_0");TH1D* h12 = (TH1D*)file2->Get("hist_0");TH1D* h13 = (TH1D*)file3->Get("hist_0");
	TH1D* h21 = (TH1D*)file1->Get("hist_1");TH1D* h22 = (TH1D*)file2->Get("hist_1");TH1D* h23 = (TH1D*)file3->Get("hist_1");
	TH1D* h31 = (TH1D*)file1->Get("hist_2");TH1D* h32 = (TH1D*)file2->Get("hist_2");TH1D* h33 = (TH1D*)file3->Get("hist_2");
        TH1D*h1=(TH1D*)h11->Clone();
        TH1D*h2=(TH1D*)h21->Clone();
        TH1D*h3=(TH1D*)h31->Clone();
        h1->Add(h12,1); h1->Add(h13,1);
        h2->Add(h22,1); h2->Add(h23,1);

	const int num =h1->GetNbinsX();
	Double_t bincontent_new[num],bincontent_up[num],bincontent_down[num];
	Double_t uncer[num];
	f1<<"l1pref=[";
	cout<<"uncertainty in "<<channel<<" ";
		 for(Int_t i=0;i<num;i++){
			 bincontent_new[i]  = h1->GetBinContent(i+1);
			 bincontent_up[i]   = h2->GetBinContent(i+1);
			 bincontent_down[i] = h3->GetBinContent(i+1);

                         if(bincontent_new[i]==0) uncer[i] =0;
			 else
				 uncer[i] = fabs(bincontent_up[i]-bincontent_down[i])/2/bincontent_new[i]*h1->GetBinContent(i+1)/(h1->GetBinContent(i+1)+h13->GetBinContent(i+1));
			 cout<<fixed<<setprecision(3)<<1+uncer[i]<<endl;;
			 if(i<num-1)f1<<fixed<<setprecision(3)<<uncer[i]+1<<",";
			 if(i==num-1) f1<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
		 }
		 cout<<endl;
}
int uncer_pref(){
     vector<TString> channels={"mu","ele"};//,"Mva","Mjj"};
     for(int i=0;i<channels.size();i++){
		     run(channels[i]);
     }
return 1;
}
