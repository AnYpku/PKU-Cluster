void aa()
{
//=========Macro generated from canvas: /
//=========  (Mon Jun  8 03:45:41 2020) by ROOT version 6.12/07
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
   pad1->Range(-1.3125,-12.40525,7.4375,83.01978);
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
   hs->SetMaximum(70.88716);
   
   TH1F *hs_stack_1 = new TH1F("hs_stack_1","",7,0,7);
   hs_stack_1->SetMinimum(0);
   hs_stack_1->SetMaximum(74.43152);
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
   
   
   TH1D *unrolledsPhist_stack_1 = new TH1D("unrolledsPhist_stack_1","unrolled hist",7,0,7);
   unrolledsPhist_stack_1->SetBinContent(1,0.4847301);
   unrolledsPhist_stack_1->SetBinContent(4,0.1953613);
   unrolledsPhist_stack_1->SetBinError(1,0.3435251);
   unrolledsPhist_stack_1->SetBinError(4,0.1953613);
   unrolledsPhist_stack_1->SetEntries(7);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#33ff33");
   unrolledsPhist_stack_1->SetFillColor(ci);

   ci = TColor::GetColor("#33ff33");
   unrolledsPhist_stack_1->SetLineColor(ci);
   unrolledsPhist_stack_1->SetLineStyle(0);
   unrolledsPhist_stack_1->SetLineWidth(2);

   ci = TColor::GetColor("#33ff33");
   unrolledsPhist_stack_1->SetMarkerColor(ci);
   unrolledsPhist_stack_1->SetMarkerStyle(20);
   unrolledsPhist_stack_1->GetXaxis()->SetBinLabel(1,"Mjj 500~800");
   unrolledsPhist_stack_1->GetXaxis()->SetBinLabel(2,"Mjj 800~1000");
   unrolledsPhist_stack_1->GetXaxis()->SetBinLabel(3,"Mjj 1200~2000");
   unrolledsPhist_stack_1->GetXaxis()->SetBinLabel(4,"Mjj 500~800");
   unrolledsPhist_stack_1->GetXaxis()->SetBinLabel(5,"Mjj 800~1000");
   unrolledsPhist_stack_1->GetXaxis()->SetBinLabel(6,"Mjj 1200~2000");
   unrolledsPhist_stack_1->GetXaxis()->SetBinLabel(7,"Mjj 500~2000");
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
   
   TH1D *unrolledsPhist_stack_2 = new TH1D("unrolledsPhist_stack_2","unrolled hist",7,0,7);
   unrolledsPhist_stack_2->SetBinContent(1,0.1473504);
   unrolledsPhist_stack_2->SetBinContent(2,0.6570108);
   unrolledsPhist_stack_2->SetBinContent(3,0.3647233);
   unrolledsPhist_stack_2->SetBinContent(4,-0.152539);
   unrolledsPhist_stack_2->SetBinContent(5,0.00992473);
   unrolledsPhist_stack_2->SetBinContent(6,0.2394498);
   unrolledsPhist_stack_2->SetBinContent(7,0.2214106);
   unrolledsPhist_stack_2->SetBinError(1,0.4544371);
   unrolledsPhist_stack_2->SetBinError(2,0.3709705);
   unrolledsPhist_stack_2->SetBinError(3,0.2115774);
   unrolledsPhist_stack_2->SetBinError(4,0.3351587);
   unrolledsPhist_stack_2->SetBinError(5,0.1701037);
   unrolledsPhist_stack_2->SetBinError(6,0.1693266);
   unrolledsPhist_stack_2->SetEntries(7);

   ci = TColor::GetColor("#ccffcc");
   unrolledsPhist_stack_2->SetFillColor(ci);

   ci = TColor::GetColor("#ccffcc");
   unrolledsPhist_stack_2->SetLineColor(ci);
   unrolledsPhist_stack_2->SetLineStyle(0);
   unrolledsPhist_stack_2->SetLineWidth(2);

   ci = TColor::GetColor("#ccffcc");
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
   
   TH1D *unrolledsPhist_stack_3 = new TH1D("unrolledsPhist_stack_3","unrolled hist",7,0,7);
   unrolledsPhist_stack_3->SetBinContent(1,1.163758);
   unrolledsPhist_stack_3->SetBinContent(3,0.3795467);
   unrolledsPhist_stack_3->SetBinContent(4,0.7401595);
   unrolledsPhist_stack_3->SetBinContent(5,0.3375475);
   unrolledsPhist_stack_3->SetBinError(1,0.6820268);
   unrolledsPhist_stack_3->SetBinError(3,0.3795467);
   unrolledsPhist_stack_3->SetBinError(4,0.5268886);
   unrolledsPhist_stack_3->SetBinError(5,0.3375475);
   unrolledsPhist_stack_3->SetEntries(7);

   ci = TColor::GetColor("#ccffcc");
   unrolledsPhist_stack_3->SetFillColor(ci);

   ci = TColor::GetColor("#ccffcc");
   unrolledsPhist_stack_3->SetLineColor(ci);
   unrolledsPhist_stack_3->SetLineStyle(0);
   unrolledsPhist_stack_3->SetLineWidth(2);

   ci = TColor::GetColor("#ccffcc");
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
   
   TH1D *unrolledsPhist_stack_4 = new TH1D("unrolledsPhist_stack_4","unrolled hist",7,0,7);
   unrolledsPhist_stack_4->SetEntries(7);

   ci = TColor::GetColor("#6666ff");
   unrolledsPhist_stack_4->SetFillColor(ci);

   ci = TColor::GetColor("#6666ff");
   unrolledsPhist_stack_4->SetLineColor(ci);
   unrolledsPhist_stack_4->SetLineStyle(0);
   unrolledsPhist_stack_4->SetLineWidth(2);

   ci = TColor::GetColor("#6666ff");
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
   
   TH1D *unrolledsPhist_stack_5 = new TH1D("unrolledsPhist_stack_5","unrolled hist",7,0,7);
   unrolledsPhist_stack_5->SetBinContent(1,12.16833);
   unrolledsPhist_stack_5->SetBinContent(2,0.743091);
   unrolledsPhist_stack_5->SetBinContent(4,19.09258);
   unrolledsPhist_stack_5->SetBinContent(5,6.352399);
   unrolledsPhist_stack_5->SetBinContent(6,1.418142);
   unrolledsPhist_stack_5->SetBinContent(7,11.55996);
   unrolledsPhist_stack_5->SetBinError(1,2.021625);
   unrolledsPhist_stack_5->SetBinError(2,0.4785975);
   unrolledsPhist_stack_5->SetBinError(4,2.634302);
   unrolledsPhist_stack_5->SetBinError(5,1.512655);
   unrolledsPhist_stack_5->SetBinError(6,0.598465);
   unrolledsPhist_stack_5->SetEntries(7);

   ci = TColor::GetColor("#ffcc33");
   unrolledsPhist_stack_5->SetFillColor(ci);

   ci = TColor::GetColor("#ffcc33");
   unrolledsPhist_stack_5->SetLineColor(ci);
   unrolledsPhist_stack_5->SetLineStyle(0);
   unrolledsPhist_stack_5->SetLineWidth(2);

   ci = TColor::GetColor("#ffcc33");
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
   
   TH1D *unrolledsPhist_stack_6 = new TH1D("unrolledsPhist_stack_6","unrolled hist",7,0,7);
   unrolledsPhist_stack_6->SetBinContent(1,24.31164);
   unrolledsPhist_stack_6->SetBinContent(2,5.570548);
   unrolledsPhist_stack_6->SetBinContent(3,1.097247);
   unrolledsPhist_stack_6->SetBinContent(4,27.63722);
   unrolledsPhist_stack_6->SetBinContent(5,11.75839);
   unrolledsPhist_stack_6->SetBinContent(6,2.193929);
   unrolledsPhist_stack_6->SetBinContent(7,14.55868);
   unrolledsPhist_stack_6->SetBinError(1,3.780616);
   unrolledsPhist_stack_6->SetBinError(2,1.604271);
   unrolledsPhist_stack_6->SetBinError(3,0.8401799);
   unrolledsPhist_stack_6->SetBinError(4,4.142601);
   unrolledsPhist_stack_6->SetBinError(5,2.500843);
   unrolledsPhist_stack_6->SetBinError(6,0.8969943);
   unrolledsPhist_stack_6->SetEntries(7);

   ci = TColor::GetColor("#ff6666");
   unrolledsPhist_stack_6->SetFillColor(ci);

   ci = TColor::GetColor("#ff6666");
   unrolledsPhist_stack_6->SetLineColor(ci);
   unrolledsPhist_stack_6->SetLineStyle(0);
   unrolledsPhist_stack_6->SetLineWidth(2);

   ci = TColor::GetColor("#ff6666");
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
   
   TH1D *unrolledsPhist_stack_7 = new TH1D("unrolledsPhist_stack_7","unrolled hist",7,0,7);
   unrolledsPhist_stack_7->SetBinContent(1,7.929587);
   unrolledsPhist_stack_7->SetBinContent(2,6.391691);
   unrolledsPhist_stack_7->SetBinContent(3,4.553414);
   unrolledsPhist_stack_7->SetBinContent(4,1.374918);
   unrolledsPhist_stack_7->SetBinContent(5,3.303559);
   unrolledsPhist_stack_7->SetBinContent(6,5.961218);
   unrolledsPhist_stack_7->SetBinContent(7,3.012038);
   unrolledsPhist_stack_7->SetBinError(1,0.4164815);
   unrolledsPhist_stack_7->SetBinError(2,0.3745807);
   unrolledsPhist_stack_7->SetBinError(3,0.3154036);
   unrolledsPhist_stack_7->SetBinError(4,0.1723177);
   unrolledsPhist_stack_7->SetBinError(5,0.2671687);
   unrolledsPhist_stack_7->SetBinError(6,0.363425);
   unrolledsPhist_stack_7->SetEntries(7);

   ci = TColor::GetColor("#ff0000");
   unrolledsPhist_stack_7->SetFillColor(ci);

   ci = TColor::GetColor("#ff0000");
   unrolledsPhist_stack_7->SetLineColor(ci);
   unrolledsPhist_stack_7->SetLineStyle(0);
   unrolledsPhist_stack_7->SetLineWidth(2);

   ci = TColor::GetColor("#ff0000");
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
   TLegendEntry *entry=leg->AddEntry("unrolled hist_stack_7","EWK [32.53]","lpf");

   ci = TColor::GetColor("#ff0000");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("unrolled hist_stack_6","ZA [87.13]","lpf");

   ci = TColor::GetColor("#ff6666");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ff6666");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#ff6666");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("unrolled hist_stack_5","non-prompt [51.33]","lpf");

   ci = TColor::GetColor("#ffcc33");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ffcc33");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#ffcc33");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("unrolled hist_stack_4","WA [0.00]","lpf");

   ci = TColor::GetColor("#6666ff");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#6666ff");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#6666ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("unrolled hist_stack_3","VV [2.62]","lpf");

   ci = TColor::GetColor("#ccffcc");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ccffcc");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#ccffcc");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("unrolled hist_stack_2","TTA [1.49]","lpf");

   ci = TColor::GetColor("#ccffcc");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#ccffcc");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#ccffcc");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("unrolled hist_stack_1","ST  [0.68]","lpf");

   ci = TColor::GetColor("#33ff33");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#33ff33");
   entry->SetLineColor(ci);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#33ff33");
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
