void run(TString tag,TString sample,TString type,TString vars,TString njets){
	ofstream f1("./txt/jesr_uncer_"+sample+"_"+vars+"_"+njets+"_"+type+tag+".txt");
	ofstream ftxt("./jesr_uncer_"+vars+"_"+njets+"_"+type+tag+".txt",ios::app);
	TFile* file ;
        if(sample.Contains("Top")==0)
                file= new TFile("./root/hist_"+sample+"_"+vars+"_"+njets+"_"+type+tag+".root");
        else
                file= new TFile("./root/hist_ST_"+vars+"_"+njets+"_"+type+tag+".root");
        TString mc;
        if(sample.Contains("WWG"))mc="sig";else mc="bkg";
	cout<<type<<endl;
	TH1D* h1 = (TH1D*)file->Get("hist_"+mc+"_0");
	TH1D* h2 = (TH1D*)file->Get("hist_"+mc+"_1");
	TH1D* h3 = (TH1D*)file->Get("hist_"+mc+"_2");
        if(sample.Contains("Top")){
                TFile* file1 = new TFile("./root/hist_TTGJets_"+vars+"_"+njets+"_"+type+tag+".root");
                TH1D* hh1 = (TH1D*)file1->Get("hist_"+mc+"_0");
                TH1D* hh2 = (TH1D*)file1->Get("hist_"+mc+"_1");
                TH1D* hh3 = (TH1D*)file1->Get("hist_"+mc+"_2");
                h1->Add(hh1);h2->Add(hh2);h3->Add(hh3);
        }

	const int num =h1->GetNbinsX();
        const int kk =h1->GetNbinsX();
	Double_t bincontent_new[num],bincontent_up[num],bincontent_down[num];
	Double_t uncer[num];
		f1<<type<<tag<<"=[";
		ftxt<<type<<"_"<<sample<<"_"<<vars<<"_"<<njets<<"=[";
	cout<<tag<<" "<<" "<<sample<<" "<<type<<" uncertainty ";
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
				 ftxt<<fixed<<setprecision(3)<<uncer[i]+1<<",";
			 }
			 if(i==num-1){
				 f1<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
				 ftxt<<fixed<<setprecision(3)<<uncer[i]+1<<"]"<<endl;
			 }
		 }
		 cout<<endl;
}
int uncer_jesr(){
	vector<TString> channels={"mubarrel","muendcap","elebarrel","eleendcap"};
	vector<TString> tag={"16","_pre16","17","18"};
	vector<TString> vars={"mllg"};
	vector<TString> sample={"ZGJets","TTGJets","VV","ST","tZq","WGJets","WWG_emu","Top"};
	vector<TString> njets={"0jets","1jets","2jets"};
	for(int i=1;i<njets.size()-1;i++){
		for(int j=0;j<tag.size();j++){
			for(int k=0;k<sample.size();k++){
				for(int n=0;n<vars.size();n++){
					run(tag[j],sample[k],"jer1",vars[n],njets[i]);
					run(tag[j],sample[k],"jesTotal",vars[n],njets[i]);
				}
			}
		}
	}
	return 1;
}
