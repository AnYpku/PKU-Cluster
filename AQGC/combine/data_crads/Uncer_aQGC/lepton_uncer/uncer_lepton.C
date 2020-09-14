void run(TString particle,TString type){
//	ofstream f1("./"+var+"_"+particle+"_"+type+"_"+tag+".txt");
	ofstream f2("./Mva_"+particle+"_"+type+".txt");
	TFile* file1 = new TFile("./Mva_"+particle+"_"+type+"16.root");
	TFile* file2 = new TFile("./Mva_"+particle+"_"+type+"17.root");
	TFile* file3 = new TFile("./Mva_"+particle+"_"+type+"18.root");

	cout<<particle+"_"+type+".root"<<endl;
	TH1D* h1 = (TH1D*)file1->Get("Mva_0");
	TH1D* h2 = (TH1D*)file1->Get("Mva_1");
	TH1D* h3 = (TH1D*)file1->Get("Mva_2");
	TH1D* h11 = (TH1D*)file2->Get("Mva_0");
	TH1D* h21 = (TH1D*)file2->Get("Mva_1");
	TH1D* h31 = (TH1D*)file2->Get("Mva_2");
	TH1D* h12 = (TH1D*)file3->Get("Mva_0");
	TH1D* h22 = (TH1D*)file3->Get("Mva_1");
	TH1D* h32 = (TH1D*)file3->Get("Mva_2");
	h1->Add(h11,1);h1->Add(h12,1);
	h2->Add(h21,1);h2->Add(h22,1);
	h3->Add(h31,1);h3->Add(h32,1);
	const int num =h1->GetNbinsX();
	Double_t bincontent_new,bincontent_up,bincontent_down;
	Double_t uncer;
	cout<<"uncertainty ";
	bincontent_new=h1->GetSum();
	bincontent_up=h2->GetSum();
	bincontent_down=h3->GetSum();
	cout<<h1->GetSum()<<endl;
	if(type.Contains("trigger")==0){
		uncer=fabs(bincontent_up-bincontent_down)/2/bincontent_new;
	}
	else uncer=0.02;
	cout<<bincontent_new<<" "<< bincontent_up<<" "<< bincontent_down<<endl;
	//                 f1<<1+uncer<<"]"<<endl;
	f2<<fixed<<setprecision(2)<<1+uncer<<endl;
	cout<<uncer<<endl;
	cout<<endl;
}
int uncer_lepton(){
	vector<TString> par={"ele","muon","photon"};
	vector<TString> tag={"16","17","18"};
	vector<TString> recovars={"Mva"};
	for(int i=0;i<par.size();i++){
		if(par[i].Contains("muon")){
			run(par[i],"all");
//			run(par[i],"trigger");
		}
		if(par[i].Contains("photon")){
			run(par[i],"ID");
		}
		if(par[i].Contains("ele")){
			run(par[i],"ID");
			run(par[i],"reco");
		}
	}    
	return 1;
}
