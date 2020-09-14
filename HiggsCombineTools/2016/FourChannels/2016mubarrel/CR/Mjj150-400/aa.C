void aa()
{
//=========Macro generated from canvas: /
//=========  (Fri Jun  5 00:04:05 2020) by ROOT version 6.12/07
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
   pad1->Range(-0.1875,-270.4995,1.0625,1810.266);
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
   hs->SetMaximum(1545.711);
   
   TH1F *hs_stack_1 = new TH1F("hs_stack_1","",1,0,1);
   hs_stack_1->SetMinimum(0);
   hs_stack_1->SetMaximum(1622.997);
   hs_stack_1->SetDirectory(0);
   hs_stack_1->SetStats(0);
   hs_stack_1->SetLineStyle(0);
   hs_stack_1->SetLineWidth(2);
   hs_stack_1->SetMarkerStyle(20);
   hs_stack_1->GetXaxis()->SetBinLabel(1,"Mjj 150~500");
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
   
   
   TH1D *unrolledsPhist_stack_1 = new TH1D("unrolledsPhist_stack_1","unrolled hist",1,0,1);
   unrolledsPhist_stack_1->SetBinContent(1,1.789032);
   unrolledsPhist_stack_1->SetBinError(1,0.5697309);
   unrolledsPhist_stack_1->SetEntries(1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#00ff00");
   unrolledsPhist_stack_1->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   unrolledsPhist_stack_1->SetLineColor(ci);
   unrolledsPhist_stack_1->SetLineStyle(0);
   unrolledsPhist_stack_1->SetLineWidth(2);

   ci = TColor::GetColor("#00ff00");
   unrolledsPhist_stack_1->SetMarkerColor(ci);
   unrolledsPhist_stack_1->SetMarkerStyle(20);
   unrolledsPhist_stack_1->GetXaxis()->SetBinLabel(1,"Mjj 150~500");
   unrolledsPhist_stack_1->GetXaxis()->SetLabelFont(42);
   unrolledsPhist_stack_1->GetXaxis()->SetLabelOffset(0.007);
   unrolledsPhist_stack_1->GetXaxis()->SetTitleSize(0.06);
   unrolledsPhist_stack_1->GetXaxis()->SetTitleOffset(0.9);
   unrolledsPhist_stack_1->GetXaxis()->SetTitleFont(42);
   unrolledsPhist_stack_1->GetYaxis()->SetLabelFont(42);
   unrolledsPhist_stack_1->GetYaxis()->SetLabelOffset(0.007);
   unrolledsPhist_stack_1->GetYaxis()->SetTitleSize(0.06);
   unrolledsPhist_stack_1->GetYaxis()->SetTitleOffset(1.1);
   unrolledsPhist_stack_1->GetYaxis()->SetTitleFont(42);
   unrolledsPhist_stack_1->GetZaxis()->SetLabelFont(42);
   unrolledsPhist_stack_1->GetZaxis()->SetLabelOffset(0.007);
   unrolledsPhist_stack_1->GetZaxis()->SetTitleSize(0.06);
   unrolledsPhist_stack_1->GetZaxis()->SetTitleFont(42);
   hs->Add(unrolled hist_stack_1,"");
   
   TH1D *unrolledsPhist_stack_2 = new TH1D("unrolledsPhist_stack_2","unrolled hist",1,0,1);
   unrolledsPhist_stack_2->SetBinContent(1,15.82389);
   unrolledsPhist_stack_2->SetBinError(1,2.30014);
   unrolledsPhist_stack_2->SetEntries(1);

   ci = TColor::GetColor("#00ffff");
   unrolledsPhist_stack_2->SetFillColor(ci);

   ci = TColor::GetColor("#00ffff");
   unrolledsPhist_stack_2->SetLineColor(ci);
   unrolledsPhist_stack_2->SetLineStyle(0);
   unrolledsPhist_stack_2->SetLineWidth(2);

   ci = TColor::GetColor("#00ffff");
   unrolledsPhist_stack_2->SetMarkerColor(ci);
   unrolledsPhist_stack_2->SetMarkerStyle(20);
   unrolledsPhist_stack_2->GetXaxis()->SetLabelFont(42);
   unrolledsPhist_stack_2->GetXaxis()->SetLabelOffset(0.007);
   unrolledsPhist_stack_2->GetXaxis()->SetTitleSize(0.06);
   unrolledsPhist_stack_2->GetXaxis()->SetTitleOffset(0.9);
   unrolledsPhist_stack_2->GetXaxis()->SetTitleFont(42);
   unrolledsPhist_stack_2->GetYaxis()->SetLabelFont(42);
   unrolledsPhist_stack_2->GetYaxis()->SetLabelOffset(0.007);
   unrolledsPhist_stack_2->GetYaxis()->SetTitleSize(0.06);
   unrolledsPhist_stack_2->GetYaxis()->SetTitleOffset(1.1);
   unrolledsPhist_stack_2->GetYaxis()->SetTitleFont(42);
   unrolledsPhist_stack_2->GetZaxis()->SetLabelFont(42);
   unrolledsPhist_stack_2->GetZaxis()->SetLabelOffset(0.007);
   unrolledsPhist_stack_2->GetZaxis()->SetTitleSize(0.06);
   unrolledsPhist_stack_2->GetZaxis()->SetTitleFont(42);
   hs->Add(unrolled hist_stack_2,"");
   
   TH1D *unrolledsPhist_stack_3 = new TH1D("unrolledsPhist_stack_3","unrolled hist",1,0,1);
   unrolledsPhist_stack_3->SetBinContent(1,18.08509);
   unrolledsPhist_stack_3->SetBinError(1,4.672145);
   unrolledsPhist_stack_3->SetEntries(1);

   ci = TColor::GetColor("#6666cc");
   unrolledsPhist_stack_3->SetFillColor(ci);

   ci = TColor::GetColor("#6666cc");
   unrolledsPhist_stack_3->SetLineColor(ci);
   unrolledsPhist_stack_3->SetLineStyle(0);
   unrolledsPhist_stack_3->SetLineWidth(2);

   ci = TColor::GetColor("#6666cc");
   unrolledsPhist_stack_3->SetMarkerColor(ci);
   unrolledsPhist_stack_3->SetMarkerStyle(20);
   unrolledsPhist_stack_3->GetXaxis()->SetLabelFont(42);
   unrolledsPhist_stack_3->GetXaxis()->SetLabelOffset(0.007);
   unrolledsPhist_stack_3->GetXaxis()->SetTitleSize(0.06);
   unrolledsPhist_stack_3->GetXaxis()->SetTitleOffset(0.9);
   unrolledsPhist_stack_3->GetXaxis()->SetTitleFont(42);
   unrolledsPhist_stack_3->GetYaxis()->SetLabelFont(42);
   unrolledsPhist_stack_3->GetYaxis()->SetLabelOffset(0.007);
   unrolledsPhist_stack_3->GetYaxis()->SetTitleSize(0.06);
   unrolledsPhist_stack_3->GetYaxis()->SetTitleOffset(1.1);
   unrolledsPhist_stack_3->GetYaxis()->SetTitleFont(42);
   unrolledsPhist_stack_3->GetZaxis()->SetLabelFont(42);
   unrolledsPhist_stack_3->GetZaxis()->SetLabelOffset(0.007);
   unrolledsPhist_stack_3->GetZaxis()->SetTitleSize(0.06);
   unrolledsPhist_stack_3->GetZaxis()->SetTitleFont(42);
   hs->Add(unrolled hist_stack_3,"");
   
   TH1D *unrolledsPhist_stack_4 = new TH1D("unrolledsPhist_stack_4","unrolled hist",1,0,1);
   unrolledsPhist_stack_4->SetEntries(1);

   ci = TColor::GetColor("#000099");
   unrolledsPhist_stack_4->SetFillColor(ci);

   ci = TColor::GetColor("#000099");
   unrolledsPhist_stack_4->SetLineColor(ci);
   unrolledsPhist_stack_4->SetLineStyle(0);
   unrolledsPhist_stack_4->SetLineWidth(2);

   ci = TColor::GetColor("#000099");
   unrolledsPhist_stack_4->SetMarkerColor(ci);
   unrolledsPhist_stack_4->SetMarkerStyle(20);
   unrolledsPhist_stack_4->GetXaxis()->SetLabelFont(42);
   unrolledsPhist_stack_4->GetXaxis()->SetLabelOffset(0.007);
   unrolledsPhist_stack_4->GetXaxis()->SetTitleSize(0.06);
   unrolledsPhist_stack_4->GetXaxis()->SetTitleOffset(0.9);
   unrolledsPhist_stack_4->GetXaxis()->SetTitleFont(42);
   unrolledsPhist_stack_4->GetYaxis()->SetLabelFont(42);
   unrolledsPhist_stack_4->GetYaxis()->SetLabelOffset(0.007);
   unrolledsPhist_stack_4->GetYaxis()->SetTitleSize(0.06);
   unrolledsPhist_stack_4->GetYaxis()->SetTitleOffset(1.1);
   unrolledsPhist_stack_4->GetYaxis()->SetTitleFont(42);
   unrolledsPhist_stack_4->GetZaxis()->SetLabelFont(42);
   unrolledsPhist_stack_4->GetZaxis()->SetLabelOffset(0.007);
   unrolledsPhist_stack_4->GetZaxis()->SetTitleSize(0.06);
   unrolledsPhist_stack_4->GetZaxis()->SetTitleFont(42);
   hs->Add(unrolled hist_stack_4,"");
   
   TH1D *unrolledsPhist_stack_5 = new TH1D("unrolledsPhist_stack_5","unrolled hist",1,0,1);
   unrolledsPhist_stack_5->SetBinContent(1,205.3513);
   unrolledsPhist_stack_5->SetBinError(1,8.026592);
   unrolledsPhist_stack_5->SetEntries(1);

   ci = TColor::GetColor("#ffff00");
   unrolledsPhist_stack_5->SetFillColor(ci);

   ci = TColor::GetColor("#ffff00");
   unrolledsPhist_stack_5->SetLineColor(ci);
   unrolledsPhist_stack_5->SetLineStyle(0);
   unrolledsPhist_stack_5->SetLineWidth(2);

   ci = TColor::GetColor("#ffff00");
   unrolledsPhist_stack_5->SetMarkerColor(ci);
   unrolledsPhist_stack_5->SetMarkerStyle(20);
   unrolledsPhist_stack_5->GetXaxis()->SetLabelFont(42);
   unrolledsPhist_stack_5->GetXaxis()->SetLabelOffset(0.007);
   unrolledsPhist_stack_5->GetXaxis()->SetTitleSize(0.06);
   unrolledsPhist_stack_5->GetXaxis()->SetTitleOffset(0.9);
   unrolledsPhist_stack_5->GetXaxis()->SetTitleFont(42);
   unrolledsPhist_stack_5->GetYaxis()->SetLabelFont(42);
   unrolledsPhist_stack_5->GetYaxis()->SetLabelOffset(0.007);
   unrolledsPhist_stack_5->GetYaxis()->SetTitleSize(0.06);
   unrolledsPhist_stack_5->GetYaxis()->SetTitleOffset(1.1);
   unrolledsPhist_stack_5->GetYaxis()->SetTitleFont(42);
   unrolledsPhist_stack_5->GetZaxis()->SetLabelFont(42);
   unrolledsPhist_stack_5->GetZaxis()->SetLabelOffset(0.007);
   unrolledsPhist_stack_5->GetZaxis()->SetTitleSize(0.06);
   unrolledsPhist_stack_5->GetZaxis()->SetTitleFont(42);
   hs->Add(unrolled hist_stack_5,"");
   
   TH1D *unrolledsPhist_stack_6 = new TH1D("unrolledsPhist_stack_6","unrolled hist",1,0,1);
   unrolledsPhist_stack_6->SetBinContent(1,519.4785);
   unrolledsPhist_stack_6->SetBinError(1,10.38161);
   unrolledsPhist_stack_6->SetEntries(1);

   ci = TColor::GetColor("#ff00ff");
   unrolledsPhist_stack_6->SetFillColor(ci);

   ci = TColor::GetColor("#ff00ff");
   unrolledsPhist_stack_6->SetLineColor(ci);
   unrolledsPhist_stack_6->SetLineStyle(0);
   unrolledsPhist_stack_6->SetLineWidth(2);

   ci = TColor::GetColor("#ff00ff");
   unrolledsPhist_stack_6->SetMarkerColor(ci);
   unrolledsPhist_stack_6->SetMarkerStyle(20);
   unrolledsPhist_stack_6->GetXaxis()->SetLabelFont(42);
   unrolledsPhist_stack_6->GetXaxis()->SetLabelOffset(0.007);
   unrolledsPhist_stack_6->GetXaxis()->SetTitleSize(0.06);
   unrolledsPhist_stack_6->GetXaxis()->SetTitleOffset(0.9);
   unrolledsPhist_stack_6->GetXaxis()->SetTitleFont(42);
   unrolledsPhist_stack_6->GetYaxis()->SetLabelFont(42);
   unrolledsPhist_stack_6->GetYaxis()->SetLabelOffset(0.007);
   unrolledsPhist_stack_6->GetYaxis()->SetTitleSize(0.06);
   unrolledsPhist_stack_6->GetYaxis()->SetTitleOffset(1.1);
   unrolledsPhist_stack_6->GetYaxis()->SetTitleFont(42);
   unrolledsPhist_stack_6->GetZaxis()->SetLabelFont(42);
   unrolledsPhist_stack_6->GetZaxis()->SetLabelOffset(0.007);
   unrolledsPhist_stack_6->GetZaxis()->SetTitleSize(0.06);
   unrolledsPhist_stack_6->GetZaxis()->SetTitleFont(42);
   hs->Add(unrolled hist_stack_6,"");
   
   TH1D *unrolledsPhist_stack_7 = new TH1D("unrolledsPhist_stack_7","unrolled hist",1,0,1);
   unrolledsPhist_stack_7->SetBinContent(1,12.32787);
   unrolledsPhist_stack_7->SetBinError(1,0.4009325);
   unrolledsPhist_stack_7->SetEntries(1);

   ci = TColor::GetColor("#ff3333");
   unrolledsPhist_stack_7->SetFillColor(ci);

   ci = TColor::GetColor("#ff3333");
   unrolledsPhist_stack_7->SetLineColor(ci);
   unrolledsPhist_stack_7->SetLineStyle(0);
   unrolledsPhist_stack_7->SetLineWidth(2);

   ci = TColor::GetColor("#ff3333");
   unrolledsPhist_stack_7->SetMarkerColor(ci);
   unrolledsPhist_stack_7->SetMarkerStyle(21);
   unrolledsPhist_stack_7->GetXaxis()->SetLabelFont(42);
   unrolledsPhist_stack_7->GetXaxis()->SetLabelOffset(0.007);
   unrolledsPhist_stack_7->GetXaxis()->SetTitleSize(0.06);
   unrolledsPhist_stack_7->GetXaxis()->SetTitleOffset(0.9);
   unrolledsPhist_stack_7->GetXaxis()->SetTitleFont(42);
   unrolledsPhist_stack_7->GetYaxis()->SetLabelFont(42);
   unrolledsPhist_stack_7->GetYaxis()->SetLabelOffset(0.007);
   unrolledsPhist_stack_7->GetYaxis()->SetTitleSize(0.06);
   unrolledsPhist_stack_7->GetYaxis()->SetTitleOffset(1.1);
   unrolledsPhist_stack_7->GetYaxis()->SetTitleFont(42);
   unrolledsPhist_stack_7->GetZaxis()->SetLabelFont(42);
   unrolledsPhist_stack_7->GetZaxis()->SetLabelOffset(0.007);
   unrolledsPhist_stack_7->GetZaxis()->SetTitleSize(0.06);
   unrolledsPhist_stack_7->GetZaxis()->SetTitleFont(42);
   hs->Add(unrolled hist_stack_7,"");
   hs->Draw("hist");
   
   TLegend *leg = new TLegend(0.65,0.45,0.85,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("unrolled hist_stack_7","EWK [12.33]","lpf");

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
   entry=leg->AddEntry("unrolled hist_stack_6","ZA [519.48]","lpf");

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
   entry=leg->AddEntry("unrolled hist_stack_5","non-prompt [205.35]","lpf");

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
   entry=leg->AddEntry("unrolled hist_stack_4","WA [0.00]","lpf");

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
   entry=leg->AddEntry("unrolled hist_stack_3","VV [18.09]","lpf");

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
   entry=leg->AddEntry("unrolled hist_stack_2","TTA [15.82]","lpf");

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
   entry=leg->AddEntry("unrolled hist_stack_1","ST  [1.79]","lpf");

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
