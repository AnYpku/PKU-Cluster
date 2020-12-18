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

void cmsLumi(bool channel) 
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
        latex.DrawLatex(0.76,0.92,Form("137.1 fb^{-1} (%d TeV)", (beamcomenergytev)));
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


void unroll_run(TString channel){
	setTDRStyle();
	TFile* fout = new TFile("aa_"+channel+".root","RECREATE");
	std::ostringstream strs;
	Double_t lumi=137.1;
	Double_t mjj_bins[4]={500, 800, 1200, 2000};
        Double_t detajj_bins[4]={2.5,4.5,6,6.5};

	TFile* f_ZA=TFile::Open("../root/hist_ZA_16"+channel+".root");
	TFile* f_ZA17=TFile::Open("../root/hist_ZA_17"+channel+".root");
	TFile* f_ZA18=TFile::Open("../root/hist_ZA_18"+channel+".root");
	TH1D* th2_ZA16=(TH1D*)f_ZA->Get("hist_bkg");
	TH1D* th2_ZA17=(TH1D*)f_ZA17->Get("hist_bkg");
	TH1D* th2_ZA18=(TH1D*)f_ZA18->Get("hist_bkg");
        th2_ZA16->Add(th2_ZA17,1);
        th2_ZA16->Add(th2_ZA18,1);
        TH1D* th2_ZA= unroll(th2_ZA16,"t_ZA");
	cout<<th2_ZA->GetSum()<<endl;
        cout<<th2_ZA->GetSumOfWeights()<<endl;
        cout<<th2_ZA->Integral()<<endl;

	th2_ZA->SetFillColor(kBlue-6);
	th2_ZA->SetMarkerColor(kBlue-6);
	th2_ZA->SetLineColor(kBlue-6);
//	th2_ZA->Scale(lumi*ZA_scale);
	const char *name[7]={"500~800","800~1200","1200~2000","500~800","800~1200","1200~2000","500~2000"};

	TFile* f_ZA_sig=TFile::Open("../root/hist_ZA-EWK_16"+channel+".root");
	TFile* f_ZA_sig17=TFile::Open("../root/hist_ZA-EWK_17"+channel+".root");
	TFile* f_ZA_sig18=TFile::Open("../root/hist_ZA-EWK_18"+channel+".root");
        TH1D* th2_ZA_sig16=(TH1D*)f_ZA_sig->Get("hist_sig");
        TH1D* th2_ZA_sig17=(TH1D*)f_ZA_sig17->Get("hist_sig");
        TH1D* th2_ZA_sig18=(TH1D*)f_ZA_sig18->Get("hist_sig");
        th2_ZA_sig16->Add(th2_ZA_sig17,1);
        th2_ZA_sig16->Add(th2_ZA_sig18,1);
        TH1D* th2_ZA_sig= unroll(th2_ZA_sig16,"t_ZA_sig");

	th2_ZA_sig->SetFillColor(kRed-7);
	th2_ZA_sig->SetMarkerColor(kRed-7);
        th2_ZA_sig->SetLineColor(kRed-7);
//	th2_ZA_sig->Scale(lumi);
	th2_ZA_sig->SetMarkerStyle(21);

	TH1D* th2_ZA_sigout16=(TH1D*)f_ZA_sig->Get("hist_sigout");
	TH1D* th2_ZA_sigout17=(TH1D*)f_ZA_sig17->Get("hist_sigout");
	TH1D* th2_ZA_sigout18=(TH1D*)f_ZA_sig18->Get("hist_sigout");
        th2_ZA_sigout16->Add(th2_ZA_sigout17,1);
        th2_ZA_sigout16->Add(th2_ZA_sigout18,1);
        TH1D* th2_ZA_sigout= unroll(th2_ZA_sigout16,"t_ZA_sigout");
        cout<<"EWK out yields "<<th2_ZA_sigout->GetBinContent(1)<<" "<<th2_ZA_sigout->GetBinContent(2)<<" "<<th2_ZA_sigout->GetBinContent(3)<<endl;
	th2_ZA_sigout->SetFillColor(kMagenta);
	th2_ZA_sigout->SetMarkerColor(kMagenta);
	th2_ZA_sigout->SetLineColor(kMagenta);
//	th2_ZA_sigout->Scale(lumi);
	th2_ZA_sigout->SetMarkerStyle(21);

	TFile* f_VV=TFile::Open("../root/hist_VV_16"+channel+".root");
	TFile* f_VV17=TFile::Open("../root/hist_VV_17"+channel+".root");
	TFile* f_VV18=TFile::Open("../root/hist_VV_18"+channel+".root");
	TH1D* th2_VV16=(TH1D*)f_VV->Get("hist_bkg");
	TH1D* th2_VV17=(TH1D*)f_VV17->Get("hist_bkg");
	TH1D* th2_VV18=(TH1D*)f_VV18->Get("hist_bkg");
	th2_VV16->Add(th2_VV17,1);
	th2_VV16->Add(th2_VV18,1);
	TH1D* th2_VV= unroll(th2_VV16,"t_VV");
	th2_VV->SetFillColor(40);
	th2_VV->SetMarkerColor(40);
	th2_VV->SetLineColor(40);
	//	th2_VV->Scale(lumi);

	TFile* f_TTA=TFile::Open("../root/hist_TTA_16"+channel+".root");
	TFile* f_TTA17=TFile::Open("../root/hist_TTA_17"+channel+".root");
	TFile* f_TTA18=TFile::Open("../root/hist_TTA_18"+channel+".root");
	TH1D* th2_TTA16=(TH1D*)f_TTA->Get("hist_bkg");
	TH1D* th2_TTA17=(TH1D*)f_TTA17->Get("hist_bkg");
	TH1D* th2_TTA18=(TH1D*)f_TTA18->Get("hist_bkg");

	th2_TTA16->Add(th2_TTA17,1);
	th2_TTA16->Add(th2_TTA18,1);
	TH1D* th2_TTA= unroll(th2_TTA16,"t_TTA");
	th2_TTA->SetFillColor(kCyan);
	th2_TTA->SetMarkerColor(kCyan);
	th2_TTA->SetLineColor(kCyan);
	//	th2_TTA->Scale(lumi);

	TFile* f_ST=TFile::Open("../root/hist_ST_16"+channel+".root");
	TFile* f_ST17=TFile::Open("../root/hist_ST_17"+channel+".root");
	TFile* f_ST18=TFile::Open("../root/hist_ST_18"+channel+".root");
	TH1D* th2_ST16=(TH1D*)f_ST->Get("hist_bkg");
	TH1D* th2_ST17=(TH1D*)f_ST17->Get("hist_bkg");
	TH1D* th2_ST18=(TH1D*)f_ST18->Get("hist_bkg");
	th2_ST16->Add(th2_ST17,1);
	th2_ST16->Add(th2_ST18,1);
	TH1D* th2_ST= unroll(th2_ST16,"t_ST");
	th2_ST->SetFillColor(kGreen+2);
	th2_ST->SetMarkerColor(kGreen+2);
	th2_ST->SetLineColor(kGreen+2);
	//	th2_ST->Scale(lumi);
	for(Int_t i=1;i<=th2_ST->GetNbinsX();i++){ th2_ST->GetXaxis()->SetBinLabel(i,name[i-1]);}

	TFile* f_plj=TFile::Open("../root/hist_plj_16"+channel+".root");
	TFile* f_plj17=TFile::Open("../root/hist_plj_17"+channel+".root");
	TFile* f_plj18=TFile::Open("../root/hist_plj_18"+channel+".root");
	TH1D* th2_plj16=(TH1D*)f_plj->Get("hist_bkg");
	TH1D* th2_plj17=(TH1D*)f_plj17->Get("hist_bkg");
	TH1D* th2_plj18=(TH1D*)f_plj18->Get("hist_bkg");
	th2_plj16->Add(th2_plj17,1);
	th2_plj16->Add(th2_plj18,1);
	TH1D* th2_plj= unroll(th2_plj16,"t_plj");
	th2_plj->SetFillColor(kYellow-7);
	th2_plj->SetMarkerColor(kYellow-7);
	th2_plj->SetLineColor(kYellow-7);

	THStack* hs = new THStack("hs", "");
	hs->Add(th2_ST);
	hs->Add(th2_TTA);
	hs->Add(th2_VV);
	hs->Add(th2_plj);
	hs->Add(th2_ZA);
	hs->Add(th2_ZA_sigout);
	hs->Add(th2_ZA_sig);

	TH1D*htot=(TH1D*)th2_ST->Clone();
	htot->Add(th2_TTA,1);
	htot->Add(th2_VV,1);
	htot->Add(th2_plj,1);
	htot->Add(th2_ZA,1);
	htot->Add(th2_ZA_sig,1);
	htot->Add(th2_ZA_sigout,1);
	for(int i=0;i<htot->GetNbinsX();i++){
		htot->SetBinError(i+1,sqrt( th2_TTA->GetBinError(i+1)*th2_TTA->GetBinError(i+1)+th2_VV->GetBinError(i+1)*th2_VV->GetBinError(i+1)+th2_plj->GetBinError(i+1)*th2_plj->GetBinError(i+1)+th2_ZA->GetBinError(i+1)*th2_ZA->GetBinError(i+1)+th2_ZA_sig->GetBinError(i+1)*th2_ZA_sig->GetBinError(i+1)+th2_ZA_sigout->GetBinError(i+1)*th2_ZA_sigout->GetBinError(i+1) ));
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
	fPads1->SetBottomMargin(0);
	fPads2->SetTopMargin(0);
	fPads2->SetBottomMargin(0.5);
	fPads1->Draw();
	fPads2->Draw();
	fPads1->cd();
	fPads1->SetGridx();
	fPads2->SetGridy();
	double max=hs->GetMaximum();
	hs->SetMaximum(max*1.6);
	hs->Draw("HIST");
	htot->SetFillColor(1);
	htot->SetLineColor(0);
	htot->SetMarkerSize(0);
	htot->SetFillStyle(3005);
	htot->Draw("E2 same");
	hs->GetYaxis()->SetTitleOffset(0.8);
	hs->GetYaxis()->SetTitle("Events /bin");
	TLegend* leg1 = new TLegend(0.42, 0.6, 0.65, 0.9);
	leg1->SetTextSize(0.05);
        leg1->SetFillColor(kWhite);
	leg1->AddEntry(th2_ZA_sig,Form("EWK [%.1f]",th2_ZA_sig->GetSum()),"f" );
	leg1->AddEntry(th2_ZA_sigout,Form("EWK_{out} [%.1f]",th2_ZA_sigout->GetSum()),"f" );
	leg1->AddEntry(th2_ZA, Form("ZA [%.1f]",th2_ZA->GetSum()),"f");
	leg1->AddEntry(th2_plj, Form("non-prompt [%.1f]",th2_plj->GetSum() ),"f");
	leg1->Draw();
	TLegend* leg = new  TLegend(0.72, 0.6, 0.95, 0.9);
	leg->SetTextSize(0.05);
        leg->SetFillColor(kWhite);
	leg->AddEntry(th2_VV, Form("VV [%.1f]", th2_VV->GetSum() ), "f");
	leg->AddEntry(th2_TTA, Form("TTA [%.1f]",th2_TTA->GetSum()),"f" );
	leg->AddEntry(th2_ST, Form("ST  [%.1f]",th2_ST->GetSum() ) ,"f");
	TLegend* leg2 = new TLegend(0.2, 0.8, 0.39, 0.9);
	leg2->AddEntry(htot," MC stat");
        leg2->Draw();
	leg->Draw();
	////
	TLatex latex;
	latex.SetTextSize(0.08);
	latex.SetLineWidth(2);
	latex.DrawLatex(1.1,0.8*max,"2.5<#Delta#eta_{jj}<4.5");
	latex.DrawLatex(4.2,0.8*max,"4.5<#Delta#eta_{jj}<6");
	latex.DrawLatex(6.1,0.8*max,"#Delta#eta_{jj}>6");
	TLine* vline1 = new TLine(htot->GetBinLowEdge(4),0,htot->GetBinLowEdge(4),max*1.5);
	TLine* vline2 = new TLine(htot->GetBinLowEdge(7),0,htot->GetBinLowEdge(7),max*1.5);
	vline1->SetLineStyle(2);
	vline2->SetLineStyle(2);
	vline1->SetLineWidth(2);
	vline2->SetLineWidth(2);
	vline1->Draw();
	vline2->Draw();
	//	
//	cmsLumi(0);
        string lumivalue;
//        if(tag.Contains("16")) lumivalue="35.86";
//        if(tag.Contains("17")) lumivalue="41.52";
//        if(tag.Contains("18")) lumivalue="59.7";
        CMS_lumi(fPads1, 4, 0, "137.1");
	fPads1->Update();
	fPads2->cd();
	TH1D*nominal=(TH1D*)htot->Clone("nominal");
	TH1D*nomNoErr=(TH1D*)nominal->Clone("nomNoErr");
	for (int i = 1; i<= nomNoErr->GetNbinsX(); ++i){nomNoErr->SetBinError(i,0);}
	TH1D*h_up=(TH1D*)htot->Clone();
	h_up->Divide(nominal);
	nominal->Divide(nomNoErr);
	nominal->GetYaxis()->SetRangeUser(0,2);
	nominal->SetLineColor(2);
	nominal->SetTitle(";m_{jj} [GeV];Data/MC;");
        nominal->GetYaxis()->SetTitleOffset(0.23);
        nominal->GetYaxis()->SetTitleSize(0.2);
        nominal->GetYaxis()->SetNdivisions(404);
	nominal->GetYaxis()->SetLabelSize(0.15);
	nominal->GetXaxis()->SetLabelSize(0.17);
	nominal->GetXaxis()->SetTitleSize(0.2);
	nominal->Draw("E2");
	h_up->SetMarkerStyle(20);
	h_up->SetMarkerColor(1);
	h_up->SetLineColor(2);
	h_up->SetMarkerSize(1.2);
	h_up->Draw("EP same");
	fPads2->Update();

	fout->cd();
	hs->Write();
	fout->Close();

	c1->SaveAs("aa_"+channel+".pdf");
}
int unroll_full(){
	vector<TString> tags={"16","17","18"};
	vector<TString> channels={"mubarrel","muendcap","elebarrel","eleendcap"};
	for(int i=0;i<channels.size();i++){
		unroll_run(channels[i]);
	}
	return 0;

}
