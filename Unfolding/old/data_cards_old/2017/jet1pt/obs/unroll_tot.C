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
	TFile* f1 = new TFile("hist_bkg.root","RECREATE");
	Double_t ZA_scale= 0.94;
	std::ostringstream strs;
	std::string lumivalue = strs.str();
	Double_t lumi=35.862;

	TFile* f_ZA16=TFile::Open("./2016/obs/root/hist_ZA.root");
	TFile* f_ZA17=TFile::Open("./2017/obs/root/hist_ZA.root");
	TFile* f_ZA18=TFile::Open("./2018/obs/root/hist_ZA.root");
	TH1D* hist_ZA16=(TH1D*)f_ZA16->Get("hist");
	TH1D* hist_ZA17=(TH1D*)f_ZA17->Get("hist");
	TH1D* hist_ZA18=(TH1D*)f_ZA18->Get("hist");
        
        TH1D* hist_ZA=(TH1D*)hist_ZA16->Clone();
        hist_ZA->Add(hist_ZA17)
        hist_ZA->Add(hist_ZA18)

	hist_ZA->SetFillColor(kMagenta);
	hist_ZA->SetMarkerColor(kMagenta);
	hist_ZA->SetLineColor(kMagenta);
//	hist_ZA->Scale(lumi*ZA_scale);
        const int kk =hist_ZA->GetXaxis()->GetNbins();
	const char *name[5]={"20~50","50~80","80~120","120~200","200~400"};
	for(Int_t i=1;i<=kk;i++){ hist_ZA->GetXaxis()->SetBinLabel(i,name[i-1]);}

	TFile* f_ZA_sig16=TFile::Open("./2016/obs/root/hist_ZA-EWK.root");
        TH1D* hist_ZA_sig16=(TH1D*)f_ZA_sig16->Get("hist");
	TFile* f_ZA_sig17=TFile::Open("./2017/obs/root/hist_ZA-EWK.root");
        TH1D* hist_ZA_sig17=(TH1D*)f_ZA_sig17->Get("hist");
	TFile* f_ZA_sig18=TFile::Open("./2018/obs/root/hist_ZA-EWK.root");
        TH1D* hist_ZA_sig18=(TH1D*)f_ZA_sig18->Get("hist");

        TH1D* hist_ZA_sig = (TH1D*)hist_ZA_sig16->Clone();
        hist_ZA_sig->Add(hist_ZA_sig17)
        hist_ZA_sig->Add(hist_ZA_sig18)
 
	hist_ZA_sig->SetFillColor(kRed-4);
	hist_ZA_sig->SetMarkerColor(kRed-4);
        hist_ZA_sig->SetLineColor(kRed-4);
//	hist_ZA_sig->Scale(lumi);
	hist_ZA_sig->SetMarkerStyle(21);
	for(Int_t i=1;i<=kk;i++){ hist_ZA_sig->GetXaxis()->SetBinLabel(i,name[i-1]);}

        TH1D* hist_ZA_sig_out16=(TH1D*)f_ZA_sig16->Get("hist3");
        TH1D* hist_ZA_sig_out17=(TH1D*)f_ZA_sig17->Get("hist3");
        TH1D* hist_ZA_sig_out18=(TH1D*)f_ZA_sig18->Get("hist3");

        TH1D* hist_ZA_sig_out=(TH1D*)hist_ZA_sig_out16->Clone();
        hist_ZA_sig_out->Add(hist_ZA_sig_out17)
        hist_ZA_sig_out->Add(hist_ZA_sig_out18)

	hist_ZA_sig_out->SetFillColor(kOrange);
	hist_ZA_sig_out->SetMarkerColor(kOrange);
        hist_ZA_sig_out->SetLineColor(kOrange);
//	hist_ZA_sig_out->Scale(lumi);
	hist_ZA_sig_out->SetMarkerStyle(21);
	for(Int_t i=1;i<=kk;i++){ hist_ZA_sig_out->GetXaxis()->SetBinLabel(i,name[i-1]);}

	TFile* f_WA16=TFile::Open("./2016/obs/root/hist_WA.root");
	TFile* f_WA17=TFile::Open("./2017/obs/root/hist_WA.root");
	TFile* f_WA18=TFile::Open("./2018/obs/root/hist_WA.root");
        TH1D* hist_WA16=(TH1D*)f_WA16->Get("hist");
        TH1D* hist_WA17=(TH1D*)f_WA17->Get("hist");
        TH1D* hist_WA18=(TH1D*)f_WA18->Get("hist");
        TH1D* hist_WA=(TH1D*)hist_WA16->Clone();
	hist_WA->Add(hist_WA17)
	hist_WA->Add(hist_WA18)

	hist_WA->SetFillColor(kBlue + 2);
	hist_WA->SetMarkerColor(kBlue+2);
        hist_WA->SetLineColor(kBlue+2);
//	hist_WA->Scale(lumi);
	for(Int_t i=1;i<=kk;i++){ hist_WA->GetXaxis()->SetBinLabel(i,name[i-1]);}

	TFile* f_VV16=TFile::Open("./2016/obs/root/hist_VV.root");
	TFile* f_VV17=TFile::Open("./2017/obs/root/hist_VV.root");
	TFile* f_VV18=TFile::Open("./2018/obs/root/hist_VV.root");
        TH1D* hist_VV16=(TH1D*)f_VV16->Get("hist");
        TH1D* hist_VV17=(TH1D*)f_VV17->Get("hist");
        TH1D* hist_VV18=(TH1D*)f_VV18->Get("hist");
        TH1D* hist_VV=(TH1D*)hist_VV16->Clone();   
        hist_VV->Add(hist_VV17);
        hist_VV->Add(hist_VV18);

	hist_VV->SetFillColor(kBlue - 6);
	hist_VV->SetMarkerColor(kBlue-6);
        hist_VV->SetLineColor(kBlue-6);
//	hist_VV->Scale(lumi);
	for(Int_t i=1;i<=kk;i++){ hist_VV->GetXaxis()->SetBinLabel(i,name[i-1]);}

	TFile* f_TTA16=TFile::Open("./2016/obs/root/hist_TTA.root");
	TFile* f_TTA17=TFile::Open("./2017/obs/root/hist_TTA.root");
	TFile* f_TTA18=TFile::Open("./2018/obs/root/hist_TTA.root");
        TH1D* hist_TTA16=(TH1D*)f_TTA16->Get("hist");
        TH1D* hist_TTA17=(TH1D*)f_TTA17->Get("hist");
        TH1D* hist_TTA18=(TH1D*)f_TTA18->Get("hist");
        TH1D* hist_TTA=(TH1D*)hist_TTA16->Clone();
        hist_TTA->Add(hist_TTA17);
        hist_TTA->Add(hist_TTA18);

	hist_TTA->SetFillColor(kCyan);
	hist_TTA->SetMarkerColor(kCyan);
        hist_TTA->SetLineColor(kCyan);
//	hist_TTA->Scale(lumi);
	for(Int_t i=1;i<=kk;i++){ hist_TTA->GetXaxis()->SetBinLabel(i,name[i-1]);}

	TFile* f_ST16=TFile::Open("./2016/obs/root/hist_ST.root");
	TFile* f_ST17=TFile::Open("./2017/obs/root/hist_ST.root");
	TFile* f_ST18=TFile::Open("./2018/obs/root/hist_ST.root");
        TH1D* hist_ST16=(TH1D*)f_ST16->Get("hist");
        TH1D* hist_ST17=(TH1D*)f_ST17->Get("hist");
        TH1D* hist_ST18=(TH1D*)f_ST18->Get("hist");
        TH1D* hist_ST=(TH1D*)hist_ST16->Clone();
        hist_ST->Add(hist_ST17);
        hist_ST->Add(hist_ST18);

	hist_ST->SetFillColor(kGreen);
	hist_ST->SetMarkerColor(kGreen);
        hist_ST->SetLineColor(kGreen);
//	hist_ST->Scale(lumi);
	for(Int_t i=1;i<=kk;i++){ hist_ST->GetXaxis()->SetBinLabel(i,name[i-1]);}

	TFile* f_plj16=TFile::Open("./2016/obs/root/hist_plj.root");
	TFile* f_plj17=TFile::Open("./2017/obs/root/hist_plj.root");
	TFile* f_plj18=TFile::Open("./2018/obs/root/hist_plj.root");
        TH1D* hist_plj16=(TH1D*)f_plj16->Get("hist");
        TH1D* hist_plj17=(TH1D*)f_plj17->Get("hist");
        TH1D* hist_plj18=(TH1D*)f_plj18->Get("hist");

        TH1D* hist_plj=(TH1D*)hist_plj16->Clone();   
        hist_plj->Add(hist_plj17);
        hist_plj->Add(hist_plj18);

	hist_plj->SetFillColor(kYellow);
	hist_plj->SetMarkerColor(kYellow);
        hist_plj->SetLineColor(kYellow);
	for(Int_t i=1;i<=kk;i++){ hist_plj->GetXaxis()->SetBinLabel(i,name[i-1]);}

	TFile* f_Data16=TFile::Open("./2016/obs/root/hist_Data16.root");
	TFile* f_Data17=TFile::Open("./2017/obs/root/hist_Data16.root");
	TFile* f_Data18=TFile::Open("./2018/obs/root/hist_Data16.root");
        TH1D* hist_Data16=(TH1D*)f_Data16->Get("hist");
        TH1D* hist_Data17=(TH1D*)f_Data17->Get("hist");
        TH1D* hist_Data18=(TH1D*)f_Data18->Get("hist");

        TH1D* hist_Data=(TH1D*)hist_Data16->Clone();
        hist_Data->Add(hist_Data17);
        hist_Data->Add(hist_Data16);

	THStack* hs = new THStack("hs", "");
        TH1D*hbkg = (TH1D*)hist_ST->Clone();
	hbkg->Add(hist_TTA);
	hbkg->Add(hist_VV);
	hbkg->Add(hist_WA);
	hbkg->Add(hist_plj);
	hbkg->Add(hist_ZA);
//	hbkg->Add(hist_ZA_sig_out);
        
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
//        hist_Data->Draw("EP SAME");

	TLegend* leg = new TLegend(0.82, 0.7, 0.95, 0.88);
        leg->SetMargin(0.4);
	leg->AddEntry(hist_ST, "ST");
	leg->AddEntry(hist_TTA, "TTA");
//	leg->AddEntry(hist_Data, "Data");
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
        f1->cd();
        hbkg->Write();
	f1->Close();

//	c1->SaveAs("aa.root");
	c1->SaveAs("aa.pdf");
	c1->SaveAs("aa.C");
        return 0;
  
}
