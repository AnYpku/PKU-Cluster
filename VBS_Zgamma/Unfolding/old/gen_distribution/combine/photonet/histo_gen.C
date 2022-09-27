void histo_gen(){
	gStyle->SetOptStat(0);
	TFile*file=new TFile("../../2016/photonet/hist_ZA-EWK.root");
	TFile*file1=new TFile("../../2017/photonet/hist_ZA-EWK-pweight.root");
	TFile*file2=new TFile("../../2018/photonet/hist_ZA-EWK-pweight.root");
	TH1D*hist1[3];TH1D*hist2[3];TH1D*hist3[3];TH1D*hist4[3];
	TH1D*hist1_17[3];TH1D*hist2_17[3];TH1D*hist3_17[3];TH1D*hist4_17[3];
	TH1D*hist1_18[3];TH1D*hist2_18[3];TH1D*hist3_18[3];TH1D*hist4_18[3];
	TCanvas*c1[2];
	for(int i=0;i<3;i++){
            hist1[i]=(TH1D*)file->Get(Form("hist1_%i",i));
            hist2[i]=(TH1D*)file->Get(Form("hist2_%i",i));
            hist3[i]=(TH1D*)file->Get(Form("hist3_%i",i));
            hist4[i]=(TH1D*)file->Get(Form("hist4_%i",i));

            hist1_17[i]=(TH1D*)file1->Get(Form("hist1_%i",i));
            hist2_17[i]=(TH1D*)file1->Get(Form("hist2_%i",i));
            hist3_17[i]=(TH1D*)file1->Get(Form("hist3_%i",i));
            hist4_17[i]=(TH1D*)file1->Get(Form("hist4_%i",i));

            hist1_18[i]=(TH1D*)file2->Get(Form("hist1_%i",i));
            hist2_18[i]=(TH1D*)file2->Get(Form("hist2_%i",i));
            hist3_18[i]=(TH1D*)file2->Get(Form("hist3_%i",i));
            hist4_18[i]=(TH1D*)file2->Get(Form("hist4_%i",i));
	}
      for(int i=0;i<3;i++){
          hist1[i]->Add(hist1_17[i],41.52/35.86);
          hist1[i]->Add(hist1_18[i],58.7/35.9);

          hist2[i]->Add(hist2_17[i],41.52/35.8);
          hist2[i]->Add(hist2_18[i],58.7/35.9);

          hist3[i]->Add(hist3_17[i],41.52/35.8);
          hist3[i]->Add(hist3_18[i],58.7/35.9);

          hist4[i]->Add(hist4_17[i],41.52/35.8);
          hist4[i]->Add(hist4_18[i],58.7/35.9);
      }
       c1[0]=new TCanvas("c0","reco && gen",900,600);
       c1[0]->cd();
       TPad*    fPads1 = new TPad("pad1", "", 0.00, 0.4, 0.99, 0.99);
       TPad*    fPads2 = new TPad("pad2", "", 0.00, 0.00, 0.99, 0.4);
       fPads1->SetBottomMargin(0);
       fPads2->SetTopMargin(0);
       fPads2->SetBottomMargin(0.3);
       fPads1->Draw();
       fPads2->Draw();
       fPads1->cd();
       hist2[0]->SetTitle("leading photon p_{T}");
       hist2[0]->GetYaxis()->SetRangeUser(0,hist2[0]->GetMaximum()*1.2);
       hist2[0]->SetLineColor(2); 
       hist2[0]->SetLineWidth(2); 
       hist2[0]->Draw("hist");
       hist3[0]->SetLineStyle(1);
       hist3[0]->SetLineColor(1);
       hist3[0]->SetMarkerStyle(20);
       double Err[4]={0.22,0.36,0.38,0.47};
       for(int i=0;i<hist3[0]->GetNbinsX();i++){
	       hist3[0]->SetBinError(i+1,Err[i]);
       }
       hist3[0]->Draw("EP same");
       double uf[3]={1,2,0.5};
       TLegend*l1=new TLegend(0.7,0.3,0.9,0.9);
       l1->AddEntry(hist3[0],"p_{T}^{gen} #times r");
       for(int i=0;i<3;i++){
          hist2[i]->SetLineColor(2+i);
          hist2[i]->Draw("same hist");
//          hist3[i]->SetLineStyle(2);
//          hist3[i]->SetLineColor(2+i);
//          hist3[i]->Draw("same hist");
          l1->AddEntry(hist2[i],Form("p_{T}^{gen} #mu_{f}=%1.2f",uf[i]));
       }
      l1->Draw();  
      fPads1->Update();
      fPads2->cd();
      TH1D*nominal=(TH1D*)hist2[0]->Clone("nominal");
      TH1D*nomNoErr=(TH1D*)nominal->Clone("nomNoErr");
      for (int i = 1; i<= nomNoErr->GetNbinsX(); ++i){nomNoErr->SetBinError(i,0);}
      TH1D*hist3_clone=(TH1D*)hist3[0]->Clone();
      TH1D*h_up=(TH1D*)hist2[1]->Clone();
      TH1D*h_down=(TH1D*)hist2[2]->Clone();
      hist3_clone->Divide(nominal);
      h_up->Divide(nominal);
      h_down->Divide(nominal);

      nominal->Divide(nomNoErr);
      nominal->SetFillStyle(3004);
      nominal->SetFillColor(16);
      nominal->GetYaxis()->SetRangeUser(0.84,1.2);
      nominal->SetTitle("");
      nominal->GetXaxis()->SetLabelSize(0.05);
      nominal->GetXaxis()->SetTitleSize(0.07);
      nominal->GetYaxis()->SetTitle("ratio");
      nominal->GetYaxis()->SetTitleOffset(0.25);
      nominal->GetYaxis()->SetTitleSize(0.07);
      TLine*line=new TLine(nominal->GetXaxis()->GetXmin(),1,nominal->GetXaxis()->GetXmax(),1);
      line->SetLineColor(2);
      nominal->Draw("E2");
      h_up->Draw("same hist ][");
      h_down->Draw("same hist ][");
      line->Draw();
      hist3_clone->Draw("EP same");
      fPads2->Update();
      c1[0]->Print("unfold_photonet_full.pdf");

      c1[1]=new TCanvas("c1","gen",900,600);
      c1[1]->cd();
      hist4[0]->GetYaxis()->SetRangeUser(0,hist4[0]->GetMaximum()*1.2);
      hist4[0]->SetLineColor(2); 
      hist4[0]->SetLineWidth(2); 
      hist4[0]->Draw("hist");
      TLegend*l2=new TLegend(0.7,0.7,0.9,0.9);
      for(int i=0;i<3;i++){
          hist4[i]->SetLineColor(2+i);
          hist4[i]->Draw("same hist");
          l2->AddEntry(hist4[i],Form("#mu_{f}=%1.2f",uf[i]));
       }
      l2->Draw();  
      c1[1]->Print("gen_photonet.pdf");
}
