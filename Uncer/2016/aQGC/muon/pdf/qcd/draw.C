#define num 103
void open(){
gStyle->SetOptStat(0);
TFile*file=new TFile("aa.root","recreate");
TFile*f1=new TFile("ZA-pweight-scale_hist.root");
TH1D*h1[103];
for (int i=0;i<103;i++){
	h1[i]=(TH1D*)f1->Get(Form("th2_%i",i));
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
