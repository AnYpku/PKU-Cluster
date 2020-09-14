void run(TString var,TString particle,TString type,TString tag){
//	ofstream f1("./"+var+"_"+particle+"_"+type+"_"+tag+".txt");
	ofstream f2("./txt/"+var+"_"+particle+"_"+type+"_"+tag+".txt");
	TFile* file = new TFile("./"+var+particle+"_"+type+"_2d_"+tag+".root");
	cout<<var+particle+"_"+type+"_2d_"+tag+".root"<<endl;
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
	Double_t bincontent_new,bincontent_up,bincontent_down;
	Double_t uncer;
//        if(tag.Contains("16"))
//		f1<<particle<<"_"<<type<<"16=[";
//        if(tag.Contains("17"))
//		f1<<particle<<"_"<<type<<"17=[";
//        if(tag.Contains("18"))
//		f1<<particle<<"_"<<type<<"=[";
	cout<<"uncertainty ";
                 bincontent_new=h1->GetSum();
                 bincontent_up=h2->GetSum();
                 bincontent_down=h3->GetSum();
cout<<h1->GetSum()<<endl;
                 uncer=fabs(bincontent_up-bincontent_down)/2/bincontent_new;
		 cout<<bincontent_new<<" "<< bincontent_up<<" "<< bincontent_down<<endl;
//                 f1<<1+uncer<<"]"<<endl;
                 f2<<1+uncer<<endl;
                 cout<<uncer<<endl;
		 cout<<endl;
}
int uncer_fakephoton(){
	vector<TString> par={"ele","muon","photon"};
	vector<TString> tag={"16","17","18"};
        vector<TString> recovars={"ptlep1","photonet","jet1pt"};
	for(int i=0;i<par.size();i++){
		for(int j=0;j<recovars.size();j++){
			if(par[i].Contains("muon")){
				run(recovars[j],par[i],"all","16");
				run(recovars[j],par[i],"all","17");
				run(recovars[j],par[i],"all","18");
			}
			if(par[i].Contains("photon")){
				run(recovars[j],par[i],"ID","16");
				run(recovars[j],par[i],"ID","17");
				run(recovars[j],par[i],"ID","18");
			}
			if(par[i].Contains("ele")){
				run(recovars[j],par[i],"ID","16");
				run(recovars[j],par[i],"ID","17");
				run(recovars[j],par[i],"ID","18");
				run(recovars[j],par[i],"reco","16");
				run(recovars[j],par[i],"reco","17");
				run(recovars[j],par[i],"reco","18");
			}
		}
	}    
	return 1;
}
