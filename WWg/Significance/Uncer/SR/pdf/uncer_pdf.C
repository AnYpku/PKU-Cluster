void run(TString sample, TString tag,int num){
	ofstream ftxt("./uncer_"+sample+"_"+tag+".txt");//,ios::app);
	ofstream ff("./uncer_"+tag+".txt",ios::app);
	TFile*file;
	TH1D*h1[num];
	if(sample.Contains("Top")==0)
		file=new TFile("./root/hist_"+sample+"_"+tag+".root");
	else
		file=new TFile("./root/hist_TTGJets_"+tag+".root");
	for(int j=0;j<num;j++){
		h1[j]=(TH1D*)file->Get(Form("hist_bkg_%i",j));
	}
	if(sample.Contains("Top")){
		TFile*f2=new TFile("./root/hist_ST_"+tag+".root");
		TH1D*h2[num];
		for(int j=0;j<num;j++){
			h2[j]=(TH1D*)f2->Get(Form("hist_bkg_%i",j));
			h1[j]->Add(h2[j],1);
		}
	}
	TString name=file->GetName();
	double lumi;
	if(tag.Contains("16"))
		lumi=35.86;
	else if(tag.Contains("17"))
		lumi=41.52;
	else if(tag.Contains("18"))
		lumi=58.7;

	const int kk=h1[0]->GetNbinsX();
	for(int k=0;k<kk;k++){
		double error=0;
		double diff=0,sum=0;
		for(int j=0;j<num;j++){
			double center=h1[0]->GetBinContent(k+1);
			diff=h1[j]->GetBinContent(k+1)-center;
			sum+=pow(diff,2);
		}
		if(h1[0]->GetBinContent(k+1)!=0)
			cout<<sample<<" "<<tag<<" "<<sqrt(sum/(num-1))<<" "<<h1[0]->GetBinContent(k+1)<<" "<<sqrt(sum/(num-1))/h1[0]->GetBinContent(k+1)<<endl;
		else
			cout<<sample<<" "<<tag<<" "<<sqrt(sum/(num-1))<<" "<<h1[0]->GetBinContent(k+1)<<" no data in bin"<<k+1<<endl;
		if(h1[0]->GetBinContent(k+1)!=0)
			error=sqrt(sum/(num-1))/h1[0]->GetBinContent(k+1);
		else    error=0;
		if(k==0){
			ftxt<<sample+"_pdf=[";
			ff<<sample+"_pdf=[";
		}
		if(k<kk-1){
			ftxt<<fixed<<setprecision(3)<<1+error<<",";
			ff<<fixed<<setprecision(3)<<1+error<<",";
		}
		if(k==kk-1){
			ftxt<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
			ff<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
		}
	}
}
int uncer_pdf(){
	vector<TString> tag={"16","17","18"};
	vector<TString> sample={"TTGJets","ST","Top"};
	int num;
	for(int i=1;i<tag.size()-1;i++){
		for(int j=0;j<sample.size();j++){
			if(sample[j].Contains("ST")||sample[j].Contains("Top")) num=100;
			else num=103;
			run(sample[j],tag[i],num);
		}
	}
	return 0;
}
