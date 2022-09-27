#include "TH1.h"
#include "TFile.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TStyle.h"
#include <iostream>
#include "TLegend.h"
#include "THStack.h"
#include "CMSTDRStyle.h"
#include "CMS_lumi.C"
#define num 3
using namespace std;
TString name="_content";
void cmsLumi(bool channel); 
TH1D* unroll(TH2D* th2_in,Double_t* xbin, Double_t* ybin,  Int_t xbins_in, Int_t ybins_in,char *hname);
void cmsLumi(bool channel) 
{
        TLatex latex;
        latex.SetNDC();
        latex.SetTextSize(0.04);
        latex.SetLineWidth(2);
        float lumiel=41.52;
        float lumimu=41.52;
        int beamcomenergytev=13;
        latex.SetTextAlign(31); 
        latex.SetTextAlign(11);
        latex.DrawLatex(0.18,0.82,"Preliminary");
        latex.DrawLatex(0.18,0.86,"CMS");
        latex.SetTextSize(0.03);
        latex.DrawLatex(0.76,0.92,Form("42.52 fb^{-1} (%d TeV)", (beamcomenergytev)));
}

TH1D* unroll(TH2D* th2_in,Double_t* xbin, Double_t* ybin,  Int_t xbins_in, Int_t ybins_in,char *hname)//,char* htitle)
{
	TH2D* th2 = th2_in;
	Int_t nbinsx =xbins_in;//2D histo的bin的数量,x
	Int_t nbinsy =ybins_in;////2D histo的bin的数量,y
	Int_t nbins = nbinsx*nbinsy;// 2d histo一共被分为多少区域

    TH1D* h1= new TH1D("h1", "", nbins, 0, nbins);
    TH1D* h1_out= new TH1D(hname, "", nbins-2, 0, nbins-2);
    for(Int_t iy=1; iy<=nbinsy; iy++){
	    for(Int_t ix=1; ix<=nbinsx; ix++){
		    Double_t x_temp = 0.5*(xbin[ix-1]+xbin[ix]);
		    Double_t y_temp = 0.5*(ybin[iy-1]+ybin[iy]);
		    h1->SetBinContent(ix+(iy-1)*nbinsx,th2->GetBinContent(th2->FindBin(x_temp, y_temp)));//void SetBinContent(Int_t bin, Double_t content),the FindBin function can return Global bin number corresponding to x,y
		    h1->SetBinError(ix+(iy-1)*nbinsx,th2->GetBinError(th2->FindBin(x_temp, y_temp)));
//		    cout<<"ix = "<<ix<<", iy = "<<iy<<"; bin = "<<ix+(iy-1)*nbinsx<<", BinContent"<<41.52*th2->GetBinContent(th2->FindBin(x_temp, y_temp))<<endl;
	    }
    }
    for(Int_t i=0;i<6;i++){
        h1_out->SetBinContent(i+1,h1->GetBinContent(i+1));
        h1_out->SetBinError(i+1,h1->GetBinError(i+1));
    } 
    h1_out->SetBinContent(7,h1->GetBinContent(7) + h1->GetBinContent(8)+h1->GetBinContent(9) );
    h1_out->SetBinError(7,sqrt(h1->GetBinError(7)*h1->GetBinError(7) + h1->GetBinError(8)*h1->GetBinError(8)+h1->GetBinError(9)*h1->GetBinError(9) ) );
//    h1_out->SetBinContent(8,h1->GetBinContent(9));
//    cout<<h1->GetBinContent(7)<<"; "<<h1->GetBinContent(8)<<"; "<<h1_out->GetBinContent(7)<<endl;
    delete h1;
    return h1_out;
}

int unroll(){
   /* ifstream file1;
    file1.open("./scalefactor.txt");
    if(!file1.is_open()) cout<<"can not open the file"<<endl;
    Double_t scale_factor[9];
    for(Int_t i=0;i<9;i++){
       file1>>scale_factor[i];
       cout<<"scale factor = "<<scale_factor[i]<<endl;
      }*/
	setTDRStyle();
	gStyle->SetPadBorderMode(0);
    gStyle->SetOptStat(0);
	gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetPadTickX(1);
    gStyle->SetPadTickY(1);
    gStyle->SetAxisColor(1, "XYZ");
    gStyle->SetStripDecimals(kTRUE);
    gStyle->SetTickLength(0.03, "XYZ");
    gStyle->SetNdivisions(510, "XYZ");

	TFile* fout = new TFile("aa.root","RECREATE");
	Double_t ZA_scale= 1;
	std::ostringstream strs;
	std::string lumivalue = strs.str();
	Double_t lumi=41.52;
//	Double_t mjj_bins[4]={500, 800, 1200, 2000};
	Double_t mjj_bins[4]={500, 800, 1200,2000};
    Double_t detajj_bins[4]={2.5,4.5,6,6.5};
	const char *name[9]={"Mjj 500~800","Mjj 800~1200","Mjj 1200~2000","Mjj 500~800","Mjj 800~1200","Mjj 1200~2000","Mjj 500~2000"};
//	const char *name[6]={"Mjj 500~800","Mjj 800~1200","Mjj 500~800","Mjj 800~1200","Mjj 500~800","Mjj 800~1200"};

	TFile* f_ZA=TFile::Open("2d_jer.root");
	TH2D* th2_ZA[num];
	TH1D* t_ZA[num];
    TCanvas* cc[num];
    TLegend *ll[num];
    for(Int_t i=0;i<num;i++){
        ll[i] = new TLegend(0.55,0.4,0.8,0.9);
        cc[i] = new TCanvas(Form("cc_%d",i),Form("Mjj vs deltajj %d",i+1),900,600);
        th2_ZA[i]=(TH2D*)f_ZA->Get(Form("th2_%d",i));
        t_ZA[i]= unroll(th2_ZA[i], mjj_bins, detajj_bins, 3,3,Form("hist_%d",i+1));//Form("%d central scale pdf variable",i+1));
        ofstream file2(Form("./txt/content-hist_no%d",i+1));
        t_ZA[i]->SetLineWidth(3);
        t_ZA[i]->SetLineColor(i+11);
        for(Int_t j=1;j<=t_ZA[i]->GetNbinsX()*t_ZA[i]->GetNbinsY();j++){ t_ZA[i]->GetXaxis()->SetBinLabel(j,name[j-1]);}
//        t_ZA[i]->Scale(lumi*ZA_scale);
        t_ZA[i]->Draw("HIST");
//        t_ZA[i]->DrawNormalized("HIST");
        if(i==0) ll[i]->AddEntry(t_ZA[i],"mjj_new");
        else if(i==1)    ll[i]->AddEntry(t_ZA[i],"mjj_JER_up");
        else if(i==2)    ll[i]->AddEntry(t_ZA[i],"mjj_JER_down");
        ll[i]->Draw();
        cc[i]->Print(Form("./figs/tmp-hist2d_%d.eps",i+1));
        for(Int_t k=0;k < t_ZA[i]->GetNbinsX()*t_ZA[i]->GetNbinsY();k++){
//        file2<<t_ZA[i]->GetBinContent(k+1)*scale_factor[i]<<endl;}
        file2<<t_ZA[i]->GetBinContent(k+1)<<endl;}
      }
     TCanvas* c1 = new TCanvas("c1","Mjj vs deltajj",900,600);
     TLine* line = new TLine(t_ZA[0]->GetXaxis()->GetXmin(),0,t_ZA[0]->GetXaxis()->GetXmax(),0);
     c1->SetFrameFillColor(41);
     TLegend *l2 = new TLegend(0.7,0.7,0.9,0.9);
     t_ZA[0]->SetTitle("Mjj vs detajj");
     t_ZA[0]->SetLineWidth(1);
     t_ZA[0]->SetLineColor(kRed);
     t_ZA[0]->GetYaxis()->SetRangeUser(0,0.28);
     t_ZA[0]->Draw("HIST");
     t_ZA[0]->GetXaxis()->SetTitle("mjj(GeV)");
     t_ZA[0]->GetXaxis()->SetTitleSize(0.065);
     t_ZA[0]->GetXaxis()->SetTitleFont(12);
     l2->AddEntry(t_ZA[0],"mjj_new");
//     t_ZA[0]->GetXaxis()->CenterTitle();
     for(Int_t i=1;i<num;i++){
 //         t_ZA[i]->SetFillColor(kMagenta);
 //         t_ZA[i]->SetMarkerColor(kMagenta);
          t_ZA[i]->SetLineColor(i+2);
          t_ZA[i]->SetLineWidth(1);
          t_ZA[i]->SetLineStyle(2);
//          t_ZA[i]->Scale(scale_factor[i]);
          for(Int_t j=1;j<=t_ZA[i]->GetNbinsX()*t_ZA[i]->GetNbinsY();j++){ t_ZA[i]->GetXaxis()->SetBinLabel(j,name[j-1]);}
          //t_ZA[i]->Draw("HIST,SAME");
          t_ZA[i]->Draw("HIST,SAME");
          if(i==0)         l2->AddEntry(t_ZA[i],"mjj_new");
          else if(i==1)    l2->AddEntry(t_ZA[i],"mjj_JER_up");
          else if(i==2)    l2->AddEntry(t_ZA[i],"mjj_JER_down");

         // delete t_ZA[i];
         // delete cc[i];
       }
       l2->Draw();
       line->SetLineColor(2);
       line->SetLineWidth(1);
       line->Draw();
       c1->Print("./figs/hist-2d.eps");
       c1->Print("./figs/hist-2d.pdf");

//	TH1D* t_ZA=unroll(th2_ZA, mjj_bins, detajj_bins, 3,3);
//    for(Int_t i=0;i<num;i++){
//	  t_ZA[i]->SetFillColor(i+1);
//	  t_ZA[i]->SetMarkerColor(i+1);
//	  t_ZA[i]->SetLineColor(i+1);
//	  t_ZA[i]->Scale(lumi*ZA_scale);  
//    }
	THStack* hs = new THStack("hs", "");
    TLegend *l1 = new TLegend(0.55,0.4,0.8,0.9);
    for(Int_t i=0;i<num;i++){
	   hs->Add(t_ZA[i]);
       l1->AddEntry(t_ZA[i],Form("%d central scale pdf variations",i+1));
      }

//    TCanvas* c = new TCanvas("c","Mjj vs deltajj",800,600);
//    c->cd();
//	TPad* fPad1 = new TPad("pad1", "", 0.00, 0.00, 0.99, 0.99);
//	fPad1->Draw();
//	CMS_lumi(fPad1, 4, 0, lumivalue);
//    c->SetFrameFillColor(41);
//    hs->Draw("HIST");
//    hs->GetYaxis()->SetTitleOffset(0.8);
//    hs->GetYaxis()->SetTitle("Events /bin");
//    for(Int_t i=1;i<=9;i++){ hs->GetXaxis()->SetBinLabel(i,name[i-1]);}
//    l1->Draw();
//    c->Print("tmp.eps");

	
//	cmsLumi(0);

	fout->cd();

    for(Int_t i=0;i<num;i++){
	t_ZA[i]->Write();}
    hs->Write();
	fout->Close();
return 0;


}
