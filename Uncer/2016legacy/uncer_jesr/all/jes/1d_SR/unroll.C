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
void cmsLumi(bool channel) 
{
        TLatex latex;
        latex.SetNDC();
        latex.SetTextSize(0.04);
        latex.SetLineWidth(2);
        float lumiel=35.86;
        float lumimu=35.86;
        int beamcomenergytev=13;
        latex.SetTextAlign(31); 
        latex.SetTextAlign(11);
        latex.DrawLatex(0.18,0.82,"Preliminary");
        latex.DrawLatex(0.18,0.86,"CMS");
        latex.SetTextSize(0.03);
        latex.DrawLatex(0.76,0.92,Form("35.86 fb^{-1} (%d TeV)", (beamcomenergytev)));
}

void unroll_name(TString filename){
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

	TFile* fout = new TFile("aa_"+filename+".root","RECREATE");
	Double_t ZA_scale= 1;
	std::ostringstream strs;
	std::string lumivalue = strs.str();
	Double_t lumi=35.86;
        Double_t detajj_bins[4]={2.5,4.5,6,6.5};
        Double_t mjj_bins[4]={500, 800,1200,2000};
        const char *name[3]={"Mjj 500~800","Mjj 800~1200","Mjj 1200~2000"};

	TFile* f_ZA=TFile::Open("2d_"+filename+"_jec.root");
	TH1D* th2_ZA[num];
	TH1D* t_ZA[num];
	TCanvas* cc[num];
	TLegend *ll[num];
	for(Int_t i=0;i<num;i++){
		ll[i] = new TLegend(0.55,0.4,0.8,0.9);
		//        cc[i] = new TCanvas(Form("cc_%d",i),Form("Mjj vs deltajj %d",i+1),900,600);
		t_ZA[i]=(TH1D*)f_ZA->Get(Form("th2_%d",i));
		ofstream file2(Form("./txt/content-hist_no%d",i+1));
		t_ZA[i]->SetLineWidth(3);
		t_ZA[i]->SetLineColor(i+11);
		for(Int_t j=1;j<=t_ZA[i]->GetNbinsX();j++){ t_ZA[i]->GetXaxis()->SetBinLabel(j,name[j-1]);}
		//        t_ZA[i]->Draw("HIST");
		if(i==0) ll[i]->AddEntry(t_ZA[i],"mjj_new");
		else if(i==1)    ll[i]->AddEntry(t_ZA[i],"mjj_JEC_up");
		else if(i==2)    ll[i]->AddEntry(t_ZA[i],"mjj_JEC_down");
		//        ll[i]->Draw();
		//        cc[i]->Print(Form("./figs/tmp-hist2d_"+filename+"_%d.eps",i+1));
		for(Int_t k=0;k < t_ZA[i]->GetNbinsX();k++){
			file2<<t_ZA[i]->GetBinContent(k+1)<<endl;}
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
	fPads2->SetBottomMargin(0.3);
	fPads1->Draw();
	fPads2->Draw();
	fPads1->cd();
	CMS_lumi(fPads1, 4, 0, lumivalue);
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
		//          t_ZA[i]->Scale(scale_factor[i]);
		for(Int_t j=1;j<=t_ZA[i]->GetNbinsX();j++){ t_ZA[i]->GetXaxis()->SetBinLabel(j,name[j-1]);}
		t_ZA[i]->Draw("HIST,SAME");
		if(i==0)         l2->AddEntry(t_ZA[i],"mjj_new");
		else if(i==1)    l2->AddEntry(t_ZA[i],"mjj_JEC_up");
		else if(i==2)    l2->AddEntry(t_ZA[i],"mjj_JEC_down");
	}
	cmsLumi(0);
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
	nominal->SetMarkerStyle(20);
	nominal->Draw();
	h_up->Draw("same hist error ");
	h_down->Draw("same hist error ");
	fPads2->Update();
	c1->Print("./figs/hist-2d_"+filename+".eps");
	c1->Print("./figs/hist-2d_"+filename+".pdf");

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
	vec_ymax.clear();
}
int unroll(){

	unroll_name("ZA-EWK");
	unroll_name("ZA_v3");
	return 0;
}
