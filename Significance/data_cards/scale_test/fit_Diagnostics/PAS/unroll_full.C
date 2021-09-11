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

void run(TString channel){
	setTDRStyle();
	TFile* fout = new TFile("aa_"+channel+".root","RECREATE");
	std::ostringstream strs;
	std::string lumivalue = strs.str();
	Double_t lumi=137.1;

        TFile*f1=new TFile("./hist_fit16.root");
        TFile*f2=new TFile("./hist_fit17.root");
        TFile*f3=new TFile("./hist_fit18.root");

        TH1F*th2_ZA  =(TH1F*)f1->Get("hist_QCD_"+channel);
        TH1F*th2_ZA17=(TH1F*)f2->Get("hist_QCD_"+channel);
        TH1F*th2_ZA18=(TH1F*)f3->Get("hist_QCD_"+channel);
        th2_ZA->Add(th2_ZA17,1);
        th2_ZA->Add(th2_ZA18,1);
	cout<<th2_ZA->GetSum()<<endl;

	th2_ZA->SetFillColor(kBlue-6);
	th2_ZA->SetMarkerColor(kBlue-6);
	th2_ZA->SetLineColor(kBlue-6);

//	const char *name[7]={"0.5-0.8","0.8-1.2","1.2-2","0.5-0.8","0.8-1.2","1.2-2","0.5-2"};
	const char *name[7]={"0.5-0.8","0.8-1.2","1.2-#infty ","0.5-0.8","0.8-1.2","1.2-#infty","0.5-#infty"};

        TH1F*th2_ZA_sig  =(TH1F*)f1->Get("hist_Sig_"+channel);
        TH1F*th2_ZA_sig17=(TH1F*)f2->Get("hist_Sig_"+channel);
        TH1F*th2_ZA_sig18=(TH1F*)f3->Get("hist_Sig_"+channel);
        th2_ZA_sig->Add(th2_ZA_sig17,1);
        th2_ZA_sig->Add(th2_ZA_sig18,1);

	th2_ZA_sig->SetFillColor(kRed-7);
	th2_ZA_sig->SetMarkerColor(kRed-7);
        th2_ZA_sig->SetLineColor(kRed-7);
	th2_ZA_sig->SetMarkerStyle(21);

        TH1F* th2_VV  =(TH1F*)f1->Get("hist_VV_"+channel);
        TH1F* th2_VV17=(TH1F*)f2->Get("hist_VV_"+channel);
        TH1F* th2_VV18=(TH1F*)f3->Get("hist_VV_"+channel);
        th2_VV->Add(th2_VV17,1);
        th2_VV->Add(th2_VV18,1);

	th2_VV->SetFillColor(40);
	th2_VV->SetMarkerColor(40);
        th2_VV->SetLineColor(40);

        TH1F* th2_TTA  =(TH1F*)f1->Get("hist_TTA_"+channel);
        TH1F* th2_TTA17=(TH1F*)f2->Get("hist_TTA_"+channel);
        TH1F* th2_TTA18=(TH1F*)f3->Get("hist_TTA_"+channel);

        th2_TTA->Add(th2_TTA17,1);
        th2_TTA->Add(th2_TTA18,1);

	th2_TTA->SetFillColor(kCyan);
	th2_TTA->SetMarkerColor(kCyan);
        th2_TTA->SetLineColor(kCyan);

        TH1F* th2_ST  =(TH1F*)f1->Get("hist_ST_"+channel);
        TH1F* th2_ST17=(TH1F*)f2->Get("hist_ST_"+channel);
        TH1F* th2_ST18=(TH1F*)f3->Get("hist_ST_"+channel);
        th2_ST->Add(th2_ST17,1);
        th2_ST->Add(th2_ST18,1);

	th2_ST->SetFillColor(kGreen+2);
	th2_ST->SetMarkerColor(kGreen+2);
        th2_ST->SetLineColor(kGreen+2);

        TH1F* th2_plj  =(TH1F*)f1->Get("hist_non_prompt_"+channel);
        TH1F* th2_plj17=(TH1F*)f2->Get("hist_non_prompt_"+channel);
        TH1F* th2_plj18=(TH1F*)f3->Get("hist_non_prompt_"+channel);
        th2_plj->Add(th2_plj17,1);
        th2_plj->Add(th2_plj18,1);

	th2_plj->SetFillColor(kYellow-7);
	th2_plj->SetMarkerColor(kYellow-7);
        th2_plj->SetLineColor(kYellow-7);

	THStack* hs = new THStack("hs", "");
	hs->Add(th2_ST);
	hs->Add(th2_TTA);
	hs->Add(th2_VV);
	hs->Add(th2_plj);
	hs->Add(th2_ZA);
	hs->Add(th2_ZA_sig);
        TH1F*htot  =(TH1F*)f1->Get("hist_total_"+channel);
        TH1F*htot17=(TH1F*)f2->Get("hist_total_"+channel);
        TH1F*htot18=(TH1F*)f3->Get("hist_total_"+channel);
	htot->Add(htot17,1);
	htot->Add(htot18,1);
        TGraphAsymmErrors*gr16=(TGraphAsymmErrors*)f1->Get("data_"+channel);
        TGraphAsymmErrors*gr17=(TGraphAsymmErrors*)f2->Get("data_"+channel);
        TGraphAsymmErrors*gr18=(TGraphAsymmErrors*)f3->Get("data_"+channel);
	double x[7],x_up[7],x_down[7],y_up[7],y_down[7];
	double y16[7],y17[7],y18[7],y[7];
	for(int i=0;i<gr16->GetN();i++) {
                y16[i]=0;y17[i]=0;y18[i]=0;y[i]=0;
		gr16->GetPoint(i,x[i],y16[i]);
		gr17->GetPoint(i,x[i],y17[i]);
		gr18->GetPoint(i,x[i],y18[i]);
                x_up[i]=gr16->GetErrorXhigh(i);
                x_down[i]=gr16->GetErrorXlow(i);
                y[i]=(y16[i]+y17[i]+y18[i]);
                y_up[i]=sqrt( pow(gr16->GetErrorYhigh(i),2) + pow(gr17->GetErrorYhigh(i),2) + pow(gr18->GetErrorYhigh(i),2) );
                y_down[i]=sqrt( pow(gr16->GetErrorYlow(i),2) + pow(gr17->GetErrorYlow(i),2) + pow(gr18->GetErrorYlow(i),2) );
                
	}
	TGraphAsymmErrors*gr1=new TGraphAsymmErrors(gr16->GetN(),x,y,x_down,x_up,y_down,y_up);
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

//      TLine* line = new TLine(th2_ZA->GetXaxis()->GetXmin(),0,th2_ZA->GetXaxis()->GetXmax(),0);
	TCanvas* c1=new TCanvas("","",800,600);
        TPad*    fPads1 = new TPad("pad1", "", 0.00, 0.3, 0.99, 0.99);
        TPad*    fPads2 = new TPad("pad2", "", 0.00, 0.00, 0.99, 0.3);
        fPads1->SetBottomMargin(0);
        fPads2->SetTopMargin(0);
        fPads2->SetBottomMargin(0.5);
        fPads1->Draw();
        fPads2->Draw();
        fPads1->cd();
//        fPads1->SetGridx();
        fPads2->SetGridy();
        double max=hs->GetMaximum();
        hs->SetMaximum(max*2.);
	hs->Draw("HIST");
        gr1->SetMarkerStyle(20);
        gr1->SetMarkerColor(1);
        gr1->SetLineColor(1);
        gr1->SetMarkerSize(1.2);
        gr1->Draw("EP same");
        htot->SetFillColor(1);
        htot->SetLineColor(0);
        htot->SetMarkerSize(0);
        htot->SetFillStyle(3005);
        htot->Draw("E2 same");
	hs->GetYaxis()->SetTitleOffset(0.8);
	hs->GetYaxis()->SetTitle("Events /bin");
	TLegend* leg = new TLegend(0.62, 0.6, 0.85, 0.9);
	TLegend* leg1 = new TLegend(0.4, 0.6, 0.62, 0.9);
	TLegend* leg2 = new TLegend(0.2, 0.8, 0.39, 0.9);
	leg->SetTextSize(0.04);
        leg1->SetFillColor(kWhite);
	leg1->SetTextSize(0.04);
	leg2->SetTextSize(0.04);
//	leg->AddEntry(th2_ZA_sig,Form("EWK[%.1f] ",th2_ZA_sig->GetSum()) );
//	leg->AddEntry(th2_ZA, Form("Z#gamma [%.1f] ",th2_ZA->GetSum()));
//	leg->AddEntry(th2_plj, Form("non-prompt [%.1f] ",th2_plj->GetSum() ),"f");
//	leg1->AddEntry(th2_VV, Form("VV  [%.1f] ", th2_VV->GetSum() ) );
//	leg1->AddEntry(th2_TTA, Form("TT#gamma [%.1f] ",th2_TTA->GetSum()) );
//	leg1->AddEntry(th2_ST, Form("ST  [%.1f] ",th2_ST->GetSum() ) );
	leg->AddEntry(th2_ZA_sig,"EWK" );
	leg->AddEntry(th2_ZA,    "Z#gamma");
	leg->AddEntry(th2_plj,   "non-prompt","f");
	leg1->AddEntry(th2_VV,   "VV");
	leg1->AddEntry(th2_TTA,  "TT#gamma");
	leg1->AddEntry(th2_ST,   "ST");
        leg2->AddEntry(htot,"Stat #oplus Syst");
	leg->Draw();
	leg1->Draw();
	leg2->Draw();
////
        TLatex latex;
        latex.SetTextSize(0.06);
        latex.SetLineWidth(2);
        latex.DrawLatex(1.4,1*max,"2.5<|#Delta#eta_{jj}|<4.5");
        latex.DrawLatex(4.2,1*max,"4.5<|#Delta#eta_{jj}|<6");
        latex.DrawLatex(6.1,1*max,"|#Delta#eta_{jj}|>6");
        TLine* vline1 = new TLine(htot->GetBinLowEdge(4),0,htot->GetBinLowEdge(4),max*2);
        TLine* vline2 = new TLine(htot->GetBinLowEdge(7),0,htot->GetBinLowEdge(7),max*2);
        vline1->SetLineStyle(2);
        vline2->SetLineStyle(2);
        vline1->SetLineWidth(2);
        vline2->SetLineWidth(2);
        vline1->Draw();
        vline2->Draw();

	CMS_lumi(fPads1, 4, 0, "137.1");
//	cmsLumi(0);
        fPads1->Update();
        fPads2->cd();
        TH1F*nominal=(TH1F*)htot->Clone("nominal");
        TH1F*nomNoErr=(TH1F*)nominal->Clone("nomNoErr");
        for (int i = 1; i<= nomNoErr->GetNbinsX(); ++i){nomNoErr->SetBinError(i,0);}

	for(int i=0;i<gr16->GetN();i++){
                y16[i]=0;y17[i]=0;y18[i]=0;y[i]=0;
		gr16->GetPoint(i,x[i],y16[i]);
		gr17->GetPoint(i,x[i],y17[i]);
		gr18->GetPoint(i,x[i],y18[i]);
                x_up[i]=gr16->GetErrorXhigh(i);
                x_down[i]=gr16->GetErrorXlow(i);
                y[i]=(y16[i]+y17[i]+y18[i])/nominal->GetBinContent(i+1);
                y_up[i]=sqrt( pow(gr16->GetErrorYhigh(i),2) + pow(gr17->GetErrorYhigh(i),2) + pow(gr18->GetErrorYhigh(i),2) )/nominal->GetBinContent(i+1);
                y_down[i]=sqrt( pow(gr16->GetErrorYlow(i),2) + pow(gr17->GetErrorYlow(i),2) + pow(gr18->GetErrorYlow(i),2) )/nominal->GetBinContent(i+1);
                
	}
        TGraphAsymmErrors*gr=new TGraphAsymmErrors(gr16->GetN(),x,y,x_down,x_up,y_down,y_up);
        nominal->Divide(nomNoErr);
        nominal->GetYaxis()->SetRangeUser(0.5,1.8);
        if(channel.Contains("eleendcap"))
		nominal->GetYaxis()->SetRangeUser(0.5,2.8);
        nominal->SetLineColor(2);
        nominal->SetTitle(";m_{jj} [TeV];Data/MC;");
	nominal->GetYaxis()->SetTitleOffset(0.3);
	nominal->GetYaxis()->SetTitleSize(0.15);
	nominal->GetYaxis()->SetNdivisions(404);
	nominal->GetYaxis()->SetLabelSize(0.15);
	nominal->GetXaxis()->SetLabelSize(0.23);
        nominal->GetXaxis()->SetLabelOffset(0.032);
	nominal->GetXaxis()->SetTitleSize(0.2);
        nominal->GetXaxis()->SetTitleOffset(1.1);
	for(Int_t i=1;i<=nominal->GetNbinsX();i++){ nominal->GetXaxis()->SetBinLabel(i,name[i-1]);}

        nominal->Draw("E2");
        gr->SetMarkerStyle(20);
        gr->SetMarkerColor(1);
        gr->SetLineColor(1);
        gr->SetMarkerSize(1.2);
        gr->Draw("EP same");
        fPads2->Update();

	fout->cd();
	hs->Write();
	fout->Close();

	c1->SaveAs("aa_"+channel+".pdf");
}
int unroll_full(){
       vector<TString> tags={"16","17","18"};
       vector<TString> channels={"mubarrel","muendcap","elebarrel","eleendcap"};
//       run("eleendcap");
       for(int i=0;i<channels.size();i++){
	       run(channels[i]);
       }
       return 0;

}
