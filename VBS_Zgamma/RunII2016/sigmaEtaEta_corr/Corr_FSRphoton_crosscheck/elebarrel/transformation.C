void transformation(){

	TFile*fout=new TFile("transformation_barrel.root","RECREATE");

    TFile* f1=TFile::Open("./trans_DEle16.root");
    TFile* f2=TFile::Open("./trans_ZJets_FX.root");
//    TFile* fb=TFile::Open("./trans_barrel.root");
    TH1D* hdatab;
    TH1D* hmcb;
    f1->GetObject("DEle16",hdatab);
    f2->GetObject("ZJets_FX",hmcb);

        double xmcb[200], ymcb[200];
        double xdab[200], ydab[200];

        for(int i=0;i<200;i++){
                xmcb[i]=(i+1)*1.0/200;
                xdab[i]=(i+1)*1.0/200;
        }

        hdatab->Scale(1./hdatab->Integral());
        hmcb->Scale(hdatab->Integral()/hmcb->Integral());
        hmcb->Scale(1./hmcb->Integral());

        hdatab->GetQuantiles(200, ydab, xdab);//divide the data to 200 parts, yda[i] presents the value of sieie that hdatab->Integral(0,hdatab>FindFixBin(yda[i])) >= i/200, which means that between two yda[i], the number of the events is same.
        hmcb->GetQuantiles(200, ymcb, xmcb);

//        TGraph*g1b=new TGraph(200, xdab, ydab);
        TGraph*g1b=new TGraph(200, ymcb, ydab);
        g1b->SetNameTitle("barrel","barrel");
        g1b->SetTitle("barrel;ZJets;DoubleEle");

	fout->cd();
    g1b->Draw("alp");
	g1b->Write();
	fout->Close();
}
