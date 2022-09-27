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

void run(TString channel,TString tag){
	setTDRStyle();
	TFile* fout = new TFile("aa_"+channel+"CR.root","RECREATE");
	std::ostringstream strs;
	Double_t lumi=137.1;

        TFile*f1=new TFile("./hist_fit"+tag+"CR.root");
	TString par;
	if(channel.Contains("mu")) par="DMuon";
	else  par="DEle";
        TString ch;
	if(channel.Contains("mubarrel")) ch="mubarrel";
        else if(channel.Contains("elebarrel")) ch="elebarrel";
        else if(channel.Contains("eleendcap")) ch="eleendcap";
        else ch="muendcap";
        TFile*f2=new TFile("/home/pku/anying/cms/PKU-Cluster/SignalStrength/batch/CR/root/hist_"+par+"_"+tag+"CR_"+ch+".root");        
 
        TH1F*th2_ZA  =(TH1F*)f1->Get("hist_QCD_"+channel);

	th2_ZA->SetFillColor(kBlue-6);
	th2_ZA->SetMarkerColor(kBlue-6);
	th2_ZA->SetLineColor(kBlue-6);

	const char *name[3]={"150-300","300-400","400-500"};

        TH1F*th2_ZA_sig  =(TH1F*)f1->Get("hist_Sig_"+channel);

	th2_ZA_sig->SetFillColor(kRed-7);
	th2_ZA_sig->SetMarkerColor(kRed-7);
        th2_ZA_sig->SetLineColor(kRed-7);
	th2_ZA_sig->SetMarkerStyle(21);

        TH1F*th2_ZA_sigout  =(TH1F*)f1->Get("hist_Sig_out_"+channel);

	th2_ZA_sigout->SetFillColor(kMagenta);
	th2_ZA_sigout->SetMarkerColor(kMagenta);
        th2_ZA_sigout->SetLineColor(kMagenta);
	th2_ZA_sigout->SetMarkerStyle(21);

        TH1F* th2_VV  =(TH1F*)f1->Get("hist_VV_"+channel);

	th2_VV->SetFillColor(40);
	th2_VV->SetMarkerColor(40);
        th2_VV->SetLineColor(40);

        TH1F* th2_TTA  =(TH1F*)f1->Get("hist_TTA_"+channel);

	th2_TTA->SetFillColor(kCyan);
	th2_TTA->SetMarkerColor(kCyan);
        th2_TTA->SetLineColor(kCyan);

        TH1F* th2_ST  =(TH1F*)f1->Get("hist_ST_"+channel);

	th2_ST->SetFillColor(kGreen+2);
	th2_ST->SetMarkerColor(kGreen+2);
        th2_ST->SetLineColor(kGreen+2);

        TH1F* th2_plj  =(TH1F*)f1->Get("hist_non_prompt_"+channel);

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
	hs->Add(th2_ZA_sigout);
        TH1F*htot  =(TH1F*)f1->Get("hist_total_"+channel);
        TH1F*hist_data=(TH1F*)f2->Get("hist_data");
        TH1F*h_data=new TH1F("h_data","",3,0,3);
        for(int i=0;i<h_data->GetNbinsX();i++){
            h_data->SetBinContent(i+1,hist_data->GetBinContent(i+1));
            h_data->SetBinError(i+1,hist_data->GetBinError(i+1));
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
        fPads1->SetGridx();
        fPads2->SetGridy();
        double max=hs->GetMaximum();

        h_data->SetMarkerStyle(20);
        h_data->SetMarkerColor(1);
        h_data->SetLineColor(1);
        h_data->SetMarkerSize(1.2);
	h_data->GetYaxis()->SetTitleOffset(0.8);
	h_data->GetYaxis()->SetTitle("Events /bin");
        double high= h_data->GetMaximum();
	h_data->GetYaxis()->SetRangeUser(0,2*high);
        h_data->SetTitle("");

        hs->SetMaximum(high*2);
	hs->Draw("HIST");
        h_data->Draw("PE same");
	cout<<htot->GetBinContent(1)<<" "<<h_data->GetBinContent(1)<<endl;
        htot->SetFillColor(1);
        htot->SetLineColor(0);
        htot->SetMarkerSize(0);
        htot->SetFillStyle(3005);
        htot->Draw("E2 same");
	TLegend* leg = new TLegend(0.62, 0.6, 0.85, 0.9);
	TLegend* leg1 = new TLegend(0.4, 0.6, 0.62, 0.9);
	TLegend* leg2 = new TLegend(0.2, 0.8, 0.39, 0.9);
	leg->SetTextSize(0.04);
        leg1->SetFillColor(kWhite);
	leg1->SetTextSize(0.04);
	leg2->SetTextSize(0.04);
	leg->AddEntry(th2_ZA_sig,Form("EWK[%.1f] ",th2_ZA_sig->GetSum()) );
	leg->AddEntry(th2_ZA_sigout,Form("EWK_{out}[%.1f] ",th2_ZA_sigout->GetSum()) );
	leg->AddEntry(th2_ZA, Form("Z#gamma [%.1f] ",th2_ZA->GetSum()));
	leg->AddEntry(th2_plj, Form("non-prompt [%.1f] ",th2_plj->GetSum() ),"f");
	leg1->AddEntry(th2_VV, Form("VV  [%.1f] ", th2_VV->GetSum() ) );
	leg1->AddEntry(th2_TTA, Form("TT#gamma [%.1f] ",th2_TTA->GetSum()) );
	leg1->AddEntry(th2_ST, Form("ST  [%.1f] ",th2_ST->GetSum() ) );
        leg2->AddEntry(htot,"Stat #oplus Syst");
	leg->Draw();
	leg1->Draw();
	leg2->Draw();
////
        TLatex latex;
        latex.SetTextSize(0.06);
        latex.SetLineWidth(2);
//        latex.DrawLatex(1.4,0.8*max,"2.5<#Delta#eta_{jj}<4.5");
//        latex.DrawLatex(4.2,0.8*max,"4.5<#Delta#eta_{jj}<6");
//        latex.DrawLatex(6.1,0.8*max,"#Delta#eta_{jj}>6");
        TLine* vline1 = new TLine(htot->GetBinLowEdge(4),0,htot->GetBinLowEdge(4),max*1.5);
        TLine* vline2 = new TLine(htot->GetBinLowEdge(7),0,htot->GetBinLowEdge(7),max*1.5);
        vline1->SetLineStyle(2);
        vline2->SetLineStyle(2);
        vline1->SetLineWidth(2);
        vline2->SetLineWidth(2);
        vline1->Draw();
        vline2->Draw();

        string lumivalue;
        if(tag.Contains("16")) lumivalue="35.86";
        if(tag.Contains("17")) lumivalue="41.52";
        if(tag.Contains("18")) lumivalue="59.7";
        CMS_lumi(fPads1, 4, 0, lumivalue);
        fPads1->Update();
        fPads2->cd();
        TH1F*nominal=(TH1F*)htot->Clone("nominal");
        TH1F*nomNoErr=(TH1F*)nominal->Clone("nomNoErr");
        TH1F*htemp=(TH1F*)h_data->Clone();
        for (int i = 1; i<= nomNoErr->GetNbinsX(); ++i){nomNoErr->SetBinError(i,0);}

        TGraphAsymmErrors*gr1=(TGraphAsymmErrors*)f1->Get("data_"+channel);
	double x[3],x_up[3],x_down[3],y_up[3],y_down[3];
	double y[3];
	for(int i=0;i<gr1->GetN();i++){
                y[i]=0;
		gr1->GetPoint(i,x[i],y[i]);
                x_up[i]=gr1->GetErrorXhigh(i);
                x_down[i]=gr1->GetErrorXlow(i);
                y[i]=y[i]/nominal->GetBinContent(i+1);
                y_up[i]=sqrt( pow(gr1->GetErrorYhigh(i),2) )/nominal->GetBinContent(i+1);
                y_down[i]=sqrt( pow(gr1->GetErrorYlow(i),2) )/nominal->GetBinContent(i+1);
                
	}
        TGraphAsymmErrors*gr=new TGraphAsymmErrors(gr1->GetN(),x,y,x_down,x_up,y_down,y_up);
        htemp->Divide(nominal);
        cout<<htemp->GetBinContent(1)<<endl;
        nominal->Divide(nomNoErr);
        nominal->GetYaxis()->SetRangeUser(0.5,1.8);
        nominal->SetLineColor(2);
        nominal->SetTitle(";m_{jj} [GeV];Data/MC;");
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
//        gr->Draw("EP same");
        htemp->Draw("EP same");
        fPads2->Update();

	fout->cd();
	hs->Write();
	fout->Close();

	c1->SaveAs("aa_"+channel+tag+".pdf");
}
int unroll_test_CR(){
       vector<TString> tag={"16","17","18"};
       vector<TString> channels={"mubarrel","muendcap","elebarrel","eleendcap"};
       for(int i=0;i<channels.size();i++){
	       for(int j=0;j<tag.size();j++){
		       cout<<channels[i]<<" "<<tag[j]<<endl;
                       TString channel=channels[i]+"_CR";
		       run(channel,tag[j]);
	       }
       }
       return 0;

}
