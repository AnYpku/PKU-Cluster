//#define num 9
void run(TString var,TString sample, TString tag,int num){
	ofstream ftxt("./"+var+"_uncer_"+sample+"_"+tag+".txt");//,ios::app);
	TFile*file1=new TFile("./bkg_root/unfold_"+var+"_"+sample+"_scale16.root");
	TFile*file2=new TFile("./bkg_root/unfold_"+var+"_"+sample+"_scale17.root");
	TFile*file3=new TFile("./bkg_root/unfold_"+var+"_"+sample+"_scale18.root");
	TString name=file1->GetName();
        TH1D*h1[num];TH1D*h2[num];;TH1D*h3[num];
	vector<double> vec_content;
	vector<Double_t>:: iterator biggest;
	vector<Double_t>:: iterator smallest;
	for(int j=0;j<num;j++){
		h1[j]=(TH1D*)file1->Get(Form(var+"_%i",j));
		h2[j]=(TH1D*)file2->Get(Form(var+"_%i",j));
		h3[j]=(TH1D*)file3->Get(Form(var+"_%i",j));
		h1[j]->Scale(35.86);
		h2[j]->Scale(41.52);
		h3[j]->Scale(58.7);
		h1[j]->Add(h2[j],1);
                h1[j]->Add(h3[j],1);
	}
        const int kk=h1[0]->GetNbinsX();
        for(int i=0;i<num;i++){
                h1[i]->SetBinContent(kk,h1[i]->GetBinContent(kk)+h1[i]->GetBinContent(kk+1));
        }//combine overflow bin
	for(int k=0;k<kk;k++){
            double error=0;
	    double diff=0,sum=0;
            for(int j=0;j<num;j++){
		    if(name.Contains("qcd")){
			    if((j!=5||j!=7)) vec_content.push_back(h1[j]->GetBinContent(k+1));
		    }
                    else if(name.Contains("Sig")&& num<4)
			    vec_content.push_back(h1[j]->GetBinContent(k+1));
	    }
	    biggest = max_element(begin(vec_content),end(vec_content));
	    smallest= min_element(begin(vec_content),end(vec_content));
	    if(h1[0]->GetBinContent(k+1)>0)
		    error=(*biggest - *smallest)/2/h1[0]->GetBinContent(k+1);
	    else    error=0;
            cout<<*biggest<<" "<<*smallest<<" "<<h1[0]->GetBinContent(k+1)<<" "<<error<<endl;
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
            vec_content.clear();
	}
	file1->Close();
	file2->Close();
	file3->Close();
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
     bins.push_back(MvaBins);
     bins.push_back(MjjBins);
     vector<TString> recovars={"ptlep1","photonet","jet1pt","Mva","Mjj"};
     for(int i=0;i<recovars.size();i++){
	     run(recovars[i],"qcd","All",9);
	     run(recovars[i],"SigOut","All",3);
     }
     return 0;
}
