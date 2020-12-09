void run(TString var,int i,TString tag){
	ofstream ftxt(Form("./txt/"+var+"_recobin%i_uncer"+tag+".txt",i));//,ios::app);
	TString index=Form("recobin%i",i);
//        ftxt<<index<<" "<<endl;
	TFile*file1=new TFile("./sig_root/unfold_"+var+"_"+index+"_ewk_scale16.root");
	TFile*file2=new TFile("./sig_root/unfold_"+var+"_"+index+"_ewk_scale17.root");
	TFile*file3=new TFile("./sig_root/unfold_"+var+"_"+index+"_ewk_scale18.root");
        TH1D*h1[3];TH1D*h2[3];;TH1D*h3[3];
	for(int j=0;j<3;j++){
		h1[j]=(TH1D*)file1->Get(Form(var+"_scale%i_recobin%i",j,i));
		h2[j]=(TH1D*)file2->Get(Form(var+"_scale%i_recobin%i",j,i));
		h3[j]=(TH1D*)file3->Get(Form(var+"_scale%i_recobin%i",j,i));
		h1[j]->Scale(35.86);
		h2[j]->Scale(41.52);
		h3[j]->Scale(58.7);
		h1[j]->Add(h2[j],1);
		h1[j]->Add(h3[j],1);

	}
        const int kk=h1[0]->GetNbinsX();
        for(int i=0;i<3;i++){
                h1[i]->SetBinContent(kk,h1[i]->GetBinContent(kk)+h1[i]->GetBinContent(kk+1));
                h2[i]->SetBinContent(kk,h2[i]->GetBinContent(kk)+h2[i]->GetBinContent(kk+1));
                h3[i]->SetBinContent(kk,h3[i]->GetBinContent(kk)+h3[i]->GetBinContent(kk+1));
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
               fout<<fixed<<setprecision(2)<<1+uncer[j][i]<<",";
               if(j==kk-2) fout<<"]"<<endl;
	    }
	}



}
int Print_uncer_sigAll(){
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
     vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt","genZGmass","genMjj"};
     for(int i=0;i<genvars.size();i++){
             for(int j=1;j<bins[i].size();j++){//open the jth recobin root file of the ith gen variables
		     run(genvars[i],j,"All");
	     }
	     open(genvars[i],bins[i],"All");
     }
     return 0;
}
