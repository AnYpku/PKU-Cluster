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
		latex.DrawLatex(0.76,0.92,Form("59.7 fb^{-1} (%d TeV)", (beamcomenergytev)));
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
	Double_t mjj_bins[4]={500, 800, 1200,2000};
	Double_t detajj_bins[4]={2.5,4.5,6,6.5};
	const char *name[7]={"0.5~0.8","0.8~1.2","1.2~2","0.5~0.8","0.8~1.2","1.2~2","0.5~2"};

	TFile* f_ZA;
	f_ZA=new TFile("./referee/unfold_"+filename+"_jet1pt_jes"+tag+".root");
	TH1D* t_ZA[num];
	TCanvas* cc[num];
	TLegend *ll[num];
	for(Int_t i=0;i<num;i++){
		t_ZA[i]=(TH1D*)f_ZA->Get(Form("jet1pt_%d",i));
                const int nbins=t_ZA[i]->GetNbinsX();
                cout<<"Integral "<<t_ZA[i]->Integral()<<endl;
                t_ZA[i]->Scale(1/t_ZA[i]->Integral());
		t_ZA[i]->SetLineWidth(3);
		t_ZA[i]->SetLineColor(i+11);
//		for(Int_t j=1;j<=t_ZA[i]->GetNbinsX();j++){ t_ZA[i]->GetXaxis()->SetBinLabel(j,name[j-1]);}
	}
	vector<double> vec_ymax;
	vec_ymax.push_back(t_ZA[0]->GetMaximum());
	vec_ymax.push_back(t_ZA[1]->GetMaximum());
	vec_ymax.push_back(t_ZA[2]->GetMaximum());
	sort(vec_ymax.begin(), vec_ymax.end(), greater<double>());
	TCanvas* c1 = new TCanvas("c1","",900,600);
	TLine* line = new TLine(t_ZA[0]->GetXaxis()->GetXmin(),0,t_ZA[0]->GetXaxis()->GetXmax(),0);
	c1->SetFrameFillColor(41);
	TPad*    fPads1 = new TPad("pad1", "", 0.00, 0.4, 0.99, 0.99);
	TPad*    fPads2 = new TPad("pad2", "", 0.00, 0.00, 0.99, 0.4);
	fPads1->SetBottomMargin(0);
	fPads2->SetTopMargin(0);
	fPads2->SetBottomMargin(0.4);
	fPads1->Draw();
	fPads2->Draw();
	fPads1->cd();
        fPads2->SetGridy();
        fPads1->SetGridx();
	TLegend *l2 = new TLegend(0.7,0.7,0.9,0.9);
        t_ZA[0]->SetTitle("");
	t_ZA[0]->SetLineWidth(2);
	t_ZA[0]->SetLineColor(kRed);
        t_ZA[0]->GetYaxis()->SetLabelSize(0.05);
        t_ZA[0]->GetYaxis()->SetRangeUser(0,vec_ymax[0]+0.3*vec_ymax[0]);
	t_ZA[0]->Draw("HIST");
	l2->AddEntry(t_ZA[0],"Nominal");
	for(Int_t i=1;i<num;i++){
		t_ZA[i]->SetLineColor(i+2);
		t_ZA[i]->SetLineWidth(2);
		t_ZA[i]->SetLineStyle(1);
		for(Int_t j=1;j<=t_ZA[i]->GetNbinsX();j++){ t_ZA[i]->GetXaxis()->SetBinLabel(j,name[j-1]);}
		t_ZA[i]->Draw("HIST,SAME");
		if(i==0)         l2->AddEntry(t_ZA[i],"Nominal");
		else if(i==1)    l2->AddEntry(t_ZA[i],"Up");
		else if(i==2)    l2->AddEntry(t_ZA[i],"Down");
	}

//	cmsLumi(tag) ;
        string lumivalue;
        if(tag.Contains("16")) lumivalue="35.86";
        if(tag.Contains("17")) lumivalue="41.52";
        if(tag.Contains("18")) lumivalue="59.7";
        CMS_lumi(fPads1, 4, 0, lumivalue);
	l2->Draw();
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
        nominal->GetYaxis()->SetLabelSize(0.08);
        nominal->GetYaxis()->SetNdivisions(404);
        nominal->GetXaxis()->SetTitle("m_{jj} [TeV]");
        nominal->GetXaxis()->SetLabelSize(0.08);
        nominal->GetXaxis()->SetTitleFont(12);
        nominal->GetXaxis()->SetTitleSize(0.15);
	nominal->GetYaxis()->SetRangeUser(0,2);
	nominal->Draw("EP");
	h_up->Draw("same hist ][");
	h_down->Draw("same hist ][");
	fPads2->Update();
	c1->Print("./figs/hist-2d_"+filename+tag+"_jes.eps");
	c1->Print("./figs/hist-2d_"+filename+tag+"_jes.pdf");

	THStack* hs = new THStack("hs", "");
	TLegend *l1 = new TLegend(0.55,0.4,0.8,0.9);
	fout->cd();

	for(Int_t i=0;i<num;i++){
		t_ZA[i]->Write();}
	hs->Write();
	fout->Close();
	vec_ymax.clear();
}
int unroll_test(){

	TString sample[1]={"ZA"};
	for(int i=0;i<1;i++){
		unroll_name(sample[i],"16");
		unroll_name(sample[i],"17");
		unroll_name(sample[i],"18");
	}
	return 0;
}
