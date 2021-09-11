void run(TString sample,TString channel,TString type,TString tag){
//	ofstream f1("./"+type+"_uncer_"+sample+"_"+channel+".txt");
	ofstream ftxt("./"+type+"_uncer_"+channel+tag+".txt",ios::app);
	TFile* file;TFile* file1;TFile*file2;
	if(sample.Contains("ZA")&&sample.Contains("out")==0){
		file = new TFile("../root/hist_ZA-EWK_puId"+type+"_"+channel+tag+".root");
		file1 = new TFile("./root/hist_ZA_puId"+type+"_"+channel+tag+".root");
		file2 = new TFile("./root/hist_ZA_interf_puId"+type+"_"+channel+tag+".root");
	}
	else if(sample.Contains("ZA")&&sample.Contains("out")){
		file = new TFile("../root/hist_ZA-EWKout_puId"+type+"_"+channel+tag+".root");
		file1 = new TFile("./root/hist_ZAout_puId"+type+"_"+channel+tag+".root");
		file2 = new TFile("./root/hist_ZA_interfout_puId"+type+"_"+channel+tag+".root");
	}
	else file = new TFile("../root/hist_"+sample+"_puId"+type+"_"+channel+tag+".root");
	TH1D* h1 = (TH1D*)file->Get("hist_0");
	TH1D* h2 = (TH1D*)file->Get("hist_1");
	TH1D* h3 = (TH1D*)file->Get("hist_2");
	if(sample.Contains("ZA")){
		TH1D* hh1 = (TH1D*)file1->Get("hist_0");
		TH1D* hh2 = (TH1D*)file1->Get("hist_1");
		TH1D* hh3 = (TH1D*)file1->Get("hist_2");
		h1->Add(hh1);h2->Add(hh2);h3->Add(hh3);
		TH1D* hhh1 = (TH1D*)file2->Get("hist_0");
                TH1D* hhh2 = (TH1D*)file2->Get("hist_1");
                TH1D* hhh3 = (TH1D*)file2->Get("hist_2");
		h1->Add(hhh1);h2->Add(hhh2);h3->Add(hhh3);
	}

	const int num =h1->GetNbinsX()-2;
	const int kk =h1->GetNbinsX();
	h1->SetBinContent(kk-2,h1->GetBinContent(kk-2)+h1->GetBinContent(kk-1)+h1->GetBinContent(kk));
	h2->SetBinContent(kk-2,h2->GetBinContent(kk-2)+h2->GetBinContent(kk-1)+h2->GetBinContent(kk));
	h3->SetBinContent(kk-2,h3->GetBinContent(kk-2)+h3->GetBinContent(kk-1)+h3->GetBinContent(kk));
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
	vector<TString> channels={"mubarrel","muendcap","elebarrel","eleendcap"};
	vector<TString> sample={"ZA","ZAout","TTA","VV","ST"};
	vector<TString> tag={"16","17","18"};
	for(int k=0;k<tag.size();k++){
		for(int i=0;i<channels.size();i++){
			for(int j=0;j<sample.size();j++){
				run(sample[j],channels[i],"mis",tag[k]);
				run(sample[j],channels[i],"eff",tag[k]);
			}
		}
	}
	return 1;
}
