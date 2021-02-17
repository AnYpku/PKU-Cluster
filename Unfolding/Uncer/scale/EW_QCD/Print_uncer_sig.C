#define num 9
void run(TString var,int i,TString tag){
	ofstream ftxt(Form("./txt/"+var+"_recobin%i_uncer"+tag+".txt",i));//,ios::app);
	TString index=Form("recobin%i",i);
//        ftxt<<index<<" "<<endl;
	TFile*file=new TFile("../root/unfold_"+var+"_"+index+"_ewk_scale"+tag+".root");
	TFile*file1=new TFile("./root/unfold_"+var+"_"+index+"_qcd_scale"+tag+".root");
        TH1D*h2[3];TH1D*h1[num];
	for(int j=0;j<3;j++){
		h2[j]=(TH1D*)file->Get(Form(var+"_scale%i_recobin%i",j,i));
	}
	for(int j=0;j<num;j++){
		h1[j]=(TH1D*)file1->Get(Form(var+"_scale%i_recobin%i",j,i));
		if(tag.Contains("16")&&j!=0) h1[j]->Scale(2);
	}
        const int kk=h1[0]->GetNbinsX();
        for(int i=0;i<3;i++){
                h2[i]->SetBinContent(kk,h2[i]->GetBinContent(kk)+h2[i]->GetBinContent(kk+1));
        }//combine overflow bin ewk
        for(int i=0;i<num;i++){
                h1[i]->SetBinContent(kk,h1[i]->GetBinContent(kk)+h1[i]->GetBinContent(kk+1));
		if(i==0||i==3||i==6) h1[i]->Add(h2[0]);
		if(i==1||i==4) h1[i]->Add(h2[1]);
		if(i==2||i==8) h1[i]->Add(h2[2]);
        }//combine overflow bin qcd
        vector<double> vec_content;
        vector<Double_t>:: iterator biggest;
        vector<Double_t>:: iterator smallest;
        double max,min;
	for(int k=0;k<kk;k++){
            double factor=1;
            double error=0,extra_up=0,extra_down=0;
            double diff=0,sum=0;
	    for(int j=0;j<num;j++){
		    factor=h1[0]->Integral()/h1[j]->Integral();
		    if(!(j==5||j==7)) vec_content.push_back(factor*h1[j]->GetBinContent(k+1));
	    }
            biggest = max_element(begin(vec_content),end(vec_content));
            smallest= min_element(begin(vec_content),end(vec_content));
	    if(h1[0]->GetBinContent(k+1)>0&&*biggest>=0&&*smallest>=0) 
		    error=(*biggest - *smallest)/2/h1[0]->GetBinContent(k+1);
	    else error=0;
	    cout<<tag<<" "<<var<<" "<<factor<<" "<<*biggest<<" "<<*smallest<<" "<<h1[0]->GetBinContent(k+1)<<" "<<error<<endl; 
	    ftxt<<error<<endl;
	    vec_content.clear();
	}
}
void open(TString var,vector<double> genbins,TString tag,int kk){
	double uncer[kk-1][kk-1];
	ofstream fout("./"+var+"_uncer"+tag+".txt");
	for(int k=0;k<kk-1;k++){
		ifstream f1(Form("./txt/"+var+"_recobin%i_uncer"+tag+".txt",k+1));
		for(int j=0;j<kk-1;j++){
			f1>>uncer[k][j];//the kth file and jth element
			//cout<<var<<" "<<uncer[k][j]<<endl;
		}
	}
	for(int i=0;i<kk-1;i++){
		for(int j=0;j<kk-1;j++){
			if(j==0)fout<<"genbin"<<i+1<<"_scale=[";
			if(j<kk-2)fout<<fixed<<setprecision(3)<<1+uncer[j][i]<<",";
			if(j==kk-2) fout<<1+uncer[j][i]<<"]"<<endl;
		}
	}



}
int Print_uncer_sig(){
	vector<vector<double>> bins;
	vector<double> ptlepBins={20,80,120,200,400};
	vector<double> photonEtBins={20,80,120,200,400};
	vector<double> jetptBins={30,150,250,350,800};
	vector<double> MjjBins={0,1,2,3,4,5,6,7};
	bins.push_back(ptlepBins);
	bins.push_back(photonEtBins);
	bins.push_back(jetptBins);
	bins.push_back(MjjBins);
	vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt","genMjj"};
	vector<TString> tag={"16","17","18"};
	for(int k=0;k<tag.size();k++){
		//if(tag[k].Contains("17")) continue;
		for(int i=0;i<genvars.size();i++){
			for(int j=1;j<bins[i].size();j++){//open the jth recobin root file of the ith gen variables
				run(genvars[i],j,tag[k]);
			}
			if(genvars[i].Contains("Mjj")==0)open(genvars[i],bins[i],tag[k],bins[i].size());
			else open(genvars[i],bins[i],tag[k],8);

		}
	}
	return 0;
}
