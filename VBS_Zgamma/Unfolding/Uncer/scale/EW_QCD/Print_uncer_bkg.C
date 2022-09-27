#define num 9
void run(TString var, TString tag){
	ofstream ff("./"+var+"_uncer_"+tag+".txt",ios::app);
	TFile*file=new TFile("../root/unfold_"+var+"_SigOut_scale"+tag+".root");
	TFile*file1=new TFile("./root/unfold_"+var+"_qcdOut_scale"+tag+".root");
	TFile*file2=new TFile("./root/unfold_"+var+"_interfOut_scale"+tag+".root");
	TString name=file->GetName();
	double lumi;
	if(tag.Contains("16"))
		lumi=35.86;
	else if(tag.Contains("17"))
		lumi=41.52;
	else if(tag.Contains("18"))
		lumi=58.7;

        TH1D*h1[num];TH1D*h2[3];TH1D*h3[3];
	vector<double> vec_content;
	vector<Double_t>:: iterator biggest;
	vector<Double_t>:: iterator smallest;
        double max,min;
	for(int j=0;j<num;j++){
		h1[j]=(TH1D*)file1->Get(Form(var+"_%i",j));
		if(j<3){
			h2[j]=(TH1D*)file->Get(Form(var+"_%i",j));
			h3[j]=(TH1D*)file2->Get(Form(var+"_%i",j));

		}
		if(j==0||j==3||j==6) {h1[j]->Add(h2[0]);h1[j]->Add(h3[0]);}
		if(j==1||j==4)       {h1[j]->Add(h2[1]);h1[j]->Add(h3[1]);}
		if(j==2||j==8)       {h1[j]->Add(h2[2]);h1[j]->Add(h3[2]);}
	}
	const int kk=h1[0]->GetNbinsX();
	for(int i=0;i<num;i++){
		h1[i]->SetBinContent(kk,h1[i]->GetBinContent(kk)+h1[i]->GetBinContent(kk+1));
	}//combine overflow bin
	for(int k=0;k<kk;k++){
		double error=0,extra_up=0,extra_down=0;
		double diff=0,sum=0;
		for(int j=0;j<num;j++){
			if((j!=5||j!=7)) vec_content.push_back(h1[j]->GetBinContent(k+1));
		}
		biggest = max_element(begin(vec_content),end(vec_content));
		smallest= min_element(begin(vec_content),end(vec_content));
		if(h1[0]->GetBinContent(k+1)>0)
			error=(*biggest - *smallest)/2/h1[0]->GetBinContent(k+1);
		else    error=0;
		//            cout<<*biggest<<" "<<*smallest<<" "<<h1[0]->GetBinContent(k+1)<<" "<<error<<endl;
		max=h1[6]->GetBinContent(k+1);min=h1[3]->GetBinContent(k+1);
		if(k==0){
			ff<<"SigOut_scale=[";
		}
		if(k<kk-1){
			ff<<fixed<<setprecision(3)<<1+error<<",";
		}
		if(k==kk-1){
			ff<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
		}
		vec_content.clear();
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
int Print_uncer_bkg(){
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
	vector<TString> recovars={"ptlep1","photonet","jet1pt","Mjj"};
	for(int i=0;i<recovars.size();i++){
		run(recovars[i],"16");
		run(recovars[i],"17");
		run(recovars[i],"18");
		cout<<recovars[i]<<endl;
	}
	return 0;
}
