double ntot_fake,ntot_true;
vector<double> n_true_bins;
vector<double> n_fake_bins;
void run(TString year,TString style,vector<double> ptbins){
        gStyle->SetOptStat(0);
	TFile*file=new TFile("hist"+year+".root");
        TH1D*hdata=(TH1D*)file->Get("data_"+style);
        TH1D*hmc=(TH1D*)file->Get("mc_"+style);
        hdata->Add(hmc,-1);
//	cout<<style<<" photon counts "<<hdata->Integral()<<endl;
        if(style=="tight") ntot_true=hdata->Integral();
	else ntot_fake=hdata->Integral();
	for(int i=0;i<ptbins.size()-1;i++){
		TH1D*h1=(TH1D*)file->Get(Form("data_"+style+"_%0.f_%0.f",ptbins[i],ptbins[i+1]));
		TH1D*h2=(TH1D*)file->Get(Form("mc_"+style+"_%0.f_%0.f",ptbins[i],ptbins[i+1]));
		h1->Add(h2,-1);
//		cout<<style<<" photon counts in bins of "<<ptbins[i]<<"-"<<ptbins[i+1]<<" "<<h1->Integral()<<endl;
		if(style=="tight")  n_true_bins.push_back(h1->Integral());
		else                n_fake_bins.push_back(h1->Integral());
	}


}
int cal(){
	vector<double> ptbins={25,40,60};
	run("18","tight",ptbins);
	run("18","fake",ptbins);

        cout<<ntot_true<<" "<<ntot_fake<<" "<<ntot_true/ntot_fake<<endl;
	double rate_tot=ntot_true/ntot_fake;
	ofstream ftxt("fakelepton.txt");
	ftxt<<fixed<<setprecision(0)<<ptbins[0]<<"\t"<<ptbins[2]<<"\t"<<fixed<<setprecision(3)<<rate_tot<<"\t"<<"0"<<endl;
        for(int i=0;i<n_true_bins.size();i++){
		double rate_bins=n_true_bins[i]/n_fake_bins[i];
		cout<<n_true_bins[i]<<" "<<n_fake_bins[i]<<" "<<n_true_bins[i]/n_fake_bins[i]<<endl;
		ftxt<<fixed<<setprecision(0)<<ptbins[i]<<"\t"<<ptbins[i+1]<<"\t"<<fixed<<setprecision(3)<<rate_bins<<"\t"<<fabs(rate_tot-rate_bins)<<endl;
	}

	return 0;
}
