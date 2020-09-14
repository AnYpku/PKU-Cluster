void draw(){
gStyle->SetOptStat(0);
TFile*file=new TFile("aa.root","recreate");
TString dir16="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Uncer/2016legacy/aQGC/fakephoton/ele/";
TFile*f1=new TFile(dir16+"ele_hist.root");
TFile*f2=new TFile(dir16+"ele_up_hist.root");
TFile*f3=new TFile(dir16+"ele_down_hist.root");

TH1D*h1=(TH1D*)f1->Get("ele");
TH1D*h2=(TH1D*)f2->Get("ele_up");
TH1D*h3=(TH1D*)f3->Get("ele_down");

TString dir17="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Uncer/2017/aQGC/fakephoton/ele/";
TFile*ff1=new TFile(dir17+"ele_hist.root");
TFile*ff2=new TFile(dir17+"ele_up_hist.root");
TFile*ff3=new TFile(dir17+"ele_down_hist.root");

TH1D*hh1=(TH1D*)ff1->Get("ele");
TH1D*hh2=(TH1D*)ff2->Get("ele_up");
TH1D*hh3=(TH1D*)ff3->Get("ele_down");

TString dir18="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Uncer/2018/aQGC/fakephoton/ele/";
TFile*fff1=new TFile(dir18+"ele_hist.root");
TFile*fff2=new TFile(dir18+"ele_up_hist.root");
TFile*fff3=new TFile(dir18+"ele_down_hist.root");

TH1D*hhh1=(TH1D*)fff1->Get("ele");
TH1D*hhh2=(TH1D*)fff2->Get("ele_up");
TH1D*hhh3=(TH1D*)fff3->Get("ele_down");


h1->Add(hh1);
h1->Add(hhh1);
h2->Add(hh2);
h2->Add(hhh2);
h3->Add(hh3);
h3->Add(hhh3);

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
c1->Print("Mva_hist.eps");
file->cd();
h1->Write();
h2->Write();
h3->Write();
file->Close();
}
