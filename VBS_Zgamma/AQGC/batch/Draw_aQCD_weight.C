double get_max(TString tag,int index);
void run(TString tag,int index){
	TFile*file=new TFile("./rootfiles/optimal_ZA_aQGC"+tag+".root");
	TTree*tree=(TTree*)file->Get("outtree");
	TString name;
	if(index==1) name="fM0";
        if(index==2) name="fM1";
        if(index==3) name="fM2";
        if(index==4) name="fM3";
        if(index==5) name="fM4";
        if(index==6) name="fM5";
        if(index==7) name="fM6";
        if(index==8) name="fM7";
        if(index==9) name="fT0";
        if(index==10) name="fT1";
        if(index==11) name="fT2";
        if(index==12) name="fT5";
        if(index==13) name="fT6";
        if(index==14) name="fT7";
        if(index==15) name="fT8";
        if(index==16) name="fT9";
        TH1D*h1[16];//every operator has 16 weights
        TString histname;
        double max=get_max(tag,index);
        int binnumber=(max+1)/1;
	cout<<binnumber<<endl;
	cout<<name<<" "<<index<<" "<<max<<endl;
        for(int i=0;i<16;i++){
                histname=name+Form("_%i",i+1);
		h1[i]=new TH1D(histname,name+" "+tag,binnumber,-0.5,max+1);
	}
	double pweight[703];
	tree->SetBranchAddress("pweight",pweight);
	for(int i=0;i<tree->GetEntries();i++){
            tree->GetEntry(i);
	    for(int k=0;k<16;k++){
		    int iii;
		    if(tag.Contains("16")) iii= 447+(index-1)*16;
		    else iii = 1+(index-1)*16;
		    iii=iii+k;
		    if(i==0)cout<<iii<<endl;
                    if(pweight[iii]>max+1) cout<<tag<<" "<<name<<" pweight["<<iii<<"]="<<pweight[iii]<<endl;
                    if(pweight[iii]<0) cout<<tag<<" "<<name<<" pweight["<<iii<<"]="<<pweight[iii]<<endl;
		    h1[k]->Fill(pweight[iii]);
	    } 
	}
	gStyle->SetOptStat(0);
        TLegend*l1=new TLegend(0.6,0.6,0.9,0.9);
	TCanvas*c1=new TCanvas("c1","",900,600);
        h1[0]->GetXaxis()->SetTitle(name+" weight");
	h1[0]->Draw("P");
        h1[0]->SetMarkerStyle(5);
	h1[0]->SetLineColor(2);
	h1[0]->SetMarkerColor(1);
	for(int i=1;i<16;i++){
		h1[i]->SetMarkerStyle(5);
		h1[i]->Draw("P SAME");
		h1[i]->SetLineColor(2+i);
		if(i<15)h1[i]->SetMarkerColor(2+i);
		else if(i==15) h1[i]->SetMarkerColor(2);
	}
        l1->AddEntry(h1[0],"aQGC weights of opertator "+name);
	l1->Draw();
	c1->SaveAs(name+"_weight"+tag+".pdf");

}
int Draw_aQCD_weight(){
	for(int i=1;i<=16;i++){
		run("16",i);
		run("17",i);
		run("18",i);
	}
	return 0;
}
double get_max(TString tag,int index){
	TFile*file=new TFile("./rootfiles/optimal_ZA_aQGC"+tag+".root");
	TTree*tree=(TTree*)file->Get("outtree");
	TString name;
	if(index==1) name="fM0";
        if(index==2) name="fM1";
        if(index==3) name="fM2";
        if(index==4) name="fM3";
        if(index==5) name="fM4";
        if(index==6) name="fM5";
        if(index==7) name="fM6";
        if(index==8) name="fM7";
        if(index==9) name="fT0";
        if(index==10) name="fT1";
        if(index==11) name="fT2";
        if(index==12) name="fT5";
        if(index==13) name="fT6";
        if(index==14) name="fT7";
        if(index==15) name="fT8";
        if(index==16) name="fT9";
        TH1D*h1[16];//every operator has 16 weights
        TString histname;
        for(int i=0;i<16;i++){
                histname=name+Form("_%i",i+1);
		h1[i]=new TH1D(histname,name,100,-0.5,100);
	}
	double pweight[703];
	tree->SetBranchAddress("pweight",pweight);
        vector<double> aQGC_weight;
	vector<double>::iterator biggest;
	double max=0;
	for(int i=0;i<tree->GetEntries();i++){
            tree->GetEntry(i);
	    for(int k=0;k<16;k++){
		    int iii;
		    if(tag.Contains("16")) iii= 447+(index-1)*16;
		    else iii = 1+(index-1)*16;
		    iii=iii+k;
                    aQGC_weight.push_back(pweight[iii]);
	    } 
	    biggest=max_element(begin(aQGC_weight),end(aQGC_weight));
	    if(*biggest>max) max=*biggest;
	    aQGC_weight.clear();
	}
	return max;
}
