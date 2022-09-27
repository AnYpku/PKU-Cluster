#include "TAxis.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TNtupleD.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector.h>
#include <fstream>

#include "tdrstyle.C"
////CMS Preliminary label and lumi -- upper left corner
void cmsLumi(bool channel) //0 for el
{
	TLatex latex;
	latex.SetNDC();
	latex.SetTextSize(0.04);
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
	latex.DrawLatex(0.21,0.88,"CMS");
	latex.SetTextSize(0.03);
	latex.DrawLatex(0.76,0.96,Form("35.862 fb^{-1} (%d TeV)", (beamcomenergytev)));
}



void aa(string a, double limit){
	setTDRStyle();
	string mu_file="/eos/uscms/store/user/mlu/ZAjj-more-HLT/aQGC_estimation/muon/step1/ZGmass/paramsets_"+a+"_mu.txt";
	string ele_file="/eos/uscms/store/user/mlu/ZAjj-more-HLT/aQGC_estimation/ele/step1/ZGmass/paramsets_"+a+"_el.txt";
	ifstream infile_mu;
	ifstream infile_ele;
        infile_mu.open(mu_file.c_str());
        infile_ele.open(ele_file.c_str());
	double aa, bb, cc, dd;
	int count=5;
	double mu_a2[5];
	double mu_a1[5];
	double ele_a2[5];
	double ele_a1[5];
	while (count)
	{
		infile_mu >>aa>>bb;
		infile_ele >>cc>>dd;
		cout<<aa<<" "<<bb<<" "<<cc<<" "<<dd<<endl; 
		mu_a2[5-count]=aa;
		mu_a1[5-count]=bb;
		ele_a2[5-count]=cc;
		ele_a1[5-count]=dd;
		count--;
	}

	Double_t fT0 = limit;
	Double_t weight_mu[5]={1.};
	Double_t weight_ele[5]={1.};
	for(Int_t i=0;i<5;i++){
		weight_mu[i]=mu_a2[i]*fT0*fT0+mu_a1[i]*fT0+1;
		weight_ele[i]=ele_a2[i]*fT0*fT0+ele_a1[i]*fT0+1;
//		weight[i]=1;
	}


	TFile *file1 = new TFile("out_m.root","R"); 
	file1->cd("");
	TH1D* h1= (TH1D*) ZG_optimal_outDMuon_nominal->Clone();
	h1->Sumw2();
	TH1D* h2= (TH1D*) ZG_optimal_outZA_EWK_nominal->Clone();
	h2->Sumw2();
	TH1D* h3= (TH1D*) ZG_optimal_outphotonlikejet_mu_mediumlikephoton_nominal->Clone();
	h3->Sumw2();
	TH1D* h4= (TH1D*) ZG_optimal_bkg_nominal->Clone();
	h4->Sumw2();
	TH1D* h5= (TH1D*) ZG_optimal_ZA_nominal->Clone();
	h5->Sumw2();
	TH1D* h6= (TH1D*) ZG_optimal_outZA_EWK_nominal->Clone();
	h6->Sumw2();

	TFile *file2 = new TFile("out_e.root","R");
        file2->cd("");
        TH1D* h11= (TH1D*) ZG_optimal_outDEle_nominal->Clone();
        h11->Sumw2();
        TH1D* h21= (TH1D*) ZG_optimal_outZA_EWK_nominal->Clone();
        h21->Sumw2();
        TH1D* h31= (TH1D*) ZG_optimal_outphotonlikejet_ele_mediumlikephoton_nominal->Clone();
        h31->Sumw2();
        TH1D* h41= (TH1D*) ZG_optimal_bkg_nominal->Clone();
        h41->Sumw2();
        TH1D* h51= (TH1D*) ZG_optimal_ZA_nominal->Clone();
        h51->Sumw2();
	TH1D* h61= (TH1D*) ZG_optimal_outZA_EWK_nominal->Clone();
	h61->Sumw2();

	h1->Add(h11);
	h2->Add(h21);
	h3->Add(h31);
	h4->Add(h41);
	h5->Add(h51);

	for(Int_t i=0;i<5;i++){
		h6->SetBinContent(i+1,weight_mu[i]*h6->GetBinContent(i+1));
		h61->SetBinContent(i+1,weight_ele[i]*h61->GetBinContent(i+1));
	}
	h6->Add(h61);
	h6->Add(h5);
	h6->Add(h4);
	h6->Add(h3);

	h1->SetFillColor(kBlack);
	h1->SetMarkerStyle(20);
	h1->SetMarkerSize(1.3);

	h2->SetMarkerStyle(21);
	h2->SetMarkerColor(kYellow);
	h2->SetFillColor(kYellow);
	h2->SetLineColor(kYellow);

	h3->SetFillColor(7);
	h3->SetMarkerColor(7);
	h3->SetLineColor(7);

	h4->SetFillColor(kGreen+1);
	h4->SetMarkerColor(kGreen+1);
	h4->SetLineColor(kGreen+1);

	h5->SetFillColor(6);
	h5->SetMarkerColor(6);
	h5->SetLineColor(6);

	h6->SetLineWidth(2);
	h6->SetLineColor(kRed);


	THStack * Mstack = new THStack("Mstack","");
	Mstack->Add(h4);
	Mstack->Add(h3);
	Mstack->Add(h5);
	Mstack->Add(h2);


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

	TCanvas *c01 = new TCanvas("c01","",700,500);
	c01->SetLogy();
	//c01->SetLogx();

	Mstack->SetMaximum(float(4.0)*Mstack->GetMaximum());
	Mstack->SetMinimum(0.1);
	Mstack->Draw("bar HIST");
	//     Mstack->Draw("EP same");
	Mstack->GetXaxis()->SetTitle("ZGmass (GeV) ");
	Mstack->GetYaxis()->SetTitle("Events /bin");
	Mstack->GetXaxis()->SetTitleSize(0.04);
	Mstack->GetYaxis()->SetTitleSize(0.04);
	//Mstack->GetXaxis()->CenterTitle();
	//Mstack->GetYaxis()->CenterTitle();
	Mstack->GetXaxis()->SetTitleOffset(1.5);


	h6->Draw("hist same");  // aQGC
//	h1->Draw("hist P0 same");  // 0 for Zero data

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




	TLegend *l1 = new TLegend(0.5,0.78,0.65,0.91);
	//l1->SetBorderSize(2);
	l1->SetFillColor(10);
//	l1->AddEntry(h1,"data","EP");
	char buffer[256];
        sprintf(buffer, "%s=-%0.2fe-12",a.c_str(),limit);
	l1->AddEntry(h2,"VBS ZA","f");
	l1->AddEntry(h5,"QCD ZA","f");
	l1->AddEntry(h3,"non-prompt","f");
	l1->AddEntry(h4,"Other Bkg","f");
	l1->AddEntry(h6,buffer,"l");
	l1->Draw("same");

	cmsLumi(1);

	char buffer1[256];
        sprintf(buffer1, "ZG_%s.png",a.c_str());
	char buffer2[256];
        sprintf(buffer2, "ZG_%s.C",a.c_str());

	c01->SaveAs(buffer1);
	c01->SaveAs(buffer2);

}

void plot(){
	aa("fM0",15);
	aa("fM1",30);
	aa("fM2",6);
	aa("fM3",13);
	aa("fM4",12);
	aa("fM5",19);
	aa("fM6",30);
	aa("fM7",46);
	aa("fT0",0.5);
	aa("fT1",0.7);
	aa("fT2",1.5);
	aa("fT5",0.5);
	aa("fT6",1.3);
	aa("fT7",2.0);
	aa("fT8",0.4);
	aa("fT9",0.9);
}
