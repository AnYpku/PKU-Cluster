void get_jec(TString name){
	ofstream f1("./2016jes-uncertainty-barrel_"+name+".txt");
	cout<<"open file "<<name<<endl;
	TFile* file = new TFile("./aa_"+name+".root");
	TH1D* h1 = (TH1D*)file->Get("th2_0");
	TH1D* h2 = (TH1D*)file->Get("th2_1");
	TH1D* h3 = (TH1D*)file->Get("th2_2");

/*	
	ofstream f1("./Uncertainty_2.txt");
 	TFile* file = new TFile("./output.root");
	TH1D* h1 = (TH1D*)file->Get("mjj_new");
	TH1D* h2 = (TH1D*)file->Get("mjj_JEC_up");
	TH1D* h3 = (TH1D*)file->Get("mjj_JEC_down");
*/
        const int num = h1->GetNbinsX();
	Double_t bincontent_new[num],bincontent_up[num],bincontent_down[num];
	Double_t uncer[num];
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
//			 cout<<" "<<fixed<<setprecision(1)<<uncer[i]*100<<"%,";
			 cout<<" "<<fixed<<setprecision(2)<<uncer[i]+1<<",";
			 f1<<uncer[i]<<endl;
		 }
      for(Int_t i=0;i<h1->GetNbinsX();i++){
	      cout<<" "<<fixed<<setprecision(2)<<uncer[i]+1<<",";
      }
      double uncer_sum;
      double binnew=h1->GetSum(),binup=h2->GetSum(),bindown=h3->GetSum();
      if( fabs(binup-binnew) > fabs(binnew-bindown) )
	      uncer_sum=fabs(binup-binnew)/binnew;
      else
              uncer_sum=fabs(binnew-bindown)/binnew;

      cout<<fixed<<setprecision(2)<<uncer_sum+1<<" "<<endl;
}
int uncer_jec(){
	get_jec("ZA_v3");
//	get_jec("ZA_tot");
	get_jec("ZA-EWK");
return 0;
}
