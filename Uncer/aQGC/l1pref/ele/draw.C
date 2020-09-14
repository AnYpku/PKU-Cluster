void open(TString name){
gStyle->SetOptStat(0);
TFile*file=new TFile("aa_"+name+".root","recreate");
TString dir16="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Uncer/2016legacy/aQGC/l1pref/ele/";
TFile*f1;
f1=new TFile(dir16+name+".root");

TH1D*h1=(TH1D*)f1->Get("th2_0");
TH1D*h2=(TH1D*)f1->Get("th2_1");
TH1D*h3=(TH1D*)f1->Get("th2_2");

TString dir17="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Uncer/2017/aQGC/l1pref/ele/";
TFile*ff1=new TFile(dir17+name+".root");

TH1D*hh1=(TH1D*)ff1->Get("th2_0");
TH1D*hh2=(TH1D*)ff1->Get("th2_1");
TH1D*hh3=(TH1D*)ff1->Get("th2_2");

TString dir18="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Uncer/2018/aQGC/l1pref/ele/";
TFile*fff1=new TFile(dir18+name+".root");

TH1D*hhh1=(TH1D*)fff1->Get("th2_0");
TH1D*hhh2=(TH1D*)fff1->Get("th2_1");
TH1D*hhh3=(TH1D*)fff1->Get("th2_2");

h1->Add(hh1);
h2->Add(hh2);
h3->Add(hh3);



TCanvas*c1=new TCanvas("c1","",900,600);
TLegend*l1 =new TLegend(0.7,0.7,0.9,0.9);
h1->SetLineColor(2);
h2->SetLineColor(kGreen);
h3->SetLineColor(kBlue);
h1->SetLineWidth(2);
h2->SetLineWidth(2);
h3->SetLineWidth(2);
l1->AddEntry(h1,"center");
l1->AddEntry(h2,"Up");
l1->AddEntry(h3,"Down");
h2->Draw();
h1->Draw("same");
h3->Draw("same");
l1->Draw();
c1->Print("Mva_"+name+"_hist.eps");
file->cd();
h1->Write();
h2->Write();
h3->Write();
file->Close();
}
int draw(){

//open("ZA");
open("ZA-EWK");
return 1;

}
