//#define num 9
void run(TString sample, TString tag,int num){
	ofstream ftxt("./uncer_"+sample+"_"+tag+"CR.txt");//,ios::app);
	ofstream f_up,f_down;
	if(sample.Contains("qcd")){
		f_up.open("./uncer_QCD_extra_up_"+tag+"CR.txt");//,ios::app);
		f_down.open("./uncer_QCD_extra_down_"+tag+"CR.txt");//,ios::app);
	}
	ofstream ff("./uncer_"+tag+"CR.txt",ios::app);
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
//        const int kk=h1[0]->GetNbinsX()-2;
//        for(int i=0;i<num;i++){
//                h1[i]->SetBinContent(kk,h1[i]->GetBinContent(kk)+h1[i]->GetBinContent(kk+1)+h1[i]->GetBinContent(kk+2)+h1[i]->GetBinContent(kk+3));
//        }//combine the last three bins and overflow bin to the seventh bin
	for(int k=0;k<kk;k++){
            double error=0,extra_up=0,extra_down=0;
	    double diff=0,sum=0;
            for(int j=0;j<num;j++){
		    if(name.Contains("qcd")){
			    if(!(j==5||j==7)) vec_content.push_back(h1[j]->GetBinContent(k+1));
		    }
                    else if(name.Contains("qcd")==0&& num<4)
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
			    ff<<fixed<<setprecision(3)<<1+error<<",";
		    }
		    if(k==kk-1){
			    ftxt<<fixed<<setprecision(3)<<1+error<<"]"<<endl;
			    f_up<<fixed<<setprecision(3)<<extra_up<<"]"<<endl;
			    cout<<"file open ? "<<f_down.is_open()<<endl;
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
}
int Print_uncer_bkg(){
        vector<TString> tag={"16","17","18"};
	for(int i=0;i<tag.size();i++){
		run("qcd",tag[i],9);
//		run("SigOut",tag[i],3);
		run("ewk",tag[i],3);
	}
	return 0;
}
