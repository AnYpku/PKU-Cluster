void draw(){
	TFile*f1=new TFile("higgsCombineTest.MultiDimFit.mH120.1.root");
	TTree*tree=(TTree*)f1->Get("limit");
	int iToy;float deltaNLL,param;
        vector<double> t_alpha;
	tree->SetBranchAddress("iToy",&iToy);
	tree->SetBranchAddress("deltaNLL",&deltaNLL);
	tree->SetBranchAddress("param",&param);
	for(int i=0;i<tree->GetEntries();i++){
                 tree->GetEntry(i);
		 for(int j=1;j<=1000;j++){
			 if(iToy==j && param>1 && param<1.03){
                              t_alpha.push_back(2*deltaNLL);
//			      cout<<i<<" "<<" "<<j<<" "<<deltaNLL<<" "<<2*deltaNLL<<endl;
			 }
		 }
	}
        const int size=t_alpha.size();
        sort(t_alpha.begin(), t_alpha.end(), greater<double>());
        TH1D*h1=new TH1D("h1","test-statistics distribution",100,0,12);
        cout<<t_alpha[0]<<" "<<t_alpha[size]<<endl;
        for(int i=0;i<size;i++){
		h1->Fill(t_alpha[i]);
	}
        TFile*f2=new TFile("histo_test-statistics.root","recreate");
        f2->cd();
        h1->Write();
	f2->Close();
}
