void create(TString name){
TFile*f1=new TFile("plj_hist.root");
TFile*f2=new TFile("ZA_hist.root");
TFile*f3=new TFile("ZA-EWK_hist.root");
TFile*f4=new TFile("DMuon16_hist.root");
TH1D*h1=(TH1D*)f1->Get("plj");
TH1D*h2=(TH1D*)f2->Get("ZA");
TH1D*h3=(TH1D*)f3->Get("ZA-EWK");
TH1D*h4=(TH1D*)f4->Get("DMuon16");
TFile*file=new TFile("mu_"+name+".root","recreate");
file->cd();
h1->Write("plj");
h2->Write("QCD");
h3->Write("diboson");
h4->Write("data_obs");
file->Close();

}
int merge(){

create("fM0");
create("fM1");
create("fM2");

return 1;

}
