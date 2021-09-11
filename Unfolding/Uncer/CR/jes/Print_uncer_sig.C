#define num 3
void run(TString var,int i,TString tag){
	ofstream ftxt(Form("./txt/"+var+"_recobin%i_uncer"+tag+".txt",i));//,ios::app);
	TString index=Form("recobin%i",i);
//        ftxt<<index<<" "<<endl;
	TFile*file=new TFile("./root/unfold_ZA-EWK_"+var+"_"+index+"_jes"+tag+".root");
	TString sample=file->GetName();
	double lumi;
	if(tag.Contains("16"))
		lumi=35.86;
	else if(tag.Contains("17"))
		lumi=41.52;
	else if(tag.Contains("18"))
		lumi=59.7;
        TH1D*h1[num];
        cout<<"./root/unfold_ZA-EWK_"+var+"_"+index+"_jes"+tag+".root"<<endl;
	for(int j=0;j<num;j++){
		h1[j]=(TH1D*)file->Get(Form(var+"_%i_recobin%i",j,i));
		h1[j]->Scale(lumi);
        }
	const int kk=h1[0]->GetNbinsX();
	for(int k=0;k<kk;k++){
            double error=0;
	    double max=0;
	    if(fabs(h1[1]->GetBinContent(k+1)-h1[0]->GetBinContent(k+1))>fabs(h1[2]->GetBinContent(k+1)-h1[0]->GetBinContent(k+1)))
		    max=fabs(h1[1]->GetBinContent(k+1)-h1[0]->GetBinContent(k+1));
	    else    max=fabs(h1[2]->GetBinContent(k+1)-h1[0]->GetBinContent(k+1));
	    if(h1[0]->GetBinContent(k+1)!=0&&h1[1]->GetBinContent(k+1)!=0&&h1[2]->GetBinContent(k+1)!=0){
		    if(sample.Contains("ZA")){
			    error=max/h1[0]->GetBinContent(k+1);
		    }
		    else error=std::max( fabs(h1[1]->GetSum()-h1[0]->GetSum()),fabs(h1[2]->GetSum()-h1[0]->GetSum()) )/h1[0]->GetSum();
	    }
	    else    error=0;
	    if(error>1) error=1;
            ftxt<<error<<endl;
	}
}
void open(TString var,vector<double> genbins,TString tag,int kk){
	double uncer[kk-1][kk-1];
	ofstream fout("./"+var+"_jes_uncer"+tag+"CR.txt");
	for(int k=0;k<kk-1;k++){
		ifstream f1(Form("./txt/"+var+"_recobin%i_uncer"+tag+".txt",k+1));
		for(int j=0;j<kk-1;j++){
			f1>>uncer[k][j];//the kth file and jth element
//			cout<<var<<" "<<uncer[k][j]<<endl;
		}
	}
	for(int i=0;i<kk-1;i++){
            for(int j=0;j<kk-1;j++){
               if(j==0)fout<<"genbin"<<i+1<<"_jes=[";
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
     vector<double> MjjBins={150,300,400,500};
     bins.push_back(ptlepBins);
     bins.push_back(photonEtBins);
     bins.push_back(jetptBins);
     bins.push_back(MjjBins);
     vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt","genMjj"};
     vector<TString> tag={"16","17","18"};
     for(int k=0;k<tag.size();k++){
//             if(tag[k].Contains("17")) continue;
	     for(int i=0;i<genvars.size();i++){
		     for(int j=1;j<bins[i].size();j++){//open the jth recobin root file of the ith gen variables
			     run(genvars[i],j,tag[k]);
		     }
		     open(genvars[i],bins[i],tag[k],bins[i].size());
	     }
     }
     return 0;
}
