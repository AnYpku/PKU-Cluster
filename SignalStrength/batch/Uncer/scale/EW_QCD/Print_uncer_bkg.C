//#define num 9
void run(TString sample, TString tag,int num){
	ofstream ftxt("./uncer_"+sample+"_"+tag+".txt");//,ios::app);
	ofstream f_up,f_down;
	ofstream ff("./uncer_"+tag+".txt",ios::app);
	TFile*file;
        TFile*file1;TFile*file2;
	if(sample.Contains("ZA")){
		file =new TFile("./hist_qcd_scale"+tag+".root");
		file1=new TFile("../hist_ewk_scale"+tag+".root");
		file2=new TFile("./hist_interf_scale"+tag+".root");
	}
	else{
		file =new TFile("./hist_qcdout_scale"+tag+".root");
		file1=new TFile("../hist_SigOut_scale"+tag+".root");
		file2=new TFile("./hist_interfout_scale"+tag+".root");
	}
	double lumi;
	if(tag.Contains("16"))
		lumi=35.86;
	else if(tag.Contains("17"))
		lumi=41.52;
	else if(tag.Contains("18"))
		lumi=58.7;

        TH1D*h1[num];TH1D*hh1[num];
        TH1D*h2[num];TH1D*hh2[num];
	vector<double> vec_content;
	vector<Double_t>:: iterator biggest;
	vector<Double_t>:: iterator smallest;
        double max,min;
	for(int j=0;j<num;j++){
		h1[j]=(TH1D*)file->Get(Form("hist_%i",j));
	}
	for(int i=0;i<3;i++){
		hh1[i]=(TH1D*)file1->Get(Form("hist_%i",i));//0->0,3,6;1->1,4;2->2,8
		h2[i]=(TH1D*)file2->Get(Form("hist_%i",i));
                hh1[i]->Add(h2[i]);
	}
        const int kk=h1[0]->GetNbinsX()-2;
        for(int i=0;i<num;i++){
                h1[i]->SetBinContent(kk,h1[i]->GetBinContent(kk)+h1[i]->GetBinContent(kk+1)+h1[i]->GetBinContent(kk+2)+h1[i]->GetBinContent(kk+3));
        }//combine the last three bins and overflow bin to the seventh bin
	for(int i=0;i<3;i++){
                hh1[i]->SetBinContent(kk,hh1[i]->GetBinContent(kk)+hh1[i]->GetBinContent(kk+1)+hh1[i]->GetBinContent(kk+2)+hh1[i]->GetBinContent(kk+3));
        }//combine the last three bins and overflow bin to the seventh bin
	for(int k=0;k<kk;k++){
            double factor=1;
            double error=0,extra_up=0,extra_down=0;
	    double diff=0,sum=0;
            for(int j=0;j<num;j++){
                    if(j==0||j==3||j==6) h1[j]->Add(hh1[0]);
                    if(j==1||j==4) h1[j]->Add(hh1[1]);
                    if(j==2||j==8) h1[j]->Add(hh1[2]);
		    factor=h1[0]->Integral()/h1[j]->Integral();
		    if(sample.Contains("ZA")){
			    if(!(j==5||j==7)) vec_content.push_back(factor*h1[j]->GetBinContent(k+1));
			    cout<<tag<<" "<<sample<<" "<<factor<<endl;
		    }
		    else
			    vec_content.push_back(h1[j]->GetBinContent(k+1));
	    }
	    biggest = max_element(begin(vec_content),end(vec_content));
	    smallest= min_element(begin(vec_content),end(vec_content));
	    if(h1[0]->GetBinContent(k+1)>0){
		    error=(*biggest - *smallest)/2/h1[0]->GetBinContent(k+1);
	    }
            cout<<tag<<" "<<sample<<" "<<*biggest<<" "<<*smallest<<" "<<h1[0]->GetBinContent(k+1)<<" "<<error<<endl;
	    if(sample.Contains("ZA")){
		    if(k==0){
			        ftxt<<"ZA_scale=[";
			        ff<<"ZA_scale=[";
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
            else if(sample.Contains("SigOut")){
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
            vec_content.clear();
	}
}
int Print_uncer_bkg(){
	vector<TString> tag={"16","17","18"};
	for(int i=0;i<tag.size();i++){
		run("ZA",tag[i],9);
		run("SigOut",tag[i],9);
	}
	return 0;
}
