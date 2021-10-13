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
void unroll_name(TString filename,TString tag,TString type){
	setTDRStyle();
	gStyle->SetOptStat(0);
	TFile* f_ZA=new TFile("./root/hist_"+filename+"_"+tag+".root");
	TH1D* t_ZA[num];
	for(Int_t i=0;i<num;i++){
		if(filename.Contains("WWG")==0)
			t_ZA[i]=(TH1D*)f_ZA->Get(Form("hist_hist_%d",i));
		else
			t_ZA[i]=(TH1D*)f_ZA->Get(Form("hist_sig_%d",i));
		t_ZA[i]->SetTitle("");
	}
        TCanvas* c1=new TCanvas("","",800,600);
	TLine* line = new TLine(t_ZA[0]->GetXaxis()->GetXmin(),0,t_ZA[0]->GetXaxis()->GetXmax(),0);
	c1->SetFrameFillColor(41);
        TPad*    fPads1 = new TPad("pad1", "", 0.00, 0.3, 0.99, 0.99);
        TPad*    fPads2 = new TPad("pad2", "", 0.00, 0.00, 0.99, 0.3);
        fPads1->SetBottomMargin(0.028);
        fPads2->SetTopMargin(0.012);
        fPads2->SetBottomMargin(0.45);
        fPads1->Draw();
        fPads2->Draw();
        fPads1->cd();
        fPads2->SetGridy();

        const char *name[16]={"20-80","80-120","120-160","160-#infty","20-80","80-120","120-160","160-#infty","20-80","80-120","120-160","160-#infty","20-80","80-120","120-160","160-#infty"};

	double max=t_ZA[0]->GetMaximum();
	t_ZA[0]->SetMaximum(2.5*max);
	t_ZA[0]->SetLineWidth(2);
	t_ZA[0]->SetLineColor(1);
	t_ZA[0]->SetMarkerStyle(20);
        t_ZA[0]->GetYaxis()->SetTitleSize(0.08);
        t_ZA[0]->GetYaxis()->SetLabelSize(0.07);
        t_ZA[0]->GetXaxis()->SetLabelSize(0.0);
        t_ZA[0]->GetYaxis()->SetNdivisions(505);
	t_ZA[0]->Draw("PE");

	TLegend *l2 = new TLegend(0.6,0.6,0.9,0.9);
	l2->AddEntry(t_ZA[0],type+" central");

	for(Int_t i=1;i<num;i++){
		if(i==1)t_ZA[i]->SetLineColor(kBlue);
		if(i==2)t_ZA[i]->SetLineColor(kGreen);
		t_ZA[i]->SetLineWidth(2);
		t_ZA[i]->SetLineStyle(1);
		t_ZA[i]->Draw("HIST,SAME");
		if(i==0)         l2->AddEntry(t_ZA[i],type+" central");
		else if(i==1)    l2->AddEntry(t_ZA[i],type+" up");
		else if(i==2)    l2->AddEntry(t_ZA[i],type+" down");
	}

        TLatex latex;
        latex.SetTextSize(0.06);
        latex.SetLineWidth(2);
        latex.DrawLatex(0.5,1.4*max,"20<m_{#font[12]{ll}}<80");
        latex.DrawLatex(4.5,1.4*max,"80<m_{#font[12]{ll}}<120");
        latex.DrawLatex(8.5,1.4*max,"120<m_{#font[12]{ll}}<160");
        latex.DrawLatex(13, 1.4*max,"m_{#font[12]{ll}}>160");
        latex.DrawLatex(1.2, 1.8*max,"sample: "+filename);

        TLine* vline1 = new TLine(t_ZA[0]->GetBinLowEdge(5),0,t_ZA[0]->GetBinLowEdge(5),max*1.5);
        TLine* vline2 = new TLine(t_ZA[0]->GetBinLowEdge(9),0,t_ZA[0]->GetBinLowEdge(9),max*1.5);
        TLine* vline3 = new TLine(t_ZA[0]->GetBinLowEdge(13),0,t_ZA[0]->GetBinLowEdge(13),max*1.5);
        vline1->SetLineStyle(2);
        vline2->SetLineStyle(2);
        vline3->SetLineStyle(2);
        vline1->SetLineWidth(2);
        vline2->SetLineWidth(2);
        vline3->SetLineWidth(2);
        vline1->Draw();
        vline2->Draw();
        vline3->Draw();

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
        nominal->GetXaxis()->SetTitle("m_{T_{WW}} [GeV]");
	nominal->GetYaxis()->SetRangeUser(0.3,1.7);
        nominal->GetYaxis()->SetTitleOffset(0.35);
        nominal->GetYaxis()->SetTitleSize(0.16);
        nominal->GetYaxis()->SetNdivisions(303);
        nominal->GetXaxis()->SetLabelSize(0.16);
        nominal->GetYaxis()->SetLabelSize(0.16);
        nominal->GetXaxis()->SetLabelOffset(0.032);
        nominal->GetXaxis()->SetTitleSize(0.2);
        nominal->GetXaxis()->SetTitleOffset(1.05);
	for(Int_t i=1;i<=nominal->GetNbinsX();i++){ nominal->GetXaxis()->SetBinLabel(i,name[i-1]);}

	nominal->Draw("EP");
	h_up->Draw("same hist ][");
	h_down->Draw("same hist ][");

	fPads2->Update();
	c1->Print("./figs/hist_"+filename+"_"+type+tag+".pdf");

}
int unroll_test(){

	vector<TString> names={"plj"};
	for(int i=0;i<names.size();i++){
//		unroll_name(names[i],"18","");
		unroll_name(names[i],"17","");
	}
	return 0;
}
