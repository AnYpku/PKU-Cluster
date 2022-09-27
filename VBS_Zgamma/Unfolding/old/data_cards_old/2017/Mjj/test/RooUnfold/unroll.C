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


int unroll(){
	setTDRStyle();
	TFile* fout = new TFile("aa.root","RECREATE");
	Double_t ZA_scale= 0.94;
	std::ostringstream strs;
	std::string lumivalue = strs.str();
	Double_t lumi=35.862;

	TFile* f_ZA=TFile::Open("./root/hist_ZA_total.root");
	TH1D* hist_ZA=(TH1D*)f_ZA->Get("hist");
	hist_ZA->SetFillColor(kMagenta);
	hist_ZA->SetMarkerColor(kMagenta);
	hist_ZA->SetLineColor(kMagenta);
//	hist_ZA->Scale(lumi*ZA_scale);
        const int kk =hist_ZA->GetXaxis()->GetNbins();
	const char *name[5]={"20~50","50~80","80~120","120~200","200~400"};
	for(Int_t i=1;i<=kk;i++){ hist_ZA->GetXaxis()->SetBinLabel(i,name[i-1]);}

	TFile* f_ZA_sig=TFile::Open("./root/hist_ZA-EWK.root");
        TH1D* hist_ZA_sig=(TH1D*)f_ZA_sig->Get("hist");
	hist_ZA_sig->SetFillColor(kRed-4);
	hist_ZA_sig->SetMarkerColor(kRed-4);
        hist_ZA_sig->SetLineColor(kRed-4);
//	hist_ZA_sig->Scale(lumi);
	hist_ZA_sig->SetMarkerStyle(21);
	for(Int_t i=1;i<=kk;i++){ hist_ZA_sig->GetXaxis()->SetBinLabel(i,name[i-1]);}

        TH1D* hist_ZA_sig_out=(TH1D*)f_ZA_sig->Get("hist3");
	hist_ZA_sig_out->SetFillColor(kOrange);
	hist_ZA_sig_out->SetMarkerColor(kOrange);
        hist_ZA_sig_out->SetLineColor(kOrange);
//	hist_ZA_sig_out->Scale(lumi);
	hist_ZA_sig_out->SetMarkerStyle(21);
	for(Int_t i=1;i<=kk;i++){ hist_ZA_sig_out->GetXaxis()->SetBinLabel(i,name[i-1]);}

	TFile* f_WA=TFile::Open("./root/hist_WA.root");
        TH1D* hist_WA=(TH1D*)f_WA->Get("hist");
	hist_WA->SetFillColor(kBlue + 2);
	hist_WA->SetMarkerColor(kBlue+2);
        hist_WA->SetLineColor(kBlue+2);
//	hist_WA->Scale(lumi);
	for(Int_t i=1;i<=kk;i++){ hist_WA->GetXaxis()->SetBinLabel(i,name[i-1]);}

	TFile* f_VV=TFile::Open("./root/hist_VV.root");
        TH1D* hist_VV=(TH1D*)f_VV->Get("hist");
	hist_VV->SetFillColor(kBlue - 6);
	hist_VV->SetMarkerColor(kBlue-6);
        hist_VV->SetLineColor(kBlue-6);
//	hist_VV->Scale(lumi);
	for(Int_t i=1;i<=kk;i++){ hist_VV->GetXaxis()->SetBinLabel(i,name[i-1]);}

	TFile* f_TTA=TFile::Open("./root/hist_TTA.root");
        TH1D* hist_TTA=(TH1D*)f_TTA->Get("hist");
	hist_TTA->SetFillColor(kCyan);
	hist_TTA->SetMarkerColor(kCyan);
        hist_TTA->SetLineColor(kCyan);
//	hist_TTA->Scale(lumi);
	for(Int_t i=1;i<=kk;i++){ hist_TTA->GetXaxis()->SetBinLabel(i,name[i-1]);}

	TFile* f_ST=TFile::Open("./root/hist_ST.root");
        TH1D* hist_ST=(TH1D*)f_ST->Get("hist");
	hist_ST->SetFillColor(kGreen);
	hist_ST->SetMarkerColor(kGreen);
        hist_ST->SetLineColor(kGreen);
//	hist_ST->Scale(lumi);
	for(Int_t i=1;i<=kk;i++){ hist_ST->GetXaxis()->SetBinLabel(i,name[i-1]);}

	TFile* f_plj=TFile::Open("./root/hist_plj_mu.root");
        TH1D* hist_plj=(TH1D*)f_plj->Get("hist");
	hist_plj->SetFillColor(kYellow);
	hist_plj->SetMarkerColor(kYellow);
        hist_plj->SetLineColor(kYellow);
	for(Int_t i=1;i<=kk;i++){ hist_plj->GetXaxis()->SetBinLabel(i,name[i-1]);}

	TFile* f_Data=TFile::Open("./root/hist_DMuon.root");
        TH1D* hist_Muon=(TH1D*)f_Data->Get("hist");

	THStack* hs = new THStack("hs", "");
	hs->Add(hist_ST);
	hs->Add(hist_TTA);
	hs->Add(hist_VV);
	hs->Add(hist_WA);
	hs->Add(hist_plj);
	hs->Add(hist_ZA);
	hs->Add(hist_ZA_sig);
	hs->Add(hist_ZA_sig_out);

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
//        hist_Muon->Draw("EP SAME");

	TLegend* leg = new TLegend(0.82, 0.7, 0.95, 0.88);
        leg->SetMargin(0.4);
	leg->AddEntry(hist_ST, "ST");
	leg->AddEntry(hist_TTA, "TTA");
//	leg->AddEntry(hist_Muon, "Data");
	leg->AddEntry(hist_VV, "VV");
	leg->AddEntry(hist_WA, "WA");
	leg->AddEntry(hist_plj, "non-prompt");
	leg->AddEntry(hist_ZA, "ZA");
	leg->AddEntry(hist_ZA_sig, "ZA_sig");
	leg->AddEntry(hist_ZA_sig_out, "ZA_sig_out");
	leg->Draw();
	
	cmsLumi(1);

	fout->cd();
	hs->Write();
	fout->Close();

//	c1->SaveAs("aa.root");
	c1->SaveAs("aa.pdf");
	c1->SaveAs("aa.C");
        return 0;
  
}
