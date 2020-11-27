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
#define num 2
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

void unroll_name(TString tag){
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

	TFile* fout = new TFile("aa_interf"+tag+".root","RECREATE");
	Double_t ZA_scale= 1;
	std::ostringstream strs;
	std::string lumivalue = strs.str();
	Double_t mjj_bins[4]={500, 800, 1200,2000};
	Double_t detajj_bins[4]={2.5,4.5,6,6.5};
	const char *name[7]={"Mjj 500~800","Mjj 800~1200","Mjj 1200~2000","Mjj 500~800","Mjj 800~1200","Mjj 1200~2000","Mjj 500~2000"};

	TFile* f_ZA1;TFile* f_ZA2;
	f_ZA1=new TFile("./hist_"+tag+".root");
	f_ZA2=new TFile("./hist_interf_"+tag+".root");
	TH1D* th1_ZA[num];
	TH1D* t_ZA[num];
	TCanvas* cc[num];
	TLegend *ll[num];
	th1_ZA[0]=(TH1D*)f_ZA1->Get("hist");
	th1_ZA[1]=(TH1D*)f_ZA2->Get("hist_interf");
	for(Int_t i=0;i<num;i++){
                const int nbins=th1_ZA[i]->GetNbinsX()-2;
                t_ZA[i]=new TH1D(Form("t_ZA%d",i),"",nbins,0,nbins);
                for(int k=1;k<=nbins;k++){
                   if(k<nbins)  {
			   t_ZA[i]->SetBinContent(k,th1_ZA[i]->GetBinContent(k));
			   t_ZA[i]->SetBinError(k,th1_ZA[i]->GetBinError(k));
		   }
                   if(k==nbins) {
			   t_ZA[i]->SetBinContent(k,th1_ZA[i]->GetBinContent(k)+th1_ZA[i]->GetBinContent(k+1)+th1_ZA[i]->GetBinContent(k+2));
			   t_ZA[i]->SetBinError(k,sqrt(pow(th1_ZA[i]->GetBinError(k),2)+pow(th1_ZA[i]->GetBinError(k+1),2)+pow(th1_ZA[i]->GetBinError(k+2),2)));
		   }
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
        fPads2->SetGridy();
        fPads1->SetGridx();
//        fPads1->SetLogy();
	TLegend *l2 = new TLegend(0.7,0.7,0.9,0.9);
	t_ZA[0]->SetLineWidth(2);
	t_ZA[0]->SetLineColor(kRed);
	t_ZA[0]->GetYaxis()->SetRangeUser(0,vec_ymax[0]+0.3*vec_ymax[0]);
	t_ZA[0]->Draw("HIST");
	t_ZA[0]->GetXaxis()->SetLabelSize(0.1);
	t_ZA[0]->GetYaxis()->SetLabelSize(0.07);
	t_ZA[0]->GetXaxis()->SetTitle("mjj(GeV)");
	t_ZA[0]->GetXaxis()->SetTitleSize(0.1);
	t_ZA[0]->GetXaxis()->SetTitleFont(12);
	l2->AddEntry(t_ZA[0],"EWK ");
	for(Int_t i=1;i<num;i++){
		t_ZA[i]->SetLineColor(i+3);
		t_ZA[i]->SetLineWidth(2);
		t_ZA[i]->SetLineStyle(1);
		for(Int_t j=1;j<=t_ZA[i]->GetNbinsX();j++){ t_ZA[i]->GetXaxis()->SetBinLabel(j,name[j-1]);}
		t_ZA[i]->Draw("HIST,SAME");
		if(i==0)         l2->AddEntry(t_ZA[i],"EWK ");
		else             l2->AddEntry(t_ZA[i],"interference");
	}

        TLatex latex;
        latex.SetTextSize(0.06);
        latex.SetLineWidth(2);
        latex.DrawLatex(1.4,0.85*vec_ymax[0],"2.5<#Delta#eta_{jj}<4.5");
        latex.DrawLatex(4.,0.85*vec_ymax[0],"4.5<#Delta#eta_{jj}<6");
        latex.DrawLatex(6.1,0.85*vec_ymax[0],"#Delta#eta_{jj}>6");
        TLine* vline1 = new TLine(t_ZA[0]->GetBinLowEdge(4),0,t_ZA[0]->GetBinLowEdge(4),vec_ymax[0]+0.3*vec_ymax[0]);
        TLine* vline2 = new TLine(t_ZA[0]->GetBinLowEdge(7),0,t_ZA[0]->GetBinLowEdge(7),vec_ymax[0]+0.3*vec_ymax[0]);
        vline1->SetLineStyle(2);
        vline2->SetLineStyle(2);
        vline1->SetLineWidth(2);
        vline2->SetLineWidth(2);
        vline1->Draw(); 
        vline2->Draw(); 

	cmsLumi(tag) ;
	l2->Draw();

	fPads1->Update();
	fPads2->cd();

	TH1D*nominal=(TH1D*)t_ZA[0]->Clone("nominal");
	TH1D*nomNoErr=(TH1D*)nominal->Clone("nomNoErr");
	for (int i = 1; i<= nomNoErr->GetNbinsX(); ++i){nomNoErr->SetBinError(i,0);}
	TH1D*h_up=(TH1D*)t_ZA[1]->Clone();
//	TH1D*h_down=(TH1D*)t_ZA[2]->Clone();
	h_up->Divide(nominal);
//	h_down->Divide(nominal);
	nominal->Divide(nomNoErr);
	nominal->SetFillStyle(3001);
	nominal->SetFillColor(16);
	h_up->GetYaxis()->SetLabelSize(0.1);
	h_up->GetXaxis()->SetLabelSize(0.1);
        h_up->GetYaxis()->SetTitle("ratio");
        h_up->GetYaxis()->SetTitleSize(0.16);
        h_up->GetYaxis()->SetTitleOffset(0.3);
        h_up->GetYaxis()->SetTitleFont(12);
        h_up->GetXaxis()->SetTitle("mjj(GeV)");
        h_up->GetXaxis()->SetTitleSize(0.1);
        h_up->GetXaxis()->SetTitleFont(12);
        h_up->SetLineColor(1);
        h_up->SetMarkerStyle(20);
//	nominal->GetXaxis()->SetTitleSize(0.3);
	nominal->GetYaxis()->SetRangeUser(h_up->GetMinimum()-0.05,h_up->GetMaximum()+0.05);
//	nominal->Draw("EP");
	h_up->Draw(" P E");
//	h_down->Draw("same hist ][");
	fPads2->Update();
	c1->Print("./figs/interf_"+tag+".eps");
	c1->Print("./figs/interf_"+tag+".pdf");

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
int unroll_test(){

	TString sample[2]={"ZA","ZA-EWK"};
		unroll_name("16");
		unroll_name("17");
		unroll_name("18");
	return 0;
}
