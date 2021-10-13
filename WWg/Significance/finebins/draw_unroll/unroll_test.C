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

void cmsLumi(TString tag) 
{
        TLatex latex;
        latex.SetNDC();
        latex.SetTextSize(0.04);
        latex.SetLineWidth(2);
        float lumiel=137.1;
        float lumimu=137.1;
        int beamcomenergytev=13;
        latex.SetTextAlign(31); 
        latex.SetTextAlign(11);
        latex.SetTextSize(0.06);
        latex.DrawLatex(0.18,0.82,"Preliminary");
        latex.DrawLatex(0.18,0.86,"CMS");
        latex.SetTextSize(0.06);
	if(tag.Contains("16"))
		latex.DrawLatex(0.76,0.92,Form("35.86 fb^{-1} (%d TeV)", (beamcomenergytev)));
	if(tag.Contains("17"))
		latex.DrawLatex(0.76,0.92,Form("41.52 fb^{-1} (%d TeV)", (beamcomenergytev)));
	if(tag.Contains("18"))
		latex.DrawLatex(0.76,0.92,Form("58.7 fb^{-1} (%d TeV)", (beamcomenergytev)));
}
TH1D* unroll(TH1D* h1,TString hname){
	int nbins=h1->GetNbinsX();
	TH1D* h1_out= new TH1D(hname, "", nbins, 0, nbins);
	for(Int_t i=0;i<nbins;i++){
		h1_out->SetBinContent(i+1,h1->GetBinContent(i+1));
		h1_out->SetBinError(i+1,h1->GetBinError(i+1));
	}
	return h1_out;
}


void unroll_run(TString tag){
	setTDRStyle();
	TFile* fout = new TFile("aa_"+tag+".root","RECREATE");

	TFile* f_ZA=TFile::Open("../root/hist_ZGJets_"+tag+".root");
	TH1D* th2_ZA16=(TH1D*)f_ZA->Get("hist_bkg");
        TH1D* th2_ZA= unroll(th2_ZA16,"t_ZA");

	TFile* f_WA=TFile::Open("../root/hist_WGJets_"+tag+".root");
	TH1D* th2_WA16=(TH1D*)f_WA->Get("hist_bkg");
        TH1D* th2_WA= unroll(th2_WA16,"t_WA");

        th2_ZA->Add(th2_WA,1);      

	cout<<th2_ZA->GetSum()<<endl;
        cout<<th2_ZA->GetSumOfWeights()<<endl;
        cout<<th2_ZA->Integral()<<endl;

	th2_ZA->SetFillColor(kYellow-7);
	th2_ZA->SetMarkerColor(kYellow-7);
	th2_ZA->SetLineColor(kYellow-7);
	const char *name[16]={"20-80","80-120","120-160","160-#infty","20-80","80-120","120-160","160-#infty","20-80","80-120","120-160","160-#infty","20-80","80-120","120-160","160-#infty"};

	TFile* f_ZA_sig=TFile::Open("../root/hist_WWG_emu_"+tag+".root");
        TH1D* th2_ZA_sig16=(TH1D*)f_ZA_sig->Get("hist_sig");
        TH1D* th2_ZA_sig= unroll(th2_ZA_sig16,"t_ZA_sig");

	th2_ZA_sig->SetFillColor(kRed-7);
	th2_ZA_sig->SetMarkerColor(kRed-7);
        th2_ZA_sig->SetLineColor(kRed-7);
	th2_ZA_sig->SetMarkerStyle(21);


	TFile* f_VV=TFile::Open("../root/hist_VV_"+tag+".root");
        TH1D* th2_VV16=(TH1D*)f_VV->Get("hist_bkg");
        TH1D* th2_VV= unroll(th2_VV16,"t_VV");
	th2_VV->SetFillColor(kCyan);
	th2_VV->SetMarkerColor(kCyan);
        th2_VV->SetLineColor(kCyan);

	TFile* f_TTA=TFile::Open("../root/hist_TTGJets_"+tag+".root");
        TH1D* th2_TTA16=(TH1D*)f_TTA->Get("hist_bkg");

        TH1D* th2_TTA= unroll(th2_TTA16,"t_TTA");
	th2_TTA->SetFillColor(kBlue);
	th2_TTA->SetMarkerColor(kBlue);
        th2_TTA->SetLineColor(kBlue);

	TFile* f_ST=TFile::Open("../root/hist_ST_"+tag+".root");
        TH1D* th2_ST16=(TH1D*)f_ST->Get("hist_bkg");
        TH1D* th2_ST= unroll(th2_ST16,"t_ST");
	th2_ST->SetFillColor(40);
	th2_ST->SetMarkerColor(40);
        th2_ST->SetLineColor(40);
//	for(Int_t i=1;i<=th2_ST->GetNbinsX();i++){ th2_ST->GetXaxis()->SetBinLabel(i,name[i-1]);}

	TFile* f_plj=TFile::Open("../root/hist_plj_"+tag+".root");
        TH1D* th2_plj16=(TH1D*)f_plj->Get("hist_bkg");
        TH1D* th2_plj= unroll(th2_plj16,"t_plj");
	th2_plj->SetFillColor(kGreen+2);
	th2_plj->SetMarkerColor(kGreen+2);
        th2_plj->SetLineColor(kGreen+2);

	TFile* f_fakeL=TFile::Open("../root/hist_fakeL_"+tag+".root");
        TH1D* th2_fakeL16=(TH1D*)f_fakeL->Get("hist_bkg");
        TH1D* th2_fakeL= unroll(th2_fakeL16,"t_fakeL");
	th2_fakeL->SetFillColor(kGreen-3);
	th2_fakeL->SetMarkerColor(kGreen-3);
        th2_fakeL->SetLineColor(kGreen-3);

	THStack* hs = new THStack("hs", "");
	hs->Add(th2_ST);
	hs->Add(th2_TTA);
	hs->Add(th2_VV);
	hs->Add(th2_plj);
	hs->Add(th2_fakeL);
	hs->Add(th2_ZA);
	hs->Add(th2_ZA_sig);
        TH1D*htot=(TH1D*)th2_ST->Clone();
	htot->Add(th2_TTA,1);
	htot->Add(th2_VV,1);
	htot->Add(th2_plj,1);
	htot->Add(th2_fakeL,1);
	htot->Add(th2_ZA,1);
	htot->Add(th2_ZA_sig,1);
	for(int i=0;i<htot->GetNbinsX();i++){
            htot->SetBinError(i+1,sqrt( th2_TTA->GetBinError(i+1)*th2_TTA->GetBinError(i+1)+th2_VV->GetBinError(i+1)*th2_VV->GetBinError(i+1)+th2_plj->GetBinError(i+1)*th2_plj->GetBinError(i+1)+th2_fakeL->GetBinError(i+1)*th2_fakeL->GetBinError(i+1)+th2_ZA->GetBinError(i+1)*th2_ZA->GetBinError(i+1)+th2_ZA_sig->GetBinError(i+1)*th2_ZA_sig->GetBinError(i+1) ));
	    cout<<htot->GetBinError(i+1)<<endl;
	}
        
	cout<<"create THStack"<<endl;
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
        fPads1->SetBottomMargin(0.028);
        fPads2->SetTopMargin(0.012);
        fPads2->SetBottomMargin(0.45);
        fPads1->Draw();
        fPads2->Draw();
        fPads1->cd();
        double max=hs->GetMaximum();
        hs->SetMaximum(max*3.2);
	hs->Draw("HIST");
        htot->SetFillColor(kMagenta+1);
        htot->SetLineColor(0);
        htot->SetMarkerSize(0);
        htot->SetFillStyle(3005);
        htot->Draw("E2 same");
        TH1D*h1_clone=(TH1D*)htot->Clone();
        h1_clone->SetMarkerColor(1);
        h1_clone->SetLineColor(1);
        h1_clone->SetMarkerStyle(20);
        h1_clone->SetMarkerSize(1.2);
        h1_clone->Draw("EP same");
	hs->GetYaxis()->SetTitleOffset(0.8);
	hs->GetYaxis()->SetTitle("Events /bin");
        hs->GetYaxis()->SetTitleSize(0.08);
        hs->GetYaxis()->SetLabelSize(0.07);
        hs->GetXaxis()->SetLabelSize(0.0);
        hs->GetYaxis()->SetNdivisions(505);
        TLegend* leg = new TLegend(0.2, 0.5, 0.4, 0.9);
        TLegend* leg1 = new TLegend(0.6, 0.5, 0.9, 0.9);
	leg->SetTextSize(0.04);
        leg->SetMargin(0.4);
	leg->AddEntry(th2_ZA_sig,Form("WW#gamma [%.1f]",th2_ZA_sig->GetSum()) );
	leg->AddEntry(th2_ZA, Form("V#gamma [%.1f]",th2_ZA->GetSum()));
	leg->AddEntry(th2_plj, Form("Nonprompt #gamma [%.1f]",th2_plj->GetSum() ));
	leg->AddEntry(th2_fakeL, Form("Nonprompt #font[12]{l} [%.1f]",th2_fakeL->GetSum() ));
	leg1->AddEntry(th2_VV, Form("VV [%.1f]", th2_VV->GetSum() ) );
	leg1->AddEntry(th2_TTA, Form("t#bar{t}#gamma [%.1f]",th2_TTA->GetSum()) );
	leg1->AddEntry(th2_ST, Form("tW  [%.1f]",th2_ST->GetSum() ) );
//	leg->AddEntry(th2_ZA_sig,"WWG");
//	leg->AddEntry(th2_ZA,"QCD Z#gamma");
//	leg->AddEntry(th2_plj,"Nonprompt #gamma");
//	leg->AddEntry(th2_fakeL,"Nonprompt #font[12]{l}");
//	leg1->AddEntry(th2_VV,"VV");
//	leg1->AddEntry(th2_TTA,"t#bar{t}#gamma");
//	leg1->AddEntry(th2_ST,"tW");
       
        leg1->AddEntry(htot," MC stat.");
        leg->SetTextSize(0.07);
        leg1->SetTextSize(0.07);
////
        TLatex latex;
        latex.SetTextSize(0.06);
        latex.SetLineWidth(2);
//        latex.DrawLatex(0.5,1.4*max,"20<m_{#font[12]{ll}}<80");
//        latex.DrawLatex(4.5,1.4*max,"80<m_{#font[12]{ll}}<140");
//        latex.DrawLatex(8.5,1.4*max,"m_{#font[12]{ll}}>140");
//        latex.DrawLatex(13, 1.4*max,"m_{#font[12]{ll}}>160");

	TH1D* h2_sig=(TH1D*)f_ZA_sig->Get("sig");
        double nx=h2_sig->GetNbinsX();
        double ny=h2_sig->GetNbinsY();
        TLine* vline1 = new TLine(htot->GetBinLowEdge(nx+1),0,htot->GetBinLowEdge(nx+1),max*1.5);
        TLine* vline2 = new TLine(htot->GetBinLowEdge(nx*2+1),0,htot->GetBinLowEdge(nx*2+1),max*1.5);
        TLine* vline3 = new TLine(htot->GetBinLowEdge(nx*3+1),0,htot->GetBinLowEdge(nx*3+1),max*1.5);
        vline1->SetLineStyle(2);
        vline2->SetLineStyle(2);
        vline3->SetLineStyle(2);
        vline1->SetLineWidth(2);
        vline2->SetLineWidth(2);
        vline3->SetLineWidth(2);
        vline1->Draw();
        vline2->Draw();
        vline3->Draw();
	leg->Draw();
        leg1->Draw();
//	
//	cmsLumi(tag);
        string lumivalue;
        if(tag.Contains("16")) lumivalue="35.86";
        if(tag.Contains("17")) lumivalue="41.52";
        if(tag.Contains("18")) lumivalue="59.7";
        CMS_lumi(fPads1, 4, 0, lumivalue);
        fPads1->Update();
        fPads2->cd();
        TH1D*nominal=(TH1D*)htot->Clone("nominal");
        TH1D*nomNoErr=(TH1D*)nominal->Clone("nomNoErr");
        for (int i = 1; i<= nomNoErr->GetNbinsX(); ++i){nomNoErr->SetBinError(i,0);}
        TH1D*h_up=(TH1D*)htot->Clone();
        h_up->Divide(nominal);
        nominal->Divide(nomNoErr);
        nominal->GetYaxis()->SetRangeUser(0.4,1.9);
        nominal->SetLineColor(2);
        nominal->SetTitle(";m^{WW}_{T} [GeV];Data/Pred.;");
        nominal->GetYaxis()->SetTitleOffset(0.35);
        nominal->GetYaxis()->SetTitleSize(0.16);
        nominal->GetYaxis()->SetNdivisions(303);
        nominal->GetXaxis()->SetLabelSize(0.13);
        nominal->GetYaxis()->SetLabelSize(0.16);
        nominal->GetXaxis()->SetLabelOffset(0.032);
        nominal->GetXaxis()->SetTitleSize(0.2);
        nominal->GetXaxis()->SetTitleOffset(1.05);

        nominal->Draw("E2");
        h_up->SetMarkerStyle(20);
        h_up->SetMarkerColor(1);
        h_up->SetLineColor(1);
        h_up->SetMarkerSize(1.2);
        h_up->Draw("EP same");
        fPads2->Update();

	fout->cd();
	hs->Write();
	fout->Close();

	c1->Print("aa_"+tag+".pdf");
}
int unroll_test(){
       vector<TString> tags={"16","17","18"};
       for(int j=0;j<3;j++){
//	       unroll_run(tags[j]);
       }
	       unroll_run("17");
	       unroll_run("18");
       return 0;

}
