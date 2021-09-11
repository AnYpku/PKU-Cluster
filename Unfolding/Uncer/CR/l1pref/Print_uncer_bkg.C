#define num 3
void run(TString var, TString tag,TString sample){
	ofstream ftxt("./txt/"+var+"_l1pref_"+sample+"_uncer"+tag+"CR.txt");//,ios::app);
	ofstream ff("./"+var+"_uncer"+tag+"CR.txt",ios::app);
	TFile*file=new TFile("./root/unfold_"+var+"_"+sample+"_pref"+tag+".root");
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
	}
        TH1D*hh1[3];
        if(sample.Contains("ZA")||sample.Contains("EW")==0){
                TFile*file1=new TFile("./root/unfold_"+var+"_ZA_interf_pref"+tag+".root");
                for(int j=0;j<num;j++){
                        hh1[j]=(TH1D*)file1->Get(Form(var+"_%i",j));
                        h1[j]->Add(hh1[j],1);
                }
        }
        const int kk=h1[0]->GetNbinsX();
        for(int i=0;i<num;i++){
                h1[i]->SetBinContent(kk,h1[i]->GetBinContent(kk)+h1[i]->GetBinContent(kk+1));
        }//add overflow
	for(int k=0;k<kk;k++){
            double error=0;
            if(h1[0]->GetBinContent(k+1)!=0&&h1[1]->GetBinContent(k+1)!=0&&h1[2]->GetBinContent(k+1)!=0)
		    error=fabs(h1[1]->GetBinContent(k+1)-h1[2]->GetBinContent(k+1))/2/h1[0]->GetBinContent(k+1);
            else    error=0;
            if(error>1) error=1;
	    if(k==0){
                    ftxt<<"l1pref_"<<sample<<"=[";
                    ff<<  "l1pref_"<<sample<<"=[";
	    }
	    if(k<kk-1){
		    ftxt<<fixed<<setprecision(3)<<1+error<<",";
		    ff<<fixed<<setprecision(3)<<1+error<<",";
	    }
	    if(k==kk-1){
		    ftxt<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
		    ff<<setprecision(3)<<1+error<<"]"<<endl;
	    }
	}
}
int Print_uncer_bkg(){
	vector<vector<double>> bins;
	vector<double> ptlepBins={20,80,120,200,400};
	vector<double> photonEtBins={20,80,120,200,400};
	vector<double> jetptBins={30,150,250,350,800};
	vector<double> MjjBins={150,300,400,500};
	bins.push_back(ptlepBins);
	bins.push_back(photonEtBins);
	bins.push_back(jetptBins);
	bins.push_back(MjjBins);
	vector<TString> recovars={"ptlep1","photonet","jet1pt","Mjj"};
	vector<TString> sample={"ZA","ZA-EWK","TTA","VV","ST"};
	for(int i=0;i<recovars.size();i++){
		for(int k=0;k<sample.size();k++){
			run(recovars[i],"16",sample[k]);
			run(recovars[i],"17",sample[k]);
		}
	}
	return 0;
}
