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
void cmsLumi(bool channel,TString tag) 
{
        TLatex latex;
        latex.SetNDC();
        latex.SetTextSize(0.04);
        latex.SetLineWidth(2);
        int beamcomenergytev=13;
        latex.SetTextAlign(31); 
        latex.SetTextAlign(11);
        latex.DrawLatex(0.18,0.82,"Preliminary");
        latex.DrawLatex(0.18,0.86,"CMS");
        latex.SetTextSize(0.03);
	if(tag.Contains("16"))
		latex.DrawLatex(0.76,0.92,Form("35.86 fb^{-1} (%d TeV)", (beamcomenergytev)));
	if(tag.Contains("17"))
		latex.DrawLatex(0.76,0.92,Form("41.52 fb^{-1} (%d TeV)", (beamcomenergytev)));
	if(tag.Contains("18"))
		latex.DrawLatex(0.76,0.92,Form("58.7 fb^{-1} (%d TeV)", (beamcomenergytev)));
}

void unroll_name(TString filename,TString tag){
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

	TFile* fout = new TFile("aa_"+filename+"_jes"+tag+".root","RECREATE");
	Double_t ZA_scale= 1;
	std::ostringstream strs;
	std::string lumivalue = strs.str();
	Double_t mjj_bins[4]={500, 800, 1200,2000};
	Double_t detajj_bins[4]={2.5,4.5,6,6.5};
	const char *name[7]={"Mjj 500~800","Mjj 800~1200","Mjj 1200~2000","Mjj 500~800","Mjj 800~1200","Mjj 1200~2000","Mjj 500~2000"};

	TFile* f_ZA;
        if(filename.Contains("EWK"))
		f_ZA=new TFile("./root/hist_"+tag+filename+"_jes"+tag+".root");
        else    f_ZA=new TFile("./root/hist_"+filename+"_jes"+tag+".root");
	TH1D* th1_ZA[num];
	TH1D* t_ZA[num];
	TCanvas* cc[num];
	TLegend *ll[num];
	for(Int_t i=0;i<num;i++){
		th1_ZA[i]=(TH1D*)f_ZA->Get(Form("hist_%d",i));
                const int nbins=th1_ZA[i]->GetNbinsX()-2;
                t_ZA[i]=new TH1D(Form("t_ZA%d",i),"",3,0,3);
                for(int k=1;k<=3;k++){
			   t_ZA[i]->SetBinContent(k,th1_ZA[i]->GetBinContent(3*k-2)+th1_ZA[i]->GetBinContent(3*k-2+1)+th1_ZA[i]->GetBinContent(3*k-2+2));
			   t_ZA[i]->SetBinError(k,sqrt(pow(th1_ZA[i]->GetBinError(3*k-2),2)+pow(th1_ZA[i]->GetBinError(3*k-2+1),2)+pow(th1_ZA[i]->GetBinError(3*k-2+2),2)));
		}
		t_ZA[i]->SetLineWidth(3);
		t_ZA[i]->SetLineColor(i+11);
		for(Int_t j=1;j<=t_ZA[i]->GetNbinsX();j++){ t_ZA[i]->GetXaxis()->SetBinLabel(j,name[j-1]);}
	}
	vector<double> vec_ymax;
	vec_ymax.push_back(t_ZA[0]->GetMaximum());
	vec_ymax.push_back(t_ZA[1]->GetMaximum());
	vec_ymax.push_back(t_ZA[2]->GetMaximum());
	sort(vec_ymax.begin(), vec_ymax.end(), greater<double>());
	TCanvas* c1 = new TCanvas("c1","Mjj vs deltajj",900,600);
	TLine* line = new TLine(t_ZA[0]->GetXaxis()->GetXmin(),0,t_ZA[0]->GetXaxis()->GetXmax(),0);
	c1->SetFrameFillColor(41);
	TPad*    fPads1 = new TPad("pad1", "", 0.00, 0.4, 0.99, 0.99);
	TPad*    fPads2 = new TPad("pad2", "", 0.00, 0.00, 0.99, 0.4);
	fPads1->SetBottomMargin(0);
	fPads2->SetTopMargin(0);
	fPads2->SetBottomMargin(0.3);
	fPads1->Draw();
	fPads2->Draw();
	fPads1->cd();
	TLegend *l2 = new TLegend(0.7,0.7,0.9,0.9);
	t_ZA[0]->SetLineWidth(1);
	t_ZA[0]->SetLineColor(kRed);
	t_ZA[0]->GetYaxis()->SetRangeUser(0,vec_ymax[0]+0.3*vec_ymax[0]);
	t_ZA[0]->Draw("HIST");
	t_ZA[0]->GetXaxis()->SetTitle("mjj(GeV)");
	t_ZA[0]->GetXaxis()->SetTitleSize(0.1);
	t_ZA[0]->GetXaxis()->SetLabelSize(0.1);
	t_ZA[0]->GetXaxis()->SetTitleSize(0.065);
	t_ZA[0]->GetXaxis()->SetTitleFont(12);
	l2->AddEntry(t_ZA[0],"mjj_new");
	for(Int_t i=1;i<num;i++){
		t_ZA[i]->SetLineColor(i+2);
		t_ZA[i]->SetLineWidth(1);
		t_ZA[i]->SetLineStyle(2);
		for(Int_t j=1;j<=t_ZA[i]->GetNbinsX();j++){ t_ZA[i]->GetXaxis()->SetBinLabel(j,name[j-1]);}
		t_ZA[i]->Draw("HIST,SAME");
		if(i==0)         l2->AddEntry(t_ZA[i],"mjj_new");
		else if(i==1)    l2->AddEntry(t_ZA[i],"mjj_JEC_up");
		else if(i==2)    l2->AddEntry(t_ZA[i],"mjj_JEC_down");
	}
	l2->Draw();
	line->SetLineColor(2);
	line->SetLineWidth(1);

	fPads1->Update();
	fPads2->cd();

	TH1D*nominal=(TH1D*)t_ZA[0]->Clone("nominal");
	TH1D*nomNoErr=(TH1D*)nominal->Clone("nomNoErr");
	for (int i = 1; i<= nomNoErr->GetNbinsX(); ++i){nomNoErr->SetBinError(i,0);}
	TH1D*h_up=(TH1D*)t_ZA[1]->Clone();
	TH1D*h_down=(TH1D*)t_ZA[2]->Clone();
	h_up->Divide(nominal);
	h_down->Divide(nominal);
	nominal->Divide(nomNoErr);
	nominal->SetFillStyle(3001);
	nominal->SetFillColor(16);
	nominal->GetYaxis()->SetRangeUser(h_down->GetMinimum()-0.05,h_up->GetMaximum()+0.05);
	nominal->Draw();
	h_up->Draw("same hist ][");
	h_down->Draw("same hist ][");
	fPads2->Update();
	c1->Print("./figs/hist-1d_"+filename+tag+".pdf");

	THStack* hs = new THStack("hs", "");
	TLegend *l1 = new TLegend(0.55,0.4,0.8,0.9);
	for(Int_t i=0;i<num;i++){
		hs->Add(t_ZA[i]);
		l1->AddEntry(t_ZA[i],Form("%d central scale pdf variations",i+1));
	}

	fout->cd();

	for(Int_t i=0;i<num;i++){
		t_ZA[i]->Write();}
	hs->Write();
	fout->Close();
	vec_ymax.clear();
}
int unroll_1d(){

	TString sample[2]={"ZA","outJEC_ZA-EWK"};
	for(int i=0;i<2;i++){
		unroll_name(sample[i],"16");
		unroll_name(sample[i],"17");
		unroll_name(sample[i],"18");
	}
	return 0;
}
