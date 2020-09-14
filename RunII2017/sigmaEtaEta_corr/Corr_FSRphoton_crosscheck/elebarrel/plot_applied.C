void plot_applied(){
	TCanvas*c=new TCanvas("aa","aa",800,600);
	c->SetLogy();
	c->cd();
	TFile* f1=TFile::Open("trans_DEle16_applied.root");
	TFile* f2=TFile::Open("trans_ZJets_FX_applied.root");
        TH1D* hdata;
        TH1D* hmc;
        f1->GetObject("DEle16",hdata);
        f2->GetObject("ZJets_FX",hmc);

        gStyle->SetOptStat(0);
        TLegend* l1 = new TLegend(0.7,0.7,0.9,0.9);
        l1->AddEntry(hdata,"DEle16");
        l1->AddEntry(hmc,"ZJets");
        cout<<hdata->Integral()<<endl;
        cout<<hmc->Integral()<<endl;
        hmc->Scale(hdata->Integral()/hmc->Integral());
        cout<<hdata->Integral()/hmc->Integral()<<endl;
        hdata->SetLineColor(kBlack);
        hdata->SetLineWidth(2);
        hdata->Rebin(5);
        hdata->SetTitle(";#sigma_{i#eta i#eta};");
        hdata->Draw();
        hmc->SetLineColor(kRed);
        hmc->SetLineWidth(2);
        hmc->Rebin(5);
        hmc->Draw("SAME");
        l1->Draw();

//        c->SaveAs("aa_barrel.png");
        c->SaveAs("aa_barrel_applied.pdf");
//        c->SaveAs("aa_endcap.png");
//        c->SaveAs("aa_endcap.pdf");
}
