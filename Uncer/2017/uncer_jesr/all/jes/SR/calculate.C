void get_jec(TString name){
	ofstream f1("./2017jes-uncertainty-barrel.txt");
	TFile* file1 = new TFile("./aa_"+name+".root");
	TH1D* h1 = (TH1D*)file1->Get("hist_1");
	TH1D* h2 = (TH1D*)file1->Get("hist_2");
	TH1D* h3 = (TH1D*)file1->Get("hist_3");
        const int num=h1->GetNbinsX();
	Double_t bincontent_new[num],bincontent_up[num],bincontent_down[num];
	Double_t uncer[num],sum_new=0,sum_down=0,sum_up=0;
	for(int i=0;i<num;i++){
		bincontent_new[i]=0;
		bincontent_up[i]=0;
		bincontent_down[i]=0;
                uncer[i]=0;
	}
        for(Int_t i=0;i<h1->GetNbinsX();i++){
		bincontent_new[i] = h1->GetBinContent(i+1);
		bincontent_up[i] = h2->GetBinContent(i+1);
		bincontent_down[i] = h3->GetBinContent(i+1);
		sum_new=sum_new+bincontent_new[i];
		sum_up=sum_up+bincontent_up[i];
		sum_down=sum_down+bincontent_down[i];
	}
	cout<<name<<" uncertaity: ";
		 for(Int_t i=0;i<h1->GetNbinsX();i++){
                         double max;
                         if(fabs(sum_up-sum_new)>fabs(sum_new - sum_down) )
				 max = fabs(sum_up-sum_new);
                         else    max = fabs(sum_new - sum_down); 
                         uncer[i] = max/sum_new;
//			 cout<<"new "<<bincontent_new[i]<<"; up "<<bincontent_up[i]<<"; down "<<bincontent_down[i]<<endl;
//			 cout<<"uncertainty "<<uncer[i]<<endl;
			 cout<<fixed<<setprecision(2)<<1+uncer[i]<<",";
			 f1<<uncer[i]<<endl;
		 }
      cout<<endl;
}
void get_jec(){
	ofstream f1("./2016jes-uncertainty-barrel.txt");
	TFile* file1 = new TFile("./aa_ST.root");
	TFile* file3 = new TFile("./aa_VV.root");
	TH1D* h1 = (TH1D*)file1->Get("hist_1");
	TH1D* h2 = (TH1D*)file1->Get("hist_2");
	TH1D* h3 = (TH1D*)file1->Get("hist_3");
	TH1D* h111 = (TH1D*)file3->Get("hist_1");
	TH1D* h222 = (TH1D*)file3->Get("hist_2");
	TH1D* h333 = (TH1D*)file3->Get("hist_3");
        h1->Add(h111,1); 
        h2->Add(h222,1); 
        h3->Add(h333,1); 
        const int num=h1->GetNbinsX();
	Double_t bincontent_new[num],bincontent_up[num],bincontent_down[num];
	Double_t uncer[num],sum_new=0,sum_down=0,sum_up=0;
        for(int i=0;i<num;i++){
                bincontent_new[i]=0;
                bincontent_up[i]=0;
                bincontent_down[i]=0;
                uncer[i]=0;
        }
        for(Int_t i=0;i<h1->GetNbinsX();i++){
		bincontent_new[i] = h1->GetBinContent(i+1);
		bincontent_up[i] = h2->GetBinContent(i+1);
		bincontent_down[i] = h3->GetBinContent(i+1);
		sum_new=sum_new+bincontent_new[i];
		sum_up=sum_up+bincontent_up[i];
		sum_down=sum_down+bincontent_down[i];
	}
		 for(Int_t i=0;i<h1->GetNbinsX();i++){
                         double max;
                         if(fabs(sum_up-sum_new)>fabs(sum_new - sum_down) )
				 max = fabs(sum_up-sum_new);
                         else    max = fabs(sum_new - sum_down); 
                         uncer[i] = max/sum_new;
//			 cout<<"new "<<bincontent_new[i]<<"; up "<<bincontent_up[i]<<"; down "<<bincontent_down[i]<<endl;
//			 cout<<"uncertainty "<<uncer[i]<<endl;
			 cout<<" "<<fixed<<setprecision(2)<<1+uncer[i]<<",";
			 f1<<uncer[i]<<endl;
		 }
      cout<<endl;
}
int calculate(){
	get_jec("ST");
	get_jec("TTA");
	get_jec("VV");
	get_jec();
return 0;
}
