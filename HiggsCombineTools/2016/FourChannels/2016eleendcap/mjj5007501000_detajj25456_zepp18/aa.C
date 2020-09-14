void aa()
{
//=========Macro generated from canvas: /
//=========  (Mon Apr 27 16:15:04 2020) by ROOT version6.06/01
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
   pad1->Range(-1.3125,-2.910218,7.4375,19.47607);
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
   hs->SetMaximum(16.62982);
   
   TH1F *hs_stack_1 = new TH1F("hs_stack_1","",7,0,7);
   hs_stack_1->SetMinimum(0);
   hs_stack_1->SetMaximum(17.46131);
   hs_stack_1->SetDirectory(0);
   hs_stack_1->SetStats(0);
   hs_stack_1->SetLineStyle(0);
   hs_stack_1->SetLineWidth(2);
   hs_stack_1->SetMarkerStyle(20);
   hs_stack_1->GetXaxis()->SetBinLabel(1,"Mjj 500~800");
   hs_stack_1->GetXaxis()->SetBinLabel(2,"Mjj 800~1000");
   hs_stack_1->GetXaxis()->SetBinLabel(3,"Mjj 1200~2000");
   hs_stack_1->GetXaxis()->SetBinLabel(4,"Mjj 500~800");
   hs_stack_1->GetXaxis()->SetBinLabel(5,"Mjj 800~1000");
   hs_stack_1->GetXaxis()->SetBinLabel(6,"Mjj 1200~2000");
   hs_stack_1->GetXaxis()->SetBinLabel(7,"Mjj 500~2000");
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
   
   
   TH1D *unrolledsPhist__1 = new TH1D("unrolledsPhist__1","unrolled hist",7,0,7);
   unrolledsPhist__1->SetEntries(7);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#00ff00");
   unrolledsPhist__1->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   unrolledsPhist__1->SetLineColor(ci);
   unrolledsPhist__1->SetLineStyle(0);
   unrolledsPhist__1->SetLineWidth(2);

   ci = TColor::GetColor("#00ff00");
   unrolledsPhist__1->SetMarkerColor(ci);
   unrolledsPhist__1->SetMarkerStyle(20);
   unrolledsPhist__1->GetXaxis()->SetBinLabel(1,"Mjj 500~800");
   unrolledsPhist__1->GetXaxis()->SetBinLabel(2,"Mjj 800~1000");
   unrolledsPhist__1->GetXaxis()->SetBinLabel(3,"Mjj 1200~2000");
   unrolledsPhist__1->GetXaxis()->SetBinLabel(4,"Mjj 500~800");
   unrolledsPhist__1->GetXaxis()->SetBinLabel(5,"Mjj 800~1000");
   unrolledsPhist__1->GetXaxis()->SetBinLabel(6,"Mjj 1200~2000");
   unrolledsPhist__1->GetXaxis()->SetBinLabel(7,"Mjj 500~2000");
   unrolledsPhist__1->GetXaxis()->SetLabelFont(42);
   unrolledsPhist__1->GetXaxis()->SetLabelOffset(0.007);
   unrolledsPhist__1->GetXaxis()->SetTitleSize(0.06);
   unrolledsPhist__1->GetXaxis()->SetTitleOffset(0.9);
   unrolledsPhist__1->GetXaxis()->SetTitleFont(42);
   unrolledsPhist__1->GetYaxis()->SetLabelFont(42);
   unrolledsPhist__1->GetYaxis()->SetLabelOffset(0.007);
   unrolledsPhist__1->GetYaxis()->SetTitleSize(0.06);
   unrolledsPhist__1->GetYaxis()->SetTitleOffset(1.1);
   unrolledsPhist__1->GetYaxis()->SetTitleFont(42);
   unrolledsPhist__1->GetZaxis()->SetLabelFont(42);
   unrolledsPhist__1->GetZaxis()->SetLabelOffset(0.007);
   unrolledsPhist__1->GetZaxis()->SetTitleSize(0.06);
   unrolledsPhist__1->GetZaxis()->SetTitleFont(42);
   hs->Add(unrolled hist,"");
   
   TH1D *unrolledsPhist__2 = new TH1D("unrolledsPhist__2","unrolled hist",7,0,7);
   unrolledsPhist__2->SetBinContent(1,0.002597661);
   unrolledsPhist__2->SetBinContent(2,0.08589979);
   unrolledsPhist__2->SetBinContent(4,0.08266353);
   unrolledsPhist__2->SetBinContent(5,0.08186175);
   unrolledsPhist__2->SetBinContent(6,0.08146858);
   unrolledsPhist__2->SetBinError(1,0.1155318);
   unrolledsPhist__2->SetBinError(2,0.1457545);
   unrolledsPhist__2->SetBinError(4,0.08266353);
   unrolledsPhist__2->SetBinError(5,0.08186175);
   unrolledsPhist__2->SetBinError(6,0.08146858);
   unrolledsPhist__2->SetEntries(7);

   ci = TColor::GetColor("#00ffff");
   unrolledsPhist__2->SetFillColor(ci);

   ci = TColor::GetColor("#00ffff");
   unrolledsPhist__2->SetLineColor(ci);
   unrolledsPhist__2->SetLineStyle(0);
   unrolledsPhist__2->SetLineWidth(2);

   ci = TColor::GetColor("#00ffff");
   unrolledsPhist__2->SetMarkerColor(ci);
   unrolledsPhist__2->SetMarkerStyle(20);
   unrolledsPhist__2->GetXaxis()->SetLabelFont(42);
   unrolledsPhist__2->GetXaxis()->SetLabelOffset(0.007);
   unrolledsPhist__2->GetXaxis()->SetTitleSize(0.06);
   unrolledsPhist__2->GetXaxis()->SetTitleOffset(0.9);
   unrolledsPhist__2->GetXaxis()->SetTitleFont(42);
   unrolledsPhist__2->GetYaxis()->SetLabelFont(42);
   unrolledsPhist__2->GetYaxis()->SetLabelOffset(0.007);
   unrolledsPhist__2->GetYaxis()->SetTitleSize(0.06);
   unrolledsPhist__2->GetYaxis()->SetTitleOffset(1.1);
   unrolledsPhist__2->GetYaxis()->SetTitleFont(42);
   unrolledsPhist__2->GetZaxis()->SetLabelFont(42);
   unrolledsPhist__2->GetZaxis()->SetLabelOffset(0.007);
   unrolledsPhist__2->GetZaxis()->SetTitleSize(0.06);
   unrolledsPhist__2->GetZaxis()->SetTitleFont(42);
   hs->Add(unrolled hist,"");
   
   TH1D *unrolledsPhist__3 = new TH1D("unrolledsPhist__3","unrolled hist",7,0,7);
   unrolledsPhist__3->SetEntries(7);

   ci = TColor::GetColor("#6666cc");
   unrolledsPhist__3->SetFillColor(ci);

   ci = TColor::GetColor("#6666cc");
   unrolledsPhist__3->SetLineColor(ci);
   unrolledsPhist__3->SetLineStyle(0);
   unrolledsPhist__3->SetLineWidth(2);

   ci = TColor::GetColor("#6666cc");
   unrolledsPhist__3->SetMarkerColor(ci);
   unrolledsPhist__3->SetMarkerStyle(20);
   unrolledsPhist__3->GetXaxis()->SetLabelFont(42);
   unrolledsPhist__3->GetXaxis()->SetLabelOffset(0.007);
   unrolledsPhist__3->GetXaxis()->SetTitleSize(0.06);
   unrolledsPhist__3->GetXaxis()->SetTitleOffset(0.9);
   unrolledsPhist__3->GetXaxis()->SetTitleFont(42);
   unrolledsPhist__3->GetYaxis()->SetLabelFont(42);
   unrolledsPhist__3->GetYaxis()->SetLabelOffset(0.007);
   unrolledsPhist__3->GetYaxis()->SetTitleSize(0.06);
   unrolledsPhist__3->GetYaxis()->SetTitleOffset(1.1);
   unrolledsPhist__3->GetYaxis()->SetTitleFont(42);
   unrolledsPhist__3->GetZaxis()->SetLabelFont(42);
   unrolledsPhist__3->GetZaxis()->SetLabelOffset(0.007);
   unrolledsPhist__3->GetZaxis()->SetTitleSize(0.06);
   unrolledsPhist__3->GetZaxis()->SetTitleFont(42);
   hs->Add(unrolled hist,"");
   
   TH1D *unrolledsPhist__4 = new TH1D("unrolledsPhist__4","unrolled hist",7,0,7);
   unrolledsPhist__4->SetEntries(7);

   ci = TColor::GetColor("#000099");
   unrolledsPhist__4->SetFillColor(ci);

   ci = TColor::GetColor("#000099");
   unrolledsPhist__4->SetLineColor(ci);
   unrolledsPhist__4->SetLineStyle(0);
   unrolledsPhist__4->SetLineWidth(2);

   ci = TColor::GetColor("#000099");
   unrolledsPhist__4->SetMarkerColor(ci);
   unrolledsPhist__4->SetMarkerStyle(20);
   unrolledsPhist__4->GetXaxis()->SetLabelFont(42);
   unrolledsPhist__4->GetXaxis()->SetLabelOffset(0.007);
   unrolledsPhist__4->GetXaxis()->SetTitleSize(0.06);
   unrolledsPhist__4->GetXaxis()->SetTitleOffset(0.9);
   unrolledsPhist__4->GetXaxis()->SetTitleFont(42);
   unrolledsPhist__4->GetYaxis()->SetLabelFont(42);
   unrolledsPhist__4->GetYaxis()->SetLabelOffset(0.007);
   unrolledsPhist__4->GetYaxis()->SetTitleSize(0.06);
   unrolledsPhist__4->GetYaxis()->SetTitleOffset(1.1);
   unrolledsPhist__4->GetYaxis()->SetTitleFont(42);
   unrolledsPhist__4->GetZaxis()->SetLabelFont(42);
   unrolledsPhist__4->GetZaxis()->SetLabelOffset(0.007);
   unrolledsPhist__4->GetZaxis()->SetTitleSize(0.06);
   unrolledsPhist__4->GetZaxis()->SetTitleFont(42);
   hs->Add(unrolled hist,"");
   
   TH1D *unrolledsPhist__5 = new TH1D("unrolledsPhist__5","unrolled hist",7,0,7);
   unrolledsPhist__5->SetBinContent(1,4.441757);
   unrolledsPhist__5->SetBinContent(2,0.899087);
   unrolledsPhist__5->SetBinContent(3,0.102959);
   unrolledsPhist__5->SetBinContent(4,3.770669);
   unrolledsPhist__5->SetBinContent(5,1.320594);
   unrolledsPhist__5->SetBinContent(6,0.732366);
   unrolledsPhist__5->SetBinContent(7,1.834846);
   unrolledsPhist__5->SetBinError(1,0.9999636);
   unrolledsPhist__5->SetBinError(2,0.3890702);
   unrolledsPhist__5->SetBinError(3,0.102959);
   unrolledsPhist__5->SetBinError(4,0.9289053);
   unrolledsPhist__5->SetBinError(5,0.545341);
   unrolledsPhist__5->SetBinError(6,0.4228317);
   unrolledsPhist__5->SetEntries(7);

   ci = TColor::GetColor("#ffff00");
   unrolledsPhist__5->SetFillColor(ci);

   ci = TColor::GetColor("#ffff00");
   unrolledsPhist__5->SetLineColor(ci);
   unrolledsPhist__5->SetLineStyle(0);
   unrolledsPhist__5->SetLineWidth(2);

   ci = TColor::GetColor("#ffff00");
   unrolledsPhist__5->SetMarkerColor(ci);
   unrolledsPhist__5->SetMarkerStyle(20);
   unrolledsPhist__5->GetXaxis()->SetLabelFont(42);
   unrolledsPhist__5->GetXaxis()->SetLabelOffset(0.007);
   unrolledsPhist__5->GetXaxis()->SetTitleSize(0.06);
   unrolledsPhist__5->GetXaxis()->SetTitleOffset(0.9);
   unrolledsPhist__5->GetXaxis()->SetTitleFont(42);
   unrolledsPhist__5->GetYaxis()->SetLabelFont(42);
   unrolledsPhist__5->GetYaxis()->SetLabelOffset(0.007);
   unrolledsPhist__5->GetYaxis()->SetTitleSize(0.06);
   unrolledsPhist__5->GetYaxis()->SetTitleOffset(1.1);
   unrolledsPhist__5->GetYaxis()->SetTitleFont(42);
   unrolledsPhist__5->GetZaxis()->SetLabelFont(42);
   unrolledsPhist__5->GetZaxis()->SetLabelOffset(0.007);
   unrolledsPhist__5->GetZaxis()->SetTitleSize(0.06);
   unrolledsPhist__5->GetZaxis()->SetTitleFont(42);
   hs->Add(unrolled hist,"");
   
   TH1D *unrolledsPhist__6 = new TH1D("unrolledsPhist__6","unrolled hist",7,0,7);
   unrolledsPhist__6->SetBinContent(1,5.259431);
   unrolledsPhist__6->SetBinContent(2,1.740147);
   unrolledsPhist__6->SetBinContent(3,0.6179744);
   unrolledsPhist__6->SetBinContent(4,5.794332);
   unrolledsPhist__6->SetBinContent(5,1.704559);
   unrolledsPhist__6->SetBinContent(6,0.8658185);
   unrolledsPhist__6->SetBinContent(7,2.420192);
   unrolledsPhist__6->SetBinError(1,1.178007);
   unrolledsPhist__6->SetBinError(2,0.6106667);
   unrolledsPhist__6->SetBinError(3,0.2764299);
   unrolledsPhist__6->SetBinError(4,1.039386);
   unrolledsPhist__6->SetBinError(5,0.6007356);
   unrolledsPhist__6->SetBinError(6,0.415086);
   unrolledsPhist__6->SetEntries(7);

   ci = TColor::GetColor("#ff00ff");
   unrolledsPhist__6->SetFillColor(ci);

   ci = TColor::GetColor("#ff00ff");
   unrolledsPhist__6->SetLineColor(ci);
   unrolledsPhist__6->SetLineStyle(0);
   unrolledsPhist__6->SetLineWidth(2);

   ci = TColor::GetColor("#ff00ff");
   unrolledsPhist__6->SetMarkerColor(ci);
   unrolledsPhist__6->SetMarkerStyle(20);
   unrolledsPhist__6->GetXaxis()->SetLabelFont(42);
   unrolledsPhist__6->GetXaxis()->SetLabelOffset(0.007);
   unrolledsPhist__6->GetXaxis()->SetTitleSize(0.06);
   unrolledsPhist__6->GetXaxis()->SetTitleOffset(0.9);
   unrolledsPhist__6->GetXaxis()->SetTitleFont(42);
   unrolledsPhist__6->GetYaxis()->SetLabelFont(42);
   unrolledsPhist__6->GetYaxis()->SetLabelOffset(0.007);
   unrolledsPhist__6->GetYaxis()->SetTitleSize(0.06);
   unrolledsPhist__6->GetYaxis()->SetTitleOffset(1.1);
   unrolledsPhist__6->GetYaxis()->SetTitleFont(42);
   unrolledsPhist__6->GetZaxis()->SetLabelFont(42);
   unrolledsPhist__6->GetZaxis()->SetLabelOffset(0.007);
   unrolledsPhist__6->GetZaxis()->SetTitleSize(0.06);
   unrolledsPhist__6->GetZaxis()->SetTitleFont(42);
   hs->Add(unrolled hist,"");
   
   TH1D *unrolledsPhist__7 = new TH1D("unrolledsPhist__7","unrolled hist",7,0,7);
   unrolledsPhist__7->SetBinContent(1,1.765053);
   unrolledsPhist__7->SetBinContent(2,1.289461);
   unrolledsPhist__7->SetBinContent(3,0.9994529);
   unrolledsPhist__7->SetBinContent(4,0.2881472);
   unrolledsPhist__7->SetBinContent(5,0.8315984);
   unrolledsPhist__7->SetBinContent(6,1.866314);
   unrolledsPhist__7->SetBinContent(7,1.060907);
   unrolledsPhist__7->SetBinError(1,0.1461382);
   unrolledsPhist__7->SetBinError(2,0.1253148);
   unrolledsPhist__7->SetBinError(3,0.1104434);
   unrolledsPhist__7->SetBinError(4,0.05884027);
   unrolledsPhist__7->SetBinError(5,0.1001477);
   unrolledsPhist__7->SetBinError(6,0.1504425);
   unrolledsPhist__7->SetEntries(7);

   ci = TColor::GetColor("#ff3333");
   unrolledsPhist__7->SetFillColor(ci);

   ci = TColor::GetColor("#ff3333");
   unrolledsPhist__7->SetLineColor(ci);
   unrolledsPhist__7->SetLineStyle(0);
   unrolledsPhist__7->SetLineWidth(2);

   ci = TColor::GetColor("#ff3333");
   unrolledsPhist__7->SetMarkerColor(ci);
   unrolledsPhist__7->SetMarkerStyle(21);
   unrolledsPhist__7->GetXaxis()->SetLabelFont(42);
   unrolledsPhist__7->GetXaxis()->SetLabelOffset(0.007);
   unrolledsPhist__7->GetXaxis()->SetTitleSize(0.06);
   unrolledsPhist__7->GetXaxis()->SetTitleOffset(0.9);
   unrolledsPhist__7->GetXaxis()->SetTitleFont(42);
   unrolledsPhist__7->GetYaxis()->SetLabelFont(42);
   unrolledsPhist__7->GetYaxis()->SetLabelOffset(0.007);
   unrolledsPhist__7->GetYaxis()->SetTitleSize(0.06);
   unrolledsPhist__7->GetYaxis()->SetTitleOffset(1.1);
   unrolledsPhist__7->GetYaxis()->SetTitleFont(42);
   unrolledsPhist__7->GetZaxis()->SetLabelFont(42);
   unrolledsPhist__7->GetZaxis()->SetLabelOffset(0.007);
   unrolledsPhist__7->GetZaxis()->SetTitleSize(0.06);
   unrolledsPhist__7->GetZaxis()->SetTitleFont(42);
   hs->Add(unrolled hist,"");
   hs->Draw("hist");
   
   TLegend *leg = new TLegend(0.65,0.45,0.85,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("unrolled hist","EWK [8.10]","lpf");

   ci = TColor::GetColor("#ff3333");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ff3333");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#ff3333");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("unrolled hist","ZA [18.40]","lpf");

   ci = TColor::GetColor("#ff00ff");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ff00ff");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#ff00ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("unrolled hist","non-prompt [13.10]","lpf");

   ci = TColor::GetColor("#ffff00");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ffff00");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#ffff00");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("unrolled hist","WA [0.00]","lpf");

   ci = TColor::GetColor("#000099");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#000099");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#000099");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("unrolled hist","VV [0.00]","lpf");

   ci = TColor::GetColor("#6666cc");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#6666cc");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#6666cc");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("unrolled hist","TTA [0.33]","lpf");

   ci = TColor::GetColor("#00ffff");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#00ffff");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#00ffff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("unrolled hist","ST  [0.00]","lpf");

   ci = TColor::GetColor("#00ff00");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#00ff00");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#00ff00");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
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
      tex = new TLatex(0.76,0.92,"35.862 fb^{-1} (13 TeV)");
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
