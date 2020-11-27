#define num 103
void run(TString var,TString sample, TString tag){
	ofstream ftxt("./"+var+"_uncer_"+sample+"_"+tag+".txt");//,ios::app);
	TFile*file=new TFile("./root/unfold_"+var+"_"+sample+"_pdf16.root");
	TString name=file->GetName();
        TH1D*h1[num];TH1D*h2[num];;TH1D*h3[num];
        TFile*file2;TFile*file3;
	for(int j=0;j<num;j++){
		h1[j]=(TH1D*)file->Get(Form(var+"_%i",j));
		h1[j]->Scale(35.86);
	}
        if(sample.Contains("Sig")){
		file2=new TFile("./root/unfold_"+var+"_"+sample+"_pdf17.root");
		file3=new TFile("./root/unfold_"+var+"_"+sample+"_pdf18.root");
		for(int j=0;j<num;j++){
			h2[j]=(TH1D*)file2->Get(Form(var+"_%i",j));
			h2[j]->Scale(41.52);
			h3[j]=(TH1D*)file3->Get(Form(var+"_%i",j));
			h3[j]->Scale(58.7);
			h1[j]->Add(h2[j],1);
			h1[j]->Add(h3[j],1);
		}

	}
        const int kk=h1[0]->GetNbinsX();
        for(int i=0;i<num;i++){
                h1[i]->SetBinContent(kk,h1[i]->GetBinContent(kk)+h1[i]->GetBinContent(kk+1));
        }
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
                    }
                    ftxt<<error<<",";
                    if(k==kk-1) ftxt<<"]"<<endl;
            }
            else{
                    if(k==0){
                                ftxt<<"SigOut_pdf=[";
                    }
                    ftxt<<error<<",";
                    if(k==kk-1) ftxt<<"]"<<endl;
            }
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
int Print_uncer_bkgAll(){
     vector<vector<double>> bins;
     vector<double> ptlepBins={20,80,120,200,400};
     vector<double> photonEtBins={20,80,120,200,400};
     vector<double> jetptBins={30,150,250,350,800};
     vector<double> MvaBins={100,150,1000};
     vector<double> MjjBins={500,1000,1500,2000};
     bins.push_back(ptlepBins);
     bins.push_back(photonEtBins);
     bins.push_back(jetptBins);
     bins.push_back(MjjBins);
     vector<TString> recovars={"ptlep1","photonet","jet1pt","Mjj","Mjj"};
     for(int i=0;i<recovars.size();i++){
	     run(recovars[i],"qcd","All");
	     run(recovars[i],"Sigout","All");
     }
     return 0;
}
