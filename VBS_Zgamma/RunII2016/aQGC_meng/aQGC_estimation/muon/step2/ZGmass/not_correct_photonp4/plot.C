#include "TAxis.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TNtupleD.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector.h>

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



void plot(){
	setTDRStyle();
	Double_t a2[5] = {5.16069e-06,0.00112813,0.000246776,0.00323872,7.92093};
	Double_t a1[5] = {0.000535323,0.0024095,0.00862249,0.021855,0.438308};

	Double_t fT0 = 0.6;
	Double_t weight[5]={1.};
	for(Int_t i=0;i<5;i++){
		weight[i]=a2[i]*fT0*fT0+a1[i]*fT0+1;
//		weight[i]=1;
	}

	TFile *file1 = new TFile("out1.root","R"); 
	file1->cd("");
	TH1D* h1= (TH1D*) ZG_optimal_outDMuon_nominal->Clone();
	h1->Sumw2();
	TH1D* h2= (TH1D*) ZG_optimal_outZA_EWK_nominal->Clone();
	h2->Sumw2();
	TH1D* h3= (TH1D*) ZG_optimal_outphotonlikejet_mu_mediumlikephoton_nominal->Clone();
	h3->Sumw2();
	TH1D* h4= (TH1D*) ZG_optimal_bkg_nominal->Clone();
	h4->Sumw2();

	TH1D* h5= (TH1D*) ZG_optimal_outZA_EWK_nominal->Clone();
	h5->Sumw2();
	for(Int_t i=0;i<5;i++){
		h5->SetBinContent(i+1,weight[i]*h5->GetBinContent(i+1));
	}
	h5->Add(h4);
	h5->Add(h3);

	h1->SetFillColor(kBlack);
	h1->SetMarkerStyle(20);
	h1->SetMarkerSize(1.3);

	h2->SetMarkerStyle(21);
	h2->SetMarkerColor(kYellow);
	h2->SetFillColor(kYellow);
	h2->SetLineColor(kYellow);

	h3->SetFillColor(kViolet);
	h3->SetMarkerColor(kViolet);
	h3->SetLineColor(kViolet);

	h4->SetFillColor(kGreen+1);
	h4->SetMarkerColor(kGreen+1);
	h4->SetLineColor(kGreen+1);

	h5->SetLineWidth(2);
	h5->SetLineColor(kRed);


	THStack * Mstack = new THStack("Mstack","");
	Mstack->Add(h4);
	Mstack->Add(h3);
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
	Mstack->SetMinimum(0.01);
	Mstack->Draw("bar HIST");
	//     Mstack->Draw("EP same");
	Mstack->GetXaxis()->SetTitle("m_ZG (GeV) ");
	Mstack->GetYaxis()->SetTitle("Events /bin");
	Mstack->GetXaxis()->SetTitleSize(0.04);
	Mstack->GetYaxis()->SetTitleSize(0.04);
	//Mstack->GetXaxis()->CenterTitle();
	//Mstack->GetYaxis()->CenterTitle();
	Mstack->GetXaxis()->SetTitleOffset(1.5);


	h5->Draw("hist same");  // aQGC
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
	l1->AddEntry(h2,"VBS ZA","f");
	l1->AddEntry(h3,"JFP","f");
	l1->AddEntry(h4,"Other Bkg","f");
	l1->AddEntry(h5,"fT0=-0.6e-12","l");
	l1->Draw("same");

	cmsLumi(1);

	c01->SaveAs("ZG.png");
	c01->SaveAs("ZG.C");

}
