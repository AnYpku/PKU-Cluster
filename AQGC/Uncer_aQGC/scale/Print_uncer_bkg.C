//#define num 9
void run_combine(TString sample,int num);
void run(TString sample, TString tag,int num){
	ofstream ftxt("./uncer_"+sample+tag+".txt");//,ios::app);
        ofstream fband("./uncer_"+sample+"_scaleband"+tag+".txt");
	ofstream f_up,f_down;
	if(sample.Contains("qcd")){
		f_up.open("./uncer_QCD_extra_up"+tag+".txt");//,ios::app);
		f_down.open("./uncer_QCD_extra_down"+tag+".txt");//,ios::app);
	}
	ofstream ff("./uncer_"+tag+".txt",ios::app);
	TFile*file=new TFile("./hist_"+sample+"_scale"+tag+".root");
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
		h1[j]=(TH1D*)file->Get(Form("hist_%i",j));
		h1[j]->Scale(lumi);
	}
        const int kk=h1[0]->GetNbinsX();
	double scale_band1[kk],scale_band2[kk],scale_band3[kk];
	for(int k=0;k<kk;k++){
            double error=0,extra_up=0,extra_down=0;
	    double diff=0,sum=0;
            for(int j=0;j<num;j++){
		    if(name.Contains("qcd")){
			    if(!(j==5||j==7)) {
				    vec_content.push_back(h1[j]->GetBinContent(k+1));
//                                    cout<<"hist"<<j+1<<endl;
			    }
		    }
                    else if(name.Contains("qcd")==0&& num<4)
			    vec_content.push_back(h1[j]->GetBinContent(k+1));
	    }
	    biggest = max_element(begin(vec_content),end(vec_content));
	    smallest= min_element(begin(vec_content),end(vec_content));
	    if(h1[0]->GetBinContent(k+1)>0){
		    error=(*biggest - *smallest)/2/h1[0]->GetBinContent(k+1);
		    if(name.Contains("qcd")){
			    scale_band1[k]=fabs(vec_content[5]-vec_content[3])/2/h1[0]->GetBinContent(k+1);
			    scale_band2[k]=fabs(vec_content[2]-vec_content[1])/2/h1[0]->GetBinContent(k+1);
			    scale_band3[k]=fabs(vec_content[6]-vec_content[4])/2/h1[0]->GetBinContent(k+1);
                            cout<<tag<<" "<<scale_band1[k]<<" "<<scale_band2[k]<<" "<<scale_band3[k]<<endl;
		    }
	    }
	    else{    error=0;
                     scale_band1[k]=0;
		     scale_band2[k]=0;
		     scale_band3[k]=0;
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
//			    cout<<extra_down<<endl;
			    f_down<<fixed<<setprecision(3)<<extra_down<<",";
			    ff<<fixed<<setprecision(3)<<1+error<<",";
		    }
		    if(k==kk-1){
			    ftxt<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
			    f_up<<fixed<<setprecision(3)<<extra_up<<"]"<<endl;
//			    cout<<"file open ? "<<f_down.is_open()<<endl;
			    f_down<<fixed<<setprecision(3)<<extra_down<<"]"<<endl;
			    ff<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
		    }
	    }
            else if(name.Contains("SigOut")){
		    if(k==0){
			        ftxt<<"SigOut_scale=[";
			        ff<<"SigOut_scale=[";
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
            else if(name.Contains("ewk")){
		    if(k==0){
			        ftxt<<"Sig_scale=[";
			        ff<<"Sig_scale=[";
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
            vec_content.clear();
	}
           for(int j=0;j<kk;j++){
             if(j==0)    fband<<"scale_band1=[";
	     if(j<kk-1)  fband<<fixed<<setprecision(3)<<1+scale_band1[j]<<","; 
             if(j==kk-1) fband<<fixed<<setprecision(3)<<1+scale_band1[j]<<"]"<<endl; 
	   }
           for(int j=0;j<kk;j++){
             if(j==0)    fband<<"scale_band2=[";
             if(j<kk-1)  fband<<fixed<<setprecision(3)<<1+scale_band2[j]<<","; 
             if(j==kk-1) fband<<fixed<<setprecision(3)<<1+scale_band2[j]<<"]"<<endl; 
	   }
           for(int j=0;j<kk;j++){
             if(j==0)    fband<<"scale_band3=[";
             if(j<kk-1)  fband<<fixed<<setprecision(3)<<1+scale_band3[j]<<","; 
             if(j==kk-1) fband<<fixed<<setprecision(3)<<1+scale_band3[j]<<"]"<<endl; 
	   }
}
int Print_uncer_bkg(){
        vector<TString> tag={"16","17","18"};
	run_combine("qcd",9);
	run_combine("ewk",3);
	for(int i=0;i<tag.size();i++){
		run("qcd",tag[i],9);
	      //run("SigOut",tag[i],3);
		run("ewk",tag[i],3);
	}
	return 0;
}
void run_combine(TString sample,int num){
	ofstream ftxt("./uncer_"+sample+".txt");//,ios::app);
	ofstream fband("./uncer_"+sample+"_scaleband.txt");
	ofstream f_up,f_down;
	if(sample.Contains("qcd")){
		f_up.open("./uncer_QCD_extra_up.txt");//,ios::app);
		f_down.open("./uncer_QCD_extra_down.txt");//,ios::app);
	}
	ofstream ff("./uncer_full.txt",ios::app);
	TFile*file1=new TFile("./hist_"+sample+"_scale16.root");
	TFile*file2=new TFile("./hist_"+sample+"_scale17.root");
	TFile*file3=new TFile("./hist_"+sample+"_scale18.root");
	TString name=file1->GetName();
	TH1D*h1[num];TH1D*h2[num];TH1D*h3[num];
	vector<double> vec_content;
	vector<Double_t>:: iterator biggest;
	vector<Double_t>:: iterator smallest;
	double max,min;
	for(int j=0;j<num;j++){
		h1[j]=(TH1D*)file1->Get(Form("hist_%i",j));
		h1[j]->Scale(35.86);
		h2[j]=(TH1D*)file2->Get(Form("hist_%i",j));
		h2[j]->Scale(41.52);
		h3[j]=(TH1D*)file3->Get(Form("hist_%i",j));
		h3[j]->Scale(58.7);
		h1[j]->Add(h2[j],1);
		h1[j]->Add(h3[j],1);
	}
	const int kk=h1[0]->GetNbinsX();
	double scale_band1[kk],scale_band2[kk],scale_band3[kk];
	for(int k=0;k<kk;k++){
		double error=0,extra_up=0,extra_down=0;
		double diff=0,sum=0;
		for(int j=0;j<num;j++){
			if(name.Contains("qcd")){
				if(!(j==5||j==7)) {
					vec_content.push_back(h1[j]->GetBinContent(k+1));
					//                                    cout<<"hist"<<j+1<<endl;
				}
			}
			else if(name.Contains("qcd")==0&& num<4)
				vec_content.push_back(h1[j]->GetBinContent(k+1));
		}
		biggest = max_element(begin(vec_content),end(vec_content));
		smallest= min_element(begin(vec_content),end(vec_content));
		if(h1[0]->GetBinContent(k+1)>0){
			error=(*biggest - *smallest)/2/h1[0]->GetBinContent(k+1);
			if(name.Contains("qcd")){
				scale_band1[k]=fabs(vec_content[5]-vec_content[3])/2/h1[0]->GetBinContent(k+1);
				scale_band2[k]=fabs(vec_content[2]-vec_content[1])/2/h1[0]->GetBinContent(k+1);
				scale_band3[k]=fabs(vec_content[6]-vec_content[4])/2/h1[0]->GetBinContent(k+1);
				cout<<"combined "<<scale_band1[k]<<" "<<scale_band2[k]<<" "<<scale_band3[k]<<endl;
			}
		}
		else{    error=0;
			scale_band1[k]=0;
			scale_band2[k]=0;
			scale_band3[k]=0;
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
				//			    cout<<extra_down<<endl;
				f_down<<fixed<<setprecision(3)<<extra_down<<",";
				ff<<fixed<<setprecision(3)<<1+error<<",";
			}
			if(k==kk-1){
				ftxt<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
				f_up<<fixed<<setprecision(3)<<extra_up<<"]"<<endl;
				//			    cout<<"file open ? "<<f_down.is_open()<<endl;
				f_down<<fixed<<setprecision(3)<<extra_down<<"]"<<endl;
				ff<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
			}
		}
		else if(name.Contains("SigOut")){
			if(k==0){
				ftxt<<"SigOut_scale=[";
				ff<<"SigOut_scale=[";
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
		else if(name.Contains("ewk")){
			if(k==0){
				ftxt<<"Sig_scale=[";
				ff<<"Sig_scale=[";
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
		vec_content.clear();
	}
	for(int j=0;j<kk;j++){
		if(j==0)    fband<<"scale_band1=[";
		if(j<kk-1)  fband<<fixed<<setprecision(3)<<1+scale_band1[j]<<","; 
		if(j==kk-1) fband<<fixed<<setprecision(3)<<1+scale_band1[j]<<"]"<<endl; 
	}
	for(int j=0;j<kk;j++){
		if(j==0)    fband<<"scale_band2=[";
		if(j<kk-1)  fband<<fixed<<setprecision(3)<<1+scale_band2[j]<<","; 
		if(j==kk-1) fband<<fixed<<setprecision(3)<<1+scale_band2[j]<<"]"<<endl; 
	}
	for(int j=0;j<kk;j++){
		if(j==0)    fband<<"scale_band3=[";
		if(j<kk-1)  fband<<fixed<<setprecision(3)<<1+scale_band3[j]<<","; 
		if(j==kk-1) fband<<fixed<<setprecision(3)<<1+scale_band3[j]<<"]"<<endl; 
	}
}
