//#define num 9
void run(TString var,TString sample, TString tag,int num){
	ofstream ftxt("./"+var+"_uncer_"+sample+"_"+tag+"CR.txt");//,ios::app);
	ofstream f_up,f_down;
	if(sample.Contains("qcd")){
		f_up.open("./"+var+"_uncer_QCD_extra_up_"+tag+"CR.txt");//,ios::app);
		f_down.open("./"+var+"_uncer_QCD_extra_down_"+tag+"CR.txt");//,ios::app);
	}
	ofstream ff("./"+var+"_uncer_"+tag+"CR.txt",ios::app);
	TFile*file=new TFile("./bkg_root/unfold_"+var+"_"+sample+"_scale"+tag+".root");
	TString name=file->GetName();
	double lumi;
	if(tag.Contains("16"))
		lumi=35.86;
	else if(tag.Contains("17"))
		lumi=41.52;
	else if(tag.Contains("18"))
		lumi=58.7;

        TH1D*h1[num];
	vector<double> vec_content;
	vector<Double_t>:: iterator biggest;
	vector<Double_t>:: iterator smallest;
        double max,min;
	for(int j=0;j<num;j++){
		h1[j]=(TH1D*)file->Get(Form(var+"_%i",j));
		h1[j]->Scale(lumi);
	}
        const int kk=h1[0]->GetNbinsX();
        for(int i=0;i<num;i++){
                h1[i]->SetBinContent(kk,h1[i]->GetBinContent(kk)+h1[i]->GetBinContent(kk+1));
        }//combine overflow bin
	for(int k=0;k<kk;k++){
            double error=0,extra_up=0,extra_down=0;
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
//            cout<<*biggest<<" "<<*smallest<<" "<<h1[0]->GetBinContent(k+1)<<" "<<error<<endl;
	    if(name.Contains("qcd")){
		    max=h1[6]->GetBinContent(k+1);min=h1[3]->GetBinContent(k+1);
		    extra_up = 1 + (max-h1[0]->GetBinContent(k+1))/h1[0]->GetBinContent(k+1);
		    extra_down= 1 - (h1[0]->GetBinContent(k+1)-min)/h1[0]->GetBinContent(k+1);
		    cout<< extra_up <<" "<<extra_down<<endl;
		    if(k==0){
			        ftxt<<"QCD_scale=[";
			        ff<<"QCD_scale=[";
                                f_up<<"QCD_scale_up=[";
                                f_down<<"QCD_scale_down=[";
		    }
		    if(k<kk-1){
			    ftxt<<fixed<<setprecision(3)<<1+error<<",";
			    f_up<<fixed<<setprecision(3)<<extra_up<<",";
			    f_down<<fixed<<setprecision(3)<<extra_down<<",";
		    }
		    ff<<error<<",";
		    if(k==kk-1){
			    ftxt<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
			    f_up<<fixed<<setprecision(3)<<extra_up<<"]"<<endl;
			    f_down<<fixed<<setprecision(3)<<extra_down<<"]"<<endl;
			    ff<<"]"<<endl;
		    }
	    }
            else{
		    if(k==0){
			        ftxt<<"SigOut_scale=[";
			        ff<<"SigOut_scale=[";
		    }
		    if(k<kk-1)ftxt<<fixed<<setprecision(3)<<1+error<<",";
		    ff<<error<<",";
		    if(k==kk-1){
			    ftxt<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
			    ff<<"]"<<endl;
		    }
	    } 
            vec_content.clear();
	}
}
/*void open(TString var,vector<double> genbins,TString tag){
        const int kk=genbins.size();
	double uncer[kk-1][kk-1];
	ofstream fout("./"+var+"_uncer"+tag+"CR.txt");
	for(int k=0;k<kk-1;k++){
		ifstream f1(Form(".CR.txt/"+var+"_recobin%i_uncer"+tag+"CR.txt",k+1));
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
     bins.push_back(MvaBins);
     bins.push_back(MjjBins);
     vector<TString> recovars={"ptlep1","photonet","jet1pt","Mjj"};
     for(int i=0;i<recovars.size();i++){
	     run(recovars[i],"qcd","16",9);
	     run(recovars[i],"qcd","17",9);
	     run(recovars[i],"qcd","18",9);
	     run(recovars[i],"SigOut","16",3);
	     run(recovars[i],"SigOut","17",3);
	     run(recovars[i],"SigOut","18",3);
     }
     return 0;
}
