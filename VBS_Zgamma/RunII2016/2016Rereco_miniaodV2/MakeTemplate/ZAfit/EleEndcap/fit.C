#include <string>
#include <iostream>
#include "TFile.h"
#include "TH1.h"
#include "RooRealVar.h"
#include "RooAddPdf.h"
using namespace RooFit;
ofstream file3("info_fit.txt");
TFile* fdata = TFile::Open("/afs/cern.ch/user/y/yian/work/PKU-Cluster/RunII2016/analysis_code/MakeTemplate/ZAJetfakephoton/EleEndcap/root/Data_template-cutlep-outDEle16.root");
TFile* ftrue = TFile::Open("/afs/cern.ch/user/y/yian/work/PKU-Cluster/RunII2016/analysis_code/MakeTemplate/ZAJetfakephoton/EleEndcap/root/True_template-cutlep-outZA.root");
//TFile* ftrue = TFile::Open("/afs/cern.ch/user/y/yian/work/PKU-Cluster/RunII2016/analysis_code/MakeTemplate/ZAJetfakephoton/EleEndcap/root/True_template-cutlep-outZA-EWK.root");
TFile* ffake = TFile::Open("/afs/cern.ch/user/y/yian/work/PKU-Cluster/RunII2016/analysis_code/MakeTemplate/ZAJetfakephoton/EleEndcap/root/Fake_template-cutlep-outDEle16.root");
TString name;
void fit(float lowpt, float highpt){
//TString b="chiso5-12_";
        TString filename = ftrue->GetName();
        if(filename.Contains("EWK")) name = "EWK";
        else if(filename.Contains("TTA")) name = "TTA";
        else name = "ZA";

	TH1F* hdata_ = (TH1F*)fdata->Get(Form("h3_pt%0.f-%0.f",lowpt,highpt));
	TH1F* hfake_ = (TH1F*)ffake->Get(Form("h2_pt%0.f-%0.f",lowpt,highpt));
	TH1F* htrue_ = (TH1F*)ftrue->Get(Form("h1_pt%0.f-%0.f",lowpt,highpt));
	TH1F* hzaf_  = (TH1F*)ftrue->Get(Form("h4_pt%0.f_%0.f",lowpt,highpt));
	hfake_->Add(hzaf_,-35.866);

/*	Int_t nBins = 9;
	Double_t bins[10];
	for (Int_t i=0;i<10;i++){
		bins[i] = 0.004 + 0.002*i;
	}*/
/*        Int_t nBins = 6*2;
        Double_t bins[13];
        for (Int_t i=0;i<13;i++){
                bins[i] = 0.01401 + 0.008/2*i;
		cout<<bins[i]<<",";
        }*/
//	Double_t bins[12]={0.01401,0.01801,0.02201,0.02601,0.03001,0.03401,0.03801,0.04201,0.04601,0.05001,0.05401,0.05801,0.06201};
	Int_t nBins = 11;
	Double_t bins[12]={0.01401,0.01801,0.02201,0.03001,0.03401,0.03801,0.04201,0.04601,0.05001,0.05401,0.05801,0.06201};
        Int_t sieie_bin=3;        

	TH1* hdata = hdata_->Rebin(nBins, "hdata", bins);
	TH1* htrue = htrue_->Rebin(nBins, "htrue", bins);
	TH1* hfake = hfake_->Rebin(nBins, "hfake_data", bins);
	for (Int_t i=0; i<10; i++){
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
//	RooRealVar sieie("sieie", "sieie", 0.004, 0.02);
        RooRealVar sieie("sieie", "sieie", 0.01401, 0.06201);	

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

	RooPlot* xframe = sieie.frame(Title(Form("Electron Endcap, %0.f GeV < photon PT < %0.f GeV ",lowpt, highpt)), Bins(nBins));
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

//	sieie.setRange("window",0.0052,0.0102);
        sieie.setRange("window",0.01401,0.03001);
	
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
	ofstream myfile1(TString("./txt/fakerate_") + name + Form("pt%0.f_%0.f.txt", lowpt, highpt),ios::out);
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
    file3<<Form("%0.f<pt<%0.f ",lowpt,highpt)<<"\t"<<fakerate<<"\t"<<fakerateErr<<endl;
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
