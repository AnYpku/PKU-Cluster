void run_1d(TString sample,TString tag);
void run(TString sample,TString tag){
        fstream ftxt("./jes_uncer"+tag+".txt", ios::app );
	ofstream f1("./"+sample+"_jes_uncer"+tag+".txt");
	TFile*file;
	if(sample.Contains("EWK"))
		file = new TFile("./root/hist_"+sample+"_jes"+tag+".root");
        else file=new TFile("./root/hist_"+sample+"_jes"+tag+".root");
	TH1D* h1 = (TH1D*)file->Get("hist_0");
	TH1D* h2 = (TH1D*)file->Get("hist_1");
	TH1D* h3 = (TH1D*)file->Get("hist_2");
/*	
	ofstream f1("./Uncertainty_2.txt");
 	TFile* file = new TFile("./output.root");
	TH1D* h1 = (TH1D*)file->Get("mjj_new");
	TH1D* h2 = (TH1D*)file->Get("mjj_JEC_up");
	TH1D* h3 = (TH1D*)file->Get("mjj_JEC_down");
*/
	const int kk =h1->GetNbinsX();
        const int num = kk-2;
	h1->SetBinContent(kk-2,h1->GetBinContent(kk-2)+h1->GetBinContent(kk-1)+h1->GetBinContent(kk));
	h2->SetBinContent(kk-2,h2->GetBinContent(kk-2)+h2->GetBinContent(kk-1)+h2->GetBinContent(kk));
	h3->SetBinContent(kk-2,h3->GetBinContent(kk-2)+h3->GetBinContent(kk-1)+h3->GetBinContent(kk));
	Double_t bincontent_new[num],bincontent_up[num],bincontent_down[num];
	Double_t uncer[num];
	cout<<sample<<" "<<tag<<" uncertainty ";
	f1<<"jes_"<<sample<<"=[";
	ftxt<<"jes"<<tag<<"_"<<sample<<"=[";
		 for(Int_t i=0;i<num;i++){
			 bincontent_new[i] = h1->GetBinContent(i+1);
			 bincontent_up[i] = h2->GetBinContent(i+1);
			 bincontent_down[i] = h3->GetBinContent(i+1);
			 double max;
                         if(fabs(bincontent_up[i]-bincontent_new[i])>fabs(bincontent_down[i]-bincontent_new[i]))
				 max=fabs(bincontent_up[i]-bincontent_new[i]);
			 else
				 max=fabs(bincontent_down[i]-bincontent_new[i]);
			 if(bincontent_new[i]<=0||h1->GetSum()==0) uncer[i] =0;
			 else{
				 if(sample.Contains("ZA")){
					 uncer[i] = max/bincontent_new[i];
				 }
				 else uncer[i]=std::max( fabs(h2->GetSum()-h1->GetSum()),fabs(h3->GetSum()-h1->GetSum()) )/h1->GetSum();
			 }
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
     vector<TString> sample={"ZA","ZA-EWK","ZA-EWKout","TTA","VV","ST"};
     vector<TString> genvars={"ptlep1","photonet","jet1pt","Mva","Mjj"};
     for(int j=0;j<sample.size();j++){
	     run(sample[j],"16");
	     run(sample[j],"17");
	     run(sample[j],"18");
//           run_1d(sample[j],"16");
//           run_1d(sample[j],"17");
//           run_1d(sample[j],"18");
     }
     return 1;
}
void run_1d(TString sample,TString tag){
        fstream ftxt("./jes_1duncer"+tag+".txt", ios::app );
        ofstream f1("./"+sample+"_jes_1duncer"+tag+".txt");
        TFile*file;
        if(sample.Contains("EWK"))
                file = new TFile("./root/hist_"+tag+"outJEC_"+sample+"_jes"+tag+".root");
        else file=new TFile("./root/hist_"+sample+"_jes"+tag+".root");
        TH1D* h1 = (TH1D*)file->Get("hist_0");
        TH1D* h2 = (TH1D*)file->Get("hist_1");
        TH1D* h3 = (TH1D*)file->Get("hist_2");
        const int num=3;
        Double_t bincontent_new[num],bincontent_up[num],bincontent_down[num];
        Double_t uncer[num];
        f1<<"jes_"<<sample<<"=[";
        ftxt<<"jes"<<tag<<"_"<<sample<<"=[";
        for(int i=0;i<num;i++){
                bincontent_new[i]=h1->GetBinContent(3*i+1)+h1->GetBinContent(3*i+2)+h1->GetBinContent(3*i+3); 
                bincontent_up[i]=h2->GetBinContent(3*i+1)+h2->GetBinContent(3*i+2)+h2->GetBinContent(3*i+3);  
                bincontent_down[i]=h3->GetBinContent(3*i+1)+h3->GetBinContent(3*i+2)+h3->GetBinContent(3*i+3);
                double max;
                if(fabs(bincontent_up[i]-bincontent_new[i])>fabs(bincontent_down[i]-bincontent_new[i]))       
                        max=fabs(bincontent_up[i]-bincontent_new[i]);
                else
                        max=fabs(bincontent_down[i]-bincontent_new[i]);
                if(bincontent_new[i]<=0||h1->GetSum()==0) uncer[i] =0;
                else{
                        if(sample.Contains("ZA")){
                                uncer[i] = max/bincontent_new[i];
                        }
                        else uncer[i]=std::max( fabs(h2->GetSum()-h1->GetSum()),fabs(h3->GetSum()-h1->GetSum()) )/h1->GetSum();
                }
                cout<<fixed<<setprecision(2)<<1+uncer[i]<<",";
                f1<<fixed<<setprecision(2)<<uncer[i]+1<<","<<uncer[i]+1<<","<<uncer[i]+1<<",";
                if(i<num-1)ftxt<<fixed<<setprecision(2)<<uncer[i]+1<<","<<uncer[i]+1<<","<<uncer[i]+1<<",";
                if(i==num-1) {
                        f1<<uncer[i]+1<<"]"<<endl;
                        ftxt<<fixed<<setprecision(2)<<uncer[i]+1<<"]"<<endl;
                }
        }
        cout<<endl;
        ftxt.close();
}
