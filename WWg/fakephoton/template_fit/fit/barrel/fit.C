#include <string>
#include <iostream>
#include "TFile.h"
#include "TH1.h"
#include "RooRealVar.h"
#include "RooAddPdf.h"
using namespace RooFit;
TH1D* getHist(float lowpt, float highpt,TString style,vector<TFile*>file){
        int num=file.size();
        TH1D*h[num];TH1D*h1;
	cout<<num<<endl;
	for(int i=0;i<file.size();i++){
		h[i]=(TH1D*)file[i]->Get(style+Form("_pt%0.f_%0.f",lowpt,highpt));
                cout<<file[i]->GetName()<<" "<<h[i]->GetName()<<" "<<h[i]->GetSum()<<endl;
	}
        h1=(TH1D*)h[0]->Clone();
	for(int i=1;i<num;i++){
           h1->Add(h[i],1);
	}
        cout<<h1->GetSum()<<endl;
        return h1;
}
void fit(float lowpt, float highpt, Bool_t isBarrel,TString channel){
	TString c;
        if(isBarrel) c="barrel_";
	else c="endcap_";
        vector<TFile*>fdata;
        vector<TFile*>ftrue;
        if(channel!="emu")ftrue.push_back(TFile::Open("../../barrel/hist_"+c+channel+"_outZGJets_f18.root"));
        else ftrue.push_back(TFile::Open("../../barrel/hist_"+c+channel+"_outTTGJets_f18.root"));
        vector<TString> data={"MuonEG","DMuon","DEle"};
	for(int i=0;i<data.size();i++){
		if(data[i].Contains("DEle") && channel=="mm") continue;
		if(data[i].Contains("DMuon") && channel=="ee") continue;
		fdata.push_back(TFile::Open("../../barrel/hist_"+c+channel+"_"+data[i]+"_f18.root"));
                cout<<"../barrel/hist_"+c+channel+"_"+data[i]+"_f18.root"<<endl;
	}
	TH1D* hdata_ = getHist(lowpt,highpt,"data",fdata);  
	TH1D* hfake_ = getHist(lowpt,highpt,"fake",fdata);
	TH1D* htrue_ = getHist(lowpt,highpt,"true",ftrue);
	TH1D* hzaf_  = getHist(lowpt,highpt,"fake",ftrue);
	hfake_->Add(hzaf_,-59.7);

	fstream file3("info_fit_"+c+channel+".txt",ios::app);
	TString filename = ftrue[0]->GetName();
	TString name;
        if(filename.Contains("EWK")) name = "EWK"; 
        else name = "ZA";

	Int_t nBins = 9;//9
	Int_t sieie_bin=3;//3
	Double_t bins[10];
	for (Int_t i=0;i<(nBins+1);i++){
		bins[i] = 0.00515 + 0.0025*2/3*i;
	}

	TH1* hdata = hdata_->Rebin(nBins, "hdata", bins);
	TH1* htrue = htrue_->Rebin(nBins, "htrue", bins);
	TH1* hfake = hfake_->Rebin(nBins, "hfake_data", bins);
	for (Int_t i=0; i<(nBins+1); i++){
		cout<<hdata->GetBinContent(i)<<endl;
//		cout<<htrue->GetBinContent(i)<<endl;
//		cout<<hfake->GetBinContent(i)<<endl;
	}

	for (Int_t i=0; i<nBins; i++){
		if (hdata->GetBinContent(i+1)<=0) hdata->SetBinContent(i+1,0.000000);
		if (htrue->GetBinContent(i+1)<=0) htrue->SetBinContent(i+1,0.000000);
		if (hfake->GetBinContent(i+1)<=0) hfake->SetBinContent(i+1,0.000000);
	}

	Double_t nData = hdata->GetSumOfWeights();
	RooRealVar sieie("sieie", "sieie", 0.00515, 0.02015);
	

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
	TLegend *leg = new TLegend(0.55, 0.6, 0.9, 0.9, NULL, "brNDC");
	leg->SetFillColor(10);
	leg->SetTextSize(0.05);
	leg->AddEntry(hdata, "Fit result", "L");
	leg->AddEntry(htrue, "True photons", "L");
	leg->AddEntry(hfake, "Fake photons", "L");
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

	sieie.setRange("window",0.00515,0.01015);
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
	ofstream myfile(TString("./txt/fakerate_") + channel+Form("_photon_pt%0.f_%0.f.txt", lowpt, highpt),ios::out);
	ofstream myfile1(TString("./txt/fakerate_")+ channel+ "_" +name + Form("_pt%0.f_%0.f.txt", lowpt, highpt),ios::out);
	ofstream file(TString("./txt/TrueNumber_") + channel+Form("_pt%0.f-%0.f.txt", lowpt, highpt),ios::out);
	ofstream file1(TString("./txt/FakeNumber_") +channel+ Form("_pt%0.f-%0.f.txt", lowpt, highpt),ios::out);

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
    file3<<Form("%0.f<pt<%0.f ",lowpt,highpt)<<"\t"<<fixed<<setprecision(3)<<fakerate<<"\t"<<fakerateErr<<"\t"<<chi2ToNDF<<endl;
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
        TLatex* textFR = new TLatex(0.67,0.3,strFR);
        textFR->SetNDC();
        textFR->SetTextSize(0.05);
        textFR->SetLineWidth(1);
        textFR->Draw();

    char buffer[256];
	sprintf(buffer, "./eps/"+c+channel+"_pt%0.f-%0.f.pdf",lowpt,highpt);
//	sprintf(buffer, "./eps/18bins/pt%0.f-%0.f.pdf",lowpt,highpt);
	c1->Print(buffer);
	for(int i=0;i<fdata.size();i++){
		fdata[i]->Close();
	}
	ftrue[0]->Close();
        fdata.clear();
        ftrue.clear();

}
