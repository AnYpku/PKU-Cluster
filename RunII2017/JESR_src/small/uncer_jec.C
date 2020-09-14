#define num 27
void get_jec(){
        const char* name[num]={
        "AbsoluteStat",
        "AbsoluteScale",
        "AbsoluteMPFBias",
//        "AbsoluteSample",
        "Fragmentation",
        "SinglePionECAL",
        "SinglePionHCAL",
        "FlavorQCD",
        "TimePtEta",
        "RelativeJEREC1",
        "RelativeJEREC2",
        "RelativeJERHF",
        "RelativePtBB",
        "RelativePtEC1",
        "RelativePtEC2",
        "RelativePtHF",
        "RelativeBal",
        "RelativeSample",
        "RelativeFSR",
        "RelativeStatFSR",
        "RelativeStatEC",
        "RelativeStatHF",
        "PileUpDataMC",
        "PileUpPtRef",
        "PileUpPtBB",
        "PileUpPtEC1",
        "PileUpPtEC2",
        "PileUpPtHF"
 //       "Total"
	};
	ofstream f1("./jes-uncertainty-barrel.txt");
	ofstream f2("./jes-source-barrel.txt");
	f2<<"bin"<<"\t"<<"the biggest uncertainty source"<<"\t"<<"uncertainty"<<endl;
	TFile* file = new TFile("./aa.root");
	TH1D* h1 = (TH1D*)file->Get("hist");
	TH1D*h_up[num];
        TH1D*h_down[num];
        for(int i=0;i<num;i++){
		h_up[i] = (TH1D*)file->Get(Form("hist1_up_%i",i));
		h_down[i] = (TH1D*)file->Get(Form("hist1_down_%i",i));
	}

/*	
	ofstream f1("./Uncertainty_2.txt");
 	TFile* file = new TFile("./output.root");
	TH1D* h1 = (TH1D*)file->Get("mjj_new");
	TH1D* h2 = (TH1D*)file->Get("mjj_JEC_up");
	TH1D* h3 = (TH1D*)file->Get("mjj_JEC_down");
*/
	Double_t bincontent_new[8],bincontent_up[8],bincontent_down[8];
	Double_t uncer[8];
        vector<double> vector_unc;
	vector<double>::iterator biggest_pt;
        int position;
		 for(Int_t i=0;i<h1->GetNbinsX();i++){
			 position=0;
                         for(int j=0;j<num;j++){
				 bincontent_new[i] = h1->GetBinContent(i+1);
				 bincontent_up[i] = h_up[j]->GetBinContent(i+1);
				 bincontent_down[i] = h_down[j]->GetBinContent(i+1);
                         //        if(i==3) cout<<bincontent_up[i]<<" "<<bincontent_down[i]<<endl;
				 double max;
				 if(fabs(bincontent_up[i]-bincontent_new[i])>fabs(bincontent_new[i]-bincontent_down[i]) )
					 max = fabs(bincontent_up[i]-bincontent_new[i]);
				 else    max = fabs(bincontent_new[i]-bincontent_down[i]); 
				 uncer[i] = max/bincontent_new[i];
				 //			 cout<<"new "<<bincontent_new[i]<<"; up "<<bincontent_up[i]<<"; down "<<bincontent_down[i]<<endl;
				 //			 cout<<"uncertainty "<<uncer[i]<<endl;
				 f1<<"bin"<<i+1<<": "<<name[j]<<" "<<uncer[i]<<endl;
                                 if(j!=28) vector_unc.push_back(uncer[i]);
			 }
                         cout<<vector_unc.size()<<endl;
			 biggest_pt = max_element(begin(vector_unc),end(vector_unc));     
			 position = distance( begin(vector_unc), biggest_pt);
                         cout<<"bin"<<i+1<<" "<<name[position]<<" "<<*biggest_pt<<endl;
                         f2<<"bin"<<i+1<<" "<<name[position]<<" "<<*biggest_pt<<endl;
                         vector_unc.clear();
		 }
      cout<<endl;
}
int uncer_jec(){
	get_jec();
//	get_jec("ZA_tot");
//	get_jec("ZA-EWK");
return 0;
}
