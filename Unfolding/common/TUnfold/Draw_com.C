#include "CMS_lumi.C"
void open(TString genvar,TString recovar,TString title){
	gStyle->SetOptStat(0);
	TCanvas *c1  = new TCanvas("c1","c1",0,0,600,400);
	TPad*    fPads1 = new TPad("pad1", "", 0.00, 0., 0.99, 0.99);
	fPads1->Draw();
	fPads1->cd();
	fPads1->SetBottomMargin(0.2);
	fPads1->SetLeftMargin(0.1);
        ifstream f_in("/home/pku/anying/cms/PKU-Cluster/Unfolding/data_card/combine/r_"+recovar+"_full.txt");
        ifstream f_sys("/home/pku/anying/cms/PKU-Cluster/Unfolding/data_card/combine/breakdown/r_sys_"+recovar+"_full.txt");
        if(!f_in.is_open())cout<<"can not open the file "<<"/home/pku/anying/cms/PKU-Cluster/Unfolding/data_card/combine/r_"+recovar+"_full.txt"<<endl;
        if(!f_sys.is_open())cout<<"/home/pku/anying/cms/PKU-Cluster/Unfolding/data_card/combine/breakdown/r_sys_"+recovar+"_full.txt"<<endl;
	TFile*f1=new TFile("../root/hist_ZA-EWK_"+genvar+"16.root");
	TFile*f2=new TFile("../root/hist_ZA-EWK_"+genvar+"17.root");
	TFile*f3=new TFile("../root/hist_ZA-EWK_"+genvar+"18.root");
        TH2D*h2 =(TH2D*)f1->Get("hist_"+genvar);
        TH2D*h22=(TH2D*)f2->Get("hist_"+genvar);
        TH2D*h23=(TH2D*)f3->Get("hist_"+genvar);
        h2->Add(h22,1);h2->Add(h23,1);

	TH1D*hist_gen=(TH1D*)f1->Get("histGen_"+genvar);
	TH1D*hist_gen2=(TH1D*)f2->Get("histGen_"+genvar);
	TH1D*hist_gen3=(TH1D*)f3->Get("histGen_"+genvar);
        hist_gen->Add(hist_gen2,1);hist_gen->Add(hist_gen3,1);

	TUnfoldDensity * density=new TUnfoldDensity(h2,TUnfold::kHistMapOutputHoriz, TUnfold::kRegModeNone,TUnfold::kEConstraintNone, TUnfoldDensity::kDensityModeBinWidthAndUser);
	density->SetInput(hist_gen);
	density->DoUnfold(0);
	TH1 * output = density->GetOutput("unfHist");
	output->SetLineWidth(2);
	const int num=hist_gen->GetNbinsX();
	double x[num],y[num],ymin[num],ymax[num];
        double Err_up[num],Err_down[num];
        double Err_sysUp[num],Err_sysDown[num];
	for(int i=0;i<hist_gen->GetNbinsX();i++){
		f_in>>Err_down[i]>>Err_up[i];
		f_sys>>Err_sysDown[i]>>Err_sysUp[i];
		cout<<Err_down[i]<<" "<<Err_up[i]<<endl;
		x[i]=hist_gen->GetBinCenter(i+1);
		y[i]=hist_gen->GetBinContent(i+1);
		ymin[i]=hist_gen->GetBinContent(i+1)*(1-Err_down[i]);
		ymax[i]=hist_gen->GetBinContent(i+1)*(1+Err_up[i]);
		cout<<y[i]<<" "<<ymin[i]<<" "<<ymax[i]<<endl;
	}
	TGraph *grmin = new TGraph(num,x,ymin);
	TGraph *grmax = new TGraph(num,x,ymax);
	TGraph *gr    = new TGraph(num,x,y);
	TGraph *grshade = new TGraph(2*num);
	for (int i=0;i<num;i++) {
		grshade->SetPoint(i,x[i],ymax[i]);
		grshade->SetPoint(num+i,x[num-i-1],ymin[num-i-1]);
	}
	grshade->SetFillStyle(3013);
	grshade->SetFillColor(16);
	output->SetLineColor(2);
	output->SetLineStyle(2);
	double max=output->GetMaximum();
        output->SetTitle("");
	output->GetYaxis()->SetRangeUser(0,1.5*max);
	output->GetXaxis()->SetTitle(title+" [GeV]");
	output->GetYaxis()->SetTitle("yields");
	output->GetXaxis()->SetTitleSize(0.07);
	output->GetYaxis()->SetTitleSize(0.07);
	output->GetYaxis()->SetTitleOffset(0.7);
	output->GetYaxis()->SetTitleFont(22);
	output->GetXaxis()->SetTitleFont(22);
	output->GetYaxis()->SetLabelFont(12);
	output->GetXaxis()->SetLabelFont(12);
	output->GetYaxis()->SetLabelOffset(0.001);
	output->GetYaxis()->SetLabelSize(0.07);
	output->GetXaxis()->SetLabelSize(0.07);

	output->Draw("hist");
	grmax->Draw("l same");
	gr->Draw("CP same");
	grshade->Draw("f same");
	grmin->Draw("l same");
	gr->SetLineWidth(4);
	gr->SetMarkerColor(4);
	gr->SetMarkerStyle(21);
	TLegend*l1=new TLegend(0.55,0.55,0.9,0.9);
	l1->AddEntry(gr,"from combine");
	l1->AddEntry(output,"from TUnfold");
	grshade->SetLineColor(0);
	grshade->SetMarkerSize(0);
	l1->AddEntry(grshade,"Unc. from combine");
	l1->SetTextSize(0.05);
	l1->Draw();
	CMS_lumi(fPads1, 4, 0, "137.1");
	c1->SaveAs("Com_"+genvar+".pdf");
}
int Draw_com(){
	vector<TString> title={"p_{T}^{l_{1}}","p_{T}^{#gamma}","p_{T}^{j_{1}}"};
	vector<TString> genvars={"genlep1pt","genphotonet","genjet1pt"};
	vector<TString> recovars={"ptlep1","photonet","jet1pt"};
	for(int i=0;i<genvars.size();i++){
		open(genvars[i],recovars[i],title[i]);
	}
	return 1;
}
