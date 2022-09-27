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

	TFile* fout = new TFile("aa_"+filename+"_jes"+tag+".root","RECREATE");
	Double_t ZA_scale= 1;
	std::ostringstream strs;
	Double_t mjj_bins[4]={500, 800, 1200,2000};
	Double_t detajj_bins[4]={2.5,4.5,6,6.5};
	const char *name[7]={"0.5~0.8","0.8~1.2","1.2~2","0.5~0.8","0.8~1.2","1.2~2","0.5~2"};

	TFile* f_ZA;
	f_ZA=new TFile("./root/hist_"+filename+"_jes"+tag+".root");
	TH1D* th1_ZA[num];
	TH1D* t_ZA[num];
	TCanvas* cc[num];
	TLegend *ll[num];
	for(Int_t i=0;i<num;i++){
		th1_ZA[i]=(TH1D*)f_ZA->Get(Form("hist_%d",i));
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
//                t_ZA[i]->Scale(1/t_ZA[i]->Integral());
		for(Int_t j=1;j<=t_ZA[i]->GetNbinsX();j++){ t_ZA[i]->GetXaxis()->SetBinLabel(j,name[j-1]);}
	}
	vector<double> vec_ymax;
	vec_ymax.push_back(t_ZA[0]->GetMaximum());
	vec_ymax.push_back(t_ZA[1]->GetMaximum());
	vec_ymax.push_back(t_ZA[2]->GetMaximum());
	sort(vec_ymax.begin(), vec_ymax.end(), greater<double>());

	TCanvas* c1 = new TCanvas("c1","Mjj vs deltajj",800,600);
	TLine* line = new TLine(t_ZA[0]->GetXaxis()->GetXmin(),0,t_ZA[0]->GetXaxis()->GetXmax(),0);
	c1->SetFrameFillColor(41);
        TLegend *l2 = new TLegend(0.6,0.5,0.82,0.82);
        l2->SetLineColor(10);
	TPad*    fPads1 = new TPad("pad1", "", 0.00, 0.3, 0.99, 0.99);
	TPad*    fPads2 = new TPad("pad2", "", 0.00, 0.00, 0.99, 0.3);
        fPads1->SetTopMargin(0.15);
        fPads1->SetBottomMargin(0.03);
        fPads2->SetTopMargin(0);
        fPads2->SetBottomMargin(0.5);
	fPads1->Draw();
	fPads2->Draw();
	fPads1->cd();
        t_ZA[0]->SetTitle("");
        t_ZA[0]->SetLineWidth(3);
        t_ZA[0]->SetLineColor(2);
        t_ZA[0]->GetYaxis()->SetRangeUser(0,t_ZA[0]->GetMaximum()*2.2);
        t_ZA[0]->Draw("HIST");
        t_ZA[0]->GetYaxis()->SetTitle("A.U.");
        t_ZA[0]->GetYaxis()->CenterTitle();
        t_ZA[0]->GetYaxis()->SetTitleSize(0.07);
        t_ZA[0]->GetYaxis()->SetTitleOffset(0.8);
        t_ZA[0]->GetYaxis()->SetLabelSize(0.065);
        t_ZA[0]->GetXaxis()->SetLabelSize(0.0);
	t_ZA[0]->Draw("HIST");
	l2->AddEntry(t_ZA[0],"Nominal");
	for(Int_t i=1;i<num;i++){
		t_ZA[i]->SetLineColor(i+2);
		t_ZA[i]->SetLineWidth(2);
		t_ZA[i]->SetLineStyle(1);
		for(Int_t j=1;j<=t_ZA[i]->GetNbinsX();j++){ t_ZA[i]->GetXaxis()->SetBinLabel(j,name[j-1]);}
		t_ZA[i]->Draw("HIST,SAME");
		if(i==0)         l2->AddEntry(t_ZA[i],"Nominal");
		else if(i==1)    l2->AddEntry(t_ZA[i],"JES_up");
		else if(i==2)    l2->AddEntry(t_ZA[i],"JES_down");
	}

        TLatex latex;
        latex.SetTextSize(0.06);
        latex.SetLineWidth(2);
        latex.DrawLatex(1.2,0.85*vec_ymax[0],"2.5<#Delta#eta_{jj}<4.5");
        latex.DrawLatex(4.2,0.85*vec_ymax[0],"4.5<#Delta#eta_{jj}<6");
        latex.DrawLatex(6.1,0.85*vec_ymax[0],"#Delta#eta_{jj}>6");
        TLine* vline1 = new TLine(t_ZA[0]->GetBinLowEdge(4),0,t_ZA[0]->GetBinLowEdge(4),vec_ymax[0]+0.3*vec_ymax[0]);
        TLine* vline2 = new TLine(t_ZA[0]->GetBinLowEdge(7),0,t_ZA[0]->GetBinLowEdge(7),vec_ymax[0]+0.3*vec_ymax[0]);
        vline1->SetLineStyle(2);
        vline2->SetLineStyle(2);
        vline1->SetLineWidth(2);
        vline2->SetLineWidth(2);
        vline1->Draw(); 
        vline2->Draw(); 

//	cmsLumi(tag) ;
        string lumivalue;
        if(tag.Contains("16")) lumivalue="35.86";
        if(tag.Contains("17")) lumivalue="41.52";
        if(tag.Contains("18")) lumivalue="59.7";
        CMS_lumi(fPads1, 4, 0, lumivalue);
	l2->SetTextSize(0.06);
	l2->Draw();
	fPads1->Update();
	fPads2->cd();

        cout<<"******"<<th1_ZA[0]->GetSum()<<"*******"<<t_ZA[0]->GetSum()<<endl;
	TH1D*nominal=(TH1D*)t_ZA[0]->Clone("nominal");
	TH1D*nomNoErr=(TH1D*)nominal->Clone("nomNoErr");
	for (int i = 1; i<= nomNoErr->GetNbinsX(); ++i){nomNoErr->SetBinError(i,0);}
	TH1D*h_up=(TH1D*)t_ZA[1]->Clone();
	TH1D*h_down=(TH1D*)t_ZA[2]->Clone();
        cout<<"******"<<th1_ZA[0]->GetSum()<<"*******"<<t_ZA[0]->GetSum()<<endl;
	h_up->Divide(nominal);
	h_down->Divide(nominal);
	nominal->Divide(nomNoErr);
        nominal->SetFillStyle(3001);
        nominal->SetFillColor(2);
        nominal->SetLineColor(2);
        nominal->GetYaxis()->SetRangeUser(0.5,1.8);
        nominal->SetTitle(";m_{jj} [TeV];Ratio;");
        nominal->GetYaxis()->SetTitleOffset(0.3);
        nominal->GetYaxis()->SetTitleSize(0.15);
        nominal->GetYaxis()->SetNdivisions(404);
        nominal->GetYaxis()->SetLabelSize(0.15);
        nominal->GetXaxis()->SetLabelSize(0.23);
        nominal->GetXaxis()->SetLabelOffset(0.032);
        nominal->GetXaxis()->SetTitleSize(0.2);
        nominal->GetXaxis()->SetTitleOffset(1.1);
        nominal->SetMarkerSize(0);
  
//	nominal->GetYaxis()->SetRangeUser(h_down->GetMinimum()-0.1,h_up->GetMaximum()+0.05);
	nominal->Draw("E2");
	h_up->Draw("same hist ][");
	h_down->Draw("same hist ][");
	fPads2->Update();
	c1->Print("./figs/hist-2d_"+filename+tag+"_jes.eps");
	c1->Print("./figs/hist-2d_"+filename+tag+"_jes.pdf");

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
	for(int i=0;i<2;i++){
		unroll_name(sample[i],"16");
		unroll_name(sample[i],"17");
		unroll_name(sample[i],"18");
	}
	return 0;
}
