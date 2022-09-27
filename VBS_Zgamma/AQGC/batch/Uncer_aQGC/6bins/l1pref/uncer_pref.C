void run_year(TString channel,TString tag,TString sample);
void run(TString channel,TString sample){
	ofstream f1("./l1pref_uncer_"+channel+".txt",ios::app);
	TFile* file1 = new TFile("./hist_"+sample+"_pref_16"+channel+".root");
	TFile* file2 = new TFile("./hist_"+sample+"_pref_17"+channel+".root");
	TFile* file3 = new TFile("./hist_"+sample+"_pref_18"+channel+".root");
	TH1D* h11 = (TH1D*)file1->Get("hist_0");TH1D* h12 = (TH1D*)file2->Get("hist_0");TH1D* h13 = (TH1D*)file3->Get("hist_0");
	TH1D* h21 = (TH1D*)file1->Get("hist_1");TH1D* h22 = (TH1D*)file2->Get("hist_1");TH1D* h23 = (TH1D*)file3->Get("hist_1");
	TH1D* h31 = (TH1D*)file1->Get("hist_2");TH1D* h32 = (TH1D*)file2->Get("hist_2");TH1D* h33 = (TH1D*)file3->Get("hist_2");
        TH1D*h1=(TH1D*)h11->Clone();
        TH1D*h2=(TH1D*)h21->Clone();
        TH1D*h3=(TH1D*)h31->Clone();
        h1->Add(h12,1);//sum of 16 and 17 for central histo
        h2->Add(h22,1);//sum of 16 and 17 for up histo
        h3->Add(h32,1);// sum of 16 and 17 for down histo

	const int num =h1->GetNbinsX();
	Double_t bincontent_new[num],bincontent_up[num],bincontent_down[num];
	Double_t uncer[num];
	f1<<"l1pref_"<<sample<<"=[";
	cout<<channel<<" combined uncertainty in "<<channel<<" ";
		 for(Int_t i=0;i<num;i++){
			 bincontent_new[i]  = h1->GetBinContent(i+1);
			 bincontent_up[i]   = h2->GetBinContent(i+1);
			 bincontent_down[i] = h3->GetBinContent(i+1);

                         if(bincontent_new[i]<=0) uncer[i] =0;
			 else{
				 double factor;
				 factor=h1->GetBinContent(i+1)/(h1->GetBinContent(i+1)+h13->GetBinContent(i+1));
				 uncer[i] = fabs(bincontent_up[i]-bincontent_down[i])/2/bincontent_new[i]*factor;
			 }
			 if(uncer[i]<0) uncer[i]=0;
			 cout<<fixed<<setprecision(3)<<1+uncer[i]<<" ";
			 if(i<num-1)f1<<fixed<<setprecision(3)<<uncer[i]+1<<",";
			 if(i==num-1) f1<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
		 }
		 cout<<endl;
}
int uncer_pref(){
     vector<TString> channels={"mu","ele",""};//,"Mva","Mjj";
     vector<TString> tag={"16","17"};
     vector<TString> sample={"ZA-EWK","ZA","others"};
     for(int k=0;k<sample.size();k++){
	     for(int i=0;i<channels.size();i++){
		     run(channels[i],sample[k]);
		     for(int j=0;j<tag.size();j++){
			     run_year(channels[i],tag[j],sample[k]);
		     }
	     }
     }
     return 1;
}
void run_year(TString channel,TString tag,TString sample){
	ofstream f1("./l1pref_uncer_"+channel+tag+".txt",ios::app);
	TFile* file1 = new TFile("./hist_"+sample+"_pref_"+tag+channel+".root");
	TH1D* h11 = (TH1D*)file1->Get("hist_0");
	TH1D* h21 = (TH1D*)file1->Get("hist_1");
	TH1D* h31 = (TH1D*)file1->Get("hist_2");
	TH1D*h1=(TH1D*)h11->Clone();
	TH1D*h2=(TH1D*)h21->Clone();
	TH1D*h3=(TH1D*)h31->Clone();

	const int num =h1->GetNbinsX();
	Double_t bincontent_new[num],bincontent_up[num],bincontent_down[num];
	Double_t uncer[num];
	f1<<"l1pref_"<<sample<<"=[";
	cout<<channel<<" "<<tag<<" uncertainty in "<<channel<<" ";
	for(Int_t i=0;i<num;i++){
		bincontent_new[i]  = h1->GetBinContent(i+1);
		bincontent_up[i]   = h2->GetBinContent(i+1);
		bincontent_down[i] = h3->GetBinContent(i+1);

		if(bincontent_new[i]<=0) uncer[i] =0;
		else
			uncer[i] = fabs(bincontent_up[i]-bincontent_down[i])/2/bincontent_new[i];
		cout<<fixed<<setprecision(3)<<1+uncer[i]<<" ";
		if(i<num-1)f1<<fixed<<setprecision(3)<<uncer[i]+1<<",";
		if(i==num-1) f1<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
	}
	cout<<endl;
}
