void run_combine(TString particle,TString sample,TString type);
void run(TString particle,TString sample,TString type,TString tag){
	ofstream f2("./txt/"+particle+"_"+type+tag+".txt",ios::app);
	TFile* file1 = new TFile("./root/"+particle+"_"+sample+"_"+type+tag+".root");

	cout<<particle+"_"+type+".root"<<endl;
	TH1D* h1 = (TH1D*)file1->Get("hist_0");
	TH1D* h2 = (TH1D*)file1->Get("hist_1");
	TH1D* h3 = (TH1D*)file1->Get("hist_2");
	const int num =h1->GetNbinsX();
	Double_t bincontent_new,bincontent_up,bincontent_down;
	Double_t uncer;
	cout<<particle<<" "<<type<<" in 20"<<tag<<" uncertainty ";
	bincontent_new=h1->GetSum();
	bincontent_up=h2->GetSum();
	bincontent_down=h3->GetSum();
	cout<<h1->GetSum()<<endl;
	uncer=fabs(bincontent_up-bincontent_down)/2/bincontent_new;
	cout<<bincontent_new<<" "<< bincontent_up<<" "<< bincontent_down<<endl;
	f2<<particle<<"_"<<sample<<"_"<<type<<"=["<<fixed<<setprecision(2)<<1+uncer<<"]"<<endl;
	cout<<uncer<<endl;
	cout<<endl;
}
int uncer_lepton(){
	vector<TString> par={"ele","muon","photon"};
	vector<TString> tag={"16","17","18"};
        vector<TString> sample={"ZA","ZA-EWK","others"};
	for(int k=0;k<sample.size();k++){
		for(int i=0;i<par.size();i++){
			if(par[i].Contains("muon")){
				run_combine(par[i],sample[k],"all");
				run_combine(par[i],sample[k],"trigger");
			}
			if(par[i].Contains("photon")){
				run_combine(par[i],sample[k],"ID");
			}
			if(par[i].Contains("ele")){
				run_combine(par[i],sample[k],"ID");
				run_combine(par[i],sample[k],"reco");
			}
			for(int j=0;j<tag.size();j++){
				if(par[i].Contains("muon")){
					run(par[i],sample[k],"all",tag[j]);
					run(par[i],sample[k],"trigger",tag[j]);
				}
				if(par[i].Contains("photon")){
					run(par[i],sample[k],"ID",tag[j]);
				}
				if(par[i].Contains("ele")){
					run(par[i],sample[k],"ID",tag[j]);
					run(par[i],sample[k],"reco",tag[j]);
				}
			}
		}
	}    
	return 1;
}
void run_combine(TString particle,TString sample,TString type){
	ofstream f2("./txt/"+particle+"_"+type+".txt",ios::app);
	TFile* file1 = new TFile("./root/"+particle+"_"+sample+"_"+type+"16.root");
	TFile* file2 = new TFile("./root/"+particle+"_"+sample+"_"+type+"17.root");
	TFile* file3 = new TFile("./root/"+particle+"_"+sample+"_"+type+"18.root");

	cout<<particle+"_"+type+".root"<<endl;
	TH1D* h1 = (TH1D*)file1->Get("hist_0");
	TH1D* h2 = (TH1D*)file1->Get("hist_1");
	TH1D* h3 = (TH1D*)file1->Get("hist_2");
	TH1D* hh1 = (TH1D*)file2->Get("hist_0");
	TH1D* hh2 = (TH1D*)file2->Get("hist_1");
	TH1D* hh3 = (TH1D*)file2->Get("hist_2");
	TH1D* hhh1 = (TH1D*)file3->Get("hist_0");
	TH1D* hhh2 = (TH1D*)file3->Get("hist_1");
	TH1D* hhh3 = (TH1D*)file3->Get("hist_2");
	h1->Add(hh1,1);h1->Add(hhh1,1);
	h2->Add(hh2,1);h2->Add(hhh2,1);
	h3->Add(hh3,1);h3->Add(hhh3,1);
	const int num =h1->GetNbinsX();
	Double_t bincontent_new,bincontent_up,bincontent_down;
	Double_t uncer;
	cout<<particle<<" "<<type<<" "<<" combined uncertainty ";
	bincontent_new=h1->GetSum();
	bincontent_up=h2->GetSum();
	bincontent_down=h3->GetSum();
	cout<<h1->GetSum()<<endl;
	uncer=fabs(bincontent_up-bincontent_down)/2/bincontent_new;
	cout<<bincontent_new<<" "<< bincontent_up<<" "<< bincontent_down<<endl;
	f2<<particle<<"_"<<sample<<"_"<<type<<"=["<<fixed<<setprecision(2)<<1+uncer<<"]"<<endl;
	cout<<uncer<<endl;
	cout<<endl;
}
