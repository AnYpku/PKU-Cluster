#include <string>
#include <iostream>
#include "TFile.h"
#include "TH1.h"
#include "RooRealVar.h"
#include "RooAddPdf.h"
#include "CMS_lumi.C"
#define ptnumber 6

using namespace RooFit;
using namespace std;
TString dir1 = "../mubarrel/root/";
TString dir = "./fractionfitResult_za/"; 
ofstream file3( dir + "info_fit1.txt");
ofstream file2( dir + "info_number.txt");
Double_t fr,fr_Error;
void fitf(float lowpt, float highpt, float lowchiso, float highchiso){
//TString b="chiso5-12_";

        TFile* f1 = TFile::Open(dir1 + "hist_cutlep-outZA.root");
        TFile* f2 = TFile::Open(dir1 + "hist_cutlep-outZJets_FX.root");
        TH1F* hdata1 = (TH1F*)f1->Get(Form("h11_pt%0.f_%0.f",lowpt,highpt));
        TH1F* hdata2 = (TH1F*)f2->Get(Form("h11_pt%0.f_%0.f",lowpt,highpt));
        TH1F* hfake = (TH1F*)f2->Get(Form("h12_pt%0.f_%0.f_chiso%0.f_%0.f",lowpt,highpt,lowchiso,highchiso));
        TH1F* htrue = (TH1F*)f1->Get(Form("h13_pt%0.f_%0.f",lowpt,highpt));
        TH1F* hist  = (TH1F*) f2->Get(Form("hfake_pt%0.f_%0.f",lowpt,highpt));
        TH1F* hmc    = (TH1F*)f1->Get(Form("htrue_pt%0.f_%0.f",lowpt,highpt));
        TH1F* hsieie = (TH1F*)f1->Get(Form("hsieie_pt%0.f_%0.f",lowpt,highpt));
        TH1D*hdata=(TH1D*)hdata1->Clone();
        hdata->Add(hdata2);

        hdata->Sumw2();hfake->Sumw2();htrue->Sumw2(); 
        hmc->Sumw2(); hist->Sumw2();
	cout<<"OK"<<endl;
	Int_t nBins = hdata->GetNbinsX();
	cout<<"OK1"<<endl;
        for (Int_t i=0; i<nBins; i++){
                if (hdata->GetBinContent(i+1)<=0) hdata->SetBinContent(i+1,0.000000);
                if (htrue->GetBinContent(i+1)<=0) htrue->SetBinContent(i+1,0.000000);
                if (hfake->GetBinContent(i+1)<=0) hfake->SetBinContent(i+1,0.000000);
        }
    
        TObjArray *mc = new TObjArray(2);    
        mc->Add(hfake);
        mc->Add(htrue);
        TFractionFitter* fit = new TFractionFitter(hdata, mc,"V");

//        fit->Constrain(1,0,1);
        fit->Constrain(0,0,1);
        fit->SetRangeX(1,nBins); // use only the first 15 bins in the fit
        Int_t status = fit->Fit();// perform the fit
        std::cout << "fit status: " << status << std::endl;
        if (status == 0) {                       // check on fit status
            TH1F* result = (TH1F*) fit->GetPlot();
	    TCanvas *c1 = new TCanvas("c1","c1",500,400);
	    TPad* fPad1 = new TPad("pad1", "pad1", 0.00, 0.00, 0.99, 0.99);
	    fPad1->Draw();
	    fPad1->cd();
	    fPad1->SetTicky();
	    fPad1->SetLeftMargin(0.15);
	    fPad1->SetTopMargin(0.1);
	    fPad1->SetBottomMargin(0.18);
	    gStyle->SetOptStat(0);
	    c1->SetGrid();
            hdata->SetMarkerColor(1);
            hdata->SetLineColor(1);
            hdata->SetMarkerStyle(20);
            result->SetLineColor(kRed-7);
            result->SetFillColor(kRed-7);
            result->SetLineWidth(4);
            result->SetTitle(";#sigma_{i#etai#eta};Events / bin");
            result->GetXaxis()->SetLabelSize(0.05);
            result->GetXaxis()->SetLabelOffset(0.03);
            result->GetYaxis()->SetLabelSize(0.05);
            result->GetXaxis()->SetTitleSize(0.08);
            result->GetYaxis()->SetTitleSize(0.05);
            result->GetYaxis()->SetTitleOffset(1.4);
            result->GetXaxis()->SetRangeUser(0.006,0.02);
            result->Draw("");
            hdata->Draw("EP SAME");
            auto mcp0 = (TH1F*)fit->GetMCPrediction(0);
            auto mcp1 = (TH1F*)fit->GetMCPrediction(1);
            mcp0->SetLineColor(kBlue);
            mcp0->SetLineWidth(4);
            mcp0->SetLineStyle(1);
            mcp1->SetLineColor(kGreen);
            mcp1->SetLineWidth(4);
            mcp1->SetLineStyle(1);

            Double_t p0, p1, errP0, errP1,fakeValue,fakeError,fake_window;
	    Double_t fake_window_Error,data_window,data_window_Error,mcFake,mcFake_err;

	    Double_t chi2=fit->GetChisquare();
	    Int_t Ndf=fit->GetNDF();
//            double chi2ToNdf = chi2;
	    double chi2ToNdf = chi2/Ndf;

            fit->GetResult( 0, p0, errP0);
            fit->GetResult( 1, p1, errP1);
	    double fit_err = mcp0->Integral(0, mcp0->FindFixBin(0.01015))*result->Integral()*errP0/mcp0->Integral();
            fr = p0* (hfake->Integral(0,hfake->FindFixBin(0.01015))/hfake->Integral())/(result->Integral(0,result->FindFixBin(0.01015))/result->Integral());

            fakeValue = mcp0->IntegralAndError(0,nBins,fakeError); 
            fake_window = mcp0->IntegralAndError(0,mcp0->FindFixBin(0.01015),fake_window_Error);
            data_window = result->IntegralAndError(0,result->FindFixBin(0.01015),data_window_Error);
            fr_Error =sqrt(fake_window_Error*fake_window_Error/(data_window*data_window)
                             + fake_window*fake_window*data_window_Error*data_window_Error/(data_window
                              *data_window*data_window*data_window));;

            double mcp0_scale = result->Integral()*p0/mcp0->Integral();
            double mcp1_scale = result->Integral()*(1-p0)/mcp1->Integral();

	    mcp0->Scale(result->Integral()*p0/mcp0->Integral());//scale mc prediction
	    mcp1->Scale(result->Integral()*p1/mcp1->Integral());//scale mc prediction
            fake_window = fake_window * mcp0_scale;
            fake_window_Error = fake_window_Error* mcp0_scale;
            mcFake = hist->IntegralAndError(0,hist->FindFixBin(0.01015),mcFake_err);

            cout<<"chi2 = "<<chi2<<"; chi2/Ndf = "<<chi2ToNdf<<endl;
            printf("total fake fraction %.3f +/- %.3f\n",  p0, errP0);
            printf("total true fraction %.3f +/- %.3f\n",  p1, errP1);
            cout<<"window fake fraction = "<<fr<<endl;
            cout<<"window fake fraction error = "<<fr_Error<<endl;
            cout<<fake_window<<"; "<<data_window*fr<<endl;

            mcp0->Draw("same hist  ");
            mcp1->Draw("same hist ");

	    cout<<lowchiso<<"<chiso<"<<highchiso<<endl;
	    for(int i=0;i<hist->GetNbinsX();i++){
		    hist->SetBinError(i+1,0);
		    hmc->SetBinError(i+1,0);
	    }
	    hist->SetLineColor(kBlue);
	    hist->SetMarkerColor(kBlue);
	    hist->SetMarkerStyle(24);
	    hist->SetMarkerSize(1);
	    hist->SetLineStyle(2);
	    hist->SetLineWidth(3);
	    hist->Draw("P SAME");
	    hmc->SetMarkerColor(kGreen);
	    hmc->SetLineColor(kGreen);
	    hmc->SetMarkerStyle(26);
	    hmc->SetMarkerSize(1);
	    hmc->SetLineStyle(2);
	    hmc->SetLineWidth(3);
	    hmc->Draw("P SAME");
            
            ofstream myfile(dir + Form("txt/fakerate_photon_pt%0.f_%0.f_chiso_%0.f_%0.f.txt",lowpt,highpt,lowchiso,highchiso),ios::out);
	    ofstream file(dir + TString("TrueNumber_") + Form("pt%0.f-%0.f_chiso%0.f-%0.f.txt", lowpt, highpt,lowchiso,highchiso),ios::out);
	    ofstream file1(dir + TString("FakeNumber_") + Form("pt%0.f-%0.f_chiso%0.f-%0.f.txt", lowpt, highpt,lowchiso,highchiso),ios::out);
            file1<<fake_window<<"\t"<<fit_err<<"\t"<<fr<<"\t"<<fr_Error<<endl;
            myfile <<fr<<"\t"<<fr_Error<<"\t"<<hfake->Integral(1,hfake->FindFixBin(0.01015))<<"\t"<<fakeValue<<"\t"<<fake_window<<endl;
	    file3<<Form("%0.f<pt<%0.f",lowpt,highpt)<<"\t\t"<<Form("%0.f<chiso<%0.f",lowchiso,highchiso)<<"\t"<<fixed<<setprecision(2)<<fr<<"\t"<<fixed<<setprecision(2)<<fr_Error<<endl;
	    file2<<Form("%0.f<pt<%0.f ",lowpt,highpt)<<"\t\t"<<Form("%0.f<chiso<%0.f",lowchiso,highchiso)<<"\t"<<fixed<<setprecision(2)<< mcFake<<"\t"<<fixed<<setprecision(2)<<fake_window<<"\t"<<fixed<<setprecision(2)<<mcFake_err<< fixed<<setprecision(2)<<"\t"<< fake_window_Error<<fixed<<setprecision(2)<<"\t"<<fit_err<<endl;
            myfile.close();
	    char c[200],c2[200],c3[200];
	    sprintf(c,"%.1f",chi2ToNdf);
	    sprintf(c2,"%.1f",fr*100);
	    sprintf(c3,"%.2f",fr_Error*100);
	    TString s="#chi^{2}/ndf = ";
	    TString s2="FR = ";
            TString s3="error = ";
            TString chisquare=s + c;
            TString v=s2 + "( "+c2 + " #pm " + c3+" )%";
            TString e=s3 + c3;

	    TLatex *textchi2 = new TLatex(0.6, 0.4, chisquare);
	    textchi2->SetNDC();
	    textchi2->SetTextSize(0.04);
	    textchi2->SetLineWidth(1);
	    textchi2->Draw();

	    TLatex *textvalue = new TLatex(0.6, 0.3, v);
	    textvalue->SetNDC();
	    textvalue->SetTextSize(0.04);
	    textvalue->SetLineWidth(1);
	    textvalue->Draw();

            TString ptR=Form("%0.f < p_{T}^{#gamma} < %0.f GeV, %0.f < I_{ch} < %0.f GeV",lowpt,highpt,lowchiso,highchiso);
            TLatex *texterror = new TLatex(0.45, 0.5, ptR);
            texterror->SetNDC();
            texterror->SetTextSize(0.04);
//            texterror->SetLineWidth(1);
            texterror->Draw();

	    TLegend *leg = new TLegend(0.45, 0.6, 0.89, 0.89);
            leg->SetLineColor(0);
            leg->SetFillColor(0);
            leg->SetTextSize(0.05);
	    leg->AddEntry(result, "Fit result", "LF");
	    leg->AddEntry(mcp1, "Ture #gamma", "L");
	    leg->AddEntry(mcp0, "Fake #gamma", "L");
	    leg->AddEntry(hist, "Fake #gamma of simulation", "P");
	    leg->AddEntry(hmc, "True #gamma of simulation", "P");
	    leg->Draw("same");
            CMS_lumi(fPad1, 4, 0., "59.7");
            fPad1->Update();
            c1->Print(dir + Form("eps/pt%0.f_%0.f_chiso_%0.f_%0.f.pdf",lowpt,highpt,lowchiso,highchiso));


     }
	f1->Close();
	f2->Close();
}
void run_fitf(Int_t b,Int_t a){
  float lowchiso[21];
  float highchiso[21];
  Double_t lowpt[ptnumber] ={20,25,30,40,50,60};
  Double_t highpt[ptnumber]={25,30,40,50,60,400};
  for(Int_t j=0;j<21;j++){
	  if(j<6)       {lowchiso[j]=3;highchiso[j]=j+8;}
	  if(5<j&&j<11) {lowchiso[j]=4;highchiso[j]=j+3;}
	  if(10<j&&j<15){lowchiso[j]=5;highchiso[j]=j-1;}
	  if(14<j&&j<18){lowchiso[j]=6;highchiso[j]=j-4;}
	  if(17<j&&j<20){lowchiso[j]=7;highchiso[j]=j-6;}
	  if(j==20)     {lowchiso[j]=8;highchiso[j]=j-7;}
  }
  fitf(lowpt[b],highpt[b],lowchiso[a],highchiso[a]);
}

int fitfraction(){
	file2<<"pt range"<<"\t"<<"chiso range"<<"\t"<<"mcTruth number"<<"\t"<<"fit number"<<"\t"<<"mcTruth error"<<"\t"<<"integral error"<<"\t"<<"fit error"<<endl;
        for(Int_t j=0;j<ptnumber;j++){
		file2<<"####################################################"<<endl;
                for(Int_t i=0;i<21;i++){
                        run_fitf(j,i);}
        }
//	run_fitf(1,1);
        return 0;
}

