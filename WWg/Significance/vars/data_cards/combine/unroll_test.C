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
vector<vector<double>> get_vector(vector<double> v1,vector<double> v3);
void run(TString tag,TString type,TString njets,TString var,vector<double> bins1,vector<double> bins2){
	setTDRStyle();
	TFile* fout = new TFile("aa_"+tag+"_"+njets+"_"+var+".root","RECREATE");
	std::ostringstream strs;
	Double_t lumi=137.1;

        TFile*f1=new TFile("./hist_"+type+"_fit"+tag+"_"+njets+"_"+var+".root");

        TH1F*th2_ZA  =(TH1F*)f1->Get("hist_VA_"+tag+"_"+type);
	cout<<th2_ZA->GetSum()<<endl;

	th2_ZA->SetFillColor(kYellow-7);
	th2_ZA->SetMarkerColor(kYellow-7);
	th2_ZA->SetLineColor(kYellow-7);

        const int n1=bins1.size()*bins2.size();
        const char *name[n1];
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
//        const char *name[28]={"50-100","100-150","150-#infty","50-100","100-150","150-#infty","50-100","100-150","150-#infty","50-100","100-150","150-#infty","20-80","80-120","120-160","160-#infty","20-80","80-120","120-160","160-#infty","20-80","80-120","120-160","160-#infty","20-80","80-120","120-160","160-#infty"};

        TH1F*th2_ZA_sig  =(TH1F*)f1->Get("hist_Sig_"+tag+"_"+type);

	th2_ZA_sig->SetFillColor(kRed-7);
	th2_ZA_sig->SetMarkerColor(kRed-7);
        th2_ZA_sig->SetLineColor(kRed-7);
	th2_ZA_sig->SetMarkerStyle(21);

        TH1F* th2_VV  =(TH1F*)f1->Get("hist_VV_"+tag+"_"+type);

	th2_VV->SetFillColor(kCyan);
	th2_VV->SetMarkerColor(kCyan);
        th2_VV->SetLineColor(kCyan);

        /*TH1F* th2_TTA  =(TH1F*)f1->Get("hist_TTA_"+tag+"_"+type);

	th2_TTA->SetFillColor(kBlue);
	th2_TTA->SetMarkerColor(kBlue);
        th2_TTA->SetLineColor(kBlue);*/

        TH1F* th2_ST  =(TH1F*)f1->Get("hist_Top_"+tag+"_"+type);

	th2_ST->SetFillColor(40);
	th2_ST->SetMarkerColor(40);
        th2_ST->SetLineColor(40);

        TH1F* th2_plj  =(TH1F*)f1->Get("hist_Nonprompt_photon_"+tag+"_"+type);

	th2_plj->SetFillColor(kGreen+2);
	th2_plj->SetMarkerColor(kGreen+2);
        th2_plj->SetLineColor(kGreen+2);

        TH1F* th2_fakeL  =(TH1F*)f1->Get("hist_Nonprompt_lepton_"+tag+"_"+type);

	th2_fakeL->SetFillColor(kGreen-3);
	th2_fakeL->SetMarkerColor(kGreen-3);
        th2_fakeL->SetLineColor(kGreen-3);

	THStack* hs = new THStack("hs", "");
	hs->Add(th2_ST);
//	hs->Add(th2_TTA);
	hs->Add(th2_VV);
	hs->Add(th2_plj);
	hs->Add(th2_fakeL);
	hs->Add(th2_ZA);
	hs->Add(th2_ZA_sig);
        TH1F*htot  =(TH1F*)f1->Get("hist_total_"+tag+"_"+type);
        for(Int_t i=1;i<=htot->GetNbinsX();i++){ htot->GetXaxis()->SetBinLabel(i,name[i-1]);}
        TH1F*hdata =(TH1F*)htot->Clone();
        hdata->SetMarkerStyle(20);
        hdata->SetMarkerColor(1);
        hdata->SetLineColor(1);
        hdata->SetMarkerSize(1.2);

        TGraphAsymmErrors*gr1=(TGraphAsymmErrors*)f1->Get("data_"+tag);

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
//        fPads1->SetTopMargin(0.12);
        fPads1->SetBottomMargin(0.028);
        fPads2->SetTopMargin(0.012);
        fPads2->SetBottomMargin(0.45);
        fPads1->Draw();
        fPads2->Draw();
        fPads1->cd();
        double max=hs->GetMaximum();

        hs->SetMaximum(3*max);
	hs->Draw("HIST");
        hs->GetYaxis()->SetTitleOffset(0.8);
        hs->GetYaxis()->SetTitle("Events /bin");
        hs->GetYaxis()->SetTitleSize(0.08);
        hs->GetYaxis()->SetLabelSize(0.07);
        hs->GetXaxis()->SetLabelSize(0.0);
        hs->GetYaxis()->SetNdivisions(505);
        gr1->SetMarkerStyle(20);
        gr1->SetMarkerColor(1);
        gr1->SetLineColor(1);
        gr1->SetMarkerSize(1.2);
//        gr1->Draw("EP same");
        hdata->Draw("EP same");
        htot->SetFillColor(1);
        htot->SetLineColor(0);
        htot->SetMarkerSize(0);
        htot->SetFillStyle(3005);
        htot->Draw("E2 same");
	TLegend* leg = new TLegend(0.63, 0.6, 0.85, 0.9);
	TLegend* leg1 = new TLegend(0.47, 0.6, 0.7, 0.9);
	TLegend* leg2 = new TLegend(0.17, 0.6, 0.39, 0.9);
        leg->SetFillColor(0);
        leg1->SetFillColor(0);
        leg2->SetFillColor(0);
	leg->SetTextSize(0.065);
	leg1->SetTextSize(0.065);
	leg2->SetTextSize(0.065);
        double ewk_y,ewk_e,ZA_y,ZA_e,plj_y,plj_e,fakeL_y,fakeL_e,VV_y,VV_e,TTA_y,TTA_e,ST_y,ST_e;
	int n=th2_ZA_sig->GetNbinsX();
        ewk_y=th2_ZA_sig->IntegralAndError(0,n,ewk_e);
        ZA_y =th2_ZA->IntegralAndError(0,n,ZA_e);
	plj_y=th2_plj->IntegralAndError(0,n,plj_e);
	fakeL_y=th2_fakeL->IntegralAndError(0,n,fakeL_e);
        VV_y =th2_VV->IntegralAndError(0,n,VV_e);
	ST_y =th2_ST->IntegralAndError(0,n,ST_e);

	cout<< Form("WW#gamma [%.1f #pm %.1f]",th2_ZA_sig->GetSum(),ewk_e)<<endl ;
	cout<< Form("QCD Z#gamma [%.1f #pm %.1f]",th2_ZA->GetSum(),ZA_e)<<endl;
	cout<< Form("Nonprompt #gamma [%.1f #pm %.1f]",th2_plj->GetSum(),plj_e )<<endl;
	cout<< Form("Nonprompt #font[12]{l} [%.1f #pm %.1f]",th2_fakeL->GetSum(),fakeL_e )<<endl;
	cout<< Form("VV  [%.1f#pm %.1f]", th2_VV->GetSum() ,VV_e)<<endl;
	cout<< Form("Top [%.1f #pm %.1f]",th2_ST->GetSum(),ST_e)<<endl;
//	cout<< Form("tW [%.1f #pm %.1f]",th2_ST->GetSum() ,ST_e)<<endl;
//	TTA_y=th2_TTA->IntegralAndError(0,n,TTA_e);
//	leg->AddEntry(th2_ZA_sig,Form("WW#gamma [%.1f #pm %.1f]",th2_ZA_sig->GetSum(),ewk_e) );
//	leg->AddEntry(th2_ZA, Form("QCD Z#gamma [%.1f #pm %.1f]",th2_ZA->GetSum(),ZA_e));
//	leg->AddEntry(th2_plj, Form("Nonprompt #gamma [%.1f #pm %.1f]",th2_plj->GetSum(),plj_e ),"f");
//	leg->AddEntry(th2_fakeL, Form("Nonprompt #font[12]{l} [%.1f #pm %.1f]",th2_fakeL->GetSum(),fakeL_e ),"f");
//	leg1->AddEntry(th2_VV, Form("VV  [%.1f#pm %.1f]", th2_VV->GetSum() ,VV_e) );
//	leg1->AddEntry(th2_TTA, Form("t#bar{t}#gamma [%.1f #pm %.1f]",th2_TTA->GetSum(),TTA_e) );
//	leg1->AddEntry(th2_ST, Form("tW [%.1f #pm %.1f]",th2_ST->GetSum() ,ST_e) );

	leg->AddEntry(th2_ZA, "QCD V#gamma");
	leg->AddEntry(th2_plj, "Nonprompt #gamma");
	leg->AddEntry(th2_fakeL, "Nonprompt #font[12]{l}");
	leg1->AddEntry(th2_ZA_sig,"WW#gamma");
	leg1->AddEntry(th2_VV, "VV");
	leg1->AddEntry(th2_ST, "Top");
        leg2->AddEntry(htot,"Stat #oplus Syst");
//
        TLatex latex;
        latex.SetLineWidth(2);
        TString l_var;
        if(var=="ml1g") l_var="m_{#font[12]{l_{1}#gamma}}";
        if(var=="mllg") l_var="m_{#font[12]{ll#gamma}}";
	if(type=="full"){
		latex.SetTextSize(0.04);
		for(int i=0;i<bins2.size()-1;i++){
			if(i<bins2.size()-2)
				latex.DrawLatex(i*(bins1.size()-1)+0.5,1.4*max,Form("%.0f<"+l_var+"<%.0f",bins2[i],bins2[i+1]));
			else
				latex.DrawLatex(i*(bins1.size()-1)+0.5,1.4*max,Form(l_var+">%.0f",bins2[i]));
		}
	}
	else if(type=="SR"){
		latex.SetTextSize(0.07);
		cout<<"bins2 size "<<bins2.size()<<endl;
		for(int i=0;i<bins2.size()-1;i++){
			if(i<bins2.size()-2)
				latex.DrawLatex(i*(bins1.size()-1)+0.5,1.4*max,Form("%.0f<"+l_var+"<%.0f",bins2[i],bins2[i+1]));
			else
				latex.DrawLatex(i*(bins1.size()-1)+0.5,1.4*max,Form(l_var+">%.0f",bins2[i]));
		}
	}
	else{
		latex.SetTextSize(0.07);
		for(int i=0;i<bins2.size()-1;i++){
			if(i<bins2.size()-2)
				latex.DrawLatex(i*(bins1.size()-1)+0.5,1.4*max,Form("%.0f<"+l_var+"<%.0f",bins2[i],bins2[i+1]));
			else
				latex.DrawLatex(i*(bins1.size()-1)+0.5,1.4*max,Form(l_var+">%.0f",bins2[i]));
		}
	}

        TLine* vline1 = new TLine(htot->GetBinLowEdge(bins1.size()-1+1),0,htot->GetBinLowEdge(bins1.size()-1+1),max*1.5);
        TLine* vline2 = new TLine(htot->GetBinLowEdge(2*(bins1.size()-1)+1),0,htot->GetBinLowEdge(2*(bins1.size()-1)+1),max*1.5);
        TLine* vline3 = new TLine(htot->GetBinLowEdge(3*(bins1.size()-1)+1),0,htot->GetBinLowEdge(3*(bins1.size()-1)+1),max*1.5);
        TLine* vline4 = new TLine(htot->GetBinLowEdge(4*(bins1.size()-1)+1),0,htot->GetBinLowEdge(4*(bins1.size()-1)+1),max*1.5);
        TLine* vline5 = new TLine(htot->GetBinLowEdge(5*(bins1.size()-1)+1),0,htot->GetBinLowEdge(5*(bins1.size()-1)+1),max*1.5);
        TLine* vline6 = new TLine(htot->GetBinLowEdge(6*(bins1.size()-1)+1),0,htot->GetBinLowEdge(6*(bins1.size()-1)+1),max*1.5);
	vline1->SetLineStyle(2);
	vline2->SetLineStyle(2);
	vline3->SetLineStyle(2);
	vline4->SetLineStyle(2);
	vline5->SetLineStyle(2);
	vline6->SetLineStyle(2);
	vline1->SetLineWidth(2);
	vline2->SetLineWidth(2);
	vline3->SetLineWidth(2);
	vline4->SetLineWidth(2);
	vline5->SetLineWidth(2);
	vline6->SetLineWidth(2);
	vline1->Draw();
	vline2->Draw();
	vline3->Draw();
	vline4->Draw();
	vline5->Draw();
	vline6->Draw();
	leg1->Draw();
	leg->Draw();

	string lumivalue;
	if(tag.Contains("16")) lumivalue="35.86";
	if(tag.Contains("17")) lumivalue="41.52";
	if(tag.Contains("18")) lumivalue="59.7";
	CMS_lumi(fPads1, 4, 0, lumivalue);
	fPads1->Update();
	fPads2->cd();
	TH1F*nominal=(TH1F*)htot->Clone("nominal");
	TH1F*nomNoErr=(TH1F*)nominal->Clone("nomNoErr");
	for (int i = 1; i<= nomNoErr->GetNbinsX(); ++i){nomNoErr->SetBinError(i,0);}

	const int num=gr1->GetN();
	double x[num],x_up[num],x_down[num],y_up[num],y_down[num];
	double y[num];
	TH1D*h_data=new TH1D("h_data","",num,0,num);
	cout<<"get data hist"<<endl;
	for(int i=0;i<gr1->GetN();i++){
		y[i]=0;
		gr1->GetPoint(i,x[i],y[i]);
		h_data->SetBinContent(i+1,y[i]);
		h_data->SetBinError(i+1,sqrt( pow(gr1->GetErrorYhigh(i),2) ));
		x_up[i]=gr1->GetErrorXhigh(i);
		x_down[i]=gr1->GetErrorXlow(i);
		y[i]=y[i]/nominal->GetBinContent(i+1);
		y_up[i]=sqrt( pow(gr1->GetErrorYhigh(i),2) )/nominal->GetBinContent(i+1);
		y_down[i]=sqrt( pow(gr1->GetErrorYlow(i),2) )/nominal->GetBinContent(i+1);

	}
	cout<<"have got data hist"<<endl;
	h_data->SetMarkerStyle(20);
	h_data->SetMarkerSize(1);
	h_data->SetLineColor(1);
	double err_data,data_y;
	double err_tot,tot_y;
	data_y=h_data->IntegralAndError(0,h_data->GetNbinsX(),err_data);
	tot_y=htot->IntegralAndError(0,htot->GetNbinsX(),err_tot);
//	leg2->AddEntry(h_data,Form("Data [%0.f #pm %0.f]",h_data->GetSum(),err_data));
	leg2->AddEntry(h_data,Form("Data [%0.f]",h_data->GetSum()));
	leg2->AddEntry(htot,Form("Pred. [%0.f #pm %.0f]",htot->GetSum(),err_tot),"f");
	fPads1->cd();
	leg2->Draw();
	fPads1->Update();
	fPads2->cd();
	cout<<"get data/MC ratio"<<endl;

	TGraphAsymmErrors*gr=new TGraphAsymmErrors(gr1->GetN(),x,y,x_down,x_up,y_down,y_up);

	cout<<"get MC statistics uncertainties"<<endl;

	TH1D*h_up=(TH1D*)hdata->Clone();
	h_up->Divide(nomNoErr);
	nominal->Divide(nomNoErr);
	nominal->GetYaxis()->SetRangeUser(0.4,1.9);
	nominal->SetLineColor(2);
	nominal->SetTitle(";m^{WW}_{T} [GeV];Data/Pred.;");
	nominal->GetYaxis()->SetTitleOffset(0.35);
	nominal->GetYaxis()->SetTitleSize(0.16);
	nominal->GetYaxis()->SetNdivisions(303);
	nominal->GetXaxis()->SetLabelSize(0.2);
	nominal->GetYaxis()->SetLabelSize(0.16);
	nominal->GetXaxis()->SetLabelOffset(0.032);
	nominal->GetXaxis()->SetTitleSize(0.2);
	nominal->GetXaxis()->SetTitleOffset(1.05);
      //for(Int_t i=1;i<=nominal->GetNbinsX();i++){ nominal->GetXaxis()->SetBinLabel(i,name[i-1]);}
	cout<<"set label name"<<endl;

	nominal->Draw("E2");
	cout<<"draw MC stat"<<endl;
	gr->SetMarkerStyle(20);
	gr->SetMarkerColor(1);
	gr->SetLineColor(1);
	gr->SetMarkerSize(1.2);
//	gr->Draw("EP same");
	h_up->Draw("EP same");
	cout<<"draw data/MC"<<endl;
	fPads2->Update();
	c1->SaveAs("aa_"+type+tag+"_"+njets+"_"+var+".pdf");

	fout->cd();
	hs->Write();
	nominal->Write();
	gr->Write();
	fout->Close();

}
int unroll_test(){
	vector<TString> tag={"16","17","18"};
        vector<TString>njets={"0jets","1jets","2jets"};
        vector<TString>vars={"mllg"};
	vector<TString>types={"CR","SR","full"};
        vector<Double_t> ml1g_bins={10,80,140,200};
        vector<Double_t> mllg_bins={15,155,315,500};
        vector<vector<Double_t>> bins2;
        bins2=get_vector(ml1g_bins,mllg_bins);
	vector<Double_t> mT_bins;
	for(int j=1;j<tag.size();j++){
		for(int i=0;i<njets.size()-1;i++){
			for(int ik=0;ik<types.size();ik++){
				if(types[ik]=="SR"){
					ml1g_bins={10,80,140,200};
					mllg_bins={15,155,315,500};
					bins2=get_vector(ml1g_bins,mllg_bins);
					if(njets[i].Contains("0")) mT_bins={50,95,120,140,200};
					else mT_bins={50,105,150,200};
				}
				else if(types[ik]=="CR"){
					ml1g_bins={10,80,140,200};
					mllg_bins={15,155,315,500};
					bins2=get_vector(ml1g_bins,mllg_bins);
					if(njets[i].Contains("0")) mT_bins={0,90,130,200};
					else mT_bins={0,80,110,150,200};
				}
				else{
                                    ml1g_bins={10,80,140,200,10,80,140,200};
				    mllg_bins={15,155,315,500,15,155,315,500};
				    bins2=get_vector(ml1g_bins,mllg_bins);
                                    if(njets[i].Contains("0")) mT_bins={0,90,130,200,50,95,120,140,200};
				    else mT_bins={0,80,110,150,200,50,105,150,200};
				}
				for(int k=0;k<vars.size();k++){
					run(tag[j],types[ik],njets[i],vars[k],mT_bins,mllg_bins);
				}
			}
		}
	}
	return 0;

}
vector<vector<double>> get_vector(vector<double> v1,vector<double> v3){
	vector<vector<double>> bins;
	bins.push_back(v1);
	bins.push_back(v3);
	return bins;
}
