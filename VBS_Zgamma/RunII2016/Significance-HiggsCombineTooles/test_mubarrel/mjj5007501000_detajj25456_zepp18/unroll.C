#include "TH1.h"
#include "TFile.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TStyle.h"
#include <iostream>
#include "TLegend.h"
#include "THStack.h"
#include "CMSTDRStyle.h"
#include "CMS_lumi.C"
using namespace std;

void cmsLumi(bool channel) 
{
        TLatex latex;
        latex.SetNDC();
        latex.SetTextSize(0.04);
        latex.SetLineWidth(2);
        float lumiel=35.8*0.96;
        float lumimu=35.8;
        int beamcomenergytev=13;
        latex.SetTextAlign(31); 
        latex.SetTextAlign(11);
        latex.DrawLatex(0.18,0.82,"Preliminary");
        latex.DrawLatex(0.18,0.86,"CMS");
        latex.SetTextSize(0.03);
        latex.DrawLatex(0.76,0.92,Form("35.862 fb^{-1} (%d TeV)", (beamcomenergytev)));
}

TH1D* unroll(TH2D* th2_in,Double_t* xbin, Double_t* ybin,  Int_t xbins_in, Int_t ybins_in)
{
	TH2D* th2 = th2_in;
	Int_t nbinsx =xbins_in;
	Int_t nbinsy =ybins_in;
	Int_t nbins = nbinsx*nbinsy;

	TH1D* h1_out = new TH1D("unrolled hist", "unrolled hist", nbins, 0, nbins);

	for(Int_t iy=1; iy<=nbinsy; iy++){
		for(Int_t ix=1; ix<=nbinsx; ix++){
			Double_t x_temp = 0.5*(xbin[ix-1]+xbin[ix]);
			Double_t y_temp = 0.5*(ybin[iy-1]+ybin[iy]);
			h1_out->SetBinContent(ix+(iy-1)*nbinsx,th2->GetBinContent(th2->FindBin(x_temp, y_temp)));
			h1_out->SetBinError(ix+(iy-1)*nbinsx,th2->GetBinError(th2->FindBin(x_temp, y_temp)));
		}
	}
	return h1_out;
}

int main(){
	setTDRStyle();
	TFile* fout = new TFile("aa.root","RECREATE");
	Double_t ZA_scale= 0.94;
	std::ostringstream strs;
	std::string lumivalue = strs.str();
	Double_t lumi=35.862;
	Double_t mjj_bins[4]={500, 800, 1200, 2000};
//        Double_t mlla_bins[5]={90, 130, 170, 210, 240};
        Double_t detajj_bins[4]={2.5,4.5,6,6.5};

	TFile* f_ZA=TFile::Open("./2d_ZA.root");
	TH2D* th2_ZA=(TH2D*)f_ZA->Get("th2");
//	TH1D* t_ZA=unroll(th2_ZA, mjj_bins, mlla_bins, 4,4);
	TH1D* t_ZA=unroll(th2_ZA, mjj_bins, detajj_bins, 3,3);
	t_ZA->SetFillColor(kMagenta);
	t_ZA->SetMarkerColor(kMagenta);
	t_ZA->SetLineColor(kMagenta);
	t_ZA->Scale(lumi*ZA_scale);
	const char *name[9]={"Mjj 500~800","Mjj 800~1200","Mjj 1200~2000","Mjj 500~800","Mjj 800~1200","Mjj 1200~2000","Mjj 500~800","Mjj 800~1200","Mjj 1200~2000"};

	TFile* f_ZA_sig=TFile::Open("./2d_ZA_EWK.root");
        TH2D* th2_ZA_sig=(TH2D*)f_ZA_sig->Get("th2");
//        TH1D* t_ZA_sig=unroll(th2_ZA_sig, mjj_bins, mlla_bins, 4,4);
        TH1D* t_ZA_sig=unroll(th2_ZA_sig, mjj_bins, detajj_bins, 3,3);
	t_ZA_sig->SetFillColor(kRed-4);
	t_ZA_sig->SetMarkerColor(kRed-4);
        t_ZA_sig->SetLineColor(kRed-4);
	t_ZA_sig->Scale(lumi);
	t_ZA_sig->SetMarkerStyle(21);

	TFile* f_WA=TFile::Open("./2d_WA.root");
        TH2D* th2_WA=(TH2D*)f_WA->Get("th2");
//        TH1D* t_WA=unroll(th2_WA, mjj_bins, mlla_bins, 4,4);
        TH1D* t_WA=unroll(th2_WA, mjj_bins, detajj_bins, 3,3);
	t_WA->SetFillColor(kBlue + 2);
	t_WA->SetMarkerColor(kBlue+2);
        t_WA->SetLineColor(kBlue+2);
	t_WA->Scale(lumi);

	TFile* f_VV=TFile::Open("./2d_VV.root");
        TH2D* th2_VV=(TH2D*)f_VV->Get("th2");
//        TH1D* t_VV=unroll(th2_VV, mjj_bins, mlla_bins, 4,4);
        TH1D* t_VV=unroll(th2_VV, mjj_bins, detajj_bins, 3,3);
	t_VV->SetFillColor(kBlue - 6);
	t_VV->SetMarkerColor(kBlue-6);
        t_VV->SetLineColor(kBlue-6);
	t_VV->Scale(lumi);

	TFile* f_TTA=TFile::Open("./2d_TTA.root");
        TH2D* th2_TTA=(TH2D*)f_TTA->Get("th2");
//        TH1D* t_TTA=unroll(th2_TTA, mjj_bins, mlla_bins, 4,4);
        TH1D* t_TTA=unroll(th2_TTA, mjj_bins, detajj_bins, 3,3);
	t_TTA->SetFillColor(kCyan);
	t_TTA->SetMarkerColor(kCyan);
        t_TTA->SetLineColor(kCyan);
	t_TTA->Scale(lumi);

	TFile* f_ST=TFile::Open("./2d_ST.root");
        TH2D* th2_ST=(TH2D*)f_ST->Get("th2");
//        TH1D* t_ST=unroll(th2_ST, mjj_bins, mlla_bins, 4,4);
        TH1D* t_ST=unroll(th2_ST, mjj_bins, detajj_bins, 3,3);
	t_ST->SetFillColor(kGreen);
	t_ST->SetMarkerColor(kGreen);
        t_ST->SetLineColor(kGreen);
	t_ST->Scale(lumi);
	for(Int_t i=1;i<=9;i++){ t_ST->GetXaxis()->SetBinLabel(i,name[i-1]);}

	TFile* f_plj=TFile::Open("./2d_plj.root");
        TH2D* th2_plj=(TH2D*)f_plj->Get("th2");
        TH1D* t_plj=unroll(th2_plj, mjj_bins, detajj_bins, 3,3);
	t_plj->SetFillColor(kYellow);
	t_plj->SetMarkerColor(kYellow);
        t_plj->SetLineColor(kYellow);

	THStack* hs = new THStack("hs", "");
	hs->Add(t_ST);
	hs->Add(t_TTA);
	hs->Add(t_VV);
	hs->Add(t_WA);
	hs->Add(t_plj);
	hs->Add(t_ZA);
	hs->Add(t_ZA_sig);

	gStyle->SetPadBorderMode(0);
        gStyle->SetOptStat(0);
	gStyle->SetPadTickX(1);
        gStyle->SetPadTickY(1);
        gStyle->SetPadTickX(1);
        gStyle->SetPadTickY(1);
        gStyle->SetAxisColor(1, "XYZ");
        gStyle->SetStripDecimals(kTRUE);
        gStyle->SetTickLength(0.03, "XYZ");
        gStyle->SetNdivisions(510, "XYZ");

	TCanvas* c1=new TCanvas("","",800,600);
	c1->cd();
	TPad* fPad1 = new TPad("pad1", "", 0.00, 0.00, 0.99, 0.99);
	fPad1->Draw();
	CMS_lumi(fPad1, 4, 0, lumivalue);
	hs->Draw("HIST");
	hs->GetYaxis()->SetTitleOffset(0.8);
	hs->GetYaxis()->SetTitle("Events /bin");

	TLegend* leg = new TLegend(0.82, 0.7, 0.95, 0.88);
        leg->SetMargin(0.4);
	leg->AddEntry(t_ZA_sig, "ZA_sig");
	leg->AddEntry(t_ZA, "ZA");
	leg->AddEntry(t_plj, "non-prompt");
	leg->AddEntry(t_WA, "WA");
	leg->AddEntry(t_VV, "VV");
	leg->AddEntry(t_TTA, "TTA");
	leg->AddEntry(t_ST, "ST");
	leg->Draw();
	
	cmsLumi(0);

	fout->cd();
	hs->Write();
	fout->Close();

	c1->SaveAs("aa.png");
	c1->SaveAs("aa.pdf");
	c1->SaveAs("aa.C");


}
