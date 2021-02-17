void open(TString tag, TString var){
	TFile*f1=new TFile("rm_"+var+tag+".root");
	TH2D*h2=(TH2D*)f1->Get("hout");
	int nrows=h2->GetNbinsY();
        int ncols=h2->GetNbinsX();
        TMatrixD A(nrows,ncols);
        for(int i=0;i<nrows;i++){
		for(int j=0;j<ncols;j++){
			A(i,j)=h2->GetBinContent(j+1,i+1);
		}
	}
        TDecompSVD svd(A);
//	svd.Print();
        double contidtionNumber=svd.GetCondition();
	cout<<contidtionNumber<<endl;
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
