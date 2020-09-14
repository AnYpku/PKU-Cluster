void draw(){
gStyle->SetOptStat(0);
TFile*file=new TFile("aa.root","recreate");
TString dir16="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Uncer/2016legacy/aQGC/fakephoton/muon/";
TString dir166="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Uncer/2016legacy/aQGC/fakephoton/ele/";
TFile*f1=new TFile(dir16+"mu_hist.root");
TFile*f2=new TFile(dir16+"mu_up_hist.root");
TFile*f3=new TFile(dir16+"mu_down_hist.root");
TFile*f11=new TFile(dir166+"ele_hist.root");
TFile*f22=new TFile(dir166+"ele_up_hist.root");
TFile*f33=new TFile(dir166+"ele_down_hist.root");

TH1D*h1=(TH1D*)f1->Get("mu");
TH1D*h2=(TH1D*)f2->Get("mu_up");
TH1D*h3=(TH1D*)f3->Get("mu_down");
TH1D*h11=(TH1D*)f11->Get("ele");
TH1D*h22=(TH1D*)f22->Get("ele_up");
TH1D*h33=(TH1D*)f33->Get("ele_down");

TString dir17="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Uncer/2017/aQGC/fakephoton/muon/";
TString dir177="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Uncer/2017/aQGC/fakephoton/ele/";
TFile*ff1=new TFile(dir17+"mu_hist.root");
TFile*ff2=new TFile(dir17+"mu_up_hist.root");
TFile*ff3=new TFile(dir17+"mu_down_hist.root");
TFile*ff11=new TFile(dir177+"ele_hist.root");
TFile*ff22=new TFile(dir177+"ele_up_hist.root");
TFile*ff33=new TFile(dir177+"ele_down_hist.root");

TH1D*hh1=(TH1D*)ff1->Get("mu");
TH1D*hh2=(TH1D*)ff2->Get("mu_up");
TH1D*hh3=(TH1D*)ff3->Get("mu_down");
TH1D*hh11=(TH1D*)ff11->Get("ele");
TH1D*hh22=(TH1D*)ff22->Get("ele_up");
TH1D*hh33=(TH1D*)ff33->Get("ele_down");

TString dir18="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Uncer/2018/aQGC/fakephoton/muon/";
TString dir188="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Uncer/2018/aQGC/fakephoton/ele/";
TFile*fff1=new TFile(dir18+"mu_hist.root");
TFile*fff2=new TFile(dir18+"mu_up_hist.root");
TFile*fff3=new TFile(dir18+"mu_down_hist.root");
TFile*fff11=new TFile(dir188+"ele_hist.root");
TFile*fff22=new TFile(dir188+"ele_up_hist.root");
TFile*fff33=new TFile(dir188+"ele_down_hist.root");

TH1D*hhh1=(TH1D*)fff1->Get("mu");
TH1D*hhh2=(TH1D*)fff2->Get("mu_up");
TH1D*hhh3=(TH1D*)fff3->Get("mu_down");
TH1D*hhh11=(TH1D*)fff11->Get("ele");
TH1D*hhh22=(TH1D*)fff22->Get("ele_up");
TH1D*hhh33=(TH1D*)fff33->Get("ele_down");

h1->Add(h11);
h1->Add(hh1);
h1->Add(hh11);
h1->Add(hhh1);
h1->Add(hhh11);
h2->Add(h22);
h2->Add(hh2);
h2->Add(hh22);
h2->Add(hhh2);
h2->Add(hhh22);
h3->Add(h33);
h3->Add(hh3);
h3->Add(hh33);
h3->Add(hhh3);
h3->Add(hhh33);

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
