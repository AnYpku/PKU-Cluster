void run(TString var,TString sample,TString tag){
        fstream ftxt("./"+var+"_jer_uncer"+tag+"CR.txt", ios::app );
	ofstream f1("./"+var+"_"+sample+"_jer_uncer"+tag+"CR.txt");
	TFile*file;
	if(sample.Contains("EWK"))
		file = new TFile("./root/unfold_"+tag+"JESR_ZA-EWK"+tag+"_"+var+"_jer"+tag+".root");
        else file=new TFile("./root/unfold_"+sample+"_"+var+"_jer"+tag+".root");
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
	cout<<"uncertainty ";
	f1<<"jer_"<<sample<<"=[";
	ftxt<<"jer"<<tag<<"_"<<sample<<"=[";
		 for(Int_t i=0;i<num;i++){
			 bincontent_new[i] = h1->GetBinContent(i+1);
			 bincontent_up[i] = h2->GetBinContent(i+1);
			 bincontent_down[i] = h3->GetBinContent(i+1);
                         if(bincontent_new[i]<=0) uncer[i] =0;
			 else
				 uncer[i] = fabs(bincontent_up[i]-bincontent_down[i])/2/bincontent_new[i];
			 cout<<fixed<<setprecision(2)<<1+uncer[i]<<",";
			 f1<<fixed<<setprecision(2)<<uncer[i]+1<<",";
			 if(i<num-1)ftxt<<fixed<<setprecision(2)<<uncer[i]+1<<",";
			 if(i==num-1) {
				 f1<<uncer[i]+1<<"]"<<endl;
				 ftxt<<fixed<<setprecision(2)<<uncer[i]+1<<"]"<<endl;
			 }
		 }
		 cout<<endl;
		 ftxt.close();
}
int uncer_jesr(){
     vector<TString> sample={"ZA","ZA-EWK","TTA","VV","ST"};
     vector<TString> genvars={"ptlep1","photonet","jet1pt","Mjj"};
     for(int i=0;i<genvars.size();i++){
        for(int j=0;j<sample.size();j++){
		run(genvars[i],sample[j],"16");
		run(genvars[i],sample[j],"17");
		run(genvars[i],sample[j],"18");
	}
     }
return 1;
}
