#include <TLatex.h>
#include <iostream>
#include <ostream>
#include <fstream>
#include <TH2.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <THStack.h>
#include <TFile.h>
#include <TROOT.h>
#include <TChain.h>
#include "TObject.h"
#include <vector>
#include <TFractionFitter.h>
using namespace std;
void fit(float lowpt, float highpt, float lowchiso, float highchiso);
void run_fit(Int_t a,Int_t b);
ofstream myfile("./barrel/fraction/result_TFraction.txt");
ofstream file3("./barrel/fraction/info_fitifraction.txt");
ofstream file("./barrel/fraction/detail_frac.txt");
void fit(float lowpt, float highpt, float lowchiso, float highchiso){
  
  TFile* ftrue = TFile::Open(Form("./barrel/root/datap_lep_photonreal_pt%0.f_%0.f.root",lowpt,highpt,lowchiso,highchiso));
  TFile* fdata = TFile::Open(Form("./barrel/root/datap_lep_fake_pt%0.f-%0.f_chiso%0.f-%0.f.root",lowpt,highpt,lowchiso,highchiso));

  TH1F* hdata_ = (TH1F*)fdata->Get(Form("h11_pt%0.f-%0.f",lowpt,highpt));
  TH1F* hfake_ = (TH1F*)fdata->Get(Form("h12_pt%0.f-%0.f_chiso%0.f-%0.f",lowpt,highpt,lowchiso,highchiso));
  TH1F* htrue_ = (TH1F*)ftrue->Get(Form("h23_pt%0.f-%0.f",lowpt,highpt));
  TH1F* hsieie = (TH1F*)fdata->Get(Form("hsieie_pt%0.f-%0.f",lowpt,highpt));

  Int_t nBins = 9;
  Double_t bins[10];
     for (Int_t i=0;i<10;i++){
          bins[i] = 0.004 + 0.002*i;
         }
  TH1* hdata = hdata_->Rebin(nBins, "hdata", bins);
  TH1* htrue = htrue_->Rebin(nBins, "htrue", bins);
  TH1* hfake = hfake_->Rebin(nBins, "hfake_data", bins);

  for (Int_t i=0; i<nBins; i++){
	  if (hdata->GetBinContent(i+1)<=0) hdata->SetBinContent(i+1,0.000000);
	  if (htrue->GetBinContent(i+1)<=0) htrue->SetBinContent(i+1,0.000000);
	  if (hfake->GetBinContent(i+1)<=0) hfake->SetBinContent(i+1,0.000000);
  }

  TObjArray* mc= new TObjArray(2);        // MC histograms are put in this array
  mc->Add(hfake);
  mc->Add(htrue);
  TFractionFitter* fit = new TFractionFitter(hdata,mc,"V"); // initialise
  fit->Constrain(1,0.0,1.0);               // constrain fraction 1 to be between 0 and 1
  fit->SetRangeX(1,nBins);                    // use only the first 15 bins in the fit
  Int_t status = fit->Fit();               // perform the fit
  std::cout << "fit status: " << status <<"  pt range "<<lowpt<<"GeV ~ "<<highpt<<"GeV chiso range"<<lowchiso<<" ~ "<<highchiso<< std::endl;
  if (status == 0) {                       // check on fit status
     TCanvas* c1 = new TCanvas(Form("c1-pt%0.f-%0.f_chiso%0.f-%0.f",lowpt,highpt,lowchiso,highchiso),"fit result",900,600);
     c1->SetGrid();
     TH1F* result = (TH1F*) fit->GetPlot();
     hdata->SetTitle(Form("Barrel region %0.f < pt < %0.f ",lowpt,highpt));                                                      
     hdata->SetMarkerStyle(20);
     hdata->SetMarkerSize(1.1);
     
     hdata->Draw("Ep");
     result->SetLineColor(kRed);
     result->Draw("same");
     Int_t Ndf=fit->GetNDF();
     Double_t chi2=fit->GetChisquare();
     double chi2ToNdf = chi2/Ndf;
     Double_t value,error;
     fit->GetResult(0,value,error);
     cout<<"OK1"<<endl;

     Double_t D1_Error =0,D_Error=0;
     Double_t D1 = hsieie->IntegralAndError(1,180,D1_Error);
     Double_t D  = result->IntegralAndError(1,nBins,D_Error);
     Double_t D2 = D-D1;
     cout<<"D = "<<D<<"; D1 = "<<D1<<"; D2 = "<<D2<<endl;
     Double_t D2_Error = sqrt(D1_Error*D1_Error+D_Error*D_Error);
     Double_t fr,fr_Error,k;
            if(lowpt<60 && highpt<80){
                    k=1;
                    fr = value + (value*D2/D1) - k*D2/D1;
                    fr_Error=sqrt( pow((error+D2/D1*error),2) +
                                    pow((value/D1*D2_Error - k/D1*D2_Error),2) +
                                    pow((k*D2/(D1*D1)*D1_Error - D2/(D1*D1)*D1_Error),2));
           }
            if(lowpt>50 && highpt>60 ){
                    fr = value + (value*D2/D1) - 0.81*D2/D1;
                    fr_Error=sqrt( pow((error+D2/D1*error),2) +
                                    pow((value/D1*D2_Error-0.81/D1*D2_Error),2) +
                                    pow((0.81*D2/(D1*D1)*D1_Error - D2/(D1*D1)*D1_Error),2));
            }
    cout<<"fr = "<<value<<"+("<<value<<"*"<<D2/D1<<")-0.81*"<<D2/D1<<" = "<<fr<<endl;
    myfile<<Form("%0.f<Pt<%0.f\t%0.f<chiso<%0.f",lowpt,highpt,lowchiso,highchiso)<<"\t"<<fixed<<setprecision(1)<<chi2ToNdf<<"\t"<<fixed<<setprecision(2)<<value<<"\t"<<fixed<<setprecision(2)<<error<<"\t"<<"window fake rate\t"<<fixed<<setprecision(2)<<fr<<"\t+-\t"<<fr_Error<<endl;

    file3<<Form("%0.f<Pt<%0.f\t%0.f<chiso<%0.f",lowpt,highpt,lowchiso,highchiso)<<"\twindow fake rate\t"<<fixed<<setprecision(2)<<fr<<"\t+-\t"<<fixed<<setprecision(2)<<fr_Error<<endl;

    file<<Form("%0.f<Pt<%0.f\t%0.f<chiso<%0.f",lowpt,highpt,lowchiso,highchiso)<<"\t"<<fixed<<setprecision(2)<<value<<fixed<<setprecision(2)<<"\t"<<"D="<<D<<"\t"<<fixed<<setprecision(2)<<"D2/D1="<<D2/D1<<"\t"<<fixed<<setprecision(2)<<fr<<"\t+-\t"<<fixed<<setprecision(2)<<fr_Error<<endl;

    char c[20],c2[20],c3[20];
    sprintf(c,"%f",chi2ToNdf);
    sprintf(c2,"%f",value);
    sprintf(c3,"%f",error);
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
    TString chiso =Form("%0.f<chiso<%0.f",lowchiso,highchiso);
    TLatex *textchiso = new TLatex(0.6, 0.6, chiso);
	textchiso->SetNDC();
	textchiso->SetTextSize(0.08);
	textchiso->SetLineWidth(1);
	textchiso->Draw();
     c1->SaveAs(Form("./barrel/fraction/eps/fakefraction_pt%0.f-%0.f_chiso%0.f-%0.f.eps",lowpt,highpt,lowchiso,highchiso));
   }
}
void run_fit(Int_t a,Int_t b){
    float lowchiso[21];
    float highchiso[21];
for(Int_t j=0;j<21;j++){
    if(j<6)       {lowchiso[j]=3;highchiso[j]=j+8;}
    if(5<j&&j<11) {lowchiso[j]=4;highchiso[j]=j+3;}
    if(10<j&&j<15){lowchiso[j]=5;highchiso[j]=j-1;}
    if(14<j&&j<18){lowchiso[j]=6;highchiso[j]=j-4;}
    if(17<j&&j<20){lowchiso[j]=7;highchiso[j]=j-6;}
    if(j==20)     {lowchiso[j]=8;highchiso[j]=j-7;}
  }


    Double_t lowpt[7] ={25,30,35,40,50,65,100};
    Double_t highpt[7]={30,35,40,50,65,100,400};
	fit(lowpt[a],highpt[a],lowchiso[b],highchiso[b]);
}

int main(){
    myfile<<"pt range"<<"\t"<<"chiso range"<<"\t"<<"chi2"<<"\t"<<"value"<<"\t"<<"error"<<endl;
for(Int_t j=0;j<7;j++){    
    for(Int_t i=0;i<21;i++){
	run_fit(j,i);
    }
    myfile<<"##################################################################"<<endl;
    file<<"#######################################################################"<<endl;
    file3<<"#####################################################################"<<endl;
}
	return 0;
}
