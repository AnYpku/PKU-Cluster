#define num 103
void run(TString var,TString sample, TString tag){
	ofstream ftxt("./txt/"+var+"_uncer_"+sample+"_"+tag+".txt");//,ios::app);
	TFile*file=new TFile("./sig_root/unfold_"+var+"_"+sample+"_pdf"+tag+".root");
	double lumi;
	if(tag.Contains("16"))
		lumi=35.86;
	else if(tag.Contains("17"))
		lumi=41.52;
	else if(tag.Contains("18"))
		lumi=58.7;

        TH1D*h1[num];
	for(int j=0;j<num;j++){
		h1[j]=(TH1D*)file->Get(Form(var+"_pdf%i_recobin1",j));
		h1[j]->Scale(lumi);
	}
        const int kk=h1[0]->GetNbinsX();
	for(int k=0;k<kk;k++){
            double error=0;
	    double diff=0,sum=0;
            for(int j=0;j<num;j++){
               double center=h1[0]->GetBinContent(k+1);
               diff=h1[j]->GetBinContent(k+1)-center;
	       sum+=pow(diff,2);
	    }
            error=sqrt(sum/num);
            ftxt<<error<<endl;
	}
}
/*void open(TString var,vector<double> genbins,TString tag){
        const int kk=genbins.size();
	double uncer[kk-1][kk-1];
	ofstream fout("./"+var+"_uncer"+tag+".txt");
	for(int k=0;k<kk-1;k++){
		ifstream f1(Form("./txt/"+var+"_recobin%i_uncer"+tag+".txt",k+1));
		for(int j=0;j<kk-1;j++){
			f1>>uncer[k][j];//the kth file and jth element
//			cout<<var<<" "<<uncer[k][j]<<endl;
		}
	}
	for(int i=0;i<kk-1;i++){
            for(int j=0;j<kk-1;j++){
               if(j==0)fout<<"genbin"<<i+1<<"=[";
               fout<<fixed<<setprecision(3)<<1+uncer[j][i]<<",";
               if(j==kk-2) fout<<"]"<<endl;
	    }
	}



}*/
int test(){
     vector<vector<double>> bins;
     vector<double> ptlepBins={20,80,120,200,400};
     vector<double> photonEtBins={20,80,120,200,400};
     vector<double> jetptBins={30,150,250,350,800};
     vector<double> MvaBins={100,150,1000};
     vector<double> MjjBins={500,1000,1500,2000};
     bins.push_back(ptlepBins);
     bins.push_back(photonEtBins);
     bins.push_back(jetptBins);
     bins.push_back(MvaBins);
     bins.push_back(MjjBins);
     vector<TString> recovars={"ptlep1","photonet","jet1pt","Mva","Mjj"};
     run("genlep1pt","recobin1_ewk","16");
//     for(int i=0;i<recovars.size();i++){
//	     run(recovars[i],"Sigout","16");
//	     run(recovars[i],"Sigout","17");
//	     run(recovars[i],"Sigout","18");
//     }
     return 0;
}
