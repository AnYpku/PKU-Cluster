void run(TString channel,TString tag,TString sample){
	ofstream f1("./txt/l1pref_uncer_"+sample+"_"+channel+"_"+tag+".txt");
	ofstream ftxt("./l1pref_uncer_"+channel+"_"+tag+".txt",ios::app);
	TFile* file = new TFile("./root/hist_"+sample+"_pref_"+tag+channel+".root");
	TH1D* h1 = (TH1D*)file->Get("hist_0");
	TH1D* h2 = (TH1D*)file->Get("hist_1");
	TH1D* h3 = (TH1D*)file->Get("hist_2");
        if(sample.Contains("ZA")&&sample.Contains("EWK")==0){
          TFile*file1;
          file1=new TFile("./hist_ZA_interf_pref_"+tag+channel+".root");
          TH1D*hh1 = (TH1D*)file1->Get("hist_0");
          TH1D*hh2 = (TH1D*)file1->Get("hist_1");
          TH1D*hh3 = (TH1D*)file1->Get("hist_2");
          h1->Add(hh1,1);
          h2->Add(hh2,1);
          h3->Add(hh3,1);
        }
	const int num =h1->GetNbinsX()-2;
        const int kk =h1->GetNbinsX();
        h1->SetBinContent(kk-2,h1->GetBinContent(kk-2)+h1->GetBinContent(kk-1)+h1->GetBinContent(kk));
        h2->SetBinContent(kk-2,h2->GetBinContent(kk-2)+h2->GetBinContent(kk-1)+h2->GetBinContent(kk));
        h3->SetBinContent(kk-2,h3->GetBinContent(kk-2)+h3->GetBinContent(kk-1)+h3->GetBinContent(kk));
	Double_t bincontent_new[num],bincontent_up[num],bincontent_down[num];
	Double_t uncer[num];
        if(tag.Contains("16")){
		f1<<"l1pref16=[";
		ftxt<<"l1pref_"<<sample<<"=[";
	}
        if(tag.Contains("17")){
		f1<<"l1pref17=[";
		ftxt<<"l1pref_"<<sample<<"=[";
	}
        if(tag.Contains("18")){
		f1<<"l1pref18=[";
		ftxt<<"l1pref_"<<sample<<"=[";
	}
	cout<<tag<<" "<<channel<<" "<<sample<<" uncertainty ";
		 for(Int_t i=0;i<num;i++){
			 bincontent_new[i] = h1->GetBinContent(i+1);
			 bincontent_up[i] = h2->GetBinContent(i+1);
			 bincontent_down[i] = h3->GetBinContent(i+1);
			 if(sample.Contains("ewk")||sample.Contains("ZA")){
				 if(bincontent_new[i]==0) uncer[i] =0;
				 else
					 uncer[i] = fabs(bincontent_up[i]-bincontent_down[i])/2/bincontent_new[i];
			 }
			 else{
				 if(bincontent_new[i]==0) uncer[i] =0;
				 else  uncer[i] = fabs(h2->GetSum()-h3->GetSum())/2/h1->GetSum();
			 }
			 cout<<fixed<<setprecision(2)<<1+uncer[i]<<",";
			 if(i<num-1){
				 f1<<fixed<<setprecision(3)<<uncer[i]+1<<",";
				 ftxt<<fixed<<setprecision(3)<<uncer[i]+1<<",";
			 }
			 if(i==num-1){
				 f1<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
				 ftxt<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
			 }
		 }
		 cout<<endl;
}
int uncer_pref(){
     vector<TString> channels={"mubarrel","muendcap","elebarrel","eleendcap"};//,"Mva","Mjj"};
     vector<TString> tag={"16","17"};
     vector<TString> sample={"ZA","ewk","TTA","VV","ST"};
     for(int i=0;i<channels.size();i++){
	     for(int j=0;j<tag.size();j++){
		     for(int k=0;k<sample.size();k++){
			     run(channels[i],tag[j],sample[k]);
		     }
	     }
     }
return 1;
}
