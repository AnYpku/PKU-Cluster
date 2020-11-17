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
using namespace std;

void cmsLumi(bool channel,TString tag) 
{
        TLatex latex;
        latex.SetNDC();
        latex.SetTextSize(0.04);
        latex.SetLineWidth(2);
        float lumi;
        if(tag.Contains("16")) lumi=35.9;
        if(tag.Contains("17")) lumi=41.5;
        if(tag.Contains("18")) lumi=58.7;
        int beamcomenergytev=13;
        latex.SetTextAlign(31); 
        latex.SetTextAlign(11);
        latex.SetTextSize(0.06);
        latex.DrawLatex(0.25,0.92,"Preliminary");
        latex.DrawLatex(0.18,0.92,"CMS");
        latex.SetTextSize(0.06);
        latex.DrawLatex(0.76,0.92,Form("%0.1f fb^{-1} (%d TeV)", lumi,beamcomenergytev ));
}
TH1D* unroll(TH1D* h1,TString hname){
	int nbins=h1->GetNbinsX();
	TH1D* h1_out= new TH1D(hname, "", nbins-2, 0, nbins-2);
	for(Int_t i=0;i<6;i++){
		h1_out->SetBinContent(i+1,h1->GetBinContent(i+1));
		h1_out->SetBinError(i+1,h1->GetBinError(i+1));
	}
	h1_out->SetBinContent(7,h1->GetBinContent(7) + h1->GetBinContent(8)+h1->GetBinContent(9));
	h1_out->SetBinError(7,sqrt(h1->GetBinError(7)*h1->GetBinError(7)+h1->GetBinError(8)*h1->GetBinError(8)+h1->GetBinError(9)*h1->GetBinError(9)));
	cout<<hname<<" "<<h1_out->GetBinContent(1)<<" "<<h1_out->GetBinError(1)<<endl;
	return h1_out;
}


void unroll_run(TString channel,TString tag,TString var,TString title){
	setTDRStyle();
	TFile* fout = new TFile("./root/aa_"+channel+"_"+var+".root","RECREATE");

	TFile* f_ZA=TFile::Open("./root/hist_"+channel+"_"+var+"_jes"+tag+".root");
	TH1D* th2_ZA1=(TH1D*)f_ZA->Get("hist_0");
	TH1D* th2_ZA2=(TH1D*)f_ZA->Get("hist_1");
	TH1D* th2_ZA3=(TH1D*)f_ZA->Get("hist_2");
//      th2_ZA16->Add(th2_ZA17,1);
//      th2_ZA16->Add(th2_ZA18,1);
//      TH1D* th2_ZA= unroll(th2_ZA16,"t_ZA");
        cout<<tag<<" "<<var<<" "<<channel<<" "<<th2_ZA1->GetSumOfWeights()<<endl;

	th2_ZA1->SetLineColor(kRed);
	th2_ZA2->SetLineColor(kGreen);
	th2_ZA3->SetLineColor(kBlue);
        th2_ZA1->SetLineWidth(2);
        th2_ZA2->SetLineWidth(2);
        th2_ZA3->SetLineWidth(2);

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

//        TLine* line = new TLine(th2_ZA->GetXaxis()->GetXmin(),0,th2_ZA->GetXaxis()->GetXmax(),0);
	TCanvas* c1=new TCanvas("","",800,600);
        TPad*    fPads1 = new TPad("pad1", "", 0.00, 0.3, 0.99, 0.99);
        TPad*    fPads2 = new TPad("pad2", "", 0.00, 0.00, 0.99, 0.3);
        fPads1->SetBottomMargin(0);
        fPads2->SetTopMargin(0);
        fPads2->SetBottomMargin(0.3);
        fPads1->Draw();
        fPads2->Draw();
        fPads1->SetGridx();
        fPads2->SetGridy();
        fPads1->cd();
        double max=th2_ZA1->GetMaximum();
        double min=th2_ZA1->GetMinimum();
        th2_ZA1->GetYaxis()->SetRangeUser(0.5*min,2.5*max);
	th2_ZA1->SetTitle("");
        th2_ZA1->Draw("HIST");
        th2_ZA2->Draw("HIST same");
        th2_ZA3->Draw("HIST same");
//	CMS_lumi(fPads1, 4, 0, lumivalue);

	TLegend* leg = new TLegend(0.7, 0.7, 0.9, 0.9);
	leg->SetTextSize(0.04);
        leg->SetMargin(0.4);
	leg->AddEntry(th2_ZA1, "center");
	leg->AddEntry(th2_ZA2, "up");
	leg->AddEntry(th2_ZA3, "down");
	leg->SetTextSize(0.07);
	leg->Draw();
	
	cmsLumi(0,tag);
        fPads1->Update();
        fPads2->cd();
        TH1D*nominal=(TH1D*)th2_ZA1->Clone("nominal");
        TH1D*nomNoErr=(TH1D*)nominal->Clone("nomNoErr");
        for (int i = 1; i<= nomNoErr->GetNbinsX(); ++i){nomNoErr->SetBinError(i,0);}
        TH1D*h_up=(TH1D*)th2_ZA2->Clone();
        TH1D*h_down=(TH1D*)th2_ZA3->Clone();
        h_up->Divide(nominal);
        h_down->Divide(nominal);
        nominal->Divide(nomNoErr);
	nominal->GetYaxis()->SetRangeUser(0,2);
        cout<<"up "<<h_up->GetBinContent(1)<<" down "<<h_down->GetBinContent(1)<<" central "<<nominal->GetBinContent(1)<<endl;
        double ymax=h_up->GetMaximum()+0.05;double ymin=h_down->GetMinimum()-0.05;
	if(ymax>1>ymin) 
		nominal->GetYaxis()->SetRangeUser(ymin,ymax);
	else if(ymin>1>ymax)
		nominal->GetYaxis()->SetRangeUser(ymax,ymin);
	else if(1>ymin||1>ymax)
		nominal->GetYaxis()->SetRangeUser(0.7,1.05);
	else
		nominal->GetYaxis()->SetRangeUser(1.05,ymax+0.05);
        cout<<ymin<<" "<<ymax<<endl;
        nominal->SetLineColor(2);
        nominal->SetTitle(";"+title+";;");
        nominal->GetYaxis()->SetLabelSize(0.1);
        nominal->GetXaxis()->SetLabelSize(0.1);
	nominal->GetXaxis()->SetTitleSize(0.1);
        nominal->Draw("EP");
        nominal->SetMarkerStyle(20);
//        h_up->SetMarkerStyle(20);
//        h_up->SetMarkerColor(1);
//        h_up->SetLineColor(kGreen);
//        h_down->SetLineColor(kBlue);
//        h_up->SetMarkerSize(1.2);
        h_up->Draw("same hist ][");
        h_down->Draw(" same hist ][");
        fPads2->Update();

	fout->cd();
	fout->Close();

	c1->SaveAs("./figs/aa_"+channel+"_"+var+"_"+tag+".pdf");
}
int unroll_full(){
       vector<TString> tags={"16","17","18"};
       vector<TString> channels={"ZA","ZA-EWK"};
       vector<TString> vars={"jet1pt","jet2pt","Mjj","jet1eta","jet2eta","deltaeta"};
       vector<TString>  title={"jet1pt","jet2pt","Mjj","jet1eta","jet2eta","#Delta#eta_{jj}"};
       for(int i=0;i<channels.size();i++){
	       for(int j=1;j<tags.size()-1;j++){
		       for(int k=0;k<vars.size();k++){
			       unroll_run(channels[i],tags[j],vars[k],title[k]);
		       }
	       }
       }
       return 0;

}
