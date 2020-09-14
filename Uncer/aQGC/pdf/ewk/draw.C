#define num 101
void open(){
gStyle->SetOptStat(0);
TFile*file=new TFile("aa.root","recreate");
TString dir16="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Uncer/2016legacy/aQGC/pdf/ewk/";
TFile*f1=new TFile(dir16+"ZA-EWK-pweight-scale_hist.root");

TString dir17="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Uncer/2017/aQGC/pdf/ewk/";
TFile*f2=new TFile(dir17+"ZA-EWK-pweight-scale_hist.root");

TString dir18="/afs/cern.ch/user/y/yian/work/PKU-Cluster/Uncer/2018/aQGC/pdf/ewk/";
TFile*f3=new TFile(dir18+"ZA-EWK-pweight-scale_hist.root");

TH1D*h1[num];
TH1D*h2[num];
TH1D*h3[num];
for (int i=0;i<num;i++){
	h1[i]=(TH1D*)f1->Get(Form("th2_%i",i));
	h2[i]=(TH1D*)f2->Get(Form("th2_%i",i));
	h3[i]=(TH1D*)f3->Get(Form("th2_%i",i));
}
for (int i=0;i<num;i++){
	h1[i]->Add(h2[i]);
	h1[i]->Add(h3[i]);
}

TCanvas*c1=new TCanvas("c1","",900,600);
TLegend*l1 =new TLegend(0.7,0.7,0.9,0.9);
l1->AddEntry(h1[2],"nnpdf variation");
file->cd();
for (int i=0;i<num;i++){
	if(i==0){
		h1[i]->SetLineColor(kRed);
		h1[i]->SetLineWidth(3);
		l1->AddEntry(h1[0],"center");
                h1[i]->GetYaxis()->SetRangeUser(0,h1[0]->GetMaximum()*1.3);
		h1[i]->Write();
                h1[i]->Draw("hist");
	}
        else{
		h1[i]->SetLineColor(kBlue);
		h1[i]->SetLineWidth(2);
		h1[i]->SetLineStyle(2);
		h1[i]->Draw("same hist");
		h1[i]->Write();
	}
}
file->Close();
l1->Draw();
c1->Print("Mva_hist.eps");
}
int draw(){

open();
return 1;

}
