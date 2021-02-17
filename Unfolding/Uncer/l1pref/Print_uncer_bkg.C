void run(TString var,TString sample,TString tag){
	ofstream f1("./"+var+"_l1pref"+tag+"_uncer.txt",ios::app);
	TFile* file = new TFile("./root/unfold_"+var+"_"+sample+"_pref"+tag+".root");
	TH1D* h1 = (TH1D*)file->Get(var+"_0");
	TH1D* h2 = (TH1D*)file->Get(var+"_1");
	TH1D* h3 = (TH1D*)file->Get(var+"_2");

/*	
	ofstream f1("./Uncertainty_2.txt");
 	TFile* file = new TFile("./output.root");
	TH1D* h1 = (TH1D*)file->Get("mjj_new");
	TH1D* h2 = (TH1D*)file->Get("mjj_JEC_up");
	TH1D* h3 = (TH1D*)file->Get("mjj_JEC_down");
*/
	const int num =h1->GetNbinsX();
        for(int i=0;i<num;i++){
           h1->SetBinContent(num,h1->GetBinContent(num)+h1->GetBinContent(num+1));
           h2->SetBinContent(num,h2->GetBinContent(num)+h2->GetBinContent(num+1));
           h3->SetBinContent(num,h3->GetBinContent(num)+h3->GetBinContent(num+1));
        }//add over flow
	Double_t bincontent_new[num],bincontent_up[num],bincontent_down[num];
	Double_t uncer[num];
	cout<<var<<" "<<tag<<" uncertainty ";
	f1<<"l1pref_"<<sample<<"=[";
		 for(Int_t i=0;i<num;i++){
			 bincontent_new[i] = h1->GetBinContent(i+1);
			 bincontent_up[i] = h2->GetBinContent(i+1);
			 bincontent_down[i] = h3->GetBinContent(i+1);
                         if(bincontent_new[i]==0) uncer[i] =0;
			 else
				 uncer[i] = fabs(bincontent_up[i]-bincontent_down[i])/2/bincontent_new[i];
			 cout<<fixed<<setprecision(2)<<1+uncer[i]<<",";
			 if(i<num-1)f1<<fixed<<setprecision(2)<<uncer[i]+1<<",";
			 if(i==num-1) f1<<fixed<<setprecision(2)<<uncer[i]+1<<"]"<<endl;
		 }
		 cout<<endl;
}
int Print_uncer_bkg(){
     vector<TString> genvars={"ptlep1","photonet","jet1pt","Mjj"};
     vector<TString> sample={"ZA","ZA-EWK","TTA","VV","ST"};
     for(int i=0;i<genvars.size();i++){
	     for(int k=0;k<sample.size();k++){
		     run(genvars[i],sample[k],"16");
		     run(genvars[i],sample[k],"17");
	     }
     }
     return 1;
}
