#include <string>
#include <iostream>
#include "TFile.h"
#include "TH1.h"
#include "RooRealVar.h"
#include "RooAddPdf.h"
using namespace RooFit;
TFile* fdataT = TFile::Open("/data/pku/home/anying/cms/CMSSW_8_0_26_patch2/analysis_code/MakeTemplate/WAfit/chisoFit/rootfiles/dataTrue_template_chiso.root");
TFile* fdataF = TFile::Open("/data/pku/home/anying/cms/CMSSW_8_0_26_patch2/analysis_code/MakeTemplate/WAfit/chisoFit/rootfiles/dataFake_template_chiso.root");
TFile* fmcT = TFile::Open("/data/pku/home/anying/cms/CMSSW_8_0_26_patch2/analysis_code/MakeTemplate/WAfit/chisoFit/rootfiles/mcTrue_template_chiso.root");
TFile* fmcF = TFile::Open("/data/pku/home/anying/cms/CMSSW_8_0_26_patch2/analysis_code/MakeTemplate/WAfit/chisoFit/rootfiles/mcFake_template_chiso.root");
TFile* fdata = TFile::Open("/data/pku/home/anying/cms/CMSSW_8_0_26_patch2/analysis_code/MakeTemplate/WAfit/chisoFit/rootfiles/waData_template_chiso.root");
TFile* fmc = TFile::Open("/data/pku/home/anying/cms/CMSSW_8_0_26_patch2/analysis_code/MakeTemplate/WAfit/chisoFit/rootfiles/waMC_template_chiso.root");

TString dir = "./fitresult_za/";
//TString dir = "./fitresult/";
ofstream file3( dir + "info_fit.txt");
void fit(float lowpt, float highpt){
//TString b="chiso5-12_";
TFile *f0 = new TFile(Form("/data/pku/home/anying/cms/CMSSW_8_0_26_patch2/analysis_code/MakeTemplate/WAfit/chisoFit/rootfiles/fdata_%0.f_%0.f.root",lowpt,highpt));
        TTree *tree_datawa = (TTree*)f0->Get("tree_datawa");

        TH1F* hdata_ = (TH1F*)fdata->Get(Form("hdatawa_pt%0.f-%0.f",lowpt,highpt));
        TH1F* hsieie = (TH1F*)fdata->Get(Form("hsieie_pt%0.f-%0.f",lowpt,highpt));
//        TH1F* hfake_ = (TH1F*)fdata->Get(Form("hwaFs_pt%0.f-%0.f",lowpt,highpt)); 
        TH1F* hfake_ = (TH1F*)fdataF->Get(Form("h3_pt%0.f_%0.f",lowpt,highpt));
        TH1F* htrue_ = (TH1F*)fdataT->Get(Form("h4_pt%0.f_%0.f",lowpt,highpt));
//        TH1F* htrue_ = (TH1F*)fmc->Get(Form("hmcwaT_pt%0.f-%0.f",lowpt,highpt));
        TH1F* hmt_ = (TH1F*)fmcT->Get(Form("h2_pt%0.f_%0.f",lowpt,highpt));
        TH1F* hmf_ = (TH1F*)fmcF->Get(Form("h1_pt%0.f_%0.f",lowpt,highpt));
        TH1F* hmcFc = (TH1F*)fmc->Get(Form("hmcFc_pt%0.f-%0.f",lowpt,highpt));

        htrue_ -> Add(hmt_,-1);
        hfake_ -> Add(hmf_,-1);
//        hfake_ -> Add(hmcFc,-1);

        Int_t nBins = 10;
        Double_t bins[11];
        for (Int_t i=0;i<11;i++){
                bins[i] = 0.00 + 0.5*i;
                cout<<"bins["<<i<<"] = "<<bins[i]<<endl;
	}

	TH1* hdata = hdata_->Rebin(nBins, "hdata", bins);
	TH1* htrue = htrue_->Rebin(nBins, "htrue", bins);
	TH1* hfake = hfake_->Rebin(nBins, "hfake_data", bins);
	for (Int_t i=0; i<nBins; i++){
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
	RooRealVar chiso("chiso", "chiso", 0.001,5 );
	

	RooDataHist data_hist("datahist", "datahist", chiso, hdata);
	RooDataHist true_hist("truehist", "truehist", chiso, htrue);
	RooDataHist fake_hist("fakehist", "fakehist", chiso, hfake);

	RooHistPdf true_pdf("truepdf", "truepdf", chiso, true_hist);
	RooHistPdf fake_pdf("fakepdf", "fakepdf", chiso, fake_hist);

	RooRealVar nTrue("true number", "true number", 0.5*nData, 0, nData);
	RooRealVar nFake("fake number", "fake number", 0.5*nData, 0, nData);

	RooExtendPdf etrue_pdf("ntrue", "ntrue", true_pdf, nTrue);
	RooExtendPdf efake_pdf("nfake", "nfake", fake_pdf, nFake);

	RooAddPdf fullpdf("full_pdf", "true_plus_fake", RooArgList(etrue_pdf,efake_pdf));


	/*RooFitResult *fitres = */fullpdf.fitTo(data_hist,SumW2Error(kFALSE), Extended(kTRUE));
	RooChi2Var chi2("chi2", "chi2", fullpdf, data_hist);
	Double_t chi2ToNDF = chi2.getVal() / (nBins - 2);

	RooPlot* xframe = chiso.frame(Title(Form("Barrel region, %0.f GeV < photon PT < %0.f GeV ",lowpt, highpt)), Bins(nBins));
	data_hist.plotOn(xframe,MarkerColor(kBlack), MarkerSize(0.8),DataError(RooAbsData::SumW2));
	fullpdf.plotOn(xframe, Name("sum"), LineColor(kRed));
	fullpdf.plotOn(xframe, Components("ntrue"), Name("true"),LineColor(kGreen), LineStyle(9));
	fullpdf.plotOn(xframe, Components("nfake"), Name("fake"),LineColor(kBlue), LineStyle(9));

        //Int_t nParsToFit = (fitres->floatParsFinal()).getSize();
	//chi2ToNDF = xframe->chiSquare(nParsToFit);


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
	Double_t nDataInWindow = hdata->IntegralAndError(1,1,nDataInWindowErr);
	Double_t nDatatotal = hdata->Integral();
	Double_t nTrue_fit = nTrue.getVal();
	Double_t nTrue_fitErr = nTrue.getError();
	Double_t nFake_fit = nFake.getVal();
	Double_t nFake_fitErr = nFake.getError();

	chiso.setRange("window",0.,0.5);
//	sieie.setRange("window",0.005,0.02);
	RooRealVar *fracFake = (RooRealVar*)efake_pdf.createIntegral(chiso,chiso,"window");
	Double_t nFake_inwindow = nFake_fit*fracFake->getVal();
	Double_t nFake_inwindowErr = sqrt(nFake_fitErr*nFake_fitErr*fracFake->getVal()*fracFake->getVal()+
										nFake_fit*nFake_fit*fracFake->getError()*fracFake->getError());
	RooRealVar *fracTrue =(RooRealVar*)etrue_pdf.createIntegral(chiso,chiso,"window");
	Double_t nTrue_inwindow = nTrue_fit*fracTrue->getVal();
	Double_t nTrue_inwindowErr = sqrt(nTrue_fitErr*nTrue_fitErr*fracTrue->getVal()*fracTrue->getVal()+
										nTrue_fit*nTrue_fit*fracTrue->getError()*fracTrue->getError());

	Double_t fakerate = nFake_inwindow/nDataInWindow;
	Double_t fakerateErr = sqrt(nFake_inwindowErr*nFake_inwindowErr/(nDataInWindow*nDataInWindow)
								+ nFake_inwindow*nFake_inwindow*nDataInWindowErr*nDataInWindowErr/(nDataInWindow
									*nDataInWindow*nDataInWindow*nDataInWindow));
	ofstream myfile(dir +"txt/" + Form("fakerate_photon_pt%0.f_%0.f.txt", lowpt, highpt),ios::out);
	ofstream myfile1(dir + "txt/"+ Form("fakerate_pt%0.f_%0.f.txt", lowpt, highpt),ios::out);
	ofstream file(dir + "txt/"  + Form("TrueNumber_pt%0.f-%0.f.txt", lowpt, highpt),ios::out);
	ofstream file1(dir + "txt/" + Form("FakeNumber_pt%0.f-%0.f.txt", lowpt, highpt),ios::out);

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
    file3<<Form("%0.f <pt<%0.f ",lowpt,highpt)<<"\t"<<fixed<<setprecision(2)<<fakerate<<"\t"<<fixed<<setprecision(4)<<fakerateErr<<endl;
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
	sprintf(buffer, dir + "eps/pt%0.f-%0.f.eps",lowpt,highpt);
	c1->Print(buffer);

}
