#define ptnumber 11
TFile* file1 = new TFile("./dataTrue_template_dr.root");
TFile* file2 = new TFile("./mcTrue_template_ptbin15-400.root");
Double_t lowpt[ptnumber]= {15,20,25,30,35,40,45,50,60,80,120};
Double_t highpt[ptnumber]={20,25,30,35,40,45,50,60,80,120,400};
TH1D* h[11];
TH1D* h1[11];
TLegend *a=new TLegend(0.55,0.4,0.8,0.9);
void draw(){
	for(Int_t i=3;i<8;i++){
           h[i] =(TH1D*)file1->Get(Form("hsieie_pt%0.f_%0.f",lowpt[i],highpt[i]));
           h1[i] =(TH1D*)file2->Get(Form("h2_pt%0.f_%0.f",lowpt[i],highpt[i]));
        //   h[i]->Add(h1[i],-1);
           h[i]->SetLineColor(i+1);
           //h[i]->GetYaxis()->SetRangeUser(0,0.8);
           h[i]->SetLineWidth(2);
           h[i]->SetMarkerStyle(20);
           h[i]->DrawNormalized("same pe");
	   h[i]->SetMaximum(0.8);
           a->AddEntry(h[i],Form("pt%0.f-%0.f",lowpt[i],highpt[i]),"L");
	}
/*	h[8] =(TH1D*)file1->Get(Form("h4_pt%0.f_%0.f",lowpt[8],highpt[8]));
	h[8]->DrawNormalized("same pe");
	a->AddEntry(h[8],Form("pt%0.f-%0.f",lowpt[8],highpt[8]),"L");*/
        a->Draw();
}
int mm(){
	TCanvas *can = new TCanvas("can", "sieie distribution",0,23,900,602);
	can->SetFrameFillColor(41);
	can->SetBorderMode(0);
	can->SetBorderSize(2);
	can->SetFrameBorderMode(2);
	can->SetFrameBorderMode(0);
	draw();
        can->Print("./sieie_vs_pt_hist1.pdf");
	return 0;
}
