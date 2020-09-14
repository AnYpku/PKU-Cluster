#include <string>
#include <iostream>
#include "TFile.h"
#include "TH1.h"
#include "RooRealVar.h"
#include "RooAddPdf.h"
using namespace RooFit;
TString dir1 = "../muendcap/root/";
TFile* fdata = TFile::Open(dir1+"pesudo1.root");
TFile* ftrue = TFile::Open(dir1+"realphoton.root");
//TFile* fdataT = TFile::Open("/data/pku/home/anying/cms/CMSSW_8_0_26_patch2/analysis_code/MakeTemplate/WAJetfakephoton/dataTrue_template_t1.root");
//TFile* fdataF = TFile::Open("/data/pku/home/anying/cms/CMSSW_8_0_26_patch2/analysis_code/MakeTemplate/WAJetfakephoton/dataFake_template_t1.root");
//TFile* fmcT = TFile::Open("/data/pku/home/anying/cms/CMSSW_8_0_26_patch2/analysis_code/MakeTemplate/WAJetfakephoton/mcTrue_template_t1.root");
//TFile* fmcF = TFile::Open("/data/pku/home/anying/cms/CMSSW_8_0_26_patch2/analysis_code/MakeTemplate/WAJetfakephoton/mcFake_template_t1.root");
//TFile* fdata = TFile::Open("/data/pku/home/anying/cms/CMSSW_8_0_26_patch2/analysis_code/MakeTemplate/WAfit/sieieFit/rootfiles/waData_template.root");
//TFile* fmc = TFile::Open("/data/pku/home/anying/cms/CMSSW_8_0_26_patch2/analysis_code/MakeTemplate/WAfit/sieieFit/rootfiles/waMC_template.root");
TString dir = "./fractionfitResult_za/"; 
//TString dir = "./fractionfitResult/"; 
ofstream file3( dir + "info_fit1.txt");
void fitf(float lowpt, float highpt, float lowchiso, float highchiso){
//TString b="chiso5-12_";

	TH1F* hdata_ = (TH1F*)fdata->Get(Form("h11_pt%0.f_%0.f",lowpt,highpt));
        TH1F* hfake_ = (TH1F*)fdata->Get(Form("h12_pt%0.f_%0.f_chiso%0.f_%0.f",lowpt,highpt,lowchiso,highchiso));
        TH1F* htrue_ = (TH1F*)ftrue->Get(Form("h23_pt%0.f_%0.f",lowpt,highpt));
        TH1F* hist_ = (TH1F*) fdata->Get(Form("hfake_pt%0.f_%0.f",lowpt,highpt));
        TH1F* hmc = (TH1F*)fdata->Get(Form("htrue_pt%0.f_%0.f",lowpt,highpt));
        TH1F* hsieie = (TH1F*)fdata->Get(Form("hsieie_pt%0.f_%0.f",lowpt,highpt));
 
	Int_t nBins = hdata->GetNbinsX();
/*        Int_t nBins = 4;
        Int_t sieie_bin=1;
        Double_t bins[5];
        for (Int_t i=0;i<(nBins+1);i++){
                bins[i] = 0.0172 + 0.01*i;
	}
        TH1* hdata = hdata_->Rebin(nBins, "hdata", bins);
        TH1* hdt = htrue_->Rebin(nBins, "htrue", bins);
        TH1* hdf = hfake_->Rebin(nBins, "hfake_data", bins);
        for (Int_t i=0; i<nBins; i++){
                if (hdata->GetBinContent(i+1)<=0) hdata->SetBinContent(i+1,0.000000);
                if (hdt->GetBinContent(i+1)<=0) hdt->SetBinContent(i+1,0.000000);
                if (hdf->GetBinContent(i+1)<=0) hdf->SetBinContent(i+1,0.000000);
        }*/
        Double_t nFake=hdf->Integral();      
        Double_t nTrue=hdt->Integral();      
        Double_t nMax = hdata->GetSumOfWeights();
        Double_t nTrueStart = hmc->GetSumOfWeights();
        Double_t nFakeStart = nMax - nTrueStart;
//	Double_t nReal=hsieie->Integral();
//        std::cout<<"nMax = "<<nMax<<"; nTrueStart = "<<nTrueStart<<"; nFakeStart = "<<nFakeStart<<std::endl;
//        hdf->Scale((nMax-nReal)/nFake);
//        hdt->Scale(nTrueStart/nTrue);
    
        TObjArray *mc = new TObjArray(2);    
        mc->Add(hdf);
        mc->Add(hdt);
        TFractionFitter* fit = new TFractionFitter(hdata, mc,"V");

        fit->Constrain(1,0,1);
//        fit->Constrain(0,0,1);
        fit->SetRangeX(1,nBins); // use only the first 15 bins in the fit
        Int_t status = fit->Fit();// perform the fit
        std::cout << "fit status: " << status << std::endl;
        if (status == 0) {                       // check on fit status
            TH1F* result = (TH1F*) fit->GetPlot();
            TCanvas *c1 = new TCanvas("c1","c1",500,400);
	    c1->SetGrid();
	    hdata->SetTitle(Form("Barrel region %0.f < pt < %0.f ",lowpt,highpt)); 
            hdata->SetMarkerColor(1);
            hdata->SetLineColor(1);
            hdata->SetMarkerStyle(20);
            result->SetLineColor(kRed);
            hdata->Draw("Ep");
            result->Draw("same");
            auto mcp0 = (TH1F*)fit->GetMCPrediction(0);
            mcp0->SetLineColor(kBlue);
            mcp0->SetLineWidth(2);
            mcp0->SetLineStyle(1);
            auto mcp1 = (TH1F*)fit->GetMCPrediction(1);
            mcp1->SetLineColor(kGreen);
            mcp1->SetLineWidth(2);
            mcp1->SetLineStyle(2);
 
            //mcp0->Draw("same hist");
            //mcp1->Draw("same hist");
 
           /*Double_t fakeError, trueError, dataError, dataActualError;
            Double_t eff = hsieie->GetSumOfWeights()/hdt->GetSumOfWeights();
            Double_t trueValue = mcp1->IntegralAndError(0,nBins,trueError)*eff;
            Double_t dataValue = result->IntegralAndError(0,2,dataError);
            Double_t dataActualValue  = hdata->IntegralAndError(0,2,dataError);
            Double_t fakeValue = dataActualValue-trueValue;
                     fakeError = sqrt(dataError * dataError + trueError * trueError);
            Double_t rate = fakeValue/hdata->Integral(0,2);
            Double_t rateError = fakeError/dataActualValue+fakeValue*dataActualError/(dataActualValue*dataActualValue);*/
            Double_t p0, p1, errP0, errP1;
	    Double_t chi2=fit->GetChisquare();
	    Int_t Ndf=fit->GetNDF();
            double chi2ToNdf = chi2/Ndf;
            fit->GetResult( 0, p0, errP0);
            printf(" Parameter %d: fake, estim. %.3f +/- %.3f\n", 0, p0, errP0);
            fit->GetResult( 1, p1, errP1);
            printf(" Parameter %d: true , estim. %.3f +/- %.3f\n", 1, p1, errP1);
            
	    Double_t D1_Error =0,D_Error=0;
            Double_t D1 = hsieie->IntegralAndError(1,20,D1_Error);
            Double_t D  = result->IntegralAndError(1,20,D_Error);
            Double_t D2 = result->Integral()-D1;
            Double_t D2_Error = sqrt(D1_Error*D1_Error+D_Error*D_Error);
           
	    Double_t fr,fr_Error,k;
            if(lowpt<60 && highpt<80){
		    k=1;
		    fr = p0 + (p0*D2/D1) - k*D2/D1;
		    fr_Error=sqrt( pow((errP0+D2/D1*errP0),2) + 
                                    pow((p0/D1*D2_Error - k/D1*D2_Error),2) +
                                    pow((k*D2/(D1*D1)*D1_Error - D2/(D1*D1)*D1_Error),2));
	    }
            if(lowpt>50 && highpt>60 ){
		    fr = p0 + (p0*D2/D1) - 0.81*D2/D1;
		    fr_Error=sqrt( pow((errP0+D2/D1*errP0),2) + 
                                    pow((p0/D1*D2_Error-0.81/D1*D2_Error),2) +
                                    pow((0.81*D2/(D1*D1)*D1_Error - D2/(D1*D1)*D1_Error),2));
	    }
            cout<<"fr = "<<fr<<endl;
            cout<<"fr error = "<<fr_Error<<endl;
            cout<<"D = "<<D<<endl;
            cout<<"D1 = "<<D1<<endl;
            cout<<"D2/D1 = "<<D2/D1<<endl;
 
            ofstream myfile(dir + Form("fakerate_photon_pt%0.f_%0.f.txt",lowpt,highpt),ios::out);
 
            /*myfile <<"Fake Yields"<<fakeValue<<"+-"<<fakeError<<endl;
            myfile <<"Ture yields"<<trueValue<<"+-"<<trueError<<endl;
            myfile <<"Data yields"<<dataValue<<"+-"<<dataError<<endl;*/
            myfile <<"total Fake Rate"<<p0<<"+-"<<errP0<<"\t"<<"; window fake rate "<<fr<<endl;
	    file3<<Form("%0.f <pt<%0.f ",lowpt,highpt)<<"\t"<<fixed<<setprecision(2)<<fr<<"\t"<<fixed<<setprecision(2)<<fr_Error<<endl;
            myfile.close();
	    char c[200],c2[200],c3[200];
	    sprintf(c,"%f",chi2ToNdf);
	    sprintf(c2,"%f",fr);
	    sprintf(c3,"%f",fr_Error);
	    TString s="#chi^{2}/ndf = ";
	    TString s2="value = ";
	    TString s3="error = ";
	    TString chisquare=s + c;
	    TString v=s2 + c2;
	    TString e=s3 + c3;

	    TLatex *textchi2 = new TLatex(0.6, 0.5, chisquare);
	    textchi2->SetNDC();
	    textchi2->SetTextSize(0.05);
	    textchi2->SetLineWidth(1);
	    textchi2->Draw();
	    TLatex *textvalue = new TLatex(0.6, 0.4, v);
	    textvalue->SetNDC();
	    textvalue->SetTextSize(0.05);
	    textvalue->SetLineWidth(1);
	    textvalue->Draw();
	    TLatex *texterror = new TLatex(0.6, 0.3, e);
	    texterror->SetNDC();
	    texterror->SetTextSize(0.05);
	    texterror->SetLineWidth(1);
	    texterror->Draw();
            gPad->SetLogy(0);
            c1->Print(dir + Form("eps/pt%0.f_%0.fMB.eps",lowpt,highpt));

     }
}
