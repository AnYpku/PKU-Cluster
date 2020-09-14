void aa()
{
//=========Macro generated from canvas: /
//=========  (Sun Jan 19 22:44:53 2020) by ROOT version6.10/09
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
   pad1->Range(-0.1875,-143.4166,1.0625,959.7877);
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
   
   TH1F *hs_stack_1 = new TH1F("hs_stack_1","",1,0,1);
   hs_stack_1->SetMinimum(0);
   hs_stack_1->SetMaximum(860.4993);
   hs_stack_1->SetDirectory(0);
   hs_stack_1->SetStats(0);
   hs_stack_1->SetLineStyle(0);
   hs_stack_1->SetLineWidth(2);
   hs_stack_1->SetMarkerStyle(20);
   hs_stack_1->GetXaxis()->SetBinLabel(1,"Mjj 150~400");
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
   
   
   TH1D *ST_stack_1 = new TH1D("ST_stack_1","",1,0,1);
   ST_stack_1->SetBinContent(1,2.642779);
   ST_stack_1->SetBinError(1,0.6964701);
   ST_stack_1->SetEntries(1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#00ff00");
   ST_stack_1->SetFillColor(ci);

   ci = TColor::GetColor("#00ff00");
   ST_stack_1->SetLineColor(ci);
   ST_stack_1->SetLineStyle(0);
   ST_stack_1->SetLineWidth(2);

   ci = TColor::GetColor("#00ff00");
   ST_stack_1->SetMarkerColor(ci);
   ST_stack_1->SetMarkerStyle(20);
   ST_stack_1->GetXaxis()->SetBinLabel(1,"Mjj 150~400");
   ST_stack_1->GetXaxis()->SetLabelFont(42);
   ST_stack_1->GetXaxis()->SetLabelOffset(0.007);
   ST_stack_1->GetXaxis()->SetTitleSize(0.06);
   ST_stack_1->GetXaxis()->SetTitleOffset(0.9);
   ST_stack_1->GetXaxis()->SetTitleFont(42);
   ST_stack_1->GetYaxis()->SetLabelFont(42);
   ST_stack_1->GetYaxis()->SetLabelOffset(0.007);
   ST_stack_1->GetYaxis()->SetTitleSize(0.06);
   ST_stack_1->GetYaxis()->SetTitleOffset(1.1);
   ST_stack_1->GetYaxis()->SetTitleFont(42);
   ST_stack_1->GetZaxis()->SetLabelFont(42);
   ST_stack_1->GetZaxis()->SetLabelOffset(0.007);
   ST_stack_1->GetZaxis()->SetTitleSize(0.06);
   ST_stack_1->GetZaxis()->SetTitleFont(42);
   hs->Add(ST_stack_1,"");
   
   TH1D *TTA_stack_2 = new TH1D("TTA_stack_2","",1,0,1);
   TTA_stack_2->SetBinContent(1,18.92854);
   TTA_stack_2->SetBinError(1,1.715052);
   TTA_stack_2->SetEntries(1);

   ci = TColor::GetColor("#00ffff");
   TTA_stack_2->SetFillColor(ci);

   ci = TColor::GetColor("#00ffff");
   TTA_stack_2->SetLineColor(ci);
   TTA_stack_2->SetLineStyle(0);
   TTA_stack_2->SetLineWidth(2);

   ci = TColor::GetColor("#00ffff");
   TTA_stack_2->SetMarkerColor(ci);
   TTA_stack_2->SetMarkerStyle(20);
   TTA_stack_2->GetXaxis()->SetLabelFont(42);
   TTA_stack_2->GetXaxis()->SetLabelOffset(0.007);
   TTA_stack_2->GetXaxis()->SetTitleSize(0.06);
   TTA_stack_2->GetXaxis()->SetTitleOffset(0.9);
   TTA_stack_2->GetXaxis()->SetTitleFont(42);
   TTA_stack_2->GetYaxis()->SetLabelFont(42);
   TTA_stack_2->GetYaxis()->SetLabelOffset(0.007);
   TTA_stack_2->GetYaxis()->SetTitleSize(0.06);
   TTA_stack_2->GetYaxis()->SetTitleOffset(1.1);
   TTA_stack_2->GetYaxis()->SetTitleFont(42);
   TTA_stack_2->GetZaxis()->SetLabelFont(42);
   TTA_stack_2->GetZaxis()->SetLabelOffset(0.007);
   TTA_stack_2->GetZaxis()->SetTitleSize(0.06);
   TTA_stack_2->GetZaxis()->SetTitleFont(42);
   hs->Add(TTA_stack_2,"");
   
   TH1D *VV_stack_3 = new TH1D("VV_stack_3","",1,0,1);
   VV_stack_3->SetBinContent(1,6.593273);
   VV_stack_3->SetBinError(1,1.400525);
   VV_stack_3->SetEntries(1);

   ci = TColor::GetColor("#6666cc");
   VV_stack_3->SetFillColor(ci);

   ci = TColor::GetColor("#6666cc");
   VV_stack_3->SetLineColor(ci);
   VV_stack_3->SetLineStyle(0);
   VV_stack_3->SetLineWidth(2);

   ci = TColor::GetColor("#6666cc");
   VV_stack_3->SetMarkerColor(ci);
   VV_stack_3->SetMarkerStyle(20);
   VV_stack_3->GetXaxis()->SetLabelFont(42);
   VV_stack_3->GetXaxis()->SetLabelOffset(0.007);
   VV_stack_3->GetXaxis()->SetTitleSize(0.06);
   VV_stack_3->GetXaxis()->SetTitleOffset(0.9);
   VV_stack_3->GetXaxis()->SetTitleFont(42);
   VV_stack_3->GetYaxis()->SetLabelFont(42);
   VV_stack_3->GetYaxis()->SetLabelOffset(0.007);
   VV_stack_3->GetYaxis()->SetTitleSize(0.06);
   VV_stack_3->GetYaxis()->SetTitleOffset(1.1);
   VV_stack_3->GetYaxis()->SetTitleFont(42);
   VV_stack_3->GetZaxis()->SetLabelFont(42);
   VV_stack_3->GetZaxis()->SetLabelOffset(0.007);
   VV_stack_3->GetZaxis()->SetTitleSize(0.06);
   VV_stack_3->GetZaxis()->SetTitleFont(42);
   hs->Add(VV_stack_3,"");
   
   TH1D *WA_stack_4 = new TH1D("WA_stack_4","",1,0,1);
   WA_stack_4->SetEntries(1);

   ci = TColor::GetColor("#000099");
   WA_stack_4->SetFillColor(ci);

   ci = TColor::GetColor("#000099");
   WA_stack_4->SetLineColor(ci);
   WA_stack_4->SetLineStyle(0);
   WA_stack_4->SetLineWidth(2);

   ci = TColor::GetColor("#000099");
   WA_stack_4->SetMarkerColor(ci);
   WA_stack_4->SetMarkerStyle(20);
   WA_stack_4->GetXaxis()->SetLabelFont(42);
   WA_stack_4->GetXaxis()->SetLabelOffset(0.007);
   WA_stack_4->GetXaxis()->SetTitleSize(0.06);
   WA_stack_4->GetXaxis()->SetTitleOffset(0.9);
   WA_stack_4->GetXaxis()->SetTitleFont(42);
   WA_stack_4->GetYaxis()->SetLabelFont(42);
   WA_stack_4->GetYaxis()->SetLabelOffset(0.007);
   WA_stack_4->GetYaxis()->SetTitleSize(0.06);
   WA_stack_4->GetYaxis()->SetTitleOffset(1.1);
   WA_stack_4->GetYaxis()->SetTitleFont(42);
   WA_stack_4->GetZaxis()->SetLabelFont(42);
   WA_stack_4->GetZaxis()->SetLabelOffset(0.007);
   WA_stack_4->GetZaxis()->SetTitleSize(0.06);
   WA_stack_4->GetZaxis()->SetTitleFont(42);
   hs->Add(WA_stack_4,"");
   
   TH1D *plj_stack_5 = new TH1D("plj_stack_5","",1,0,1);
   plj_stack_5->SetBinContent(1,285.3287);
   plj_stack_5->SetBinError(1,9.998694);
   plj_stack_5->SetEntries(1);

   ci = TColor::GetColor("#ffff00");
   plj_stack_5->SetFillColor(ci);

   ci = TColor::GetColor("#ffff00");
   plj_stack_5->SetLineColor(ci);
   plj_stack_5->SetLineStyle(0);
   plj_stack_5->SetLineWidth(2);

   ci = TColor::GetColor("#ffff00");
   plj_stack_5->SetMarkerColor(ci);
   plj_stack_5->SetMarkerStyle(20);
   plj_stack_5->GetXaxis()->SetLabelFont(42);
   plj_stack_5->GetXaxis()->SetLabelOffset(0.007);
   plj_stack_5->GetXaxis()->SetTitleSize(0.06);
   plj_stack_5->GetXaxis()->SetTitleOffset(0.9);
   plj_stack_5->GetXaxis()->SetTitleFont(42);
   plj_stack_5->GetYaxis()->SetLabelFont(42);
   plj_stack_5->GetYaxis()->SetLabelOffset(0.007);
   plj_stack_5->GetYaxis()->SetTitleSize(0.06);
   plj_stack_5->GetYaxis()->SetTitleOffset(1.1);
   plj_stack_5->GetYaxis()->SetTitleFont(42);
   plj_stack_5->GetZaxis()->SetLabelFont(42);
   plj_stack_5->GetZaxis()->SetLabelOffset(0.007);
   plj_stack_5->GetZaxis()->SetTitleSize(0.06);
   plj_stack_5->GetZaxis()->SetTitleFont(42);
   hs->Add(plj_stack_5,"");
   
   TH1D *t_ZA_stack_6 = new TH1D("t_ZA_stack_6","",1,0,1);
   t_ZA_stack_6->SetBinContent(1,494.463);
   t_ZA_stack_6->SetBinError(1,9.805582);
   t_ZA_stack_6->SetEntries(1);

   ci = TColor::GetColor("#ff00ff");
   t_ZA_stack_6->SetFillColor(ci);

   ci = TColor::GetColor("#ff00ff");
   t_ZA_stack_6->SetLineColor(ci);
   t_ZA_stack_6->SetLineStyle(0);
   t_ZA_stack_6->SetLineWidth(2);

   ci = TColor::GetColor("#ff00ff");
   t_ZA_stack_6->SetMarkerColor(ci);
   t_ZA_stack_6->SetMarkerStyle(20);
   t_ZA_stack_6->GetXaxis()->SetLabelFont(42);
   t_ZA_stack_6->GetXaxis()->SetLabelOffset(0.007);
   t_ZA_stack_6->GetXaxis()->SetTitleSize(0.06);
   t_ZA_stack_6->GetXaxis()->SetTitleOffset(0.9);
   t_ZA_stack_6->GetXaxis()->SetTitleFont(42);
   t_ZA_stack_6->GetYaxis()->SetLabelFont(42);
   t_ZA_stack_6->GetYaxis()->SetLabelOffset(0.007);
   t_ZA_stack_6->GetYaxis()->SetTitleSize(0.06);
   t_ZA_stack_6->GetYaxis()->SetTitleOffset(1.1);
   t_ZA_stack_6->GetYaxis()->SetTitleFont(42);
   t_ZA_stack_6->GetZaxis()->SetLabelFont(42);
   t_ZA_stack_6->GetZaxis()->SetLabelOffset(0.007);
   t_ZA_stack_6->GetZaxis()->SetTitleSize(0.06);
   t_ZA_stack_6->GetZaxis()->SetTitleFont(42);
   hs->Add(t_ZA_stack_6,"");
   
   TH1D *ZA_sig_stack_7 = new TH1D("ZA_sig_stack_7","",1,0,1);
   ZA_sig_stack_7->SetBinContent(1,11.56688);
   ZA_sig_stack_7->SetBinError(1,0.4234945);
   ZA_sig_stack_7->SetEntries(1);

   ci = TColor::GetColor("#ff3333");
   ZA_sig_stack_7->SetFillColor(ci);

   ci = TColor::GetColor("#ff3333");
   ZA_sig_stack_7->SetLineColor(ci);
   ZA_sig_stack_7->SetLineStyle(0);
   ZA_sig_stack_7->SetLineWidth(2);

   ci = TColor::GetColor("#ff3333");
   ZA_sig_stack_7->SetMarkerColor(ci);
   ZA_sig_stack_7->SetMarkerStyle(21);
   ZA_sig_stack_7->GetXaxis()->SetLabelFont(42);
   ZA_sig_stack_7->GetXaxis()->SetLabelOffset(0.007);
   ZA_sig_stack_7->GetXaxis()->SetTitleSize(0.06);
   ZA_sig_stack_7->GetXaxis()->SetTitleOffset(0.9);
   ZA_sig_stack_7->GetXaxis()->SetTitleFont(42);
   ZA_sig_stack_7->GetYaxis()->SetLabelFont(42);
   ZA_sig_stack_7->GetYaxis()->SetLabelOffset(0.007);
   ZA_sig_stack_7->GetYaxis()->SetTitleSize(0.06);
   ZA_sig_stack_7->GetYaxis()->SetTitleOffset(1.1);
   ZA_sig_stack_7->GetYaxis()->SetTitleFont(42);
   ZA_sig_stack_7->GetZaxis()->SetLabelFont(42);
   ZA_sig_stack_7->GetZaxis()->SetLabelOffset(0.007);
   ZA_sig_stack_7->GetZaxis()->SetTitleSize(0.06);
   ZA_sig_stack_7->GetZaxis()->SetTitleFont(42);
   hs->Add(ZA_sig_stack_7,"");
   hs->Draw("hist");
   
   TLegend *leg = new TLegend(0.82,0.7,0.95,0.88,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("ZA_sig_stack_7","ZA_sig","lpf");

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
   entry=leg->AddEntry("t_ZA_stack_6","ZA","lpf");

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
   entry=leg->AddEntry("plj_stack_5","non-prompt","lpf");

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
   entry=leg->AddEntry("WA_stack_4","WA","lpf");

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
   entry=leg->AddEntry("VV_stack_3","VV","lpf");

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
   entry=leg->AddEntry("TTA_stack_2","TTA","lpf");

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
   entry=leg->AddEntry("ST_stack_1","ST","lpf");

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
      tex = new TLatex(0.76,0.92,"41.52 fb^{-1} (13 TeV)");
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
