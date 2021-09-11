#include "TAxis.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TNtupleD.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include "CMS_lumi.C"
//#include "tdrstyle.C"
////CMS Preliminary label and lumi -- upper left corner
TH1D* merge(TString sample,TString channel){
	TString dir="/home/pku/anying/cms/PKU-Cluster/AQGC/batch/hist_root/";
	TFile*f1=new TFile(dir+"hist_"+sample+"16"+channel+".root");
	TFile*f2=new TFile(dir+"hist_"+sample+"17"+channel+".root");
	TFile*f3=new TFile(dir+"hist_"+sample+"18"+channel+".root");
	TH1D*h1=(TH1D*)f1->Get("hist");
	TH1D*h2=(TH1D*)f2->Get("hist");
	TH1D*h3=(TH1D*)f3->Get("hist");
	TH1D*hist=(TH1D*)h1->Clone();
	hist->Add(h2,1);
	hist->Add(h3,1);
	int n=hist->GetNbinsX();
	hist->SetBinContent(n,hist->GetBinContent(n)+hist->GetBinContent(n+1));
	hist->SetBinError(n,sqrt(pow(hist->GetBinError(n),2)+pow(hist->GetBinError(n+1),2)));
        hist->SetBinContent(n+1,0);
	vector<double> ZGbin={150,400,600,800,1000,1200,2e3};
//      TH1D*hist_clone=new TH1D(sample,"",ZGbin.size()-1,&ZGbin[0]);
        TH1D*hist_clone=new TH1D(sample,"",ZGbin.size()-1,0,ZGbin.size()-1);
        const int num=ZGbin.size()-1;
        const char *name[num];
	for(int i=1;i<=n;i++){
           if(i==1)name[i-1]=Form("%0.2f-%0.1f",ZGbin[i-1]/1000,ZGbin[i]/1000);
           if(i!=1&&i<n)name[i-1]=Form("%0.1f-%0.1f",ZGbin[i-1]/1000,ZGbin[i]/1000);
           if(i==n)name[i-1]=Form("%0.1f-#infty",ZGbin[i-1]/1000);
           cout<<name[i-1]<<endl;
           hist_clone->SetBinContent(i,hist->GetBinContent(i));
	   hist_clone->SetBinError(i,hist->GetBinError(i));
           hist_clone->GetXaxis()->SetBinLabel(i,name[i-1]);
	}
	return hist_clone;
}
TH1D* get_hist(TString sample,TString channel,TString tag){
	TString dir="/home/pku/anying/cms/PKU-Cluster/AQGC/batch/hist_root/";
	TFile*f1=new TFile(dir+"hist_"+sample+tag+channel+".root");
	TH1D*h1=(TH1D*)f1->Get("hist");
	TH1D*hist=(TH1D*)h1->Clone();
	int n=hist->GetNbinsX();
	hist->SetBinContent(n,hist->GetBinContent(n)+hist->GetBinContent(n+1));
	hist->SetBinError(n,sqrt(pow(hist->GetBinError(n),2)+pow(hist->GetBinError(n+1),2)));
        hist->SetBinContent(n+1,0);
	vector<double> ZGbin={150,400,600,800,1000,1200,2e3};
//      TH1D*hist_clone=new TH1D(sample,"",ZGbin.size()-1,&ZGbin[0]);
        TH1D*hist_clone=new TH1D(sample,"",ZGbin.size()-1,0,ZGbin.size()-1);
        const int num=ZGbin.size()-1;
        const char *name[num];
	for(int i=1;i<=n;i++){
           if(i==1)name[i-1]=Form("%0.2f-%0.1f",ZGbin[i-1]/1000,ZGbin[i]/1000);
           if(i!=1&&i<n)name[i-1]=Form("%0.1f-%0.1f",ZGbin[i-1]/1000,ZGbin[i]/1000);
           if(i==n)name[i-1]=Form("%0.1f-#infty",ZGbin[i-1]/1000);
           cout<<name[i-1]<<endl;
           if(hist->GetBinContent(i)<0){
		   hist->SetBinContent(i,0);
		   hist->SetBinError(i,0);
	   }
           hist_clone->SetBinContent(i,hist->GetBinContent(i));
	   hist_clone->SetBinError(i,hist->GetBinError(i));
           hist_clone->GetXaxis()->SetBinLabel(i,name[i-1]);
	}
	cout<<tag<<" "<<sample<<" "<<hist_clone->GetBinContent(6)<<endl;
	return hist_clone;
}
void cmsLumi(bool channel) //0 for el
{
	TLatex latex;
	latex.SetNDC();
	latex.SetTextSize(0.06);
	// latex.SetTextFont(42);
	latex.SetLineWidth(2);
	//  latex.SetTextWidth(2);
	float lumiel=35.8;
	float lumimu=35.8;
	int beamcomenergytev=13;
	latex.SetTextAlign(31); // align right
	//latex.DrawLatex(0.95,0.96,Form("%d TeV",beamcomenergytev));
	latex.SetTextAlign(11); // align left
	latex.DrawLatex(0.21,0.84,"Preliminary");
	//latex.DrawLatex(0.17,0.96,channel? "Muon channel":"Electron channel");
	//latex.SetTextAlign(11); // align left
	latex.DrawLatex(0.16,0.88,"CMS");
	latex.SetTextSize(0.06);
	latex.DrawLatex(0.76,0.96,Form("137.1 fb^{-1} (%d TeV)", (beamcomenergytev)));
}



void aa(TString tag,TString a, double limit,int num){
	//setTDRStyle();
        TString dir="/home/pku/anying/cms/PKU-Cluster/AQGC/batch/fit/txt/";
        TString mu_file= dir+"paramsets_"+a+"_muon"+tag+".txt";
        TString ele_file=dir+"paramsets_"+a+"_ele"+tag+".txt";
	ifstream infile_mu;
	ifstream infile_ele;
	infile_mu.open(mu_file);
	infile_ele.open(ele_file);
	double aa, bb, cc, dd;
	int count=num;
	double mu_a2[num];
	double mu_a1[num];
	double ele_a2[num];
	double ele_a1[num];
	while (count)
	{
		infile_mu >>aa>>bb;
		infile_ele >>cc>>dd;
//		cout<<aa<<" "<<bb<<" "<<cc<<" "<<dd<<endl; 
		mu_a2[num-count]=aa;
		mu_a1[num-count]=bb;
		ele_a2[num-count]=cc;
		ele_a1[num-count]=dd;
		count--;
	}

	Double_t fT0 = limit;
	Double_t weight_mu[6]={1.};
	Double_t weight_ele[6]={1.};
	for(Int_t i=0;i<num;i++){
		weight_mu[i]=mu_a2[i]*fT0*fT0+mu_a1[i]*fT0+1;
		weight_ele[i]=ele_a2[i]*fT0*fT0+ele_a1[i]*fT0+1;
	}


        TH1D*h1=get_hist("Muon","mu",tag);
        TH1D*h2=get_hist("ZA-EWK","mu",tag);
        TH1D*h3=get_hist("plj","mu",tag);
        TH1D*h4=get_hist("others","mu",tag);
        TH1D*h5=get_hist("ZA","mu",tag);
	TH1D* h6= (TH1D*)h2->Clone();
	h1->Sumw2();
	h2->Sumw2();
	h3->Sumw2();
	h4->Sumw2();
	h5->Sumw2();
	h6->Sumw2();

	TH1D* h11=get_hist("Ele","ele",tag); 
	TH1D* h21=get_hist("ZA-EWK","ele",tag);
	TH1D* h31=get_hist("plj","ele",tag); 
	TH1D* h41=get_hist("others","ele",tag);
	TH1D* h51=get_hist("ZA","ele",tag);
	TH1D* h61=(TH1D*)h21->Clone();

	h11->Sumw2();
	h21->Sumw2();
	h31->Sumw2();
	h41->Sumw2();
	h51->Sumw2();
	h61->Sumw2();

	h1->Add(h11);//data
	h2->Add(h21);//ZA EWK
	h3->Add(h31);//plj
	h4->Add(h41);//other bkg
	h5->Add(h51);//QCD ZA
        cout<<"data yields "<<h1->GetSumOfWeights()<<endl;
	for(Int_t i=0;i<num;i++){
		h6->SetBinContent(i+1,weight_mu[i]*h6->GetBinContent(i+1));
		h61->SetBinContent(i+1,weight_ele[i]*h61->GetBinContent(i+1));
	}
	h6->Add(h61);//aQCD ZA
	h6->Add(h5);//QCD ZA
	h6->Add(h4);// other bkg
	h6->Add(h3);//plj

	h1->SetFillColor(kBlack);
	h1->SetMarkerStyle(20);
	h1->SetMarkerSize(1.3);

	h2->SetMarkerStyle(21);
	h2->SetMarkerColor(kRed-7);
	h2->SetFillColor(kRed-7);
	h2->SetLineColor(kRed-7);

	h3->SetFillColor(kYellow);
	h3->SetMarkerColor(kYellow);
	h3->SetLineColor(kYellow);

	h4->SetFillColor(kCyan);
	h4->SetMarkerColor(kCyan);
	h4->SetLineColor(kCyan);

	h5->SetFillColor(kBlue-7);
	h5->SetMarkerColor(kBlue-7);
	h5->SetLineColor(kBlue-7);

	h6->SetLineWidth(2);
	h6->SetLineColor(kRed);


	THStack * Mstack = new THStack("Mstack","");
	Mstack->Add(h4);
	Mstack->Add(h3);
	Mstack->Add(h2);
	Mstack->Add(h5);
        TH1D*hist=(TH1D*)h2->Clone();
        hist->Add(h3);
        hist->Add(h4);
        hist->Add(h5);
	cout<<"MC yields "<<hist->GetSum()<<endl;
	gStyle->SetOptStat(0);
	TCanvas *c01 = new TCanvas("c01","",800,600);
	c01->SetLogy();
	c01->SetTicky();
	TPad* fPad1 = new TPad("pad1", "pad1", 0.00, 0.00, 0.99, 0.99);
	fPad1->Draw();
	fPad1->cd();
	fPad1->SetLogy();
        fPad1->SetTicky();
	fPad1->SetGridx();
	fPad1->SetBottomMargin(0.2);
	//c01->SetLogx();


	Mstack->SetMaximum(float(4.0)*Mstack->GetMaximum());
	Mstack->SetMinimum(0.1);
	Mstack->Draw("bar HIST");
	//     Mstack->Draw("EP same");
	Mstack->GetXaxis()->SetTitle("m_{Z#gamma} [TeV] ");
	Mstack->GetYaxis()->SetTitle("Events / bin");
	Mstack->GetXaxis()->SetLabelSize(0.065);
	Mstack->GetXaxis()->SetLabelOffset(0.01);
	Mstack->GetXaxis()->SetTitleSize(0.06);
	Mstack->GetXaxis()->SetTitleOffset(1.2);
	Mstack->GetYaxis()->SetTitleSize(0.05);
	Mstack->GetYaxis()->SetTitleOffset(1.0);
	//Mstack->GetXaxis()->CenterTitle();
	//Mstack->GetYaxis()->CenterTitle();

	TH1D* htemp = (TH1D*)(Mstack->GetStack()->Last());
	htemp->SetBinErrorOption(TH1::kPoisson);
	Double_t x[num];
	Double_t y[num];
	Double_t xerror_l[num];
	Double_t xerror_r[num];
	Double_t yerror_u[num];
	Double_t yerror_d[num];
	for(int i=0;i<num;i++)
	{
		x[i]=htemp->GetBinCenter(i+1);
		y[i]=htemp->GetBinContent(i+1);
		xerror_l[i]=0.5*htemp->GetBinWidth(i+1);
		xerror_r[i]=0.5*htemp->GetBinWidth(i+1);
		yerror_u[i]=htemp->GetBinErrorUp(i+1);
		yerror_d[i]=htemp->GetBinErrorLow(i+1);
		if(htemp->GetBinContent(i+1)==0)
		{yerror_u[i]=0.;yerror_d[i]=0.;}
	}
	TGraphAsymmErrors* gr = new TGraphAsymmErrors(num, x, y, xerror_l,xerror_r, yerror_d, yerror_u);
	gr->SetFillColor(1);
	gr->SetFillStyle(3005);
	gr->Draw("SAME 2");

	h6->Draw("hist same");  // aQGC
        h1->SetLineColor(1);
        h1->SetMarkerStyle(20);
	h1->Draw(" PE same");  // 0 for Zero data

	const double alpha = 1 - 0.6827;
	TGraphAsymmErrors * g = new TGraphAsymmErrors(h1);
	g->SetMarkerSize(0.5);
	g->SetMarkerStyle (20);
	for (int i = 0; i < g->GetN(); ++i) {
		int N = g->GetY()[i];
		double L =  (N==0) ? 0  : (ROOT::Math::gamma_quantile(alpha/2,N,1.));
		double U =  ROOT::Math::gamma_quantile_c(alpha/2,N+1,1) ;
		g->SetPointEYlow(i, N-L);
		g->SetPointEYhigh(i, U-N);
	}
	//	g->Draw("P");  // no A, otherwise will be overlaid




	TLegend *l1 = new TLegend(0.4,0.7,0.6,0.88);
	TLegend *l2 = new TLegend(0.6,0.7,0.85,0.85);
	//l1->SetBorderSize(2);
	l1->SetTextSize(0.04);
	l1->SetFillColor(0);
	l1->SetLineColor(0);
	l1->SetLineWidth(0);
	l1->SetFillStyle(0);
	l2->SetTextSize(0.04);
	l2->SetLineWidth(0);
	l2->SetFillStyle(0);
	l2->SetFillColor(0);
	l2->SetLineColor(0);
	//        l1->SetFillStyle(4000);
	//        l2->SetFillStyle(4000);
	//	l1->AddEntry(h1,"data","EP");
	char buffer[256];
	if (a.Contains("fM0")) sprintf(buffer, "F_{M,0}=%0.2f TeV^{-4}",limit);
	if (a.Contains("fM1")) sprintf(buffer, "F_{M,1}=%0.2f TeV^{-4}",limit);
	if (a.Contains("fM2")) sprintf(buffer, "F_{M,2}=%0.2f TeV^{-4}",limit);
	if (a.Contains("fM3")) sprintf(buffer, "F_{M,3}=%0.2f TeV^{-4}",limit);
	if (a.Contains("fM4")) sprintf(buffer, "F_{M,4}=%0.2f TeV^{-4}",limit);
	if (a.Contains("fM5")) sprintf(buffer, "F_{M,5}=%0.2f TeV^{-4}",limit);
	if (a.Contains("fM6")) sprintf(buffer, "F_{M,6}=%0.2f TeV^{-4}",limit);
	if (a.Contains("fM7")) sprintf(buffer, "F_{M,7}=%0.2f TeV^{-4}",limit);
	if (a.Contains("fT0")) sprintf(buffer, "F_{T,0}=%0.2f TeV^{-4}",limit);
	if (a.Contains("fT1")) sprintf(buffer, "F_{T,1}=%0.2f TeV^{-4}",limit);
	if (a.Contains("fT2")) sprintf(buffer, "F_{T,2}=%0.2f TeV^{-4}",limit);
	if (a.Contains("fT5")) sprintf(buffer, "F_{T,5}=%0.2f TeV^{-4}",limit);
	if (a.Contains("fT6")) sprintf(buffer, "F_{T,6}=%0.2f TeV^{-4}",limit);
	if (a.Contains("fT7")) sprintf(buffer, "F_{T,7}=%0.2f TeV^{-4}",limit);
	if (a.Contains("fT8")) sprintf(buffer, "F_{T,8}=%0.2f TeV^{-4}",limit);
	if (a.Contains("fT9")) sprintf(buffer, "F_{T,9}=%0.2f TeV^{-4}",limit);
	l1->AddEntry(g,"Data","lp");
        l1->AddEntry(h2,"VBS Z#gamma","f");
        l1->AddEntry(h5,"QCD Z#gamma","f");
        l2->AddEntry(h3,"Nonprompt","f");
        l2->AddEntry(h4,"Other bkg.","f");
//	l1->AddEntry(h2,Form("VBS Z#gamma[%0.2f]",h2->GetBinContent(6)),"f");
//	l1->AddEntry(h5,Form("QCD Z#gamma[%0.2f]",h5->GetBinContent(6)),"f");
//	l2->AddEntry(h3,Form("Nonprompt  [%0.2f]",h3->GetBinContent(6)),"f");
//	l2->AddEntry(h4,Form("Other bkg. [%0.2f]",h4->GetBinContent(6)),"f");
	l2->AddEntry(h6,buffer,"l");
	l1->Draw("same");
	l2->Draw("same");
	fPad1->SetTicky();
	fPad1->SetTickx();
	string lumi;
        if(tag.Contains("16")) lumi="35.86";
        if(tag.Contains("17")) lumi="41.52";
        if(tag.Contains("18")) lumi="59.7";
	CMS_lumi(fPad1, 4, 0., lumi);	

	fPad1->Update();
	c01->SaveAs("ZG_"+a+"_"+tag+".pdf");

}

void plot_year(){
	vector<TString> tag={"16","17","18"};
        vector<double> limit16={20.079,46.211,8.352,17.411,16.344,28.557,40.158,73.856,0.739,1.030,2.002,0.819,1.758,3.081,0.541,1.065};
        vector<double> limit17={25.666,55.290,10.592,23.862,21.001,32.902,51.332,87.125,0.951,1.301,2.520,1.038,2.130,3.872,0.581,1.582};
        vector<double> limit18={16.587,34.571,6.460,11.398,12.998,21.573,33.174,56.570,0.586,0.809,1.566,0.650,1.374,2.475,0.509,0.859};
        vector<TString> op={"fM0","fM1","fM2","fM3","fM4","fM5","fM6","fM7","fT0","fT1","fT2","fT5","fT6","fT7","fT8","fT9"};
	for(int i=0;i<op.size();i++){
		aa("16",op[i],limit16[i],6);
		aa("17",op[i],limit17[i],6);
		aa("18",op[i],limit18[i],6);
	}
}
