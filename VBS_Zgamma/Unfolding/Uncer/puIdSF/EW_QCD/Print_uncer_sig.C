#define num 3
void run(TString var,int i,TString tag,TString type){
	ofstream ftxt(Form("./txt/"+var+"_recobin%i_uncer_"+type+tag+".txt",i));//,ios::app);
	TString index=Form("recobin%i",i);
//        ftxt<<index<<" "<<endl;
	TFile*file=new TFile("../root/unfold_"+var+"_"+index+"_ewk_"+type+tag+".root");
	TFile*file1=new TFile("./root/unfold_"+var+"_"+index+"_qcd_"+type+tag+".root");
	TFile*file2=new TFile("./root/unfold_"+var+"_"+index+"_interf_"+type+tag+".root");
	double lumi;
	if(tag.Contains("16"))
		lumi=35.86;
	else if(tag.Contains("17"))
		lumi=41.52;
	else if(tag.Contains("18"))
		lumi=59.7;
        TH1D*h1[num];TH1D*h2[num];TH1D*h3[num];
        cout<<"./root/unfold_"+var+"_"+index+"_ewk_"+type+tag+".root"<<endl;
        cout<<"./root/unfold_"+var+"_"+index+"_qcd_"+type+tag+".root"<<endl;
	for(int j=0;j<num;j++){
		h1[j]=(TH1D*)file->Get(Form(var+"_%i_recobin%i",j,i));
		h2[j]=(TH1D*)file1->Get(Form(var+"_%i_recobin%i",j,i));
		h3[j]=(TH1D*)file2->Get(Form(var+"_%i_recobin%i",j,i));
		h1[j]->Add(h2[j],1);
		h1[j]->Add(h3[j],1);
        }
	const int kk=h1[0]->GetNbinsX();
        for(int i=0;i<num;i++){
                h1[i]->SetBinContent(kk,h1[i]->GetBinContent(kk)+h1[i]->GetBinContent(kk+1));
        }//add overflow
	for(int k=0;k<kk;k++){
            double error=0;
	    double diff=0,sum=0;
            double factor=1;
	    if(h1[0]->GetBinContent(k+1)>0) 
		    error=fabs(h1[1]->GetBinContent(k+1)-h1[2]->GetBinContent(k+1))/2/h1[0]->GetBinContent(k+1);
	    else    error=0;
//            error=sqrt(sum/(num-1));
            ftxt<<error<<endl;
	}
}
void open(TString var,vector<double> genbins,TString tag,int kk,TString type){
	double uncer[kk-1][kk-1];
	ofstream fout("./"+var+"_uncer_"+type+tag+".txt");
	for(int k=0;k<kk-1;k++){
		ifstream f1(Form("./txt/"+var+"_recobin%i_uncer_"+type+tag+".txt",k+1));
		for(int j=0;j<kk-1;j++){
			f1>>uncer[k][j];//the kth file and jth element
//			cout<<var<<" "<<uncer[k][j]<<endl;
		}
	}
	for(int i=0;i<kk-1;i++){
            for(int j=0;j<kk-1;j++){
               if(j==0)fout<<"genbin"<<i+1<<"_"<<type<<"=[";
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
     vector<double> MjjBins={1,2,3,4,5,6,7,8};
     bins.push_back(ptlepBins);
     bins.push_back(photonEtBins);
     bins.push_back(jetptBins);
     bins.push_back(MjjBins);
     vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt","genMjj"};
     vector<TString> tag={"17","16","18"};
     vector<TString> type={"eff","mis"};
     for(int k=0;k<tag.size();k++){
//             if(tag[k].Contains("17")) continue;
	     for(int i=0;i<genvars.size();i++){
		     for(int ik=0;ik<type.size();ik++){
			     for(int j=1;j<bins[i].size();j++){//open the jth recobin root file of the ith gen variables
				     run(genvars[i],j,tag[k],type[ik]);
			     }
			     if(genvars[i].Contains("Mjj")==0)
				     open(genvars[i],bins[i],tag[k],bins[i].size(),type[ik]);
			     else open(genvars[i],bins[i],tag[k],8,type[ik]);
		     }
	     }
     }
     return 0;
}
