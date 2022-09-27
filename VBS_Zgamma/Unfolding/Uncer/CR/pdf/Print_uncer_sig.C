#define num 103
void run(TString var,int i,TString tag){
	ofstream ftxt(Form("./txt/"+var+"_recobin%i_uncer"+tag+"CR.txt",i));//,ios::app);
	TString index=Form("recobin%i",i);
//        ftxt<<index<<" "<<endl;
	TFile*file=new TFile("./root/unfold_"+var+"_"+index+"_ewk_pdf"+tag+".root");
	double lumi;
	if(tag.Contains("16"))
		lumi=35.86;
	else if(tag.Contains("17"))
		lumi=41.52;
	else if(tag.Contains("18"))
		lumi=58.7;
        TH1D*h1[num];
	for(int j=0;j<num;j++){
		h1[j]=(TH1D*)file->Get(Form(var+"_pdf%i_recobin%i",j,i));
		h1[j]->Scale(lumi);
        }
	const int kk=h1[0]->GetNbinsX();
        for(int i=0;i<num;i++){
                h1[i]->SetBinContent(kk,h1[i]->GetBinContent(kk)+h1[i]->GetBinContent(kk+1));
        }//add overflow
	for(int k=0;k<kk;k++){
            double error=0;
	    double diff=0,sum=0;
	    double factor=1;
            for(int j=0;j<num;j++){
	       factor=h1[0]->Integral()/h1[j]->Integral();
               double center=h1[0]->GetBinContent(k+1);
               diff=factor*h1[j]->GetBinContent(k+1)-center;
	       sum+=pow(diff,2);
	    }
	    if(h1[0]->GetBinContent(k+1)!=0)
		    cout<<var<<" "<<sqrt(sum/(num-1))<<" "<<h1[0]->GetBinContent(k+1)<<" "<<sqrt(sum/(num-1))/h1[0]->GetBinContent(k+1)<<endl;
	    else cout<<"no events"<<endl;
	    if(h1[0]->GetBinContent(k+1)!=0) 
		    error=sqrt(sum/(num-1))/h1[0]->GetBinContent(k+1);
	    else    error=0;
//            error=sqrt(sum/(num-1));
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
               if(j==0)fout<<"genbin"<<i+1<<"_pdf=[";
               if(j<kk-2)  fout<<fixed<<setprecision(3)<<1+uncer[j][i]<<",";
               if(j==kk-2) fout<<fixed<<setprecision(3)<<1+uncer[j][i]<<"]"<<endl;
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
