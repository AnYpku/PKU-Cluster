void run_full(TString var,int num,TString sample);
void run(TString var,TString tag,TString sample,int num){
	TFile*file=new TFile("./"+var+"_unfold_"+sample+"_scale"+tag+".root");
        TH1D*h1[num];
        for (int i=0;i<num;i++){
		h1[i]=(TH1D*)file->Get(var+Form("_%i",i));
		if(i!=0&&tag.Contains("16")&&sample.Contains("qcd")) h1[i]->Scale(2);
	}
        vector<double> vec_content;
        vector<Double_t>:: iterator biggest;
        vector<Double_t>:: iterator smallest;
	for(int i=0;i<num;i++){
		if(sample.Contains("qcd")){
			if(!(i==5||i==7))	
				vec_content.push_back(h1[i]->GetSum());
		}
		else vec_content.push_back(h1[i]->GetSum());
	}
	biggest = max_element(begin(vec_content),end(vec_content));
	smallest= min_element(begin(vec_content),end(vec_content));
	cout<<num<<" "<<sample<<" "<<h1[0]->GetSum()<<" "<<*biggest<<" "<<*smallest<<endl;
	double error;
	if(h1[0]->GetSum()>0)
		error=(*biggest - *smallest)/2/h1[0]->GetSum();
	else    error=0;
	vec_content.clear();
	cout<<tag<<" scale unc. "<<error<<" in "<<sample<<endl;
}
int cal_unc_overall(){
	run_full("genMjj",3,"ewk");
//	run("genMjj","16","qcd",9);
//	run("genMjj","17","qcd",9);
//	run("genMjj","18","qcd",9);
	run_full("genMjj",9,"qcd");
return 0;
}
void run_full(TString var,int num,TString sample){
	TFile*f1=new TFile("./"+var+"_unfold_"+sample+"_scale16.root");
	TFile*f2=new TFile("./"+var+"_unfold_"+sample+"_scale17.root");
	TFile*f3=new TFile("./"+var+"_unfold_"+sample+"_scale18.root");
        TH1D*h1[num];TH1D*h12[num];TH1D*h13[num];
        for (int i=0;i<num;i++){
		h1[i] =(TH1D*)f1->Get(var+Form("_%i",i));
		h12[i]=(TH1D*)f2->Get(var+Form("_%i",i));
		h13[i]=(TH1D*)f3->Get(var+Form("_%i",i));
                if(i!=0&&sample.Contains("qcd")) h1[i]->Scale(2);
		h1[i]->Add(h12[i],1);h1[i]->Add(h13[i],1);
	}
        vector<double> vec_content;
        vector<Double_t>:: iterator biggest;
        vector<Double_t>:: iterator smallest;
	for(int i=0;i<num;i++){
		if(sample.Contains("qcd")){     
			if(!(i==5||i==7))       
				vec_content.push_back(h1[i]->GetSum());
		}
		else vec_content.push_back(h1[i]->GetSum());
	}
	biggest = max_element(begin(vec_content),end(vec_content));
	smallest= min_element(begin(vec_content),end(vec_content));
//	cout<<num<<" "<<sample<<" "<<h1[0]->GetSum()<<" "<<*biggest<<" "<<*smallest<<endl;
	double error;
	if(h1[0]->GetSum()>0)
		error=(*biggest - *smallest)/2/h1[0]->GetSum();
	else    error=0;
	cout<<"the overall scale unc. "<<error<<" in "<<sample<<endl;
	vec_content.clear();
}
