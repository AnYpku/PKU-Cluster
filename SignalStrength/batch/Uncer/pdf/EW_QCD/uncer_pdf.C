#define num 103
void run(TString sample,TString tag){
	ofstream ftxt("./uncer_"+sample+"_"+tag+".txt");//,ios::app);
	ofstream ff("./uncer_"+tag+".txt",ios::app);
	TFile*file;TFile*file1;
	if(sample.Contains("ZA")){
		file=new TFile("./hist_qcd_pdf16.root");
		file1=new TFile("../hist_ewk_pdf"+tag+".root");
	}
	else{
		file=new TFile("./hist_qcdout_pdf16.root");
		file1=new TFile("../hist_Sigout_pdf"+tag+".root");
	}
	double lumi;
	if(tag.Contains("16"))
		lumi=35.86;
	else if(tag.Contains("17"))
		lumi=41.52;
	else if(tag.Contains("18"))
		lumi=58.7;

        TH1D*h1[num];TH1D*hh1[num];
	for(int j=0;j<num;j++){
		h1[j]=(TH1D*)file->Get(Form("hist_%i",j));
		h1[j]->Scale(lumi);
		hh1[j]=(TH1D*)file1->Get(Form("hist_%i",j));
		hh1[j]->Scale(lumi);
                h1[j]->Add(hh1[j]);
	}
        const int kk=h1[0]->GetNbinsX()-2;
        for(int i=0;i<num;i++){
                h1[i]->SetBinContent(kk,h1[i]->GetBinContent(kk)+h1[i]->GetBinContent(kk+1)+h1[i]->GetBinContent(kk+2)+h1[i]->GetBinContent(kk+3));
        }//combine the last three bins and overflow bin to the seventh bin
	for(int k=0;k<kk;k++){
            double error=0;
	    double diff=0,sum=0;
	    double factor=1;
            for(int j=0;j<num;j++){
	       if(sample.Contains("ZA")) factor=h1[0]->Integral()/h1[j]->Integral();
               double center=h1[0]->GetBinContent(k+1);

               diff=factor*h1[j]->GetBinContent(k+1)-center;
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
		    if(sample.Contains("ZA")){
			    ftxt<<"ZA_pdf=[";
			    ff<<"ZA_pdf=[";
		    }
		    else if(sample.Contains("Sigout")){
			    ftxt<<"SigOut_pdf=[";
			    ff<<"SigOut_pdf=[";
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
	for(int i=0;i<tag.size();i++){
		run("Sigout",tag[i]);
		run("ZA",tag[i]);
	}
	return 0;
}
