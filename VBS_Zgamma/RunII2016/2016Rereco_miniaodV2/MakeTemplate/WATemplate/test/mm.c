#define ptnumber 11
TFile* file1 = new TFile("./waData_template.root");
Double_t lowpt[ptnumber]= {15,20,25,30,35,40,45,50,60,80,120};
Double_t highpt[ptnumber]={20,25,30,35,40,45,50,60,80,120,400};
TH1D* h[11];
TLegend *a=new TLegend(0.55,0.4,0.8,0.9);
void draw(){
	for(Int_t i=0;i<11;i++){
           h[i] =(TH1D*)file1->Get(Form("hsieie_pt%0.f-%0.f",lowpt[i],highpt[i]));
           h[i]->SetLineColor(i+1);
           //h[i]->GetYaxis()->SetRangeUser(0,0.8);
           h[i]->SetLineWidth(2);
           h[i]->SetMarkerStyle(20);
//           h[i]->DrawNormalized("same hist");
           h[i]->DrawNormalized("same pe");
	   h[i]->SetMaximum(0.8);
           a->AddEntry(h[i],Form("pt%0.f-%0.f",lowpt[i],highpt[i]),"L");
	}
        a->Draw();
}
int mm(){
gStyle->SetOptStat(0);
	TCanvas *can = new TCanvas("can", "sieie distribution",0,23,900,602);
	can->SetFrameFillColor(41);
	can->SetBorderMode(0);
	can->SetBorderSize(2);
	can->SetFrameBorderMode(2);
	can->SetFrameBorderMode(0);
	draw();
        can->Print("./wadata_sieie_vs_pt_hist.pdf");
	return 0;
}
