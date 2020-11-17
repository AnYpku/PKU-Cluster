void run(TString channel,TString tag){
	ofstream f1("./fake_uncer_"+channel+"_"+tag+"CR.txt");
	TFile* file = new TFile("./hist_plj_"+channel+"_"+tag+"CR.root");
	TH1D* h1 = (TH1D*)file->Get("hist");
	TH1D* h2 = (TH1D*)file->Get("hist_up");
	TH1D* h3 = (TH1D*)file->Get("hist_down");

/*	
	ofstream f1("./Uncertainty_2.txt");
 	TFile* file = new TFile("./output.root");
	TH1D* h1 = (TH1D*)file->Get("mjj_new");
	TH1D* h2 = (TH1D*)file->Get("mjj_JEC_up");
	TH1D* h3 = (TH1D*)file->Get("mjj_JEC_down");
*/
	const int num =h1->GetNbinsX();
//        h1->SetBinContent(kk-2,h1->GetBinContent(kk-2)+h1->GetBinContent(kk-1)+h1->GetBinContent(kk));
//        h2->SetBinContent(kk-2,h2->GetBinContent(kk-2)+h2->GetBinContent(kk-1)+h2->GetBinContent(kk));
//        h3->SetBinContent(kk-2,h3->GetBinContent(kk-2)+h3->GetBinContent(kk-1)+h3->GetBinContent(kk));
	Double_t bincontent_new[num],bincontent_up[num],bincontent_down[num];
	Double_t uncer[num];
        if(tag.Contains("16"))
		f1<<"fake16=[";
        if(tag.Contains("17"))
		f1<<"fake17=[";
        if(tag.Contains("18"))
		f1<<"fake18=[";
	cout<<"uncertainty ";
		 for(Int_t i=0;i<num;i++){
			 bincontent_new[i] = h1->GetBinContent(i+1);
			 bincontent_up[i] = h2->GetBinContent(i+1);
			 bincontent_down[i] = h3->GetBinContent(i+1);
                         if(bincontent_new[i]==0) uncer[i] =0;
			 else
				 uncer[i] = fabs(bincontent_up[i]-bincontent_down[i])/2/bincontent_new[i];
			 cout<<fixed<<setprecision(2)<<1+uncer[i]<<",";
			 if(i<num-1)f1<<fixed<<setprecision(3)<<uncer[i]+1<<",";
			 if(i==num-1) f1<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
		 }
		 cout<<endl;
}
int uncer_fakephoton(){
     vector<TString> channels={"mubarrel","muendcap","elebarrel","eleendcap"};//,"Mva","Mjj"};
     vector<TString> tag={"16","17","18"};
     for(int i=0;i<channels.size();i++){
	     for(int j=0;j<tag.size();j++){
		     run(channels[i],tag[j]);
	     }
     }
return 1;
}
