void check_rochester()
{
	TFile*file=TFile::Open("./optimal_outDMuon.root");
	TTree*t=(TTree*)file->Get("outtree");
	
	double kr1;
	double kr2;
	t->SetBranchStatus("*",0);
	t->SetBranchStatus("muon1_rochester",1);
	t->SetBranchStatus("muon2_rochester",1);
	t->SetBranchAddress("muon1_rochester",&kr1);
	t->SetBranchAddress("muon2_rochester",&kr2);

	Long64_t entry=t->GetEntries();
	TH1D* h1= new TH1D("","",40,0.9,1.1);
	h1->SetStats(0);
	TH1D* h2= new TH1D("","",40,0.9,1.1);
	for(Long64_t i=0;i<entry;i++)
	{
		t->GetEntry(i);
		h1->Fill(kr1);
		h2->Fill(kr2);
	}
	TCanvas* c1= new TCanvas("","",800,600);
	c1->cd();
	h2->SetLineColor(kRed);
	h2->Draw();
	h1->SetLineColor(kGreen);
	h1->Draw("same");

	TLegend*l =new TLegend(0.75,0.8,0.95,0.95);
	l->AddEntry(h2,"mu2");
	l->AddEntry(h1,"mu1");
	l->Draw();
	c1->SaveAs("data.png");
}
