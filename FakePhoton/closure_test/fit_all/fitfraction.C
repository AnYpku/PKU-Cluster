#include <string>
#include <iostream>
#include "TFile.h"
#include "TH1.h"
#include "RooRealVar.h"
#include "RooAddPdf.h"

using namespace RooFit;
using namespace std;
TString dir = "./fractionfitResult_za/txt/"; 
TString dir1 = "../../root/";
TString dir2 = "./fractionfitResult_za/eps/"; 
TString dir3 = "./fractionfitResult_za/"; 
TString dir4 = "./fractionfitResult_za/closure/"; 
Double_t fr,fr_Error;
ofstream file2;
ofstream file3;
ofstream file4;
void fitf(float lowpt, float highpt, float lowchiso, float highchiso,TString tag,TString channel){
//TString b="chiso5-12_";

	TFile* fdata = TFile::Open(dir1+"histo_Pdata"+tag+"_"+channel+".root");
	cout<<"OK"<<endl;
	TH1F* hdata = (TH1F*)fdata->Get(Form("h11_pt%0.f_%0.f",lowpt,highpt));
        TH1F* hfake = (TH1F*)fdata->Get(Form("h12_pt%0.f_%0.f_chiso%0.f_%0.f",lowpt,highpt,lowchiso,highchiso));
        TH1F* htrue = (TH1F*)fdata->Get(Form("h13_pt%0.f_%0.f",lowpt,highpt));
        TH1F* hist  = (TH1F*) fdata->Get(Form("hfake_pt%0.f_%0.f",lowpt,highpt));
        TH1F* hmc    = (TH1F*)fdata->Get(Form("htrue_pt%0.f_%0.f",lowpt,highpt));
        TH1F* hsieie = (TH1F*)fdata->Get(Form("hsieie_pt%0.f_%0.f",lowpt,highpt));
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
	    gStyle->SetOptStat(0);
	    c1->SetGrid();
	    hdata->SetTitle(channel + Form(" region %0.f < pt < %0.f, %0.f < chiso < %0.f",lowpt,highpt,lowchiso,highchiso)); 
            hdata->SetMarkerColor(1);
            hdata->SetLineColor(1);
            hdata->SetMarkerStyle(20);
            result->SetLineColor(kRed);
            result->SetLineWidth(2);
            hdata->Draw("Ep");
            result->Draw("same");
            auto mcp0 = (TH1F*)fit->GetMCPrediction(0);
            auto mcp1 = (TH1F*)fit->GetMCPrediction(1);
            mcp0->SetLineColor(kBlue);
            mcp0->SetLineWidth(2);
            mcp0->SetLineStyle(1);
            mcp1->SetLineColor(kGreen);
            mcp1->SetLineWidth(2);
            mcp1->SetLineStyle(1);

            Double_t p0, p1, errP0, errP1;
	    Double_t fake_window_hist,fake_window_StatErr,data_window,data_window_Err,mcFake,mcFake_Err;
            Double_t data_total,data_Err;
            Double_t fake_window_fit,fake_window_fitErr;
	    Double_t chi2=fit->GetChisquare();
	    Int_t Ndf=fit->GetNDF();
	    double chi2ToNdf = chi2/Ndf;

//            cout<<"test "<<mcp0->Integral(0,mcp0->FindFixBin(0.01015))<<endl;
            fit->GetResult( 0, p0, errP0);
            fit->GetResult( 1, p1, errP1);
	    double sieie_medium;
            if(channel.Contains("barrel")) sieie_medium=0.01015;
            if(channel.Contains("endcap")) sieie_medium=0.0272;
            mcFake = hist->IntegralAndError(0,hist->FindFixBin(sieie_medium),mcFake_Err);
            fake_window_hist = mcp0->IntegralAndError(0,mcp0->FindFixBin(sieie_medium),fake_window_StatErr);
            data_total  = hdata->IntegralAndError(0,nBins,data_Err);
            data_window = result->IntegralAndError(0,result->FindFixBin(sieie_medium),data_window_Err);

	    fr = p0* (hfake->Integral(0,hfake->FindFixBin(sieie_medium))/hfake->Integral())/(result->Integral(0,result->FindFixBin(sieie_medium))/result->Integral());
            fr_Error = (hfake->Integral(0,hfake->FindFixBin(sieie_medium))/hfake->Integral())/(result->Integral(0,result->FindFixBin(sieie_medium))/result->Integral())*errP0;

            fake_window_fit=data_window*fr;
            fake_window_fitErr=sqrt(data_window_Err*data_window_Err*fr*fr+
                                           data_window*data_window*fr_Error*fr_Error);

            double mcp0_scale = result->Integral()*p0/mcp0->Integral();
            double mcp1_scale = result->Integral()*(1-p0)/mcp1->Integral();

	    mcp0->Scale(result->Integral()*p0/mcp0->Integral());//scale mc prediction
	    mcp1->Scale(result->Integral()*p1/mcp1->Integral());//scale mc prediction
            fake_window_hist = fake_window_hist * mcp0_scale;
            fake_window_StatErr=fake_window_StatErr*mcp0_scale;

//            cout<<"mcp0 scale = "<<result->Integral()*p0/mcp0->Integral()<<endl;
//            cout<<"mcp1 scale = "<<result->Integral()*(1-p0)/mcp1->Integral()<<endl;

            cout<<"chi2 = "<<chi2<<"; chi2/Ndf = "<<chi2ToNdf<<endl;
            printf("total fake fraction %.3f +/- %.3f\n",  p0, errP0);
            printf("total true fraction %.3f +/- %.3f\n",  p1, errP1);
            cout<<"window fake fraction = "<<fr<<endl;
            cout<<"window fake fraction error = "<<fr_Error<<endl;
            cout<<fake_window_hist<<"; "<<fake_window_fit<<endl;

            mcp0->Draw("same hist e");
            mcp1->Draw("same hist e");
	    cout<<lowchiso<<"<chiso<"<<highchiso<<endl;
//            mcp0->Print("all");
//            mcp1->Print("all");
//            result->Print("all");
//            hfake->Print("all");
//            htrue->Print("all");
//            hdata->Print("all");
	    hist->SetLineColor(kOrange);
	    hist->SetLineStyle(2);
	    hist->SetLineWidth(3);
	    hist->Draw("same hist e");
	    hmc->SetLineColor(kMagenta);
	    hmc->SetLineStyle(2);
	    hmc->SetLineWidth(3);
	    hmc->Draw("same hist e");
            
            ofstream myfile(dir + channel+tag+Form("_fakerate_photon_pt%0.f_%0.f_chiso_%0.f_%0.f.txt",lowpt,highpt,lowchiso,highchiso),ios::out);
	    ofstream file(dir + channel+tag+TString("_TrueNumber_") + Form("pt%0.f-%0.f_chiso%0.f-%0.f.txt", lowpt, highpt,lowchiso,highchiso),ios::out);
	    ofstream file1(dir +channel+tag+ TString("_FakeNumber_") + Form("pt%0.f-%0.f_chiso%0.f-%0.f.txt", lowpt, highpt,lowchiso,highchiso),ios::out);
            file1<<mcFake<<"\t"<<fake_window_fit<<"\t"<<fake_window_fitErr<<"\t"<<fr<<"\t"<<fr_Error<<endl;
            myfile <<fr<<"\t"<<fr_Error<<"\t"<<endl;
	    file3<<Form("%0.f<pt<%0.f",lowpt,highpt)<<"\t\t"<<Form("%0.f<chiso<%0.f",lowchiso,highchiso)<<"\t"<<fixed<<setprecision(2)<<fr<<"\t"<<fixed<<setprecision(2)<<fr_Error<<endl;
	    file2<<Form("%0.f<pt<%0.f ",lowpt,highpt)<<"\t\t"<<Form("%0.f<chiso<%0.f",lowchiso,highchiso)<<"\t"<<fixed<<setprecision(2)<< mcFake<<"\t"<<fake_window_fit<<"\t"<<fake_window_fitErr<<"\t"<< fabs(fake_window_fit-mcFake)/fake_window_fitErr<<"\t"<<mcFake_Err<<endl;
            file4<<lowchiso<<"\t"<<highchiso<<"\t"<<fabs(fake_window_fit-mcFake)/fake_window_fitErr<<"\t"<<fabs(fake_window_fit-mcFake)/-mcFake<<endl;
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

	    TLatex *textchi2 = new TLatex(0.7, 0.5, chisquare);
	    textchi2->SetNDC();
	    textchi2->SetTextSize(0.04);
	    textchi2->SetLineWidth(1);
	    textchi2->Draw();
	    TLatex *textvalue = new TLatex(0.7, 0.4, v);
	    textvalue->SetNDC();
	    textvalue->SetTextSize(0.04);
	    textvalue->SetLineWidth(1);
	    textvalue->Draw();
	    TLatex *texterror = new TLatex(0.7, 0.3, e);
	    texterror->SetNDC();
	    texterror->SetTextSize(0.04);
	    texterror->SetLineWidth(1);
	    texterror->Draw();
            gPad->SetLogy(0);
	    TLegend *leg = new TLegend(0.55, 0.6, 0.9, 0.9, NULL, "brNDC");
	    leg->SetFillColor(10);
            leg->SetTextSize(0.05);
	    leg->AddEntry(hdata, "Fit result", "L");
	    leg->AddEntry(mcp1, "Ture photons", "L");
	    leg->AddEntry(mcp0, "Fake photons", "L");
	    leg->AddEntry(hist, "mc truth of fake #gamma", "L");
	    leg->AddEntry(hmc, "mc truth of true #gamma", "L");
	    leg->Draw("same");

            c1->Print(dir2 + channel+tag+Form("_pt%0.f_%0.f_chiso_%0.f_%0.f.pdf",lowpt,highpt,lowchiso,highchiso));

     }
	fdata->Close();
}
void run_fitf(Int_t b,Int_t a,TString tag,TString channel,vector<double> lowpt,vector<double> highpt){
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
  fitf(lowpt[b],highpt[b],lowchiso[a],highchiso[a],tag,channel);
}

int fitfraction(){
        vector<TString> tag={"2016","2017","2018"};
	vector<TString> channel={"mubarrel","muendcap","elebarrel","eleendcap"};
	vector<double> lowpt;vector<double> highpt;
	for(int ik=0;ik<3/*tag.size()*/;ik++){
		for(int jk=0;jk<channel.size();jk++){
			if(channel[jk].Contains("barrel")) {
				lowpt={20,25,30,40,50,60};
				highpt={25,30,40,50,60,400};
			}
			else if(channel[jk].Contains("endcap")) {
				lowpt={20,25,30,50};
				highpt={25,30,50,400};
			}
			file3.open( dir3 + "info_fit_"+channel[jk]+tag[ik]+".txt");
			file2.open( dir3 + "info_number_"+channel[jk]+tag[ik]+".txt");
			file2<<"pt range"<<"\t"<<"chiso range"<<"\t"<<"nFake_mc"<<"\t"<<"nFake_fit"<<"\t"<<"nFake_fitErr"<<"\t"<<"closure"<<"\t"<<"nFake_mcStat"<<endl;
			file3<<"pt range"<<"\t"<<"chiso range"<<"\t"<<"fake_fraction"<<"\t"<<"fake_fraction_Err"<<endl;
			int ptnumber=lowpt.size();
			for(Int_t j=0;j<ptnumber;j++){
                                file4.open(dir4+channel[jk]+tag[ik]+Form("closure_test_pt%0.f_%0.f.txt",lowpt[j],highpt[j]));
				for(Int_t i=0;i<21/*21*/;i++){
					run_fitf(j,i,tag[ik],channel[jk],lowpt,highpt);

				}//run_fitf(1,1);
				file2<<"####################################################"<<endl;
				file3<<"####################################################"<<endl;
				file4.close();
			}
                        file2.close();
                        file3.close();
		}
	}
	return 0;
}
