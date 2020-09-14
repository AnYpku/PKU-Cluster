void get_jec(TString name){
	ofstream f1("./2017jes-uncertainty-barrel_"+name+".txt");
	cout<<"open file "<<name<<endl;
	TFile* file = new TFile("./aa_"+name+".root");
	TH1D* h1 = (TH1D*)file->Get("hist_1");
	TH1D* h2 = (TH1D*)file->Get("hist_2");
	TH1D* h3 = (TH1D*)file->Get("hist_3");

/*	
	ofstream f1("./Uncertainty_2.txt");
 	TFile* file = new TFile("./output.root");
	TH1D* h1 = (TH1D*)file->Get("mjj_new");
	TH1D* h2 = (TH1D*)file->Get("mjj_JEC_up");
	TH1D* h3 = (TH1D*)file->Get("mjj_JEC_down");
*/
	Double_t bincontent_new[8],bincontent_up[8],bincontent_down[8];
	Double_t uncer[8];
		 for(Int_t i=0;i<h1->GetNbinsX();i++){
			 bincontent_new[i] = h1->GetBinContent(i+1);
			 bincontent_up[i] = h2->GetBinContent(i+1);
			 bincontent_down[i] = h3->GetBinContent(i+1);
                         double max;
                         if(fabs(bincontent_up[i]-bincontent_new[i])>fabs(bincontent_new[i]-bincontent_down[i]) )
				 max = fabs(bincontent_up[i]-bincontent_new[i]);
                         else    max = fabs(bincontent_new[i]-bincontent_down[i]); 
                         uncer[i] = max/bincontent_new[i];
//			 cout<<"new "<<bincontent_new[i]<<"; up "<<bincontent_up[i]<<"; down "<<bincontent_down[i]<<endl;
//			 cout<<"uncertainty "<<uncer[i]<<endl;
			 cout<<", "<<uncer[i];
			 f1<<uncer[i]<<endl;
		 }
      cout<<"finish calculating"<<endl;
      cout<<endl;
}
int uncer_jec(){
//	get_jec("ZA_v3");
	get_jec("ZA");
	get_jec("ZA-EWK");
return 0;
}
