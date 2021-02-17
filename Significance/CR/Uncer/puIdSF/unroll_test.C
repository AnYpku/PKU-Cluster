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
void cmsLumi(TString tag) 
{
        TLatex latex;
        latex.SetNDC();
        latex.SetTextSize(0.06);
        latex.SetLineWidth(2);
        int beamcomenergytev=13;
        latex.SetTextAlign(31); 
        latex.SetTextAlign(11);
        latex.DrawLatex(0.18,0.81,"Preliminary");
        latex.DrawLatex(0.18,0.86,"CMS");
        latex.SetTextSize(0.06);
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

	Double_t ZA_scale= 1;
	std::ostringstream strs;

	TFile* f_ZA;
	f_ZA=new TFile("./root/hist_ZA_puIdmis_mubarrelCR.root");
	TH1D* th1_ZA[num];
	TH1D* t_ZA[num];
	TCanvas* cc[num];
	TLegend *ll[num];
	for(Int_t i=0;i<num;i++){
		t_ZA[i]=(TH1D*)f_ZA->Get(Form("hist_%d",i));
		t_ZA[i]->SetLineWidth(3);
		t_ZA[i]->SetLineColor(i+11);
	}
	vector<double> vec_ymax;
	vec_ymax.push_back(t_ZA[0]->GetMaximum());
	vec_ymax.push_back(t_ZA[1]->GetMaximum());
	vec_ymax.push_back(t_ZA[2]->GetMaximum());
	sort(vec_ymax.begin(), vec_ymax.end(), greater<double>());
	TCanvas* c1 = new TCanvas("c1","Mjj vs deltajj",900,600);
	TLine* line = new TLine(t_ZA[0]->GetXaxis()->GetXmin(),0,t_ZA[0]->GetXaxis()->GetXmax(),0);
	c1->SetFrameFillColor(41);
	TPad*    fPads1 = new TPad("pad1", "", 0.00, 0.0, 0.99, 0.99);
	fPads1->Draw();
	fPads1->cd();
        fPads1->SetGridx();
	TLegend *l2 = new TLegend(0.7,0.7,0.9,0.9);
	t_ZA[0]->SetLineWidth(2);
	t_ZA[0]->SetLineColor(kRed);
	t_ZA[0]->GetYaxis()->SetRangeUser(0,vec_ymax[0]+0.3*vec_ymax[0]);
	t_ZA[0]->SetTitle(";M_{jj} [GeV];");
	t_ZA[0]->Draw("HIST");
	l2->AddEntry(t_ZA[0],"mjj_new");
	for(Int_t i=1;i<num;i++){
		t_ZA[i]->SetLineColor(i+2);
		t_ZA[i]->SetLineWidth(2);
		t_ZA[i]->SetLineStyle(1);
		for(Int_t j=1;j<=t_ZA[i]->GetNbinsX();j++){ 
			if(t_ZA[i]->GetBinContent(j)<0){
				t_ZA[i]->SetBinContent(j,0);
				t_ZA[i]->SetBinError(j,0);
			}
		}
		t_ZA[i]->Draw("HIST,SAME");
		if(i==0)         l2->AddEntry(t_ZA[i],"puId_mis");
		else if(i==1)    l2->AddEntry(t_ZA[i],"puId_mis_up");
		else if(i==2)    l2->AddEntry(t_ZA[i],"puId_mis_down");
	}

//	cmsLumi(tag) ;
        string lumivalue;
        if(tag.Contains("17")) lumivalue="41.52";
        CMS_lumi(fPads1, 4, 0, lumivalue);
	l2->Draw();
	fPads1->Update();
	c1->Print("./figs/hist-2d_"+filename+tag+"_mis.eps");
	c1->Print("./figs/hist-2d_"+filename+tag+"_mis.pdf");

	vec_ymax.clear();
}
int unroll_test(){

	TString sample[2]={"ZA"};
	for(int i=0;i<2;i++){
		unroll_name(sample[i],"17");
	}
	return 0;
}
