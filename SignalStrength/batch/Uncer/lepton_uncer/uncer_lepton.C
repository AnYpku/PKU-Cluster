void run(TString particle,TString type,TString tag){
//	ofstream f1("./"+var+"_"+particle+"_"+type+"_"+tag+".txt");
	ofstream f2("./"+particle+"_"+type+"_"+tag+".txt");
        TFile* file;TH1D* h1;TH1D* h2;TH1D* h3;
	file = new TFile("./"+particle+"_"+type+tag+".root");
	cout<<particle+"_"+type+tag+".root"<<endl;
	h1 = (TH1D*)file->Get("hist_0");
	h2 = (TH1D*)file->Get("hist_1");
	h3 = (TH1D*)file->Get("hist_2");

	if(tag.Contains("16"))
		f2<<particle<<"_"<<type<<"=[";
	if(tag.Contains("17"))
		f2<<particle<<"_"<<type<<"=[";
	if(tag.Contains("18"))
		f2<<particle<<"_"<<type<<"=[";
	Double_t uncer;
	const int num =h1->GetNbinsX();
	Double_t bincontent_new,bincontent_up,bincontent_down;
	cout<<"uncertainty ";
	bincontent_new=h1->GetSum();
	bincontent_up=h2->GetSum();
	bincontent_down=h3->GetSum();
	cout<<h1->GetSum()<<endl;
	uncer=fabs(bincontent_up-bincontent_down)/2/bincontent_new;
	cout<<bincontent_new<<" "<< bincontent_up<<" "<< bincontent_down<<endl;
	//                 f1<<1+uncer<<"]"<<endl;
	f2<<fixed<<setprecision(3)<<1+uncer<<"]";
	cout<<uncer<<endl;
	cout<<endl;
}
int uncer_lepton(){
	vector<TString> par={"ele","muon","photon"};
	vector<TString> tag={"16","17","18"};
	vector<TString> recovars={"ptlep1","photonet","jet1pt"};
	for(int i=0;i<par.size();i++){
		if(par[i].Contains("muon")){
			run(par[i],"all","16");
			run(par[i],"all","17");
			run(par[i],"all","18");
			run(par[i],"trigger","16");
			run(par[i],"trigger","17");
			run(par[i],"trigger","18");
		}
		if(par[i].Contains("photon")){
			run(par[i],"ID","16");
			run(par[i],"ID","17");
			run(par[i],"ID","18");
		}
		if(par[i].Contains("ele")){
			run(par[i],"ID","16");
			run(par[i],"ID","17");
			run(par[i],"ID","18");
			run(par[i],"reco","16");
			run(par[i],"reco","17");
			run(par[i],"reco","18");
		}
	}    
	return 1;
}
