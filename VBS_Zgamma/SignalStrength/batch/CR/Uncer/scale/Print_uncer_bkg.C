//#define num 9
void run(TString sample, TString tag,int num){
	ofstream ftxt("./uncer_"+sample+"_"+tag+"CR.txt");//,ios::app);
	ofstream f_up,f_down;
        ofstream fband("./uncer_"+sample+"_scaleband_"+tag+"CR.txt");
	if(sample.Contains("qcd")){
		f_up.open("./uncer_QCD_extra_up_"+tag+"CR.txt");//,ios::app);
		f_down.open("./uncer_QCD_extra_down_"+tag+"CR.txt");//,ios::app);
	}
	ofstream ff("./uncer_"+tag+"CR.txt",ios::app);
	TFile*file=new TFile("./hist_"+sample+"_scale"+tag+"CR.root");
        TH1D*h1[num];
	for(int j=0;j<num;j++){
		h1[j]=(TH1D*)file->Get(Form("hist_%i",j));
	}
	TH1D*hh1[3];
	if(sample.Contains("qcd")){
                TFile*file1=new TFile("./hist_interf_scale"+tag+"CR.root");
		for(int j=0;j<3;j++){
			hh1[j]=(TH1D*)file1->Get(Form("hist_%i",j));
		}
	}
	TString name=file->GetName();
	double lumi;
	if(tag.Contains("16"))
		lumi=35.86;
	else if(tag.Contains("17"))
		lumi=41.52;
	else if(tag.Contains("18"))
		lumi=59.7;

	vector<double> vec_content;
	vector<Double_t>:: iterator biggest;
	vector<Double_t>:: iterator smallest;
        double max,min;
        const int kk=h1[0]->GetNbinsX();
        double scale_muR1[kk],scale_muF1[kk],scale_muFmuR[kk];
	for(int k=0;k<kk;k++){
            double error=0,extra_up=0,extra_down=0;
	    double diff=0,sum=0;
	    double factor=1;
            for(int j=0;j<num;j++){
		    if(name.Contains("qcd")){
                            if(j==0||j==3||j==6) h1[j]->Add(hh1[0]);
                            if(j==1||j==4) h1[j]->Add(hh1[1]);
                            if(j==2||j==8) h1[j]->Add(hh1[2]);
			    if(!(j==5||j==7)) vec_content.push_back(h1[j]->GetBinContent(k+1));
		    }
                    else if(name.Contains("qcd")==0&& num<4)
                            factor=h1[0]->Integral()/h1[j]->Integral();
                            cout<<tag<<" "<<name<<" "<<factor<<endl;
                            if(name.Contains("ewk"))
                                    vec_content.push_back(factor*h1[j]->GetBinContent(k+1));
                            else
                                    vec_content.push_back(h1[j]->GetBinContent(k+1));
	    }
	    biggest = max_element(begin(vec_content),end(vec_content));
	    smallest= min_element(begin(vec_content),end(vec_content));
	    if(h1[0]->GetBinContent(k+1)>0){
		    error=(*biggest - *smallest)/2/h1[0]->GetBinContent(k+1);
                    if(name.Contains("qcd")){
                            scale_muR1[k]=fabs(h1[6]->GetBinContent(k+1)-h1[3]->GetBinContent(k+1))/2/h1[0]->GetBinContent(k+1);
                            scale_muF1[k]=fabs(h1[1]->GetBinContent(k+1)-h1[2]->GetBinContent(k+1))/2/h1[0]->GetBinContent(k+1);
                            scale_muFmuR[k]=fabs(h1[4]->GetBinContent(k+1)-h1[8]->GetBinContent(k+1))/2/h1[0]->GetBinContent(k+1);
//                            scale_muR1[k]=fabs(vec_content[5]-vec_content[3])/2/h1[0]->GetBinContent(k+1);
//                            scale_muF1[k]=fabs(vec_content[2]-vec_content[1])/2/h1[0]->GetBinContent(k+1);
//                            scale_muFmuR[k]=fabs(vec_content[6]-vec_content[4])/2/h1[0]->GetBinContent(k+1);
                            cout<<tag<<" "<<scale_muR1[k]<<" "<<scale_muF1[k]<<" "<<scale_muFmuR[k]<<endl;
                    }
	    }
	    else{    error=0;
                     scale_muR1[k]=0;
                     scale_muF1[k]=0;
                     scale_muFmuR[k]=0;
	    }
//            cout<<*biggest<<" "<<*smallest<<" "<<h1[0]->GetBinContent(k+1)<<" "<<error<<endl;
	    if(name.Contains("qcd")){
		    max=h1[6]->GetBinContent(k+1);min=h1[3]->GetBinContent(k+1);
		    extra_up = 1 + (max-h1[0]->GetBinContent(k+1))/h1[0]->GetBinContent(k+1);
		    extra_down= 1 - (h1[0]->GetBinContent(k+1)-min)/h1[0]->GetBinContent(k+1);
//		    cout<< extra_up <<" "<<extra_down<<endl;
		    if(k==0){
			        ftxt<<"QCD_scale=[";
			        ff<<"QCD_scale=[";
                                f_up<<"QCD_scale_up=[";
                                f_down<<"QCD_scale_down=[";
		    }
		    if(k<kk-1){
			    ftxt<<fixed<<setprecision(3)<<1+error<<",";
			    f_up<<fixed<<setprecision(3)<<extra_up<<",";
			    cout<<extra_down<<endl;
			    f_down<<fixed<<setprecision(3)<<extra_down<<",";
		    }
		    ff<<fixed<<setprecision(3)<<1+error<<",";
		    if(k==kk-1){
			    ftxt<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
			    f_up<<fixed<<setprecision(3)<<extra_up<<"]"<<endl;
			    cout<<"file open ? "<<f_down.is_open()<<endl;
			    f_down<<fixed<<setprecision(3)<<extra_down<<"]"<<endl;
			    ff<<"]"<<endl;
		    }
	    }
            else if(name.Contains("SigOut")){
		    if(k==0){
			        ftxt<<"SigOut_scale=[";
			        ff<<"SigOut_scale=[";
		    }
		    if(k<kk-1)ftxt<<fixed<<setprecision(3)<<1+error<<",";
		    ff<<fixed<<setprecision(3)<<1+error<<",";
		    if(k==kk-1){
			    ftxt<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
			    ff<<"]"<<endl;
		    }
	    } 
            else if(name.Contains("ewk")){
		    if(k==0){
			        ftxt<<"Sig_scale=[";
			        ff<<"Sig_scale=[";
		    }
		    if(k<kk-1)ftxt<<fixed<<setprecision(3)<<1+error<<",";
		    ff<<fixed<<setprecision(3)<<1+error<<",";
		    if(k==kk-1){
			    ftxt<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
			    ff<<"]"<<endl;
		    }
	    } 
            vec_content.clear();
	}
           for(int j=0;j<kk;j++){
             if(j==0)    fband<<"scale_muR1=[";
             if(j<kk-1)  fband<<fixed<<setprecision(3)<<1+scale_muR1[j]<<",";
             if(j==kk-1) fband<<fixed<<setprecision(3)<<1+scale_muR1[j]<<"]"<<endl;
           }
           for(int j=0;j<kk;j++){
             if(j==0)    fband<<"scale_muF1=[";
             if(j<kk-1)  fband<<fixed<<setprecision(3)<<1+scale_muF1[j]<<",";
             if(j==kk-1) fband<<fixed<<setprecision(3)<<1+scale_muF1[j]<<"]"<<endl;
           }
           for(int j=0;j<kk;j++){
             if(j==0)    fband<<"scale_muFmuR=[";
             if(j<kk-1)  fband<<fixed<<setprecision(3)<<1+scale_muFmuR[j]<<",";
             if(j==kk-1) fband<<fixed<<setprecision(3)<<1+scale_muFmuR[j]<<"]"<<endl;
           }
}
int Print_uncer_bkg(){
        vector<TString> tag={"16","17","18"};
	for(int i=0;i<tag.size();i++){
		run("qcd",tag[i],9);
		run("SigOut",tag[i],3);
		run("ewk",tag[i],3);
	}
	return 0;
}
