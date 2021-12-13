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


void unroll_run(TString tag,TString var,TString njets,vector<double> bins1,vector<double> bins2){
	setTDRStyle();
	TFile* f_ZA=TFile::Open("../root/hist_1D_ZGJets_"+var+"_"+njets+"_"+tag+".root");
	TH1D* th2_ZA16=(TH1D*)f_ZA->Get("hist_bkg");
        TH1D* th2_ZA= unroll(th2_ZA16,"t_ZA");

	TFile* f_WA=TFile::Open("../root/hist_1D_WGJets_"+var+"_"+njets+"_"+tag+".root");
	TH1D* th2_WA16=(TH1D*)f_WA->Get("hist_bkg");
        TH1D* th2_WA= unroll(th2_WA16,"t_WA");

        th2_ZA->Add(th2_WA,1);      

	cout<<th2_ZA->GetSum()<<endl;
        cout<<th2_ZA->GetSumOfWeights()<<endl;
        cout<<th2_ZA->Integral()<<endl;

	th2_ZA->SetFillColor(kYellow-7);
	th2_ZA->SetMarkerColor(kYellow-7);
	th2_ZA->SetLineColor(kYellow-7);
	const int n=bins1.size()*bins2.size();
	const char *name[n];
	for(int i=0;i<(bins1.size()-1)*(bins2.size()-1);i++){
		if(i<bins1.size()-1){
			if(i<bins1.size()-2) name[i]=Form("%.0f-%.0f",bins1[i],bins1[i+1]);
			else  name[i]=Form("%.0f-#infty",bins1[i]);
		}
		else{
			name[i]=name[i-(bins1.size()-1)];
		}
		cout<<i<<" "<<name[i]<<endl;
	}
//	const char *name[16]={"60-100","100-115","115-135","135-#infty","60-100","100-115","115-135","135-#infty","60-100","100-115","115-135","135-#infty","60-100","100-115","115-135","135-#infty"};

	TFile* f_WWG=TFile::Open("../root/hist_1D_WWG_emu_"+var+"_"+njets+"_"+tag+".root");
        TH1D* th2_WWG16=(TH1D*)f_WWG->Get("hist_bkg");
        TH1D* th2_WWG= unroll(th2_WWG16,"t_WWG_emu");
	cout<<"open WWG_emu"<<endl;

	th2_WWG->SetFillColor(kRed-7);
	th2_WWG->SetMarkerColor(kRed-7);
        th2_WWG->SetLineColor(kRed-7);
	th2_WWG->SetMarkerStyle(21);

	TFile* f_HGC_sig=TFile::Open("../root/hist_1D_HGC_"+var+"_"+njets+"_"+tag+".root");
        TH1D* th2_HGC16=(TH1D*)f_HGC_sig->Get("hist_sig");
        TH1D* th2_HGC= unroll(th2_HGC16,"t_HGC");
	cout<<"open HGC"<<endl;

	th2_HGC->SetFillColor(kMagenta);
	th2_HGC->SetMarkerColor(kMagenta);
        th2_HGC->SetLineColor(kMagenta);
	th2_HGC->SetMarkerStyle(21);

	TFile* f_VV=TFile::Open("../root/hist_1D_VV_"+var+"_"+njets+"_"+tag+".root");
        TH1D* th2_VV16=(TH1D*)f_VV->Get("hist_bkg");
        TH1D* th2_VV= unroll(th2_VV16,"t_VV");
	cout<<"open VV"<<endl;
	th2_VV->SetFillColor(kCyan);
	th2_VV->SetMarkerColor(kCyan);
        th2_VV->SetLineColor(kCyan);

	TFile* f_TTA=TFile::Open("../root/hist_1D_TTGJets_"+var+"_"+njets+"_"+tag+".root");
        TH1D* th2_TTA16=(TH1D*)f_TTA->Get("hist_bkg");
        TH1D* th2_TTA= unroll(th2_TTA16,"t_TTA");
	cout<<"open TTG"<<endl;
	th2_TTA->SetFillColor(kBlue);
	th2_TTA->SetMarkerColor(kBlue);
        th2_TTA->SetLineColor(kBlue);

	TFile* f_ST=TFile::Open("../root/hist_1D_ST_"+var+"_"+njets+"_"+tag+".root");
        TH1D* th2_ST16=(TH1D*)f_ST->Get("hist_bkg");
        TH1D* th2_ST= unroll(th2_ST16,"t_ST");
	cout<<"open ST"<<endl;
	th2_ST->SetFillColor(40);
	th2_ST->SetMarkerColor(40);
        th2_ST->SetLineColor(40);
	for(Int_t i=1;i<=th2_ST->GetNbinsX();i++){ th2_ST->GetXaxis()->SetBinLabel(i,name[i-1]);}

	TFile* f_plj=TFile::Open("../root/hist_1D_plj_"+var+"_"+njets+"_"+tag+".root");
        TH1D* th2_plj16=(TH1D*)f_plj->Get("hist_bkg");
        TH1D* th2_plj= unroll(th2_plj16,"t_plj");
	cout<<"open plj"<<endl;
	th2_plj->SetFillColor(kGreen+2);
	th2_plj->SetMarkerColor(kGreen+2);
        th2_plj->SetLineColor(kGreen+2);

	TFile* f_fakeL=TFile::Open("../root/hist_1D_fakeL_"+var+"_"+njets+"_"+tag+".root");
        TH1D* th2_fakeL16=(TH1D*)f_fakeL->Get("hist_bkg");
        TH1D* th2_fakeL= unroll(th2_fakeL16,"t_fakeL");
	cout<<"open fakeL"<<endl;
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
	hs->Add(th2_WWG);
	hs->Add(th2_HGC);
        TH1D*htot=(TH1D*)th2_ST->Clone();
	htot->Add(th2_TTA,1);
	htot->Add(th2_VV,1);
	htot->Add(th2_plj,1);
	htot->Add(th2_fakeL,1);
	htot->Add(th2_ZA,1);
	htot->Add(th2_WWG,1);
	htot->Add(th2_HGC,1);
	for(int i=0;i<htot->GetNbinsX();i++){
            htot->SetBinError(i+1,sqrt( th2_TTA->GetBinError(i+1)*th2_TTA->GetBinError(i+1)+th2_VV->GetBinError(i+1)*th2_VV->GetBinError(i+1)+th2_plj->GetBinError(i+1)*th2_plj->GetBinError(i+1)+th2_fakeL->GetBinError(i+1)*th2_fakeL->GetBinError(i+1)+th2_ZA->GetBinError(i+1)*th2_ZA->GetBinError(i+1)+th2_WWG->GetBinError(i+1)*th2_WWG->GetBinError(i+1) + th2_HGC->GetBinError(i+1)*th2_HGC->GetBinError(i+1) ));
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
	leg->AddEntry(th2_HGC,Form("H#gamma [%.1f]",th2_HGC->GetSum()) );
	leg->AddEntry(th2_WWG,Form("WW#gamma [%.1f]",th2_WWG->GetSum()) );
	leg->AddEntry(th2_ZA, Form("V#gamma [%.1f]",th2_ZA->GetSum()));
	leg->AddEntry(th2_plj, Form("Nonprompt #gamma [%.1f]",th2_plj->GetSum() ));
	leg->AddEntry(th2_fakeL, Form("Nonprompt #font[12]{l} [%.1f]",th2_fakeL->GetSum() ));
	leg1->AddEntry(th2_VV, Form("VV [%.1f]", th2_VV->GetSum() ) );
	leg1->AddEntry(th2_TTA, Form("t#bar{t}#gamma [%.1f]",th2_TTA->GetSum()) );
	leg1->AddEntry(th2_ST, Form("tW  [%.1f]",th2_ST->GetSum() ) );
//	leg->AddEntry(th2_HGC,"WWG");
//	leg->AddEntry(th2_WWG,"WWG");
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
        TString l_var;
	if(var=="ml1g") l_var="m_{#font[12]{l_{1}#gamma}}";
	if(var=="ml2g") l_var="m_{#font[12]{l_{2}#gamma}}";
	if(var=="mllg") l_var="m_{#font[12]{ll#gamma}}";
	for(int i=0;i<bins2.size()-1;i++){
		if(i<bins2.size()-2)
			latex.DrawLatex(i*(bins1.size()-1)+0.5,1.4*max,Form("%.0f<"+l_var+"<%.0f",bins2[i],bins2[i+1]));
		else
			latex.DrawLatex(i*(bins1.size()-1)+0.5,1.4*max,Form(l_var+">%.0f",bins2[i]));
	}
        TLine* vline1 = new TLine(htot->GetBinLowEdge(bins1.size()-1+1),0,htot->GetBinLowEdge(bins1.size()-1+1),max*1.5);
        TLine* vline2 = new TLine(htot->GetBinLowEdge(2*(bins1.size()-1)+1),0,htot->GetBinLowEdge(2*(bins1.size()-1)+1),max*1.5);
        TLine* vline3 = new TLine(htot->GetBinLowEdge(3*(bins1.size()-1)+1),0,htot->GetBinLowEdge(3*(bins1.size()-1)+1),max*1.5);
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
        h_up->Divide(nomNoErr);
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

	c1->Print("aa_"+var+"_"+njets+"_"+tag+".pdf");
}
int unroll_1Dtest(){
       vector<TString> tags={"16","17","18"};
       vector<TString> var={"mT"};
       vector<TString> njets={"0jets","1jets"};
       vector<Double_t> mT_bins;
       vector<vector<Double_t>> bins2;
       vector<Double_t> drll_bins={0.5,0.8,1.2,1.5,2.3};
       bins2.push_back(drll_bins);

       for(int j=2;j<tags.size();j++){
	       for(int i=0;i<var.size();i++){
		       for(int k=0;k<njets.size();k++){
			       if(njets[k]=="0jets") mT_bins={50,75,90,110,200};
			       else if(njets[k]=="1jets") mT_bins={50,75,90,110,200};
			       unroll_run(tags[j],var[i],njets[k],mT_bins,bins2[i]);
			       unroll_run(tags[j],var[i],njets[k],mT_bins,bins2[i]);
		       }
	       }
       }
       return 0;

}
