void draw(){
gStyle->SetOptStat(0);
TFile*file=new TFile("aa.root","recreate");
TFile*f1=new TFile("ele_hist.root");
TFile*f2=new TFile("ele_up_hist.root");
TFile*f3=new TFile("ele_down_hist.root");

TH1D*h1=(TH1D*)f1->Get("ele");
TH1D*h2=(TH1D*)f2->Get("ele_up");
TH1D*h3=(TH1D*)f3->Get("ele_down");

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
