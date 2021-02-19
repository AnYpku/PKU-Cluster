void fX0_parameterization_el(int index,vector<double>ZGbin,TString channel){

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
	TString dir6;
	TString dir7;
	TString dir8;
	TString ch;
	if(channel.Contains("mu")) ch="muon";
	else ch="ele";
	dir6="/home/pku/anying/cms/PKU-Cluster/AQGC/batch/fit/hist/hist_"+ch+"_"; 
	dir7="/home/pku/anying/cms/PKU-Cluster/AQGC/batch/fit/hist/hist_"+ch+"_"; 
	dir8="/home/pku/anying/cms/PKU-Cluster/AQGC/batch/fit/hist/hist_"+ch+"_"; 
	TFile*f6=new TFile(dir6+name+"_16.root");
	TFile*f7=new TFile(dir7+name+"_17.root");
	TFile*f8=new TFile(dir8+name+"_18.root");
	std::ofstream ParamSetf ;
	//      ParamSetf.open("paramsets_fT0_mu.txt");
	if(index==1) {ParamSetf.open("./txt/paramsets_fM0_"+channel+".txt"); }
	if(index==2) {ParamSetf.open("./txt/paramsets_fM1_"+channel+".txt"); }
	if(index==3) {ParamSetf.open("./txt/paramsets_fM2_"+channel+".txt"); }
	if(index==4) {ParamSetf.open("./txt/paramsets_fM3_"+channel+".txt"); }
	if(index==5) {ParamSetf.open("./txt/paramsets_fM4_"+channel+".txt"); }
	if(index==6) {ParamSetf.open("./txt/paramsets_fM5_"+channel+".txt"); }
	if(index==7) {ParamSetf.open("./txt/paramsets_fM6_"+channel+".txt"); }
	if(index==8) {ParamSetf.open("./txt/paramsets_fM7_"+channel+".txt"); }
	if(index==9) {ParamSetf.open("./txt/paramsets_fT0_"+channel+".txt"); }
	if(index==10){ParamSetf.open("./txt/paramsets_fT1_"+channel+".txt");}
	if(index==11){ParamSetf.open("./txt/paramsets_fT2_"+channel+".txt");}
	if(index==12){ParamSetf.open("./txt/paramsets_fT5_"+channel+".txt");}
	if(index==13){ParamSetf.open("./txt/paramsets_fT6_"+channel+".txt");}
	if(index==14){ParamSetf.open("./txt/paramsets_fT7_"+channel+".txt");}
	if(index==15){ParamSetf.open("./txt/paramsets_fT8_"+channel+".txt");}
	if(index==16){ParamSetf.open("./txt/paramsets_fT9_"+channel+".txt");}


	const int num=ZGbin.size()-1;
	TFile* fout = new TFile("./root/signal_proc_"+channel+"__"+name+".root", "RECREATE");
	TGraph*g6[num];TGraph*g7[num];TGraph*g8[num];
	for(int i=0;i<num;i++){
		g6[i]=(TGraph*)f6->Get(Form("bin%i",i));
		g7[i]=(TGraph*)f7->Get(Form("bin%i",i));
		g8[i]=(TGraph*)f8->Get(Form("bin%i",i));
		double rf6[17]={0};double xf6[17];
		double rf7[17]={0};double xf7[17];
		double rf8[17]={0};double xf8[17];
		double rf[17]={0}; double xf[17];
		for(int j=0;j<g6[i]->GetN();j++){
			g6[i]->GetPoint(j,xf6[j],rf6[j]);
			g7[i]->GetPoint(j,xf7[j],rf7[j]);
			g8[i]->GetPoint(j,xf8[j],rf8[j]);
			if( (xf6[j]-xf7[j])>1 || (xf6[j]-xf8[j])>1  || (xf8[j]-xf7[j])>1 ){
				cout<<"bin "<<i<<endl;
				cout<<"check the TGraph X-axis binning"<<endl;
				break;
			}
			rf[j]=rf6[j]+rf7[j]+rf8[j];xf[j]=xf6[j];
			cout<<j<<" 16: "<<rf6[j]<<"; 17: "<<rf7[j]<<"; 18: "<<rf8[j]<<endl;
		}
		double rsm=rf[8];
		for(int k=0;k<g6[i]->GetN();k++){
			rf[k]=rf[k]/rsm;
		}
		TGraph *gr = new TGraph(17,xf,rf);
		double low;
		double high;
		if(index==1) {low=-150;high=150;};
		if(index==2) {low=-400;high=400;};
		if(index==3) {low=-100;high=100;};
		if(index==4) {low=-200;high=200;};
		if(index==5) {low=-200;high=200;};
		if(index==6) {low=-200;high=200;};
		if(index==7) {low=-250;high=250;};
		if(index==8) {low=-200;high=200;};
		if(index==9) {low=-20;high=20;};
		if(index==10){low=-20;high=20;};
		if(index==11){low=-40;high=40;};
		if(index==12){low=-40;high=40;};
		if(index==13){low=-40;high=40;};
		if(index==14){low=-40;high=40;};
		if(index==15){low=-20;high=20;};
		if(index==16){low=-20;high=20;};
		TString tf1_name = TString("signal_proc_")+name+Form("_bin%u",i+1);
		TF1 *fitFunc = new TF1(tf1_name,"[0]*(x**2) + [1]*x + 1",low,high) ;
		cout<<"OK"<<endl;
		fitFunc->SetParLimits(0,0,1000);
		if(index==16&&i==0) fitFunc->SetParLimits(0,-1,1) ;
		if(index==16&&i==0) fitFunc->SetParLimits(1,-1,1) ;
		if(index==15&&i==0) fitFunc->SetParLimits(0,0,1) ;
		if(index==15&&i==0) fitFunc->SetParLimits(1,-1,1) ;
		cout<<"OK"<<endl;
		fitFunc->SetLineColor(kBlue) ;
		cout <<"x1"<<endl;
		TFitResultPtr r = gr->Fit(tf1_name,"ESR") ;  //C:Do not calc chi2 M:mirror R:range
		Double_t chi2   = r->Chi2() ;
		Double_t par0   = fitFunc->GetParameter(0);
		Double_t par1   = fitFunc->GetParameter(1);
		Double_t err0   = fitFunc->GetParError(0) ;
		Double_t err1   = fitFunc->GetParError(1) ;
		r->Print("V") ;
		//r->Write() ;
		fout->cd();
		fitFunc->Write();
		cout <<"x2"<<endl;
		TCanvas *c1= new TCanvas("c1","fitFunc",500,500) ;
		c1->SetGridx(1) ;
		c1->SetGridy(1) ;
		cout <<"x3"<<endl;

		gr->SetTitle(TString(" Fitted line of AQGC/SM in ZGmass : ")+Form("(%.0f,%.0f)",ZGbin[i],ZGbin[i+1])) ;
		cout <<"x4"<<endl;
		gr->GetYaxis()->SetTitleOffset(1.4) ;
		char buffer2[256];
		if(index==1) sprintf(buffer2, "fM0/#Lambda^{4} (#times 10^{-12} GeV)");
		if(index==2) sprintf(buffer2, "fM1/#Lambda^{4} (#times 10^{-12} GeV)");
		if(index==3) sprintf(buffer2, "fM2/#Lambda^{4} (#times 10^{-12} GeV)");
		if(index==4) sprintf(buffer2, "fM3/#Lambda^{4} (#times 10^{-12} GeV)");
		if(index==5) sprintf(buffer2, "fM4/#Lambda^{4} (#times 10^{-12} GeV)");
		if(index==6) sprintf(buffer2, "fM5/#Lambda^{4} (#times 10^{-12} GeV)");
		if(index==7) sprintf(buffer2, "fM6/#Lambda^{4} (#times 10^{-12} GeV)");
		if(index==8) sprintf(buffer2, "fM7/#Lambda^{4} (#times 10^{-12} GeV)");
		if(index==9) sprintf(buffer2, "fT0/#Lambda^{4} (#times 10^{-12} GeV)");
		if(index==10)sprintf(buffer2,"fT1/#Lambda^{4} (#times 10^{-12} GeV)");
		if(index==11)sprintf(buffer2,"fT2/#Lambda^{4} (#times 10^{-12} GeV)");
		if(index==12)sprintf(buffer2,"fT5/#Lambda^{4} (#times 10^{-12} GeV)");
		if(index==13)sprintf(buffer2,"fT6/#Lambda^{4} (#times 10^{-12} GeV)");
		if(index==14)sprintf(buffer2,"fT7/#Lambda^{4} (#times 10^{-12} GeV)");
		if(index==15)sprintf(buffer2,"fT8/#Lambda^{4} (#times 10^{-12} GeV)");
		if(index==16)sprintf(buffer2,"fT9/#Lambda^{4} (#times 10^{-12} GeV)");

		gr->GetXaxis()->SetTitle(buffer2) ;
		gr->GetYaxis()->SetTitle("Ratio") ;
		gr->SetMarkerStyle(4) ;
		cout <<"x5"<<endl;
		gr->SetLineWidth(2) ;
		gr->SetLineColor(kBlue) ;
		gr->Draw("AP") ;
		cout <<"x6"<<endl;
		TLegend *leg = new TLegend(0.3,0.58,0.70,0.88) ;
		leg->SetFillColor(10) ;
		leg->AddEntry(gr,"Fitted line: r =  p0 x^{2} + p1 x + 1","L") ;
		cout <<"x7"<<endl;
		leg->AddEntry(gr,Form("p0 = %f ",par0),"") ;
		leg->AddEntry(gr,Form("p1 = %f ",par1),"") ;
		cout <<"x8"<<endl;
		//leg->AddEntry(gr,TString("SM yield: ")+Form("%f",signal_SM->Integral()),"") ;
		leg->Draw("SAME") ;
		cout <<"x9"<<endl;
		if(index==1) c1->SaveAs(TString("figs/fit_fM0_")+channel+Form("_ZGbin_%u",i)+TString(".pdf")) ;
		if(index==2) c1->SaveAs(TString("figs/fit_fM1_")+channel+Form("_ZGbin_%u",i)+TString(".pdf")) ;
		if(index==3) c1->SaveAs(TString("figs/fit_fM2_")+channel+Form("_ZGbin_%u",i)+TString(".pdf")) ;
		if(index==4) c1->SaveAs(TString("figs/fit_fM3_")+channel+Form("_ZGbin_%u",i)+TString(".pdf")) ;
		if(index==5) c1->SaveAs(TString("figs/fit_fM4_")+channel+Form("_ZGbin_%u",i)+TString(".pdf")) ;
		if(index==6) c1->SaveAs(TString("figs/fit_fM5_")+channel+Form("_ZGbin_%u",i)+TString(".pdf")) ;
		if(index==7) c1->SaveAs(TString("figs/fit_fM6_")+channel+Form("_ZGbin_%u",i)+TString(".pdf")) ;
		if(index==8) c1->SaveAs(TString("figs/fit_fM7_")+channel+Form("_ZGbin_%u",i)+TString(".pdf")) ;
		if(index==9) c1->SaveAs(TString("figs/fit_fT0_")+channel+Form("_ZGbin_%u",i)+TString(".pdf")) ;
		if(index==10)c1->SaveAs(TString("figs/fit_fT1_")+channel+Form("_ZGbin_%u",i)+TString(".pdf")) ;
		if(index==11)c1->SaveAs(TString("figs/fit_fT2_")+channel+Form("_ZGbin_%u",i)+TString(".pdf")) ;
		if(index==12)c1->SaveAs(TString("figs/fit_fT5_")+channel+Form("_ZGbin_%u",i)+TString(".pdf")) ;
		if(index==13)c1->SaveAs(TString("figs/fit_fT6_")+channel+Form("_ZGbin_%u",i)+TString(".pdf")) ;
		if(index==14)c1->SaveAs(TString("figs/fit_fT7_")+channel+Form("_ZGbin_%u",i)+TString(".pdf")) ;
		if(index==15)c1->SaveAs(TString("figs/fit_fT8_")+channel+Form("_ZGbin_%u",i)+TString(".pdf")) ;
		if(index==16)c1->SaveAs(TString("figs/fit_fT9_")+channel+Form("_ZGbin_%u",i)+TString(".pdf")) ;
		//              c1->SaveAs(TString("fit_fT0")+Form("_ZPTbin_%u",i)+TString(".pdf")) ;

		ParamSetf << par0 << " " << par1 << " " << endl;
		cout <<"x10 "<<i<<endl;
	}
	ParamSetf.close();
	f6->Close();f7->Close();f8->Close();
	fout->Close();
}
void f_parameterization(){
	vector<TString>channel={"ele","mu"};
	vector<double>ZGbin={150,400,600,800, 1000,1200, 2e4};
	for(int i=1;i<17;i++){
		for(int j=0;j<channel.size();j++){
			fX0_parameterization_el(i,ZGbin,channel[j]);
		}
	}

}
