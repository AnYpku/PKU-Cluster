#define num 103
void run(TString sample, TString tag){
	ofstream ftxt("./uncer_"+sample+"_"+tag+"CR.txt");//,ios::app);
	ofstream ff("./uncer_"+tag+"CR.txt",ios::app);
	TFile*file;
	if(sample.Contains("qcd"))
		file=new TFile("./hist_"+sample+"_pdf16CR.root");
	else
		file=new TFile("./hist_"+sample+"_pdf"+tag+"CR.root");
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
	    if(k<kk-1)
		    ftxt<<fixed<<setprecision(3)<<1+error<<",";
	    ff<<error<<",";
	    if(k==kk-1){
		    ftxt<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
		    ff<<"]"<<endl;
	    }
	}
}
int uncer_pdf(){
	vector<TString> tag={"16","17","18"};
	for(int i=0;i<tag.size();i++){
		run("qcd",tag[i]);
		run("Sigout",tag[i]);
		run("ewk",tag[i]);
	}
	return 0;
}
