void run(TString channel){
	ofstream f1("./fake_uncer_"+channel+".txt");
	TFile* file1 = new TFile("./hist_plj_"+channel+"_2016.root");
	TFile* file2 = new TFile("./hist_plj_"+channel+"_2017.root");
	TFile* file3 = new TFile("./hist_plj_"+channel+"_2018.root");
	TH1D* h1 = (TH1D*)file1->Get("hist");
	TH1D* h2 = (TH1D*)file1->Get("hist_up");
	TH1D* h3 = (TH1D*)file1->Get("hist_down");
	TH1D* hh1 = (TH1D*)file2->Get("hist");
	TH1D* hh2 = (TH1D*)file2->Get("hist_up");
	TH1D* hh3 = (TH1D*)file2->Get("hist_down");
	TH1D* hhh1 = (TH1D*)file3->Get("hist");
	TH1D* hhh2 = (TH1D*)file3->Get("hist_up");
	TH1D* hhh3 = (TH1D*)file3->Get("hist_down");
        h1->Add(hh1,1);
        h1->Add(hhh1,1);
        h2->Add(hh2,1);
        h2->Add(hhh2,1);
        h3->Add(hh3,1);
        h3->Add(hhh3,1);

/*	
	ofstream f1("./Uncertainty_2.txt");
 	TFile* file = new TFile("./output.root");
	TH1D* h1 = (TH1D*)file->Get("mjj_new");
	TH1D* h2 = (TH1D*)file->Get("mjj_JEC_up");
	TH1D* h3 = (TH1D*)file->Get("mjj_JEC_down");
*/
	const int num =h1->GetNbinsX();
	Double_t bincontent_new[num],bincontent_up[num],bincontent_down[num];
	Double_t uncer[num];
	f1<<"fake=[";
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
     vector<TString> channels={"mu","ele"};//,"Mva","Mjj"};
     vector<TString> tag={"2016","2017","2018"};
     for(int i=0;i<channels.size();i++){
		     run(channels[i]);
     }
return 1;
}
