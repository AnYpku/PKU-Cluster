void run(TString var,TString particle,TString type,TString tag){
	ofstream f2("./"+var+"_"+particle+"_"+type+"_"+tag+".txt");
	TFile* file = new TFile("./root/"+var+particle+"_"+type+"_"+tag+".root");
	cout<<var+particle+"_"+type+tag+".root"<<endl;
	TH1D* h1 = (TH1D*)file->Get(var+"_0");
	TH1D* h2 = (TH1D*)file->Get(var+"_1");
	TH1D* h3 = (TH1D*)file->Get(var+"_2");

	const int num =h1->GetNbinsX();
	Double_t bincontent_new,bincontent_up,bincontent_down;
	Double_t uncer;
	cout<<var<<" "<<particle<<" "<<type<<" "<<tag<<" uncertainty ";
                 bincontent_new=h1->GetSum();
                 bincontent_up=h2->GetSum();
                 bincontent_down=h3->GetSum();
cout<<h1->GetSum()<<endl;
                 uncer=fabs(bincontent_up-bincontent_down)/2/bincontent_new;
		 cout<<bincontent_new<<" "<< bincontent_up<<" "<< bincontent_down<<endl;
//                 f1<<1+uncer<<"]"<<endl;
                 f2<<particle<<"_"<<type<<"=["<<fixed<<setprecision(3)<<1+uncer<<"]"<<endl;
                 cout<<uncer<<endl;
		 cout<<endl;
}
int uncer_eff(){
	vector<TString> par={"ele","muon","photon"};
	vector<TString> tag={"16","17","18"};
        vector<TString> recovars={"ptlep1","photonet","jet1pt","Mjj"};
        vector<TString> channels={"mubarrel","muendcap","elebarrel","eleendcap"};
	for(int i=0;i<par.size();i++){
		for(int j=0;j<recovars.size();j++){
			if(par[i].Contains("muon")){
				run(recovars[j],par[i],"all","16");
				run(recovars[j],par[i],"all","17");
				run(recovars[j],par[i],"all","18");
				run(recovars[j],par[i],"trigger","16");
				run(recovars[j],par[i],"trigger","17");
				run(recovars[j],par[i],"trigger","18");
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
