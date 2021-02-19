void run_all(TString sample,TString channel,TString type,double frac);
void run(TString sample,TString channel,TString type){
//	ofstream f1("./"+type+"_uncer_"+sample+"_"+channel+".txt");
	ofstream ftxt("./"+type+"_uncer_"+channel+"17.txt",ios::app);
	TFile* file = new TFile("./root/hist_"+sample+"_puId"+type+"_"+channel+".root");
	TH1D* h1 = (TH1D*)file->Get("hist_0");
	TH1D* h2 = (TH1D*)file->Get("hist_1");
	TH1D* h3 = (TH1D*)file->Get("hist_2");

	const int num =h1->GetNbinsX();
	const int kk =h1->GetNbinsX();
	Double_t bincontent_new[num],bincontent_up[num],bincontent_down[num];
	Double_t uncer[num];
//	f1<<sample<<"_"<<type<<"=[";
	ftxt<<sample<<"_"<<type<<"=[";
	cout<<type<<" "<<sample<<" "<<channel<<" uncertainty ";
	for(Int_t i=0;i<num;i++){
		if(sample.Contains("ZA")){
			bincontent_new[i] = h1->GetBinContent(i+1);
			bincontent_up[i] = h2->GetBinContent(i+1);
			bincontent_down[i] = h3->GetBinContent(i+1);
		}
		else{
			bincontent_new[i] = h1->GetSumOfWeights();
			bincontent_up[i] =  h2->GetSumOfWeights();
			bincontent_down[i] =h3->GetSumOfWeights();
		}
		if(bincontent_up[i]<=0) bincontent_up[i] =0;
		if(bincontent_down[i]<=0) bincontent_down[i] =0;
		if(bincontent_new[i]<=0) uncer[i] =0;
		else
			uncer[i] = fabs(bincontent_up[i]-bincontent_down[i])/2/bincontent_new[i];
		cout<<fixed<<setprecision(2)<<1+uncer[i]<<",";
		if(i<num-1){
//			f1<<fixed<<setprecision(3)<<uncer[i]+1<<",";
			ftxt<<fixed<<setprecision(3)<<uncer[i]+1<<",";
		}
		if(i==num-1){
//			f1<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
			ftxt<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
		}
	}
	cout<<endl;
}
int uncer_eff(){
	vector<TString> channels={"mu","ele"};
	vector<TString> sample={"ZA","ZA-EWK","others"};
	for(int i=0;i<channels.size();i++){
		for(int j=0;j<sample.size();j++){
			TFile*f1=new TFile("/home/pku/anying/cms/PKU-Cluster/AQGC/batch/hist_root/hist_"+sample[j]+"16"+channels[i]+".root");
			TFile*f2=new TFile("/home/pku/anying/cms/PKU-Cluster/AQGC/batch/hist_root/hist_"+sample[j]+"17"+channels[i]+".root");
			TFile*f3=new TFile("/home/pku/anying/cms/PKU-Cluster/AQGC/batch/hist_root/hist_"+sample[j]+"18"+channels[i]+".root");
                        TH1D*h1=(TH1D*)f1->Get("hist");
                        TH1D*h2=(TH1D*)f2->Get("hist");
                        TH1D*h3=(TH1D*)f3->Get("hist");
                        h1->Add(h2,1);h1->Add(h3,1);
                        double frac;
			if(h1->GetSum()>0) frac=h2->GetSum()/h1->GetSum();
			else frac=0;
			run(sample[j],channels[i],"mis");
			run(sample[j],channels[i],"eff");
			run_all(sample[j],channels[i],"mis",frac);
			run_all(sample[j],channels[i],"eff",frac);
		}
	}
	return 1;
}
void run_all(TString sample,TString channel,TString type,double frac){
//	ofstream f1("./"+type+"_uncer_"+sample+"_"+channel+".txt");
	ofstream ftxt("./"+type+"_uncer_"+channel+".txt",ios::app);
	TFile* file = new TFile("./root/hist_"+sample+"_puId"+type+"_"+channel+".root");
	TH1D* h1 = (TH1D*)file->Get("hist_0");
	TH1D* h2 = (TH1D*)file->Get("hist_1");
	TH1D* h3 = (TH1D*)file->Get("hist_2");

	const int num =h1->GetNbinsX();
	const int kk =h1->GetNbinsX();
	Double_t bincontent_new[num],bincontent_up[num],bincontent_down[num];
	Double_t uncer[num];
//	f1<<sample<<"_"<<type<<"=[";
	ftxt<<sample<<"_"<<type<<"=[";
	cout<<type<<" "<<sample<<" "<<channel<<" uncertainty ";
	for(Int_t i=0;i<num;i++){
		if(sample.Contains("ZA")){
			bincontent_new[i] = h1->GetBinContent(i+1);
			bincontent_up[i] = h2->GetBinContent(i+1);
			bincontent_down[i] = h3->GetBinContent(i+1);
		}
		else{
			bincontent_new[i] = h1->GetSumOfWeights();
			bincontent_up[i] =  h2->GetSumOfWeights();
			bincontent_down[i] =h3->GetSumOfWeights();
		}
		if(bincontent_up[i]<=0) bincontent_up[i] =0;
		if(bincontent_down[i]<=0) bincontent_down[i] =0;
		if(bincontent_new[i]<=0) uncer[i] =0;
		else
			uncer[i] = fabs(bincontent_up[i]-bincontent_down[i])/2/bincontent_new[i]*frac;
		cout<<fixed<<setprecision(2)<<1+uncer[i]<<",";
		if(i<num-1){
//			f1<<fixed<<setprecision(3)<<uncer[i]+1<<",";
			ftxt<<fixed<<setprecision(3)<<uncer[i]+1<<",";
		}
		if(i==num-1){
//			f1<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
			ftxt<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
		}
	}
	cout<<endl;
}
