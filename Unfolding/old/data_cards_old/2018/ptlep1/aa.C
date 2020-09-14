void aa()
{
//=========Macro generated from canvas: /
//=========  (Tue Jan  7 00:21:43 2020) by ROOT version6.10/09
   TCanvas * = new TCanvas("", "",0,0,800,600);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetTickx(1);
   c1->SetTicky(1);
   c1->SetLeftMargin(0.15);
   c1->SetRightMargin(0.05);
   c1->SetBottomMargin(0.13);
   c1->SetFrameFillStyle(0);
   c1->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: pad1
   TPad *pad1 = new TPad("pad1", "",0,0,0.99,0.99);
   pad1->Draw();
   pad1->cd();
   pad1->Range(-51.25,-137.5433,423.75,920.4818);
   pad1->SetFillColor(0);
   pad1->SetBorderMode(0);
   pad1->SetBorderSize(2);
   pad1->SetTickx(1);
   pad1->SetTicky(1);
   pad1->SetLeftMargin(0.15);
   pad1->SetRightMargin(0.05);
   pad1->SetBottomMargin(0.13);
   pad1->SetFrameFillStyle(0);
   pad1->SetFrameBorderMode(0);
   pad1->SetFrameFillStyle(0);
   pad1->SetFrameBorderMode(0);
   
   THStack *hs = new THStack();
   hs->SetName("hs");
   hs->SetTitle("");
   Double_t xAxis1[5] = {20, 80, 120, 200, 400}; 
   
   TH1F *hs_stack_1 = new TH1F("hs_stack_1","",4, xAxis1);
   hs_stack_1->SetMinimum(0);
   hs_stack_1->SetMaximum(825.2596);
   hs_stack_1->SetDirectory(0);
   hs_stack_1->SetStats(0);
   hs_stack_1->SetLineStyle(0);
   hs_stack_1->SetLineWidth(2);
   hs_stack_1->SetMarkerStyle(20);
   hs_stack_1->GetXaxis()->SetBinLabel(1,"20~80");
   hs_stack_1->GetXaxis()->SetBinLabel(2,"80~120");
   hs_stack_1->GetXaxis()->SetBinLabel(3,"120~200");
   hs_stack_1->GetXaxis()->SetBinLabel(4,"200~400");
   hs_stack_1->GetXaxis()->SetLabelFont(42);
   hs_stack_1->GetXaxis()->SetLabelOffset(0.007);
   hs_stack_1->GetXaxis()->SetTitleSize(0.06);
   hs_stack_1->GetXaxis()->SetTitleOffset(0.9);
   hs_stack_1->GetXaxis()->SetTitleFont(42);
   hs_stack_1->GetYaxis()->SetTitle("Events /bin");
   hs_stack_1->GetYaxis()->SetLabelFont(42);
   hs_stack_1->GetYaxis()->SetLabelOffset(0.007);
   hs_stack_1->GetYaxis()->SetTitleSize(0.06);
   hs_stack_1->GetYaxis()->SetTitleOffset(0.8);
   hs_stack_1->GetYaxis()->SetTitleFont(42);
   hs_stack_1->GetZaxis()->SetLabelFont(42);
   hs_stack_1->GetZaxis()->SetLabelOffset(0.007);
   hs_stack_1->GetZaxis()->SetTitleSize(0.06);
   hs_stack_1->GetZaxis()->SetTitleFont(42);
   hs->SetHistogram(hs_stack_1);
   
   Double_t xAxis2[5] = {20, 80, 120, 200, 400}; 
   
   TH1D *hist_stack_1 = new TH1D("hist_stack_1","ST		 20<leading p_{T}^{reco}<400  reco && gen",4, xAxis2);
   hist_stack_1->SetBinContent(1,0.6434696);
   hist_stack_1->SetBinContent(2,0.4850079);
   hist_stack_1->SetBinContent(3,0.270518);
   hist_stack_1->SetBinError(1,0.3715074);
   hist_stack_1->SetBinError(2,0.3452331);
   hist_stack_1->SetBinError(3,0.270518);
   hist_stack_1->SetEntries(6);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#00ff00");
   hist_stack_1->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   hist_stack_1->SetLineColor(ci);

   ci = TColor::GetColor("#00ff00");
   hist_stack_1->SetMarkerColor(ci);
   hist_stack_1->GetXaxis()->SetTitle("leding p_{T}^{reco}");
   hist_stack_1->GetXaxis()->SetBinLabel(1,"20~80");
   hist_stack_1->GetXaxis()->SetBinLabel(2,"80~120");
   hist_stack_1->GetXaxis()->SetBinLabel(3,"120~200");
   hist_stack_1->GetXaxis()->SetBinLabel(4,"200~400");
   hist_stack_1->GetXaxis()->SetLabelFont(42);
   hist_stack_1->GetXaxis()->SetLabelSize(0.035);
   hist_stack_1->GetXaxis()->SetTitleSize(0.035);
   hist_stack_1->GetXaxis()->SetTitleFont(42);
   hist_stack_1->GetYaxis()->SetTitle("yields");
   hist_stack_1->GetYaxis()->SetLabelFont(42);
   hist_stack_1->GetYaxis()->SetLabelSize(0.035);
   hist_stack_1->GetYaxis()->SetTitleSize(0.035);
   hist_stack_1->GetYaxis()->SetTitleOffset(0);
   hist_stack_1->GetYaxis()->SetTitleFont(42);
   hist_stack_1->GetZaxis()->SetLabelFont(42);
   hist_stack_1->GetZaxis()->SetLabelSize(0.035);
   hist_stack_1->GetZaxis()->SetTitleSize(0.035);
   hist_stack_1->GetZaxis()->SetTitleFont(42);
   hs->Add(hist_stack_1,"");
   Double_t xAxis3[5] = {20, 80, 120, 200, 400}; 
   
   TH1D *hist_stack_2 = new TH1D("hist_stack_2","TTA		 20<leading p_{T}^{reco}<400  reco && gen",4, xAxis3);
   hist_stack_2->SetBinContent(1,7.795711);
   hist_stack_2->SetBinContent(2,1.429214);
   hist_stack_2->SetBinContent(3,0.259857);
   hist_stack_2->SetBinError(1,1.61237);
   hist_stack_2->SetBinError(2,0.9094996);
   hist_stack_2->SetBinError(3,0.486148);
   hist_stack_2->SetBinError(4,0.1837467);
   hist_stack_2->SetEntries(219);

   ci = TColor::GetColor("#00ffff");
   hist_stack_2->SetFillColor(ci);

   ci = TColor::GetColor("#00ffff");
   hist_stack_2->SetLineColor(ci);

   ci = TColor::GetColor("#00ffff");
   hist_stack_2->SetMarkerColor(ci);
   hist_stack_2->GetXaxis()->SetTitle("leding p_{T}^{reco}");
   hist_stack_2->GetXaxis()->SetBinLabel(1,"20~80");
   hist_stack_2->GetXaxis()->SetBinLabel(2,"80~120");
   hist_stack_2->GetXaxis()->SetBinLabel(3,"120~200");
   hist_stack_2->GetXaxis()->SetBinLabel(4,"200~400");
   hist_stack_2->GetXaxis()->SetLabelFont(42);
   hist_stack_2->GetXaxis()->SetLabelSize(0.035);
   hist_stack_2->GetXaxis()->SetTitleSize(0.035);
   hist_stack_2->GetXaxis()->SetTitleFont(42);
   hist_stack_2->GetYaxis()->SetTitle("yields");
   hist_stack_2->GetYaxis()->SetLabelFont(42);
   hist_stack_2->GetYaxis()->SetLabelSize(0.035);
   hist_stack_2->GetYaxis()->SetTitleSize(0.035);
   hist_stack_2->GetYaxis()->SetTitleOffset(0);
   hist_stack_2->GetYaxis()->SetTitleFont(42);
   hist_stack_2->GetZaxis()->SetLabelFont(42);
   hist_stack_2->GetZaxis()->SetLabelSize(0.035);
   hist_stack_2->GetZaxis()->SetTitleSize(0.035);
   hist_stack_2->GetZaxis()->SetTitleFont(42);
   hs->Add(hist_stack_2,"");
   Double_t xAxis4[5] = {20, 80, 120, 200, 400}; 
   
   TH1D *hist_stack_3 = new TH1D("hist_stack_3","VV		 20<leading p_{T}^{reco}<400  reco && gen",4, xAxis4);
   hist_stack_3->SetBinContent(1,3.371147);
   hist_stack_3->SetBinContent(2,1.251121);
   hist_stack_3->SetBinContent(3,1.989648);
   hist_stack_3->SetBinContent(4,1.155567);
   hist_stack_3->SetBinError(1,1.124618);
   hist_stack_3->SetBinError(2,0.7223351);
   hist_stack_3->SetBinError(3,0.8913354);
   hist_stack_3->SetBinError(4,0.6683064);
   hist_stack_3->SetEntries(20);

   ci = TColor::GetColor("#6666cc");
   hist_stack_3->SetFillColor(ci);

   ci = TColor::GetColor("#6666cc");
   hist_stack_3->SetLineColor(ci);

   ci = TColor::GetColor("#6666cc");
   hist_stack_3->SetMarkerColor(ci);
   hist_stack_3->GetXaxis()->SetTitle("leding p_{T}^{reco}");
   hist_stack_3->GetXaxis()->SetBinLabel(1,"20~80");
   hist_stack_3->GetXaxis()->SetBinLabel(2,"80~120");
   hist_stack_3->GetXaxis()->SetBinLabel(3,"120~200");
   hist_stack_3->GetXaxis()->SetBinLabel(4,"200~400");
   hist_stack_3->GetXaxis()->SetLabelFont(42);
   hist_stack_3->GetXaxis()->SetLabelSize(0.035);
   hist_stack_3->GetXaxis()->SetTitleSize(0.035);
   hist_stack_3->GetXaxis()->SetTitleFont(42);
   hist_stack_3->GetYaxis()->SetTitle("yields");
   hist_stack_3->GetYaxis()->SetLabelFont(42);
   hist_stack_3->GetYaxis()->SetLabelSize(0.035);
   hist_stack_3->GetYaxis()->SetTitleSize(0.035);
   hist_stack_3->GetYaxis()->SetTitleOffset(0);
   hist_stack_3->GetYaxis()->SetTitleFont(42);
   hist_stack_3->GetZaxis()->SetLabelFont(42);
   hist_stack_3->GetZaxis()->SetLabelSize(0.035);
   hist_stack_3->GetZaxis()->SetTitleSize(0.035);
   hist_stack_3->GetZaxis()->SetTitleFont(42);
   hs->Add(hist_stack_3,"");
   Double_t xAxis5[5] = {20, 80, 120, 200, 400}; 
   
   TH1D *hist_stack_4 = new TH1D("hist_stack_4","WA		 20<leading p_{T}^{reco}<400  reco && gen",4, xAxis5);

   ci = TColor::GetColor("#000099");
   hist_stack_4->SetFillColor(ci);

   ci = TColor::GetColor("#000099");
   hist_stack_4->SetLineColor(ci);

   ci = TColor::GetColor("#000099");
   hist_stack_4->SetMarkerColor(ci);
   hist_stack_4->GetXaxis()->SetTitle("leding p_{T}^{reco}");
   hist_stack_4->GetXaxis()->SetBinLabel(1,"20~80");
   hist_stack_4->GetXaxis()->SetBinLabel(2,"80~120");
   hist_stack_4->GetXaxis()->SetBinLabel(3,"120~200");
   hist_stack_4->GetXaxis()->SetBinLabel(4,"200~400");
   hist_stack_4->GetXaxis()->SetLabelFont(42);
   hist_stack_4->GetXaxis()->SetLabelSize(0.035);
   hist_stack_4->GetXaxis()->SetTitleSize(0.035);
   hist_stack_4->GetXaxis()->SetTitleFont(42);
   hist_stack_4->GetYaxis()->SetTitle("yields");
   hist_stack_4->GetYaxis()->SetLabelFont(42);
   hist_stack_4->GetYaxis()->SetLabelSize(0.035);
   hist_stack_4->GetYaxis()->SetTitleSize(0.035);
   hist_stack_4->GetYaxis()->SetTitleOffset(0);
   hist_stack_4->GetYaxis()->SetTitleFont(42);
   hist_stack_4->GetZaxis()->SetLabelFont(42);
   hist_stack_4->GetZaxis()->SetLabelSize(0.035);
   hist_stack_4->GetZaxis()->SetTitleSize(0.035);
   hist_stack_4->GetZaxis()->SetTitleFont(42);
   hs->Add(hist_stack_4,"");
   Double_t xAxis6[5] = {20, 80, 120, 200, 400}; 
   
   TH1D *hist_stack_5 = new TH1D("hist_stack_5","plj		 20<leading p_{T}^{reco}<400  reco && gen",4, xAxis6);
   hist_stack_5->SetBinContent(1,469.7359);
   hist_stack_5->SetBinContent(2,111.7903);
   hist_stack_5->SetBinContent(3,41.17417);
   hist_stack_5->SetBinContent(4,13.16508);
   hist_stack_5->SetBinError(1,11.53803);
   hist_stack_5->SetBinError(2,5.41518);
   hist_stack_5->SetBinError(3,3.283083);
   hist_stack_5->SetBinError(4,1.871036);
   hist_stack_5->SetEntries(2510);

   ci = TColor::GetColor("#ffff00");
   hist_stack_5->SetFillColor(ci);

   ci = TColor::GetColor("#ffff00");
   hist_stack_5->SetLineColor(ci);

   ci = TColor::GetColor("#ffff00");
   hist_stack_5->SetMarkerColor(ci);
   hist_stack_5->GetXaxis()->SetTitle("leding p_{T}^{reco}");
   hist_stack_5->GetXaxis()->SetBinLabel(1,"20~80");
   hist_stack_5->GetXaxis()->SetBinLabel(2,"80~120");
   hist_stack_5->GetXaxis()->SetBinLabel(3,"120~200");
   hist_stack_5->GetXaxis()->SetBinLabel(4,"200~400");
   hist_stack_5->GetXaxis()->SetLabelFont(42);
   hist_stack_5->GetXaxis()->SetLabelSize(0.035);
   hist_stack_5->GetXaxis()->SetTitleSize(0.035);
   hist_stack_5->GetXaxis()->SetTitleFont(42);
   hist_stack_5->GetYaxis()->SetTitle("yields");
   hist_stack_5->GetYaxis()->SetLabelFont(42);
   hist_stack_5->GetYaxis()->SetLabelSize(0.035);
   hist_stack_5->GetYaxis()->SetTitleSize(0.035);
   hist_stack_5->GetYaxis()->SetTitleOffset(0);
   hist_stack_5->GetYaxis()->SetTitleFont(42);
   hist_stack_5->GetZaxis()->SetLabelFont(42);
   hist_stack_5->GetZaxis()->SetLabelSize(0.035);
   hist_stack_5->GetZaxis()->SetTitleSize(0.035);
   hist_stack_5->GetZaxis()->SetTitleFont(42);
   hs->Add(hist_stack_5,"");
   Double_t xAxis7[5] = {20, 80, 120, 200, 400}; 
   
   TH1D *hist_stack_6 = new TH1D("hist_stack_6","ZA		 20<leading p_{T}^{reco}<400  reco && gen",4, xAxis7);
   hist_stack_6->SetBinContent(1,242.5969);
   hist_stack_6->SetBinContent(2,93.04569);
   hist_stack_6->SetBinContent(3,53.11515);
   hist_stack_6->SetBinContent(4,21.09538);
   hist_stack_6->SetBinError(1,11.78064);
   hist_stack_6->SetBinError(2,7.581006);
   hist_stack_6->SetBinError(3,6.109099);
   hist_stack_6->SetBinError(4,3.841634);
   hist_stack_6->SetEntries(1750);

   ci = TColor::GetColor("#ff00ff");
   hist_stack_6->SetFillColor(ci);

   ci = TColor::GetColor("#ff00ff");
   hist_stack_6->SetLineColor(ci);

   ci = TColor::GetColor("#ff00ff");
   hist_stack_6->SetMarkerColor(ci);
   hist_stack_6->GetXaxis()->SetTitle("leding p_{T}^{reco}");
   hist_stack_6->GetXaxis()->SetBinLabel(1,"20~80");
   hist_stack_6->GetXaxis()->SetBinLabel(2,"80~120");
   hist_stack_6->GetXaxis()->SetBinLabel(3,"120~200");
   hist_stack_6->GetXaxis()->SetBinLabel(4,"200~400");
   hist_stack_6->GetXaxis()->SetLabelFont(42);
   hist_stack_6->GetXaxis()->SetLabelSize(0.035);
   hist_stack_6->GetXaxis()->SetTitleSize(0.035);
   hist_stack_6->GetXaxis()->SetTitleFont(42);
   hist_stack_6->GetYaxis()->SetTitle("yields");
   hist_stack_6->GetYaxis()->SetLabelFont(42);
   hist_stack_6->GetYaxis()->SetLabelSize(0.035);
   hist_stack_6->GetYaxis()->SetTitleSize(0.035);
   hist_stack_6->GetYaxis()->SetTitleOffset(0);
   hist_stack_6->GetYaxis()->SetTitleFont(42);
   hist_stack_6->GetZaxis()->SetLabelFont(42);
   hist_stack_6->GetZaxis()->SetLabelSize(0.035);
   hist_stack_6->GetZaxis()->SetTitleSize(0.035);
   hist_stack_6->GetZaxis()->SetTitleFont(42);
   hs->Add(hist_stack_6,"");
   Double_t xAxis8[5] = {20, 80, 120, 200, 400}; 
   
   TH1D *hist_stack_7 = new TH1D("hist_stack_7","ZA-EWK		 20<leading p_{T}^{reco}<400  reco && gen",4, xAxis8);
   hist_stack_7->SetBinContent(1,55.11462);
   hist_stack_7->SetBinContent(2,30.18932);
   hist_stack_7->SetBinContent(3,21.95587);
   hist_stack_7->SetBinContent(4,10.16809);
   hist_stack_7->SetBinError(1,1.116207);
   hist_stack_7->SetBinError(2,0.8259347);
   hist_stack_7->SetBinError(3,0.7056645);
   hist_stack_7->SetBinError(4,0.4793235);
   hist_stack_7->SetEntries(5248);

   ci = TColor::GetColor("#ff3333");
   hist_stack_7->SetFillColor(ci);

   ci = TColor::GetColor("#ff3333");
   hist_stack_7->SetLineColor(ci);

   ci = TColor::GetColor("#ff3333");
   hist_stack_7->SetMarkerColor(ci);
   hist_stack_7->SetMarkerStyle(21);
   hist_stack_7->GetXaxis()->SetTitle("leding p_{T}^{reco}");
   hist_stack_7->GetXaxis()->SetBinLabel(1,"20~80");
   hist_stack_7->GetXaxis()->SetBinLabel(2,"80~120");
   hist_stack_7->GetXaxis()->SetBinLabel(3,"120~200");
   hist_stack_7->GetXaxis()->SetBinLabel(4,"200~400");
   hist_stack_7->GetXaxis()->SetLabelFont(42);
   hist_stack_7->GetXaxis()->SetLabelSize(0.035);
   hist_stack_7->GetXaxis()->SetTitleSize(0.035);
   hist_stack_7->GetXaxis()->SetTitleFont(42);
   hist_stack_7->GetYaxis()->SetTitle("yields");
   hist_stack_7->GetYaxis()->SetLabelFont(42);
   hist_stack_7->GetYaxis()->SetLabelSize(0.035);
   hist_stack_7->GetYaxis()->SetTitleSize(0.035);
   hist_stack_7->GetYaxis()->SetTitleOffset(0);
   hist_stack_7->GetYaxis()->SetTitleFont(42);
   hist_stack_7->GetZaxis()->SetLabelFont(42);
   hist_stack_7->GetZaxis()->SetLabelSize(0.035);
   hist_stack_7->GetZaxis()->SetTitleSize(0.035);
   hist_stack_7->GetZaxis()->SetTitleFont(42);
   hs->Add(hist_stack_7,"");
   Double_t xAxis9[5] = {20, 80, 120, 200, 400}; 
   
   TH1D *hist3_stack_8 = new TH1D("hist3_stack_8","ZA-EWK		 20<leading p_{T}^{reco}<400 reco out of gen",4, xAxis9);
   hist3_stack_8->SetBinContent(1,6.703738);
   hist3_stack_8->SetBinContent(2,2.789475);
   hist3_stack_8->SetBinContent(3,1.91214);
   hist3_stack_8->SetBinContent(4,0.9223263);
   hist3_stack_8->SetBinError(1,0.3883371);
   hist3_stack_8->SetBinError(2,0.2505022);
   hist3_stack_8->SetBinError(3,0.2074007);
   hist3_stack_8->SetBinError(4,0.1440432);
   hist3_stack_8->SetEntries(548);

   ci = TColor::GetColor("#ffcc00");
   hist3_stack_8->SetFillColor(ci);

   ci = TColor::GetColor("#ffcc00");
   hist3_stack_8->SetLineColor(ci);

   ci = TColor::GetColor("#ffcc00");
   hist3_stack_8->SetMarkerColor(ci);
   hist3_stack_8->SetMarkerStyle(21);
   hist3_stack_8->GetXaxis()->SetTitle("leding p_{T}^{gen}");
   hist3_stack_8->GetXaxis()->SetBinLabel(1,"20~80");
   hist3_stack_8->GetXaxis()->SetBinLabel(2,"80~120");
   hist3_stack_8->GetXaxis()->SetBinLabel(3,"120~200");
   hist3_stack_8->GetXaxis()->SetBinLabel(4,"200~400");
   hist3_stack_8->GetXaxis()->SetLabelFont(42);
   hist3_stack_8->GetXaxis()->SetLabelSize(0.035);
   hist3_stack_8->GetXaxis()->SetTitleSize(0.035);
   hist3_stack_8->GetXaxis()->SetTitleFont(42);
   hist3_stack_8->GetYaxis()->SetTitle("yields");
   hist3_stack_8->GetYaxis()->SetLabelFont(42);
   hist3_stack_8->GetYaxis()->SetLabelSize(0.035);
   hist3_stack_8->GetYaxis()->SetTitleSize(0.035);
   hist3_stack_8->GetYaxis()->SetTitleOffset(0);
   hist3_stack_8->GetYaxis()->SetTitleFont(42);
   hist3_stack_8->GetZaxis()->SetLabelFont(42);
   hist3_stack_8->GetZaxis()->SetLabelSize(0.035);
   hist3_stack_8->GetZaxis()->SetTitleSize(0.035);
   hist3_stack_8->GetZaxis()->SetTitleFont(42);
   hs->Add(hist3_stack_8,"");
   hs->Draw("hist");
   
   TLegend *leg = new TLegend(0.82,0.7,0.95,0.88,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("hist_stack_1","ST","lpf");

   ci = TColor::GetColor("#00ff00");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#00ff00");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#00ff00");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hist_stack_2","TTA","lpf");

   ci = TColor::GetColor("#00ffff");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#00ffff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#00ffff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hist_stack_3","VV","lpf");

   ci = TColor::GetColor("#6666cc");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#6666cc");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#6666cc");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hist_stack_4","WA","lpf");

   ci = TColor::GetColor("#000099");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#000099");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hist_stack_5","non-prompt","lpf");

   ci = TColor::GetColor("#ffff00");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ffff00");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ffff00");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hist_stack_6","ZA","lpf");

   ci = TColor::GetColor("#ff00ff");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ff00ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff00ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(1);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hist_stack_7","ZA_sig","lpf");

   ci = TColor::GetColor("#ff3333");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ff3333");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff3333");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hist3_stack_8","ZA_sig_out","lpf");

   ci = TColor::GetColor("#ffcc00");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ffcc00");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ffcc00");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   TLatex *   tex = new TLatex(0.18,0.82,"Preliminary");
tex->SetNDC();
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.18,0.86,"CMS");
tex->SetNDC();
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.76,0.92,"58.7 fb^{-1} (13 TeV)");
tex->SetNDC();
   tex->SetTextSize(0.03);
   tex->SetLineWidth(2);
   tex->Draw();
   pad1->Modified();
   ->cd();
   c1->Modified();
   ->cd();
   ->SetSelected();
}
