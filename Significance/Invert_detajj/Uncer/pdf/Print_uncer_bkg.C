#define num 103
void run(TString var,TString sample, TString tag){
	ofstream ftxt("./"+var+"_uncer_"+sample+"_"+tag+".txt");//,ios::app);
	ofstream ff("./"+var+"_uncer_"+tag+".txt",ios::app);
	TFile*file=new TFile("./hist_"+var+"_"+sample+"_pdf"+tag+".root");
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
            for(int j=0;j<num;j++){
               double center=h1[0]->GetBinContent(k+1);
               diff=h1[j]->GetBinContent(k+1)-center;
	       sum+=pow(diff,2);
	    }
            cout<<var<<" "<<sqrt(sum/(num-1))<<" "<<h1[0]->GetBinContent(k+1)<<" "<<sqrt(sum/(num-1))/h1[0]->GetBinContent(k+1)<<endl;
            if(h1[0]->GetBinContent(k+1)!=0)
                    error=sqrt(sum/(num-1))/h1[0]->GetBinContent(k+1);
            else    error=0;
            if(name.Contains("qcd")){
                    if(k==0){
                                ftxt<<"QCD_pdf=[";
                                ff<<"QCD_pdf=[";
                    }
                    if(k<kk-1){ftxt<<fixed<<setprecision(3)<<1+error<<",";
			    ff<<fixed<<setprecision(3)<<1+error<<",";
		    }
                    if(k==kk-1){
			    ftxt<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
			    ff<<setprecision(3)<<1+error<<"]"<<endl;
		    }
            }
            else{
                    if(k==0){
                                ftxt<<"Sig_pdf=[";
                                ff<<"Sig_pdf=[";
                    }
                    if(k<kk-1){ ftxt<<fixed<<setprecision(3)<<1+error<<",";
			    ff<<fixed<<setprecision(3)<<1+error<<",";
		    }
                    if(k==kk-1) {
			    ftxt<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
			    ff<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
		    }
            }
	}
}
int Print_uncer_bkg(){
     vector<vector<double>> bins;
     vector<double> MjjBins={500,600,700,800};
     bins.push_back(MjjBins);
     vector<TString> recovars={"Mjj"};
     for(int i=0;i<recovars.size();i++){
	     run(recovars[i],"qcd","16");
	     run(recovars[i],"Sig","16");
	     run(recovars[i],"Sig","17");
	     run(recovars[i],"Sig","18");
     }
     return 0;
}
