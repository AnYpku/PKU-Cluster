void run_full(TString var,int num);
void run(TString var,TString tag,int num,TString sample){
	TFile*file=new TFile("./unfold_"+var+"_"+sample+"_pdf"+tag+".root");
        TH1D*h1[num];
        for (int i=0;i<num;i++){
		h1[i]=(TH1D*)file->Get(var+Form("_%i",i));
	}
	double error=0;
	double diff=0,sum=0;
	double center=h1[0]->GetSum();
	for(int i=0;i<num;i++){
		diff=h1[i]->GetSum()-center;
		sum+=pow(diff,2);
	}
	if(h1[0]->GetSum()>0)
		error=sqrt(sum/(num-1))/h1[0]->GetSum();
	else    error=0;
	cout<<"pdf unc. "<<error<<" in "<<sample<<endl;
}
int cal_unc_overall(){
	run("genMjj","16",103,"qcd");
	run_full("genMjj",103);
	return 0;
}
void run_full(TString var,int num){
	TFile*f1=new TFile("./unfold_"+var+"_ewk_pdf16.root");
	TFile*f2=new TFile("./unfold_"+var+"_ewk_pdf17.root");
	TFile*f3=new TFile("./unfold_"+var+"_ewk_pdf18.root");
        TH1D*h1[num];TH1D*h12[num];TH1D*h13[num];
        for (int i=0;i<num;i++){
		h1[i] =(TH1D*)f1->Get(var+Form("_%i",i));
		h12[i]=(TH1D*)f2->Get(var+Form("_%i",i));
		h13[i]=(TH1D*)f3->Get(var+Form("_%i",i));
                h1[i]->Add(h12[i],1);h1[i]->Add(h13[i],1);
	}
	double error=0;
	double diff=0,sum=0;
	double center=h1[0]->GetSum();
	for(int i=0;i<num;i++){
		diff=h1[i]->GetSum()-center;
		sum+=pow(diff,2);
	}
	if(h1[0]->GetSum()>0)
		error=sqrt(sum/(num-1))/h1[0]->GetSum();
	else    error=0;
	cout<<"overall pdf unc. "<<error<<" in EW"<<endl;
}


