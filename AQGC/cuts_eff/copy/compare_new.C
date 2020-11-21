#include "ratioplot.h"


void run(TString sample, TString type){
	TString dir="/afs/cern.ch/user/y/yian/work/PKU-Cluster/AQGC/cuts_eff/"+sample+"/";
	TFile*f1=new TFile(dir+"2016_results.root");
	TFile*f2=new TFile(dir+"2017_results.root");
	TFile*f3=new TFile(dir+"2018_results.root");
        TH1D*h1=(TH1D*)f1->Get(type);
        TH1D*h2=(TH1D*)f2->Get(type);
        TH1D*h3=(TH1D*)f3->Get(type);

	MyRatioPlot ratio;

	vector<TH1D*> vec_hist;
	vec_hist.push_back(h1);
        vec_hist.push_back(h2);
        vec_hist.push_back(h3);

	vector<TString>	vec_leg;
	vec_leg.push_back("2016 "+sample);
        vec_leg.push_back("2017 "+sample);
        vec_leg.push_back("2018 "+sample);

	double max=h1->GetMaximum()*3;

	if(type.Contains("yields"))ratio.DrawRatioPlot(vec_hist, vec_leg, "", type, 10, max, 0., 3,1);
	else ratio.DrawRatioPlot(vec_hist, vec_leg, "", type, 10, max, 0., 3,0);
	ratio.canvas->SetLogy(1);
	ratio.canvas->Print(sample+"Com_"+type+".pdf");
/*
        h1->GetYaxis()->SetRangeUser(10,max);

        h3->SetLineColor(2); 
        h2->SetLineColor(3); 
        h1->SetLineColor(4); 
        TCanvas*c1=new TCanvas("","",900,600);
	c1->SetLogy();
        h1->Draw();
        h3->Draw("same");
        h2->Draw("same");
        TLegend*l1=new TLegend(0.75,0.75,0.9,0.9);
        l1->AddEntry(h3,"2018");
        l1->AddEntry(h2,"2017");
        l1->AddEntry(h1,"2016");
	l1->Draw();
*/
//        c1->Print(sample+"Com_"+type+".pdf");
}
int compare_new(){
TString type[3]={"entries","yields","eff_entries"};
for(int i=0;i<3;i++){
	run("EWK",type[i]);
//	run("QCD",type[i],"ele");
}
return 1;
}
