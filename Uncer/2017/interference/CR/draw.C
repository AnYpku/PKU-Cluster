void open(TString name1,TString name2){
gStyle->SetOptStat(0);
TFile*file=new TFile("aa.root","recreate");

TFile*f1=new TFile("2d_"+name1+".root");
TH1D*h1=(TH1D*)f1->Get(name1+"_hist");


TFile*f2=new TFile("2d_"+name2+".root");
TH1D*h2=(TH1D*)f2->Get(name2+"_hist");

TCanvas*c1=new TCanvas("c1","",900,600);
TLegend*l1 =new TLegend(0.7,0.7,0.9,0.9);
TPad*    fPads1 = new TPad("pad1", "", 0.00, 0.4, 0.99, 0.99);
TPad*    fPads2 = new TPad("pad2", "", 0.00, 0.00, 0.99, 0.4);
fPads1->SetBottomMargin(0);
fPads2->SetTopMargin(0);
fPads2->SetBottomMargin(0.3);
fPads1->Draw();
fPads1->SetGrid();
fPads2->Draw();
fPads1->cd();
h1->SetLineColor(2);
h2->SetLineColor(kBlue);
h1->SetLineWidth(2);
h2->SetLineWidth(2);
l1->AddEntry(h1,"EWK");
l1->AddEntry(h2,"Interference");
h1->Draw();
h2->Draw("same");
l1->Draw();
fPads1->Update();
fPads2->cd();
fPads2->SetGrid();
TH1D*nominal=(TH1D*)h1->Clone("nominal");
TH1D*nomNoErr=(TH1D*)nominal->Clone("nomNoErr");
for (int i = 1; i<= nomNoErr->GetNbinsX(); ++i){nomNoErr->SetBinError(i,0);}
nominal->Divide(nomNoErr);
TH1D*h3=(TH1D*)h2->Clone();
h3->Divide(nominal);
//h3->Scale(100);
//nominal->Draw();
h3->GetYaxis()->SetTitle("inter/EWK [%]");
h3->GetYaxis()->SetTitleSize(0.12);
h3->GetYaxis()->SetTitleOffset(0.15);
const char *name[8]={"Mjj 500~800","Mjj 800~1200","Mjj 1200~2000","Mjj 500~800","Mjj 800~1200","Mjj 1200~2000","Mjj 500~1200","Mjj 1200~2000"};
for(Int_t j=1;j<=h3->GetNbinsX()*h3->GetNbinsY();j++){ h3->GetXaxis()->SetBinLabel(j,name[j-1]);}
h3->GetXaxis()->SetLabelSize(0.09);
h3->Draw("hist ][");

fPads2->Update();
c1->Print("hist.eps");
c1->Print("hist.pdf");
file->cd();
h1->Write();
h2->Write();
file->Close();
for(int i = 1; i<= nomNoErr->GetNbinsX(); ++i){cout<<fixed<<setprecision(2)<<1+h3->GetBinContent(i)<<",";}
cout<<endl;
}
int draw(){

open("ZA-EWK","ZA_interference");
return 1;

}
