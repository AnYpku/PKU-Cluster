//#define num 9
void run(TString sample, TString tag,int num){
	ofstream ftxt("./uncer_"+sample+"_"+tag+".txt");//,ios::app);
        ofstream fband("./uncer_"+sample+"_scaleband_"+tag+".txt");
	ofstream f_up,f_down;
	f_up.open("./uncer_"+sample+"_extra_up_"+tag+".txt");//,ios::app);
	f_down.open("./uncer_"+sample+"_extra_down_"+tag+".txt");//,ios::app);
	ofstream ff("./uncer_"+tag+".txt",ios::app);
	TFile*file;
	if(sample.Contains("Top")==0)
		file=new TFile("./root/hist_"+sample+"_"+tag+".root");
	else
		file=new TFile("./root/hist_TTGJets_"+tag+".root");
        TH1D*h1[num];
	for(int j=0;j<num;j++){
		h1[j]=(TH1D*)file->Get(Form("hist_bkg_%i",j));
	}
	TH1D*h2[num];
        if(sample.Contains("Top")){
		TFile*file1=new TFile("./root/hist_ST_"+tag+".root");
		for(int j=0;j<num;j++){
			h2[j]=(TH1D*)file1->Get(Form("hist_bkg_%i",j));
                        h1[j]->Add(h2[j]);
		}
	}
	TString name=file->GetName();
	double lumi;
	if(tag.Contains("16"))
		lumi=35.86;
	else if(tag.Contains("17"))
		lumi=41.52;
	else if(tag.Contains("18"))
		lumi=59.7;

	vector<double> vec_content;
	vector<Double_t>:: iterator biggest;
	vector<Double_t>:: iterator smallest;
	double max,min;
	const int kk=h1[0]->GetNbinsX();
	double scale_muR1[kk],scale_muF1[kk],scale_muFmuR[kk];
	for(int k=0;k<kk;k++){
		double error=0,extra_up=0,extra_down=0;
		double diff=0,sum=0;
		for(int j=0;j<num;j++){
                        if( !(j==2||j==6))
				vec_content.push_back(h1[j]->GetBinContent(k+1));
		}
		biggest = max_element(begin(vec_content),end(vec_content));
		smallest= min_element(begin(vec_content),end(vec_content));
		if(h1[4]->GetBinContent(k+1)>0){
			error=(*biggest - *smallest)/2/h1[4]->GetBinContent(k+1);
			scale_muF1[k]=fabs(h1[3]->GetBinContent(k+1)-h1[5]->GetBinContent(k+1))/2/h1[4]->GetBinContent(k+1);
			scale_muR1[k]=fabs(h1[1]->GetBinContent(k+1)-h1[7]->GetBinContent(k+1))/2/h1[4]->GetBinContent(k+1);
			scale_muFmuR[k]=fabs(h1[0]->GetBinContent(k+1)-h1[8]->GetBinContent(k+1))/2/h1[4]->GetBinContent(k+1);
			cout<<tag<<" "<<scale_muR1[k]<<" "<<scale_muF1[k]<<" "<<scale_muFmuR[k]<<endl;
		}
		else{   error=0;
			scale_muR1[k]=0;
			scale_muF1[k]=0;
			scale_muFmuR[k]=0;
		}
		//cout<<*biggest<<" "<<*smallest<<" "<<h1[0]->GetBinContent(k+1)<<" "<<error<<endl;
		max=h1[5]->GetBinContent(k+1);min=h1[3]->GetBinContent(k+1);
		extra_up = 1 + (max-h1[4]->GetBinContent(k+1))/h1[4]->GetBinContent(k+1);
		extra_down= 1 - (h1[4]->GetBinContent(k+1)-min)/h1[4]->GetBinContent(k+1);
		//cout<< extra_up <<" "<<extra_down<<endl;
		if(k==0){
			ftxt<<sample+"_scale=[";
			ff<<sample+"_scale=[";
			f_up<<sample+"_scale_up=[";
			f_down<<sample+"_scale_down=[";
		}
		if(k<kk-1){
			ftxt<<fixed<<setprecision(3)<<1+error<<",";
			f_up<<fixed<<setprecision(3)<<extra_up<<",";
		        //cout<<extra_down<<endl;
			f_down<<fixed<<setprecision(3)<<extra_down<<",";
			ff<<fixed<<setprecision(3)<<1+error<<",";
		}
		if(k==kk-1){
			ftxt<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
			f_up<<fixed<<setprecision(3)<<extra_up<<"]"<<endl;
		      //cout<<"file open ? "<<f_down.is_open()<<endl;
			f_down<<fixed<<setprecision(3)<<extra_down<<"]"<<endl;
			ff<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
		}
		vec_content.clear();
	}
	for(int j=0;j<kk;j++){
		if(j==0)    fband<<sample<<"_scale_muR1=[";
		if(j<kk-1)  fband<<fixed<<setprecision(3)<<1+scale_muR1[j]<<","; 
		if(j==kk-1) fband<<fixed<<setprecision(3)<<1+scale_muR1[j]<<"]"<<endl; 
	}
	for(int j=0;j<kk;j++){
		if(j==0)    fband<<sample<<"_scale_muF1=[";
		if(j<kk-1)  fband<<fixed<<setprecision(3)<<1+scale_muF1[j]<<","; 
		if(j==kk-1) fband<<fixed<<setprecision(3)<<1+scale_muF1[j]<<"]"<<endl; 
	}
	for(int j=0;j<kk;j++){
		if(j==0)    fband<<sample<<"_scale_muFmuR=[";
		if(j<kk-1)  fband<<fixed<<setprecision(3)<<1+scale_muFmuR[j]<<","; 
		if(j==kk-1) fband<<fixed<<setprecision(3)<<1+scale_muFmuR[j]<<"]"<<endl; 
	}
}
int uncer_scale(){
	vector<TString> tag={"16","17","18"};
        vector<TString> sample={"TTGJets","WWG_emu","Top"};
	for(int i=1;i<tag.size();i++){
		for(int j=0;j<sample.size();j++){
			run(sample[j],tag[i],9);
		}
	}
	return 0;
}
