void run(TString sample, TString tag,int num){
	ofstream ftxt("./uncer_"+sample+"_"+tag+".txt");//,ios::app);
	ofstream ff("./uncer_"+tag+".txt",ios::app);
	TFile*file;
//	if(sample.Contains("qcd"))
//		file=new TFile("./hist_"+sample+"_scale16.root");
//	else
	file=new TFile("./hist_"+sample+"_scale"+tag+".root");
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
        const int kk=h1[0]->GetNbinsX()-2;
        for(int i=0;i<num;i++){
                h1[i]->SetBinContent(kk,h1[i]->GetBinContent(kk)+h1[i]->GetBinContent(kk+1)+h1[i]->GetBinContent(kk+2)+h1[i]->GetBinContent(kk+3));
        }//combine the last three bins and overflow bin to the seventh bin
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
			    ftxt<<"QCD_scale=[";
			    ff<<"QCD_scale=[";
		    }
		    else if(name.Contains("SigOut")){
			    ftxt<<"SigOut_scale=[";
			    ff<<"SigOut_scale=[";
		    }
                    else{
			    ftxt<<"Sig_scale=[";
			    ff<<"Sig_scale=[";
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
int uncer_scale(){
	vector<TString> tag={"16","17","18"};
	for(int i=0;i<tag.size();i++){
		run("qcd",tag[i],9);
		run("SigOut",tag[i],3);
		run("ewk",tag[i],3);
	}
	return 0;
}
