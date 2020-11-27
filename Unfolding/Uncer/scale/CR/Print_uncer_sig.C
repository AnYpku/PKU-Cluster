#define num 3
void run(TString var,int i,TString tag){
	ofstream ftxt(Form("./txt/"+var+"_recobin%i_uncer"+tag+"CR.txt",i));//,ios::app);
	TString index=Form("recobin%i",i);
//        ftxt<<index<<" "<<endl;
	TFile*file=new TFile("./sig_root/unfold_"+var+"_"+index+"_ewk_scale"+tag+".root");
        TH1D*h1[3];
	for(int j=0;j<3;j++){
		h1[j]=(TH1D*)file->Get(Form(var+"_scale%i_recobin%i",j,i));
	}
        const int kk=h1[0]->GetNbinsX();
        for(int i=0;i<num;i++){
                h1[i]->SetBinContent(kk,h1[i]->GetBinContent(kk)+h1[i]->GetBinContent(kk+1));
        }//combine overflow bin
	for(int k=0;k<kk;k++){
            cout<<index<<" genbin"<<k+1<<" "<<h1[0]->GetBinContent(k+1)<<" "<<fabs(h1[1]->GetBinContent(k+1)-h1[2]->GetBinContent(k+1))<<endl;
            double error;
	    if(h1[0]->GetBinContent(k+1)>0) error=fabs(h1[1]->GetBinContent(k+1)-h1[2]->GetBinContent(k+1))/2/h1[0]->GetBinContent(k+1);
	    else error=0;
            ftxt<<error<<endl;
	}
}
void open(TString var,vector<double> genbins,TString tag){
        const int kk=genbins.size();
	double uncer[kk-1][kk-1];
	ofstream fout("./"+var+"_uncer"+tag+"CR.txt");
	for(int k=0;k<kk-1;k++){
		ifstream f1(Form("./txt/"+var+"_recobin%i_uncer"+tag+"CR.txt",k+1));
		for(int j=0;j<kk-1;j++){
			f1>>uncer[k][j];//the kth file and jth element
//			cout<<var<<" "<<uncer[k][j]<<endl;
		}
	}
	for(int i=0;i<kk-1;i++){
            for(int j=0;j<kk-1;j++){
               if(j==0)fout<<"genbin"<<i+1<<"_scale=[";
               if(j<kk-2)fout<<fixed<<setprecision(2)<<1+uncer[j][i]<<",";
               if(j==kk-2) fout<<1+uncer[j][i]<<"]"<<endl;
	    }
	}



}
int Print_uncer_sig(){
     vector<vector<double>> bins;
     vector<double> ptlepBins={20,80,120,200,400};
     vector<double> photonEtBins={20,80,120,200,400};
     vector<double> jetptBins={30,150,250,350,800};
     vector<double> MvaBins={100,150,1000};
     vector<double> MjjBins={150,300,400,500};
     bins.push_back(ptlepBins);
     bins.push_back(photonEtBins);
     bins.push_back(jetptBins);
     bins.push_back(MjjBins);
     vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt","genMjj"};
     for(int i=0;i<genvars.size();i++){
             for(int j=1;j<bins[i].size();j++){//open the jth recobin root file of the ith gen variables
		     run(genvars[i],j,"16");
		     run(genvars[i],j,"17");
		     run(genvars[i],j,"18");
	     }
	     open(genvars[i],bins[i],"16");
	     open(genvars[i],bins[i],"17");
	     open(genvars[i],bins[i],"18");
     }
     return 0;
}
