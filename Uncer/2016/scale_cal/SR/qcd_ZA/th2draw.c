void th2draw(){

TFile* file = new TFile("th2-histo.root");
TFile* f = new TFile("drawth2.root","RECREATE");
TH2D* h2[9];
TCanvas* c[9];
for(Int_t i=0;i<9;i++){
    c[i] = new TCanvas(Form("c%d",i+1),Form("Mjj vs deltaeatjj %d histo",i+1),900,600);
    h2[i] = (TH2D*)file->Get(Form("th2_%d",i));
    h2[i]->Draw("COLZTEXTE");
    h2[i]->SetMarkerSize(1.8);
    c[i]->Write();
    } 
f->Close();









}
