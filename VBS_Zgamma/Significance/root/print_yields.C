void run(TString sample,TString tag,TString channel){
	TFile*file=new TFile("hist_"+sample+"_"+tag+channel+".root");
	TH1D*h1;
	if(sample.Contains("EWK")==0)
		h1=(TH1D*)file->Get("hist_bkg");
	else h1=(TH1D*)file->Get("hist_sig");
	double yields,yErr;
	int num=h1->GetNbinsX();
	yields=h1->IntegralAndError(0,num,yErr);
//        cout<<sample<<" "<<channel<<endl;
        cout<<tag<<" "<<sample<<" "<<fixed<<setprecision(2)<<yields<<"+-"<<yErr<<endl; 

}
int print_yields(){
//	vector<TString> names={"ZA-EWK","ST","VV","TTA","ZA","plj"};
	vector<TString> names={"WWA","WZA","WW","WZ","ZZ","VV"};
	vector<TString> channels={"mubarrel","muendcap","elebarrel","eleendcap"};
	vector<TString> tag={"16","17","18"};
	for(int k=0;k<tag.size();k++){
		for(int j=0;j<channels.size();j++){
			cout<<channels[j]<<endl;
			for(int i=0;i<names.size();i++){
				run(names[i],tag[k],channels[j]);
			}
		}
	}
	return 0;
}
