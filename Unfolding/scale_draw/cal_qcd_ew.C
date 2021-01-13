void run_full(TString var,int num);
int cal_qcd_ew(){
	run_full("genMjj",9);
return 0;
}
void run_full(TString var,int num){
	TFile*f1=new TFile("./"+var+"_unfold_qcd_scale16.root");
	TFile*f2=new TFile("./"+var+"_unfold_qcd_scale17.root");
	TFile*f3=new TFile("./"+var+"_unfold_qcd_scale18.root");
	TFile*ff1=new TFile("./"+var+"_unfold_ewk_scale16.root");
	TFile*ff2=new TFile("./"+var+"_unfold_ewk_scale17.root");
	TFile*ff3=new TFile("./"+var+"_unfold_ewk_scale18.root");
        TH1D*h1[num];TH1D*h12[num];TH1D*h13[num];
        TH1D*hh1[num];TH1D*hh12[num];TH1D*hh13[num];
	for(int i=0;i<3;i++){
		hh1[i] =(TH1D*)ff1->Get(var+Form("_%i",i));
		hh12[i]=(TH1D*)ff2->Get(var+Form("_%i",i));
		hh13[i]=(TH1D*)ff3->Get(var+Form("_%i",i));
		hh1[i]->Add(hh12[i],1);hh1[i]->Add(hh13[i],1);
	}
	for (int i=0;i<num;i++){
		h1[i] =(TH1D*)f1->Get(var+Form("_%i",i));
		h12[i]=(TH1D*)f2->Get(var+Form("_%i",i));
		h13[i]=(TH1D*)f3->Get(var+Form("_%i",i));
		if(i!=0) h1[i]->Scale(2);
		h1[i]->Add(h12[i],1);h1[i]->Add(h13[i],1);

		if(i==0||i==3||i==6) h1[i]->Add(hh1[0]);
		if(i==1||i==4) h1[i]->Add(hh1[1]);
		if(i==2||i==8) h1[i]->Add(hh1[2]);
	}
	vector<double> vec_content;
	vector<Double_t>:: iterator biggest;
	vector<Double_t>:: iterator smallest;
	for(int i=0;i<num;i++){
		if(!(i==5||i==7))       
			vec_content.push_back(h1[i]->GetSum());
	}
	biggest = max_element(begin(vec_content),end(vec_content));
	smallest= min_element(begin(vec_content),end(vec_content));
	//	cout<<num<<" "<<sample<<" "<<h1[0]->GetSum()<<" "<<*biggest<<" "<<*smallest<<endl;
	double error;
	if(h1[0]->GetSum()>0)
		error=(*biggest - *smallest)/2/h1[0]->GetSum();
	else    error=0;
	cout<<"the overall scale unc. "<<error<<" in "<<endl;
	vec_content.clear();
}
