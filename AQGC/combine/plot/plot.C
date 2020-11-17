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
void cmsLumi(bool channel) //0 for el
{
	TLatex latex;
	latex.SetNDC();
	latex.SetTextSize(0.04);
	// latex.SetTextFont(42);
	latex.SetLineWidth(2);
	//  latex.SetTextWidth(2);
	float lumiel=41.5;
	float lumimu=41.5;
	int beamcomenergytev=13;
	latex.SetTextAlign(31); // align right
	//latex.DrawLatex(0.95,0.96,Form("%d TeV",beamcomenergytev));
	latex.SetTextAlign(11); // align left
//	latex.DrawLatex(0.21,0.84,"Preliminary");
	//latex.DrawLatex(0.17,0.96,channel? "Muon channel":"Electron channel");
	//latex.SetTextAlign(11); // align left
	latex.DrawLatex(0.16,0.88,"CMS");
	latex.SetTextSize(0.04);
	latex.DrawLatex(0.76,0.96,Form("41.5 fb^{-1} (%d TeV)", (beamcomenergytev)));
}
TH1D*merge(TFile*f1,TFile*f2,TFile*f3,TString hname){
	TString fname=f2->GetName();
        TH1D*h1;TH1D*h2;TH1D*h3;
	if(hname.Contains("EWK")){
		h1=(TH1D*)f1->Get("ZA_EWK");
		h2=(TH1D*)f2->Get("ZA-EWK");
		h3=(TH1D*)f3->Get("ZA-EWK");
	}
	else{
		h1=(TH1D*)f1->Get(hname);
		h2=(TH1D*)f2->Get(hname);
		h3=(TH1D*)f3->Get(hname);
	}
//        h1->Scale(35.86/41.52);         
//        h3->Scale(58.7/41.52);         

        h1->Add(h2,1);
        h1->Add(h3,1);

	cout<<"merging "<<hname<<endl;
return h1;

}


void aa(string a, double limit){
//	setTDRStyle();
	string mu_file16="/home/pku/anying/cms/PKU-Cluster/AQGC/2016/muon/paramsets_"+a+"_mu.txt";
	string ele_file16="/home/pku/anying/cms/PKU-Cluster/AQGC/2016/muon/paramsets_"+a+"_el.txt";
	string mu_file17="/home/pku/anying/cms/PKU-Cluster/AQGC/2017/muon/paramsets_"+a+"_mu.txt";
	string ele_file17="/home/pku/anying/cms/PKU-Cluster/AQGC/2017/muon/paramsets_"+a+"_el.txt";
	string mu_file18="/home/pku/anying/cms/PKU-Cluster/AQGC/2018/muon/paramsets_"+a+"_mu.txt";
	string ele_file18="/home/pku/anying/cms/PKU-Cluster/AQGC/2018/muon/paramsets_"+a+"_el.txt";
	ifstream infile_mu16;
	ifstream infile_ele16;
	ifstream infile_mu17;
	ifstream infile_ele17;
	ifstream infile_mu18;
	ifstream infile_ele18;
        infile_mu16.open(mu_file16.c_str());
        infile_ele16.open(ele_file16.c_str());
        infile_mu17.open(mu_file17.c_str());
        infile_ele17.open(ele_file17.c_str());
        infile_mu18.open(mu_file18.c_str());
        infile_ele18.open(ele_file18.c_str());
	double aa[3], bb[3], cc[3], dd[3];
	int count=5;
	double mu_a2[5][3];
	double mu_a1[5][3];
	double ele_a2[5][3];
	double ele_a1[5][3];
	while (count)
	{
		infile_mu16 >>aa[0]>>bb[0];
		infile_ele16 >>cc[0]>>dd[0];
		infile_mu17 >>aa[1]>>bb[1];
		infile_ele17 >>cc[1]>>dd[1];
		infile_mu18 >>aa[2]>>bb[2];
		infile_ele18 >>cc[2]>>dd[2];

		cout<<aa<<" "<<bb<<" "<<cc<<" "<<dd<<endl; 
		mu_a2[5-count] [0]=aa[0];
		mu_a1[5-count] [0]=bb[0];
		ele_a2[5-count][0]=cc[0];
		ele_a1[5-count][0]=dd[0];
		mu_a2[5-count] [1]=aa[1];
		mu_a1[5-count] [1]=bb[1];
		ele_a2[5-count][1]=cc[1];
		ele_a1[5-count][1]=dd[1];
		mu_a2[5-count] [2]=aa[2];
		mu_a1[5-count] [2]=bb[2];
		ele_a2[5-count][2]=cc[2];
		ele_a1[5-count][2]=dd[2];
		count--;
	}

	Double_t fT0 = limit;
	Double_t weight_mu[5][3]={1.};
	Double_t weight_ele[5][3]={1.};
	for(Int_t i=0;i<5;i++){
		for(int j=0;j<3;j++){
			weight_mu[i][j]=mu_a2[i][j]*fT0*fT0+mu_a1[i][j]*fT0+1;
			weight_ele[i][j]=ele_a2[i][j]*fT0*fT0+ele_a1[i][j]*fT0+1;
			//		weight[i]=1;
		}
	}


	TFile *fmu1 = new TFile("out_aqgc_mu16.root","R"); 
	TFile *fmu2 = new TFile("out_aqgc_mu17.root","R"); 
	TFile *fmu3 = new TFile("out_aqgc_mu18.root","R"); 
	TFile *fele1 = new TFile("out_aqgc_ele16.root","R");
	TFile *fele2 = new TFile("out_aqgc_ele17.root","R");
	TFile *fele3 = new TFile("out_aqgc_ele18.root","R");

//        TH1D*h1=merge(fmu1,fmu2,fmu3,"Muon");
	cout<<"in muon ";
        TH1D*h2=merge(fmu1,fmu2,fmu3,"ZA");
	cout<<"in muon ";
        TH1D*h3=merge(fmu1,fmu2,fmu3,"bkg");
	cout<<"in muon ";
        TH1D*h4=merge(fmu1,fmu2,fmu3,"plj");
	cout<<"in muon ";
        TH1D*h5=merge(fmu1,fmu2,fmu3,"ZA-EWK");
        TH1D* hh6[3];
        hh6[0]= (TH1D*)fmu1->Get("ZA_EWK");
	cout<<"get ZA_EWK"<<endl;
        hh6[1]= (TH1D*)fmu2->Get("ZA-EWK");
        hh6[2]= (TH1D*)fmu3->Get("ZA-EWK");
//	hh6[0]->Scale(35.86/41.52);
//	hh6[2]->Scale(58.7/41.52);
	cout<<"get ZA_EWK"<<endl;
        
//        TH1D*h11=merge(fele1,fele2,fele3,"Ele");
	cout<<"in ele ";
        TH1D*h21=merge(fele1,fele2,fele3,"ZA");
	cout<<"in ele ";
        TH1D*h31=merge(fele1,fele2,fele3,"bkg");
	cout<<"in ele ";
        TH1D*h41=merge(fele1,fele2,fele3,"plj");
	cout<<"in ele ";
        TH1D*h51=merge(fele1,fele2,fele3,"ZA-EWK");
        TH1D* hh61[3];
        hh61[0]= (TH1D*)fele1->Get("ZA_EWK");
        hh61[1]= (TH1D*)fele2->Get("ZA-EWK");
        hh61[2]= (TH1D*)fele3->Get("ZA-EWK");
//        hh61[0]->Scale(35.86/41.52);
//        hh61[2]->Scale(58.7/41.52);
	cout<<"get ZA_EWK"<<endl;

//	h1->Add(h11);//data
	h2->Add(h21);//ZA 
	h3->Add(h31);//Others
	h4->Add(h41);//plj
	h5->Add(h51);// ZA-EWK

	for(int j=0;j<3;j++){
		for(Int_t i=0;i<5;i++){
			hh6[j]->SetBinContent(i+1,weight_mu[i][j]*hh6[j]->GetBinContent(i+1));
			hh61[j]->SetBinContent(i+1,weight_ele[i][j]*hh61[j]->GetBinContent(i+1));
		}
	}
        TH1D*h6=(TH1D*)hh6[0]->Clone();
        h6->Add(hh6[1]);
        h6->Add(hh6[2]);
        TH1D*h61=(TH1D*)hh61[0]->Clone();
        h61->Add(hh61[1]);
        h61->Add(hh61[2]);

	h6->Add(h61);//aQCD ZA
//	h6->Add(h5);//ZA-EWK
	h6->Add(h4);//plj
	h6->Add(h3);//Others
	h6->Add(h2);//ZA

//	h1->SetFillColor(kBlack);
//	h1->SetMarkerStyle(20);
//	h1->SetMarkerSize(1.3);

	h5->SetMarkerStyle(21);
	h5->SetMarkerColor(kRed-7);
	h5->SetFillColor(kRed-7);
	h5->SetLineColor(kRed-7);

	h4->SetFillColor(kYellow);
	h4->SetMarkerColor(kYellow);
	h4->SetLineColor(kYellow);

	h3->SetFillColor(kCyan);
	h3->SetMarkerColor(kCyan);
	h3->SetLineColor(kCyan);

	h2->SetFillColor(kBlue-6);
	h2->SetMarkerColor(kBlue-6);
	h2->SetLineColor(kBlue-6);

	h6->SetLineWidth(2);
	h6->SetLineColor(kRed);


	THStack * Mstack = new THStack("Mstack","");
	Mstack->Add(h3);
	Mstack->Add(h4);
	Mstack->Add(h2);
	Mstack->Add(h5);



	gStyle->SetPadBorderMode(0);
	gStyle->SetOptStat(0);
	//      gStyle->SetPadGridX(1);
	//      gStyle->SetPadGridY(1);
	gStyle->SetPadTickX(1);
	gStyle->SetPadTickY(1);
	gStyle->SetPadTickX(1);
	gStyle->SetPadTickY(1);
	gStyle->SetAxisColor(1, "XYZ");
	gStyle->SetStripDecimals(kTRUE);
	gStyle->SetTickLength(0.03, "XYZ");
	gStyle->SetNdivisions(510, "XYZ");

	TCanvas *c01 = new TCanvas("c01","",800,600);
	c01->SetLogy();
	TPad* fPad1 = new TPad("pad1", "pad1", 0.00, 0.00, 0.99, 0.99);
        fPad1->SetTicky();
        fPad1->SetTickx();
	fPad1->SetLogy();
	fPad1->Draw();
	fPad1->cd();
	//c01->SetLogx();

	Mstack->SetMaximum(float(4.0)*Mstack->GetMaximum());
	Mstack->SetMinimum(0.1);
	Mstack->Draw("bar HIST");
	//     Mstack->Draw("EP same");
	Mstack->GetXaxis()->SetTitle("m_{Z#gamma} [GeV] ");
	Mstack->GetYaxis()->SetTitle("Events / bin");
	Mstack->GetXaxis()->SetTitleSize(0.05);
	Mstack->GetXaxis()->SetTitleOffset(1.05);
	Mstack->GetYaxis()->SetTitleSize(0.05);
	Mstack->GetYaxis()->SetTitleOffset(1.05);
	//Mstack->GetXaxis()->CenterTitle();
	//Mstack->GetYaxis()->CenterTitle();

	TH1D* htemp = (TH1D*)(Mstack->GetStack()->Last());
	htemp->SetBinErrorOption(TH1::kPoisson);
	Double_t x[5];
	Double_t y[5];
	Double_t xerror_l[5];
	Double_t xerror_r[5];
	Double_t yerror_u[5];
	Double_t yerror_d[5];
	for(int i=0;i<5;i++)
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
	TGraphAsymmErrors* gr = new TGraphAsymmErrors(5, x, y, xerror_l,xerror_r, yerror_d, yerror_u);
	//        gr->SetFillColor(1);
	gr->SetFillStyle(3008);
	gr->Draw("SAME 2");

	h6->Draw("hist same");  // aQGC
	//	h1->Draw("hist P0 same");  // 0 for Zero data

	const double alpha = 1 - 0.6827;
/*	TGraphAsymmErrors * g = new TGraphAsymmErrors(h1);
	g->SetMarkerSize(0.5);
	g->SetMarkerStyle (20);
	for (int i = 0; i < g->GetN(); ++i) {
		int N = g->GetY()[i];
		double L =  (N==0) ? 0  : (ROOT::Math::gamma_quantile(alpha/2,N,1.));
		double U =  ROOT::Math::gamma_quantile_c(alpha/2,N+1,1) ;
		g->SetPointEYlow(i, N-L);
		g->SetPointEYhigh(i, U-N);
	}*/
	//	g->Draw("P");  // no A, otherwise will be overlaid




	TLegend *l1 = new TLegend(0.3,0.7,0.5,0.85);
	TLegend *l2 = new TLegend(0.52,0.7,0.72,0.85);
	//l1->SetBorderSize(2);
	l1->SetFillColor(10);
	l1->SetTextSize(0.04);
	l2->SetFillColor(10);
	l2->SetTextSize(0.04);
	l1->SetLineWidth(0);
	l1->SetFillStyle(0);
	l2->SetLineWidth(0);
	l2->SetFillStyle(0);
	//        l1->SetFillStyle(4000);
	//        l2->SetFillStyle(4000);
	//	l1->AddEntry(h1,"data","EP");
	char buffer[256];
	if (a.find("fM0")!=std::string::npos) sprintf(buffer, "F_{M,0}=-%0.2fe-12",limit);
	if (a.find("fM1")!=std::string::npos) sprintf(buffer, "F_{M,1}=-%0.2fe-12",limit);
	if (a.find("fM2")!=std::string::npos) sprintf(buffer, "F_{M,2}=-%0.2fe-12",limit);
	if (a.find("fM3")!=std::string::npos) sprintf(buffer, "F_{M,3}=-%0.2fe-12",limit);
	if (a.find("fM4")!=std::string::npos) sprintf(buffer, "F_{M,4}=-%0.2fe-12",limit);
	if (a.find("fM5")!=std::string::npos) sprintf(buffer, "F_{M,5}=-%0.2fe-12",limit);
	if (a.find("fM6")!=std::string::npos) sprintf(buffer, "F_{M,6}=-%0.2fe-12",limit);
	if (a.find("fM7")!=std::string::npos) sprintf(buffer, "F_{M,7}=-%0.2fe-12",limit);
	if (a.find("fT0")!=std::string::npos) sprintf(buffer, "F_{T,0}=-%0.2fe-12",limit);
	if (a.find("fT1")!=std::string::npos) sprintf(buffer, "F_{T,1}=-%0.2fe-12",limit);
	if (a.find("fT2")!=std::string::npos) sprintf(buffer, "F_{T,2}=-%0.2fe-12",limit);
	if (a.find("fT5")!=std::string::npos) sprintf(buffer, "F_{T,5}=-%0.2fe-12",limit);
	if (a.find("fT6")!=std::string::npos) sprintf(buffer, "F_{T,6}=-%0.2fe-12",limit);
	if (a.find("fT7")!=std::string::npos) sprintf(buffer, "F_{T,7}=-%0.2fe-12",limit);
	if (a.find("fT8")!=std::string::npos) sprintf(buffer, "F_{T,8}=-%0.2fe-12",limit);
	if (a.find("fT9")!=std::string::npos) sprintf(buffer, "F_{T,9}=-%0.2fe-12",limit);
//	l1->AddEntry(g,"Data","lp");
	l1->AddEntry(h5,"VBS Z#gamma","f");
	l1->AddEntry(h2,"QCD Z#gamma","f");
	l2->AddEntry(h4,"Nonprompt","f");
	l2->AddEntry(h3,"Other bkgd.","f");
	l2->AddEntry(h6,buffer,"l");
	l1->Draw("same");
	l2->Draw("same");

	//	cmsLumi(1);
	CMS_lumi(fPad1, 4, 0, "136.1");	
	char buffer1[256];
	sprintf(buffer1, "ZG_%s.png",a.c_str());
	char buffer2[256];
	sprintf(buffer2, "ZG_%s.C",a.c_str());
	char buffer3[256];
	sprintf(buffer3, "ZG_%s.pdf",a.c_str());

	//	c01->SaveAs(buffer1);
	//	c01->SaveAs(buffer2);
	fPad1->Update();
	c01->SaveAs(buffer3);

}

void plot(){
	aa("fM0",20.5);
	aa("fM1",40.5);
	aa("fM2",8.5);
	aa("fM3",18);
	aa("fM4",16);
	aa("fM5",25);
	aa("fM6",40.5);
	aa("fM7",62.5);
	aa("fT0",0.75);
	aa("fT1",1.0);
	aa("fT2",2.0);
	aa("fT5",0.75);
	aa("fT6",1.7);
	aa("fT7",2.85);
	aa("fT8",0.5);
	aa("fT9",1.3);
}
