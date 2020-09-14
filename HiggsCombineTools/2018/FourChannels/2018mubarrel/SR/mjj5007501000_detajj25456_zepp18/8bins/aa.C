void aa()
{
//=========Macro generated from canvas: /
//=========  (Tue Apr 28 12:37:27 2020) by ROOT version 6.12/07
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
   pad1->Range(-1.5,-20.26361,8.5,135.6103);
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
   hs->SetMaximum(115.792);
   
   TH1F *hs_stack_1 = new TH1F("hs_stack_1","",8,0,8);
   hs_stack_1->SetMinimum(0);
   hs_stack_1->SetMaximum(121.5816);
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
   hs_stack_1->GetXaxis()->SetBinLabel(8,"px•9Ã");
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
   
   
   TH1D *unrolledsPhist_stack_1 = new TH1D("unrolledsPhist_stack_1","unrolled hist",8,0,8);
   unrolledsPhist_stack_1->SetBinContent(1,0.2054346);
   unrolledsPhist_stack_1->SetBinError(1,0.2054346);
   unrolledsPhist_stack_1->SetEntries(8);

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
   unrolledsPhist_stack_1->GetXaxis()->SetBinLabel(1,"Mjj 500~800");
   unrolledsPhist_stack_1->GetXaxis()->SetBinLabel(2,"Mjj 800~1000");
   unrolledsPhist_stack_1->GetXaxis()->SetBinLabel(3,"Mjj 1200~2000");
   unrolledsPhist_stack_1->GetXaxis()->SetBinLabel(4,"Mjj 500~800");
   unrolledsPhist_stack_1->GetXaxis()->SetBinLabel(5,"Mjj 800~1000");
   unrolledsPhist_stack_1->GetXaxis()->SetBinLabel(6,"Mjj 1200~2000");
   unrolledsPhist_stack_1->GetXaxis()->SetBinLabel(7,"Mjj 500~2000");
   unrolledsPhist_stack_1->GetXaxis()->SetBinLabel(8,"px•9Ã");
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
   
   TH1D *unrolledsPhist_stack_2 = new TH1D("unrolledsPhist_stack_2","unrolled hist",8,0,8);
   unrolledsPhist_stack_2->SetBinContent(1,1.603482);
   unrolledsPhist_stack_2->SetBinContent(2,0.5477401);
   unrolledsPhist_stack_2->SetBinContent(3,0.3737356);
   unrolledsPhist_stack_2->SetBinContent(4,0.7843642);
   unrolledsPhist_stack_2->SetBinContent(5,0.5149172);
   unrolledsPhist_stack_2->SetBinContent(6,0.5284774);
   unrolledsPhist_stack_2->SetBinContent(7,-0.00633875);
   unrolledsPhist_stack_2->SetBinContent(8,0.2902446);
   unrolledsPhist_stack_2->SetBinError(1,0.791876);
   unrolledsPhist_stack_2->SetBinError(2,0.4792489);
   unrolledsPhist_stack_2->SetBinError(3,0.2764141);
   unrolledsPhist_stack_2->SetBinError(4,0.3633771);
   unrolledsPhist_stack_2->SetBinError(5,0.3574193);
   unrolledsPhist_stack_2->SetBinError(6,0.3224656);
   unrolledsPhist_stack_2->SetEntries(8);

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
   
   TH1D *unrolledsPhist_stack_3 = new TH1D("unrolledsPhist_stack_3","unrolled hist",8,0,8);
   unrolledsPhist_stack_3->SetBinContent(1,0.7866766);
   unrolledsPhist_stack_3->SetBinContent(2,0.6973315);
   unrolledsPhist_stack_3->SetBinContent(7,1.174724);
   unrolledsPhist_stack_3->SetBinError(1,0.5562792);
   unrolledsPhist_stack_3->SetBinError(2,0.4931278);
   unrolledsPhist_stack_3->SetEntries(8);

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
   
   TH1D *unrolledsPhist_stack_4 = new TH1D("unrolledsPhist_stack_4","unrolled hist",8,0,8);
   unrolledsPhist_stack_4->SetEntries(8);

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
   
   TH1D *unrolledsPhist_stack_5 = new TH1D("unrolledsPhist_stack_5","unrolled hist",8,0,8);
   unrolledsPhist_stack_5->SetBinContent(1,23.96688);
   unrolledsPhist_stack_5->SetBinContent(2,4.220245);
   unrolledsPhist_stack_5->SetBinContent(3,1.724982);
   unrolledsPhist_stack_5->SetBinContent(4,31.72532);
   unrolledsPhist_stack_5->SetBinContent(5,14.83266);
   unrolledsPhist_stack_5->SetBinContent(6,3.265832);
   unrolledsPhist_stack_5->SetBinContent(7,18.09819);
   unrolledsPhist_stack_5->SetBinContent(8,12.82476);
   unrolledsPhist_stack_5->SetBinError(1,2.772783);
   unrolledsPhist_stack_5->SetBinError(2,1.172242);
   unrolledsPhist_stack_5->SetBinError(3,0.728968);
   unrolledsPhist_stack_5->SetBinError(4,3.270976);
   unrolledsPhist_stack_5->SetBinError(5,2.221558);
   unrolledsPhist_stack_5->SetBinError(6,0.9914894);
   unrolledsPhist_stack_5->SetEntries(8);

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
   
   TH1D *unrolledsPhist_stack_6 = new TH1D("unrolledsPhist_stack_6","unrolled hist",8,0,8);
   unrolledsPhist_stack_6->SetBinContent(1,34.52712);
   unrolledsPhist_stack_6->SetBinContent(2,7.701004);
   unrolledsPhist_stack_6->SetBinContent(3,3.043689);
   unrolledsPhist_stack_6->SetBinContent(4,45.00443);
   unrolledsPhist_stack_6->SetBinContent(5,16.87915);
   unrolledsPhist_stack_6->SetBinContent(6,1.731103);
   unrolledsPhist_stack_6->SetBinContent(7,13.45554);
   unrolledsPhist_stack_6->SetBinContent(8,11.18099);
   unrolledsPhist_stack_6->SetBinError(1,4.902126);
   unrolledsPhist_stack_6->SetBinError(2,2.017237);
   unrolledsPhist_stack_6->SetBinError(3,1.189079);
   unrolledsPhist_stack_6->SetBinError(4,5.353364);
   unrolledsPhist_stack_6->SetBinError(5,3.369796);
   unrolledsPhist_stack_6->SetBinError(6,1.34483);
   unrolledsPhist_stack_6->SetEntries(8);

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
   
   TH1D *unrolledsPhist_stack_7 = new TH1D("unrolledsPhist_stack_7","unrolled hist",8,0,8);
   unrolledsPhist_stack_7->SetBinContent(1,13.13507);
   unrolledsPhist_stack_7->SetBinContent(2,10.07016);
   unrolledsPhist_stack_7->SetBinContent(3,6.365804);
   unrolledsPhist_stack_7->SetBinContent(4,2.342467);
   unrolledsPhist_stack_7->SetBinContent(5,5.551283);
   unrolledsPhist_stack_7->SetBinContent(6,9.778908);
   unrolledsPhist_stack_7->SetBinContent(7,0.4992971);
   unrolledsPhist_stack_7->SetBinContent(8,3.795017);
   unrolledsPhist_stack_7->SetBinError(1,0.5394769);
   unrolledsPhist_stack_7->SetBinError(2,0.4735115);
   unrolledsPhist_stack_7->SetBinError(3,0.3776674);
   unrolledsPhist_stack_7->SetBinError(4,0.2280582);
   unrolledsPhist_stack_7->SetBinError(5,0.3509037);
   unrolledsPhist_stack_7->SetBinError(6,0.4675727);
   unrolledsPhist_stack_7->SetEntries(8);

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
   TLegendEntry *entry=leg->AddEntry("unrolled hist_stack_7","EWK [51.54]","lpf");

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
   entry=leg->AddEntry("unrolled hist_stack_6","ZA [133.52]","lpf");

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
   entry=leg->AddEntry("unrolled hist_stack_5","non-prompt [110.66]","lpf");

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
   entry=leg->AddEntry("unrolled hist_stack_3","VV [2.66]","lpf");

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
   entry=leg->AddEntry("unrolled hist_stack_2","TTA [4.64]","lpf");

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
   entry=leg->AddEntry("unrolled hist_stack_1","ST  [0.21]","lpf");

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
      tex = new TLatex(0.76,0.92,"58.6 fb^{-1} (13 TeV)");
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
