void compare(){
TString dir16="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/data_card/2016/Mva/";
TString dir17="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/data_card/2017/Mva/";
TString dir18="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Unfolding/data_card/2018/Mva/";
TFile* f1= new TFile(dir16+"root/hist_ZA-EWK.root");
TFile* ff1= new TFile(dir17+"root/hist_ZA-EWK.root");
TFile* fff1= new TFile(dir18+"root/hist_ZA-EWK.root");
TH1D* h1=(TH1D*)f1->Get("hist");
TH1D* hh1=(TH1D*)ff1->Get("hist");
TH1D* hhh1=(TH1D*)fff1->Get("hist");
h1->Add(hh1);
h1->Add(hhh1);
TFile*f2=new TFile("unfold_hist.root");
TH1D*h2=(TH1D*)f2->Get("unfHist");

double uncer[5]={4.44e-01,4.55e-01,2.02e-01,5.15e-01};
double x[5],y[5],y_down[5],y_up[5];
TCanvas *c1 = new TCanvas("c1","",900,600);

TLegend*l1=new TLegend(0.5,0.7,0.9,0.9);
//c1->SetGrid();
//c1->DrawFrame(0,0,2.2,12);
for(int i=0;i<h1->GetNbinsX();i++){
   x[i]=h1->GetBinCenter(i+1);
   y[i]=h1->GetBinContent(i+1);
   y_up[i]= (1+uncer[i])*h1->GetBinContent(i+1);
   y_down[i]=(1-uncer[i])*h1->GetBinContent(i+1);
  }
Int_t n=h1->GetNbinsX();
TGraph *grmin = new TGraph(n,x,y_down);
TGraph *grmax = new TGraph(n,x,y_up);
TGraph *gr = new TGraph(n,x,y);
TGraph *grshade = new TGraph(2*n);
for(int i=0;i<n;i++){
    grshade->SetPoint(i,x[i],y_up[i]);
    grshade->SetPoint(n+i,x[n-i-1],y_down[n-i-1]);
}
grshade->SetFillStyle(3013);
grshade->SetFillColor(16);
gr->SetLineWidth(2);
gr->SetLineColor(4);
gr->SetMarkerColor(4);
gr->SetMarkerStyle(21);
gr->SetFillColor(0);
gr->SetTitle("ZGmass; ZGmass ;");
gr->GetYaxis()->SetRangeUser(0,1.5*h2->GetMaximum());
h2->SetLineWidth(2);
h2->SetLineStyle(3);
h2->SetLineColor(2);
h2->SetMarkerColor(2);
h2->SetMarkerStyle(21);
gr->Draw("ACP");
h2->Draw("HIST SAME");
//h1->Draw("HIST");
grshade->Draw("f");
grmin->Draw("l");
grmax->Draw("l");
l1->AddEntry(gr,"from combine tools","l");
l1->AddEntry(h2,"from TUnfold","l");
l1->SetTextSize(0.06);
l1->Draw();
c1->Print("ZGmass_com.pdf");
}
