void run(TString tag,TString sample){
	ofstream f1("./fake_uncer_"+tag+".txt");
	TFile* file = new TFile("./root/hist_"+sample+"_"+tag+".root");
	TH1D* h1 = (TH1D*)file->Get("hist_hist_0");
	TH1D* h2 = (TH1D*)file->Get("hist_hist_1");
	TH1D* h3 = (TH1D*)file->Get("hist_hist_2");

	const int num =h1->GetNbinsX();
        const int kk =h1->GetNbinsX();
	Double_t bincontent_new[num],bincontent_up[num],bincontent_down[num];
	Double_t uncer[num];
	f1<<"fakephoton"<<tag<<"=[";
	cout<<tag<<" "<<" "<<sample<<" "<<" uncertainty ";
		 for(Int_t i=0;i<num;i++){
			 bincontent_new[i] = h1->GetBinContent(i+1);
			 bincontent_up[i] = h2->GetBinContent(i+1);
			 bincontent_down[i] = h3->GetBinContent(i+1);
			 if(bincontent_new[i]<=0) uncer[i] =0;
			 else{
				 uncer[i] = fabs(bincontent_up[i]-bincontent_down[i])/2/bincontent_new[i];
			 }
			 cout<<fixed<<setprecision(3)<<1+uncer[i]<<",";
			 if(i<num-1){
				 f1<<fixed<<setprecision(3)<<uncer[i]+1<<",";
			 }
			 if(i==num-1){
				 f1<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
			 }
		 }
		 cout<<endl;
}
int uncer_fake(){
	vector<TString> tag={"16","17","18"};
	vector<TString> sample={"plj"};
	for(int j=1;j<tag.size()-1;j++){
		for(int k=0;k<sample.size();k++){
			run(tag[j],sample[k]);
		}
	}
	return 1;
}
