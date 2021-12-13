void draw(TString year,TString histName){
     TFile*f1=new TFile("histos_emua_WWG"+year+".root");
     TFile*f2=new TFile("histos_emua_WWG_emu"+year+".root");
     TH1D*h1=(TH1D*)f1->Get(histName);
     TH1D*h2=(TH1D*)f2->Get(histName);
//     h1->Scale(1/h1->Integral());
//     h2->Scale(1/h2->Integral());
     TCanvas*c1=new TCanvas("c1","",800,600);
     TPad*    fPads1 = new TPad("pad1", "", 0.00, 0.3, 0.99, 0.99);
     TPad*    fPads2 = new TPad("pad2", "", 0.00, 0.00, 0.99, 0.3);
     TLegend*l1=new TLegend(0.6,0.6,0.9,0.9); 
     fPads1->SetBottomMargin(0.02);
     fPads2->SetTopMargin(0.012);
     fPads2->SetBottomMargin(0.5);
     fPads1->Draw();
     fPads2->Draw();
     fPads1->cd();
     h1->SetLineColor(2);
     h2->SetLineColor(4);
     h1->GetXaxis()->SetLabelSize(0.0);
     h2->GetXaxis()->SetLabelSize(0.0);
     h1->GetYaxis()->SetTitleOffset(0.8);
     l1->AddEntry(h1,"Scheme 1");
     l1->AddEntry(h2,"Scheme 3");
     h1->Draw("HIST");
     h2->Draw("HIST SAME");
     l1->Draw();


     fPads1->Update();
     fPads2->cd();

     TH1F*nominal=(TH1F*)h1->Clone("nominal");
     TH1D*h_up=(TH1D*)h2->Clone();
     TH1F*nomNoErr=(TH1F*)nominal->Clone("nomNoErr");
     for (int i = 1; i<= nomNoErr->GetNbinsX(); ++i){nomNoErr->SetBinError(i,0);}
     h_up->Divide(nominal);
     nominal->Divide(nomNoErr);
     nominal->SetTitle("");
     nominal->SetFillStyle(3002);
     nominal->SetFillColor(kRed-7);
     nominal->SetLineColor(0);
     nominal->SetMarkerSize(0);
     nominal->GetYaxis()->SetRangeUser(-0.1,2.2);
     nominal->GetXaxis()->SetTitle(histName);
     nominal->GetXaxis()->SetTitleSize(0.16);
     nominal->GetXaxis()->SetTitleOffset(1.);
     nominal->GetXaxis()->SetLabelSize(0.13);
     nominal->GetXaxis()->SetLabelOffset(0.03);
     nominal->GetYaxis()->SetTitle("ratio");
     nominal->GetYaxis()->SetNdivisions(404);
     nominal->GetYaxis()->SetTitleOffset(0.3);
     nominal->GetYaxis()->SetTitleSize(0.15);
     nominal->GetYaxis()->SetLabelSize(0.13);
     nominal->Draw("E2");
     h_up->Draw("PE SAME");
     c1->Print("figs/"+histName+"_com"+year+".pdf");
}
int draw_com(){
        vector<TString> var={"mll_emu","photonet_emu","photoneta_emu","photonphi_emu","lep1pt_emu","lep1eta_emu","lep1phi_emu","lep2pt_emu","lep2eta_emu","lep2phi_emu","mllg_emu","ptll_emu","phiVlep_emu","yVlep_emu","puppimet_emu","puppimetphi_emu","mT_emu","mT2_emu","PuppiMET_T1_pt_emu","PuppiMET_T1_phi_emu"};
	for(int i=0;i<var.size();i++){
		draw("17",var[i]);
		draw("18",var[i]);
	}
	return 0;
}
