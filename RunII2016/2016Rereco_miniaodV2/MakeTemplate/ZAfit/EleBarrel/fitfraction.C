#include <string>
#include <iostream>
#include "TFile.h"
#include "TH1.h"
#include "RooRealVar.h"
#include "RooAddPdf.h"
#define ptnumber 9

using namespace RooFit;
using namespace std;
TString dir = "./fractionfitResult_za/"; 
ofstream file3( dir + "info_fit1.txt");
ofstream file2( dir + "info_number.txt");
TFile* fdata = TFile::Open("/home/pku/anying/cms/RunII2016/analysis_code/MakeTemplate/ZAJetfakephoton/EleBarrel/root/Data_template-cutlep-outDEle16.root");
TFile* ftrue = TFile::Open("/home/pku/anying/cms/RunII2016/analysis_code/MakeTemplate/ZAJetfakephoton/EleBarrel/root/True_template-cutlep-outZA.root");
TFile* ffake = TFile::Open("/home/pku/anying/cms/RunII2016/analysis_code/MakeTemplate/ZAJetfakephoton/EleBarrel/root/Fake_template-cutlep-outDEle16.root");
Double_t fr,fr_Error;
TString name;
void fitf(float lowpt, float highpt){
//TString b="chiso5-12_";
        TString filename = ftrue->GetName();
        if(filename.Contains("EWK")) name = "EWK";
        else name = "ZA";
        TH1F* hdata = (TH1F*)fdata->Get(Form("h3_pt%0.f-%0.f",lowpt,highpt));
        TH1F* hfake = (TH1F*)ffake->Get(Form("h2_pt%0.f-%0.f",lowpt,highpt));
        TH1F* htrue = (TH1F*)ftrue->Get(Form("h1_pt%0.f-%0.f",lowpt,highpt));
        TH1F* hzaf  = (TH1F*)ftrue->Get(Form("h4_pt%0.f_%0.f",lowpt,highpt));
        hfake->Add(hzaf,-35.86);
	    htrue->Scale(35.86);

        hdata->Sumw2();hfake->Sumw2();htrue->Sumw2(); 
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
	        gStyle->SetOptStat(0);
	        c1->SetGrid();
	        hdata->SetTitle(Form("Ele Barrel region %0.f < pt < %0.f",lowpt,highpt)); 
            hdata->SetMarkerColor(1);
            hdata->SetLineColor(1);
            hdata->SetMarkerStyle(20);
            result->SetLineColor(kRed);
            hdata->Draw("Ep");
            result->Draw("same");
            auto mcp0 = (TH1F*)fit->GetMCPrediction(0);
            auto mcp1 = (TH1F*)fit->GetMCPrediction(1);
            mcp0->SetLineColor(kBlue);
            mcp0->SetLineWidth(2);
            mcp0->SetLineStyle(1);
            mcp1->SetLineColor(kGreen);
            mcp1->SetLineWidth(2);
            mcp1->SetLineStyle(2);

            Double_t p0, p1, errP0, errP1,fakeValue,fakeError,fake_window,real_window;
	        Double_t fake_window_Error,data_window,data_window_Error,mcFake,mcFake_err,real_window_Error;

	        Double_t chi2=fit->GetChisquare();
	        Int_t Ndf=fit->GetNDF();
            double chi2ToNdf = chi2;//double chi2ToNdf = chi2/Ndf;

            fit->GetResult( 0, p0, errP0);
            fit->GetResult( 1, p1, errP1);
	        double fit_err = mcp0->Integral(0, mcp0->FindFixBin(0.0102)-1)*result->Integral()*errP0/mcp0->Integral();
            fr = p0* (hfake->Integral(0,hfake->FindFixBin(0.0102)-1)/hfake->Integral())/(result->Integral(0,result->FindFixBin(0.0102)-1)/result->Integral());

            fakeValue = mcp0->IntegralAndError(0,nBins,fakeError); 
            fake_window = mcp0->IntegralAndError(0,mcp0->FindFixBin(0.0102)-1,fake_window_Error);
	        real_window = mcp1->IntegralAndError(0,mcp1->FindFixBin(0.0102)-1,real_window_Error);
            data_window = result->IntegralAndError(0,result->FindFixBin(0.0102)-1,data_window_Error);
            fr_Error =sqrt(fake_window_Error*fake_window_Error/(data_window*data_window)
                             + fake_window*fake_window*data_window_Error*data_window_Error/(data_window
                              *data_window*data_window*data_window));;

            double mcp0_scale = result->Integral()*p0/mcp0->Integral();
            double mcp1_scale = result->Integral()*(1-p0)/mcp1->Integral();

	        mcp0->Scale(result->Integral()*p0/mcp0->Integral());//scale mc prediction
	        mcp1->Scale(result->Integral()*(1-p0)/mcp1->Integral());//scale mc prediction
            fake_window = fake_window * mcp0_scale;
            real_window = real_window * mcp1_scale;
            fake_window_Error = fake_window_Error* mcp0_scale;
            fake_window_Error = fake_window_Error* mcp0_scale;
//            mcFake = hist->IntegralAndError(0,hist->FindFixBin(0.03001),mcFake_err);
//            cout<<"mcp0 scale = "<<result->Integral()*p0/mcp0->Integral()<<endl;
//            cout<<"mcp1 scale = "<<result->Integral()*(1-p0)/mcp1->Integral()<<endl;

            cout<<"chi2 = "<<chi2<<"; chi2/Ndf = "<<chi2ToNdf<<endl;
            printf("total fake fraction %.3f +/- %.3f\n",  p0, errP0);
            printf("total true fraction %.3f +/- %.3f\n",  p1, errP1);
            cout<<"window fake fraction = "<<fr<<endl;
            cout<<"window fake fraction error = "<<fr_Error<<endl;
            cout<<fake_window<<"; "<<data_window*fr<<endl;

            mcp0->Draw("same hist e");
            mcp1->Draw("same hist e");
//            mcp0->Print("all");
//            mcp1->Print("all");
//            result->Print("all");
//            hfake->Print("all");
//            htrue->Print("all");
//            hdata->Print("all");
            
//            fr = p0* (hfake->Integral(1,hfake->GetXaxis()->FindFixBin(0.03001)-1)/hfake->Integral())/(hdata->Integral(1,hdata->GetXaxis()->FindFixBin(0.03001)-1)/hdata->Integral());
//            fr = p0* (hfake->Integral(1,hfake->FindFixBin(0.03001))/hfake->Integral())/(hdata->Integral(1,hdata->FindFixBin(0.03001))/hdata->Integral());
            ofstream myfile(dir + Form("txt/fakerate_photon_pt%0.f_%0.f.txt",lowpt,highpt),ios::out);
	        ofstream file(dir + TString("TrueNumber_") + Form("pt%0.f-%0.f.txt", lowpt, highpt),ios::out);
	        ofstream file1(dir + TString("FakeNumber_") + Form("pt%0.f-%0.f.txt", lowpt, highpt),ios::out);
            file1<<fake_window<<"\t"<<fit_err<<"\t"<<fr<<"\t"<<fr_Error<<endl;
            myfile <<fr<<"\t"<<fr_Error<<"\t"<<hfake->Integral(0,hfake->FindFixBin(0.03001)-1)<<"\t"<<fakeValue<<"\t"<<fake_window<<endl;
	        file3<<Form("%0.f<pt<%0.f",lowpt,highpt)<<"\t\t"<<"\t"<<fixed<<setprecision(2)<<fr<<"\t"<<fixed<<setprecision(2)<<fr_Error<<endl;
//	    file2<<Form("%0.f<pt<%0.f ",lowpt,highpt)<<"\t\t"<<Form("%0.f<chiso<%0.f",lowchiso,highchiso)<<"\t"<<fixed<<setprecision(2)<< mcFake<<"\t"<<fixed<<setprecision(2)<<fake_window<<"\t"<<fixed<<setprecision(2)<<mcFake_err<< fixed<<setprecision(2)<<"\t"<< fake_window_Error<<fixed<<setprecision(2)<<"\t"<<fit_err<<endl;
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

	    TLatex *textchi2 = new TLatex(0.6, 0.7, chisquare);
	    textchi2->SetNDC();
	    textchi2->SetTextSize(0.05);
	    textchi2->SetLineWidth(1);
	    textchi2->Draw();
	    TLatex *textvalue = new TLatex(0.6, 0.6, v);
	    textvalue->SetNDC();
	    textvalue->SetTextSize(0.05);
	    textvalue->SetLineWidth(1);
	    textvalue->Draw();
	    TLatex *texterror = new TLatex(0.6, 0.5, e);
	    texterror->SetNDC();
	    texterror->SetTextSize(0.05);
	    texterror->SetLineWidth(1);
	    texterror->Draw();
        gPad->SetLogy(0);
	    TLegend *leg = new TLegend(0.7, 0.8, 0.88, 0.88, NULL, "brNDC");
	    leg->SetFillColor(10);
	    leg->AddEntry(hdata, "Fit result", "L");
	    leg->AddEntry(mcp1, "Ture photons", "L");
	    leg->AddEntry(mcp0, "Fake photons", "L");
	    leg->Draw("same");

        c1->Print(dir + Form("eps/pt%0.f_%0.f.eps",lowpt,highpt));

     }
}
//void run_fitf(Int_t b,Int_t a){
void run_fitf(Int_t b){
  float lowchiso[21];
  float highchiso[21];
 Double_t lowpt[ptnumber]= {20,25,30,35,40,50,60,80,120};
 Double_t highpt[ptnumber]={25,30,35,40,50,60,80,120,400};
  for(Int_t j=0;j<21;j++){
	  if(j<6)       {lowchiso[j]=3;highchiso[j]=j+8;}
	  if(5<j&&j<11) {lowchiso[j]=4;highchiso[j]=j+3;}
	  if(10<j&&j<15){lowchiso[j]=5;highchiso[j]=j-1;}
	  if(14<j&&j<18){lowchiso[j]=6;highchiso[j]=j-4;}
	  if(17<j&&j<20){lowchiso[j]=7;highchiso[j]=j-6;}
	  if(j==20)     {lowchiso[j]=8;highchiso[j]=j-7;}
  }
//  fitf(lowpt[b],highpt[b],lowchiso[a],highchiso[a]);
  fitf(lowpt[b],highpt[b]);
}

int fitfraction(){
	file2<<"pt range"<<"\t"<<"chiso range"<<"\t"<<"mcTruth number"<<"\t"<<"fit number"<<"\t"<<"mcTruth error"<<"\t"<<"integral error"<<"\t"<<"fit error"<<endl;
	run_fitf(0);
	run_fitf(1);
	run_fitf(2);
	run_fitf(3);
	run_fitf(4);
	run_fitf(5);
	run_fitf(6);
	run_fitf(7);
	run_fitf(8);
//        for(Int_t j=0;j<ptnumber;j++){
//		file2<<"####################################################"<<endl;
//                /*for(Int_t i=0;i<21;i++){
//                        run_fitf(j,i);}*/
//		run_fitf(j);
//	}
//	fdata->Close();
//	ftrue->Close();
//	ffake->Close();
      
        return 0;
}

