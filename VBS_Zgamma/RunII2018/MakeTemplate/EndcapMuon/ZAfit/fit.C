#include <string>
#include <iostream>
#include "TFile.h"
#include "TH1.h"
#include "RooRealVar.h"
#include "RooAddPdf.h"
using namespace RooFit;
ofstream file3("info_fit.txt");
TString name;
TFile* fdata = TFile::Open("../root/Data_template-DMuon.root");
//TFile* ftrue = TFile::Open("../root/True_template-cutlep-outTTA.root");
TFile* ftrue = TFile::Open("../root/True_template-ZA.root");
//TFile* ftrue = TFile::Open("../root/True_template-ZA-EWK.root");
//TFile* ftrue = TFile::Open("../root/True_template-TTA.root");
//TFile* ftrue = TFile::Open("/Users/andy/tmp/True_template-cutLEP-outZA.root");
TFile* ffake = TFile::Open("../root/Fake_template-DMuon.root");
void fit(float lowpt, float highpt){
//TString b="chiso5-12_";
        TString filename = ftrue->GetName();
        if(filename.Contains("EWK")) name = "EWK";
        else if(filename.Contains("TTA")) name = "TTA";
        else name = "ZA1";
	TH1F* hdata_ = (TH1F*)fdata->Get(Form("h3_pt%0.f_%0.f",lowpt,highpt));
	TH1F* hfake_ = (TH1F*)ffake->Get(Form("h2_pt%0.f_%0.f",lowpt,highpt));
	TH1F* htrue_ = (TH1F*)ftrue->Get(Form("h1_pt%0.f_%0.f",lowpt,highpt));
//	TH1F* htrue_ = (TH1F*)ftrue->Get(Form("h1_pt%0.f-%0.f",lowpt,highpt));
	TH1F* hzaf_  = (TH1F*)ftrue->Get(Form("h4_pt%0.f_%0.f",lowpt,highpt));
	hfake_->Add(hzaf_,-59.97);
	Int_t nBins = 6;
	Int_t sieie_bin=2;
	Double_t bins[7]={0.0172,0.0222,0.0272,0.0322,0.0372,0.0472,0.0572};
//	Double_t bins[10]={0.004,0.006,0.008,0.01015,0.012,0.014,0.016,0.018,0.02,0.022};
//	Int_t nBins = 4;
//    Int_t sieie_bin=1;
//    Double_t bins[5];
//	for (Int_t i=0;i<(nBins+1);i++){
//		bins[i] = 0.0172 + 0.01*i;
//	}

	TH1* hdata = hdata_->Rebin(nBins, "hdata", bins);
	TH1* htrue = htrue_->Rebin(nBins, "htrue", bins);
	TH1* hfake = hfake_->Rebin(nBins, "hfake_data", bins);
	for (Int_t i=0; i<(nBins+1); i++){
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
	RooRealVar sieie("sieie", "sieie", 0.0172, 0.0572);
	

	RooDataHist data_hist("datahist", "datahist", sieie, hdata);
	RooDataHist true_hist("truehist", "truehist", sieie, htrue);
	RooDataHist fake_hist("fakehist", "fakehist", sieie, hfake);

	RooHistPdf true_pdf("truepdf", "truepdf", sieie, true_hist);
	RooHistPdf fake_pdf("fakepdf", "fakepdf", sieie, fake_hist);

//	RooRealVar nFake("fake number", "fake number",1600,0, nData);
//	RooRealVar nTrue("true number", "true number",800,0, nData);
	RooRealVar nFake("fake number", "fake number",0, nData);
	RooRealVar nTrue("true number", "true number",0, nData);

	RooExtendPdf etrue_pdf("ntrue", "ntrue", true_pdf, nTrue);
	RooExtendPdf efake_pdf("nfake", "nfake", fake_pdf, nFake);

	RooAddPdf fullpdf("full_pdf", "true_plus_fake", RooArgList(etrue_pdf,efake_pdf));

	fullpdf.fitTo(data_hist, SumW2Error(kFALSE), Extended(kTRUE));
	RooChi2Var chi2("chi2", "chi2", fullpdf, data_hist);
	Double_t chi2ToNDF = chi2.getVal() / (nBins - 2);

	RooPlot* xframe = sieie.frame(Title(Form("Barrel region, %0.f GeV < photon PT < %0.f GeV ",lowpt, highpt)), Bins(nBins));
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
	TLegend *leg = new TLegend(0.7, 0.8, 0.88, 0.88, NULL, "brNDC");
	leg->SetFillColor(10);
	leg->AddEntry(hdata, "Fit result", "L");
	leg->AddEntry(htrue, "Ture photons", "L");
	leg->AddEntry(hfake, "Fake photons", "L");
	leg->Draw("same");


	TString strChi = "#chi^{2}/ndf=";
	float chiFloat = (100 * chi2ToNDF);
	int chiInt = chiFloat;
	strChi += (chiInt / 100);
	strChi += ".";
	strChi += (chiInt % 100);
	TLatex *textChi2 = new TLatex(0.7, 0.75, strChi);
	textChi2->SetNDC();
	textChi2->SetTextSize(0.03);
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

	sieie.setRange("window",0.0172,0.0272);
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
	ofstream myfile(TString("./txt/fakerate_") + Form("photon_pt%0.f_%0.f.txt", lowpt, highpt),ios::out);
	ofstream myfile1(TString("./txt/fakerate_") +name+ Form("pt%0.f_%0.f.txt", lowpt, highpt),ios::out);
	ofstream file(TString("./txt/TrueNumber_") + Form("pt%0.f-%0.f.txt", lowpt, highpt),ios::out);
	ofstream file1(TString("./txt/FakeNumber_") + Form("pt%0.f-%0.f.txt", lowpt, highpt),ios::out);

	myfile << "data in window = " << nDataInWindow << "+-" << nDataInWindowErr <<" "<<nDataInWindow_1<<" "<<nDataInWindow_2<<" "<<nDataInWindow_3<<" "<<nDataInWindow_4<<" "<<nDataInWindow_5<<" "<<nDataInWindow_6<<" "<<nDataInWindow_7<<std::endl;
	myfile << "nDatatotal = " << nDatatotal << std::endl;
	myfile << "fake number = "<< nFake_fit << "+-" <<nFake_fitErr <<std::endl;
	myfile << "true number = "<< nTrue_fit << "+-" << nTrue_fitErr <<std::endl;
	myfile << "fake in window = "<< nFake_inwindow << "+-" <<nFake_inwindowErr <<std::endl;
	myfile << "true in window = "<< nTrue_inwindow << "+-" <<nTrue_inwindowErr <<std::endl;
	myfile << "fakerate = " << fakerate << "+-" <<fakerateErr <<std::endl; 
	myfile1 << fakerate <<std::endl; 
	myfile << "chi2ToNDF = " << chi2ToNDF <<std::endl;
    file<<nTrue_fit<<"\t"<<nTrue_fitErr<<endl;
    file1<<nFake_fit<<"\t"<<nFake_fitErr<<endl;
    file3<<Form("%0.f <pt<%0.f ",lowpt,highpt)<<"\t"<<fakerate<<"\t"<<fakerateErr<<"\t"<<chi2ToNDF<<endl;
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
        TLatex* textFR = new TLatex(0.67,0.7,strFR);
        textFR->SetNDC();
        textFR->SetTextSize(0.03);
        textFR->SetLineWidth(1);
        textFR->Draw();

    char buffer[256];
	sprintf(buffer, "./eps/pt%0.f-%0.f.eps",lowpt,highpt);
	c1->Print(buffer);

}
