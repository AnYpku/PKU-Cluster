#include <string>
#include <iostream>
#include "TFile.h"
#include "TH1.h"
#include "RooRealVar.h"
#include "RooAddPdf.h"
#include <TLatex.h>
#include <TLegend.h>
#include <ostream>
#include <fstream>


using namespace RooFit;
TString dir =  "../all/roofit/txt/";
TString dir1 = "../all/root/";
TString dir2 = "../all/roofit/eps/";
void fit(float lowpt, float highpt, float lowchiso, float highchiso,TString tag,TString channel){

ofstream file3("../all/roofit/info_roofit_"+channel+tag+".txt",ios::app);
TFile* fdata = TFile::Open(dir1 + "histo_Pdata"+tag+"_"+channel+".root");
//TFile* ftrue = TFile::Open(dir1 + "ZA.root");

	TH1F* hdata_ = (TH1F*)fdata->Get(Form("h11_pt%0.f_%0.f",lowpt,highpt));
	TH1F* hfake_ = (TH1F*)fdata->Get(Form("h12_pt%0.f_%0.f_chiso%0.f_%0.f",lowpt,highpt,lowchiso,highchiso));
	TH1F* htrue_ = (TH1F*)fdata->Get(Form("h13_pt%0.f_%0.f",lowpt,highpt));
	TH1F* hist_ = (TH1F*) fdata->Get(Form("hfake_pt%0.f_%0.f",lowpt,highpt));
	TH1F* hist1_ = (TH1F*)fdata->Get(Form("htrue_pt%0.f_%0.f",lowpt,highpt));

	Int_t nBins = 8;
	Int_t sieie_bin=2;
	Double_t bins[9];
	for (Int_t i=0;i<9;i++){
		if(channel.Contains("barrel"))bins[i] = 0.00515 + 0.0025*i;
		else if(channel.Contains("endcap"))bins[i] = 0.0172 + 0.005*i;
	}
        double sieie_low,sieie_high,sieie_medium;
	if(channel.Contains("barrel")){
               sieie_low=0.00515;sieie_high=0.02015;
	       sieie_medium=0.01015;
	}
	else if(channel.Contains("endcap")){
               sieie_low=0.0172;sieie_high=0.0572;
	       sieie_medium=0.0272;
	}

	TH1* hdata = hdata_->Rebin(nBins, "hdata", bins);
	TH1* htrue = htrue_->Rebin(nBins, "htrue", bins);
	TH1* hfake = hfake_->Rebin(nBins, "hfake_data", bins);
	TH1* hist = hist_->Rebin(nBins, "fake mc truth", bins);
	TH1* hist1 = hist1_->Rebin(nBins, "true mc truth", bins);
	for (Int_t i=0; i<9; i++){
		cout<<hdata->GetBinContent(i)<<endl;
		cout<<htrue->GetBinContent(i)<<endl;
		cout<<hfake->GetBinContent(i)<<endl;
	}

	for (Int_t i=0; i<nBins; i++){
		if (hdata->GetBinContent(i+1)<=0) hdata->SetBinContent(i+1,0.000000);
		if (htrue->GetBinContent(i+1)<=0) htrue->SetBinContent(i+1,0.000000);
		if (hfake->GetBinContent(i+1)<=0) hfake->SetBinContent(i+1,0.000000);
	}

	Double_t nData = hdata->GetSumOfWeights();
	RooRealVar sieie("sieie", "sieie", sieie_low, sieie_high);
	

	RooDataHist data_hist("datahist", "datahist", sieie, hdata);
	RooDataHist true_hist("truehist", "truehist", sieie, htrue);
	RooDataHist fake_hist("fakehist", "fakehist", sieie, hfake);

	RooHistPdf true_pdf("truepdf", "truepdf", sieie, true_hist);
	RooHistPdf fake_pdf("fakepdf", "fakepdf", sieie, fake_hist);

	RooRealVar nTrue("true number", "true number", 0.5*nData, 0, nData);
	RooRealVar nFake("fake number", "fake number", 0.5*nData, 0, nData);

	RooExtendPdf etrue_pdf("ntrue", "ntrue", true_pdf, nTrue);
	RooExtendPdf efake_pdf("nfake", "nfake", fake_pdf, nFake);

	RooAddPdf fullpdf("full_pdf", "true_plus_fake", RooArgList(etrue_pdf,efake_pdf));

	fullpdf.fitTo(data_hist, SumW2Error(kFALSE), Extended(kTRUE));
	RooChi2Var chi2("chi2", "chi2", fullpdf, data_hist);
	Double_t chi2ToNDF = chi2.getVal() / (nBins - 2);

	RooPlot* xframe = sieie.frame(Title(channel + Form(" region, %0.f GeV < photon PT < %0.f GeV,%0.f <chiso<%0.f ",lowpt, highpt,lowchiso,highchiso)), Bins(nBins));
	data_hist.plotOn(xframe);
	fullpdf.plotOn(xframe, Name("sum"), LineColor(kRed));
	fullpdf.plotOn(xframe, Components("ntrue"), Name("true"),LineColor(kGreen), LineStyle(9));
	fullpdf.plotOn(xframe, Components("nfake"), Name("fake"),LineColor(kBlue), LineStyle(9));


	TCanvas *c1 = new TCanvas("c1", "c1", 500, 400);
	xframe->GetXaxis()->SetTitle("#sigma_{i#etai#eta}");
	xframe->GetYaxis()->SetTitleOffset(1.4);
	xframe->Draw();


	hdata->SetLineColor(kRed);
	hdata->SetLineWidth(3);
	hfake->SetLineColor(kBlue);
	hfake->SetLineStyle(5);
	hfake->SetLineWidth(3);
	htrue->SetLineColor(kGreen);
	htrue->SetLineStyle(5);
	htrue->SetLineWidth(3);
	hist->SetLineColor(kOrange);
	hist->SetLineStyle(2);
	hist->SetLineWidth(3);
        hist->Draw("same hist"); 
	hist1->SetLineColor(kMagenta);
	hist1->SetLineStyle(2);
	hist1->SetLineWidth(3);
        hist1->Draw("same hist"); 
	TLegend *leg = new TLegend(0.5, 0.6, 0.9, 0.9, NULL, "brNDC");
	leg->SetTextSize(0.05);
	leg->SetFillColor(10);
	leg->AddEntry(hdata, "Fit result", "L");
	leg->AddEntry(htrue, "Ture photons", "L");
	leg->AddEntry(hfake, "Fake photons", "L");
	leg->AddEntry(hist, "mc truth of fake #gamma", "L");
	leg->AddEntry(hist1, "mc truth of true #gamma", "L");
	leg->Draw("same");


	TString strChi = "#chi^{2}/ndf=";
	float chiFloat = (100 * chi2ToNDF);
	int chiInt = chiFloat;
	strChi += (chiInt / 100);
	strChi += ".";
	strChi += (chiInt % 100);
	TLatex *textChi2 = new TLatex(0.7, 0.4, strChi);
	textChi2->SetNDC();
	textChi2->SetTextSize(0.05);
	textChi2->SetLineWidth(1);
	textChi2->Draw();


	

	Double_t nDataInWindowErr = 0.;
	Double_t nDataInWindow_1 = hdata->Integral(1,1);
        Double_t nDataInWindow_2 = hdata->Integral(2,2);
        Double_t nDataInWindow_3 = hdata->Integral(3,3);
        Double_t nDataInWindow_4 = hdata->Integral(4,4);
        Double_t nDataInWindow_5 = hdata->Integral(5,5);
        Double_t nDataInWindow_6 = hdata->Integral(6,6);
	Double_t nDataInWindow_7 = hdata->Integral(7,7);
	Double_t nDataInWindow = hdata->IntegralAndError(1,sieie_bin,nDataInWindowErr);
	Double_t nDatatotal = hdata->Integral();
	Double_t nTrue_fit = nTrue.getVal();
	Double_t nTrue_fitErr = nTrue.getError();
	Double_t nFake_fit = nFake.getVal();
	Double_t nFake_fitErr = nFake.getError();

	sieie.setRange("window",sieie_low,sieie_medium);
	RooRealVar *fracFake = (RooRealVar*)efake_pdf.createIntegral(sieie,sieie,"window");
	Double_t nFake_inwindow = nFake_fit*fracFake->getVal();
	Double_t nFake_inwindowErr = sqrt(nFake_fitErr*nFake_fitErr*fracFake->getVal()*fracFake->getVal()+
										nFake_fit*nFake_fit*fracFake->getError()*fracFake->getError());
	RooRealVar *fracTrue =(RooRealVar*)etrue_pdf.createIntegral(sieie,sieie,"window");
	Double_t nTrue_inwindow = nTrue_fit*fracTrue->getVal();
	Double_t nTrue_inwindowErr = sqrt(nTrue_fitErr*nTrue_fitErr*fracTrue->getVal()*fracTrue->getVal()+
										nTrue_fit*nTrue_fit*fracTrue->getError()*fracTrue->getError());

	Double_t fakerate = nFake_inwindow/nDataInWindow;
	Double_t fakerateErr = sqrt(nFake_inwindowErr*nFake_inwindowErr/(nDataInWindow*nDataInWindow)
								+ nFake_inwindow*nFake_inwindow*nDataInWindowErr*nDataInWindowErr/(nDataInWindow
									*nDataInWindow*nDataInWindow*nDataInWindow));
	ofstream myfile(dir + channel+tag+TString("_fakerate_") + Form("photon_pt%0.f_%0.f_chiso%0.f-%0.f.txt", lowpt, highpt,lowchiso,highchiso),ios::out);
	ofstream file(dir +channel+tag+ TString("_TrueNumber_") + Form("pt%0.f-%0.f_chiso%0.f-%0.f.txt", lowpt, highpt,lowchiso,highchiso),ios::out);
	ofstream file1(dir + channel+tag+TString("_FakeNumber_") + Form("pt%0.f-%0.f_chiso%0.f-%0.f.txt", lowpt, highpt,lowchiso,highchiso),ios::out);

	myfile << "data in window = " << nDataInWindow << "+-" << nDataInWindowErr <<" "<<nDataInWindow_1<<" "<<nDataInWindow_2<<" "<<nDataInWindow_3<<" "<<nDataInWindow_4<<" "<<nDataInWindow_5<<" "<<nDataInWindow_6<<" "<<nDataInWindow_7<<std::endl;
	myfile << "nDatatotal = " << nDatatotal << std::endl;
	myfile << "fake number = "<< nFake_fit << "+-" <<nFake_fitErr <<std::endl;
	myfile << "true number = "<< nTrue_fit << "+-" << nTrue_fitErr <<std::endl;
	myfile << "fake in window = "<< nFake_inwindow << "+-" <<nFake_inwindowErr <<std::endl;
	myfile << "true in window = "<< nTrue_inwindow << "+-" <<nTrue_inwindowErr <<std::endl;
	myfile << "fakerate = " << fakerate << "+-" <<fakerateErr <<std::endl; 
	myfile << "chi2ToNDF = " << chi2ToNDF <<std::endl;
    file<<nTrue_inwindow<<"\t"<<nTrue_inwindowErr<<endl;
    file1<<nFake_inwindow<<"\t"<<nFake_inwindowErr<<"\t"<<fakerate<<"\t"<<fakerateErr<<endl;
    file3<<Form("%0.f <pt<%0.f\t%0.f<chiso<%0.f",lowpt,highpt,lowchiso,highchiso)<<"\t"<<fakerate<<"\t"<<fakerateErr<<endl;
	TString strFR = "FR = (";
        float FRFloat = (1000 * fakerate);
        int FRInt = FRFloat;
        strFR += (FRInt/10);
        strFR += ".";
        strFR += (FRInt%10);
        strFR += "+-";
        float FRErrFloat = (1000 * fakerateErr);
        int FRErrInt = FRErrFloat;
        strFR += (FRErrInt/10);
        strFR += ".";
        strFR += (FRErrInt%10);
        strFR += ")%";
        TLatex* textFR = new TLatex(0.7,0.3,strFR);
        textFR->SetNDC();
        textFR->SetTextSize(0.05);
        textFR->SetLineWidth(1);
        textFR->Draw();

    char buffer[256];
	sprintf(buffer, channel+tag+"_pt%0.f-%0.f_chiso%0.f-%0.f",lowpt,highpt,lowchiso,highchiso);
	c1->Print(dir2 + buffer);
    fdata->Close();
//    ftrue->Close();
    delete c1;
}
