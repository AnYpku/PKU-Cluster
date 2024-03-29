#define num 3
void run(TString var,TString sample, TString tag,TString type){
	ofstream ff("./"+var+"_uncer_"+type+tag+".txt",ios::app);
	TFile*file=new TFile("./root/hist_"+var+"_"+sample+"_"+type+tag+".root");
        TString name=file->GetName();
	double lumi;
	if(tag.Contains("16"))
		lumi=35.86;
	else if(tag.Contains("17"))
		lumi=41.52;
	else if(tag.Contains("18"))
		lumi=59.7;

        TH1D*h1[num];
	for(int j=0;j<num;j++){
		h1[j]=(TH1D*)file->Get(Form(var+"_%i",j));
		h1[j]->Scale(lumi);
	}
        const int kk=h1[0]->GetNbinsX();
        for(int i=0;i<num;i++){
                h1[i]->SetBinContent(kk,h1[i]->GetBinContent(kk)+h1[i]->GetBinContent(kk+1));
        }//add overflow
	for(int k=0;k<kk;k++){
            double error=0;
	    double diff=0,sum=0;
            if(h1[0]->GetBinContent(k+1)!=0){
                    error=fabs(h1[1]->GetBinContent(k+1)-h1[2]->GetBinContent(k+1))/2/h1[0]->GetBinContent(k+1);
		    cout<<h1[1]->GetBinContent(k+1)<<" "<<h1[2]->GetBinContent(k+1)<<" "<<h1[0]->GetBinContent(k+1)<<" "<<fabs(h1[1]->GetBinContent(k+1)-h1[2]->GetBinContent(k+1))/2/h1[0]->GetBinContent(k+1)<<endl;
	    }
            else    error=0;
	    if(k==0){
//		    ftxt<<sample<<"_"<<type<<"=[";
		    ff<<sample<<"_"<<type<<"=[";
	    }
	    if(k<kk-1){
//		    ftxt<<fixed<<setprecision(3)<<1+error<<",";
		    ff<<fixed<<setprecision(3)<<1+error<<",";
	    }
	    if(k==kk-1){
//		    ftxt<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
		    ff<<setprecision(3)<<1+error<<"]"<<endl;
	    }
	}
}
int Print_uncer_bkg(){
	vector<vector<double>> bins;
	vector<double> MjjBins={500,600,700,800};
	bins.push_back(MjjBins);
	vector<TString> recovars={"Mjj"};
	vector<TString> sample={"ZA","ZA-EWK","TTA","ST","VV"};
	vector<TString> type={"eff","mis"};
	for(int i=0;i<recovars.size();i++){
		for(int j=0;j<sample.size();j++){
			for(int k=0;k<type.size();k++){
				run(recovars[i],sample[j],"16",type[k]);
				run(recovars[i],sample[j],"17",type[k]);
				run(recovars[i],sample[j],"18",type[k]);
			}
		}
	}
	return 0;
}
