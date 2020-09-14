void open(TString name){
gStyle->SetOptStat(0);
TFile*file=new TFile("aa_"+name+".root","recreate");
TFile*f1=new TFile("Mva_"+name+"_jer.root");

TH1D*h1=(TH1D*)f1->Get("th2_0");
TH1D*h2=(TH1D*)f1->Get("th2_1");
TH1D*h3=(TH1D*)f1->Get("th2_2");

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

open("ZA_tot");
open("ZA-EWK");
return 1;

}
