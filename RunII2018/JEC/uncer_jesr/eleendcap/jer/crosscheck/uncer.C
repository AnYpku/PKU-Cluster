void uncer(){
/*	ofstream f1("./Uncertainty_1.txt");
	TFile* file = new TFile("./aa.root");
	TH1D* h1 = (TH1D*)file->Get("hist_1");
	TH1D* h2 = (TH1D*)file->Get("hist_2");
	TH1D* h3 = (TH1D*)file->Get("hist_3");
*/
	
	ofstream f1("./Uncertainty_2.txt");
 	TFile* file = new TFile("./output.root");
	TH1D* h1 = (TH1D*)file->Get("mjj_new");
	TH1D* h2 = (TH1D*)file->Get("mjj_JEC_up");
	TH1D* h3 = (TH1D*)file->Get("mjj_JEC_down");

	Double_t bincontent_new[8],bincontent_up[8],bincontent_down[8];
	Double_t uncer[8];
		 for(Int_t i=0;i<6;i++){
			 bincontent_new[i] = h1->GetBinContent(i+1);
			 bincontent_up[i] = h2->GetBinContent(i+1);
			 bincontent_down[i] = h3->GetBinContent(i+1);
		 }
		 bincontent_new[6] = h1->GetBinContent(7)+h1->GetBinContent(8);
		 bincontent_new[7] = h1->GetBinContent(9);
		 bincontent_up[6] = h2->GetBinContent(7)+h2->GetBinContent(8);
		 bincontent_up[7] = h2->GetBinContent(9);
		 bincontent_down[6] = h3->GetBinContent(7)+h3->GetBinContent(8);
		 bincontent_down[7] = h3->GetBinContent(9);
		 cout<<h1->GetBinContent(7)<<"; "<<h1->GetBinContent(8)<<"; "<<bincontent_new[6]<<endl;
		 for(int i=0;i<8;i++){
			 uncer[i] = fabs(bincontent_up[i]-bincontent_down[i])/2/bincontent_new[i];
			 cout<<"new "<<bincontent_new[i]<<"; up "<<bincontent_up[i]<<"; down "<<bincontent_down[i]<<endl;
			 cout<<"uncertainty "<<uncer[i]<<endl;
			 f1<<uncer[i]<<endl;
		 }


}
