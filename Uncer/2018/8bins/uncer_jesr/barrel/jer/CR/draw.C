#include "TH1.h"
#include "TFile.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TStyle.h"
#include <iostream>
#include "TLegend.h"
#include "THStack.h"
#define num 3
using namespace std;

void unroll_name(TString filename){
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

	TFile* fout = new TFile("aa_"+filename+".root","RECREATE");
	Double_t ZA_scale= 1;
	Double_t lumi=58.7;
	Double_t mjj_bins[2]={150, 4000};
	Double_t detajj_bins[4]={2.5,4.5,6,6.5};
	const char *name[1]={"Mjj 150~400"};
	TFile* f_ZA=TFile::Open("1d_"+filename+"_jer.root");
	TH1D* th2_ZA[num];
	TH1D* t_ZA[num];
	for(Int_t i=0;i<num;i++){
		cout<<"OK"<<endl;
		t_ZA[i]=(TH1D*)f_ZA->Get(Form("th2_%d",i));
		ofstream file2(Form("./txt/content-hist_no%d",i+1));
		t_ZA[i]->SetLineWidth(3);
		t_ZA[i]->SetLineColor(i+11);
		for(Int_t j=1;j<=t_ZA[i]->GetNbinsX()*t_ZA[i]->GetNbinsY();j++){ t_ZA[i]->GetXaxis()->SetBinLabel(j,name[j-1]);}
        for(Int_t k=0;k < t_ZA[i]->GetNbinsX()*t_ZA[i]->GetNbinsY();k++){
		file2<<t_ZA[i]->GetBinContent(k+1)<<endl;}
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
	t_ZA[0]->SetTitle("Mjj vs detajj");
	t_ZA[0]->SetLineWidth(1);
	t_ZA[0]->SetLineColor(kRed);
	t_ZA[0]->GetYaxis()->SetRangeUser(0,vec_ymax[0]+0.3*vec_ymax[0]);
	t_ZA[0]->Draw("HIST");
	t_ZA[0]->GetXaxis()->SetTitle("mjj(GeV)");
	t_ZA[0]->GetXaxis()->SetTitleSize(0.1);
	t_ZA[0]->GetXaxis()->SetLabelSize(0.1);
	t_ZA[0]->GetXaxis()->SetTitleFont(12);
	l2->AddEntry(t_ZA[0],"mjj_new");
	for(Int_t i=1;i<num;i++){
		t_ZA[i]->SetLineColor(i+2);
		t_ZA[i]->SetLineWidth(1);
		t_ZA[i]->SetLineStyle(2);
		for(Int_t j=1;j<=t_ZA[i]->GetNbinsX()*t_ZA[i]->GetNbinsY();j++){ t_ZA[i]->GetXaxis()->SetBinLabel(j,name[j-1]);}
		t_ZA[i]->Draw("HIST,SAME");
		if(i==1)    l2->AddEntry(t_ZA[i],"mjj_JER_up");
		if(i==2)    l2->AddEntry(t_ZA[i],"mjj_JER_down");

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
	//       TH1 * f = gPad->DrawFrame(97, 0.87, 3000, 1.13, ";p_{T}   [GeV];experimental uncertainties");
	//       f->GetXaxis()->SetMoreLogLabels();
	//       f->GetXaxis()->SetNoExponent(); 

	nominal->GetYaxis()->SetRangeUser(0,2);
	nominal->Draw();
	h_up->Draw("same hist ][");
	h_down->Draw("same hist ][");
	fPads2->Update(); 

	c1->Print("./figs/hist-1d_"+filename+".eps");
	c1->Print("./figs/hist-1d_"+filename+".pdf");

	THStack* hs = new THStack("hs", "");
	TLegend *l1 = new TLegend(0.55,0.4,0.8,0.9);
	for(Int_t i=0;i<num;i++){
		hs->Add(t_ZA[i]);
		l1->AddEntry(t_ZA[i],Form("%d central scale pdf variations",i+1));
	}

//	cmsLumi(0);
	fout->cd();
	for(Int_t i=0;i<num;i++){
		t_ZA[i]->Write();}
	hs->Write();
	fout->Close();
        vec_ymax.clear();
}
int draw(){

unroll_name("ZA");
unroll_name("ZA-EWK");
return 0;
}
