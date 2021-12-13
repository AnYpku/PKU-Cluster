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
TH1F*run(vector<TFile*>file,TString process,TString type);
TGraphAsymmErrors*run(vector<TFile*>file);
void run(TString type,TString njets,TString var,vector<double> bins1,vector<double> bins2){
	setTDRStyle();
	TFile* fout = new TFile("aa_"+njets+"_"+var+".root","RECREATE");
	std::ostringstream strs;
	Double_t lumi=137.1;

        TFile*f1=new TFile("./hist_"+type+"_fit17_"+njets+"_mllg.root");
        TFile*f2=new TFile("./hist_"+type+"_fit18_"+njets+"_mllg.root");
        vector<TFile*>file;
        file.push_back(f1);file.push_back(f2);

        TH1F*th2_ZA  = run(file,"VA",type);
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

        TH1F*th2_ZA_sig  = run(file,"Sig",type);;

	th2_ZA_sig->SetFillColor(kRed-7);
	th2_ZA_sig->SetMarkerColor(kRed-7);
        th2_ZA_sig->SetLineColor(kRed-7);
	th2_ZA_sig->SetMarkerStyle(21);

        TH1F*th2_ZA_sigout  = run(file,"Sig_out",type);;

	th2_ZA_sigout->SetFillColor(0);
	th2_ZA_sigout->SetMarkerColor(kRed-7);
        th2_ZA_sigout->SetLineColor(kRed-7);
	th2_ZA_sigout->SetMarkerStyle(21);

        TH1F* th2_VV  = run(file,"VV",type);;

	th2_VV->SetFillColor(kCyan);
	th2_VV->SetMarkerColor(kCyan);
        th2_VV->SetLineColor(kCyan);

        TH1F* th2_ST  = run(file,"Top",type);;

	th2_ST->SetFillColor(40);
	th2_ST->SetMarkerColor(40);
        th2_ST->SetLineColor(40);

        TH1F* th2_plj  = run(file,"Nonprompt_photon",type);

	th2_plj->SetFillColor(kGreen+2);
	th2_plj->SetMarkerColor(kGreen+2);
        th2_plj->SetLineColor(kGreen+2);

        TH1F* th2_fakeL  = run(file,"Nonprompt_lepton",type);

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
	hs->Add(th2_ZA_sigout);
        TH1F*htot  = run(file,"total",type);
        for(Int_t i=1;i<=htot->GetNbinsX();i++){ htot->GetXaxis()->SetBinLabel(i,name[i-1]);}
        TH1F*hdata =(TH1F*)htot->Clone();
        hdata->SetMarkerStyle(20);
        hdata->SetMarkerColor(1);
        hdata->SetLineColor(1);
        hdata->SetMarkerSize(1.2);

//      TGraphAsymmErrors*gr1=(TGraphAsymmErrors*)f1->Get("data_"+tag);
        TGraphAsymmErrors*gr1=run(file);

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
	double ewkout_y,ewkout_e;
	int n=th2_ZA_sig->GetNbinsX();
        ewk_y=th2_ZA_sig->IntegralAndError(0,n,ewk_e);
        ewkout_y=th2_ZA_sigout->IntegralAndError(0,n,ewkout_e);
        ZA_y =th2_ZA->IntegralAndError(0,n,ZA_e);
	plj_y=th2_plj->IntegralAndError(0,n,plj_e);
	fakeL_y=th2_fakeL->IntegralAndError(0,n,fakeL_e);
        VV_y =th2_VV->IntegralAndError(0,n,VV_e);
	ST_y =th2_ST->IntegralAndError(0,n,ST_e);

	cout<< Form("WW#gamma [%.1f #pm %.1f]",th2_ZA_sig->GetSum(),ewk_e)<<endl ;
	cout<< Form("Out of Fid. [%.1f #pm %.1f]",th2_ZA_sigout->GetSum(),ewk_e)<<endl ;
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
	leg1->AddEntry(th2_ST, "Top");
	leg1->AddEntry(th2_VV, "VV");
	leg2->AddEntry(th2_ZA_sigout,"Out of Fid.","f");
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
	lumivalue="101";
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
//	leg2->AddEntry(h_data,Form("Data [%0.f]",h_data->GetSum()));
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
	c1->SaveAs("aa_"+type+"_"+njets+"_"+var+".pdf");

	fout->cd();
	hs->Write();
	nominal->Write();
	gr->Write();
	fout->Close();

}
int unroll_full(){
        vector<TString>njets={"0jets","1jets","2jets"};
        vector<TString>vars={"mllg"};
	vector<TString>types={"CR","SR","full"};
        vector<Double_t> ml1g_bins={10,80,140,200};
        vector<Double_t> mllg_bins={15,155,315,500};
        vector<vector<Double_t>> bins2;
        bins2=get_vector(ml1g_bins,mllg_bins);
	vector<Double_t> mT_bins;
	for(int i=0;i<njets.size()-1;i++){
		for(int ik=0;ik<types.size()-1;ik++){
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
				run(types[ik],njets[i],vars[k],mT_bins,mllg_bins);
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
TH1F*run(vector<TFile*>file,TString process,TString type){
	const int num=file.size();
	TH1F*h1[num];
	for(int i=0;i<file.size();i++){
		h1[i]=(TH1F*)file[i]->Get("hist_"+process+"_"+type);
		if(i!=0)
			h1[0]->Add(h1[i]);
	}
	return h1[0];
}
TGraphAsymmErrors*run(vector<TFile*>file){
	const int num=file.size();
	TGraphAsymmErrors*gr1[num];
	gr1[0]=(TGraphAsymmErrors*)file[0]->Get("data");
	const int size=gr1[0]->GetN();
	double x[num][size],y[num][size],y_up[num][size],y_down[num][size],x_down[num][size],x_up[num][size];
	double Y[size],Y_up[size],Y_down[size];
	for(int j=0;j<gr1[0]->GetN();j++){
		for(int i=1;i<file.size();i++){
			gr1[i]=(TGraphAsymmErrors*)file[i]->Get("data");
			gr1[i]->GetPoint(j,x[i][j],y[i][j]); 
			x_up[i][j]=gr1[i]->GetErrorXhigh(j);
			x_down[i][j]=gr1[i]->GetErrorXhigh(j);
			y_up[i][j]=gr1[i]->GetErrorYhigh(j);
			y_down[i][j]=gr1[i]->GetErrorYhigh(j);
			Y[j]=Y[j]+y[i][j];
			Y_up[j]=Y_up[j]+pow(y_up[i][j],2);
			Y_down[j]=Y_down[j]+pow(y_down[i][j],2);
		}
	}
	TGraphAsymmErrors*gr=new TGraphAsymmErrors(size,x[0],Y,x_down[0],x_up[0],Y_down,Y_up);
	return gr;
}
