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
        float lumiel=58.7;
        float lumimu=58.7;
        int beamcomenergytev=13;
        latex.SetTextAlign(31); 
        latex.SetTextAlign(11);
        latex.DrawLatex(0.18,0.82,"Preliminary");
        latex.DrawLatex(0.18,0.86,"CMS");
        latex.SetTextSize(0.03);
        latex.DrawLatex(0.76,0.92,Form("58.7 fb^{-1} (%d TeV)", (beamcomenergytev)));
}

TH1D* unroll(TH2D* th2_in,Double_t* xbin, Double_t* ybin,  Int_t xbins_in, Int_t ybins_in,TString hname)
{
        TH2D* th2 = th2_in;
        Int_t nbinsx =xbins_in;
        Int_t nbinsy =ybins_in;
        Int_t nbins = nbinsx*nbinsy;

    TH1D* h1= new TH1D("h1", "", nbins, 0, nbins);
    TH1D* h1_out= new TH1D(hname, "", nbins-2, 0, nbins-2);
    for(Int_t iy=1; iy<=nbinsy; iy++){
            for(Int_t ix=1; ix<=nbinsx; ix++){
                    Double_t x_temp = 0.5*(xbin[ix-1]+xbin[ix]);
                    Double_t y_temp = 0.5*(ybin[iy-1]+ybin[iy]);
                    h1->SetBinContent(ix+(iy-1)*nbinsx,th2->GetBinContent(th2->FindBin(x_temp, y_temp)));//void SetBinContent(Int_t bin, Double_t content),the FindBin function can return Global bin number corresponding to x,y
                    h1->SetBinError(ix+(iy-1)*nbinsx,th2->GetBinError(th2->FindBin(x_temp, y_temp)));
            }
    }
    for(Int_t i=0;i<6;i++){
        h1_out->SetBinContent(i+1,h1->GetBinContent(i+1));
        h1_out->SetBinError(i+1,h1->GetBinError(i+1));
    }
//    h1_out->SetBinContent(7,h1->GetBinContent(7) + h1->GetBinContent(8)+h1->GetBinContent(9) );
    h1_out->SetBinContent(7,h1->GetBinContent(7) + h1->GetBinContent(8)+h1->GetBinContent(9) );
//    h1_out->SetBinContent(8,h1->GetBinContent(9));
//    h1_out->SetBinError(7,sqrt(h1->GetBinError(7)*h1->GetBinError(7) + h1->GetBinError(8)*h1->GetBinError(8))+h1->GetBinError(9)*h1->GetBinError(9) );
//    cout<<hname<<"; "<<h1->GetBinContent(7)<<"; "<<h1->GetBinContent(8)<<"; "<<h1_out->GetBinContent(7)<<endl;
    delete h1;
    return h1_out;
}

int unroll(){
	setTDRStyle();
	TFile* fout = new TFile("aa.root","RECREATE");
	Double_t ZA_scale= 1;
	std::ostringstream strs;
	std::string lumivalue = strs.str();
	Double_t lumi=58.7;
	Double_t mjj_bins[4]={500, 800, 1200, 2000};
//	Double_t mjj_bins[4]={500, 750, 850, 2000};
//        Double_t mlla_bins[5]={90, 130, 170, 210, 240};
        Double_t detajj_bins[4]={2.5,4.5,6,6.5};

	TFile* f_ZA=TFile::Open("./hist_ZA.root");
	TH2D* th2_ZA=(TH2D*)f_ZA->Get("hist_bkg");
//	TH1D* t_ZA=unroll(th2_ZA, mjj_bins, mlla_bins, 4,4);
	TH1D* t_ZA=unroll(th2_ZA, mjj_bins, detajj_bins, 3,3,"t_ZA");
	cout<<t_ZA->GetSum()<<endl;
        cout<<t_ZA->GetSumOfWeights()<<endl;
        cout<<t_ZA->Integral()<<endl;

	t_ZA->SetFillColor(kRed-7);
	t_ZA->SetMarkerColor(kRed-7);
	t_ZA->SetLineColor(kRed-7);
//	t_ZA->Scale(lumi*ZA_scale);
	const char *name[7]={"Mjj 500~800","Mjj 800~1200","Mjj 1200~2000","Mjj 500~800","Mjj 800~1200","Mjj 1200~2000","Mjj 500~2000"};
//	const char *name[9]={"Mjj 500~600","Mjj 600~800","Mjj 800~2000","Mjj 500~600","Mjj 600~800","Mjj 800~2000","Mjj 500~600","Mjj 600~800","Mjj 800~2000"};

	TFile* f_ZA_sig=TFile::Open("./hist_ZA-EWK.root");
        TH2D* th2_ZA_sig=(TH2D*)f_ZA_sig->Get("hist_sig");
        TH1D* t_ZA_sig=unroll(th2_ZA_sig, mjj_bins, detajj_bins, 3,3,"ZA_sig");
	t_ZA_sig->SetFillColor(kRed);
	t_ZA_sig->SetMarkerColor(kRed);
        t_ZA_sig->SetLineColor(kRed);
//	t_ZA_sig->Scale(lumi);
	t_ZA_sig->SetMarkerStyle(21);

        TH2D* th2_ZA_sigout=(TH2D*)f_ZA_sig->Get("hist_sigout");
        TH1D* t_ZA_sigout=unroll(th2_ZA_sigout, mjj_bins, detajj_bins, 3,3,"ZA_sigout");
	t_ZA_sigout->SetFillColor(kBlack);
	t_ZA_sigout->SetMarkerColor(kBlack);
        t_ZA_sigout->SetLineColor(kBlack);
//	t_ZA_sigout->Scale(lumi);
	t_ZA_sigout->SetMarkerStyle(21);

	TFile* f_WA=TFile::Open("./hist_WA.root");
        TH2D* th2_WA=(TH2D*)f_WA->Get("hist_bkg");
//        TH1D* t_WA=unroll(th2_WA, mjj_bins, mlla_bins, 4,4);
        TH1D* t_WA=unroll(th2_WA, mjj_bins, detajj_bins, 3,3,"WA");
	t_WA->SetFillColor(kBlue -7);
	t_WA->SetMarkerColor(kBlue-7);
        t_WA->SetLineColor(kBlue-7);
//	t_WA->Scale(lumi);

	TFile* f_VV=TFile::Open("./hist_VV.root");
        TH2D* th2_VV=(TH2D*)f_VV->Get("hist_bkg");
//        TH1D* t_VV=unroll(th2_VV, mjj_bins, mlla_bins, 4,4);
        TH1D* t_VV=unroll(th2_VV, mjj_bins, detajj_bins, 3,3,"VV");
	t_VV->SetFillColor(kBlue - 4);
	t_VV->SetMarkerColor(kBlue-4);
        t_VV->SetLineColor(kBlue-4);
//	t_VV->Scale(lumi);

	TFile* f_TTA=TFile::Open("./hist_TTA.root");
        TH2D* th2_TTA=(TH2D*)f_TTA->Get("hist_bkg");
//        TH1D* t_TTA=unroll(th2_TTA, mjj_bins, mlla_bins, 4,4);
        TH1D* t_TTA=unroll(th2_TTA, mjj_bins, detajj_bins, 3,3,"TTA");
	t_TTA->SetFillColor(kGreen-10);
	t_TTA->SetMarkerColor(kGreen-10);
        t_TTA->SetLineColor(kGreen-10);
//	t_TTA->Scale(lumi);

	TFile* f_ST=TFile::Open("./hist_ST.root");
        TH2D* th2_ST=(TH2D*)f_ST->Get("hist_bkg");
//        TH1D* t_ST=unroll(th2_ST, mjj_bins, mlla_bins, 4,4);
        TH1D* t_ST=unroll(th2_ST, mjj_bins, detajj_bins, 3,3,"ST");
	t_ST->SetFillColor(kGreen-4);
	t_ST->SetMarkerColor(kGreen-4);
        t_ST->SetLineColor(kGreen-4);
//	t_ST->Scale(lumi);
	for(Int_t i=1;i<=t_ST->GetNbinsX();i++){ t_ST->GetXaxis()->SetBinLabel(i,name[i-1]);}

	TFile* f_plj=TFile::Open("./hist_plj_muendcap.root");
        TH2D* th2_plj=(TH2D*)f_plj->Get("hist_bkg");
        TH1D* t_plj=unroll(th2_plj, mjj_bins, detajj_bins, 3,3,"plj");
	t_plj->SetFillColor(kOrange - 2);
	t_plj->SetMarkerColor(kOrange - 2);
        t_plj->SetLineColor(kOrange - 2);

	THStack* hs = new THStack("hs", "");
	hs->Add(t_ST);
	hs->Add(t_TTA);
	hs->Add(t_VV);
	hs->Add(t_WA);
	hs->Add(t_plj);
	hs->Add(t_ZA);
	hs->Add(t_ZA_sig);
	hs->Add(t_ZA_sigout);

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
        double max=hs->GetMaximum();
        hs->SetMaximum(max*1.5);
	hs->Draw("HIST");
	hs->GetYaxis()->SetTitleOffset(0.8);
	hs->GetYaxis()->SetTitle("Events /bin");
	TLegend* leg = new TLegend(0.62, 0.45, 0.83, 0.9);
	leg->SetTextSize(0.04);
        leg->SetMargin(0.4);
	leg->AddEntry(t_ZA_sig,Form("EWK in fid.[%.2f]",t_ZA_sig->GetSum()) );
	leg->AddEntry(t_ZA_sigout, Form("EWK out fid. [%.2f]",t_ZA_sigout->GetSum()));
	leg->AddEntry(t_ZA, Form("ZA [%.2f]",t_ZA->GetSum()));
//	leg->AddEntry(t_ZA, Form("ZA [%.2f]",t_ZA->Integral(0,9)));
	leg->AddEntry(t_plj, Form("non-prompt [%.2f]",t_plj->GetSum() ));
	leg->AddEntry(t_WA, Form("WA [%.2f]",t_WA->GetSum()  )  );
	leg->AddEntry(t_VV, Form("VV [%.2f]", t_VV->GetSum() ) );
	leg->AddEntry(t_TTA, Form("TTA [%.2f]",t_TTA->GetSum()) );
	leg->AddEntry(t_ST, Form("ST  [%.2f]",t_ST->GetSum() ) );
	leg->Draw();
	
	cmsLumi(0);

	fout->cd();
	hs->Write();
	fout->Close();

	c1->SaveAs("aa.png");
	c1->SaveAs("aa.pdf");
	c1->SaveAs("aa.C");
        return 0;
  
}
