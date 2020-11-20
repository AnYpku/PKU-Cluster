#define num 103
void run_combine(TString sample);
void run(TString sample, TString tag){
	ofstream ftxt("./uncer_"+sample+tag+".txt");//,ios::app);
	ofstream ff("./uncer_"+tag+".txt",ios::app);
	TFile*file;
	if(sample.Contains("qcd"))
		file=new TFile("./hist_"+sample+"_pdf16.root");
	else
		file=new TFile("./hist_"+sample+"_pdf"+tag+".root");
        TString name=file->GetName();
	double lumi;
	if(tag.Contains("16"))
		lumi=35.86;
	else if(tag.Contains("17"))
		lumi=41.52;
	else if(tag.Contains("18"))
		lumi=58.7;

        TH1D*h1[num];
	for(int j=0;j<num;j++){
		h1[j]=(TH1D*)file->Get(Form("hist_%i",j));
		h1[j]->Scale(lumi);
	}
        const int kk=h1[0]->GetNbinsX();
	for(int k=0;k<kk;k++){
            double error=0;
	    double diff=0,sum=0;
            for(int j=0;j<num;j++){
               double center=h1[0]->GetBinContent(k+1);
               diff=h1[j]->GetBinContent(k+1)-center;
	       sum+=pow(diff,2);
	    }
	    if(h1[0]->GetBinContent(k+1)!=0)
		    cout<<sample<<" "<<tag<<" "<<sqrt(sum/(num-1))<<" "<<h1[0]->GetBinContent(k+1)<<" "<<sqrt(sum/(num-1))/h1[0]->GetBinContent(k+1)<<endl;
	    else
		    cout<<sample<<" "<<tag<<" "<<sqrt(sum/(num-1))<<" "<<h1[0]->GetBinContent(k+1)<<" no data in bin"<<k+1<<endl;
            if(h1[0]->GetBinContent(k+1)!=0)
                    error=sqrt(sum/(num-1))/h1[0]->GetBinContent(k+1);
            else    error=0;
	    if(k==0){
		    if(name.Contains("qcd")){
			    ftxt<<"QCD_pdf=[";
			    ff<<"QCD_pdf=[";
		    }
		    else if(name.Contains("Sigout")){
			    ftxt<<"SigOut_pdf=[";
			    ff<<"SigOut_pdf=[";
		    }
                    else{
			    ftxt<<"Sig_pdf=[";
			    ff<<"Sig_pdf=[";
		    }
	    }
	    if(k<kk-1){
		    ftxt<<fixed<<setprecision(3)<<1+error<<",";
		    ff<<fixed<<setprecision(3)<<1+error<<",";
	    }
	    if(k==kk-1){
		    ftxt<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
		    ff<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
	    }
	}
}
int uncer_pdf(){
	vector<TString> tag={"16","17","18"};
	run_combine("qcd");
	run_combine("ewk");
	for(int i=0;i<tag.size();i++){
		run("qcd",tag[i]);
		//		run("Sigout",tag[i]);
		run("ewk",tag[i]);
	}
	return 0;
}
void run_combine(TString sample){
	ofstream ftxt("./uncer_"+sample+".txt");//,ios::app);
	ofstream ff("./uncer_full.txt",ios::app);
	TFile*file1;TFile*file2;TFile*file3;
	if(sample.Contains("qcd"))
		file1=new TFile("./hist_"+sample+"_pdf16.root");
	else{
		file1=new TFile("./hist_"+sample+"_pdf16.root");
		file2=new TFile("./hist_"+sample+"_pdf17.root");
		file3=new TFile("./hist_"+sample+"_pdf18.root");
	}
	TString name=file1->GetName();

	TH1D*h1[num];TH1D*h2[num];TH1D*h3[num];
	for(int j=0;j<num;j++){
		h1[j]=(TH1D*)file1->Get(Form("hist_%i",j));
		h1[j]->Scale(35.86);
		if(sample.Contains("qcd")==0){
			h2[j]=(TH1D*)file2->Get(Form("hist_%i",j));
			h2[j]->Scale(41.52);
			h3[j]=(TH1D*)file3->Get(Form("hist_%i",j));
			h3[j]->Scale(58.7);
			h1[j]->Add(h2[j],1);
			h1[j]->Add(h3[j],1);
		}
	}
	const int kk=h1[0]->GetNbinsX();
	for(int k=0;k<kk;k++){
		double error=0;
		double diff=0,sum=0;
		for(int j=0;j<num;j++){
			double center=h1[0]->GetBinContent(k+1);
			diff=h1[j]->GetBinContent(k+1)-center;
			sum+=pow(diff,2);
		}
		if(h1[0]->GetBinContent(k+1)!=0)
			cout<<sample<<" combined "<<sqrt(sum/(num-1))<<" "<<h1[0]->GetBinContent(k+1)<<" "<<sqrt(sum/(num-1))/h1[0]->GetBinContent(k+1)<<endl;
		else
			cout<<sample<<" combined  "<<sqrt(sum/(num-1))<<" "<<h1[0]->GetBinContent(k+1)<<" no data in bin"<<k+1<<endl;
		if(h1[0]->GetBinContent(k+1)!=0)
			error=sqrt(sum/(num-1))/h1[0]->GetBinContent(k+1);
		else    error=0;
		if(k==0){
			if(name.Contains("qcd")){
				ftxt<<"QCD_pdf=[";
				ff<<"QCD_pdf=[";
			}
			else if(name.Contains("Sigout")){
				ftxt<<"SigOut_pdf=[";
				ff<<"SigOut_pdf=[";
			}
			else{
				ftxt<<"Sig_pdf=[";
				ff<<"Sig_pdf=[";
			}
		}
		if(k<kk-1){
			ftxt<<fixed<<setprecision(3)<<1+error<<",";
			ff<<fixed<<setprecision(3)<<1+error<<",";
		}
		if(k==kk-1){
			ftxt<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
			ff<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
		}
	}
}
