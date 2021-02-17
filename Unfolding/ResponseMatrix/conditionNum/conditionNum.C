void open(TString tag, TString var){
	TFile*f1=new TFile("rm_"+var+tag+".root");
	TH2D*h2=(TH2D*)f1->Get("hout");
	const int nrows=h2->GetNbinsY();
        int ncols=h2->GetNbinsX();
        TMatrixD A(nrows,ncols);
        for(int i=0;i<nrows;i++){
		for(int j=0;j<ncols;j++){
			A(i,j)=h2->GetBinContent(j+1,i+1);
//			A(i,j)=h2->GetBinContent(j+1,nrows-i);
		}
	}
        TDecompSVD svd(A);
	Bool_t ok;
	cout<<nrows<<" "<<ncols<<endl;
	vector<double> arr={10,20,30,10};
	TVectorD y(nrows,&arr[0]);
//	y.Use(nrows,ncols);
	const TVectorD c_svd = svd.Solve(y,ok);
//	c_svd.Print();
//	svd.Print();
	cout << "decomposed   " << svd.Decompose() << endl;
	cout << "condition nb " << svd.GetCondition() << endl;
	cout << "singular     ";
	svd.GetSig().Print();
	cout << endl;
	double contidtionNumber=svd.GetCondition();
	cout<<contidtionNumber<<endl;
	double det = A.Determinant(); 
	double d1,d2;
	svd.Det(d1,d2);
	bool dep=svd.Decompose();
	//	TVectorD fSig=svd.GetSig();
	//        fSig.Print(); 
	//	cout<<dep<<endl;
	//	cout<<d1<<" "<<d2<<" "<<d1*pow(2,d2)<<endl;
	//	cout<<det<<endl;
	//	return contidtionNumber;
}
int conditionNum(){
	vector<TString> tag={"16","17","18"};
	vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt","genMjj"};
	for(int i=0;i<tag.size();i++){
		for(int j=0;j<genvars.size();j++){
			cout<<tag[i]<<" "<<genvars[j]<<" ";
			open(tag[i],genvars[j]);
			cout<<endl;
		}
	}
	return 0;
}
