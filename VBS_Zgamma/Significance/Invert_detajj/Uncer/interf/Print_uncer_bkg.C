void run(TString var,TString tag){
	ofstream f1("./"+var+"_interf"+tag+"_uncer.txt");
	TFile* file = new TFile("./hist_"+var+tag+".root");
	TH1D* h1 = (TH1D*)file->Get(var+"_EWK");
	TH1D* h2 = (TH1D*)file->Get(var+"_interf");

	const int num =h1->GetNbinsX();
        for(int i=0;i<num;i++){
           h1->SetBinContent(num,h1->GetBinContent(num)+h1->GetBinContent(num+1));
           h2->SetBinContent(num,h2->GetBinContent(num)+h2->GetBinContent(num+1));
        }//add over flow
	Double_t bincontent_ewk[num],bincontent_interf[num];
	Double_t uncer[num];
	cout<<var<<" "<<tag<<" uncertainty ";
	f1<<"interf=[";
		 for(Int_t i=0;i<num;i++){
			 bincontent_ewk[i] = h1->GetBinContent(i+1);
			 bincontent_interf[i] = h2->GetBinContent(i+1);
			 if( bincontent_ewk[i]==0) uncer[i] = 0;
			 else
				 uncer[i] = bincontent_interf[i]/bincontent_ewk[i];
			 cout<<fixed<<setprecision(2)<<1+uncer[i]<<",";
			 if(i<num-1)f1<<fixed<<setprecision(2)<<uncer[i]+1<<",";
			 if(i==num-1) f1<<fixed<<setprecision(2)<<uncer[i]+1<<"]"<<endl;
		 }
		 cout<<endl;
}
int Print_uncer_bkg(){
     vector<TString> recovars={"Mjj"};
     for(int i=0;i<recovars.size();i++){
	run(recovars[i],"16");
	run(recovars[i],"17");
	run(recovars[i],"18");
     }
return 1;
}
