void run(TString particle,TString type,TString tag){
	ofstream f1("./"+particle+"_"+type+"_"+tag+".txt");
	TFile* file = new TFile("./"+particle+"_"+type+"_2d_"+tag+".root");
	cout<<particle+"_"+type+"_2d_"+tag+".root"<<endl;
	TH2D* h1 = (TH2D*)file->Get("th2_0");
	TH2D* h2 = (TH2D*)file->Get("th2_1");
	TH2D* h3 = (TH2D*)file->Get("th2_2");

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
 //       if(tag.Contains("18"))
		f1<<particle<<"_"<<type<<"=[";
	cout<<"uncertainty ";
                 bincontent_new=h1->GetSum();
                 bincontent_up=h2->GetSum();
                 bincontent_down=h3->GetSum();
                 uncer=fabs(bincontent_up-bincontent_down)/2/bincontent_new;
                 f1<<uncer<<"]"<<endl;
                 cout<<uncer<<endl;
		 cout<<endl;
}
int uncer_fakephoton(){
	vector<TString> par={"ele","muon","photon"};
	vector<TString> tag={"16","17","18"};
	for(int i=0;i<par.size();i++){
		if(par[i].Contains("muon")){
			run(par[i],"all","16");
			run(par[i],"all","17");
			run(par[i],"all","18");
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
