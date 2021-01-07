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
void cmsLumi(TString tag); 
TH1D* unroll(TH2D* th2_in,Double_t* xbin, Double_t* ybin,  Int_t xbins_in, Int_t ybins_in,char *hname);
void cmsLumi(TString tag) 
{
        TLatex latex;
        latex.SetNDC();
        latex.SetTextSize(0.06);
        latex.SetLineWidth(2);
        int beamcomenergytev=13;
        latex.SetTextAlign(31); 
        latex.SetTextAlign(11);
        latex.DrawLatex(0.15,0.80,"Preliminary");
        latex.DrawLatex(0.15,0.85,"CMS");
        latex.SetTextSize(0.06);
        if(tag.Contains("16"))
                latex.DrawLatex(0.76,0.92,Form("35.86 fb^{-1} (%d TeV)", (beamcomenergytev)));
        if(tag.Contains("17"))
                latex.DrawLatex(0.76,0.92,Form("41.52 fb^{-1} (%d TeV)", (beamcomenergytev)));
        if(tag.Contains("18"))
                latex.DrawLatex(0.76,0.92,Form("59.7 fb^{-1} (%d TeV)", (beamcomenergytev)));
}

void unroll_name(TString sample,TString tag,int num){
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

	TFile* fout = new TFile("aa_"+sample+"_"+tag+".root","RECREATE");
	const char *name[7]={"0.5~0.8","0.8~1.2","1.2~2","0.5~0.8","0.8~1.2","1.2~2","0.5~2"};

	TFile* file=TFile::Open("./hist_"+sample+"_scale"+tag+".root");
	TH1D* t_ZA[num];TH1D* th1_ZA[num];
	TCanvas* cc[num];
	TLegend *ll[num];
        vector<double> vec_ymax;
	int p=0;
	for(Int_t i=0;i<num;i++){
		if((i==5||i==7) && sample.Contains("qcd")) continue;
		ll[p] = new TLegend(0.55,0.4,0.8,0.9);
		cc[p] = new TCanvas(Form("cc_%d",i),Form("Mjj vs deltajj %d",i+1),900,600);
		cout<<"get "<<i+1<<" histo"<<endl;
		th1_ZA[p]=(TH1D*)file->Get(Form("hist_%d",i));
		const int nbins=th1_ZA[p]->GetNbinsX();
                t_ZA[p]=(TH1D*)th1_ZA[p]->Clone();
                /*t_ZA[p]=new TH1D(Form("t_ZA%d",i),"",nbins,0,nbins);
                for(int k=1;k<=nbins;k++){
                   if(k<nbins)  {
                           t_ZA[p]->SetBinContent(k,th1_ZA[p]->GetBinContent(k));
                           t_ZA[p]->SetBinError(k,th1_ZA[p]->GetBinError(k));
                   }
                   if(k==nbins) {
                           t_ZA[p]->SetBinContent(k,th1_ZA[p]->GetBinContent(k)+th1_ZA[p]->GetBinContent(k+1)+th1_ZA[p]->GetBinContent(k+2));
                           t_ZA[p]->SetBinError(k,sqrt(pow(th1_ZA[p]->GetBinError(k),2)+pow(th1_ZA[p]->GetBinError(k+1),2)+pow(th1_ZA[p]->GetBinError(k+2),2)));
                   }
                }*/
		t_ZA[p]->SetLineWidth(3);
		t_ZA[p]->SetLineColor(i+11);
		for(Int_t j=1;j<=t_ZA[p]->GetNbinsX();j++){ t_ZA[p]->GetXaxis()->SetBinLabel(j,name[j-1]);}
		t_ZA[p]->Draw("HIST");
		cout<<"hist"<<i<<" "<<t_ZA[p]->GetBinContent(1)<<endl;
		if(i==1) ll[p]->AddEntry(t_ZA[p],Form("%d central scale variation",i+1));
		else     ll[p]->AddEntry(t_ZA[p],Form("%d scale variation",i+1));
		ll[p]->Draw();
		cc[p]->Print(Form("./figs/tmp-hist2d_%d.eps",i+1));
		vec_ymax.push_back(t_ZA[p]->GetMaximum());
		p++;
	}
        sort(vec_ymax.begin(), vec_ymax.end(), greater<double>());
	TCanvas* c1 = new TCanvas("c1","Mjj vs deltajj",900,600);
        c1->SetFrameFillColor(41);
        TPad*    fPads1 = new TPad("pad1", "", 0.00, 0.4, 0.99, 0.99);
        TPad*    fPads2 = new TPad("pad2", "", 0.00, 0.00, 0.99, 0.4);
	TLegend *l2 = new TLegend(0.7,0.5,0.9,0.9);
	fPads1->SetBottomMargin(0);
        fPads2->SetTopMargin(0);
        fPads2->SetBottomMargin(0.5);
        fPads1->Draw();
        fPads2->Draw();
        fPads1->cd();
        fPads2->SetGridy();
        fPads1->SetGridx();
	t_ZA[0]->SetTitle("");
	t_ZA[0]->SetLineWidth(3);
	t_ZA[0]->SetLineColor(2);
	t_ZA[0]->GetYaxis()->SetRangeUser(0,t_ZA[0]->GetMaximum()*2);
	t_ZA[0]->Draw("HIST");
        t_ZA[0]->GetYaxis()->SetLabelSize(0.1);
	l2->AddEntry(t_ZA[0]," central scale ");
	cout<<"Draw comparison"<<endl;
	for(Int_t i=1;i<p;i++){
		t_ZA[i]->SetLineColor(i+2);
		t_ZA[i]->SetLineWidth(3);
		t_ZA[i]->SetLineStyle(2);
		for(Int_t j=1;j<=t_ZA[i]->GetNbinsX();j++){ t_ZA[i]->GetXaxis()->SetBinLabel(j,name[j-1]);}
		t_ZA[i]->Draw("HIST,SAME");
		if(i<5) l2->AddEntry(t_ZA[i],  Form("scale%d ",i+1));
		else if(i==5)   l2->AddEntry(t_ZA[i],"scale7 ");
		else if(i==6)   l2->AddEntry(t_ZA[i],"scale9 ");
	}
	cout<<"Draw latex"<<endl;
        TLatex latex;
        latex.SetTextSize(0.06);
        latex.SetLineWidth(2);
        latex.DrawLatex(1.4,0.85*vec_ymax[0],"2.5<#Delta#eta_{jj}<4.5");
        latex.DrawLatex(4.,0.85*vec_ymax[0],"4.5<#Delta#eta_{jj}<6");
        latex.DrawLatex(6.1,0.85*vec_ymax[0],"#Delta#eta_{jj}>6");
        TLine* vline1 = new TLine(t_ZA[0]->GetBinLowEdge(4),0,t_ZA[0]->GetBinLowEdge(4),vec_ymax[0]*1.7);
        TLine* vline2 = new TLine(t_ZA[0]->GetBinLowEdge(7),0,t_ZA[0]->GetBinLowEdge(7),vec_ymax[0]*1.7);
        vline1->SetLineStyle(2);
        vline2->SetLineStyle(2);
        vline1->SetLineWidth(2);
        vline2->SetLineWidth(2);
        vline1->Draw();
        vline2->Draw();

//	cmsLumi(tag);
	string lumivalue;
	if(tag.Contains("16")) lumivalue="35.86";
	if(tag.Contains("17")) lumivalue="41.52";
	if(tag.Contains("18")) lumivalue="59.7";
	CMS_lumi(fPads1, 4, 0, lumivalue);
	l2->SetTextSize(0.05);
	l2->Draw();
        fPads1->Update();
        fPads2->cd();
	cout<<"go to pad2"<<endl;
        TH1D*nominal=(TH1D*)t_ZA[0]->Clone("nominal");
        TH1D*nomNoErr=(TH1D*)nominal->Clone("nomNoErr");
        for (int i = 1; i<= nomNoErr->GetNbinsX(); ++i){nomNoErr->SetBinError(i,0);}
        nominal->SetFillStyle(3001);
        nominal->SetFillColor(16);
	nominal->SetMarkerStyle(20);
	nominal->GetYaxis()->SetLabelSize(0.15);
        nominal->GetYaxis()->SetNdivisions(404);
        nominal->GetXaxis()->SetTitle("mjj [TeV]");
        nominal->GetXaxis()->SetLabelSize(0.15);
	nominal->GetXaxis()->SetLabelOffset(0.03);
        nominal->GetXaxis()->SetTitleFont(12);
	nominal->GetXaxis()->SetTitleSize(0.2);
        TH1D*h_up[num];
	int m=1;
	cout<<"hist0 "<<nominal->GetBinContent(1)<<endl;
	vector<double> vec_min;vector<double> vec_max;
	for(int i=1;i<num;i++){
		if( (i==5||i==7) && sample.Contains("qcd"))continue;
		h_up[m]=(TH1D*)t_ZA[m]->Clone();
		h_up[m]->Divide(nominal);
                h_up[m]->SetLineWidth(1);
                h_up[m]->SetLineStyle(1);
		cout<<"hist"<<i<<" "<<h_up[m]->GetBinContent(1)<<endl;
		vec_max.push_back(h_up[m]->GetMaximum());
		vec_min.push_back(h_up[m]->GetMinimum());
		m++;
	}
        sort(vec_max.begin(), vec_max.end(), greater<double>());        
        sort(vec_min.begin(), vec_min.end(), greater<double>());        
	cout<<"draw ratio band"<<endl;
        nominal->GetYaxis()->SetRangeUser(vec_min[vec_min.size()-1]-0.05,vec_max[0]+0.05);
        nominal->Divide(nomNoErr);
	nominal->Draw("EP");
        for(int i=1;i<m;i++){h_up[i]->Draw("same hist");}
        fPads2->Update();
	c1->SaveAs("./figs/hist_scale_"+sample+tag+".eps");
	c1->SaveAs("./figs/hist_scale_"+sample+tag+".pdf");

        vec_ymax.clear();
	fout->cd();
	m=0;
	for(Int_t i=0;i<num;i++){
		if( (i==5||i==7) && sample.Contains("qcd"))continue;
		t_ZA[m]->Write();
		m++;
	}
	fout->Close();
	return 0;
}
int unroll_test(){

	TString sample[2]={"qcd","ewk"};
        int num[2]={9,3};
        for(int i=0;i<2;i++){
                unroll_name(sample[i],"16",num[i]);
                unroll_name(sample[i],"17",num[i]);
                unroll_name(sample[i],"18",num[i]);
        }

	return 0;
}
